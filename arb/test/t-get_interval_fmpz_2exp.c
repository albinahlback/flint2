/*=============================================================================

    This file is part of ARB.

    ARB is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    ARB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ARB; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2012 Fredrik Johansson

******************************************************************************/

#include "arb.h"

int main()
{
    slong iter;
    flint_rand_t state;

    printf("get_interval_fmpz_2exp....");
    fflush(stdout);
    flint_randinit(state);

    for (iter = 0; iter < 100000; iter++)
    {
        arb_t x;
        arf_t y;
        fmpz_t a, b, exp;

        arb_init(x);
        arf_init(y);
        fmpz_init(a);
        fmpz_init(b);
        fmpz_init(exp);

        arb_randtest(x, state, 200, 10);

        arb_get_interval_fmpz_2exp(a, b, exp, x);

        arf_set_fmpz_2exp(y, a, exp);
        if (!arb_contains_arf(x, y))
        {
            printf("FAIL:\n\n");
            printf("x = "); arb_print(x); printf("\n\n");
            printf("a = "); fmpz_print(a);
            printf(" exp = "); fmpz_print(exp); printf("\n\n");
            abort();
        }

        arf_set_fmpz_2exp(y, b, exp);
        if (!arb_contains_arf(x, y))
        {
            printf("FAIL:\n\n");
            printf("x = "); arb_print(x); printf("\n\n");
            printf("b = "); fmpz_print(b);
            printf(" exp = "); fmpz_print(exp); printf("\n\n");
            abort();
        }

        arb_clear(x);
        arf_clear(y);
        fmpz_clear(a);
        fmpz_clear(b);
        fmpz_clear(exp);
    }

    flint_randclear(state);
    flint_cleanup();
    printf("PASS\n");
    return EXIT_SUCCESS;
}
