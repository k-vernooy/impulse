/*=====================================
 main.cpp                 modified 3/31
 k-vernooy

 Driver for audio visualizer - 
 reads audio file, determines impulses,
 starts visualizer
=======================================*/

#include <iostream>
#include <iomanip>
#include <complex>
#include <unistd.h>
#include <ncurses.h>

#include "../include/audio.hpp"

using std::complex;
using std::cout;
using std::endl;


int main(int argc, char* argv[]) {

    if (argc != 2) {
        cout << "Error: Must provide one audio file, in format .wav" << endl;
        return 1;
    }

    Audio_Analyzer audio(argv[1]);
    Canvas canvas = Canvas();
    
    for (int i = 0; i < audio.num_frames; i++) {
        audio.render(canvas, i);
        canvas.draw();
        wrefresh(stdscr);
        usleep(14000);
        canvas.clear();
    }

    // for (int i = 1; i < audio.num_frames - 1; i++) {
    //     audio.render(canvas, i);
    //     int ch = getch();
    //     mvprintw(0,0,std::to_string(ch).c_str());
    //     // canvas.clear();
    // }

    return 0;
}