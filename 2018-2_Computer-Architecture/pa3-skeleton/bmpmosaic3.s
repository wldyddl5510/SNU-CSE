.text
	.align 4
.globl bmp_mosaic
	.type bmp_mosaic,@function
bmp_mosaic:
        subq    $40, %rsp
        movq    %rdi, -96(%rsp)
        movq    %rsi, -104(%rsp)
        movq    %rdx, -112(%rsp)
        movq    %rcx, -120(%rsp)
        movq    -104(%rsp), %rdx
        movq    %rdx, %rax
        addq    %rax, %rax
        addq    %rdx, %rax
        movq    %rax, -48(%rsp)
        movq    -48(%rsp), %rax
        andq    $3, %rax
        testq   %rax, %rax
        je      .L2
        movq    -48(%rsp), %rax
        cqto
        shrq    $62, %rdx
        addq    %rdx, %rax
        andq    $3, %rax
        subq    %rdx, %rax
        movq    $4, %rdx
        subq    %rax, %rdx
        movq    %rdx, %rax
        jmp     .L3
.L2:
        movq    $0, %rax
.L3:
        movq    %rax, -56(%rsp)
        movq    -48(%rsp), %rdx
        movq    -56(%rsp), %rax
        addq    %rdx, %rax
        movq    %rax, -64(%rsp)
        movq    -112(%rsp), %rax
        leaq    -1(%rax), %rdx
        movq    -64(%rsp), %rax
        imulq   %rdx, %rax
        movq    %rax, 32(%rsp)
        jmp     .L4
.L19:
        movq    $0, 24(%rsp)
        jmp     .L5
.L18:
        movq    32(%rsp), %rdx
        movq    24(%rsp), %rax
        addq    %rdx, %rax
        movq    %rax, -72(%rsp)
        movq    $0, 16(%rsp)
        movq    $0, 8(%rsp)
        movq    $0, (%rsp)
        movq    $0, -8(%rsp)
        movq    $0, -16(%rsp)
        jmp     .L6
.L11:
        movq    $0, -24(%rsp)
        jmp     .L7
.L9:
        addq    $1, 16(%rsp)
        movq    -16(%rsp), %rax
        imulq   -64(%rsp), %rax
        movq    -72(%rsp), %rdx
        movq    %rdx, %rcx
        subq    %rax, %rcx
        movq    -24(%rsp), %rdx
        movq    %rdx, %rax
        addq    %rax, %rax
        addq    %rdx, %rax
        addq    %rcx, %rax
        movq    %rax, -80(%rsp)
        movq    -80(%rsp), %rdx
        movq    -96(%rsp), %rax
        addq    %rdx, %rax
        movzbq  (%rax), %rax
        movzbq  %al, %rax
        addq    %rax, 8(%rsp)
        movq    -80(%rsp), %rax
        leaq    1(%rax), %rdx
        movq    -96(%rsp), %rax
        addq    %rdx, %rax
        movzbq  (%rax), %rax
        movzbq  %al, %rax
        addq    %rax, (%rsp)
        movq    -80(%rsp), %rax
        leaq    2(%rax), %rdx
        movq    -96(%rsp), %rax
        addq    %rdx, %rax
        movzbq  (%rax), %rax
        movzbq  %al, %rax
        addq    %rax, -8(%rsp)
        addq    $1, -24(%rsp)
.L7:
        movq    -24(%rsp), %rax
        cmpq    -120(%rsp), %rax
        jge     .L8
        movq    -24(%rsp), %rdx
        movq    %rdx, %rax
        addq    %rax, %rax
        addq    %rax, %rdx
        movq    24(%rsp), %rax
        addq    %rdx, %rax
        cmpq    %rax, -48(%rsp)
        jg      .L9
.L8:
        addq    $1, -16(%rsp)
.L6:
        movq    -16(%rsp), %rax
        cmpq    -120(%rsp), %rax
        jge     .L10
        movq    -16(%rsp), %rax
        imulq   -64(%rsp), %rax
        movq    32(%rsp), %rdx
        subq    %rax, %rdx
        movq    %rdx, %rax
        testq   %rax, %rax
        jns     .L11
.L10:
        movq    $0, -32(%rsp)
        jmp     .L12
.L17:
        movq    $0, -40(%rsp)
        jmp     .L13
.L15:
        movq    -32(%rsp), %rax
        imulq   -64(%rsp), %rax
        movq    -72(%rsp), %rdx
        movq    %rdx, %rcx
        subq    %rax, %rcx
        movq    -40(%rsp), %rdx
        movq    %rdx, %rax
        addq    %rax, %rax
        addq    %rdx, %rax
        addq    %rcx, %rax
        movq    %rax, -80(%rsp)
        movq    8(%rsp), %rax
        cqto
        idivq   16(%rsp)
        movq    %rax, %rcx
        movq    -80(%rsp), %rdx
        movq    -96(%rsp), %rax
        addq    %rdx, %rax
        movq    %rcx, %rdx
        movb    %dl, (%rax)
        movq    (%rsp), %rax
        cqto
        idivq   16(%rsp)
        movq    %rax, %rcx
        movq    -80(%rsp), %rax
        leaq    1(%rax), %rdx
        movq    -96(%rsp), %rax
        addq    %rdx, %rax
        movq    %rcx, %rdx
        movb    %dl, (%rax)
        movq    -8(%rsp), %rax
        cqto
        idivq   16(%rsp)
        movq    %rax, %rcx
        movq    -80(%rsp), %rax
        leaq    2(%rax), %rdx
        movq    -96(%rsp), %rax
        addq    %rdx, %rax
        movq    %rcx, %rdx
        movb    %dl, (%rax)
        addq    $1, -40(%rsp)
.L13:
        movq    -40(%rsp), %rax
        cmpq    -120(%rsp), %rax
        jge     .L14
        movq    -40(%rsp), %rdx
        movq    %rdx, %rax
        addq    %rax, %rax
        addq    %rax, %rdx
        movq    24(%rsp), %rax
        addq    %rdx, %rax
        cmpq    %rax, -48(%rsp)
        jg      .L15
.L14:
        addq    $1, -32(%rsp)
.L12:
        movq    -32(%rsp), %rax
        cmpq    -120(%rsp), %rax
        jge     .L16
        movq    -32(%rsp), %rax
        imulq   -64(%rsp), %rax
        movq    32(%rsp), %rdx
        subq    %rax, %rdx
        movq    %rdx, %rax
        testq   %rax, %rax
        jns     .L17
.L16:
        movq    -120(%rsp), %rdx
        movq    %rdx, %rax
        addq    %rax, %rax
        addq    %rdx, %rax
        addq    %rax, 24(%rsp)
.L5:
        movq    24(%rsp), %rax
        cmpq    -48(%rsp), %rax
        jl      .L18
        movq    -64(%rsp), %rax
        imulq   -120(%rsp), %rax
        subq    %rax, 32(%rsp)
.L4:
        cmpq    $0, 32(%rsp)
        jns     .L19
        nop
        addq    $40, %rsp
        ret