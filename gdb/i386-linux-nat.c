/* Native-dependent code for GNU/Linux x86.

   Copyright 1999, 2000, 2001, 2002 Free Software Foundation, Inc.

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

#include "defs.h"
#include "inferior.h"
#include "gdbcore.h"
#include "regcache.h"

#include "gdb_assert.h"
#include "gdb_string.h"
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/procfs.h>

#ifdef HAVE_SYS_REG_H
#include <sys/reg.h>
#endif

#ifndef ORIG_EAX
#define ORIG_EAX -1
#endif

#ifdef HAVE_SYS_DEBUGREG_H
#include <sys/debugreg.h>
#endif

#ifndef DR_FIRSTADDR
#define DR_FIRSTADDR 0
#endif

#ifndef DR_LASTADDR
#define DR_LASTADDR 3
#endif

#ifndef DR_STATUS
#define DR_STATUS 6
#endif

#ifndef DR_CONTROL
#define DR_CONTROL 7
#endif

/* Prototypes for supply_gregset etc.  */
#include "gregset.h"

/* Prototypes for i387_supply_fsave etc.  */
#include "i387-tdep.h"

/* Defines for XMM0_REGNUM etc. */
#include "i386-tdep.h"

/* Defines I386_LINUX_ORIG_EAX_REGNUM.  */
#include "i386-linux-tdep.h"

/* Prototypes for local functions.  */
static void dummy_sse_values (void);



/* The register sets used in GNU/Linux ELF core-dumps are identical to
   the register sets in `struct user' that is used for a.out
   core-dumps, and is also used by `ptrace'.  The corresponding types
   are `elf_gregset_t' for the general-purpose registers (with
   `elf_greg_t' the type of a single GP register) and `elf_fpregset_t'
   for the floating-point registers.

   Those types used to be available under the names `gregset_t' and
   `fpregset_t' too, and this file used those names in the past.  But
   those names are now used for the register sets used in the
   `mcontext_t' type, and have a different size and layout.  */

/* Mapping between the general-purpose registers in `struct user'
   format and GDB's register array layout.  */
static int regmap[] = 
{
  EAX, ECX, EDX, EBX,
  UESP, EBP, ESI, EDI,
  EIP, EFL, CS, SS,
  DS, ES, FS, GS,
  -1, -1, -1, -1,		/* st0, st1, st2, st3 */
  -1, -1, -1, -1,		/* st4, st5, st6, st7 */
  -1, -1, -1, -1,		/* fctrl, fstat, ftag, fiseg */
  -1, -1, -1, -1,		/* fioff, foseg, fooff, fop */
  -1, -1, -1, -1,		/* xmm0, xmm1, xmm2, xmm3 */
  -1, -1, -1, -1,		/* xmm4, xmm5, xmm6, xmm6 */
  -1,				/* mxcsr */
  ORIG_EAX
};

/* Which ptrace request retrieves which registers?
   These apply to the corresponding SET requests as well.  */
#define GETREGS_SUPPLIES(regno) \
  ((0 <= (regno) && (regno) <= 15) || (regno) == I386_LINUX_ORIG_EAX_REGNUM)
#define GETFPREGS_SUPPLIES(regno) \
  (FP0_REGNUM <= (regno) && (regno) <= LAST_FPU_CTRL_REGNUM)
#define GETFPXREGS_SUPPLIES(regno) \
  (FP0_REGNUM <= (regno) && (regno) <= MXCSR_REGNUM)

/* Does the current host support the GETREGS request?  */
int have_ptrace_getregs =
#ifdef HAVE_PTRACE_GETREGS
  1
#else
  0
#endif
;

/* Does the current host support the GETFPXREGS request?  The header
   file may or may not define it, and even if it is defined, the
   kernel will return EIO if it's running on a pre-SSE processor.

   My instinct is to attach this to some architecture- or
   target-specific data structure, but really, a particular GDB
   process can only run on top of one kernel at a time.  So it's okay
   for this to be a simple variable.  */
int have_ptrace_getfpxregs =
#ifdef HAVE_PTRACE_GETFPXREGS
  1
#else
  0
#endif
;


/* Support for the user struct.  */

/* Return the address of register REGNUM.  BLOCKEND is the value of
   u.u_ar0, which should point to the registers.  */

CORE_ADDR
register_u_addr (CORE_ADDR blockend, int regnum)
{
  return (blockend + 4 * regmap[regnum]);
}

/* Return the size of the user struct.  */

int
kernel_u_size (void)
{
  return (sizeof (struct user));
}


/* Accessing registers through the U area, one at a time.  */

/* Fetch one register.  */

static void
fetch_register (int regno)
{
  int tid;
  int val;

  gdb_assert (!have_ptrace_getregs);
  if (cannot_fetch_register (regno))
    {
      supply_register (regno, NULL);
      return;
    }

  /* GNU/Linux LWP ID's are process ID's.  */
  if ((tid = TIDGET (inferior_ptid)) == 0)
    tid = PIDGET (inferior_ptid);	/* Not a threaded program.  */

  errno = 0;
  val = ptrace (PTRACE_PEEKUSER, tid, register_addr (regno, 0), 0);
  if (errno != 0)
    error ("Couldn't read register %s (#%d): %s.", REGISTER_NAME (regno),
	   regno, safe_strerror (errno));

  supply_register (regno, &val);
}

/* Store one register. */

static void
store_register (int regno)
{
  int tid;
  int val;

  gdb_assert (!have_ptrace_getregs);
  if (cannot_store_register (regno))
    return;

  /* GNU/Linux LWP ID's are process ID's.  */
  if ((tid = TIDGET (inferior_ptid)) == 0)
    tid = PIDGET (inferior_ptid);	/* Not a threaded program.  */

  errno = 0;
  regcache_collect (regno, &val);
  ptrace (PTRACE_POKEUSER, tid, register_addr (regno, 0), val);
  if (errno != 0)
    error ("Couldn't read register %s (#%d): %s.", REGISTER_NAME (regno),
	   regno, safe_strerror (errno));
}


/* Transfering the general-purpose registers between GDB, inferiors
   and core files.  */

/* Fill GDB's register array with the general-purpose register values
   in *GREGSETP.  */

void
supply_gregset (elf_gregset_t *gregsetp)
{
  elf_greg_t *regp = (elf_greg_t *) gregsetp;
  int i;

  for (i = 0; i < I386_NUM_GREGS; i++)
    supply_register (i, (char *) (regp + regmap[i]));

  if (I386_LINUX_ORIG_EAX_REGNUM < NUM_REGS)
    supply_register (I386_LINUX_ORIG_EAX_REGNUM, (char *) (regp + ORIG_EAX));
}

/* Fill register REGNO (if it is a general-purpose register) in
   *GREGSETPS with the value in GDB's register array.  If REGNO is -1,
   do this for all registers.  */

void
fill_gregset (elf_gregset_t *gregsetp, int regno)
{
  elf_greg_t *regp = (elf_greg_t *) gregsetp;
  int i;

  for (i = 0; i < I386_NUM_GREGS; i++)
    if (regno == -1 || regno == i)
      regcache_collect (i, regp + regmap[i]);

  if ((regno == -1 || regno == I386_LINUX_ORIG_EAX_REGNUM)
      && I386_LINUX_ORIG_EAX_REGNUM < NUM_REGS)
    regcache_collect (I386_LINUX_ORIG_EAX_REGNUM, regp + ORIG_EAX);
}

#ifdef HAVE_PTRACE_GETREGS

/* Fetch all general-purpose registers from process/thread TID and
   store their values in GDB's register array.  */

static void
fetch_regs (int tid)
{
  elf_gregset_t regs;

  if (ptrace (PTRACE_GETREGS, tid, 0, (int) &regs) < 0)
    {
      if (errno == EIO)
	{
	  /* The kernel we're running on doesn't support the GETREGS
             request.  Reset `have_ptrace_getregs'.  */
	  have_ptrace_getregs = 0;
	  return;
	}

      perror_with_name ("Couldn't get registers");
    }

  supply_gregset (&regs);
}

/* Store all valid general-purpose registers in GDB's register array
   into the process/thread specified by TID.  */

static void
store_regs (int tid, int regno)
{
  elf_gregset_t regs;

  if (ptrace (PTRACE_GETREGS, tid, 0, (int) &regs) < 0)
    perror_with_name ("Couldn't get registers");

  fill_gregset (&regs, regno);
  
  if (ptrace (PTRACE_SETREGS, tid, 0, (int) &regs) < 0)
    perror_with_name ("Couldn't write registers");
}

#else

static void fetch_regs (int tid) {}
static void store_regs (int tid, int regno) {}

#endif


/* Transfering floating-point registers between GDB, inferiors and cores.  */

/* Fill GDB's register array with the floating-point register values in
   *FPREGSETP.  */

void 
supply_fpregset (elf_fpregset_t *fpregsetp)
{
  i387_supply_fsave ((char *) fpregsetp);
  dummy_sse_values ();
}

/* Fill register REGNO (if it is a floating-point register) in
   *FPREGSETP with the value in GDB's register array.  If REGNO is -1,
   do this for all registers.  */

void
fill_fpregset (elf_fpregset_t *fpregsetp, int regno)
{
  i387_fill_fsave ((char *) fpregsetp, regno);
}

#ifdef HAVE_PTRACE_GETREGS

/* Fetch all floating-point registers from process/thread TID and store
   thier values in GDB's register array.  */

static void
fetch_fpregs (int tid)
{
  elf_fpregset_t fpregs;

  if (ptrace (PTRACE_GETFPREGS, tid, 0, (int) &fpregs) < 0)
    perror_with_name ("Couldn't get floating point status");

  supply_fpregset (&fpregs);
}

/* Store all valid floating-point registers in GDB's register array
   into the process/thread specified by TID.  */

static void
store_fpregs (int tid, int regno)
{
  elf_fpregset_t fpregs;

  if (ptrace (PTRACE_GETFPREGS, tid, 0, (int) &fpregs) < 0)
    perror_with_name ("Couldn't get floating point status");

  fill_fpregset (&fpregs, regno);

  if (ptrace (PTRACE_SETFPREGS, tid, 0, (int) &fpregs) < 0)
    perror_with_name ("Couldn't write floating point status");
}

#else

static void fetch_fpregs (int tid) {}
static void store_fpregs (int tid, int regno) {}

#endif


/* Transfering floating-point and SSE registers to and from GDB.  */

#ifdef HAVE_PTRACE_GETFPXREGS

/* Fill GDB's register array with the floating-point and SSE register
   values in *FPXREGSETP.  */

void
supply_fpxregset (elf_fpxregset_t *fpxregsetp)
{
  i387_supply_fxsave ((char *) fpxregsetp);
}

/* Fill register REGNO (if it is a floating-point or SSE register) in
   *FPXREGSETP with the value in GDB's register array.  If REGNO is
   -1, do this for all registers.  */

void
fill_fpxregset (elf_fpxregset_t *fpxregsetp, int regno)
{
  i387_fill_fxsave ((char *) fpxregsetp, regno);
}

/* Fetch all registers covered by the PTRACE_GETFPXREGS request from
   process/thread TID and store their values in GDB's register array.
   Return non-zero if successful, zero otherwise.  */

static int
fetch_fpxregs (int tid)
{
  elf_fpxregset_t fpxregs;

  if (! have_ptrace_getfpxregs)
    return 0;

  if (ptrace (PTRACE_GETFPXREGS, tid, 0, (int) &fpxregs) < 0)
    {
      if (errno == EIO)
	{
	  have_ptrace_getfpxregs = 0;
	  return 0;
	}

      perror_with_name ("Couldn't read floating-point and SSE registers");
    }

  supply_fpxregset (&fpxregs);
  return 1;
}

/* Store all valid registers in GDB's register array covered by the
   PTRACE_SETFPXREGS request into the process/thread specified by TID.
   Return non-zero if successful, zero otherwise.  */

static int
store_fpxregs (int tid, int regno)
{
  elf_fpxregset_t fpxregs;

  if (! have_ptrace_getfpxregs)
    return 0;
  
  if (ptrace (PTRACE_GETFPXREGS, tid, 0, &fpxregs) == -1)
    {
      if (errno == EIO)
	{
	  have_ptrace_getfpxregs = 0;
	  return 0;
	}

      perror_with_name ("Couldn't read floating-point and SSE registers");
    }

  fill_fpxregset (&fpxregs, regno);

  if (ptrace (PTRACE_SETFPXREGS, tid, 0, &fpxregs) == -1)
    perror_with_name ("Couldn't write floating-point and SSE registers");

  return 1;
}

/* Fill the XMM registers in the register array with dummy values.  For
   cases where we don't have access to the XMM registers.  I think
   this is cleaner than printing a warning.  For a cleaner solution,
   we should gdbarchify the i386 family.  */

static void
dummy_sse_values (void)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);
  /* C doesn't have a syntax for NaN's, so write it out as an array of
     longs.  */
  static long dummy[4] = { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff };
  static long mxcsr = 0x1f80;
  int reg;

  for (reg = 0; reg < tdep->num_xmm_regs; reg++)
    supply_register (XMM0_REGNUM + reg, (char *) dummy);
  if (tdep->num_xmm_regs > 0)
    supply_register (MXCSR_REGNUM, (char *) &mxcsr);
}

#else

static int fetch_fpxregs (int tid) { return 0; }
static int store_fpxregs (int tid, int regno) { return 0; }
static void dummy_sse_values (void) {}

#endif /* HAVE_PTRACE_GETFPXREGS */


/* Transferring arbitrary registers between GDB and inferior.  */

/* Check if register REGNO in the child process is accessible.
   If we are accessing registers directly via the U area, only the
   general-purpose registers are available.
   All registers should be accessible if we have GETREGS support.  */
   
int
cannot_fetch_register (int regno)
{
  gdb_assert (regno >= 0 && regno < NUM_REGS);
  return (!have_ptrace_getregs && regmap[regno] == -1);
}

int
cannot_store_register (int regno)
{
  gdb_assert (regno >= 0 && regno < NUM_REGS);
  return (!have_ptrace_getregs && regmap[regno] == -1);
}

/* Fetch register REGNO from the child process.  If REGNO is -1, do
   this for all registers (including the floating point and SSE
   registers).  */

void
fetch_inferior_registers (int regno)
{
  int tid;

  /* Use the old method of peeking around in `struct user' if the
     GETREGS request isn't available.  */
  if (!have_ptrace_getregs)
    {
      int i;

      for (i = 0; i < NUM_REGS; i++)
	if (regno == -1 || regno == i)
	  fetch_register (i);

      return;
    }

  /* GNU/Linux LWP ID's are process ID's.  */
  if ((tid = TIDGET (inferior_ptid)) == 0)
    tid = PIDGET (inferior_ptid);		/* Not a threaded program.  */

  /* Use the PTRACE_GETFPXREGS request whenever possible, since it
     transfers more registers in one system call, and we'll cache the
     results.  But remember that fetch_fpxregs can fail, and return
     zero.  */
  if (regno == -1)
    {
      fetch_regs (tid);

      /* The call above might reset `have_ptrace_getregs'.  */
      if (!have_ptrace_getregs)
	{
	  fetch_inferior_registers (regno);
	  return;
	}

      if (fetch_fpxregs (tid))
	return;
      fetch_fpregs (tid);
      return;
    }

  if (GETREGS_SUPPLIES (regno))
    {
      fetch_regs (tid);
      return;
    }

  if (GETFPXREGS_SUPPLIES (regno))
    {
      if (fetch_fpxregs (tid))
	return;

      /* Either our processor or our kernel doesn't support the SSE
	 registers, so read the FP registers in the traditional way,
	 and fill the SSE registers with dummy values.  It would be
	 more graceful to handle differences in the register set using
	 gdbarch.  Until then, this will at least make things work
	 plausibly.  */
      fetch_fpregs (tid);
      return;
    }

  internal_error (__FILE__, __LINE__,
		  "Got request for bad register number %d.", regno);
}

/* Store register REGNO back into the child process.  If REGNO is -1,
   do this for all registers (including the floating point and SSE
   registers).  */
void
store_inferior_registers (int regno)
{
  int tid;

  /* Use the old method of poking around in `struct user' if the
     SETREGS request isn't available.  */
  if (!have_ptrace_getregs)
    {
      int i;

      for (i = 0; i < NUM_REGS; i++)
	if (regno == -1 || regno == i)
	  store_register (i);

      return;
    }

  /* GNU/Linux LWP ID's are process ID's.  */
  if ((tid = TIDGET (inferior_ptid)) == 0)
    tid = PIDGET (inferior_ptid);	/* Not a threaded program.  */

  /* Use the PTRACE_SETFPXREGS requests whenever possible, since it
     transfers more registers in one system call.  But remember that
     store_fpxregs can fail, and return zero.  */
  if (regno == -1)
    {
      store_regs (tid, regno);
      if (store_fpxregs (tid, regno))
	return;
      store_fpregs (tid, regno);
      return;
    }

  if (GETREGS_SUPPLIES (regno))
    {
      store_regs (tid, regno);
      return;
    }

  if (GETFPXREGS_SUPPLIES (regno))
    {
      if (store_fpxregs (tid, regno))
	return;

      /* Either our processor or our kernel doesn't support the SSE
	 registers, so just write the FP registers in the traditional
	 way.  */
      store_fpregs (tid, regno);
      return;
    }

  internal_error (__FILE__, __LINE__,
		  "Got request to store bad register number %d.", regno);
}


static unsigned long
i386_linux_dr_get (int regnum)
{
  int tid;
  unsigned long value;

  /* FIXME: kettenis/2001-01-29: It's not clear what we should do with
     multi-threaded processes here.  For now, pretend there is just
     one thread.  */
  tid = PIDGET (inferior_ptid);

  /* FIXME: kettenis/2001-03-27: Calling perror_with_name if the
     ptrace call fails breaks debugging remote targets.  The correct
     way to fix this is to add the hardware breakpoint and watchpoint
     stuff to the target vectore.  For now, just return zero if the
     ptrace call fails.  */
  errno = 0;
  value = ptrace (PTRACE_PEEKUSER, tid,
		  offsetof (struct user, u_debugreg[regnum]), 0);
  if (errno != 0)
#if 0
    perror_with_name ("Couldn't read debug register");
#else
    return 0;
#endif

  return value;
}

static void
i386_linux_dr_set (int regnum, unsigned long value)
{
  int tid;

  /* FIXME: kettenis/2001-01-29: It's not clear what we should do with
     multi-threaded processes here.  For now, pretend there is just
     one thread.  */
  tid = PIDGET (inferior_ptid);

  errno = 0;
  ptrace (PTRACE_POKEUSER, tid,
	  offsetof (struct user, u_debugreg[regnum]), value);
  if (errno != 0)
    perror_with_name ("Couldn't write debug register");
}

void
i386_linux_dr_set_control (unsigned long control)
{
  i386_linux_dr_set (DR_CONTROL, control);
}

void
i386_linux_dr_set_addr (int regnum, CORE_ADDR addr)
{
  gdb_assert (regnum >= 0 && regnum <= DR_LASTADDR - DR_FIRSTADDR);

  i386_linux_dr_set (DR_FIRSTADDR + regnum, addr);
}

void
i386_linux_dr_reset_addr (int regnum)
{
  gdb_assert (regnum >= 0 && regnum <= DR_LASTADDR - DR_FIRSTADDR);

  i386_linux_dr_set (DR_FIRSTADDR + regnum, 0L);
}

unsigned long
i386_linux_dr_get_status (void)
{
  return i386_linux_dr_get (DR_STATUS);
}


/* Interpreting register set info found in core files.  */

/* Provide registers to GDB from a core file.

   (We can't use the generic version of this function in
   core-regset.c, because GNU/Linux has *three* different kinds of
   register set notes.  core-regset.c would have to call
   supply_fpxregset, which most platforms don't have.)

   CORE_REG_SECT points to an array of bytes, which are the contents
   of a `note' from a core file which BFD thinks might contain
   register contents.  CORE_REG_SIZE is its size.

   WHICH says which register set corelow suspects this is:
     0 --- the general-purpose register set, in elf_gregset_t format
     2 --- the floating-point register set, in elf_fpregset_t format
     3 --- the extended floating-point register set, in elf_fpxregset_t format

   REG_ADDR isn't used on GNU/Linux.  */

static void
fetch_core_registers (char *core_reg_sect, unsigned core_reg_size,
		      int which, CORE_ADDR reg_addr)
{
  elf_gregset_t gregset;
  elf_fpregset_t fpregset;

  switch (which)
    {
    case 0:
      if (core_reg_size != sizeof (gregset))
	warning ("Wrong size gregset in core file.");
      else
	{
	  memcpy (&gregset, core_reg_sect, sizeof (gregset));
	  supply_gregset (&gregset);
	}
      break;

    case 2:
      if (core_reg_size != sizeof (fpregset))
	warning ("Wrong size fpregset in core file.");
      else
	{
	  memcpy (&fpregset, core_reg_sect, sizeof (fpregset));
	  supply_fpregset (&fpregset);
	}
      break;

#ifdef HAVE_PTRACE_GETFPXREGS
      {
	elf_fpxregset_t fpxregset;

      case 3:
	if (core_reg_size != sizeof (fpxregset))
	  warning ("Wrong size fpxregset in core file.");
	else
	  {
	    memcpy (&fpxregset, core_reg_sect, sizeof (fpxregset));
	    supply_fpxregset (&fpxregset);
	  }
	break;
      }
#endif

    default:
      /* We've covered all the kinds of registers we know about here,
         so this must be something we wouldn't know what to do with
         anyway.  Just ignore it.  */
      break;
    }
}


/* The instruction for a GNU/Linux system call is:
       int $0x80
   or 0xcd 0x80.  */

static const unsigned char linux_syscall[] = { 0xcd, 0x80 };

#define LINUX_SYSCALL_LEN (sizeof linux_syscall)

/* The system call number is stored in the %eax register.  */
#define LINUX_SYSCALL_REGNUM 0	/* %eax */

/* We are specifically interested in the sigreturn and rt_sigreturn
   system calls.  */

#ifndef SYS_sigreturn
#define SYS_sigreturn		0x77
#endif
#ifndef SYS_rt_sigreturn
#define SYS_rt_sigreturn	0xad
#endif

/* Offset to saved processor flags, from <asm/sigcontext.h>.  */
#define LINUX_SIGCONTEXT_EFLAGS_OFFSET (64)

/* Resume execution of the inferior process.
   If STEP is nonzero, single-step it.
   If SIGNAL is nonzero, give it that signal.  */

void
child_resume (ptid_t ptid, int step, enum target_signal signal)
{
  int pid = PIDGET (ptid);

  int request = PTRACE_CONT;

  if (pid == -1)
    /* Resume all threads.  */
    /* I think this only gets used in the non-threaded case, where "resume
       all threads" and "resume inferior_ptid" are the same.  */
    pid = PIDGET (inferior_ptid);

  if (step)
    {
      CORE_ADDR pc = read_pc_pid (pid_to_ptid (pid));
      unsigned char buf[LINUX_SYSCALL_LEN];

      request = PTRACE_SINGLESTEP;

      /* Returning from a signal trampoline is done by calling a
         special system call (sigreturn or rt_sigreturn, see
         i386-linux-tdep.c for more information).  This system call
         restores the registers that were saved when the signal was
         raised, including %eflags.  That means that single-stepping
         won't work.  Instead, we'll have to modify the signal context
         that's about to be restored, and set the trace flag there.  */

      /* First check if PC is at a system call.  */
      if (read_memory_nobpt (pc, (char *) buf, LINUX_SYSCALL_LEN) == 0
	  && memcmp (buf, linux_syscall, LINUX_SYSCALL_LEN) == 0)
	{
	  int syscall = read_register_pid (LINUX_SYSCALL_REGNUM,
	                                   pid_to_ptid (pid));

	  /* Then check the system call number.  */
	  if (syscall == SYS_sigreturn || syscall == SYS_rt_sigreturn)
	    {
	      CORE_ADDR sp = read_register (SP_REGNUM);
	      CORE_ADDR addr = sp;
	      unsigned long int eflags;

	      if (syscall == SYS_rt_sigreturn)
		addr = read_memory_integer (sp + 8, 4) + 20;

	      /* Set the trace flag in the context that's about to be
                 restored.  */
	      addr += LINUX_SIGCONTEXT_EFLAGS_OFFSET;
	      read_memory (addr, (char *) &eflags, 4);
	      eflags |= 0x0100;
	      write_memory (addr, (char *) &eflags, 4);
	    }
	}
    }

  if (ptrace (request, pid, 0, target_signal_to_host (signal)) == -1)
    perror_with_name ("ptrace");
}


/* Register that we are able to handle GNU/Linux ELF core file
   formats.  */

static struct core_fns linux_elf_core_fns =
{
  bfd_target_elf_flavour,		/* core_flavour */
  default_check_format,			/* check_format */
  default_core_sniffer,			/* core_sniffer */
  fetch_core_registers,			/* core_read_registers */
  NULL					/* next */
};

void
_initialize_i386_linux_nat (void)
{
  add_core_fns (&linux_elf_core_fns);
}
