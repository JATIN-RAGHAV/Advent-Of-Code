	.data
filename:	.asciz "text.txt"
mode:		.asciz "r"
size:		.asciz "Size: %d\n"
numbers:	.asciz "%d, %d\n"
array1:		.skip 4000
array2:		.skip 4000
printDigit:	.asciz "%d,"
printAns:	.asciz "Answer: %d\n"
bigNum:		.word 2000000000
	.text
	.globl _main
	.align 2
_main:
	stp x29, x30, [sp, #-16]!
	sub sp,sp, #128
	stp x19, x20, [sp, #112]
	stp x21,x22, [sp, #96]
	stp x23, x24, [sp, #80]
	stp x25, x26, [sp, #64]

	adrp x23, array1@PAGE
	add x23, x23, array1@PAGEOFF
	adrp x24, array2@PAGE
	add x24, x24, array2@PAGEOFF

	# fopen(filename, mode);
	adrp x0, filename@PAGE
	add x0, x0, filename@PAGEOFF
	adrp x1, mode@PAGE
	add x1, x1, mode@PAGEOFF
	bl _fopen
	mov x19, x0

	# fseek(filepointer, 1, 2)
	mov x0, x19
	mov x1, #0
	mov x2, #2
	bl _fseek

	# ftell (filepointer)
	mov x0, x19
	bl _ftell
	mov x20, x0
	# rewind(filepointer)
	mov x0, x19
	bl _rewind

	# malloc(length+1)
	mov x0, x20
	bl _malloc
	mov x21, x0

	# fread(buffer pointer, size of chunk, no. of chunks, filepointer)
	mov x0, x21
	mov x1, #1
	mov x2, x20
	mov x3, x19
	bl _fread

	# Accessing individual rows
	mov x22, #0
_rowLoop:
	mov x0, x21
	mov x1, x22
	mov x2, #14
	mul x1, x1, x2
	add x0, x0, x1

	mov x1, #5
	mov x2, #0
	mov x3, #0
	ldr x4, [x0]
	mov x6, #10
	
	# Getting Left Number in every row
_loop1:
	and x5, x4, #0xff
	sub x5, x5, #0x30
	mul x2, x2, x6
	add x2, x2, x5
	lsr x4,x4, #8
	sub x1, x1, #1
	cmp x1, xzr
	bne _loop1

	mov x1, #5
	mov x3, #0
	add x0, x0, #8
	ldr x4, [x0]

	# Getting the Rigth Number in every Row
_loop2:
	and x5, x4, #0xff
	sub x5, x5, #0x30
	mul x3, x3, x6
	add x3, x3, x5
	lsr x4,x4, #8
	sub x1, x1, #1
	cmp x1, xzr
	bne _loop2

	# Store the numbers in the array
	mov x0, x23
	mov x1, x24
	mov x4, #4
	mul x4, x22, X4
	add x0, x0, x4
	add x1, x1, x4
	str w2, [x0]
	str w3, [x1]
	
	add x22, x22, #1
	cmp x22, #1000
	blt _rowLoop

	#Printing the arrays
	# mov x0, x23
	# bl _printArray
	# mov x0, #10
	# bl _putchar
	# mov x0, x24
	# bl _printArray

	# Find frequencey for each element in left list in the right list
	mov x10, x23
	mov x25, #0
	mov x26, #0
_feqAdder:
	ldr w0, [x10]
	mov x1, x24
	bl _findFrequency
	
	ldr w1, [x10]
	mul w3, w0, w1
	add x26, x26, x3

	add x10, x10, #4
	add x25, x25, #1
	cmp x25, #1000
	blt _feqAdder

	str w26, [sp]
	adrp x0, printAns@PAGE
	add x0, x0, printAns@PAGEOFF

	bl _printf

	# END
	ldp x19, x20, [sp, #112]
	ldp x21,x22, [sp, #96]
	ldp x23, x24, [sp, #80]
	ldp x25, x26, [sp, #64]
	add sp, sp, #128
	ldp x29, x30, [sp], #16
	mov x0, #0
	ret

_printArray:
	stp x29, x30, [sp, #-16]!
	stp x19, x20, [sp, #-16]!
	mov x19, #0
	mov x20, x0
	sub sp, sp, #16
_arrP:
	adrp x0, printDigit@PAGE
	add x0, x0, printDigit@PAGEOFF
	ldr w1, [x20]
	str w1, [sp]
	bl _printf
	
	add x20,x20, #4
	add x19, x19, #1
	cmp x19, #1000
	blt _arrP

	add sp, sp, #16
	ldp x19, x20, [sp], #16
	ldp x29, x30, [sp], #16
	ret

_findFrequency:
	stp x29, x30, [sp, #-16]!
	mov x2, #0
	mov x3, #0
_finderLoop:
	ldr w4, [x1]
	cmp w4, w0
	cinc x3, x3, eq

	add x1, x1, #4
	add x2, x2, #1
	cmp x2, #1000
	blt _finderLoop
	
	mov x0, x3
	ldp x29, x30, [sp], #16
	ret
