EXTRN X: byte
PUBLIC exit

SD2 SEGMENT para 'DATA' ; выравнивание para в 2 байта
	Y db 'Y'
SD2 ENDS

SC2 SEGMENT para public 'CODE'
	assume CS:SC2, DS:SD2
exit:
	mov ax, seg X ; запись в ax адреса сегмента X
	mov es, ax
	mov bh, es:X ; смещение X

	mov ax, SD2
	mov ds, ax

	xchg ah, Y ; xchg - обмен операндов значениями
	xchg ah, ES:X
	xchg ah, Y	

	mov ah, 2 ; вывод символа в stdout
	mov dl, Y
	int 21h	
	
	mov ax, 4c00h
	int 21h
SC2 ENDS
END