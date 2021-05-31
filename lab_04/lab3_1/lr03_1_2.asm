PUBLIC output_X
EXTRN X: byte

DS2 SEGMENT AT 0b800h ; базовая часть адреса, видеосегмент
	CA LABEL byte
	ORG 80 * 2 * 2 + 2 * 2 ; расположение следующего указателя относительно предыдущего
	; 80 символов в строке, каждый по 2 байта, 2 строки + смещен на 2 символа по 2 байта каждый
	SYMB LABEL word
DS2 ENDS

CSEG SEGMENT PARA PUBLIC 'CODE' ; PUBLIC - объединение сегментов с одним именем
	assume CS:CSEG, ES:DS2
output_X proc near
	mov ax, DS2
	mov es, ax
	mov ah, 10 ; цвет текста B RGB
	mov al, X ; переменная отвечающая за выводимую информацию
	mov symb, ax
	ret
output_X endp
CSEG ENDS
END