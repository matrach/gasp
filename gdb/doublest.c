/* Floating point routines for GDB, the GNU debugger.
   Copyright 1986, 1988, 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996,
   1997, 1998, 1999, 2000, 2001
   Free Software Foundation, Inc.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* Support for converting target fp numbers into host DOUBLEST format.  */

/* XXX - This code should really be in libiberty/floatformat.c,
   however configuration issues with libiberty made this very
   difficult to do in the available time.  */

#include "defs.h"
#include "doublest.h"
#include "floatformat.h"
#include "gdb_assert.h"
#include "gdb_string.h"
#include <math.h>		/* ldexp */

/* The odds that CHAR_BIT will be anything but 8 are low enough that I'm not
   going to bother with trying to muck around with whether it is defined in
   a system header, what we do if not, etc.  */
#define FLOATFORMAT_CHAR_BIT 8

static unsigned long get_field (unsigned char *,
				enum floatformat_byteorders,
				unsigned int, unsigned int, unsigned int);

/* Extract a field which starts at START and is LEN bytes long.  DATA and
   TOTAL_LEN are the thing we are extracting it from, in byteorder ORDER.  */
static unsigned long
get_field (unsigned char *data, enum floatformat_byteorders order,
	   unsigned int total_len, unsigned int start, unsigned int len)
{
  unsigned long result;
  unsigned int cur_byte;
  int cur_bitshift;

  /* Start at the least significant part of the field.  */
  if (order == floatformat_little || order == floatformat_littlebyte_bigword)
    {
      /* We start counting from the other end (i.e, from the high bytes
	 rather than the low bytes).  As such, we need to be concerned
	 with what happens if bit 0 doesn't start on a byte boundary. 
	 I.e, we need to properly handle the case where total_len is
	 not evenly divisible by 8.  So we compute ``excess'' which
	 represents the number of bits from the end of our starting
	 byte needed to get to bit 0. */
      int excess = FLOATFORMAT_CHAR_BIT - (total_len % FLOATFORMAT_CHAR_BIT);
      cur_byte = (total_len / FLOATFORMAT_CHAR_BIT) 
                 - ((start + len + excess) / FLOATFORMAT_CHAR_BIT);
      cur_bitshift = ((start + len + excess) % FLOATFORMAT_CHAR_BIT) 
                     - FLOATFORMAT_CHAR_BIT;
    }
  else
    {
      cur_byte = (start + len) / FLOATFORMAT_CHAR_BIT;
      cur_bitshift =
	((start + len) % FLOATFORMAT_CHAR_BIT) - FLOATFORMAT_CHAR_BIT;
    }
  if (cur_bitshift > -FLOATFORMAT_CHAR_BIT)
    result = *(data + cur_byte) >> (-cur_bitshift);
  else
    result = 0;
  cur_bitshift += FLOATFORMAT_CHAR_BIT;
  if (order == floatformat_little || order == floatformat_littlebyte_bigword)
    ++cur_byte;
  else
    --cur_byte;

  /* Move towards the most significant part of the field.  */
  while (cur_bitshift < len)
    {
      result |= (unsigned long)*(data + cur_byte) << cur_bitshift;
      cur_bitshift += FLOATFORMAT_CHAR_BIT;
      if (order == floatformat_little || order == floatformat_littlebyte_bigword)
	++cur_byte;
      else
	--cur_byte;
    }
  if (len < sizeof(result) * FLOATFORMAT_CHAR_BIT)
    /* Mask out bits which are not part of the field */
    result &= ((1UL << len) - 1);
  return result;
}

/* Convert from FMT to a DOUBLEST.
   FROM is the address of the extended float.
   Store the DOUBLEST in *TO.  */

void
floatformat_to_doublest (const struct floatformat *fmt,
			 const void *from,
			 DOUBLEST *to)
{
  unsigned char *ufrom = (unsigned char *) from;
  DOUBLEST dto;
  long exponent;
  unsigned long mant;
  unsigned int mant_bits, mant_off;
  int mant_bits_left;
  int special_exponent;		/* It's a NaN, denorm or zero */

  /* If the mantissa bits are not contiguous from one end of the
     mantissa to the other, we need to make a private copy of the
     source bytes that is in the right order since the unpacking
     algorithm assumes that the bits are contiguous.

     Swap the bytes individually rather than accessing them through
     "long *" since we have no guarantee that they start on a long
     alignment, and also sizeof(long) for the host could be different
     than sizeof(long) for the target.  FIXME: Assumes sizeof(long)
     for the target is 4. */

  if (fmt->byteorder == floatformat_littlebyte_bigword)
    {
      static unsigned char *newfrom;
      unsigned char *swapin, *swapout;
      int longswaps;

      longswaps = fmt->totalsize / FLOATFORMAT_CHAR_BIT;
      longswaps >>= 3;

      if (newfrom == NULL)
	{
	  newfrom = (unsigned char *) xmalloc (fmt->totalsize);
	}
      swapout = newfrom;
      swapin = ufrom;
      ufrom = newfrom;
      while (longswaps-- > 0)
	{
	  /* This is ugly, but efficient */
	  *swapout++ = swapin[4];
	  *swapout++ = swapin[5];
	  *swapout++ = swapin[6];
	  *swapout++ = swapin[7];
	  *swapout++ = swapin[0];
	  *swapout++ = swapin[1];
	  *swapout++ = swapin[2];
	  *swapout++ = swapin[3];
	  swapin += 8;
	}
    }

  exponent = get_field (ufrom, fmt->byteorder, fmt->totalsize,
			fmt->exp_start, fmt->exp_len);
  /* Note that if exponent indicates a NaN, we can't really do anything useful
     (not knowing if the host has NaN's, or how to build one).  So it will
     end up as an infinity or something close; that is OK.  */

  mant_bits_left = fmt->man_len;
  mant_off = fmt->man_start;
  dto = 0.0;

  special_exponent = exponent == 0 || exponent == fmt->exp_nan;

/* Don't bias NaNs. Use minimum exponent for denorms. For simplicity,
   we don't check for zero as the exponent doesn't matter. */
  if (!special_exponent)
    exponent -= fmt->exp_bias;
  else if (exponent == 0)
    exponent = 1 - fmt->exp_bias;

  /* Build the result algebraically.  Might go infinite, underflow, etc;
     who cares. */

/* If this format uses a hidden bit, explicitly add it in now.  Otherwise,
   increment the exponent by one to account for the integer bit.  */

  if (!special_exponent)
    {
      if (fmt->intbit == floatformat_intbit_no)
	dto = ldexp (1.0, exponent);
      else
	exponent++;
    }

  while (mant_bits_left > 0)
    {
      mant_bits = min (mant_bits_left, 32);

      mant = get_field (ufrom, fmt->byteorder, fmt->totalsize,
			mant_off, mant_bits);

      dto += ldexp ((double) mant, exponent - mant_bits);
      exponent -= mant_bits;
      mant_off += mant_bits;
      mant_bits_left -= mant_bits;
    }

  /* Negate it if negative.  */
  if (get_field (ufrom, fmt->byteorder, fmt->totalsize, fmt->sign_start, 1))
    dto = -dto;
  *to = dto;
}

static void put_field (unsigned char *, enum floatformat_byteorders,
		       unsigned int,
		       unsigned int, unsigned int, unsigned long);

/* Set a field which starts at START and is LEN bytes long.  DATA and
   TOTAL_LEN are the thing we are extracting it from, in byteorder ORDER.  */
static void
put_field (unsigned char *data, enum floatformat_byteorders order,
	   unsigned int total_len, unsigned int start, unsigned int len,
	   unsigned long stuff_to_put)
{
  unsigned int cur_byte;
  int cur_bitshift;

  /* Start at the least significant part of the field.  */
  if (order == floatformat_little || order == floatformat_littlebyte_bigword)
    {
      int excess = FLOATFORMAT_CHAR_BIT - (total_len % FLOATFORMAT_CHAR_BIT);
      cur_byte = (total_len / FLOATFORMAT_CHAR_BIT) 
                 - ((start + len + excess) / FLOATFORMAT_CHAR_BIT);
      cur_bitshift = ((start + len + excess) % FLOATFORMAT_CHAR_BIT) 
                     - FLOATFORMAT_CHAR_BIT;
    }
  else
    {
      cur_byte = (start + len) / FLOATFORMAT_CHAR_BIT;
      cur_bitshift =
	((start + len) % FLOATFORMAT_CHAR_BIT) - FLOATFORMAT_CHAR_BIT;
    }
  if (cur_bitshift > -FLOATFORMAT_CHAR_BIT)
    {
      *(data + cur_byte) &=
	~(((1 << ((start + len) % FLOATFORMAT_CHAR_BIT)) - 1)
	  << (-cur_bitshift));
      *(data + cur_byte) |=
	(stuff_to_put & ((1 << FLOATFORMAT_CHAR_BIT) - 1)) << (-cur_bitshift);
    }
  cur_bitshift += FLOATFORMAT_CHAR_BIT;
  if (order == floatformat_little || order == floatformat_littlebyte_bigword)
    ++cur_byte;
  else
    --cur_byte;

  /* Move towards the most significant part of the field.  */
  while (cur_bitshift < len)
    {
      if (len - cur_bitshift < FLOATFORMAT_CHAR_BIT)
	{
	  /* This is the last byte.  */
	  *(data + cur_byte) &=
	    ~((1 << (len - cur_bitshift)) - 1);
	  *(data + cur_byte) |= (stuff_to_put >> cur_bitshift);
	}
      else
	*(data + cur_byte) = ((stuff_to_put >> cur_bitshift)
			      & ((1 << FLOATFORMAT_CHAR_BIT) - 1));
      cur_bitshift += FLOATFORMAT_CHAR_BIT;
      if (order == floatformat_little || order == floatformat_littlebyte_bigword)
	++cur_byte;
      else
	--cur_byte;
    }
}

#ifdef HAVE_LONG_DOUBLE
/* Return the fractional part of VALUE, and put the exponent of VALUE in *EPTR.
   The range of the returned value is >= 0.5 and < 1.0.  This is equivalent to
   frexp, but operates on the long double data type.  */

static long double ldfrexp (long double value, int *eptr);

static long double
ldfrexp (long double value, int *eptr)
{
  long double tmp;
  int exp;

  /* Unfortunately, there are no portable functions for extracting the exponent
     of a long double, so we have to do it iteratively by multiplying or dividing
     by two until the fraction is between 0.5 and 1.0.  */

  if (value < 0.0l)
    value = -value;

  tmp = 1.0l;
  exp = 0;

  if (value >= tmp)		/* Value >= 1.0 */
    while (value >= tmp)
      {
	tmp *= 2.0l;
	exp++;
      }
  else if (value != 0.0l)	/* Value < 1.0  and > 0.0 */
    {
      while (value < tmp)
	{
	  tmp /= 2.0l;
	  exp--;
	}
      tmp *= 2.0l;
      exp++;
    }

  *eptr = exp;
  return value / tmp;
}
#endif /* HAVE_LONG_DOUBLE */


/* The converse: convert the DOUBLEST *FROM to an extended float
   and store where TO points.  Neither FROM nor TO have any alignment
   restrictions.  */

void
floatformat_from_doublest (CONST struct floatformat *fmt,
			   const DOUBLEST *from,
			   void *to)
{
  DOUBLEST dfrom;
  int exponent;
  DOUBLEST mant;
  unsigned int mant_bits, mant_off;
  int mant_bits_left;
  unsigned char *uto = (unsigned char *) to;

  memcpy (&dfrom, from, sizeof (dfrom));
  memset (uto, 0, (fmt->totalsize + FLOATFORMAT_CHAR_BIT - 1) 
                    / FLOATFORMAT_CHAR_BIT);
  if (dfrom == 0)
    return;			/* Result is zero */
  if (dfrom != dfrom)		/* Result is NaN */
    {
      /* From is NaN */
      put_field (uto, fmt->byteorder, fmt->totalsize, fmt->exp_start,
		 fmt->exp_len, fmt->exp_nan);
      /* Be sure it's not infinity, but NaN value is irrel */
      put_field (uto, fmt->byteorder, fmt->totalsize, fmt->man_start,
		 32, 1);
      return;
    }

  /* If negative, set the sign bit.  */
  if (dfrom < 0)
    {
      put_field (uto, fmt->byteorder, fmt->totalsize, fmt->sign_start, 1, 1);
      dfrom = -dfrom;
    }

  if (dfrom + dfrom == dfrom && dfrom != 0.0)	/* Result is Infinity */
    {
      /* Infinity exponent is same as NaN's.  */
      put_field (uto, fmt->byteorder, fmt->totalsize, fmt->exp_start,
		 fmt->exp_len, fmt->exp_nan);
      /* Infinity mantissa is all zeroes.  */
      put_field (uto, fmt->byteorder, fmt->totalsize, fmt->man_start,
		 fmt->man_len, 0);
      return;
    }

#ifdef HAVE_LONG_DOUBLE
  mant = ldfrexp (dfrom, &exponent);
#else
  mant = frexp (dfrom, &exponent);
#endif

  put_field (uto, fmt->byteorder, fmt->totalsize, fmt->exp_start, fmt->exp_len,
	     exponent + fmt->exp_bias - 1);

  mant_bits_left = fmt->man_len;
  mant_off = fmt->man_start;
  while (mant_bits_left > 0)
    {
      unsigned long mant_long;
      mant_bits = mant_bits_left < 32 ? mant_bits_left : 32;

      mant *= 4294967296.0;
      mant_long = ((unsigned long) mant) & 0xffffffffL;
      mant -= mant_long;

      /* If the integer bit is implicit, then we need to discard it.
         If we are discarding a zero, we should be (but are not) creating
         a denormalized number which means adjusting the exponent
         (I think).  */
      if (mant_bits_left == fmt->man_len
	  && fmt->intbit == floatformat_intbit_no)
	{
	  mant_long <<= 1;
	  mant_long &= 0xffffffffL;
	  mant_bits -= 1;
	}

      if (mant_bits < 32)
	{
	  /* The bits we want are in the most significant MANT_BITS bits of
	     mant_long.  Move them to the least significant.  */
	  mant_long >>= 32 - mant_bits;
	}

      put_field (uto, fmt->byteorder, fmt->totalsize,
		 mant_off, mant_bits, mant_long);
      mant_off += mant_bits;
      mant_bits_left -= mant_bits;
    }
  if (fmt->byteorder == floatformat_littlebyte_bigword)
    {
      int count;
      unsigned char *swaplow = uto;
      unsigned char *swaphigh = uto + 4;
      unsigned char tmp;

      for (count = 0; count < 4; count++)
	{
	  tmp = *swaplow;
	  *swaplow++ = *swaphigh;
	  *swaphigh++ = tmp;
	}
    }
}

/* Check if VAL (which is assumed to be a floating point number whose
   format is described by FMT) is negative.  */

int
floatformat_is_negative (const struct floatformat *fmt, char *val)
{
  unsigned char *uval = (unsigned char *) val;

  return get_field (uval, fmt->byteorder, fmt->totalsize, fmt->sign_start, 1);
}

/* Check if VAL is "not a number" (NaN) for FMT.  */

int
floatformat_is_nan (const struct floatformat *fmt, char *val)
{
  unsigned char *uval = (unsigned char *) val;
  long exponent;
  unsigned long mant;
  unsigned int mant_bits, mant_off;
  int mant_bits_left;

  if (! fmt->exp_nan)
    return 0;

  exponent = get_field (uval, fmt->byteorder, fmt->totalsize,
			fmt->exp_start, fmt->exp_len);

  if (exponent != fmt->exp_nan)
    return 0;

  mant_bits_left = fmt->man_len;
  mant_off = fmt->man_start;

  while (mant_bits_left > 0)
    {
      mant_bits = min (mant_bits_left, 32);

      mant = get_field (uval, fmt->byteorder, fmt->totalsize,
			mant_off, mant_bits);

      /* If there is an explicit integer bit, mask it off.  */
      if (mant_off == fmt->man_start
	  && fmt->intbit == floatformat_intbit_yes)
	mant &= ~(1 << (mant_bits - 1));

      if (mant)
	return 1;

      mant_off += mant_bits;
      mant_bits_left -= mant_bits;
    }

  return 0;
}

/* Convert the mantissa of VAL (which is assumed to be a floating
   point number whose format is described by FMT) into a hexadecimal
   and store it in a static string.  Return a pointer to that string.  */

char *
floatformat_mantissa (const struct floatformat *fmt, char *val)
{
  unsigned char *uval = (unsigned char *) val;
  unsigned long mant;
  unsigned int mant_bits, mant_off;
  int mant_bits_left;
  static char res[50];
  char buf[9];

  /* Make sure we have enough room to store the mantissa.  */
  gdb_assert (sizeof res > ((fmt->man_len + 7) / 8) * 2);

  mant_off = fmt->man_start;
  mant_bits_left = fmt->man_len;
  mant_bits = (mant_bits_left % 32) > 0 ? mant_bits_left % 32 : 32;

  mant = get_field (uval, fmt->byteorder, fmt->totalsize,
		    mant_off, mant_bits);

  sprintf (res, "%lx", mant);

  mant_off += mant_bits;
  mant_bits_left -= mant_bits;
  
  while (mant_bits_left > 0)
    {
      mant = get_field (uval, fmt->byteorder, fmt->totalsize,
			mant_off, 32);

      sprintf (buf, "%08lx", mant);
      strcat (res, buf);

      mant_off += 32;
      mant_bits_left -= 32;
    }

  return res;
}



/* Extract a floating-point number from a target-order byte-stream at ADDR.
   Returns the value as type DOUBLEST.

   If the host and target formats agree, we just copy the raw data into the
   appropriate type of variable and return, letting the host increase precision
   as necessary.  Otherwise, we call the conversion routine and let it do the
   dirty work.  */

DOUBLEST
extract_floating (const void *addr, int len)
{
  DOUBLEST dretval;

  if (len * TARGET_CHAR_BIT == TARGET_FLOAT_BIT)
    {
      if (HOST_FLOAT_FORMAT == TARGET_FLOAT_FORMAT)
	{
	  float retval;

	  memcpy (&retval, addr, sizeof (retval));
	  return retval;
	}
      else
	floatformat_to_doublest (TARGET_FLOAT_FORMAT, addr, &dretval);
    }
  else if (len * TARGET_CHAR_BIT == TARGET_DOUBLE_BIT)
    {
      if (HOST_DOUBLE_FORMAT == TARGET_DOUBLE_FORMAT)
	{
	  double retval;

	  memcpy (&retval, addr, sizeof (retval));
	  return retval;
	}
      else
	floatformat_to_doublest (TARGET_DOUBLE_FORMAT, addr, &dretval);
    }
  else if (len * TARGET_CHAR_BIT == TARGET_LONG_DOUBLE_BIT)
    {
      if (HOST_LONG_DOUBLE_FORMAT == TARGET_LONG_DOUBLE_FORMAT)
	{
	  DOUBLEST retval;

	  memcpy (&retval, addr, sizeof (retval));
	  return retval;
	}
      else
	floatformat_to_doublest (TARGET_LONG_DOUBLE_FORMAT, addr, &dretval);
    }
  else
    {
      error ("Can't deal with a floating point number of %d bytes.", len);
    }

  return dretval;
}

void
store_floating (void *addr, int len, DOUBLEST val)
{
  if (len * TARGET_CHAR_BIT == TARGET_FLOAT_BIT)
    {
      if (HOST_FLOAT_FORMAT == TARGET_FLOAT_FORMAT)
	{
	  float floatval = val;

	  memcpy (addr, &floatval, sizeof (floatval));
	}
      else
	floatformat_from_doublest (TARGET_FLOAT_FORMAT, &val, addr);
    }
  else if (len * TARGET_CHAR_BIT == TARGET_DOUBLE_BIT)
    {
      if (HOST_DOUBLE_FORMAT == TARGET_DOUBLE_FORMAT)
	{
	  double doubleval = val;

	  memcpy (addr, &doubleval, sizeof (doubleval));
	}
      else
	floatformat_from_doublest (TARGET_DOUBLE_FORMAT, &val, addr);
    }
  else if (len * TARGET_CHAR_BIT == TARGET_LONG_DOUBLE_BIT)
    {
      if (HOST_LONG_DOUBLE_FORMAT == TARGET_LONG_DOUBLE_FORMAT)
	memcpy (addr, &val, sizeof (val));
      else
	floatformat_from_doublest (TARGET_LONG_DOUBLE_FORMAT, &val, addr);
    }
  else
    {
      error ("Can't deal with a floating point number of %d bytes.", len);
    }
}