.. _crt-helpers:

**crt_helpers.h** -- Fixed-size multiple-precision arithmetic helpers
===============================================================================

This mainly works as a helper header for the ``fft_small`` module.

This header is highly-experimental and may disappear in the future.

.. note::

    All functions here are inline only.

Functions
-------------------------------------------------------------------------------

.. function:: unsigned char _addcarry_ulong(unsigned char cf, ulong xl, ulong yl, ulong * rp)
              unsigned char _subborrow_ulong(unsigned char cf, ulong xl, ulong yl, ulong * rp)

    Computes the sum and difference of the limbs ``xl`` and ``yl``,
    respectively, and pushes the resulting limb into ``rp[0]`` and returns the
    carry (either 0 or 1).

.. function:: void multi_add_N(ulong * rp, const ulong * ap)
              void multi_sub_N(ulong * rp, const ulong * ap)
              void multi_rsub_N(ulong * rp, const ulong * ap)

    Functions for `r + a`, `r - a` and `a - r`, respectively, for the fixed-size
    multiple-precision numbers ``{rp, N}`` and ``{ap, N}``. Result is pushed
    into ``{rp, N}`` and any carry is lost.

    Here ``N`` can range from 0 to 8.

.. note::

    Note that ``multi_add_N`` and ``multi_sub_N`` are not a functions, but, for
    instance, ``multi_add_1`` and ``multi_sub_7`` are.

.. function:: void _mul(ulong * r1, ulong * r0, ulong u, ulong v)

    Computes `r_{0} + B r_{1} \leftarrow u \cdot v`.

.. function:: void _madd(ulong * r1, ulong * r0, ulong ul, ulong vl)

    Computes `r_{0} + B r_{1} + B^2 c \leftarrow r_{0} + B r_{1} + u \cdot v`,
    where the carry `c` is lost.

.. function:: void _big_mul_M_N(ulong * rp, ulong * sp, const ulong * xp, ulong yl)

    Compute two things. First, it
    computes `r_{2 k} + B r_{2 k + 1} = x_{2 k} \cdot y`
    for `0 \le k < \lfloor (M - 1) / 2 \rfloor`, and if `M` is odd it
    also computes `r_{(M - 1) / 2} = x_{(M - 1) / 2} \cdot y`.

    Similarly, and secondly, it
    computes `r_{2 k} + B r_{2 k + 1} = x_{2 k + 1} \cdot y`
    for `0 \le k < \lfloor M / 2 \rfloor - 1`, and if `M` is even it
    also computes `r_{M / 2} = x_{M / 2} \cdot y` if `M = N` or else it
    sets `r_{M / 2} = 0`.

    Requires `M \ge N`, and is currently only defined for the pairs `(M, N) \in
    \{(1, 0), (2, 1), (3, 2), (4, 3), (4, 4), (5, 4), (6, 5), (7, 6)\}`.

.. function:: void _big_mul_M_N(ulong * rp, ulong * sp, const ulong * xp, ulong yl)

    Similar to :func:`_big_mul_M_N`, but adds the result onto ``rp`` and ``xp``.


.. function:: void _reduce_big_sum_N(ulong * rp, ulong * sp, const ulong * lim)
