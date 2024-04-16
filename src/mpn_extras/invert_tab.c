/*
    Copyright (C) 2024 Albin Ahlbäck

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "mpn_extras.h"

#if FLINT_HAVE_ASSEMBLY_x86_64_adx
void flint_mpn_invert_1(mp_ptr, mp_srcptr);

const flint_mpn_invert_func_t flint_mpn_invert_func_tab[] =
{
    NULL,
    flint_mpn_invert_1,
};
#else
void flint_mpn_invert_1(mp_ptr ip, mp_srcptr dp)
{
# if FLINT_HAVE_NATIVE_mpn_invert_limb
    ip[0] = mpn_invert_limb(dp[0]);
# else
    ip[0] = n_preinvert_limb_prenorm(dp[0]);
# endif
}

const flint_mpn_invert_func_t flint_mpn_invert_func_tab[] =
{
    NULL,
    flint_mpn_invert_1,
};
#endif
