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

#define FRAMERATE 8192   // samples per frame
#define FREQUENCIES 256 // frequencies samples per frame

#define IMPULSE_TIME 8 // # of frames to search for impulses in

class Channel {

    public:
        vector<double> samples;
        void get_frequencies();
        void get_amplitudes();

        int num_frames;

        Channel(vector<double> s) : samples(s) {}
        vector<array<double, FREQUENCIES> > frequencies;
        vector<double> amplitudes;

        void locate_impulses();
        // correspond to frames, with {amplitude, frequency} of impulse
        vector<array<double, 2>> impulses;
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