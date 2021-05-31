format ELF64

section '.text'

; Microsoft x64 calling convention[18]
; https://docs.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-160&viewFallbackFrom=vs-2017

; RCX/XMM0, RDX/XMM1, R8/XMM2, R9/XMM3


_my_strcpy:
    ; rdi - dest string
    ; rsi - src string
    ; rdx - size of src strings
	
	mov rdi, rcx
	mov rsi, rdx
	
    test rdi, rdi
    je _my_strcpy_end ; nullptr check

    test rsi, rsi
    je _my_strcpy_end ; nullptr check

    mov rcx, r8 ; strlen set
    rep movsb
    mov byte [rdi], 0 ; end c string

    _my_strcpy_end:
    ret
public _my_strcpy