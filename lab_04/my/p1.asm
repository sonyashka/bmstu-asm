PUBLIC X
EXTERN input: near
EXTERN output: near

STK SEGMENT para STACK 'STACK'
	db 100 dup(0)
STK ENDS

SD1 SEGMENT para PUBLIC 'DATA'
	X db ?
SD1 ENDS

CSEG SEGMENT para PUBLIC 'CODE'
	assume CS:CSEG, DS:SD1, SS:STK
main:
	mov ax, SD1
	mov ds, ax
	
	call input
	
	call output
	
	mov ax, 4c00h
	int 21h
CSEG ENDS
END main