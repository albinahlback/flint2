/*
    Copyright (C) 2024 Albin Ahlbäck

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "mpn_extras.h"
#include "profiler.h"

#define N_MIN 1
#define N_MAX FLINT_MPN_INVERT_FUNC_TAB_WIDTH

int main(void)
{
    mp_limb_t ip[N_MAX], dp[N_MAX], scratch[2 * N_MAX];
    mp_size_t n;

    flint_printf("2 mpn_add_n / flint_mpn_2add_n_inplace\n");
    for (n = N_MIN; n <= N_MAX; n++)
    {
        double t1, t2, FLINT_SET_BUT_UNUSED(__);

        flint_printf("n = %2wd:", n);

        mpn_random2(dp, n);
        dp[n - 1] |= (UWORD(1) << (FLINT_BITS - 1));

        TIMEIT_START
        flint_mpn_invert(ip, dp, n);
        TIMEIT_STOP_VALUES(__, t1)

        TIMEIT_START
        *ip = mpn_invert_limb(*dp);
        TIMEIT_STOP_VALUES(__, t2)

        flint_printf("%7.2fx\n", t2 / t1);
    }

    flint_cleanup_master();

    return 0;
}

#undef N_MIN
#undef N_MAX
