#include <dos.h>
#include <stdio.h>

#define BYTE unsigned char

BYTE MODOTEXTO = 3;
BYTE MODOGRAFICO = 4;

void pausa(){
    union REGS inregs, outregs;
    inregs.h.ah = 0x00;
    int86(0x16, &inregs, &outregs);
}

void selecciona_modo_video(BYTE modo){
    union REGS inregs, outregs;

    inregs.h.al = modo;
    inregs.h.ah = 0x00;

    int86(0x10, &inregs, &outregs);

    return;
}

int mi_getchar(){
    union REGS inregs, outregs;
    int caracter;
    
    inregs.h.ah = 1;
    int86(0x21, &inregs, &outregs);

    caracter = outregs.h.al;
    return caracter;
}

void mi_putchar(char c){
	 union REGS inregs, outregs;

	 inregs.h.dl = c;
     inregs.h.ah = 2;
	 
	 int86(0x21, &inregs, &outregs);
}

int main(){
    int tmp;

    selecciona_modo_video(MODOGRAFICO);
    printf("Modo grafico. Pulsa una tecla para cambiar a modo texto");
    pausa();
    selecciona_modo_video(MODOTEXTO);
    printf("Modo texto.");

    printf("\nPulsa una tecla: ");
    tmp = mi_getchar();

    printf("\nPulsaste la tecla: ");
    mi_putchar( (char)tmp );

    return 0;
}