/* 32-bit ELF for the MCS-51 target
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



#define ELF_ARCH		bfd_arch_mcs51
#define ELF_TARGET_ID		MCS51_ELF_DATA
#define ELF_MACHINE_CODE	EM_MCS51
#define ELF_MACHINE_ALT1	EM_MCS51_OLD
#define ELF_MAXPAGESIZE		1

#define TARGET_LITTLE_SYM	mcs51_elf32_vec
#define TARGET_LITTLE_NAME	"elf32-mcs51"

#define bfd_elf32_bfd_link_hash_table_create elf32_mcs51_link_hash_table_create

#define elf_info_to_howto		     mcs51_info_to_howto_rela
#define elf_info_to_howto_rel		     NULL
#define elf_backend_relocate_section	     elf32_mcs51_relocate_section
#define elf_backend_can_gc_sections	     1
#define elf_backend_rela_normal		     1
#define elf_backend_final_write_processing \
					bfd_elf_mcs51_final_write_processing
#define elf_backend_object_p		elf32_mcs51_object_p

#define bfd_elf32_bfd_relax_section elf32_mcs51_relax_section
#define bfd_elf32_bfd_get_relocated_section_contents \
					elf32_mcs51_get_relocated_section_contents
#define bfd_elf32_new_section_hook	elf_mcs51_new_section_hook
#define elf_backend_special_sections	elf_mcs51_special_sections

#include "elf32-target.h"