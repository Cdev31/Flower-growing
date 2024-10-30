#include <ncurses.h>
#include <chrono>
#include <thread>

void drawCharacter(float x, float y) {
    // Dibuja el personaje en la forma [ O__o ]
    mvaddch(y, x, '[');      // Parte izquierda de la cara
    mvaddch(y, x + 1, 'O');  // Ojo izquierdo
    mvaddch(y, x + 2, '_');  // Parte superior de la boca
    mvaddch(y, x + 3, 'o');  // Ojo derecho
    mvaddch(y, x + 4, ']');  // Parte derecha de la cara
    mvaddch(y + 1, x + 3, '|' );
    mvaddch( y + 1, x + 1 , '|' );
    mvaddch( y + 1, x + 6.1, '|' );
    mvaddch( y + 1, x + 7, '|' );  
    mvaddch( y, x + 6, '/' );
    mvaddch( y, x + 7, '\\' ); 
}

int main() {
    initscr();            // Inicializa ncurses
    cbreak();             // Desactiva el buffering de línea
    noecho();             // No muestra la entrada
    keypad(stdscr, TRUE); // Habilita las teclas de función y flechas

    start_color();        // Inicia el uso de colores
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // Define un par de colores

    float x = 10;           // Posición inicial en x
    float y = 5;            // Posición inicial en y

    // Dibuja el personaje inicialmente
    attron(COLOR_PAIR(1)); // Activa el color verde
    drawCharacter(x, y);   // Dibuja el personaje
    attroff(COLOR_PAIR(1)); // Desactiva el color verde

    refresh();            // Refresca la pantalla

    while (true) {
        int ch = getch(); // Espera a que el usuario presione una tecla

        // Borra el personaje de su posición anterior
        for (int i = 0; i < 1; ++i) {
            mvaddch(y, x, ' ');     // Borra la parte izquierda de la cara
            mvaddch(y, x + 1, ' '); // Borra el ojo izquierdo
            mvaddch(y, x + 2, ' '); // Borra la parte superior de la boca
            mvaddch(y, x + 3, ' '); // Borra el ojo derecho
            mvaddch(y, x + 4, ' '); // Borra la parte derecha de la cara
            mvaddch(y + 1, x + 3, ' ' );
            mvaddch( y + 1, x + 1 , ' ' );
            mvaddch( y + 1, x + 6, ' ' );
            mvaddch( y + 1, x + 7, ' ' );  
            mvaddch( y, x + 6, ' ' );
            mvaddch( y, x + 7, ' ' ); 
        }

        // Actualiza la posición del personaje según la tecla presionada
        switch (ch) {
            case KEY_UP:    // Flecha arriba (mover hacia arriba)
                if (y > 0) y--;
                break;
            case KEY_DOWN:  // Flecha abajo (mover hacia abajo)
                if (y < LINES - 1) y++; // Ajusta según el límite inferior de la pantalla
                break;
            case KEY_LEFT:  // Flecha izquierda (mover hacia la izquierda)
                if (x > 0) x--;
                break;
            case KEY_RIGHT: // Flecha derecha (mover hacia la derecha)
                if (x < COLS - 6) x++; // Ajusta según el ancho del personaje
                break;
            case 'q':       // Salir con 'q'
                endwin();  // Finaliza ncurses
                return 0;
        }

        // Dibuja el personaje en la nueva posición
        attron(COLOR_PAIR(1)); // Activa el color verde
        drawCharacter(x, y);   // Dibuja el personaje
        attroff(COLOR_PAIR(1)); // Desactiva el color verde

        refresh();            // Refresca la pantalla
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Controla la tasa de refresco
    }

    endwin();               // Finaliza ncurses
    return 0;
}
