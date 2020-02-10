	.file	"WinReadComPort.c"
	.comm	_comh, 4, 2
	.comm	_dcb, 28, 2
	.text
	.globl	_closeProgram
	.def	_closeProgram;	.scl	2;	.type	32;	.endef
_closeProgram:
LFB25:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
L2:
	movl	_comh, %eax
	movl	%eax, (%esp)
	call	_CloseHandle@4
	subl	$4, %esp
	movl	%eax, -12(%ebp)
	cmpl	$0, -12(%ebp)
	je	L2
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE25:
	.section .rdata,"dr"
	.align 4
LC0:
	.ascii "Baud Rate: %d, Parity: %d, Stop Bits: %d\12\0"
	.text
	.globl	_printCommState
	.def	_printCommState;	.scl	2;	.type	32;	.endef
_printCommState:
LFB26:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movzbl	_dcb+20, %eax
	movzbl	%al, %ecx
	movzbl	_dcb+19, %eax
	movzbl	%al, %edx
	movl	_dcb+4, %eax
	movl	%ecx, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE26:
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
	.align 4
LC1:
	.ascii "There was an error while opening the handle to %s\12Error Code: %d\12\0"
	.align 4
LC2:
	.ascii "There was an error while getting the state of %s\12Error code: %d\12\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB27:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x78,0x6
	.cfi_escape 0x10,0x3,0x2,0x75,0x7c
	subl	$32, %esp
	movl	%ecx, %ebx
	call	___main
	addl	$4, 4(%ebx)
	movl	4(%ebx), %eax
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	_puts
	movl	4(%ebx), %eax
	movl	(%eax), %eax
	movl	$0, 24(%esp)
	movl	$0, 20(%esp)
	movl	$3, 16(%esp)
	movl	$0, 12(%esp)
	movl	$3, 8(%esp)
	movl	$-2147483648, 4(%esp)
	movl	%eax, (%esp)
	call	_CreateFileA@28
	subl	$28, %esp
	movl	%eax, _comh
	movl	_comh, %eax
	cmpl	$-1, %eax
	jne	L5
	call	_GetLastError@0
	movl	%eax, %edx
	movl	4(%ebx), %eax
	movl	(%eax), %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	_printf
	movl	$1, %eax
	jmp	L6
L5:
	movl	$28, 8(%esp)
	movl	$0, 4(%esp)
	movl	$_dcb, (%esp)
	call	_memset
	movl	$28, _dcb
	movl	_comh, %eax
	movl	$_dcb, 4(%esp)
	movl	%eax, (%esp)
	call	_GetCommState@8
	subl	$8, %esp
	testl	%eax, %eax
	jne	L7
	call	_GetLastError@0
	movl	%eax, %edx
	movl	4(%ebx), %eax
	movl	(%eax), %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$LC2, (%esp)
	call	_printf
	call	_closeProgram
	movl	$2, %eax
	jmp	L6
L7:
	call	_printCommState
	call	_closeProgram
	movl	$0, %eax
L6:
	leal	-8(%ebp), %esp
	popl	%ecx
	.cfi_restore 1
	.cfi_def_cfa 1, 0
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE27:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_CloseHandle@4;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_puts;	.scl	2;	.type	32;	.endef
	.def	_CreateFileA@28;	.scl	2;	.type	32;	.endef
	.def	_GetLastError@0;	.scl	2;	.type	32;	.endef
	.def	_memset;	.scl	2;	.type	32;	.endef
	.def	_GetCommState@8;	.scl	2;	.type	32;	.endef
