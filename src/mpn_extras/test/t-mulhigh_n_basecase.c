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

#if FLINT_HAVE_MPN_MULHIGH_N_BASECASE

#define N_MIN 7
#define N_MAX 7
/* #define N_MAX 12 */

TEST_FUNCTION_START(flint_mpn_mulhigh_n_basecase, state)
{
    slong ix;
    int result;

    for (ix = 0; ix < 100000 * flint_test_multiplier(); ix++)
    {
        mp_limb_t rp1[N_MAX + 1];
        mp_limb_t rp2[N_MAX + 1];
        mp_limb_t xp[N_MAX + 10];
        mp_limb_t yp[N_MAX + 10];
        mp_size_t n;

        n = N_MIN + n_randint(state, N_MAX - N_MIN + 1);

        mpn_random2(xp, N_MAX + 10);
        mpn_random2(yp, N_MAX + 10);

        rp1[0] = flint_mpn_mulhigh_n(rp1 + 1, xp, yp, n);
        rp2[0] = flint_mpn_mulhigh_n_basecase(rp2 + 1, xp, yp, n);

        result = (rp1[0] == rp2[0]);
        if (!result)
            TEST_FUNCTION_FAIL(
                    "Return values are not the same\n"
                    "ix = %wd\n"
                    "n = %wd\n"
                    "xp = %{ulong*}\n"
                    "yp = %{ulong*}\n"
                    "Expected: %{ulong*}\n"
                    "Got:      %{ulong*}\n",
                    ix, n, xp, n, yp, n, rp1, n + 1, rp2, n + 1);

        result = (mpn_cmp(rp1, rp2, n + 1) == 0);
        if (!result)
            TEST_FUNCTION_FAIL(
                    "Result not the same\n"
                    "ix = %wd\n"
                    "n = %wd\n"
                    "xp = %{ulong*}\n"
                    "yp = %{ulong*}\n"
                    "Expected: %{ulong*}\n"
                    "Got:      %{ulong*}\n",
                    ix, n, xp, n, yp, n, rp1, n + 1, rp2, n + 1);
    }

    TEST_FUNCTION_END(state);
}
# undef N_MIN
# undef N_MAX
#else
TEST_FUNCTION_START(flint_mpn_mulhigh_n, state)
{
    TEST_FUNCTION_END_SKIPPED(state);
}
#endif
