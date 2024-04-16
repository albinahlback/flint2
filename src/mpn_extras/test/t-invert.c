/*
    Copyright (C) 2024 Albin Ahlbäck

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "test_helpers.h"
#include "mpn_extras.h"

#define N_MIN 1
#define N_MAX 50

TEST_FUNCTION_START(flint_mpn_invert, state)
{
    slong ix;
    int result;
    mp_ptr scratch = flint_malloc(sizeof(mp_limb_t) * N_MAX);

    for (ix = 0; ix < 100000 * flint_test_multiplier(); ix++)
    {
        mp_ptr ip0, ip1, dp;
        mp_size_t n;

        n = N_MIN + n_randint(state, N_MAX - N_MIN + 1);

        ip0 = flint_malloc(sizeof(mp_limb_t) * n);
        ip1 = flint_malloc(sizeof(mp_limb_t) * n);
        dp = flint_malloc(sizeof(mp_limb_t) * n);

        mpn_random2(dp, n);
        dp[n - 1] |= (UWORD(1) << (FLINT_BITS - 1));

        flint_mpn_invert(ip0, dp, n);
        mpn_invert(ip1, dp, n, scratch);

        result = (mpn_cmp(ip0, ip1, n) == 0);
        if (!result)
            TEST_FUNCTION_FAIL(
                    "ix = %wd\n"
                    "n = %wd\n"
                    "dp = %{ulong*}\n"
                    "Expected: %{ulong*}\n"
                    "Got:      %{ulong*}\n",
                    ix, n, dp, n, ip1, n, ip0, n);

        flint_free(ip0);
        flint_free(ip1);
        flint_free(dp);
    }

    flint_free(scratch);

    TEST_FUNCTION_END(state);
}

#undef N_MIN
#undef N_MAX
