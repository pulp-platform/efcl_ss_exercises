/*
 * Copyright (C) 2023-2024 ETH Zurich and University of Bologna
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
 * Author: Francesco Conti f.conti@unibo.it
 */

void fir16_unroll6x2(
  const int16_t *arr,
  const int16_t *coeff0,
  const int16_t *coeff1,
  int32_t       *buffer,
  int16_t       *output,
  unsigned      arr_len,
  unsigned      coeff_len,
  unsigned      right_shift
);


void fir16_unroll8x2(
  const int16_t *arr,
  const int16_t *coeff0,
  const int16_t *coeff1,
  int32_t       *buffer,
  int16_t       *output,
  unsigned      arr_len,
  unsigned      coeff_len,
  unsigned      right_shift
);