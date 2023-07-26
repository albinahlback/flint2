/*
    Copyright (C) 2023 Jean Kieffer

    This file is part of Arb.

    Arb is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "acb_theta.h"

void
acb_theta_dist_pt(arb_t d2, arb_srcptr offset, const arb_mat_t cho, slong* pt, slong prec)
{
    slong g = arb_mat_nrows(cho);
    arb_ptr v;
    slong k;

    v = _arb_vec_init(g);

    for (k = 0; k < g; k++)
    {
        arb_set_si(&v[k], pt[k]);
    }
    arb_mat_vector_mul_col(v, cho, v, prec);
    _arb_vec_add(v, v, offset, g, prec);
    arb_dot(d2, NULL, 0, v, 1, v, 1, g, prec);

    _arb_vec_clear(v, g);
}
