	.file	"invsqrt.c"
	.text
	.globl	quick_rsqrt
	.type	quick_rsqrt, @function
quick_rsqrt:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movss	%xmm0, -20(%rbp)
	movss	-20(%rbp), %xmm0
	movss	%xmm0, -4(%rbp)
	movl	-4(%rbp), %eax
	shrl	%eax
	movl	%eax, %edx
	movl	$1597463007, %eax
	subl	%edx, %eax
	movl	%eax, -4(%rbp)
	movss	-4(%rbp), %xmm1
	movss	-20(%rbp), %xmm2
	movss	.LC0(%rip), %xmm0
	mulss	%xmm0, %xmm2
	movss	-4(%rbp), %xmm0
	mulss	%xmm0, %xmm2
	movss	-4(%rbp), %xmm0
	mulss	%xmm0, %xmm2
	movss	.LC1(%rip), %xmm0
	subss	%xmm2, %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -4(%rbp)
	movss	-4(%rbp), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	quick_rsqrt, .-quick_rsqrt
	.globl	simple_rsqrt
	.type	simple_rsqrt, @function
simple_rsqrt:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movss	%xmm0, -4(%rbp)
	movl	-4(%rbp), %eax
	movd	%eax, %xmm0
	call	sqrtf@PLT
	movss	.LC2(%rip), %xmm1
	divss	%xmm0, %xmm1
	movaps	%xmm1, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	simple_rsqrt, .-simple_rsqrt
	.section	.rodata
	.align 4
.LC0:
	.long	1056964608
	.align 4
.LC1:
	.long	1069547520
	.align 4
.LC2:
	.long	1065353216
	.ident	"GCC: (GNU) 13.2.1 20230801"
	.section	.note.GNU-stack,"",@progbits
