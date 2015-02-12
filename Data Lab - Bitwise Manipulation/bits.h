/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* Define __STDC_IEC_559__ and other similar macros.  */
/* Copyright (C) 2005 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
int bitXor(int, int);
int test_bitXor(int, int);
int fitsShort(int);
int test_fitsShort(int);
int thirdBits();
int test_thirdBits();
int upperBits(int);
int test_upperBits(int);
int fitsBits(int, int);
int test_fitsBits(int, int);
int implication(int, int);
int test_implication(int, int);
int leastBitPos(int);
int test_leastBitPos(int);
int isAsciiDigit(int);
int test_isAsciiDigit(int);
int satMul2(int);
int test_satMul2(int);
int rotateLeft(int, int);
int test_rotateLeft(int, int);
int subOK(int, int);
int test_subOK(int, int);
int bitParity(int);
int test_bitParity(int);
int isPower2(int);
int test_isPower2(int);
int leftBitCount(int);
int test_leftBitCount(int);
/* Extra credit */
unsigned float_neg(unsigned);
unsigned test_float_neg(unsigned);
unsigned float_i2f(int);
unsigned test_float_i2f(int);
unsigned float_twice(unsigned);
unsigned test_float_twice(unsigned);
