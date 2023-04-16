#include <ncurses.h>
#include <unistd.h>

#define DELAY 50000

int main(int argc, char *argv[]) {

	int next_x = 0;
	int directionx = 1;
	int next_y = 0;
	int directiony = 1;
	int resultado1 = 0, resultado2 = 0;
	bool seguir = true;
	int rows, cols;

	int ch = 0, ch2 = 0, ch3 = 0;

	initscr();
	noecho();
	cbreak();
	curs_set(FALSE);

    if (has_colors() == FALSE) {
    	endwin();
    	printf("Your terminal does not support color\n");
    	exit(1);
	}

    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3,COLOR_YELLOW,COLOR_BLACK);
    clear();

    refresh();
    getmaxyx(stdscr, rows, cols); 

    WINDOW *bienvenida = newwin(rows,cols,0,0);
    wbkgd(bienvenida, COLOR_PAIR(3));
    box(bienvenida, '|', '-'); 

    mvwprintw(bienvenida,10,10,"\t  ##########                                        \n"
               "\t           ###    ###  #######    #######    #########       \n"
               "\t           ######### ###     ### ###   ###  ###    ###       \n"
               "\t           ###       ###     ### ###   ###   #########       \n"
               "\t          #####        #######  ##### ##### ###     ###      \n"
               "\t                                             #########     \n\n"
               "\t Bienvenidos al juego pong realizado por: Rubén Martín    \n\n"
               "\t Controles para el jugador 1: tecla 'q' para subir y tecla 'a' para bajar.                \n"
               "\t Controles para el jugador 2: tecla 'o' para subir y tecla 'l' para bajar.\n\n"
			   "\t El juego finaliza una vez algún jugador consiga un resultado de 5.\n\n\n"
               "\t \t\t\tPulsa cualquier tecla para empezar el juego.");

	
    
	wrefresh(bienvenida);

    getch(); 
	
	nodelay(stdscr, TRUE);

	WINDOW *juego = newwin(rows,cols,0,0);
	wbkgd(juego, COLOR_PAIR(3));
	wmove(juego,rows,cols);

	int xc = 0, yc = rows/2;
	int xc2 = cols-1, yc2 = rows/2;
	int max_y = rows, max_x = cols;
	int x = cols/2, y = rows / 2;
		
	wrefresh(juego);

	
	WINDOW *resultado_1 = newwin(rows,cols,0,0);
    wbkgd(resultado_1, COLOR_PAIR(3));
    box(resultado_1, '#', '#'); 
	WINDOW *resultado_2 = newwin(rows,cols,0,0);
    wbkgd(resultado_2, COLOR_PAIR(3));
    box(resultado_2, '#', '#'); 

	
	while(ch != 'z'){
		while(seguir){
		
			for (int i = 0; i < max_x; i++) {
				for (int j = 0; j < max_y; j++) {
					mvwprintw(juego, j, i, " ");
				}
			}

			mvwprintw(juego,y, x, "o");
			mvwprintw(juego,yc, xc, "|");
			mvwprintw(juego,yc2, xc2, "|");
			mvwprintw(juego,2, max_x/2-6, "Resultado 1: %i", resultado1);
			mvwprintw(juego,4, max_x/2-6, "Resultado 2: %i", resultado2);

			ch = getch();

			if (ch == 'q' && yc > 0)
				yc -= 1;
			else if (ch == 'a' && yc < max_y)
				yc += 1;
			else if(ch == 'o' && yc2 > 0)
				yc2 -= 1;
			else if(ch == 'l' && yc2 < max_y)
				yc2 += 1;

			erase();

			wrefresh(juego);

			usleep(DELAY);

			next_x = x + directionx;
			next_y = y + directiony;

			if (next_x >= max_x || next_x < 0) {
				directionx*= -1;
			} else {
				x+= directionx;
			}

			if (next_y >= max_y || next_y < 0) {
				directiony*= -1;
			} else {
				y+= directiony;
			}

			if(next_x == 0 && next_x == xc && next_y == yc){
				directionx*= -1;
			} else if(next_x == 0){
				resultado2++;
				x = cols/2;
				y = rows / 2;
				directionx*= -1;
			}

			if(next_x == max_x -1  && next_x == xc2 && next_y == yc2){
				directionx*= -1;
			} else if(next_x == max_x){
				resultado1++;
				x = cols/2;
				y = rows / 2;
				directionx*= -1;
			}

			wrefresh(juego);

			if(resultado1 == 1 || resultado2 == 1){
				seguir = false;
			}

		}

		if(resultado1 == 1){
			mvwprintw(resultado_1,10,10,"\t ###########          #######             ####        ####           #######          ##########         #################      ###############           #######         ######  \n"
               "\t           ###              ###       ###         ########    ####        ###       ###       ####     ####      #####       #####      #####     #####           #######     ##########  \n"
               "\t           ###  #####       ###  ###  ###         ####    ########        ###  ###  ###       ####       ####    #####       #####      ###############                            #####  \n"
               "\t           ###    ###       ###       ###         ####        ####        ###       ###       ####     ####      #####       #####      #####       #####         #######          #####  \n"
               "\t          ###########     #######   #######     #######     #######     #######   #######     ##########         #################     #######        #######     #######       ########### \n\n\n"
               "\t Enhorabuena por la victoria Jugador 1\n\n"
               "\t Para finalizar el juego, pulsen la tecla 'z' \n\n\n");
			wrefresh(resultado_1);
			ch = getch();
		}

		if(resultado1 == 5){
			mvwprintw(resultado_2,10,10,"\t        ###########          #######            ####        ####           #######          ##########         #################      ###############           #######       #########  \n"
               "\t                 ###              ###       ###         ########    ####        ###       ###       ####     ####      #####       #####      #####     #####           #######     #####   ####  \n"
               "\t                 ###  #####       ###  ###  ###         ####    ########        ###  ###  ###       ####       ####    #####       #####      ###############                              #####  \n"
               "\t                 ###    ###       ###       ###         ####        ####        ###       ###       ####     ####      #####       #####      #####       #####         #######        ########  \n"
               "\t                ###########     #######   #######     #######     #######     #######   #######     ##########         #################     #######        #######     #######     ############# \n\n\n"
               "\t \n\n\n\nEnhorabuena por la victoria Jugador 2\n\n"
               "\t Para finalizar el juego, pulsen la tecla 'z' \n\n\n"); 
			wrefresh(resultado_2);
			ch = getch();

		}

		

	}

	getch();
	endwin();

}