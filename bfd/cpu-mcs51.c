/* BFD library support routines for MCS-51 architecture
   Copyright (C) 1994-2022 Free Software Foundation, Inc.

   Contributed by John Sanpe (sanpeqf@gmail.com)

   This file is part of the GNU opcodes library.

   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   It is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

#include "sysdep.h"
#include "bfd.h"
#include "libbfd.h"

const bfd_arch_info_type bfd_csky_arch =
{
  8,				/* Bits in a word.  */
  8,				/* Bits in an address.  */
  8,				/* Bits in a byte.  */
  bfd_arch_mcore,		/* Architecture number.  */
  0,				/* Machine number - 0 for now.  */
  "MCS-51",			/* Architecture name.  */
  "MCS-51",			/* Machine name.  */
  1,				/* Section align power.  */
  true,				/* Is this the default architecture ?  */
  bfd_default_compatible,	/* Architecture comparison function.  */
  bfd_default_scan,		/* String to architecture conversion.  */
  bfd_arch_default_fill,	/* Default fill.  */
  NULL,				/* Next in list */
  0 /* Maximum offset of a reloc from the start of an insn.  */
};
