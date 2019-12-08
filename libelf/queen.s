	.file	"queen.c"
	.option nopic
	.attribute arch, "rv32i2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-64
	sw	ra,60(sp)
	sw	s0,56(sp)
	addi	s0,sp,64
	sw	zero,-20(s0)
	j	.L2
.L3:
	lw	a5,-20(s0)
	slli	a5,a5,2
	addi	a4,s0,-16
	add	a5,a4,a5
	li	a4,-1
	sw	a4,-44(a5)
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L2:
	lw	a4,-20(s0)
	li	a5,7
	ble	a4,a5,.L3
	sw	zero,-20(s0)
	j	.L4
.L9:
	sw	zero,-28(s0)
	sw	zero,-24(s0)
	j	.L5
.L8:
	addi	a5,s0,-60
	mv	a2,a5
	lw	a1,-24(s0)
	lw	a0,-20(s0)
	call	Legal_Pos
	mv	a5,a0
	beq	a5,zero,.L6
	lw	a5,-20(s0)
	slli	a5,a5,2
	addi	a4,s0,-16
	add	a5,a4,a5
	lw	a4,-24(s0)
	sw	a4,-44(a5)
	li	a5,1
	sw	a5,-28(s0)
.L6:
	lw	a5,-24(s0)
	addi	a5,a5,1
	sw	a5,-24(s0)
.L5:
	lw	a4,-24(s0)
	li	a5,7
	bgt	a4,a5,.L7
	lw	a5,-28(s0)
	beq	a5,zero,.L8
.L7:
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L4:
	lw	a4,-20(s0)
	li	a5,7
	ble	a4,a5,.L9
	li	a5,5
	mv	a0,a5
	lw	ra,60(sp)
	lw	s0,56(sp)
	addi	sp,sp,64
	jr	ra
	.size	main, .-main
	.align	2
	.globl	Legal_Pos
	.type	Legal_Pos, @function
Legal_Pos:
	addi	sp,sp,-48
	sw	s0,44(sp)
	addi	s0,sp,48
	sw	a0,-36(s0)
	sw	a1,-40(s0)
	sw	a2,-44(s0)
	sw	zero,-20(s0)
	j	.L12
.L16:
	lw	a4,-20(s0)
	lw	a5,-36(s0)
	beq	a4,a5,.L13
	lw	a5,-20(s0)
	slli	a5,a5,2
	lw	a4,-44(s0)
	add	a5,a4,a5
	lw	a4,0(a5)
	li	a5,-1
	beq	a4,a5,.L13
	lw	a5,-20(s0)
	slli	a5,a5,2
	lw	a4,-44(s0)
	add	a5,a4,a5
	lw	a5,0(a5)
	lw	a4,-40(s0)
	sub	a4,a4,a5
	srai	a5,a4,31
	xor	a4,a5,a4
	sub	a4,a4,a5
	lw	a3,-20(s0)
	lw	a5,-36(s0)
	sub	a5,a3,a5
	srai	a3,a5,31
	xor	a5,a3,a5
	sub	a5,a5,a3
	beq	a4,a5,.L14
	lw	a5,-20(s0)
	slli	a5,a5,2
	lw	a4,-44(s0)
	add	a5,a4,a5
	lw	a5,0(a5)
	lw	a4,-40(s0)
	bne	a4,a5,.L13
.L14:
	li	a5,0
	j	.L15
.L13:
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L12:
	lw	a4,-20(s0)
	li	a5,7
	ble	a4,a5,.L16
	li	a5,1
.L15:
	mv	a0,a5
	lw	s0,44(sp)
	addi	sp,sp,48
	jr	ra
	.size	Legal_Pos, .-Legal_Pos
	.ident	"GCC: (SiFive GCC 8.3.0-2019.08.0) 8.3.0"
