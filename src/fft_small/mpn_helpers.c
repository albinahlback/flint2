/*
    Copyright (C) 2022 Daniel Schultz

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "fft_small.h"
#include "crt_helpers.h"

#if defined(__AVX512F__)
# define VEC_SIZE 8
# define UNROLL 8

# if BLK_SZ % (VEC_SIZE * UNROLL) != 0
#  error
# endif
void _convert_block(
        ulong * xp,
        sd_fft_ctx_struct * Rffts,
        double * dp,
        ulong dstride,
        ulong np,
        ulong idx)
{
    if (np <= 0)
        FLINT_UNREACHABLE;

    for (ulong lx = 0; lx < np; lx++)
    {
        vec8d p, pinv;
        double * xd;
        ulong jx;

        p = vec8d_set_d(Rffts[lx].p);
        pinv = vec8d_set_d(Rffts[lx].pinv);

        xd = sd_fft_ctx_blk_index(dp + lx * dstride, idx);

        for (jx = 0; jx < BLK_SZ; jx += UNROLL * VEC_SIZE)
        {
            vec8d x0, x1, x2, x3, x4, x5, x6, x7;
            vec8d t0, t1, t2, t3, t4, t5, t6, t7;
            vec8n y0, y1, y2, y3, y4, y5, y6, y7;

            x0 = vec8d_load_aligned(xd + jx + 0 * VEC_SIZE);
            x1 = vec8d_load_aligned(xd + jx + 1 * VEC_SIZE);
            x2 = vec8d_load_aligned(xd + jx + 2 * VEC_SIZE);
            x3 = vec8d_load_aligned(xd + jx + 3 * VEC_SIZE);
            x4 = vec8d_load_aligned(xd + jx + 4 * VEC_SIZE);
            x5 = vec8d_load_aligned(xd + jx + 5 * VEC_SIZE);
            x6 = vec8d_load_aligned(xd + jx + 6 * VEC_SIZE);
            x7 = vec8d_load_aligned(xd + jx + 7 * VEC_SIZE);

            /* Reduce x_{i} mod p in (-p, p) */
            t0 = vec8d_mul(x0, pinv);
            t1 = vec8d_mul(x1, pinv);
            t2 = vec8d_mul(x2, pinv);
            t3 = vec8d_mul(x3, pinv);
            t4 = vec8d_mul(x4, pinv);
            t5 = vec8d_mul(x5, pinv);
            t6 = vec8d_mul(x6, pinv);
            t7 = vec8d_mul(x7, pinv);

            t0 = vec8d_round(t0);
            t1 = vec8d_round(t1);
            t2 = vec8d_round(t2);
            t3 = vec8d_round(t3);
            t4 = vec8d_round(t4);
            t5 = vec8d_round(t5);
            t6 = vec8d_round(t6);
            t7 = vec8d_round(t7);

            x0 = vec8d_fnmadd(t0, p, x0);
            x1 = vec8d_fnmadd(t1, p, x1);
            x2 = vec8d_fnmadd(t2, p, x2);
            x3 = vec8d_fnmadd(t3, p, x3);
            x4 = vec8d_fnmadd(t4, p, x4);
            x5 = vec8d_fnmadd(t5, p, x5);
            x6 = vec8d_fnmadd(t6, p, x6);
            x7 = vec8d_fnmadd(t7, p, x7);

            /* FIXME: This is wrong */
            /* x_{i} -> |x_{i}|, so x_{i} in [0, p) */
            x0 = vec8d_abs(x0);
            x1 = vec8d_abs(x1);
            x2 = vec8d_abs(x2);
            x3 = vec8d_abs(x3);
            x4 = vec8d_abs(x4);
            x5 = vec8d_abs(x5);
            x6 = vec8d_abs(x6);
            x7 = vec8d_abs(x7);

            /* Convert from double to integer */
            y0 = vec8d_convert_limited_vec8n(x0);
            y1 = vec8d_convert_limited_vec8n(x1);
            y2 = vec8d_convert_limited_vec8n(x2);
            y3 = vec8d_convert_limited_vec8n(x3);
            y4 = vec8d_convert_limited_vec8n(x4);
            y5 = vec8d_convert_limited_vec8n(x5);
            y6 = vec8d_convert_limited_vec8n(x6);
            y7 = vec8d_convert_limited_vec8n(x7);

            vec8n_store_unaligned(xp + lx * BLK_SZ + jx + 0 * VEC_SIZE, y0);
            vec8n_store_unaligned(xp + lx * BLK_SZ + jx + 1 * VEC_SIZE, y1);
            vec8n_store_unaligned(xp + lx * BLK_SZ + jx + 2 * VEC_SIZE, y2);
            vec8n_store_unaligned(xp + lx * BLK_SZ + jx + 3 * VEC_SIZE, y3);
            vec8n_store_unaligned(xp + lx * BLK_SZ + jx + 4 * VEC_SIZE, y4);
            vec8n_store_unaligned(xp + lx * BLK_SZ + jx + 5 * VEC_SIZE, y5);
            vec8n_store_unaligned(xp + lx * BLK_SZ + jx + 6 * VEC_SIZE, y6);
            vec8n_store_unaligned(xp + lx * BLK_SZ + jx + 7 * VEC_SIZE, y7);
        }
    }
}
# undef VEC_SIZE
# undef UNROLL
#else
/* transpose a block */
void _convert_block(
    ulong* Xs,
    sd_fft_ctx_struct* Rffts, double* d, ulong dstride,
    ulong np,
    ulong I)
{
    for (ulong l = 0; l < np; l++)
    {
        vec4d p = vec4d_set_d(Rffts[l].p);
        vec4d pinv = vec4d_set_d(Rffts[l].pinv);
        double* x = sd_fft_ctx_blk_index(d + l*dstride, I);
        ulong j = 0; do {
            vec4d x0, x1, x2, x3;
            vec4n y0, y1, y2, y3;
            x0 = vec4d_load(x + j + 0*VEC_SZ);
            x1 = vec4d_load(x + j + 1*VEC_SZ);
            x2 = vec4d_load(x + j + 2*VEC_SZ);
            x3 = vec4d_load(x + j + 3*VEC_SZ);
            x0 = vec4d_reduce_to_0n(x0, p, pinv);
            x1 = vec4d_reduce_to_0n(x1, p, pinv);
            x2 = vec4d_reduce_to_0n(x2, p, pinv);
            x3 = vec4d_reduce_to_0n(x3, p, pinv);
            y0 = vec4d_convert_limited_vec4n(x0);
            y1 = vec4d_convert_limited_vec4n(x1);
            y2 = vec4d_convert_limited_vec4n(x2);
            y3 = vec4d_convert_limited_vec4n(x3);
            vec4n_store_unaligned(Xs + l*BLK_SZ + j + 0*VEC_SZ, y0);
            vec4n_store_unaligned(Xs + l*BLK_SZ + j + 1*VEC_SZ, y1);
            vec4n_store_unaligned(Xs + l*BLK_SZ + j + 2*VEC_SZ, y2);
            vec4n_store_unaligned(Xs + l*BLK_SZ + j + 3*VEC_SZ, y3);
        } while (j += 4*VEC_SZ, j < BLK_SZ);
        FLINT_ASSERT(j == BLK_SZ);
    }
}
#endif

ulong flint_mpn_nbits(const ulong* a, ulong an)
{
    while (an > 0 && a[an-1] == 0)
        an--;

    if (an == 0)
        return 0;

    return FLINT_BITS*(an - 1) + n_nbits(a[an-1]);
}

/* cmp(a, b*2^e), a does not have to be normalized */
int flint_mpn_cmp_ui_2exp(const ulong* a, ulong an, ulong b, ulong e)
{
    ulong q = e/FLINT_BITS;
    ulong r = e%FLINT_BITS;
    ulong x, b0, b1;

    while (an > 0 && a[an-1] == 0)
        an--;

    if (an == 0)
        return b != 0;

    // b*2^e = (b*2^r       )*2^(64*q)
    //       = (b0 + b1*2^64)*2^(64*q)
    if (r == 0)
    {
        b0 = b;
        b1 = 0;
    }
    else
    {
        b0 = b << r;
        b1 = b >> (FLINT_BITS - r);
    }

    //      check words [q+2,infty)
    // then check words [q+1, 64*q+128) against b1
    // then check words [q, q+1) against b0
    // then check words [0, q)

    if (an > q + 2)
        return 1;

    x = (q+1 < an) ? a[q+1] : 0;
    if (x != b1)
        return x > b1 ? 1 : -1;

    x = (q < an) ? a[q] : 0;
    if (x != b0)
        return x > b0 ? 1 : -1;

    q = n_min(q, an);
    while (q > 0)
    {
        q--;
        if (a[q] != 0)
            return 1;
    }

    return 0;
}
