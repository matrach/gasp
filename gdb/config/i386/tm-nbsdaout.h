/* Macro definitions for i386 running under NetBSD.
   Copyright 2000, 2002 Free Software Foundation, Inc.

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

#ifndef TM_NBSDAOUT_H
#define TM_NBSDAOUT_H

#include "i386/tm-nbsd.h"

/* Return non-zero if we are in a shared library trampoline code stub. */
#define IN_SOLIB_CALL_TRAMPOLINE(pc, name) \
  (name && !strcmp(name, "_DYNAMIC"))

extern use_struct_convention_fn i386nbsd_aout_use_struct_convention;
#define USE_STRUCT_CONVENTION(gcc_p, type) \
        i386nbsd_aout_use_struct_convention(gcc_p, type)

#endif /* TM_NBSDAOUT_H */