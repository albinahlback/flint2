/*
    Copyright (C) 2024 Albin Ahlbäck

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "mpn_extras.h"
#include "gr.h"

void _flint_mpn_invert(mp_ptr ip, mp_srcptr dp, mp_size_t n)
{
    mp_ptr scratch = GR_TMP_ALLOC(2 * sizeof(mp_limb_t) * n);
    FLINT_ASSERT(ip != dp);
    FLINT_ASSERT(dp[n - 1] >> (FLINT_BITS - 1));
    
    mpn_invert(ip, dp, n, scratch);

    GR_TMP_FREE(scratch, 2 * sizeof(mp_limb_t) * n);
}
