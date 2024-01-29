#
#   Copyright (C) 2024 Albin Ahlbäck
#
#   This file is part of FLINT.
#
#   FLINT is free software: you can redistribute it and/or modify it under
#   the terms of the GNU Lesser General Public License (LGPL) as published
#   by the Free Software Foundation; either version 2.1 of the License, or
#   (at your option) any later version.  See <https://www.gnu.org/licenses/>.
#

include(`config.m4')dnl
dnl
.text

.global	FUNC(flint_mpn_mulhigh_basecase)
.p2align	4, 0x90
TYPE(flint_mpn_mulhigh_basecase)

FUNC(flint_mpn_mulhigh_basecase):
	.cfi_startproc
	push	%rbx
	push	%rbp
	push	%r12
	push	%r13
	push	%r14
	push	%r15

	mov	%rdx, %rcx
	mov	0*8(%rdx), %rdx
	lea	-7*8(%rsi,%r8,8), %rsi
	lea	5*8(%rcx), %rcx
	xor	%r10d, %r10d

	mulx	5*8(%rsi), %r9, %rax
	mulx	6*8(%rsi), %r9, %rbx
	adcx	%r9, %rax
	adcx	%r10, %rbx

	mov	-4*8(%rcx), %rdx
	mulx	4*8(%rsi), %r9, %r12
	mulx	5*8(%rsi), %r9, %rbp
	adcx	%r12, %rax
	adox	%r9, %rax
	adcx	%rbp, %rbx
	mulx	6*8(%rsi), %r9, %rbp
	adox	%r9, %rbx
	adcx	%r10, %rbp
	adox	%r10, %rbp

	mov	-3*8(%rcx), %rdx
	mulx	3*8(%rsi), %r9, %r13
	mulx	4*8(%rsi), %r9, %r12
	adcx	%r13, %rax
	adox	%r9, %rax
	adcx	%r12, %rbx
	mulx	4*8(%rsi), %r9, %r12
	adox	%r9, %rbx
	adcx	%r12, %rbp
	mulx	6*8(%rsi), %r9, %r12
	adox	%r9, %rbp
	adcx	%r10, %r12
	adox	%r10, %r12

	mov	-2*8(%rcx), %rdx
	mulx	2*8(%rsi), %r9, %r14
	mulx	3*8(%rsi), %r9, %r13
	adcx	%r14, %rax
	adox	%r9, %rax
	adcx	%r13, %rbx
	mulx	3*8(%rsi), %r9, %r13
	adox	%r9, %rbx
	adcx	%r13, %rbp
	mulx	4*8(%rsi), %r9, %r13
	adox	%r9, %rbp
	adcx	%r13, %r12
	mulx	6*8(%rsi), %r9, %r13
	adox	%r9, %r12
	adcx	%r10, %r13
	adox	%r10, %r13

	mov	-1*8(%rcx), %rdx
	mulx	1*8(%rsi), %r9, %r15
	mulx	2*8(%rsi), %r9, %r14
	adcx	%r15, %rax
	adox	%r9, %rax
	adcx	%r14, %rbx
	mulx	2*8(%rsi), %r9, %r14
	adox	%r9, %rbx
	adcx	%r14, %rbp
	mulx	3*8(%rsi), %r9, %r14
	adox	%r9, %rbp
	adcx	%r14, %r12
	mulx	4*8(%rsi), %r9, %r14
	adox	%r9, %r12
	adcx	%r14, %r13
	mulx	6*8(%rsi), %r9, %r14
	adox	%r9, %r13
	adcx	%r10, %r14
	adox	%r10, %r14

	mov	0*8(%rcx), %rdx
	mulx	0*8(%rsi), %r9, %r11
	mulx	1*8(%rsi), %r9, %r15
	adcx	%r11, %rax
	adox	%r9, %rax
	adcx	%r15, %rbx
	mulx	1*8(%rsi), %r9, %r15
	adox	%r9, %rbx
	adcx	%r15, %rbp
	mulx	2*8(%rsi), %r9, %r15
	adox	%r9, %rbp
	adcx	%r15, %r12
	mulx	3*8(%rsi), %r9, %r15
	adox	%r9, %r12
	adcx	%r15, %r13
	mulx	4*8(%rsi), %r9, %r15
	adox	%r9, %r13
	adcx	%r15, %r14
	mulx	6*8(%rsi), %r9, %r15
	adox	%r9, %r14
	adcx	%r10, %r15
	adox	%r10, %r15

	lea	-6(%r8), %r8
.Lloop:
	lea	1*8(%rsi), %rsi
	lea	1*8(%rcx), %rcx
	mulx	0*8(%rsi), %r9, %r11
	adcx	%r9, %rbx
	adcx	%r11, %rbp
	mulx	1*8(%rsi), %r9, %r11
	adox	%r9, %rbp
	adox	%r11, %r12
	mulx	2*8(%rsi), %r9, %r11
	adcx	%r9, %r12
	adcx	%r11, %r13
	mulx	3*8(%rsi), %r9, %r11
	adox	%r9, %r13
	adox	%r11, %r14
	mulx	4*8(%rsi), %r9, %r11
	adcx	%r9, %r14
	adcx	%r11, %r15
	mulx	5*8(%rsi), %r9, %r11
	adox	%r9, %r15
	adcx	%r10, %r11
	adox	%r10, %r11
	dec	%r8
	lea	6*8(%rdi), %rdi
	test	%r8, %r8
	jnz	.Lloop
	mov	%rbx, 0*8(%rdi)
	mov	%rbp, 1*8(%rdi)
	mov	%r12, 2*8(%rdi)
	mov	%r13, 3*8(%rdi)
	mov	%r14, 4*8(%rdi)
	mov	%r15, 5*8(%rdi)

	pop	%r15
	pop	%r14
	pop	%r13
	pop	%r12
	pop	%rbp
	pop	%rbx

	ret
.flint_mpn_mulhigh_basecase_end:
SIZE(flint_mpn_mulhigh_basecase, .flint_mpn_mulhigh_basecase_end)
.cfi_endproc
