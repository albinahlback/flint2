dnl  AMD64 mpn_addmul_1 optimised for Intel Broadwell.

dnl  Copyright 2015, 2017 Free Software Foundation, Inc.

dnl  This file is part of the GNU MP Library.
dnl
dnl  The GNU MP Library is free software; you can redistribute it and/or modify
dnl  it under the terms of either:
dnl
dnl    * the GNU Lesser General Public License as published by the Free
dnl      Software Foundation; either version 3 of the License, or (at your
dnl      option) any later version.
dnl
dnl  or
dnl
dnl    * the GNU General Public License as published by the Free Software
dnl      Foundation; either version 2 of the License, or (at your option) any
dnl      later version.
dnl
dnl  or both in parallel, as here.
dnl
dnl  The GNU MP Library is distributed in the hope that it will be useful, but
dnl  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
dnl  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
dnl  for more details.
dnl
dnl  You should have received copies of the GNU General Public License and the
dnl  GNU Lesser General Public License along with the GNU MP Library.  If not,
dnl  see https://www.gnu.org/licenses/.
#
#   Copyright (C) 2024 Albin Ahlbäck
#
#   This file is part of FLINT.
#
#   FLINT is free software: you can redistribute it and/or modify it under
#   the terms of the GNU Lesser General Public License (LGPL) as published
#   by the Free Software Foundation; either version 3 of the License, or
#   (at your option) any later version.  See <https://www.gnu.org/licenses/>.
#

include(`config.m4')

define(`rp',	`%rdi')
define(`ap',	`%rsi')
define(`bp_old',`%rdx')
define(`n_old',	`%rcx')

define(`bp',	`%r8')
define(`rt',	`%rax')

define(`r0',	`%r11')
define(`r1',	`%rbx')
define(`r2',	`%rbp')
define(`r3',	`%r12')
define(`r4',	`%r13')

define(`sc',	`%r9')
define(`zr',	`%r10')

define(`n',	`%r9')
define(`m',	`%rcx')
define(`m_save',`%r10')

# We need
#
# rp, ap, bp, n
#
# k + 2 registers to hold k multiplications plus one carry
#
# 

.text

.global	FUNC(flint_mpn_mulhigh_n_basecase)
ALIGN(32)
TYPE(flint_mpn_mulhigh_n_basecase)

FUNC(flint_mpn_mulhigh_n_basecase):
	.cfi_startproc
	mov	bp_old, bp
	lea	-1*8(ap,n_old,8), ap	# ap += n - 1

	push	%rbx
	push	%rbp
	push	%r12
	push	%r13

	# Initial triangle
	xor	R32(zr), R32(zr)
	mov	0*8(bp), %rdx
	mulx	-1*8(ap), rt, rt
	mulx	0*8(ap), sc, r0
	add	sc, rt
	adc	zr, r0

	mov	1*8(bp), %rdx
	mulx	-2*8(ap), sc, sc
	mulx	-1*8(ap), r2, r3
	mulx	0*8(ap), %rdx, r1
	add	r2, rt
	adc	%rdx, r0
	adc	zr, r1
	add	sc, rt
	adc	r3, r0
	adc	zr, r1

	mov	2*8(bp), %rdx
	mulx	-3*8(ap), sc, sc
	mulx	-2*8(ap), r3, r2
	add	sc, rt
	adc	r2, r0
	mulx	-1*8(ap), sc, r4
	mulx	0*8(ap), %rdx, r2
	adc	r4, r1
	adc	zr, r2
	add	r3, rt
	adc	sc, r0
	adc	%rdx, r1
	adc	zr, r2

	# FIXME Remove
	mov	2*8(bp), %rdx
	mulx	-3*8(ap), sc, sc
	mulx	-2*8(ap), r3, r2
	add	sc, rt
	adc	r2, r0
	mulx	-1*8(ap), sc, r4
	mulx	0*8(ap), %rdx, r2
	adc	r4, r1
	adc	zr, r2
	add	r3, rt
	adc	sc, r0
	adc	%rdx, r1
	adc	zr, r2

	test	%al, %al
	mov	3*8(bp), %rdx
	mulx	-4*8(ap), sc, sc
	mulx	-3*8(ap), r4, r3
	adox	sc, rt
	adox	r3, r0
	adcx	r4, rt
	mulx	-2*8(ap), sc, r3
	adcx	sc, r0
	adox	r3, r1
	mulx	-1*8(ap), r4, sc
	adcx	r4, r1
	adox	sc, r2
	mulx	0*8(ap), %rdx, r3
	adcx	%rdx, r2
	adox	zr, r3
	adcx	zr, r3

	mov	4*8(bp), %rdx
	mulx	-5*8(ap), sc, sc
	adcx	sc, rt
	mulx	-4*8(ap), r4, sc
	adox	r4, rt
	adcx	sc, r0
	mulx	-3*8(ap), r4, sc
	adox	r4, r0
	adcx	sc, r1
	mov	r0, 0*8(rp)
	mulx	-2*8(ap), r4, sc
	adox	r4, r1
	adcx	sc, r2
	mov	r1, 1*8(rp)
	mulx	-1*8(ap), r4, sc
	mulx	0*8(ap), %rdx, r0
	adox	r4, r2
	adox	%rdx, r3
	adox	zr, r0
	mov	r2, 2*8(rp)
	adcx	sc, r3
	adcx	zr, r0
	mov	r3, 3*8(rp)
	mov	r0, 4*8(rp)

L(ex):	pop	%r13
	pop	%r12
	pop	%rbp
	pop	%rbx

	ret
.flint_mpn_mulhigh_n_basecase_end:
SIZE(flint_mpn_mulhigh_n_basecase, .flint_mpn_mulhigh_n_basecase_end)
.cfi_endproc
