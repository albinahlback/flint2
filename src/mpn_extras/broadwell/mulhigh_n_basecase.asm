#  AMD64 mpn_addmul_1 optimised for Intel Broadwell.
#
#  Copyright 2015, 2017 Free Software Foundation, Inc.
#
#  This file is part of the GNU MP Library.
#
#  The GNU MP Library is free software; you can redistribute it and/or modify
#  it under the terms of either:
#
#    * the GNU Lesser General Public License as published by the Free
#      Software Foundation; either version 3 of the License, or (at your
#      option) any later version.
#
#  or
#
#    * the GNU General Public License as published by the Free Software
#      Foundation; either version 2 of the License, or (at your option) any
#      later version.
#
#  or both in parallel, as here.
#
#  The GNU MP Library is distributed in the hope that it will be useful, but
#  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
#  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
#  for more details.
#
#  You should have received copies of the GNU General Public License and the
#  GNU Lesser General Public License along with the GNU MP Library.  If not,
#  see https://www.gnu.org/licenses/.
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
define(`bp_old',	`%rdx')
define(`n_old',	`%rcx')

define(`bp',	`%r8')
define(`ret',	`%rax')

define(`r0',	`%r11')
define(`r1',	`%rbx')
define(`r2',	`%rbp')
define(`r3',	`%r12')

define(`s0',	`%rbx')
define(`s0_32',	`%ebx')
define(`s1',	`%rbp')
define(`s2',	`%r12')
define(`s3',	`%r11')

define(`sc',	`%r9')
define(`zr',	`%r10')
define(`zr_32',	`%r10d')

define(`n',	`%r9')
define(`m',	`%rcx')
define(`m_32',	`%ecx')
define(`m_save',	`%r10')
define(`m_save_32',	`%r10d')

.text

.macro	tr_4 ap=%rsi, ap_os=0, bp=%r8, bp_os=0, t0, t1, t2, t3, t4, sc1, sc2, sc2_32
	mov	(\bp_os + 0)*8(\bp), %rdx
	mulx	(\ap_os - 1)*8(\ap), \t0, \t0
	mulx	(\ap_os - 0)*8(\ap), \sc1, \t1
	add	\sc1, \t0
	adc	$0, \t1
	xor	\sc2_32, \sc2_32

	mov	(\bp_os + 1)*8(\bp), %rdx
	mulx	(\ap_os - 2)*8(\ap), \sc1, \sc1
	adcx	\sc1, \t0
	mulx	(\ap_os - 1)*8(\ap), \sc1, \t2
	adox	\sc1, \t0
	adcx	\t2, \t1
	mulx	(\ap_os - 0)*8(\ap), \sc1, \t2
	adox	\sc1, \t1
	adcx	\sc2, \t2
	adox	\sc2, \t2

	mov	(\bp_os + 2)*8(\bp), %rdx
	mulx	(\ap_os - 3)*8(\ap), \sc1, \sc1
	adcx	\sc1, \t0
	mulx	(\ap_os - 2)*8(\ap), \sc1, \t3
	adox	\sc1, \t0
	adcx	\t3, \t1
	mulx	(\ap_os - 1)*8(\ap), \sc1, \t3
	adox	\sc1, \t1
	adcx	\t3, \t2
	mulx	(\ap_os - 0)*8(\ap), \sc1, \t3
	adox	\sc1, \t2
	adcx	\sc2, \t3
	adox	\sc2, \t3

	mov	(\bp_os + 3)*8(\bp), %rdx
	mulx	(\ap_os - 4)*8(\ap), \sc1, \sc1
	adcx	\sc1, \t0
	mulx	(\ap_os - 3)*8(\ap), \sc1, \t4
	adox	\sc1, \t0
	adcx	\t4, \t1
	mulx	(\ap_os - 2)*8(\ap), \sc1, \t4
	adox	\sc1, \t1
	adcx	\t4, \t2
	mulx	(\ap_os - 1)*8(\ap), \sc1, \t4
	adox	\sc1, \t2
	adcx	\t4, \t3
	mulx	(\ap_os - 0)*8(\ap), \sc1, \t4
	adox	\sc1, \t3
	adcx	\sc2, \t4
	adox	\sc2, \t4
.endm

.global	FUNC(flint_mpn_mulhigh_n_basecase)
.p2align	5, 0x90
TYPE(flint_mpn_mulhigh_n_basecase)

FUNC(flint_mpn_mulhigh_n_basecase):
	.cfi_startproc
	mov	bp_old, bp
	lea	-4*8(ap,n_old,8), ap	# ap += n - 4
	lea	4*8(bp), bp		# bp += 4

	push	%rbx
	push	%rbp
	push	%r12

	# Initial triangle
	tr_4	ap, 3, bp, -4, ret, r0, r1, r2, r3, sc, zr, zr_32
	mov	r0, 0*8(rp)
	mov	r1, 1*8(rp)
	mov	r2, 2*8(rp)
	mov	r3, 3*8(rp)

	# Addmul chains
	lea	-1(n_old), n
	mov	$4, m_save_32
	mov	$4, m_32

	.align	32, 0x90
.Lloop:	mov	0*8(bp), %rdx
	mulx	-2*8(ap), s1, s1
.Lfin:	mov	m_32, s0_32
	shr	$3, m
	and	$7, s0_32
	mulx	-1*8(%rsi), %r12, %r11
	adcx	%rbp, %rax
	adox	%r12, %rax
	mov	%r11, %rbp
	lea	.Ljmptab(%rip), %r12
ifdef(`PIC',
`	movslq	(%r12,%rbx,4), %rbx
	lea	(%rbx,%r12), %r12
	jmp	*%r12
',`
	jmp	*(%r12,%rbx,8)
')
	.section	.data.rel.ro.local,"a",@progbits
	.align	8, 0x90
ifdef(`PIC',
`.Ljmptab:
	.long	.Lp0-.Ljmptab
	.long	.Lp1-.Ljmptab
	.long	.Lp2-.Ljmptab
	.long	.Lp3-.Ljmptab
	.long	.Lp4-.Ljmptab
	.long	.Lp5-.Ljmptab
	.long	.Lp6-.Ljmptab
	.long	.Lp7-.Ljmptab',
`.Ljmptab:
	.quad	.Lp0
	.quad	.Lp1
	.quad	.Lp2
	.quad	.Lp3
	.quad	.Lp4
	.quad	.Lp5
	.quad	.Lp6
	.quad	.Lp7')
	.text

.Lp0:	mulx	0*8(%rsi), %rbx, %rbp
	adcx	%r11, %rbx
	lea	-1*8(%rsi), %rsi
	lea	-1*8(%rsi), %rdi
	lea	-1(%rcx), %rcx
	jmp	.Lam0
.Lp1:	mulx	0*8(%rsi), %r12, %r11
	adcx	%rbp, %r12
	jmp	.Lam1
.Lp2:	mulx	0*8(%rsi), %rbx, %rbp
	adcx	%r11, %rbx
	lea	1*8(%rsi), %rsi
	lea	1*8(%rdi), %rdi
	jmp	.Lam2
.Lp3:	mulx	0*8(%rsi), %r12, %r11
	adcx	%rbp, %r12
	lea	2*8(%rsi), %rsi
	lea	-6*8(%rdi), %rdi
	jmp	.Lam3
.Lp4:	mulx	0*8(%rsi), %rbx, %rbp
	adcx	%r11, %rbx
	lea	3*8(%rsi), %rsi
	lea	-5*8(%rdi), %rdi
	jmp	.Lam4
.Lp6:	mulx	0*8(%rsi), %rbx, %rbp
	adcx	%r11, %rbx
	lea	5*8(%rsi), %rsi
	lea	-3*8(%rdi), %rdi
	jmp	.Lam6
.Lp7:	mulx	0*8(%rsi), %r12, %r11
	adcx	%rbp, %r12
	lea	-2*8(%rsi), %rsi
	lea	-2*8(%rdi), %rdi
	jmp	.Lam7

.Lp5:	mulx	0*8(%rsi), %r12, %r11
	adcx	%rbp, %r12
	lea	4*8(%rsi), %rsi
	lea	-4*8(%rdi), %rdi
	.align	32, 0x90
.Lam5:	mulx	-3*8(%rsi), %rbx, %rbp
	adcx	%r11, %rbx
	adox	4*8(%rdi), %r12
	mov	%r12, 4*8(%rdi)
.Lam4:	mulx	-2*8(%rsi), %r12, %r11
	adox	5*8(%rdi), %rbx
	adcx	%rbp, %r12
	mov	%rbx, 5*8(%rdi)
.Lam3:	adox	6*8(%rdi), %r12
	mulx	-1*8(%rsi), %rbx, %rbp
	mov	%r12, 6*8(%rdi)
	lea	8*8(%rdi), %rdi
	adcx	%r11, %rbx
.Lam2:	mulx	0*8(%rsi), %r12, %r11
	adox	-1*8(%rdi), %rbx
	adcx	%rbp, %r12
	mov	%rbx, -1*8(%rdi)
	jrcxz	.Lend
.Lam1:	mulx	1*8(%rsi), %rbx, %rbp
	adox	0*8(%rdi), %r12
	lea	-1(%rcx), %rcx
	mov	%r12, 0*8(%rdi)
	adcx	%r11, %rbx
.Lam0:	mulx	2*8(%rsi), %r12, %r11
	adcx	%rbp, %r12
	adox	1*8(%rdi), %rbx
	mov	%rbx, 1*8(%rdi)
.Lam7:	mulx	3*8(%rsi), %rbx, %rbp
	lea	8*8(%rsi), %rsi
	adcx	%r11, %rbx
	adox	2*8(%rdi), %r12
	mov	%r12, 2*8(%rdi)
.Lam6:	mulx	-4*8(%rsi), %r12, %r11
	adox	3*8(%rdi), %rbx
	adcx	%rbp, %r12
	mov	%rbx, 3*8(%rdi)
	jmp	.Lam5

.Lend:	adox	0*8(%rdi), %r12
	adcx	%rcx, %r11
	adox	%rcx, %r11
	lea	1(%r10), %rcx
	neg	%r10
	lea	1*8(%r8), %r8
	mov	%r12, 0*8(%rdi)
	mov	%r11, 1*8(%rdi)
	lea	1*8(%rdi,%r10,8), %rdi
	lea	(%rsi,%r10,8), %rsi
	neg	%r10
	cmp	%r9, %rcx
	lea	1(%r10), %r10
	jb	.Lloop
	ja	.Lexit
	mov	0*8(%r8), %rdx
	xor	%ebp, %ebp
	jmp	.Lfin

.Lexit:	pop	%r12
	pop	%rbp
	pop	%rbx

	ret
.flint_mpn_mulhigh_n_basecase_end:
SIZE(flint_mpn_mulhigh_n_basecase, .flint_mpn_mulhigh_n_basecase_end)
.cfi_endproc
