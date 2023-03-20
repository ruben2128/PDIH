#include <dos.h>
#include <stdio.h>

#define BYTE unsigned char

BYTE MODOTEXTO = 3;
BYTE MODOGRAFICO = 4;
unsigned char cfondo = 7;
unsigned char ctexto = 14;

void gotoxy(int x, int y){
    union REGS inregs, outregs;

    inregs.h.ah = 2;
    inregs.h.dh = x;
    inregs.h.dl = y;
    inregs.h.bh = 0;
    
    int86(0x10, &inregs, &outregs);
}

void setcursortype(int tipo_cursor){
    union REGS inregs, outregs;

    inregs.h.ah = 0x01;
    switch(tipo_cursor){
        case 0:
            inregs.h.ch = 010;
            inregs.h.cl = 000;
            break;
        
        case 1:
            inregs.h.ch = 010;
            inregs.h.cl = 010;
            break;
        
        case 2:
            inregs.h.ch = 000;
            inregs.h.cl = 010;
            break;
    }

    int86(0x10, &inregs, &outregs);

}

void setvideomode(BYTE modo){
    union REGS inregs, outregs;

    inregs.h.al = modo;
    inregs.h.ah = 0x00;

    int86(0x10, &inregs, &outregs);
}

int getvideomode(){
    union REGS inregs, outregs;
    int modo;

    inregs.h.ah = 0x0F;

    int86(0x10, &inregs, &outregs);

    modo = outregs.h.al;
	return modo;

}

void clrscr(){
    setvideomode(4);
    setvideomode(3);
}


void escribir_char_con_color(char caracter){
    union REGS inregs, outregs;

    inregs.h.ah = 0x09;
    inregs.h.al = caracter;
    inregs.h.bl = cfondo << 4 | ctexto;
    inregs.h.bh = 0x00;
    inregs.x.cx = 1;

    int86(0x10, &inregs, &outregs);
}

void pausa(){
    union REGS inregs, outregs;
    inregs.h.ah = 0x00;
    int86(0x16, &inregs, &outregs);
}

int getche(){
    union REGS inregs, outregs;
    int caracter;

    inregs.h.ah = 1;
    int86(0x21, &inregs, &outregs);

    caracter = outregs.h.al;
    return caracter;
}

void dibujar_pixel(int x, int y, BYTE C){
    union REGS inregs, outregs;

    inregs.x.cx = x;
    inregs.x.dx = y;
    inregs.h.al = C;
    inregs.h.ah = 0x0C;
    
    int86(0x10, &inregs, &outregs);
}

void dibujarrecuadro(int x1, int y1, int x2, int y2, char colorprplano, char cfondo){
    int i;
    int j;

    for (i=x1; i<=x2; i++){
      for(j=y1; j<=y2; j++){
        dibujar_pixel(i,j,colorprplano);
      }
    }

}


// Esta función dibuja las iniciales de mi nombre y apellidos, es decir, las letras R, M y J.
void dibujarfiguras(){
    int i;
    int j=0;

    setvideomode(MODOGRAFICO);

    //Dibujo de la letra R

    j=5;
    for(i=5; i<80; i++){
      dibujar_pixel(j,i, 1 );
      dibujar_pixel(i,j, 1 );
    }

    j=i;
    for(i=5; i<40; i++){
      dibujar_pixel(j,i, 1 );
    }

    j=i;
    for(i=40; i<80; i++){
      dibujar_pixel(i,j, 1 );
    }

    for(i=40; i<80; i++){
      dibujar_pixel(i,i, 1 );
    }

    // Dibujo de la letra M

    j=100;
    for(i=5; i<80; i++){
      dibujar_pixel(j,i, 2 );
    }

    j=5;
    for(i=100; i<125; i++,j++){
      dibujar_pixel(i,j, 2 );
    }

    j=30;
    for(i=125; j>=5; i++,j--){
      dibujar_pixel(i,j, 2 );
    }

    j=150;
    for(i=5; i<80; i++){
      dibujar_pixel(j,i, 2 );
    }  

    //Dibujo de la letra J

    j=5;
    for(i=175; i<225; i++){
      dibujar_pixel(i,j, 3 );
    }

    j=200;
    for(i=5; i<80; i++){
      dibujar_pixel(j,i, 3 );
    } 

    j=80;
    for(i=175; i<200; i++){
      dibujar_pixel(i,j, 3 );
    }

    pausa();
    setvideomode(MODOTEXTO);    

}


int main(){
    int modovideo;
    int caracter;

    setvideomode(MODOGRAFICO);
    modovideo = getvideomode();
    printf("Modo video: %d\n",modovideo);

    gotoxy(20,8);
    setcursortype(2);

    pausa();

    setvideomode(MODOTEXTO);

    escribir_char_con_color('r');
    
    printf("\nIntroduce un caracter: ");
    caracter = getche();
    printf("\nCaracter leido en la tabla ASCII: %d\n", caracter);

    pausa();
    setvideomode(MODOGRAFICO);
    dibujarrecuadro(0,0, 100, 100, 2, 2);
    pausa();
    setvideomode(MODOTEXTO);

    dibujarfiguras();
    clrscr();

    return 0;

}
