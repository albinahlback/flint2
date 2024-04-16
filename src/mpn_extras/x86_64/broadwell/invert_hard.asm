dnl
dnl Copyright (C) 2024 Albin Ahlbäck
dnl
dnl This file is part of FLINT.
dnl
dnl FLINT is free software: you can redistribute it and/or modify it under
dnl the terms of the GNU Lesser General Public License (LGPL) as published
dnl by the Free Software Foundation; either version 3 of the License, or
dnl (at your option) any later version.  See <https://www.gnu.org/licenses/>.
dnl

include(`config.m4')

define(`ip',  `%rdi')
define(`dp',  `%rsi')

define(`r0',  `%rax')
define(`r1',  `%rdx')
define(`r2',  `%rcx')
define(`r3',  `%r8')
define(`r4',  `%r9')
define(`r5',  `%r10')
define(`r6',  `%r11')
define(`r7',  `%rbx')
define(`r8',  `%rbp')
define(`r9',  `%r12')
define(`r10', `%r13')
define(`r11', `%r14')
define(`r12', `%r15')

	TEXT
	ALIGN(16)
PROLOGUE(flint_mpn_invert_1)
	mov	$-1, %rdx
	mov	$-1, %rax
	sub	0*8(dp), %rdx
	divq	0*8(dp)
	mov	%rax, 0*8(ip)
	ret
EPILOGUE()

