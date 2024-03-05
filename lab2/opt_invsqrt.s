	.file	"opt_invsqrt.c"
	.text
	.p2align 4
	.globl	opt_simple_rsqrt
	.type	opt_simple_rsqrt, @function
opt_simple_rsqrt:
.LFB0:
	.cfi_startproc
	movaps	%xmm0, %xmm1
	rsqrtss	%xmm1, %xmm1
	mulss	%xmm1, %xmm0
	mulss	%xmm1, %xmm0
	mulss	.LC1(%rip), %xmm1
	addss	.LC0(%rip), %xmm0
	mulss	%xmm1, %xmm0
	ret
	.cfi_endproc
.LFE0:
	.size	opt_simple_rsqrt, .-opt_simple_rsqrt
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC0:
	.long	-1069547520
	.align 4
.LC1:
	.long	-1090519040
	.ident	"GCC: (GNU) 13.2.1 20230801"
	.section	.note.GNU-stack,"",@progbits
