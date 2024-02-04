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
define(`n',	`%rcx')

define(`bp',	`%r8')
define(`n_save',`%r9')

.text

.global	FUNC(flint_mpn_mulhigh_n_basecase)
ALIGN(32)
TYPE(flint_mpn_mulhigh_n_basecase)

FUNC(flint_mpn_mulhigh_n_basecase):
	.cfi_startproc
	mov	bp_old, bp

	push	%rbx
	push	%rbp
	push	%r12
	push	%r13
	push	%r14
	push	%r15

	ALIGN(32)
L(lp1):	mov	0*8(bp), %rdx
	mulx	0*8(ap), s0, s0
	mulx	1*8(ap), s1, s2
	add	s0, r0
	adc	s2, r1
	mulx	2*8(ap), s3, s4
	mulx	3*8(ap), s0, s2
	adc	s4, r2
	adc	s2, r3
	mulx	4*8(ap), %rdx, s4
	adc	s4, r4
	adc	$0, r5
	add	$8, bp
	sub	$8, ap
	dec	n
	add	s1, r0
	adc	s3, r1
	adc	s0, r2
	adc	%rdx, r3
	adc	$0, r4
	adc	$0, r5
	jrcxz	L(cnt)
	jmp	L(lp1)

L(cnt):

	ALIGN(32)
L(lp2):	mov	0*8(bp), %rdx
	mulx	0*8(ap), s0, s1
	add	s0, r0
	adc	s1, r1
	mulx	1*8(ap), s2, s3
	mulx	2*8(ap), s0, s1
	adc	s3, r2
	adc	s1, r3
	mulx	3*8(ap), %rdx, s3
	adc	s3, r4
	adc	$0, r5
	add	$8, bp
	sub	$8, ap
	dec	n
	add	s2, r1
	adc	s0, r2
	adc	%rdx, r3
	adc	$0, r4
	adc	$0, r5
	jrcxz	L(nxt)
	jmp	L(lp2)

L(nxt):

L(fin):	pop	%r15
	pop	%r14
	pop	%r13
	pop	%r12
	pop	%rbp
	pop	%rbx

	ret
.flint_mpn_mulhigh_n_basecase_end:
SIZE(flint_mpn_mulhigh_n_basecase, .flint_mpn_mulhigh_n_basecase_end)
.cfi_endproc
