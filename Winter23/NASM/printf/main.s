	.file	"main.cpp"
	.text
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "ccc\0"
.LC1:
	.ascii "bbb\0"
.LC2:
	.ascii "aaa\0"
	.align 8
.LC3:
	.ascii "C(l): %s-%s-%s-%s-%s%l %s %x %d%%%c%b\12\0"
.LC4:
	.ascii "love\0"
.LC5:
	.ascii "eee\0"
.LC6:
	.ascii "ddd\0"
	.align 8
.LC7:
	.ascii "C(d): %s-%s-%s-%s-%s%d %s %x %d%%%c%b\12\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
.LFB28:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$96, %rsp
	.seh_stackalloc	96
	.seh_endprologue
	call	__main
	call	asmMain
	movl	$127, 88(%rsp)
	movl	$33, 80(%rsp)
	movl	$100, 72(%rsp)
	movl	$3802, 64(%rsp)
	leaq	.LC4(%rip), %rax
	movq	%rax, 56(%rsp)
	movq	$-1, 48(%rsp)
	leaq	.LC5(%rip), %rax
	movq	%rax, 40(%rsp)
	leaq	.LC6(%rip), %rax
	movq	%rax, 32(%rsp)
	leaq	.LC0(%rip), %r9
	leaq	.LC1(%rip), %r8
	leaq	.LC2(%rip), %rdx
	leaq	.LC3(%rip), %rcx
	call	callPrintfm
	movl	$127, 88(%rsp)
	movl	$33, 80(%rsp)
	movl	$100, 72(%rsp)
	movl	$3802, 64(%rsp)
	leaq	.LC4(%rip), %rax
	movq	%rax, 56(%rsp)
	movl	$-1, 48(%rsp)
	leaq	.LC5(%rip), %rax
	movq	%rax, 40(%rsp)
	leaq	.LC6(%rip), %rax
	movq	%rax, 32(%rsp)
	leaq	.LC0(%rip), %r9
	leaq	.LC1(%rip), %r8
	leaq	.LC2(%rip), %rdx
	leaq	.LC7(%rip), %rcx
	call	callPrintfm
	movl	$0, %eax
	addq	$96, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	asmMain;	.scl	2;	.type	32;	.endef
	.def	callPrintfm;	.scl	2;	.type	32;	.endef
