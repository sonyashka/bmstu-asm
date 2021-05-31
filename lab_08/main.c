#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
void _my_strcpy(char *dst, const char *src, int size);
}

int _my_strlen_emb(const char *str){
    int res;

    __asm__ (
        "mov rax, %1 \n"
        "_my_strlen_emb_loop: \n"
        "    cmpb [rax], 0 \n"
        "    je _my_strlen_emb_loop_ends \n"
        "    inc rax \n"
        "    jmp _my_strlen_emb_loop \n"
        "_my_strlen_emb_loop_ends: \n"
        "sub rax, %1 \n"
        "mov %0, eax\n"
        : "=r"(res) 
        : "r"(str)
        : "%rax"
    );

    return res;
}

int main(){
	setbuf(stdout, NULL);
	
    char *s = (char *) malloc(255);
    for (size_t i = 0; i < 255; i++) s[i] = '!';
    
    s[15] = 0;

    const char *str = "sonyashka";
    int t = _my_strlen_emb(str);
    //printf("ptr(s)=%p ptr(str)=%p\n", (void *)s, (void *)str);
	_my_strcpy(s, str, t);
    printf("s=%s str=%s t=%d\n", s, str, t);
}