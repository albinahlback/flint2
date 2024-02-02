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

include(`config.m4')dnl
dnl
.text

.macro	tr_4 ap=%rsi, ap_os=0, bp=%r8, bp_os=0, r0, r1, r2, r3, r4, sc, zr, zr32
	mov	(\bp_os + 0)*8(\bp), %rdx
	mulx	(\ap_os - 1)*8(\ap), \r0, \r0
	mulx	(\ap_os - 0)*8(\ap), \sc, \r1
	add	\sc, \r0
	adc	$0, \r1
	xor	\zr32, \zr32

	mov	(\bp_os + 1)*8(\bp), %rdx
	mulx	(\ap_os - 2)*8(\ap), \sc, \sc
	adcx	\sc, \r0
	mulx	(\ap_os - 1)*8(\ap), \sc, \r2
	adox	\sc, \r0
	adcx	\r2, \r1
	mulx	(\ap_os - 0)*8(\ap), \sc, \r2
	adox	\sc, \r1
	adcx	\zr, \r2
	adox	\zr, \r2

	mov	(\bp_os + 2)*8(\bp), %rdx
	mulx	(\ap_os - 3)*8(\ap), \sc, \sc
	adcx	\sc, \r0
	mulx	(\ap_os - 2)*8(\ap), \sc, \r3
	adox	\sc, \r0
	adcx	\r3, \r1
	mulx	(\ap_os - 1)*8(\ap), \sc, \r3
	adox	\sc, \r1
	adcx	\r3, \r2
	mulx	(\ap_os - 0)*8(\ap), \sc, \r3
	adox	\sc, \r2
	adcx	\zr, \r3
	adox	\zr, \r3

	mov	(\bp_os + 3)*8(\bp), %rdx
	mulx	(\ap_os - 4)*8(\ap), \sc, \sc
	adcx	\sc, \r0
	mulx	(\ap_os - 3)*8(\ap), \sc, \r4
	adox	\sc, \r0
	adcx	\r4, \r1
	mulx	(\ap_os - 2)*8(\ap), \sc, \r4
	adox	\sc, \r1
	adcx	\r4, \r2
	mulx	(\ap_os - 1)*8(\ap), \sc, \r4
	adox	\sc, \r2
	adcx	\r4, \r3
	mulx	(\ap_os - 0)*8(\ap), \sc, \r4
	adox	\sc, \r3
	adcx	\zr, \r4
	adox	\zr, \r4
.endm

.global	FUNC(flint_mpn_mulhigh_n_basecase)
.p2align	5, 0x90
TYPE(flint_mpn_mulhigh_n_basecase)

FUNC(flint_mpn_mulhigh_n_basecase):
	.cfi_startproc
	mov	%rdx, %r8
	lea	-4*8(%rsi,%rcx,8), %rsi
	lea	4*8(%r8), %r8
	push	%rbx
	push	%rbp
	push	%r12

	tr_4	%rsi, 3, %r8, -4, %rax, %r11, %rbx, %rbp, %r12, %r9, %r10, %r10d
	mov	%r11, 0*8(%rdi)
	mov	%rbx, 1*8(%rdi)
	mov	%rbp, 2*8(%rdi)
	mov	%r12, 3*8(%rdi)

	lea	-1(%rcx), %r9
	mov	$4, %r10d
	mov	$4, %ecx
	jmp	.Ltmp
	.align	32, 0x90
.Lloop:	mov	0*8(%r8), %rdx
	mulx	-2*8(%rsi), %rbp, %rbp
.Lfin:	mov	%ecx, %ebx
	shr	$3, %rcx
	and	$7, %ebx
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
	lea	(%rdi,%r10,8), %rdi
	lea	(%rsi,%r10,8), %rsi
	neg	%r10
	cmp	%r9, %rcx
	lea	1(%r10), %r10
	jb	.Lloop
	ja	.Lexit
.Ltmp:	mov	0*8(%r8), %rdx
	xor	%ebp, %ebp
	jmp	.Lfin

.Lexit:	pop	%r12
	pop	%rbp
	pop	%rbx

	ret
.flint_mpn_mulhigh_n_basecase_end:
SIZE(flint_mpn_mulhigh_n_basecase, .flint_mpn_mulhigh_n_basecase_end)
.cfi_endproc
