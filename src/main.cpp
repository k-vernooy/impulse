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

    if (argc != 1) cout << "Must provide one audio file" << endl;
    
    AudioFile<double> file;
    std::cout << "Loading audio..." << std::endl;
    Audio_Analyzer audio(file);
}