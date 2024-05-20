/*
    Copyright (C) 2024 Albin Ahlbäck

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "fmpz_mod.h"
#include "fmpz_mod_mat.h"

int fmpz_mod_mat_is_canonical(const fmpz_mod_mat_t am, const fmpz_mod_ctx_t ctx)
{
    slong ix, jx;

    for (ix = 0; ix < fmpz_mod_mat_nrows(am, ctx); ix++)
        for (jx = 0; jx < fmpz_mod_mat_ncols(am, ctx); jx++)
            if (!fmpz_mod_is_canonical(fmpz_mod_mat_entry(am, ix, jx), ctx))
                return 0;

    return 1;
}
