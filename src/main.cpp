#include <iostream>
#include <iomanip>

#include "../include/audio.hpp"

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

    AudioFile<double> f;
    f.load(argv[1]);
    f.printSummary();

    // Audio_Analyzer audio(argv[1]);
}