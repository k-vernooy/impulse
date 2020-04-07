/*=====================================
 audio.hpp                modified 3/31
 k-vernooy

Definitiom of the Audio_Analyzer class
that takes in audio file and locates
impulses
=======================================*/


#include <vector>
#include <array>
#include <complex>

#include "../include/canvas.hpp"
#include "../lib/AudioFile/AudioFile.h"

using std::vector;
using std::array;

#define FRAMERATE 1024   // samples per frame
#define FREQUENCIES 256 // frequencies samples per frame


class Channel {

    public:
        vector<double> samples;

        array<double,FREQUENCIES> get_frequencies(int frame);
        double get_amplitude(int frame);
        array<double, 2> get_impulse(int frame);

        int num_frames;

        Channel(vector<double> s) : samples(s) {}
};


class Audio_Analyzer {

    public:
        vector<Channel> channels;
        int num_frames;
        double time_per_frame;
        
        // store audio information and samples
        AudioFile<double> audio;

        void render(Canvas& canvas, int frame);
        Audio_Analyzer(char* filepath);

        void locate_impulses(); // {{amplitude, time}};
};