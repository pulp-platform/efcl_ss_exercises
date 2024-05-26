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

/* 
 * Mantainer: Luca Valente, luca.valente2@unibo.it
 */
#include <stdio.h>
#include <stdint.h>
#include "common.h"

void fir16(
  const int16_t *arr,
  const int16_t *coeff,
  int16_t       *output,
  unsigned      arr_len,
  unsigned      coeff_len,
  unsigned      right_shift
) {
  for (int i=0; i<1 /* TASK: replace with a reasonable loop bound */; i++) {
    int32_t sum=0;
    for (int j=0; j<1 /* TASK: replace with a reasonable loop bound */; j++) {
      sum += 0x0bad;
      // TASK do something useful here!
    }

    // shift accumulator and fit it into 16 bits
    output[i] = 0xf00d; // TASK: do something useful here!
  }
}

