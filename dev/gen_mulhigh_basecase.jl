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

_regs = ["%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9", "%r10", "%r11", "%rax"]
__regs = ["%rbx", "%rbp", "%r12", "%r13", "%r14", "%r15"]

function R8(reg::String)
    if reg == "%rax"
        return "%al"
    elseif reg == "%rbx"
        return "%bl"
    elseif reg == "%rcx"
        return "%cl"
    elseif reg == "%rdx"
        return "%dl"
    elseif reg == "%rsp"
        return "%spl"
    elseif reg == "%rbp"
        return "%bpl"
    elseif reg == "%rsi"
        return "%sil"
    elseif reg == "%rdi"
        return "%dil"
    elseif reg == "%r8"
        return "%r8b"
    elseif reg == "%r9"
        return "%r9b"
    elseif reg == "%r10"
        return "%r10b"
    elseif reg == "%r11"
        return "%r11b"
    elseif reg == "%r12"
        return "%r12b"
    elseif reg == "%r13"
        return "%r13b"
    elseif reg == "%r14"
        return "%r14b"
    elseif reg == "%r15"
        return "%r15b"
    else
        return "hejhoppgummi"
    end
end

function R32(reg::String)
    if reg == "%rax"
        return "%eax"
    elseif reg == "%rbx"
        return "%ebx"
    elseif reg == "%rcx"
        return "%ecx"
    elseif reg == "%rdx"
        return "%edx"
    elseif reg == "%rsp"
        return "%esp"
    elseif reg == "%rbp"
        return "%ebp"
    elseif reg == "%rsi"
        return "%esi"
    elseif reg == "%rdi"
        return "%edi"
    elseif reg == "%r8"
        return "%r8d"
    elseif reg == "%r9"
        return "%r9d"
    elseif reg == "%r10"
        return "%r10d"
    elseif reg == "%r11"
        return "%r11d"
    elseif reg == "%r12"
        return "%r12d"
    elseif reg == "%r13"
        return "%r13d"
    elseif reg == "%r14"
        return "%r14d"
    elseif reg == "%r15"
        return "%r15d"
    else
        return "hejhoppgummi"
    end
end

###############################################################################
# Preamble
###############################################################################

copyright = "#
#   Copyright (C) 2024 Albin Ahlbäck
#
#   This file is part of FLINT.
#
#   FLINT is free software: you can redistribute it and/or modify it under
#   the terms of the GNU Lesser General Public License (LGPL) as published
#   by the Free Software Foundation; either version 3 of the License, or
#   (at your option) any later version.  See <https://www.gnu.org/licenses/>.
#\n"

preamble = "include(`config.m4')dnl\ndnl\n.text\n"

function function_pre_post(funname::String)
    pre = ".global\tFUNC($funname)
.p2align\t4, 0x90
TYPE($funname)

FUNC($funname):
\t.cfi_startproc\n"

    post = ".$(funname)_end:
SIZE($(funname), .$(funname)_end)
.cfi_endproc\n"

    return (pre, post)
end

###############################################################################
# mulhigh, hardcoded
###############################################################################

function mulhigh_1()
    r0 = _regs[9] # Important that r0 is rax
    r1 = _regs[4]

    res = _regs[1]
    ap = _regs[2]
    bp = _regs[3]

    body = ""

    body *= "\tmov\t0*8($bp), %rdx\n"
    body *= "\tmulx\t0*8($ap), $r0, $r1\n"
    body *= "\tmov\t$r1, 0*8($res)\n"

    return body * "\n\tret\n"
end

function mulhigh_2()
    r0 = _regs[9]
    r1 = _regs[4]
    r2 = _regs[5]

    sc = _regs[6]
    zr = _regs[7]

    res = _regs[1]
    ap = _regs[2]
    bp_old = _regs[3]
    b1 = _regs[8]

    body = ""

    body *= "\tmov\t1*8($bp_old), $b1\n"
    body *= "\tmov\t0*8($bp_old), %rdx\n"
    body *= "\txor\t$(R32(zr)), $(R32(zr))\n"
    body *= "\tmulx\t0*8($ap), $sc, $r0\n"
    body *= "\tmulx\t1*8($ap), $sc, $r1\n"
    body *= "\tadcx\t$sc, $r0\n"
    body *= "\tadcx\t$zr, $r1\n"

    body *= "\tmov\t$b1, %rdx\n"
    body *= "\tmulx\t0*8($ap), $sc, $r2\n"
    body *= "\tadcx\t$sc, $r0\n"
    body *= "\tadcx\t$r2, $r1\n"
    body *= "\tmulx\t1*8($ap), $sc, $r2\n"
    body *= "\tadox\t$sc, $r1\n"
    body *= "\tadox\t$zr, $r2\n"
    body *= "\tadcx\t$zr, $r2\n"
    body *= "\tmov\t$r1, 0*8($res)\n"
    body *= "\tmov\t$r2, 1*8($res)\n"

    return body * "\n\tret\n"
end

# When n = 9, push res to stack.
# When n = 10, push res and rsp to xmm register.
# When n = 11, do it like n = 10, and also use bp as r(11) as r(11) is only
# really needed in the last step.
# When n = 12, do it like n = 11 but do not use a zero register.
function mulhigh(n::Int; debug::Bool = false)
    if n < 1
        error()
    elseif n == 1
        return mulhigh_1()
    elseif n == 2
        return mulhigh_2()
    elseif n <= 12
        # Continue
    else
        error()
    end

    if debug
        res = "res"
        ap = "ap"
        bp_old = "bp_old"
        bp = "bp"
        sc = "sc"
        zr = "zr"
    else
        res = _regs[1]
        ap = _regs[2]
        bp_old = _regs[3] # rdx
        bp = _regs[4] # rdx is used by mulx, so we need to switch register for bp

        if n != 12
            sc = _regs[5] # scrap register
            zr = (n < 10) ? _regs[6] : "%rsp" # zero
        else
            sc = "%rsp"
            zr = sc
        end

        if n < 9
            _r = [_regs[9]; _regs[7:8]; __regs[1:n - 2]]
        elseif n == 9
            _r = [_regs[9]; _regs[7:8]; __regs[1:6]; res]
        elseif n == 10
            _r = [_regs[9]; _regs[6:8]; __regs[1:6]; res]
        elseif n == 11
            _r = [_regs[9]; _regs[6:8]; __regs[1:6]; res; bp]
        elseif n == 12
            _r = [_regs[9]; _regs[5:8]; __regs[1:6]; res; bp]
        end
    end

    r(ix::Int) = debug ? "r$ix" : _r[ix + 1]

    # Push
    body = ""
    for ix in 1:min(n - 2, 6)
        body *= "\tpush\t$(__regs[ix])\n"
    end
    if n == 9
        body *= "\tpush\t$res\n"
    elseif n >= 10
        body *= "\tvmovq\t%rsp, %xmm0\n"
        body *= "\tvmovq\t$res, %xmm1\n"
    end
    body *= "\n"

    # Prepare
    body *= "\tmov\t$bp_old, $bp\n"
    body *= "\tmov\t0*8($bp_old), %rdx\n"
    if n != 12
        body *= "\txor\t$(R32(zr)), $(R32(zr))\n"
    end
    body *= "\n"

    # First multiplication chain
    body *= "\tmulx\t$(n - 2)*8($ap), $sc, $(r(0))\n"
    body *= "\tmulx\t$(n - 1)*8($ap), $sc, $(r(1))\n"
    if n != 12
        body *= "\tadcx\t$sc, $(r(0))\n"
        body *= "\tadcx\t$zr, $(r(1))\n"
    else
        body *= "\tadd\t$sc, $(r(0))\n"
        body *= "\tadc\t\$0, $(r(1))\n"
        body *= "\ttest\t%al, %al\n"
    end
    body *= "\n"

    # Intermediate multiplication chains
    for ix in 1:min(n - 2, (n != 12) ? 8 : 9)
        body *= "\tmov\t$ix*8($bp), %rdx\n"

        body *= "\tmulx\t$(n - 2 - ix)*8($ap), $sc, $(r(ix + 2))\n"
        body *= "\tmulx\t$(n - 1 - ix)*8($ap), $sc, $(r(ix + 1))\n"
        body *= "\tadcx\t$(r(ix + 2)), $(r(0))\n"
        body *= "\tadox\t$sc, $(r(0))\n"
        body *= "\tadcx\t$(r(ix + 1)), $(r(1))\n"

        for jx in 1:ix - 1
            body *= "\tmulx\t$(n - 1 - ix + jx)*8($ap), $sc, $(r(ix + 1))\n"
            body *= "\tadox\t$sc, $(r(jx + 0))\n"
            body *= "\tadcx\t$(r(ix + 1)), $(r(jx + 1))\n"
        end

        body *= "\tmulx\t$(n - 1)*8($ap), $sc, $(r(ix + 1))\n"
        body *= "\tadox\t$sc, $(r(ix + 0))\n"
        if n == 12
            body *= "\tmov\t\$0, $(R32(zr))\n"
        end
        body *= "\tadcx\t$zr, $(r(ix + 1))\n"
        body *= "\tadox\t$zr, $(r(ix + 1))\n"

        body *= "\n"
    end

    if n >= 11
        N = n - 1
        body *= "\tmov\t$(n - 2)*8($bp), %rdx\n"
        for ix in 0:n - 2
            body *= "\tmulx\t$ix*8($ap), $sc, $(r(N))\n"
            if ix == 0
                body *= "\tadcx\t$(r(N)), $(r(ix + 0))\n"
            else
                body *= "\tadox\t$sc, $(r(ix - 1))\n"
                body *= "\tadcx\t$(r(N)), $(r(ix + 0))\n"
            end
        end
        body *= "\tmulx\t$(n - 1)*8($ap), $sc, $(r(N))\n"
        body *= "\tadox\t$sc, $(r(N - 1))\n"
        if n == 12
            body *= "\tmov\t\$0, $(R32(zr))\n"
        end
        body *= "\tadcx\t$zr, $(r(N))\n"
        body *= "\tadox\t$zr, $(r(N))\n"
        body *= "\n"
    end

    # Last multiplication chain
    body *= "\tmov\t$(n - 1)*8($bp), %rdx\n"
    for ix in 0:n - 2
        body *= "\tmulx\t$ix*8($ap), $sc, $(r(n))\n"
        if ix % 2 == 0
            body *= "\tadcx\t$sc, $(r(ix + 0))\n"
            body *= "\tadcx\t$(r(n)), $(r(ix + 1))\n"
        else
            body *= "\tadox\t$sc, $(r(ix + 0))\n"
            body *= "\tadox\t$(r(n)), $(r(ix + 1))\n"
        end
    end
    body *= "\tmulx\t$(n - 1)*8($ap), $sc, $(r(n))\n"
    if (n - 1) % 2 == 0
        body *= "\tadcx\t$sc, $(r(n - 1))\n"
    else
        body *= "\tadox\t$sc, $(r(n - 1))\n"
    end
    if n == 12
        body *= "\tmov\t\$0, $(R32(zr))\n"
    end
    body *= "\tadcx\t$zr, $(r(n))\n"
    if n == 9
        # Use scrap register for storing pointer to res
        res = sc
        body *= "\tpop\t$res\n"
    end
    body *= "\tadox\t$zr, $(r(n))\n"
    body *= "\n"

    if n == 10 || n == 11
        res, zr = sc, "error zr"
        body *= "\tvmovq\t%xmm1, $res\n"
        body *= "\tvmovq\t%xmm0, %rsp\n"
    elseif n == 12
        res = sc
        body *= "\tvmovq\t%xmm1, $res\n"
    end

    # Store result
    for ix in 1:n
        body *= "\tmov\t$(r(ix)), $(ix - 1)*8($res)\n"
    end
    body *= "\n"

    # Pop
    if n == 12
        body *= "\tvmovq\t%xmm0, %rsp\n"
    end
    for ix in min(n - 2, 6):-1:1
        body *= "\tpop\t$(__regs[ix])\n"
    end
    body *= "\n"

    if debug
        print(body * "\tret\n")
    else
        return body * "\tret\n"
    end
end


###############################################################################
# Initial triangle
###############################################################################
# ap + ap_os ~= ap + n - 1
# Triangle with side of size k - 1.
# Assumes that bp[X] is already in rdx.
# r0 should be rax.
function macro_init_triangle(k::Int)
    pre = ".macro\ttr_init_$(k) ap=$(_regs[2]), ap_os=0, bp=$(_regs[5]), bp_os=0, "
    for ix in 0:k - 1
        pre *= "r$ix, "
    end
    pre *= "sc, zr\n"
    post = ".endm\n"

    body = ""
    body *= "\tmulx\t(\\ap_os - 1)*8(\\ap), \\r0, \\r0\n"
    body *= "\tmulx\t(\\ap_os - 0)*8(\\ap), \\sc, \\r1\n"
    body *= "\tadcx\t\\sc, \\r0\n"
    body *= "\tadcx\t\\zr, \\r1\n"
    body *= "\n"

    for ix in 1:k - 2
        body *= "\tmov\t$ix*8(\\bp), %rdx\n"
        body *= "\tmulx\t(\\ap_os - $(ix + 1))*8(\\ap), \\sc, \\sc\n"
        body *= "\tadcx\t\\sc, \\r0\n"
        body *= "\tmulx\t(\\ap_os - $(ix + 0))*8(\\ap), \\sc, \\r$(ix + 1)\n"
        body *= "\tadox\t\\sc, \\r0\n"
        body *= "\tadcx\t\\r$(ix + 1), \\r1\n"
        for jx in 2:ix
            body *= "\tmulx\t(\\ap_os - $(ix - jx + 1))*8(\\ap), \\sc, \\r$(ix + 1)\n"
            body *= "\tadox\t\\sc, \\r$(jx - 1)\n"
            body *= "\tadcx\t\\r$(ix + 1), \\r$(jx - 0)\n"
        end
        body *= "\tmulx\t(\\ap_os - 0)*8(\\ap), \\sc, \\r$(ix + 1)\n"
        body *= "\tadox\t\\sc, \\r$(ix + 0)\n"
        body *= "\tadcx\t\\zr, \\r$(ix + 1)\n"
        body *= "\tadox\t\\zr, \\r$(ix + 1)\n"
        if ix != k - 2
            body *= "\n"
        end
    end

    return pre * body * post
end

###############################################################################
# Initial parallelogram
###############################################################################
# Parallelogram with a projection of size mx + 1.
# r0 should be rax.
# Assumes cy is zero already
function macro_init_parallelogram(k::Int, unroll::Int = 0)
    pre = ".macro\tpg_init_$(k) ap=$(_regs[2]), ap_os=0, bp=$(_regs[5]), bp_os=0, mx=$(_regs[4]), "
    for ix in 0:k
        pre *= "r$ix, "
    end
    pre *= "cy, sl, sh, zr\n"
    post = ".endm\n"

    # Set initial rk
    body *= "\tmov\t(\\bp_os + 0)*8(\\bp), %rdx\n"
    body *= "\tmulx\t(\\ap_os + 0)*8(\\ap), \\sh, \\sh\n"
    body *= "\tadox\t\\sh, \\r0\n"
    body *= "\tmulx\t(\\ap_os + 1)*8(\\ap), \\sl, \\r$k\n"
    body *= "\tadcx\t\\sl, \\r0\n"
    body *= "\tadcx\t\\r$k, \\r1\n"
    for ix in 1:k - 2
        body *= "\tmulx\t(\\ap_os + $(ix + 1))*8(\\ap), \\sl, \\r$k\n"
        if ix % 2 == 0
            body *= "\tadcx\t\\sl, \\r$(ix + 0)\n"
            body *= "\tadcx\t\\r$k, \\r$(ix + 1)\n"
        else
            body *= "\tadox\t\\sl, \\r$(ix + 0)\n"
            body *= "\tadox\t\\r$k, \\r$(ix + 1)\n"
        end
    end
    body *= "\tmulx\t(\\ap_os + $(k - 1))*8(\\ap), \\sl, \\r$k\n"
    if k % 2 == 1
        body *= "\tadcx\t\\sl, \\r$(k - 1)\n"
    else
        body *= "\tadox\t\\sl, \\r$(k - 1)\n"
    end
    body *= "\tadcx\t\\zr, \\r$k\n"
    body *= "\tadox\t\\zr, \\r$k\n"
    body *= "\n"

    for ur in 1:unroll
        body *= "\tmov\t(\\bp_os + $ur)*8(\\bp), %rdx\n"
        body *= "\tmulx\t(\\ap_os + 0 - $ur)*8(\\ap), \\sh, \\sh\n"
        body *= "\tadox\t\\sh, \\r0\n"
        body *= "\tmulx\t(\\ap_os + 1 - $ur)*8(\\ap), \\sl, \\sh\n"
        body *= "\tadcx\t\\sl, \\r0\n"
        body *= "\tadcx\t\\sh, \\r1\n"
        for ix in 1:k - 2
            body *= "\tmulx\t(\\ap_os + $(ix + 1) - $ur)*8(\\ap), \\sl, \\sh\n"
            if ix % 2 == 0
                body *= "\tadcx\t\\sl, \\r$(ix + 0)\n"
                body *= "\tadcx\t\\sh, \\r$(ix + 1)\n"
            else
                body *= "\tadox\t\\sl, \\r$(ix + 0)\n"
                body *= "\tadox\t\\sh, \\r$(ix + 1)\n"
            end
        end
        body *= "\tmulx\t(\\ap_os + $(k - 1) - $ur)*8(\\ap), \\sl, \\sh\n"
        if k % 2 == 1
            body *= "\tadox\t\\zr, \\r$k\n"
            body *= "\tadcx\t\\sl, \\r$(k - 1)\n"
            body *= "\tadcx\t\\sh, \\r$k\n"
        else
            body *= "\tadcx\t\\zr, \\r$k\n"
            body *= "\tadox\t\\sl, \\r$(k - 1)\n"
            body *= "\tadox\t\\sh, \\r$k\n"
        end
        body *= "\tadcx\t\\zr, \\cy\n"
        body *= "\tadox\t\\zr, \\cy\n"
        body *= "\n"
    end

    # FIXME: Unroll this one?
    body *= ".Ltr_init:\n"
    body *= "\tmov\t(\\bp_os + $(unroll + 1))*8(\\bp), %rdx\n"
    body *= "\tmulx\t(\\ap_os + 0 - $(unroll + 1))*8(\\ap), \\sh, \\sh\n"
    body *= "\tadox\t\\sh, \\r0\n"
    body *= "\tmulx\t(\\ap_os + 1 - $(unroll + 1))*8(\\ap), \\sl, \\sh\n"
    body *= "\tadcx\t\\sl, \\r0\n"
    body *= "\tadcx\t\\sh, \\r1\n"
    for ix in 1:k - 2
        body *= "\tmulx\t(\\ap_os + $(ix + 1) - $(unroll + 1))*8(\\ap), \\sl, \\sh\n"
        if ix % 2 == 0
            body *= "\tadcx\t\\sl, \\r$(ix + 0)\n"
            body *= "\tadcx\t\\sh, \\r$(ix + 1)\n"
        else
            body *= "\tadox\t\\sl, \\r$(ix + 0)\n"
            body *= "\tadox\t\\sh, \\r$(ix + 1)\n"
        end
    end
    body *= "\tmulx\t(\\ap_os + $(k - 1) - $(unroll + 1))*8(\\ap), \\sl, \\sh\n"
    if k % 2 == 1
        body *= "\tadox\t\\zr, \\r$k\n"
        body *= "\tadcx\t\\sl, \\r$(k - 1)\n"
        body *= "\tadcx\t\\sh, \\r$k\n"
    else
        body *= "\tadcx\t\\zr, \\r$k\n"
        body *= "\tadox\t\\sl, \\r$(k - 1)\n"
        body *= "\tadox\t\\sh, \\r$k\n"
    end
    body *= "\tadcx\t\\zr, \\cy\n"
    body *= "\tadox\t\\zr, \\cy\n"
    body *= "\n"

    body *= "\tjnz\t.Ltr_init\n"
    body *= "\n"

    return pre * body * post
end

# Products we calculate, where h stands for upper result only:
#          b_{0}   b_{1}  ...  b_{n-3} b_{n-2} b_{n-1}
#  a_{0}                  ...             h       x
#  a_{1}                  ...     h       x       x
#  a_{2}                  ...     x       x       x
#  ...
#  ...
# a_{n-3}            h    ...     x       x       x
# a_{n-2}    h       x    ...     x       x       x
# a_{n-1}    x       x    ...     x       x       x
#
# Herein we assume that n > k + unroll.
function mulhigh_basecase2(k::Int, unroll::Int = 0, debug::Bool = false)
    if !(2 <= k <= 6)
        error()
    end

    # TODO: Check if we want to push res into stack? We only need it once after
    # every triangle and parallelogram.
    res = _regs[1]
    ap = _regs[2]
    bp_old = _regs[3] # rdx
    n = _regs[4]
    bp = _regs[5] # rdx is used by mulx

    ap_save = "-1*8(%rsp)\n"
    bp_save = "-2*8(%rsp)\n"
    n_save = "-1*8(%rsp)\n"

    w0, w1, w2, w3 = 0, 1, 2, 3
    sl = _regs[6] # scrap register
    sh = "error sh" # scrap register
    zr = _regs[7] # zero
    cy = _regs[8] # carry for next chain
    ret = _regs[9] # return value, i.e the lowest limb

    _r = __regs[1:6]
    # r(ix::Int) = _r[ix + 1]
    r = _r

    # Push
    body = ""
    for reg in __regs
        body *= "\tpush\t$reg\n"
    end
    body *= "\n"

    # Prepare
    # body *= "\tmov\t$ap, $ap_save\n"
    # body *= "\tmov\t$bp_old, $bp_save\n"
    # body *= "\tmov\t$n, $n_save\n"

    body *= "\tmov\t$bp_old, $bp\n"
    body *= "\tmov\t0*8($bp_old), %rdx\n"

    body *= "\tlea\t-$(k + 1)*8($ap,$n,8), $ap\n" # ap <- ap + n - k - 1
    body *= "\tlea\t$(k + 0)*8($bp), $bp\n" # bp <- bp + k
    body *= "\tlea\t-$(k + 1)($n), $n\n"

    body *= "\txor\t$(R32(zr)), $(R32(zr))\n"
    body *= "\n"

    # Initial triangle
    # FIXME: ap_os and bp_os
    body *= "\ttr_init_$k\t$ap, $ap_os, $bp, $bp_os, $ret, "
    for ix in 1:k - 1
        body *= "$(r[ix]), "
    end
    body *= "$sc, $zr"

    # Crooked rectangle
    # k + 1 multiplications
    body *= "\txor\t$(R32(cy)), $(R32(cy))\n"
    body *= ".L1:\n"
    body *= "\tmov\t0*8($bp), %rdx\n"
    body *= "\tmulx\t-1*8($ap), $sc, $(r(k))\n"
    body *= "\tadox\t$(r(k)), $ret\n"
    body *= "\tmulx\t0*8($ap), $sc, $(r(k))\n"
    body *= "\tadcx\t$sc, $ret\n"
    body *= "\tadcx\t$(r(k)), $(r(0))\n"
    for ix in 1:k - 2
        body *= "\tmulx\t$ix*8($ap), $sc, $(r(k))\n"
        if ix % 2 == 0
            body *= "\tadcx\t$sc, $(r(ix - 1))\n"
            body *= "\tadcx\t$(r(k)), $(r(ix))\n"
        else
            body *= "\tadox\t$sc, $(r(ix - 1))\n"
            body *= "\tadox\t$(r(k)), $(r(ix))\n"
        end
    end
    body *= "\tmulx\t$(k - 1)*8($ap), $sc, $(r(k))\n"
    if (k - 1) % 2 == 0
        body *= "\tadcx\t$sc, $(r(k - 2))\n"
        body *= "\tadcx\t$(r(k)), $(r(k - 1))\n"
    else
        body *= "\tadox\t$sc, $(r(k - 2))\n"
        body *= "\tadox\t$(r(k)), $(r(k - 1))\n"
    end
    body *= "\tadcx\t$zr, $(r(k - 1))\n"
    body *= "\tadox\t$zr, $(r(k - 1))\n"
    body *= "\tadcx\t$zr, $(r(k))\n"
    body *= "\tadox\t$zr, $(r(k))\n"
    body *= "\tdec\t$n\n"
    body *= "\tlea\t-1*8($ap), $ap\n"
    body *= "\tlea\t1*8($bp), $bp\n"
    body *= "\tjnz\t.L1\n"

    body *= "\tmov\t0*8($bp), %rdx\n"
    body *= "\tmulx\t0*8($ap), $sc, $(r(k))\n"
    body *= "\tadcx\t$sc, $ret\n"
    body *= "\tadcx\t$(r(k)), $(r(0))\n"
    for ix in 1:k - 1
        body *= "\tmulx\t$ix*8($ap), $sc, $(r(k))\n"
        if ix % 2 == 0
            body *= "\tadcx\t$sc, $(r(ix - 1))\n"
            body *= "\tadcx\t$(r(k)), $(r(ix))\n"
        else
            body *= "\tadox\t$sc, $(r(ix - 1))\n"
            body *= "\tadox\t$(r(k)), $(r(ix))\n"
        end
    end
    # body *= "\tmulx\t$(k - 1)*8($ap), $sc, $(r(k))\n"
    # if (k - 1) % 2 == 0
    #     body *= "\tadcx\t$sc, $(r(k - 2))\n"
    #     body *= "\tadcx\t$(r(k)), $(r(k - 1))\n"
    # else
    #     body *= "\tadox\t$sc, $(r(k - 2))\n"
    #     body *= "\tadox\t$(r(k)), $(r(k - 1))\n"
    # end
    # body *= "\tadcx\t$zr, $(r(k - 1))\n"
    # body *= "\tadox\t$zr, $(r(k - 1))\n"
    body *= "\tadcx\t$zr, $(r(k))\n"
    body *= "\tadox\t$zr, $(r(k))\n"

    for ix in 0:k - 1
        body *= "\tmov\t$(r(ix)), $ix*8($res)\n"
    end
    body *= "\n"

    # Pop
    for reg in reverse(__regs)
        body *= "\tpop\t$reg\n"
    end
    body *= "\n"

    body *= "\tret\n"
    return body
end

# IDEA: Compute initial triangle, so that 
function mulhigh_basecase()
    res = _regs[1]
    ap = _regs[2]
    bp_old = _regs[3] # rdx
    n = _regs[4]
    bp = _regs[5] # rdx is used by mulx

    ap_save = "-1*8(%rsp)\n"
    bp_save = "-2*8(%rsp)\n"
    n_save = "-1*8(%rsp)\n"

    w0, w1, w2, w3 = 0, 1, 2, 3
    sl = _regs[6] # scrap register
    sh = "error sh" # scrap register
    zr = _regs[7] # zero
    cy = _regs[8] # carry for next chain
    ret = _regs[9] # return value, i.e the lowest limb

    _r = __regs[1:6]
    # r(ix::Int) = _r[ix + 1]
    r = _r

    # Push
    body = ""
    for reg in __regs
        body *= "\tpush\t$reg\n"
    end
    body *= "\n"

    # Prepare
    # body *= "\tmov\t$ap, $ap_save\n"
    # body *= "\tmov\t$bp_old, $bp_save\n"
    # body *= "\tmov\t$n, $n_save\n"

    body *= "\tmov\t$bp_old, $bp\n"
    body *= "\tmov\t0*8($bp_old), %rdx\n"

    body *= "\tlea\t-$(k + 1)*8($ap,$n,8), $ap\n" # ap <- ap + n - k - 1
    body *= "\tlea\t$(k + 0)*8($bp), $bp\n" # bp <- bp + k
    body *= "\tlea\t-$(k + 1)($n), $n\n"

    body *= "\txor\t$(R32(zr)), $(R32(zr))\n"
    body *= "\n"

    # Initial triangle
    # FIXME: ap_os and bp_os
    body *= "\ttr_init_$k\t$ap, $ap_os, $bp, $bp_os, $ret, "
    for ix in 1:k - 1
        body *= "$(r[ix]), "
    end
    body *= "$sc, $zr"

    # Crooked rectangle
    # k + 1 multiplications
    body *= "\txor\t$(R32(cy)), $(R32(cy))\n"
    body *= ".L1:\n"
    body *= "\tmov\t0*8($bp), %rdx\n"
    body *= "\tmulx\t-1*8($ap), $sc, $(r(k))\n"
    body *= "\tadox\t$(r(k)), $ret\n"
    body *= "\tmulx\t0*8($ap), $sc, $(r(k))\n"
    body *= "\tadcx\t$sc, $ret\n"
    body *= "\tadcx\t$(r(k)), $(r(0))\n"
    for ix in 1:k - 2
        body *= "\tmulx\t$ix*8($ap), $sc, $(r(k))\n"
        if ix % 2 == 0
            body *= "\tadcx\t$sc, $(r(ix - 1))\n"
            body *= "\tadcx\t$(r(k)), $(r(ix))\n"
        else
            body *= "\tadox\t$sc, $(r(ix - 1))\n"
            body *= "\tadox\t$(r(k)), $(r(ix))\n"
        end
    end
    body *= "\tmulx\t$(k - 1)*8($ap), $sc, $(r(k))\n"
    if (k - 1) % 2 == 0
        body *= "\tadcx\t$sc, $(r(k - 2))\n"
        body *= "\tadcx\t$(r(k)), $(r(k - 1))\n"
    else
        body *= "\tadox\t$sc, $(r(k - 2))\n"
        body *= "\tadox\t$(r(k)), $(r(k - 1))\n"
    end
    body *= "\tadcx\t$zr, $(r(k - 1))\n"
    body *= "\tadox\t$zr, $(r(k - 1))\n"
    body *= "\tadcx\t$zr, $(r(k))\n"
    body *= "\tadox\t$zr, $(r(k))\n"
    body *= "\tdec\t$n\n"
    body *= "\tlea\t-1*8($ap), $ap\n"
    body *= "\tlea\t1*8($bp), $bp\n"
    body *= "\tjnz\t.L1\n"

    body *= "\tmov\t0*8($bp), %rdx\n"
    body *= "\tmulx\t0*8($ap), $sc, $(r(k))\n"
    body *= "\tadcx\t$sc, $ret\n"
    body *= "\tadcx\t$(r(k)), $(r(0))\n"
    for ix in 1:k - 1
        body *= "\tmulx\t$ix*8($ap), $sc, $(r(k))\n"
        if ix % 2 == 0
            body *= "\tadcx\t$sc, $(r(ix - 1))\n"
            body *= "\tadcx\t$(r(k)), $(r(ix))\n"
        else
            body *= "\tadox\t$sc, $(r(ix - 1))\n"
            body *= "\tadox\t$(r(k)), $(r(ix))\n"
        end
    end
    # body *= "\tmulx\t$(k - 1)*8($ap), $sc, $(r(k))\n"
    # if (k - 1) % 2 == 0
    #     body *= "\tadcx\t$sc, $(r(k - 2))\n"
    #     body *= "\tadcx\t$(r(k)), $(r(k - 1))\n"
    # else
    #     body *= "\tadox\t$sc, $(r(k - 2))\n"
    #     body *= "\tadox\t$(r(k)), $(r(k - 1))\n"
    # end
    # body *= "\tadcx\t$zr, $(r(k - 1))\n"
    # body *= "\tadox\t$zr, $(r(k - 1))\n"
    body *= "\tadcx\t$zr, $(r(k))\n"
    body *= "\tadox\t$zr, $(r(k))\n"

    for ix in 0:k - 1
        body *= "\tmov\t$(r(ix)), $ix*8($res)\n"
    end
    body *= "\n"

    # Pop
    for reg in reverse(__regs)
        body *= "\tpop\t$reg\n"
    end
    body *= "\n"

    body *= "\tret\n"
    return body
end
###############################################################################
# mulhigh, normalised
###############################################################################

function mulhigh_normalised_1()
    r0 = _regs[9] # Important that r0 is rax
    r1 = _regs[4]

    res = _regs[1]
    ap = _regs[2]
    bp = _regs[3]

    body = ""

    body *= "\tmov\t0*8($bp), %rdx\n"
    body *= "\tmulx\t0*8($ap), $r0, $r1\n"

    # Check if normalised
    body *= "\tmov\t\$0, %rdx\n"
    body *= "\ttest\t$r1, $r1\n"
    body *= "\tsetns\t$(R8("%rdx"))\n"
    body *= "\tjs\t.Lcontinue\n"

    # If not normalised, shift by one
    body *= "\tadd\t$r0, $r0\n"
    body *= "\tadc\t$r1, $r1\n"

    body *= ".Lcontinue:\n"
    body *= "\tmov\t$r1, 0*8($res)\n"

    return body * "\n\tret\n"
end

function mulhigh_normalised_2()
    r0 = _regs[9]
    r1 = _regs[4]
    r2 = _regs[5]

    sc = _regs[6]
    zr = _regs[7]

    res = _regs[1]
    ap = _regs[2]
    bp_old = _regs[3]
    b1 = _regs[8]

    body = ""

    body *= "\tmov\t1*8($bp_old), $b1\n"
    body *= "\tmov\t0*8($bp_old), %rdx\n"
    body *= "\txor\t$(R32(zr)), $(R32(zr))\n"
    body *= "\tmulx\t0*8($ap), $sc, $r0\n"
    body *= "\tmulx\t1*8($ap), $sc, $r1\n"
    body *= "\tadcx\t$sc, $r0\n"
    body *= "\tadcx\t$zr, $r1\n"

    body *= "\tmov\t$b1, %rdx\n"
    body *= "\tmulx\t0*8($ap), $sc, $r2\n"
    body *= "\tadcx\t$sc, $r0\n"
    body *= "\tadcx\t$r2, $r1\n"
    body *= "\tmulx\t1*8($ap), $sc, $r2\n"
    body *= "\tadox\t$sc, $r1\n"
    body *= "\tadox\t$zr, $r2\n"
    body *= "\tadcx\t$zr, $r2\n"

    # Check if normalised
    body *= "\tmov\t\$0, %rdx\n"
    body *= "\ttest\t$r2, $r2\n"
    body *= "\tsetns\t$(R8("%rdx"))\n"
    body *= "\tjs\t.Lcontinue\n"

    # If not normalised, shift by one
    body *= "\tadd\t$r0, $r0\n"
    body *= "\tadc\t$r1, $r1\n"
    body *= "\tadc\t$r2, $r2\n"

    body *= ".Lcontinue:\n"
    body *= "\tmov\t$r1, 0*8($res)\n"
    body *= "\tmov\t$r2, 1*8($res)\n"

    return body * "\n\tret\n"
end

function mulhigh_normalised(n::Int; debug::Bool = false)
    if n < 1
        error()
    elseif n == 1
        return mulhigh_normalised_1()
    elseif n == 2
        return mulhigh_normalised_2()
    elseif n <= 12
        # Continue
    else
        error()
    end

    if debug
        res = "res"
        ap = "ap"
        bp_old = "bp_old"
        bp = "bp"
        sc = "sc"
        zr = "zr"
    else
        res = _regs[1]
        ap = _regs[2]
        bp_old = _regs[3] # rdx
        bp = _regs[4] # rdx is used by mulx, so we need to switch register for bp

        if n != 12
            sc = _regs[5] # scrap register
            zr = (n < 10) ? _regs[6] : "%rsp" # zero
        else
            sc = "%rsp"
            zr = sc
        end

        if n < 9
            _r = [_regs[9]; _regs[7:8]; __regs[1:n - 2]]
        elseif n == 9
            _r = [_regs[9]; _regs[7:8]; __regs[1:6]; res]
        elseif n == 10
            _r = [_regs[9]; _regs[6:8]; __regs[1:6]; res]
        elseif n == 11
            _r = [_regs[9]; _regs[6:8]; __regs[1:6]; res; bp]
        elseif n == 12
            _r = [_regs[9]; _regs[5:8]; __regs[1:6]; res; bp]
        end
    end

    r(ix::Int) = debug ? "r$ix" : _r[ix + 1]

    # Push
    body = ""
    for ix in 1:min(n - 2, 6)
        body *= "\tpush\t$(__regs[ix])\n"
    end
    if n == 9
        body *= "\tpush\t$res\n"
    elseif n >= 10
        body *= "\tvmovq\t%rsp, %xmm0\n"
        body *= "\tvmovq\t$res, %xmm1\n"
    end
    body *= "\n"

    # Prepare
    body *= "\tmov\t$bp_old, $bp\n"
    body *= "\tmov\t0*8($bp_old), %rdx\n"
    if n != 12
        body *= "\txor\t$(R32(zr)), $(R32(zr))\n"
    end
    body *= "\n"

    # First multiplication chain
    body *= "\tmulx\t$(n - 2)*8($ap), $sc, $(r(0))\n"
    body *= "\tmulx\t$(n - 1)*8($ap), $sc, $(r(1))\n"
    if n != 12
        body *= "\tadcx\t$sc, $(r(0))\n"
        body *= "\tadcx\t$zr, $(r(1))\n"
    else
        body *= "\tadd\t$sc, $(r(0))\n"
        body *= "\tadc\t\$0, $(r(1))\n"
        body *= "\ttest\t%al, %al\n"
    end
    body *= "\n"

    # Intermediate multiplication chains
    for ix in 1:min(n - 2, (n != 12) ? 8 : 9)
        body *= "\tmov\t$ix*8($bp), %rdx\n"

        body *= "\tmulx\t$(n - 2 - ix)*8($ap), $sc, $(r(ix + 2))\n"
        body *= "\tmulx\t$(n - 1 - ix)*8($ap), $sc, $(r(ix + 1))\n"
        body *= "\tadcx\t$(r(ix + 2)), $(r(0))\n"
        body *= "\tadox\t$sc, $(r(0))\n"
        body *= "\tadcx\t$(r(ix + 1)), $(r(1))\n"

        for jx in 1:ix - 1
            body *= "\tmulx\t$(n - 1 - ix + jx)*8($ap), $sc, $(r(ix + 1))\n"
            body *= "\tadox\t$sc, $(r(jx + 0))\n"
            body *= "\tadcx\t$(r(ix + 1)), $(r(jx + 1))\n"
        end

        body *= "\tmulx\t$(n - 1)*8($ap), $sc, $(r(ix + 1))\n"
        body *= "\tadox\t$sc, $(r(ix + 0))\n"
        if n == 12
            body *= "\tmov\t\$0, $(R32(zr))\n"
        end
        body *= "\tadcx\t$zr, $(r(ix + 1))\n"
        body *= "\tadox\t$zr, $(r(ix + 1))\n"

        body *= "\n"
    end

    if n >= 11
        N = n - 1
        body *= "\tmov\t$(n - 2)*8($bp), %rdx\n"
        for ix in 0:n - 2
            body *= "\tmulx\t$ix*8($ap), $sc, $(r(N))\n"
            if ix == 0
                body *= "\tadcx\t$(r(N)), $(r(ix + 0))\n"
            else
                body *= "\tadox\t$sc, $(r(ix - 1))\n"
                body *= "\tadcx\t$(r(N)), $(r(ix + 0))\n"
            end
        end
        body *= "\tmulx\t$(n - 1)*8($ap), $sc, $(r(N))\n"
        body *= "\tadox\t$sc, $(r(N - 1))\n"
        if n == 12
            body *= "\tmov\t\$0, $(R32(zr))\n"
        end
        body *= "\tadcx\t$zr, $(r(N))\n"
        body *= "\tadox\t$zr, $(r(N))\n"
        body *= "\n"
    end

    # Last multiplication chain
    body *= "\tmov\t$(n - 1)*8($bp), %rdx\n"
    for ix in 0:n - 2
        body *= "\tmulx\t$ix*8($ap), $sc, $(r(n))\n"
        if ix % 2 == 0
            body *= "\tadcx\t$sc, $(r(ix + 0))\n"
            body *= "\tadcx\t$(r(n)), $(r(ix + 1))\n"
        else
            body *= "\tadox\t$sc, $(r(ix + 0))\n"
            body *= "\tadox\t$(r(n)), $(r(ix + 1))\n"
        end
    end
    body *= "\tmulx\t$(n - 1)*8($ap), $sc, $(r(n))\n"
    if (n - 1) % 2 == 0
        body *= "\tadcx\t$sc, $(r(n - 1))\n"
    else
        body *= "\tadox\t$sc, $(r(n - 1))\n"
    end
    if n == 12
        body *= "\tmov\t\$0, $(R32(zr))\n"
    end
    body *= "\tadcx\t$zr, $(r(n))\n"
    if n == 9
        # Use scrap register for storing pointer to res
        res = sc
        body *= "\tpop\t$res\n"
    end
    body *= "\tadox\t$zr, $(r(n))\n"
    body *= "\n"

    # Check if normalised
    body *= "\tmov\t\$0, %rdx\n"
    body *= "\ttest\t$(r(n)), $(r(n))\n"
    body *= "\tsetns\t$(R8("%rdx"))\n"
    body *= "\tjs\t.Lcontinue\n"

    # If not normalised, shift by one
    body *= "\tadd\t$(r(0)), $(r(0))\n"
    for ix in 1:n
        body *= "\tadc\t$(r(ix)), $(r(ix))\n"
    end

    body *= ".Lcontinue:\n"
    if n == 10 || n == 11
        res, zr = sc, "error zr"
        body *= "\tvmovq\t%xmm1, $res\n"
        body *= "\tvmovq\t%xmm0, %rsp\n"
    elseif n == 12
        res = sc
        body *= "\tvmovq\t%xmm1, $res\n"
    end

    # Store result
    for ix in 1:n
        body *= "\tmov\t$(r(ix)), $(ix - 1)*8($res)\n"
    end
    body *= "\n"

    # Pop
    if n == 12
        body *= "\tvmovq\t%xmm0, %rsp\n"
    end
    for ix in min(n - 2, 6):-1:1
        body *= "\tpop\t$(__regs[ix])\n"
    end
    body *= "\n"

    if debug
        print(body * "\tret\n")
    else
        return body * "\tret\n"
    end
end

###############################################################################
# Generate file
###############################################################################

function gen_mulhigh_basecase(nofile::Bool = false)
    (pre, post) = function_pre_post("flint_mpn_mulhigh_n_basecase")
    functionbody = mulhigh_basecase()

    str = "$copyright\n$preamble\n$pre$functionbody$post"

    if nofile
        print(str)
    else
        path = String(@__DIR__) * "/../src/mpn_extras/broadwell/mulhigh_n_basecase.asm"
        file = open(path, "w")
        write(file, str)
        close(file)
    end
end

function gen_mulhigh(m::Int, nofile::Bool = false)
    (pre, post) = function_pre_post("flint_mpn_mulhigh_$m")
    functionbody = mulhigh(m)

    str = "$copyright\n$preamble\n$pre$functionbody$post"

    if nofile
        print(str)
    else
        path = String(@__DIR__) * "/../src/mpn_extras/broadwell/mulhigh_$m.asm"
        file = open(path, "w")
        write(file, str)
        close(file)
    end
end

function gen_mulhigh_normalised(m::Int, nofile::Bool = false)
    (pre, post) = function_pre_post("flint_mpn_mulhigh_normalised_$m")
    functionbody = mulhigh_normalised(m)

    str = "$copyright\n$preamble\n$pre$functionbody$post"

    if nofile
        print(str)
    else
        path = String(@__DIR__) * "/../src/mpn_extras/broadwell/mulhigh_normalised_$m.asm"
        file = open(path, "w")
        write(file, str)
        close(file)
    end
end

function gen_all()
    gen_mulhigh_basecase()
    for m in 1:12
        gen_mulhigh(m)
    end
    for m in 1:12
        gen_mulhigh_normalised(m)
    end
end
