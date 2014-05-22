/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2014 Abhinav Baid

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "d_vec.h"
#include "ulong_extras.h"

#define D_VEC_SP_EPS (1e-14)

int
main(void)
{
    int i, result;
    FLINT_TEST_INIT(state);

    flint_printf("dot....");
    fflush(stdout);

    /* check sum of scalar products of parts of vectors is equal to the
       scalar product of vectors */
    for (i = 0; i < 10000 * flint_test_multiplier(); i++)
    {
        double *a, *b;
        double res1, res2, res3;
        slong len = n_randint(state, 100);
        if (!len)
            continue;

        a = _d_vec_init(len);
        b = _d_vec_init(len);
        _d_vec_randtest(a, state, len);
        _d_vec_randtest(b, state, len);

        res1 = _d_vec_dot(a, b, len - 1);
        res2 = _d_vec_dot(a + len - 1, b + len - 1, 1);
        res3 = _d_vec_dot(a, b, len);

        result = fabs(res1 + res2 - res3) < D_VEC_SP_EPS;
        if (!result)
        {
            flint_printf("FAIL:\n");
            printf("%g\n", fabs(res1 + res2 - res3));
            abort();
        }

        _d_vec_clear(a);
        _d_vec_clear(b);
    }

    FLINT_TEST_CLEANUP(state);

    flint_printf("PASS\n");
    return 0;
}
