#--------------------------------------------------------------
#
#  4190.308 Computer Architecture (Fall 2018)
#
#  Project #3: Image Pixelization
#
#  November 6, 2018
#
#  Jin-Soo Kim (jinsoo.kim@snu.ac.kr)
#  Systems Software & Architecture Laboratory
#  Dept. of Computer Science and Engineering
#  Seoul National University
#  http://csl.snu.ac.kr
#
#--------------------------------------------------------------

.text
	.align 4
.globl bmp_mosaic
	.type bmp_mosaic,@function

bmp_mosaic:

	#------------------------------------------------------------
	# Use %rax, %rbx, %rcx, %rdx, %rsi, and %rdi registers only
	#	imgptr is in %rdi
	#	width  is in %rsi
	#	height is in %rdx
	#	size   is in %rcx
	#------------------------------------------------------------
		# function setting
        subq    $24, %rsp
        movq    %rdi, -96(%rsp)
        movq    %rsi, -104(%rsp)
        movq    %rdx, -112(%rsp)
        movq    %rcx, -120(%rsp)

		# horiz
        movq    -104(%rsp), %rdx
        movq    %rdx, %rax
        addq    %rax, %rax
        addq    %rdx, %rax
        movq    %rax, -64(%rsp)

		# one line
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

		# for i
        movq    -112(%rsp), %rax
        leaq    -1(%rax), %rdx
        movq    -72(%rsp), %rax
        imulq   %rdx, %rax
        movq    %rax, 16(%rsp)
        jmp     .L2

		# for j
.L17:
        movq    $0, 8(%rsp)
        jmp     .L3

		# set cnt, r, g, b
.L16:
        movq    $0, (%rsp)
        movq    $0, -8(%rsp)
        movq    $0, -16(%rsp)
        movq    $0, -24(%rsp)

		# for k
        movq    $0, -32(%rsp)
        jmp     .L4
		# for l
.L9:
        movq    $0, -40(%rsp)
        jmp     .L5
.L7:
		# cnt++
        addq    $1, (%rsp)

		# loca
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

		# r +=
        movq    -80(%rsp), %rdx
        movq    -96(%rsp), %rax
        addq    %rdx, %rax
        movzbq  (%rax), %rax
        movzbq  %al, %rax
        addq    %rax, -8(%rsp)

		# g +=
        movq    -80(%rsp), %rax
        leaq    1(%rax), %rdx
        movq    -96(%rsp), %rax
        addq    %rdx, %rax
        movzbq  (%rax), %rax
        movzbq  %al, %rax
        addq    %rax, -16(%rsp)

		# b +=
        movq    -80(%rsp), %rax
        leaq    2(%rax), %rdx
        movq    -96(%rsp), %rax
        addq    %rdx, %rax
        movzbq  (%rax), %rax
        movzbq  %al, %rax
        addq    %rax, -24(%rsp)

		# l++
        addq    $1, -40(%rsp)

		# for l condition
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

		# k ++
.L6:
        addq    $1, -32(%rsp)

		# for k condition
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

		# for k
.L8:
        movq    $0, -48(%rsp)
        jmp     .L10

		# for l
.L15:
        movq    $0, -56(%rsp)
        jmp     .L11

		# loca
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

		# img[loca] = r /cnt
        movq    -8(%rsp), %rax
        cqto
        idivq   (%rsp)
        movq    %rax, %rcx
        movq    -80(%rsp), %rdx
        movq    -96(%rsp), %rax
        addq    %rdx, %rax
        movq    %rcx, %rdx
        movb    %dl, (%rax)

		# g/ cnt
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

		# b / cnt
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

		# l ++
        addq    $1, -56(%rsp)

		# l condition
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

		# k++
.L12:
        addq    $1, -48(%rsp)

		# k condition
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

		# j +=
.L14:
        movq    -120(%rsp), %rdx
        movq    %rdx, %rax
        addq    %rax, %rax
        addq    %rdx, %rax
        addq    %rax, 8(%rsp)

		# j <
.L3:
        movq    8(%rsp), %rax
        cmpq    -64(%rsp), %rax
        jl      .L16

		# i +=
        movq    -72(%rsp), %rax
        imulq   -120(%rsp), %rax
        subq    %rax, 16(%rsp)

		# i >= 0
.L2:
        cmpq    $0, 16(%rsp)
        jns     .L17
        nop
        addq    $24, %rsp
        ret
