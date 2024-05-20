/*
    Copyright (C) 2024 Albin Ahlbäck

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#ifndef TEST_MAT_H
#define TEST_MAT_H

#include "test_helpers.h"

/*
   _MAT_AORS_TEST_CTX

   Tests addition, subtraction and negation coherently.

   Assumptions:
    * Assumes that the operations tested are boiler-plate, that is, they are a
      simple double for-loop with operations over base ring.
    * Ring has a context-structure.
    * Add, sub and neg on matrices are not null-operations.
*/
#define _MAT_AORS_TEST_CTX(                                             \
            name,                                                       \
            state,                                                      \
            coeff,                                                      \
            M_MIN, M_MAX,                                               \
            N_MIN, N_MAX,                                               \
            T_ctx_t,                                                    \
            T_ctx_init_rand, /* Must be an expression containing `ctx' */ \
            T_ctx_clear,                                                \
            T,                                                          \
            T_init,                                                     \
            T_randtest,                                                 \
            T_add, T_sub, T_neg,                                        \
            T_is_zero, T_equal,                                         \
            T_is_canonical,                                             \
            T_clear                                                     \
        )                                                               \
TEST_FUNCTION_START(name, state)                                        \
{                                                                       \
    slong ix;                                                           \
    int result;                                                         \
                                                                        \
    for (ix = 0; ix < coeff * flint_test_multiplier(); ix++)            \
    {                                                                   \
        slong m, n;                                                     \
        T am, bm, cm;                                                   \
        T_ctx_t ctx;                                                    \
                                                                        \
        m = M_MIN + n_randint(state, M_MAX - M_MIN + 1);                \
        n = N_MIN + n_randint(state, N_MAX - N_MIN + 1);                \
                                                                        \
        T_ctx_init_rand; /* Initializes ctx */                          \
                                                                        \
        T_init(am, m, n, ctx);                                          \
        T_init(bm, m, n, ctx);                                          \
        T_init(cm, m, n, ctx);                                          \
                                                                        \
        T_randtest(am, state, ctx);                                     \
        T_randtest(bm, state, ctx);                                     \
        T_randtest(cm, state, ctx);                                     \
                                                                        \
        /* Check left-aliasing of add and sub */                        \
        T_neg(cm, am, ctx);                                             \
        result = T_is_canonical(cm, ctx);                               \
        T_add(am, am, bm, ctx);                                         \
        result = result && T_is_canonical(am, ctx);                     \
        T_sub(am, am, bm, ctx);                                         \
        result = result && T_is_canonical(am, ctx);                     \
        T_neg(am, am, ctx);                                             \
        result = result && T_is_canonical(am, ctx);                     \
        result = result && T_equal(am, cm, ctx);                        \
                                                                        \
        /* Check right-aliasing of add and sub. */                      \
        T_neg(cm, bm, ctx);                                             \
        result = result && T_is_canonical(cm, ctx);                     \
        T_add(bm, am, bm, ctx);                                         \
        result = result && T_is_canonical(bm, ctx);                     \
        T_sub(bm, am, bm, ctx);                                         \
        result = result && T_is_canonical(bm, ctx);                     \
        result = result && T_equal(bm, cm, ctx);                        \
                                                                        \
        if (!result)                                                    \
            TEST_FUNCTION_FAIL("Add-sub-neg test failed.\n");           \
                                                                        \
        T_clear(am, ctx);                                               \
        T_clear(bm, ctx);                                               \
        T_clear(cm, ctx);                                               \
                                                                        \
        T_ctx_clear(ctx);                                               \
    }                                                                   \
                                                                        \
    TEST_FUNCTION_END(state);                                           \
}

#define MAT_AORS_TEST_CTX(name, state, T, T_ctx_init_rand) \
    _MAT_AORS_TEST_CTX(                             \
            name, state,                            \
            100,                                    \
            0, 10,                                  \
            0, 10,                                  \
            T##_ctx_t,                              \
            T_ctx_init_rand,                        \
            T##_ctx_clear,                          \
            T##_mat_t,                              \
            T##_mat_init,                           \
            T##_mat_randtest,                       \
            T##_mat_add, T##_mat_sub, T##_mat_neg,  \
            T##_mat_is_zero, T##_mat_equal,         \
            T##_mat_is_canonical,                   \
            T##_mat_clear)

#endif
