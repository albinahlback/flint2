/*
    Copyright (C) 2024 Albin Ahlbäck

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include <string.h>
#include "mpn_extras.h"
#include "gr.h"

#ifdef FLINT_HAVE_FFT_SMALL
# include "fft_small.h"
# define FFT_MUL mpn_mul_default_mpn_ctx
#else
# include "fft.h"
# define FFT_MUL flint_mpn_mul_fft_main
#endif

#if FLINT_HAVE_ADX
mp_limb_t flint_mpn_mulhigh_1(mp_ptr, mp_srcptr, mp_srcptr);
mp_limb_t flint_mpn_mulhigh_2(mp_ptr, mp_srcptr, mp_srcptr);
mp_limb_t flint_mpn_mulhigh_3(mp_ptr, mp_srcptr, mp_srcptr);
mp_limb_t flint_mpn_mulhigh_4(mp_ptr, mp_srcptr, mp_srcptr);
mp_limb_t flint_mpn_mulhigh_5(mp_ptr, mp_srcptr, mp_srcptr);
mp_limb_t flint_mpn_mulhigh_6(mp_ptr, mp_srcptr, mp_srcptr);
mp_limb_t flint_mpn_mulhigh_7(mp_ptr, mp_srcptr, mp_srcptr);
mp_limb_t flint_mpn_mulhigh_8(mp_ptr, mp_srcptr, mp_srcptr);
mp_limb_t flint_mpn_mulhigh_9(mp_ptr, mp_srcptr, mp_srcptr);
mp_limb_t flint_mpn_mulhigh_10(mp_ptr, mp_srcptr, mp_srcptr);
mp_limb_t flint_mpn_mulhigh_11(mp_ptr, mp_srcptr, mp_srcptr);
mp_limb_t flint_mpn_mulhigh_12(mp_ptr, mp_srcptr, mp_srcptr);

struct mp_limb_pair_t flint_mpn_mulhigh_normalised_1(mp_ptr, mp_srcptr, mp_srcptr);
struct mp_limb_pair_t flint_mpn_mulhigh_normalised_2(mp_ptr, mp_srcptr, mp_srcptr);
struct mp_limb_pair_t flint_mpn_mulhigh_normalised_3(mp_ptr, mp_srcptr, mp_srcptr);
struct mp_limb_pair_t flint_mpn_mulhigh_normalised_4(mp_ptr, mp_srcptr, mp_srcptr);
struct mp_limb_pair_t flint_mpn_mulhigh_normalised_5(mp_ptr, mp_srcptr, mp_srcptr);
struct mp_limb_pair_t flint_mpn_mulhigh_normalised_6(mp_ptr, mp_srcptr, mp_srcptr);
struct mp_limb_pair_t flint_mpn_mulhigh_normalised_7(mp_ptr, mp_srcptr, mp_srcptr);
struct mp_limb_pair_t flint_mpn_mulhigh_normalised_8(mp_ptr, mp_srcptr, mp_srcptr);
struct mp_limb_pair_t flint_mpn_mulhigh_normalised_9(mp_ptr, mp_srcptr, mp_srcptr);
struct mp_limb_pair_t flint_mpn_mulhigh_normalised_10(mp_ptr, mp_srcptr, mp_srcptr);
struct mp_limb_pair_t flint_mpn_mulhigh_normalised_11(mp_ptr, mp_srcptr, mp_srcptr);
struct mp_limb_pair_t flint_mpn_mulhigh_normalised_12(mp_ptr, mp_srcptr, mp_srcptr);

const flint_mpn_mul_func_t flint_mpn_mulhigh_n_func_tab[] =
{
    flint_mpn_mulhigh_1,
    flint_mpn_mulhigh_2,
    flint_mpn_mulhigh_3,
    flint_mpn_mulhigh_4,
    flint_mpn_mulhigh_5,
    flint_mpn_mulhigh_6,
    flint_mpn_mulhigh_7,
    flint_mpn_mulhigh_8,
    flint_mpn_mulhigh_9,
    flint_mpn_mulhigh_10,
    flint_mpn_mulhigh_11,
    flint_mpn_mulhigh_12
};

const flint_mpn_mulhigh_normalised_func_t flint_mpn_mulhigh_normalised_n_func_tab[] =
{
    flint_mpn_mulhigh_normalised_1,
    flint_mpn_mulhigh_normalised_2,
    flint_mpn_mulhigh_normalised_3,
    flint_mpn_mulhigh_normalised_4,
    flint_mpn_mulhigh_normalised_5,
    flint_mpn_mulhigh_normalised_6,
    flint_mpn_mulhigh_normalised_7,
    flint_mpn_mulhigh_normalised_8,
    flint_mpn_mulhigh_normalised_9,
    flint_mpn_mulhigh_normalised_10,
    flint_mpn_mulhigh_normalised_11,
    flint_mpn_mulhigh_normalised_12
};
#endif

#define CUTOFF 48

struct mp_limb_pair_t
_flint_mpn_mulhigh_normalised_n(mp_ptr rp, mp_srcptr xp, mp_srcptr yp, mp_size_t n)
{
    struct mp_limb_pair_t res;
    mp_ptr rp_tmp;

    if (n <= 2)
        FLINT_UNREACHABLE;

    rp_tmp = GR_TMP_ALLOC(2 * sizeof(mp_limb_t) * n);

#if !FLINT_HAVE_MPN_MULHIGH_NORMALISED_N_BASECASE
    if (n < CUTOFF)
    {
        slong ix;
        for (ix = 0; ix < n; ix++)
            rp_tmp[n + ix] = mpn_addmul_1(rp_tmp + n - 2,
                    xp + n - 2 - ix, ix + 2, yp[ix]);

        goto cont;
    }
#endif

    if (n < FLINT_FFT_MUL_THRESHOLD)
        mpn_mul_n(rp_tmp, xp, yp, n);
    else
        FFT_MUL(rp_tmp, xp, n, yp, n);

cont:

    if (rp_tmp[2 * n - 1] & (UWORD(1) << (FLINT_BITS - 1)))
    {
        /* No normalisation needed */
        memcpy(rp, rp_tmp + n, sizeof(mp_limb_t) * n);
        res.m1 = rp_tmp[n - 1];
        res.m2 = 0;
    }
    else
    {
        /* Normalisation needed */
        mpn_lshift(rp, rp_tmp + n, n, 1);
        res.m1 = rp_tmp[n - 1] << 1;
        res.m2 = 1;
    }

    GR_TMP_FREE(rp_tmp, 2 * sizeof(mp_limb_t) * n);

    return res;
}
