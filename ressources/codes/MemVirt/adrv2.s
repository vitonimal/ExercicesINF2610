	.file	"adrv2.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"Deux parametres sont recquis: adresse virtuelle (en decimal)  et taille d'une page (en decimal) "
	.align 8
.LC1:
	.string	"adrv(decimal)=%lu, adrv(hex)=%lX, pagenum(decimal)=%lu, offset(decimal)=%lu \n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	cmpl	$3, -36(%rbp)
	je	.L2
	movl	$.LC0, %edi
	call	puts
	movl	$1, %eax
	jmp	.L3
.L2:
	movl	$16, %edi
	call	malloc
	movq	%rax, -8(%rbp)
	movq	-48(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	$0, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtoul
	movq	%rax, -16(%rbp)
	movq	-48(%rbp), %rax
	addq	$16, %rax
	movq	(%rax), %rax
	movl	$0, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtoul
	movq	%rax, -24(%rbp)
	movq	-16(%rbp), %rax
	movl	$0, %edx
	divq	-24(%rbp)
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-16(%rbp), %rax
	movl	$0, %edx
	divq	-24(%rbp)
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rsi
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-16(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rsi, %r8
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	main, .-main
	.ident	"GCC: (GNU) 8.1.1 20180712 (Red Hat 8.1.1-5)"
	.section	.note.GNU-stack,"",@progbits
