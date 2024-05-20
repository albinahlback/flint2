/*
    Copyright (C) 2024 Albin Ahlbäck

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "test_helpers/mat.h"
#include "fmpz_mod.h"
#include "fmpz_mod_mat.h"

MAT_AORS_TEST_CTX(
        fmpz_mod_mat_aors,
        state,
        fmpz_mod,
        fmpz_mod_ctx_init_rand_bits(ctx, state, 150))
