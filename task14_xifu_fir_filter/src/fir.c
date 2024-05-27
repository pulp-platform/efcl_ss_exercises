/*
 * Copyright (C) 2018 ETH Zurich and University of Bologna
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdint.h>
#include "common.h"

static inline void fir16_unroll8x2_inner(
  const int16_t *arr,
  const int16_t *coeff0,
  int16_t       *coeff_buffer,
  int32_t       *buffer,
  unsigned      arr_len,
  int           j
) {

  // marshal coeff_buffer (coefficients "shifted" by one elemnt + padding)
  // placeholder: set coeff_buffer:
  //  - element  0    -> 0
  //  - elements 1-16 -> coeff0[0-16]
  //  - element  17   -> 0

  // load coefficients into FIR XIFU
  volatile int *pcoeff0 = (volatile int *) &coeff0[j];
  // placeholder: XFIRLW of registers from 15 to 22 from pcoeff0
  volatile int *pcoeff1 = (volatile int *) &coeff_buffer[0];
  // placeholder: XFIRLW of registers from 23 to 31 from pcoeff1

  // loop strip-mined on output dimension
  int nb_stripmine_iter     = 1; // placeholder: number of stripmined iterations should be the array length divided by the unrolling factor on *output* dimension
  int nb_stripmine_leftover = 1; // placeholder: number of leftover elements is given by the remainder (modulus)
  for (int i=0; i<nb_stripmine_iter; i++) {

    // pointers to temp buffer
    volatile int *psum0 = (volatile int *) &buffer[2*i];
    volatile int *psum1 = (volatile int *) &buffer[2*i+1];

    // load accumulator into FIR XIFU
    // placeholder: XFIRLW of registers 0, 1 from psum0, psum1 respectively

    // load arrays
    volatile int *parr = (volatile int *) &arr[j+2*i];

    // load all array elements
    // placeholder: XFIRLW of registers from 2 to 10 from parr

    // perform all dot-products
    // placeholder: XFIRDOTP of pcoeff0 registers by parr[2-9]
    // placeholder: XFIRDOTP of pcoeff1 registers by parr[2-10]

    // store temporary
    // placeholder: XFIRSW of registers 0, 1 to psum0, psum1 respectively
    
  }
  // leftover on output dimension
  for (int i=nb_stripmine_iter*2; i<arr_len; i++) {

    // pointers to temp buffer
    volatile int *psum0 = (volatile int *) &buffer[i];

    // load accumulator into FIR XIFU
    // placeholder: XFIRLW of register 0 from psum0

    // fully reload arrays (for now)
    volatile int *parr = (volatile int *) &arr[j+i];

    // load all array elements
    // placeholder: XFIRLW of registers from 2 to 9 from parr
    // perform all dot-products
    // placeholder: XFIRDOTP of pcoeff0 registers by parr[2-9]

    // store result
    // placeholder: XFIRSW of registers 0 to psum0 respectively

  }

}

void fir16_unroll8x2(
  const int16_t *arr,
  const int16_t *coeff0,
  int16_t       *coeff_buffer,
  int32_t       *buffer,
  int16_t       *output,
  unsigned      arr_len,
  unsigned      coeff_len,
  unsigned      right_shift
) {

  // loop strip-mined on coefficient dimension
  int nb_stripmine_coeff_iter     = coeff_len / 16; // number of stripmined iterations should be the array length divided by the unrolling factor on *input* dimension in terms of elements (16)
  int nb_stripmine_coeff_leftover = coeff_len % 16 > 0 ? 1 : 0;
  for (int j=0; j<nb_stripmine_coeff_iter; j++) {
    // call inner
    fir16_unroll8x2_inner(arr, coeff0, coeff_buffer, buffer, arr_len, j*16);
  }
  
  if (nb_stripmine_coeff_leftover) {
    // call inner
    fir16_unroll8x2_inner(arr, coeff0, coeff_buffer, buffer, arr_len, nb_stripmine_coeff_iter*16);
  }

  // process outputs
  for (int i=0; i<arr_len; i++) {
    output[i] = (int16_t) ((buffer[i] >> right_shift) & 0xffff);
  }

}

