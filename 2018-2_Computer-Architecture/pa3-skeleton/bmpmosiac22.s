bmp_mosaic:
        iaddq    $-24, %rsp
        rmmovq    %rdi, -96(%rsp)
        rmmovq    %rsi, -104(%rsp)
        rmmovq    %rdx, -112(%rsp)
        rmmovq    %rcx, -120(%rsp)

        mrmovq    -104(%rsp), %rax
        irmovq    $3, %r8
        mulq      %r8, %rax
        rmmovq    %rax, -64(%rsp)

        mrmovq    -64(%rsp), %rax   #rax=horiz
        mrmovq    -64(%rsp), %rbx   #rbx=horiz
        andq      %r8, %rax         #rax=horiz%4
        je        L3
        iaddq     $4, %rbx
        subq      %rax, %rbx        #rbx=horiz+4
L3:
        movq    %rbx, -72(%rsp)     #oneline

        movq    -112(%rsp), %rax
        leaq    -1(%rax), %rdx
        movq    -72(%rsp), %rax
        imulq   %rdx, %rax
        movq    %rax, 16(%rsp)
        jmp     .L4

.L19:
        movq    $0, 8(%rsp)
        jmp     .L5

.L18:
        movq    16(%rsp), %rdx
        movq    8(%rsp), %rax
        addq    %rdx, %rax
        movq    %rax, -80(%rsp)

        movq    $0, (%rsp)

        movq    $0, -8(%rsp)

        movq    $0, -16(%rsp)

        movq    $0, -24(%rsp)

        movq    $0, -32(%rsp)
        jmp     .L6

.L11:
        movq    $0, -40(%rsp)
        jmp     .L7
.L9:
        addq    $1, (%rsp)

        movq    -32(%rsp), %rax
        imulq   -72(%rsp), %rax
        movq    -80(%rsp), %rdx
        movq    %rdx, %rcx
        subq    %rax, %rcx
        movq    -40(%rsp), %rdx
        movq    %rdx, %rax
        addq    %rax, %rax
        addq    %rdx, %rax
        addq    %rcx, %rax
        movq    %rax, -88(%rsp)

        movq    -88(%rsp), %rdx
        movq    -96(%rsp), %rax
        addq    %rdx, %rax
        movzbl  (%rax), %eax
        movzbl  %al, %eax
        addq    %rax, -8(%rsp)

        movq    -88(%rsp), %rax
        leaq    1(%rax), %rdx
        movq    -96(%rsp), %rax
        addq    %rdx, %rax
        movzbl  (%rax), %eax
        movzbl  %al, %eax
        addq    %rax, -16(%rsp)

        movq    -88(%rsp), %rax
        leaq    2(%rax), %rdx
        movq    -96(%rsp), %rax
        addq    %rdx, %rax
        movzbl  (%rax), %eax
        movzbl  %al, %eax
        addq    %rax, -24(%rsp)

        addq    $1, -40(%rsp)
.L7:
        movq    -40(%rsp), %rax
        cmpq    -120(%rsp), %rax
        jge     .L8
        movq    -40(%rsp), %rdx
        movq    %rdx, %rax
        addq    %rax, %rax
        addq    %rax, %rdx
        movq    8(%rsp), %rax
        addq    %rdx, %rax
        cmpq    %rax, -64(%rsp)
        jg      .L9

.L8:
        addq    $1, -32(%rsp)
.L6:
        movq    -32(%rsp), %rax
        cmpq    -120(%rsp), %rax
        jge     .L10
        movq    -32(%rsp), %rax
        imulq   -72(%rsp), %rax
        movq    16(%rsp), %rdx
        subq    %rax, %rdx
        movq    %rdx, %rax
        testq   %rax, %rax
        jns     .L11
.L10:
        movq    $0, -48(%rsp)
        jmp     .L12
.L17:
        movq    $0, -56(%rsp)
        jmp     .L13
.L15:
        movq    -48(%rsp), %rax
        imulq   -72(%rsp), %rax
        movq    -80(%rsp), %rdx
        movq    %rdx, %rcx
        subq    %rax, %rcx
        movq    -56(%rsp), %rdx
        movq    %rdx, %rax
        addq    %rax, %rax
        addq    %rdx, %rax
        addq    %rcx, %rax
        movq    %rax, -88(%rsp)
        movq    -8(%rsp), %rax
        cqto
        idivq   (%rsp)
        movq    %rax, %rcx
        movq    -88(%rsp), %rdx
        movq    -96(%rsp), %rax
        addq    %rdx, %rax
        movl    %ecx, %edx
        movb    %dl, (%rax)
        movq    -16(%rsp), %rax
        cqto
        idivq   (%rsp)
        movq    %rax, %rcx
        movq    -88(%rsp), %rax
        leaq    1(%rax), %rdx
        movq    -96(%rsp), %rax
        addq    %rdx, %rax
        movl    %ecx, %edx
        movb    %dl, (%rax)
        movq    -24(%rsp), %rax
        cqto
        idivq   (%rsp)
        movq    %rax, %rcx
        movq    -88(%rsp), %rax
        leaq    2(%rax), %rdx
        movq    -96(%rsp), %rax
        addq    %rdx, %rax
        movl    %ecx, %edx
        movb    %dl, (%rax)
        addq    $1, -56(%rsp)
.L13:
        movq    -56(%rsp), %rax
        cmpq    -120(%rsp), %rax
        jge     .L14
        movq    -56(%rsp), %rdx
        movq    %rdx, %rax
        addq    %rax, %rax
        addq    %rax, %rdx
        movq    8(%rsp), %rax
        addq    %rdx, %rax
        cmpq    %rax, -64(%rsp)
        jg      .L15
.L14:
        addq    $1, -48(%rsp)
.L12:
        movq    -48(%rsp), %rax
        cmpq    -120(%rsp), %rax
        jge     .L16
        movq    -48(%rsp), %rax
        imulq   -72(%rsp), %rax
        movq    16(%rsp), %rdx
        subq    %rax, %rdx
        movq    %rdx, %rax
        testq   %rax, %rax
        jns     .L17
.L16:
        movq    -120(%rsp), %rdx
        movq    %rdx, %rax
        addq    %rax, %rax
        addq    %rdx, %rax
        addq    %rax, 8(%rsp)
.L5:
        movq    8(%rsp), %rax
        cmpq    -64(%rsp), %rax
        jl      .L18
        movq    -72(%rsp), %rax
        imulq   -120(%rsp), %rax
        subq    %rax, 16(%rsp)
.L4:
        cmpq    $0, 16(%rsp)
        jns     .L19
        nop
        addq    $24, %rsp
        ret
