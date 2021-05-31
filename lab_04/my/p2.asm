EXTRN X: byte
PUBLIC input, output

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG
input:
	mov ax, seg X
	mov ds, ax
	mov bh, ds:X

	mov ah, 1
	int 21h
	sub al, 30h
	mov ah, 2
	mul ah
	add al, 30h
	mov ds:X, al
	ret
	
output:
	mov ah, 2
	mov dl, 13
	int 21h
	mov dl, 10
	int 21h
	
	mov dl, ds:X
	mov ah, 2
	int 21h
	ret
CSEG ENDS
END