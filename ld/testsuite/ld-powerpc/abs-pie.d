#source: abs-reloc.s
#as: -a64
#ld: -melf64ppc -pie --hash-style=sysv --defsym a=1 --defsym 'HIDDEN(b=2)' --defsym c=0x123456789abcdef0
#objdump: -sdr

#...
Contents of section \.got:
.* (00000000 00018400|00840100 00000000) (00000000 00000001|01000000 00000000) .*
.* (00000000 00000002|02000000 00000000) (12345678 9abcdef0|f0debc9a 78563412) .*
.* (00000000 00000002|02000000 00000000) (12345678 9abcdef0|f0debc9a 78563412) .*
.* (00000000 00000001|01000000 00000000) .*
Contents of section \.data:
.* (00000000 00010438|38040100 00000000) (00000000 00000001|01000000 00000000) .*
.* (00000000 00000002|02000000 00000000) (12345678 9abcdef0|f0debc9a 78563412) .*
#...
.* <_start>:
.*:	(3c 4c 00 02|02 00 4c 3c) 	addis   r2,r12,2
.*:	(38 42 82 10|10 82 42 38) 	addi    r2,r2,-32240
.*:	(60 00 00 00|00 00 00 60) 	nop
.*:	(38 62 80 38|38 80 62 38) 	addi    r3,r2,-32712
.*:	(60 00 00 00|00 00 00 60) 	nop
.*:	(e8 82 80 08|08 80 82 e8) 	ld      r4,-32760\(r2\)
.*:	(60 00 00 00|00 00 00 60) 	nop
.*:	(e8 a2 80 10|10 80 a2 e8) 	ld      r5,-32752\(r2\)
.*:	(60 00 00 00|00 00 00 60) 	nop
.*:	(e8 c2 80 18|18 80 c2 e8) 	ld      r6,-32744\(r2\)
.*:	(60 00 00 00|00 00 00 60) 	nop
.*:	(38 e2 80 38|38 80 e2 38) 	addi    r7,r2,-32712
.*:	(3d 02 00 00|00 00 02 3d) 	addis   r8,r2,0
.*:	(e9 08 80 30|30 80 08 e9) 	ld      r8,-32720\(r8\)
.*:	(3d 22 00 00|00 00 22 3d) 	addis   r9,r2,0
.*:	(e9 29 80 20|20 80 29 e9) 	ld      r9,-32736\(r9\)
.*:	(3d 42 00 00|00 00 42 3d) 	addis   r10,r2,0
.*:	(e9 4a 80 28|28 80 4a e9) 	ld      r10,-32728\(r10\)
