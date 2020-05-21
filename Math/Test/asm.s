	//.global _main
	.global	_swap
	.global	@swap2@8
	//.global	PMD

	.data
/*
M_DATA:
	.long 47, 56
PRT:
	.ascii "%d, %d\n\0"
*/
	.text
/*
PMD:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$M_DATA, %eax
	pushl	4(%eax)
	pushl	(%eax)
	pushl	$PRT
	call 	_printf
	movl	$0, %eax
	leave
	ret
*/
_swap:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	movl	(%eax), %ecx
	movl	(%ebx), %edx
	movl	%ecx, (%ebx)
	movl	%edx, (%eax)
	movl	$0, %eax
	leave
	ret

@swap2@8:
	movl	(%ecx), %eax
	movl	(%edx), %ebx
	movl	%eax, (%edx)
	movl	%ebx, (%ecx)
	movl	$0, %eax
	ret

/*
_main:
	pushl	%ebp
	movl	%esp, %ebp
	call	PMD
	movl	$M_DATA, %ebx
	pushl	%ebx
	leal	4(%ebx), %ebx
	pushl	%ebx
	call	swap
	call	PMD
	movl	$0, %eax
	leave
	ret*/
	
	
