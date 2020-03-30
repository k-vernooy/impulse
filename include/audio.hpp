#include <vector>
#include <array>
#include "../lib/AudioFile/AudioFile.h"

using std::vector;
using std::array;

class Audio_Analyzer {
    AudioFile<double> audio;

    public:
        Audio_Analyzer(char* filepath);
        vector<array<double, 2> > locate_impulses(); // {{amplitude, time}};

    // vector<double> amplitudes();
    // vector<double> frequencies();
};