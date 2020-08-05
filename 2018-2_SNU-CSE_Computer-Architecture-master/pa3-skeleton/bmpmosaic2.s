.text
	.align 4
.globl bmp_mosaic
	.type bmp_mosaic,@function

bmp_mosaic:
        subq    $24, %rsp
        movq    %rdi, -96(%rsp)
        movq    %rsi, -104(%rsp)
        movq    %rdx, -112(%rsp)
        movq    %rcx, -120(%rsp)
        movq    -104(%rsp), %rdx
        movq    %rdx, %rax
        addq    %rax, %rax
        addq    %rdx, %rax
        movq    %rax, -64(%rsp)
        movq    -64(%rsp), %rax
        leaq    4(%rax), %rcx
        movq    -64(%rsp), %rax
        cqto
        shrq    $62, %rdx
        addq    %rdx, %rax
        andq    $3, %rax
        subq    %rdx, %rax
        subq    %rax, %rcx
        movq    %rcx, %rax
        movq    %rax, -72(%rsp)
        movq    -112(%rsp), %rax
        leaq    -1(%rax), %rdx
        movq    -72(%rsp), %rax
        imulq   %rdx, %rax
        movq    %rax, 16(%rsp)
        jmp     .L2
.L17:
        movq    $0, 8(%rsp)
        jmp     .L3
.L16:
        movq    $0, (%rsp)
        movq    $0, -8(%rsp)
        movq    $0, -16(%rsp)
        movq    $0, -24(%rsp)
        movq    $0, -32(%rsp)
        jmp     .L4
.L9:
        movq    $0, -40(%rsp)
        jmp     .L5
.L7:
        addq    $1, (%rsp)
        movq    16(%rsp), %rdx
        movq    8(%rsp), %rax
        addq    %rax, %rdx
        movq    -32(%rsp), %rax
        imulq   -72(%rsp), %rax
        movq    %rdx, %rcx
        subq    %rax, %rcx
        movq    -40(%rsp), %rdx
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
        addq    %rax, -8(%rsp)
        movq    -80(%rsp), %rax
        leaq    1(%rax), %rdx
        movq    -96(%rsp), %rax
        addq    %rdx, %rax
        movzbq  (%rax), %rax
        movzbq  %al, %rax
        addq    %rax, -16(%rsp)
        movq    -80(%rsp), %rax
        leaq    2(%rax), %rdx
        movq    -96(%rsp), %rax
        addq    %rdx, %rax
        movzbq  (%rax), %rax
        movzbq  %al, %rax
        addq    %rax, -24(%rsp)
        addq    $1, -40(%rsp)
.L5:
        movq    -40(%rsp), %rax
        cmpq    -120(%rsp), %rax
        jge     .L6
        movq    -40(%rsp), %rdx
        movq    %rdx, %rax
        addq    %rax, %rax
        addq    %rax, %rdx
        movq    8(%rsp), %rax
        addq    %rdx, %rax
        cmpq    %rax, -64(%rsp)
        jg      .L7
.L6:
        addq    $1, -32(%rsp)
.L4:
        movq    -32(%rsp), %rax
        cmpq    -120(%rsp), %rax
        jge     .L8
        movq    -32(%rsp), %rax
        imulq   -72(%rsp), %rax
        movq    16(%rsp), %rdx
        subq    %rax, %rdx
        movq    %rdx, %rax
        testq   %rax, %rax
        jns     .L9
.L8:
        movq    $0, -48(%rsp)
        jmp     .L10
.L15:
        movq    $0, -56(%rsp)
        jmp     .L11
.L13:
        movq    16(%rsp), %rdx
        movq    8(%rsp), %rax
        addq    %rax, %rdx
        movq    -48(%rsp), %rax
        imulq   -72(%rsp), %rax
        movq    %rdx, %rcx
        subq    %rax, %rcx
        movq    -56(%rsp), %rdx
        movq    %rdx, %rax
        addq    %rax, %rax
        addq    %rdx, %rax
        addq    %rcx, %rax
        movq    %rax, -80(%rsp)
        movq    -8(%rsp), %rax
        cqto
        idivq   (%rsp)
        movq    %rax, %rcx
        movq    -80(%rsp), %rdx
        movq    -96(%rsp), %rax
        addq    %rdx, %rax
        movq    %rcx, %rdx
        movb    %dl, (%rax)
        movq    -16(%rsp), %rax
        cqto
        idivq   (%rsp)
        movq    %rax, %rcx
        movq    -80(%rsp), %rax
        leaq    1(%rax), %rdx
        movq    -96(%rsp), %rax
        addq    %rdx, %rax
        movq    %rcx, %rdx
        movb    %dl, (%rax)
        movq    -24(%rsp), %rax
        cqto
        idivq   (%rsp)
        movq    %rax, %rcx
        movq    -80(%rsp), %rax
        leaq    2(%rax), %rdx
        movq    -96(%rsp), %rax
        addq    %rdx, %rax
        movq    %rcx, %rdx
        movb    %dl, (%rax)
        addq    $1, -56(%rsp)
.L11:
        movq    -56(%rsp), %rax
        cmpq    -120(%rsp), %rax
        jge     .L12
        movq    -56(%rsp), %rdx
        movq    %rdx, %rax
        addq    %rax, %rax
        addq    %rax, %rdx
        movq    8(%rsp), %rax
        addq    %rdx, %rax
        cmpq    %rax, -64(%rsp)
        jg      .L13
.L12:
        addq    $1, -48(%rsp)
.L10:
        movq    -48(%rsp), %rax
        cmpq    -120(%rsp), %rax
        jge     .L14
        movq    -48(%rsp), %rax
        imulq   -72(%rsp), %rax
        movq    16(%rsp), %rdx
        subq    %rax, %rdx
        movq    %rdx, %rax
        testq   %rax, %rax
        jns     .L15
.L14:
        movq    -120(%rsp), %rdx
        movq    %rdx, %rax
        addq    %rax, %rax
        addq    %rdx, %rax
        addq    %rax, 8(%rsp)
.L3:
        movq    8(%rsp), %rax
        cmpq    -64(%rsp), %rax
        jl      .L16
        movq    -72(%rsp), %rax
        imulq   -120(%rsp), %rax
        subq    %rax, 16(%rsp)
.L2:
        cmpq    $0, 16(%rsp)
        jns     .L17
        nop
        addq    $24, %rsp
        ret