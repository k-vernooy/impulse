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
}