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
#include <thread> 
#include <chrono>

#include "../include/audio.hpp"

using std::complex;
using std::cout;
using std::endl;

using namespace std::chrono;


void detect_imp(Audio_Analyzer audio) {
    int tpf = audio.time_per_frame * 1000000;
    int total_lag = 0;

    for (int i = 0; i < audio.num_frames; i++) {
        auto start = high_resolution_clock::now();
        array<double, 2> ar = audio.channels[0].get_impulse(i);
        auto stop = high_resolution_clock::now();
        auto duration = stop - start;
        // cout << tpf << ", " << duration.count() << endl;
        total_lag += tpf - (duration.count() * 0.001);
        if (total_lag > 0) {
            usleep(total_lag);
            total_lag = 0;
        }
        // cout << total_lag << endl;
    }
}


void playsound(char* audio) {
    system((std::string("/Users/svernooy/Downloads/mpv-0.31.0/mpv.app/Contents/MacOS/mpv ") + std::string(audio) + " &> /dev/null").c_str());
}


int main(int argc, char* argv[]) {

    if (argc != 2) {
        cout << "Error: Must provide one audio file, in format .wav" << endl;
        return 1;
    }

    Audio_Analyzer audio(argv[1]);
    // Canvas canvas = Canvas();
    std::thread th1(detect_imp, audio);
    std::thread th2(playsound, argv[1]);


    th1.join();
    th2.join();
    // for (int i = 0; i < audio.num_frames; i++) {
    //     array<double, 2> ar = audio.channels[0].get_impulse(i);
    // }

    return 0;
}