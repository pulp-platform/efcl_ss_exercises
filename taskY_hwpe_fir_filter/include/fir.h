/*
 * Copyright (C) 2018-2019 ETH Zurich and University of Bologna
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
 * Authors:  Francesco Conti <fconti@iis.ee.ethz.ch>
 * Authors:  Arpan Suravi Prasad <prasadar@iis.ee.ethz.ch>
 */

#ifndef __HAL_FIR_H__
#define __HAL_FIR_H__

void fir16(
  const int16_t *arr,
  const int16_t *coeff,
  int16_t       *output,
  unsigned      arr_len,
  unsigned      coeff_len,
  unsigned      right_shift
);

/* REGISTER MAP */
#define ARCHI_CL_EVT_ACC0 0
#define ARCHI_CL_EVT_ACC1 1
#define __builtin_bitinsert(a,b,c,d) (a | (((b << (32-c)) >> (32-c)) << d))

/* HWPE related control registers */
#define FIR_TRIGGER          0x00
#define FIR_ACQUIRE          0x04
#define FIR_FINISHED         0x08
#define FIR_STATUS           0x0c
#define FIR_RUNNING_JOB      0x10
#define FIR_SOFT_CLEAR       0x14

/* Dedicated functional registers */
#define FIR_REG_X_ADDR       0x20
#define FIR_REG_H_ADDR       0x24
#define FIR_REG_Y_ADDR       0x28
#define FIR_REG_SHIFT_LENGTH 0x2c

/* LOW-LEVEL HAL */
#define FIR_ADDR_BASE /* TASK1: Add correct base address */
#define FIR_ADDR_SPACE /* TASK1: Add correct address size */

#define HWPE_WRITE(value, offset) *(int *)(FIR_ADDR_BASE + offset) = value
#define HWPE_READ(offset)         *(int *)(FIR_ADDR_BASE + offset)

static inline void fir_x_addr_set(unsigned int value) {
  /* TASK2: Fill the place holder */
}

static inline void fir_y_addr_set(unsigned int value) {
  /* TASK2: Fill the place holder */
}

static inline void fir_h_addr_set(unsigned int value) {
  /* TASK2: Fill the place holder */
}

static inline void fir_shift_length_set(
  unsigned int shift,
  unsigned int length
) {
  unsigned int res = 0;
  /* TASK3: Compute the  res place holder */
  HWPE_WRITE(res, FIR_REG_SHIFT_LENGTH);
}

static inline void fir_trigger_job() {
  HWPE_WRITE(0, FIR_TRIGGER);
}

static inline int fir_acquire_job() {
  return HWPE_READ(FIR_ACQUIRE);
}

static inline unsigned int fir_get_status() {
  return HWPE_READ(FIR_STATUS);
}

static inline void fir_soft_clear() {
  volatile int i;
  HWPE_WRITE(0, FIR_SOFT_CLEAR);
}
#define FIR_BUSYWAIT()              do {} while((*(int volatile *)(FIR_ADDR_BASE + FIR_STATUS)) != 0)

#endif /* __HAL_FIR_H__ */
