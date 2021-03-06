/* This file is tc-h8300.h
   Copyright 1987, 1988, 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996,
   1997, 1998, 2000, 2002
   Free Software Foundation, Inc.

   This file is part of GAS, the GNU Assembler.

   GAS is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   GAS is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GAS; see the file COPYING.  If not, write to the Free
   Software Foundation, 59 Temple Place - Suite 330, Boston, MA
   02111-1307, USA.  */

#define TC_H8300

#define TARGET_BYTES_BIG_ENDIAN 1

#define TARGET_ARCH bfd_arch_h8300

#ifdef BFD_ASSEMBLER
/* Fixup debug sections since we will never relax them.  */
#define TC_LINKRELAX_FIXUP(seg) (seg->flags & SEC_ALLOC)
#endif
#ifdef OBJ_ELF
#define TARGET_FORMAT "elf32-h8300"
#endif

#if ANSI_PROTOTYPES
struct fix;
struct internal_reloc;
#endif

#define WORKING_DOT_WORD

/* This macro translates between an internal fix and an coff reloc type */
#define TC_COFF_FIX2RTYPE(fixP) abort ();

#define BFD_ARCH bfd_arch_h8300
#define COFF_MAGIC ( Smode ? 0x8302 : Hmode ? 0x8301 : 0x8300)
#define TC_COUNT_RELOC(x) (1)
#define IGNORE_NONSTANDARD_ESCAPES

#define tc_coff_symbol_emit_hook(a) ; /* not used */
#define TC_RELOC_MANGLE(s,a,b,c) tc_reloc_mangle(a,b,c)
extern void tc_reloc_mangle
  PARAMS ((struct fix *, struct internal_reloc *, bfd_vma));

/* No shared lib support, so we don't need to ensure externally
   visible symbols can be overridden.  */
#define EXTERN_FORCE_RELOC 0

#ifdef OBJ_ELF
/* Provide mappings from the original H8 COFF relocation names to
   their corresponding BFD relocation names.  This allows us to use
   most of tc-h8300.c without modifications for both ELF and COFF
   ports.  */
#define R_MOV24B1 BFD_RELOC_H8_DIR24A8
#define R_MOVL1 BFD_RELOC_H8_DIR32A16
#define R_MOV24B1 BFD_RELOC_H8_DIR24A8
#define R_MOVL1 BFD_RELOC_H8_DIR32A16
#define R_RELLONG BFD_RELOC_32
#define R_MOV16B1 BFD_RELOC_H8_DIR16A8
#define R_RELWORD BFD_RELOC_16
#define R_RELBYTE BFD_RELOC_8
#define R_PCRWORD BFD_RELOC_16_PCREL
#define R_PCRBYTE BFD_RELOC_8_PCREL
#define R_JMPL1 BFD_RELOC_H8_DIR24R8
#define R_MEM_INDIRECT BFD_RELOC_8

/* We do not want to adjust any relocations to make implementation of
   linker relaxations easier.  */
#define tc_fix_adjustable(FIX) 0
#endif

#define TC_CONS_RELOC          (Hmode ? R_RELLONG: R_RELWORD)

#define DO_NOT_STRIP 0
#define LISTING_HEADER "Hitachi H8/300 GAS "
#define NEED_FX_R_TYPE 1
#ifndef OBJ_ELF
#define RELOC_32 1234
#endif

extern int Hmode;
extern int Smode;

#define md_operand(x)
