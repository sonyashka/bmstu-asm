EXTRN output_X: near ; передача управления в пределах сегмента 

STK SEGMENT PARA STACK 'STACK' ; выравнивание PARA дает 16 байт
	db 100 dup(0) ; выделение память в 100байт и заполнение 0
STK ENDS

DSEG SEGMENT PARA PUBLIC 'DATA' ; PUBLIC - объединение сегментов с одним именем
	X db 'R'
DSEG ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG, DS:DSEG, SS:STK ; инструкция компилятору, с каким регстром будет связан сегмент во время работы
main:
	mov ax, DSEG
	mov ds, ax

	call output_X ; вызов функции вывода	

	mov ax, 4c00h ; завершение программы. вход - al = код завершения, выход - пустой
	int 21h
CSEG ENDS

PUBLIC X

END main