.align 2
.section .text
.globl _start

_start:
        csrr  t0, mhartid             # read hardware thread id (`hart` stands for `hardware thread`)
        bnez  t0, halt                # run only on the first hardware thread (hartid == 0), halt all the other threads

        la    sp, stack_top           # setup stack pointer

        call    kmain      

halt:   j     halt                    # enter the infinite loop

