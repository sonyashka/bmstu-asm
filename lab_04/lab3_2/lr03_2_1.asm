STK SEGMENT para STACK 'STACK'
	db 100 dup(0)
STK ENDS

SD1 SEGMENT para common 'DATA' ; common отвечает за наложение сегментов друг на друга
	W dw 3444h ; 34h - 4, 44h - D, порядок записи - little-endian(характерен для x86)
SD1 ENDS
END

