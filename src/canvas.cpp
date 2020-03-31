#include <ncurses.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>

#include "../include/canvas.hpp"

void Canvas::draw() {
    for (int i = 0; i < screen.size(); i++) {
        for (int j = 0; j < screen[i].size(); j++) {
            if (screen[i][j] != -1) mvprintw(i, j, "█");
        }
    }
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