// RISC-V Compliance Test Header File
// Copyright (c) 2017, Codasip Ltd. All Rights Reserved.
// See LICENSE for license details.
//
// Description: Common header file for RV32I tests

#ifndef _COMPLIANCE_TEST_H
#define _COMPLIANCE_TEST_H

#include "riscv_test.h"

#define WORD_SIZE 4
#define CONTEXT_SIZE 32*WORD_SIZE

// RPU macros

#define RPUTEST_CODE_BEGIN                                               \
        .section .text.init;                                            \
        .align  6;                                                      \
        .weak stvec_handler;                                            \
        .weak mtvec_handler;                                            \
        .globl _start;                                                  \
_start:                                                                 \
    addi sp, sp, -CONTEXT_SIZE;                        \
    sw x1, 1 * WORD_SIZE( sp );                   \
    sw x5, 2 * WORD_SIZE( sp );                   \
    sw x6, 3 * WORD_SIZE( sp );                   \
    sw x7, 4 * WORD_SIZE( sp );                   \
    sw x8, 5 * WORD_SIZE( sp );                   \
    sw x9, 6 * WORD_SIZE( sp );                   \
    sw x10, 7 * WORD_SIZE( sp );                  \
    sw x11, 8 * WORD_SIZE( sp );                  \
    sw x12, 9 * WORD_SIZE( sp );                  \
    sw x13, 10 * WORD_SIZE( sp );                 \
    sw x14, 11 * WORD_SIZE( sp );                 \
    sw x15, 12 * WORD_SIZE( sp );                 \
    sw x16, 13 * WORD_SIZE( sp );                 \
    sw x17, 14 * WORD_SIZE( sp );                 \
    sw x18, 15 * WORD_SIZE( sp );                 \
    sw x19, 16 * WORD_SIZE( sp );                 \
    sw x20, 17 * WORD_SIZE( sp );                 \
    sw x21, 18 * WORD_SIZE( sp );                 \
    sw x22, 19 * WORD_SIZE( sp );                 \
    sw x23, 20 * WORD_SIZE( sp );                 \
    sw x24, 21 * WORD_SIZE( sp );                 \
    sw x25, 22 * WORD_SIZE( sp );                 \
    sw x26, 23 * WORD_SIZE( sp );                 \
    sw x27, 24 * WORD_SIZE( sp );                 \
    sw x28, 25 * WORD_SIZE( sp );                 \
    sw x29, 26 * WORD_SIZE( sp );                 \
    sw x30, 27 * WORD_SIZE( sp );                 \
    sw x31, 28 * WORD_SIZE( sp );                 \
    la	t5, end_signature;                            \
    sw	sp,0(t5);                                     \
        /* reset vector */                                              \
        j reset_vector;                                                 \
        .align 2;                                                       \
trap_vector:                                                            \
        /* test whether the test came from pass/fail */                 \
        csrr t5, mcause;                                                \
        li t6, CAUSE_USER_ECALL;                                        \
        beq t5, t6, write_tohost;                                       \
        li t6, CAUSE_SUPERVISOR_ECALL;                                  \
        beq t5, t6, write_tohost;                                       \
        li t6, CAUSE_MACHINE_ECALL;                                     \
        beq t5, t6, write_tohost;                                       \
        /* if an mtvec_handler is defined, jump to it */                \
        la t5, mtvec_handler;                                           \
        beqz t5, 1f;                                                    \
        jr t5;                                                          \
        /* was it an interrupt or an exception? */                      \
  1:    csrr t5, mcause;                                                \
        bgez t5, handle_exception;                                      \
        INTERRUPT_HANDLER;                                              \
handle_exception:                                                       \
        /* we don't know how to handle whatever the exception was */    \
  other_exception:                                                      \
        /* some unhandlable exception occurred */                       \
  1:    ori TESTNUM, TESTNUM, 1337;                                     \
  write_tohost:                                                         \
        sw TESTNUM, tohost, t5;                                         \
        j write_tohost;                                                 \
reset_vector:                                                           \
        li TESTNUM, 0;                                                  \
        init;                                                           \
        la t0, 1f;                                                      \
        csrw mepc, t0;                                                  \
        csrr a0, mhartid;                                               \
1:                                                                      \
begin_testcode:



//-----------------------------------------------------------------------
// RV Compliance Macros
//-----------------------------------------------------------------------

#define RV_COMPLIANCE_HALT                                                    \
        li TESTNUM, 1;                                                  \
        SWSIG (0, TESTNUM);                                             \
    la	t5, end_signature;                            \
    lw	sp,0(t5);                                     \
    lw x1, 1 * WORD_SIZE( sp );                   \
    lw x5, 2 * WORD_SIZE( sp );                   \
    lw x6, 3 * WORD_SIZE( sp );                   \
    lw x7, 4 * WORD_SIZE( sp );                   \
    lw x8, 5 * WORD_SIZE( sp );                   \
    lw x9, 6 * WORD_SIZE( sp );                   \
    lw x10, 7 * WORD_SIZE( sp );                  \
    lw x11, 8 * WORD_SIZE( sp );                  \
    lw x12, 9 * WORD_SIZE( sp );                  \
    lw x13, 10 * WORD_SIZE( sp );                 \
    lw x14, 11 * WORD_SIZE( sp );                 \
    lw x15, 12 * WORD_SIZE( sp );                 \
    lw x16, 13 * WORD_SIZE( sp );                 \
    lw x17, 14 * WORD_SIZE( sp );                 \
    lw x18, 15 * WORD_SIZE( sp );                 \
    lw x19, 16 * WORD_SIZE( sp );                 \
    lw x20, 17 * WORD_SIZE( sp );                 \
    lw x21, 18 * WORD_SIZE( sp );                 \
    lw x22, 19 * WORD_SIZE( sp );                 \
    lw x23, 20 * WORD_SIZE( sp );                 \
    lw x24, 21 * WORD_SIZE( sp );                 \
    lw x25, 22 * WORD_SIZE( sp );                 \
    lw x26, 23 * WORD_SIZE( sp );                 \
    lw x27, 24 * WORD_SIZE( sp );                 \
    lw x28, 25 * WORD_SIZE( sp );                 \
    lw x29, 26 * WORD_SIZE( sp );                 \
    lw x30, 27 * WORD_SIZE( sp );                 \
    lw x31, 28 * WORD_SIZE( sp );                 \
    addi sp, sp, CONTEXT_SIZE;                        \
        ret;

#define RV_COMPLIANCE_RV32M                                                   \
        RVTEST_RV32M       
        
#define RV_COMPLIANCE_RV64V                                                  \
        RVTEST_RV64V                                                          \

#define RV_COMPLIANCE_CODE_BEGIN                                              \
        RPUTEST_CODE_BEGIN                                                     \

#define RV_COMPLIANCE_CODE_END                                                \
end_testcode:                                                           \
    la	t5, end_signature;                            \
    lw	sp,0(t5);                                     \
    lw x1, 1 * WORD_SIZE( sp );                   \
    lw x5, 2 * WORD_SIZE( sp );                   \
    lw x6, 3 * WORD_SIZE( sp );                   \
    lw x7, 4 * WORD_SIZE( sp );                   \
    lw x8, 5 * WORD_SIZE( sp );                   \
    lw x9, 6 * WORD_SIZE( sp );                   \
    lw x10, 7 * WORD_SIZE( sp );                  \
    lw x11, 8 * WORD_SIZE( sp );                  \
    lw x12, 9 * WORD_SIZE( sp );                  \
    lw x13, 10 * WORD_SIZE( sp );                 \
    lw x14, 11 * WORD_SIZE( sp );                 \
    lw x15, 12 * WORD_SIZE( sp );                 \
    lw x16, 13 * WORD_SIZE( sp );                 \
    lw x17, 14 * WORD_SIZE( sp );                 \
    lw x18, 15 * WORD_SIZE( sp );                 \
    lw x19, 16 * WORD_SIZE( sp );                 \
    lw x20, 17 * WORD_SIZE( sp );                 \
    lw x21, 18 * WORD_SIZE( sp );                 \
    lw x22, 19 * WORD_SIZE( sp );                 \
    lw x23, 20 * WORD_SIZE( sp );                 \
    lw x24, 21 * WORD_SIZE( sp );                 \
    lw x25, 22 * WORD_SIZE( sp );                 \
    lw x26, 23 * WORD_SIZE( sp );                 \
    lw x27, 24 * WORD_SIZE( sp );                 \
    lw x28, 25 * WORD_SIZE( sp );                 \
    lw x29, 26 * WORD_SIZE( sp );                 \
    lw x30, 27 * WORD_SIZE( sp );                 \
    lw x31, 28 * WORD_SIZE( sp );                 \
    addi sp, sp, CONTEXT_SIZE;                        \
        ret;                                                          \
        unimp;

#define RV_COMPLIANCE_DATA_BEGIN                                              \
        RVTEST_DATA_BEGIN                                                     \

#define RV_COMPLIANCE_DATA_END                                                \
        RVTEST_DATA_END                                                       \

#endif
