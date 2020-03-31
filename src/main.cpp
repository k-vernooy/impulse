#include <iostream>
#include <iomanip>
#include <complex>

#include "../include/audio.hpp"

using std::complex;
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
    /*
        Driver for audio visualizer - 
        reads audio file, determines impulses,
        starts visualizer
    */

    if (argc != 2) {
        cout << "Error: Must provide one audio file, in format .wav" << endl;
        return 1;
    }


    typedef complex<double> cx;
    
    cx a[] = { 
        cx(0,0), cx(1,0), cx(3,0), cx(4,0), 
        cx(4, 0), cx(3, 0), cx(1,0), cx(0,0),
        cx(1,0), cx(3,0), cx(4,0), cx(4,0),
        cx(4, 0), cx(3, 0), cx(1,0), cx(0,0) 
    };

    cx b[12];
    fft(a, b, 3);

    for (int i = 0; i < 16; ++i) cout << abs(b[i]) << "\n";

    // Audio_Analyzer audio(argv[1]);
}