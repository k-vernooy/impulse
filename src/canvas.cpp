#include <ncurses.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>

#include "../include/canvas.hpp"


array<int, 2> Canvas::get_terminal_dimensions() {
    /*
        @desc: retrieves the current dimensions of the terminal
        @params: none
        @return: `array<int, 2>` size of terminal in format {rows, columns}
    */

    struct winsize size;
    ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);
    return {size.ws_row - 1, size.ws_col - 1};
}


void Canvas::draw() {
    for (int i = 0; i < screen.size(); i++) {
        for (int j = 0; j < screen[i].size(); j++) {
            if (screen[i][j] == 1) mvprintw(i, j, "█");
        }
    }
}


void Canvas::clear() {
    for (int i = 0; i < screen.size(); i++) {
        for (int j = 0; j < screen[i].size(); j++) {
            mvprintw(i, j, " ");
        }
    }

    screen.clear();
}


Canvas::Canvas() {
    // initialize ncurses screen
    setlocale(LC_CTYPE, "");
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    use_default_colors();
}

Canvas::~Canvas() {
    endwin();
}