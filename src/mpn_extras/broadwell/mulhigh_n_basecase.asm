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

.global	FUNC(flint_mpn_mulhigh_n_basecase)
.p2align	4, 0x90
TYPE(flint_mpn_mulhigh_n_basecase)

FUNC(flint_mpn_mulhigh_n_basecase):
	.cfi_startproc
	push	%rbx
	push	%rbp
	push	%r12
	push	%r13
	push	%r14
	push	%r15

	mov	%rdx, %r8
	mov	0*8(%rdx), %rdx
	lea	-4*8(%rsi,%rcx,8), %rsi
	lea	3*8(%r8), %r8
	lea	-4(%rcx), %rcx
	xor	%r10d, %r10d

	mulx	2*8(%rsi), %r9, %rax
	mulx	3*8(%rsi), %r9, %rbx
	adcx	%r9, %rax
	adcx	%r10, %rbx

	mov	-2*8(%r8), %rdx
	mulx	1*8(%rsi), %r9, %r12
	mulx	2*8(%rsi), %r9, %rbp
	adcx	%r12, %rax
	adox	%r9, %rax
	adcx	%rbp, %rbx
	mulx	3*8(%rsi), %r9, %rbp
	adox	%r9, %rbx
	adcx	%r10, %rbp
	adox	%r10, %rbp

	mov	-1*8(%r8), %rdx
	mulx	0*8(%rsi), %r9, %r11
	mulx	1*8(%rsi), %r9, %r12
	adcx	%r11, %rax
	adox	%r9, %rax
	adcx	%r12, %rbx
	mulx	2*8(%rsi), %r9, %r12
	adox	%r9, %rbx
	adcx	%r12, %rbp
	mulx	3*8(%rsi), %r9, %r12
	adox	%r9, %rbp
	adcx	%r10, %r12
	adox	%r10, %r12

.L1:
	mov	0*8(%r8), %rdx
	mulx	-1*8(%rsi), %r9, %r11
	adox	%r11, %rax
	mulx	0*8(%rsi), %r9, %r11
	adcx	%r9, %rax
	adcx	%r11, %rbx
	mulx	1*8(%rsi), %r9, %r11
	adox	%r9, %rbx
	adox	%r11, %rbp
	mulx	2*8(%rsi), %r9, %r11
	adcx	%r9, %rbp
	adcx	%r11, %r12
	adcx	%r10, %r11
	adox	%r10, %r11
	dec	%rcx
	lea	-1*8(%rsi), %rsi
	lea	1*8(%r8), %r8
	jnz	.L1
	mov	0*8(%r8), %rdx
	mulx	0*8(%rsi), %r9, %r11
	adcx	%r9, %rax
	adcx	%r11, %rbx
	mulx	1*8(%rsi), %r9, %r11
	adox	%r9, %rbx
	adox	%r11, %rbp
	mulx	2*8(%rsi), %r9, %r11
	adcx	%r9, %rbp
	adcx	%r11, %r12
	adcx	%r10, %r11
	adox	%r10, %r11
	mov	%rbx, 0*8(%rdi)
	mov	%rbp, 1*8(%rdi)
	mov	%r12, 2*8(%rdi)

	pop	%r15
	pop	%r14
	pop	%r13
	pop	%r12
	pop	%rbp
	pop	%rbx

	ret
.flint_mpn_mulhigh_n_basecase_end:
SIZE(flint_mpn_mulhigh_n_basecase, .flint_mpn_mulhigh_n_basecase_end)
.cfi_endproc
