/*
    Copyright (C) 2020 Daniel Schultz

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "fmpq.h"
#include "mpoly.h"
#include "gr_mpoly.h"

int gr_mpoly_mul_scalar(
    gr_mpoly_t A,
    const gr_mpoly_t B,
    gr_srcptr c,
    gr_mpoly_ctx_t ctx)
{
    mpoly_ctx_struct * mctx = GR_MPOLY_MCTX(ctx);
    gr_ctx_struct * cctx = GR_MPOLY_CCTX(ctx);
    slong i, N;
    slong Alen;
    slong Blen = B->length;
    ulong * Aexp;
    const ulong * Bexp;
    fmpz * Acoeff;
    const fmpz * Bcoeff;
    int status = GR_SUCCESS;
    slong sz = cctx->sizeof_elem;

    if (Blen == 0 || gr_is_zero(c, cctx) == T_TRUE)
    {
        return gr_mpoly_zero(A, ctx);
    }

/*
    todo: integral domains

    todo
    if (gr_is_one(c) == T_TRUE || (Blen > 10 && gr_is_invertible(c, cctx) == T_TRUE))
    {
        return gr_mpoly_scalar_mul_gr_invertible(A, B, c, ctx);
    }
*/

    N = mpoly_words_per_exp(B->bits, mctx);

    gr_mpoly_fit_length_reset_bits(A, B->length, B->bits, ctx);

    Aexp = A->exps;
    Bexp = B->exps;
    Acoeff = A->coeffs;
    Bcoeff = B->coeffs;

    Alen = 0;
    for (i = 0; i < Blen; i++)
    {
        mpoly_monomial_set(Aexp + N*Alen, Bexp + N*i, N);
        status |= gr_mul(GR_ENTRY(Acoeff, Alen, sz), GR_ENTRY(Bcoeff, i, sz), c, cctx);
        Alen += (gr_is_zero(GR_ENTRY(Acoeff, Alen, sz), cctx) != T_TRUE);
    }

    A->length = Alen;

    return status;
}

int gr_mpoly_mul_si(
    gr_mpoly_t A,
    const gr_mpoly_t B,
    slong c,
    gr_mpoly_ctx_t ctx)
{
    if (c == 0 || B->length == 0)
    {
        return gr_mpoly_zero(A, ctx);
    }
    else
    {
        gr_ctx_struct * cctx = GR_MPOLY_CCTX(ctx);
        int status;
        gr_ptr t;
        GR_TMP_INIT(t, cctx);
        status = gr_set_si(t, c, cctx);
        status |= gr_mpoly_mul_scalar(A, B, t, ctx);
        GR_TMP_CLEAR(t, cctx);
        return status;
    }
}

int gr_mpoly_mul_ui(
    gr_mpoly_t A,
    const gr_mpoly_t B,
    ulong c,
    gr_mpoly_ctx_t ctx)
{
    if (c == 0 || B->length == 0)
    {
        return gr_mpoly_zero(A, ctx);
    }
    else
    {
        gr_ctx_struct * cctx = GR_MPOLY_CCTX(ctx);
        int status;
        gr_ptr t;
        GR_TMP_INIT(t, cctx);
        status = gr_set_ui(t, c, cctx);
        status |= gr_mpoly_mul_scalar(A, B, t, ctx);
        GR_TMP_CLEAR(t, cctx);
        return status;
    }
}

int gr_mpoly_mul_fmpz(
    gr_mpoly_t A,
    const gr_mpoly_t B,
    const fmpz_t c,
    gr_mpoly_ctx_t ctx)
{
    if (fmpz_is_zero(c) || B->length == 0)
    {
        return gr_mpoly_zero(A, ctx);
    }
    else
    {
        gr_ctx_struct * cctx = GR_MPOLY_CCTX(ctx);
        int status;
        gr_ptr t;
        GR_TMP_INIT(t, cctx);
        status = gr_set_fmpz(t, c, cctx);
        status |= gr_mpoly_mul_scalar(A, B, t, ctx);
        GR_TMP_CLEAR(t, cctx);
        return status;
    }
}

int gr_mpoly_mul_fmpq(
    gr_mpoly_t A,
    const gr_mpoly_t B,
    const fmpq_t c,
    gr_mpoly_ctx_t ctx)
{
    if (fmpq_is_zero(c) || B->length == 0)
    {
        return gr_mpoly_zero(A, ctx);
    }
    else
    {
        gr_ctx_struct * cctx = GR_MPOLY_CCTX(ctx);
        int status;
        gr_ptr t;
        GR_TMP_INIT(t, cctx);
        status = gr_set_fmpq(t, c, cctx);
        status |= gr_mpoly_mul_scalar(A, B, t, ctx);
        GR_TMP_CLEAR(t, cctx);
        return status;
    }
}
