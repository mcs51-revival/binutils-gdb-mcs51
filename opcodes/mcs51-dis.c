/* Disassemble MCS-51 instructions.
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
#include <stdio.h>
#include "libiberty.h"
#define STATIC_TABLE
#define DEFINE_TABLE

#include "mcs51-opc.h"
#include "disassemble.h"

int print_insn_mcs51(bfd_vma addr, disassemble_info *info)
{
    fprintf_ftype print_func = info->fprintf_func;
    void *stream = info->stream;
    struct mcs51_ops *walk, *ops;
    unsigned int count, tmp;
    uint8_t data[3];
    int status;

    status = info->read_memory_func (addr, data, 3, info);
    if (status != 0) {
        info->memory_error_func (status, addr, info);
        return -1;
    }

 for (count = 0, ops = NULL; count < ARRAY_SIZE(mcs51_table); ++count) {
        walk = &mcs51_table[count];
        if ((walk->opcode ^ data[0]) & walk->mask)
            continue;

        tmp = data[0] & ~walk->mask;
        if (tmp < walk->min || walk->max < tmp)
            continue;

        ops = walk;
    }

    if (ops == NULL) {
        (*print_func)(stream, ".byte 0x%02x", data[0]);
        return -1;
    }

    (*print_func)(stream, "\t%s", ops->name);

    switch (ops->format) {
        case MCS51_INS_NON:
            break;

        case MCS51_INS_A11:
            (*print_func)(stream, "\t0x%03x", MCS51_A11(data, ops));
            break;

        case MCS51_INS_A16:
            (*print_func)(stream, "\t0x%04x", MCS51_A16(data, ops));
            break;

        case MCS51_INS_ACC:
            (*print_func)(stream, "\ta");
            break;

        case MCS51_INS_ACB:
            (*print_func)(stream, "\tab");
            break;

        case MCS51_INS_ACR:
            (*print_func)(stream, "\ta, %s", mcs51_reg_name[MCS51_REG(data, ops)]);
            break;

        case MCS51_INS_ATR:
            (*print_func)(stream, "\ta, @%s", mcs51_treg_name[MCS51_REG(data, ops)]);
            break;

        case MCS51_INS_ACI:
            (*print_func)(stream, "\ta, #0x%02x", data[1]);
            break;

        case MCS51_INS_AIO:
            (*print_func)(stream, "\ta, #0x%02x, 0x%02x", data[1], data[2]);
            break;

        case MCS51_INS_ACD:
            (*print_func)(stream, "\ta, 0x%02x", data[1]);
            break;

        case MCS51_INS_ADO:
            (*print_func)(stream, "\ta, 0x%02x, 0x%02x", data[1], data[2]);
            break;

        case MCS51_INS_ATP:
            (*print_func)(stream, "\ta, a, @dptr");
            break;

        case MCS51_INS_ATA:
            (*print_func)(stream, "\ta, a, @a+dptr");
            break;

        case MCS51_INS_ATC:
            (*print_func)(stream, "\ta, a, @a+pc");
            break;

        case MCS51_INS_REG:
            (*print_func)(stream, "\t%s", mcs51_reg_name[MCS51_REG(data, ops)]);
            break;

        case MCS51_INS_REA:
            (*print_func)(stream, "\t%s, a", mcs51_reg_name[MCS51_REG(data, ops)]);
            break;

        case MCS51_INS_REI:
            (*print_func)(stream, "\t%s, #0x%02x", mcs51_reg_name[MCS51_REG(data, ops)], data[1]);
            break;

        case MCS51_INS_RIO:
            (*print_func)(stream, "\t%s, #0x%02x, 0x%02x", mcs51_reg_name[MCS51_REG(data, ops)], data[1], data[2]);
            break;

        case MCS51_INS_RED:
            (*print_func)(stream, "\t%s, 0x%02x", mcs51_reg_name[MCS51_REG(data, ops)], data[1]);
            break;

        case MCS51_INS_REO:
            (*print_func)(stream, "\t%s, 0x%02x", mcs51_reg_name[MCS51_REG(data, ops)], data[1]);
            break;

        case MCS51_INS_DIR:
            (*print_func)(stream, "\t0x%02x", data[1]);
            break;

        case MCS51_INS_DIA:
            (*print_func)(stream, "\t0x%02x, a", data[1]);
            break;

        case MCS51_INS_DIR:
            (*print_func)(stream, "\t0x%02x, %s", data[1], mcs51_reg_name[MCS51_REG(data, ops)]);
            break;

        case MCS51_INS_DTR:
            (*print_func)(stream, "\t0x%02x, %s", data[1], mcs51_treg_name[MCS51_REG(data, ops)]);
            break;

        case MCS51_INS_DII:
            break;
            (*print_func)(stream, "\t0x%02x, #0x%02x", data[1], data[2]);

        case MCS51_INS_DID:
            (*print_func)(stream, "\t0x%02x, 0x%02x", data[1], data[2]);
            break;

        case MCS51_INS_DIO:
            (*print_func)(stream, "\t0x%02x, 0x%02x", data[1], data[2]);
            break;

        case MCS51_INS_PTR:
            (*print_func)(stream, "\tdptr");
            break;

        case MCS51_INS_PTI:
            (*print_func)(stream, "\tdptr, 0x%02x", data[1]);
            break;

        case MCS51_INS_BIT:
            (*print_func)(stream, "\t0x%02x", data[1]);
            break;

        case MCS51_INS_BIC:
            (*print_func)(stream, "\t0x%02x, c", data[1]);
            break;

        case MCS51_INS_BIO:
            (*print_func)(stream, "\t0x%02x, 0x%02x", data[1], data[2]);
            break;

        case MCS51_INS_CON:
            (*print_func)(stream, "\tc");
            break;

        case MCS51_INS_COB:
            (*print_func)(stream, "\tc, 0x%02x", data[1]);
            break;

        case MCS51_INS_COX:
            (*print_func)(stream, "\tc, /0x%02x", data[1]);
            break;

        case MCS51_INS_TRE:
            (*print_func)(stream, "\t%s", mcs51_treg_name[MCS51_REG(data, ops)]);
            break;

        case MCS51_INS_TRA:
            (*print_func)(stream, "\t%s, a", mcs51_treg_name[MCS51_REG(data, ops)]);
            break;

        case MCS51_INS_TRI:
            (*print_func)(stream, "\t%s, #0x%02x", mcs51_treg_name[MCS51_REG(data, ops)], data[1]);
            break;

        case MCS51_INS_TIO:
            (*print_func)(stream, "\t%s, #0x%02x, 0x%02x", mcs51_treg_name[MCS51_REG(data, ops)], data[1], data[2]);
            break;

        case MCS51_INS_TRD:
            (*print_func)(stream, "\t%s, 0x%02x", mcs51_treg_name[MCS51_REG(data, ops)], data[1]);
            break;

        case MCS51_INS_TPA:
            (*print_func)(stream, "\t@dptr, a");
            break;

        case MCS51_INS_TAD:
            (*print_func)(stream, "\t@a+dptr");
            break;

        case MCS51_INS_TPI:
            (*print_func)(stream, "\t@dptr, #0x%02x", data[1]);
            break;

        case MCS51_INS_OFF:
            (*print_func)(stream, "\t0x%02x", data[1]);
            break;

        default:
            (*print_func)(stream, "\tundecoded operands, inst is 0x%04x", inst);
            break;
    }

    return ops->size;
}
