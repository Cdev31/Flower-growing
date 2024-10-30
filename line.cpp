#include <ncurses.h>
#include <cmath>

void drawLine(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1; // Dirección de x
    int sy = (y0 < y1) ? 1 : -1; // Dirección de y
    int err = dx - dy;

    // Recorre la línea
    while (true) {
        mvaddch(y0, x0, '\\'); // Dibuja un asterisco en (x0, y0)

        if (x0 == x1 && y0 == y1) break; // Si hemos llegado al punto final
        int err2 = err * 2;
        if (err2 > -dy) {
            err -= dy;
            x0 += sx; // Mueve x hacia la dirección
        }
        if (err2 < dx) {
            err += dx;
            y0 += sy; // Mueve y hacia la dirección
        }

        // Aseguramos que se dibuje en cada paso intermedio
        // Esto puede hacer que la línea se dibuje más densa
        if (abs(x0 - x1) <= 1 && abs(y0 - y1) <= 1) {
            break; // Termina si ya está muy cerca del final
        }
    }
}

int main() {
    initscr();            // Inicializa ncurses
    cbreak();             // Desactiva el buffering de línea
    noecho();             // No muestra la entrada

    // Definimos los puntos de inicio y fin
    int x1 = 5; // Coordenada x del punto inicial
    int y1 = 5; // Coordenada y del punto inicial
    int d = 20; // Distancia a recorrer (puedes aumentar esto)
    int x2 = x1 + d; // Coordenada x del punto final
    int y2 = y1 + d; // Coordenada y del punto final

    drawLine(x1, y1, x2, y2); // Dibuja la línea
    refresh();            // Refresca la pantalla

    getch(); // Espera a que el usuario presione una tecla

    endwin();               // Finaliza ncurses
    return 0;
}

