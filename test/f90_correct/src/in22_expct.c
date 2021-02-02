/*
 * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
 * See https://llvm.org/LICENSE.txt for license information.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 * Part of the f2008 bessel_yn intrinsic test
 */

#include <stdio.h>
#include <math.h>

void
get_expected_f(float src1[], float expct[], int order, int n)
{
    int i;

    for(i= 0; i <n; i++ ) {
#if defined(_WIN32) || defined(osx86)
        expct[i] = (float)yn(order, src1[i]);
#else
        expct[i] = ynf(order, src1[i]);
#endif
        /*printf("%d) ynf(%e) = %e\n", i, src1[i], expct[i]);*/
    }
}

void
get_expected_d(double src1[], double expct[], int order, int n)
{
    int i;

    for(i= 0; i <n; i++ ) {
        expct[i] = yn(order, src1[i]);
        /*printf("%d) yn(%e) = %e\n", i, src1[i], expct[i]);*/
    }
}
