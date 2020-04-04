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
#define FREQUENCIES 512 // frequencies samples per frame

void fft(std::complex<double> a[], std::complex<double> b[], int log2n);


class Channel {

    public:
        vector<double> samples;
        void get_frequencies();
        void get_amplitudes();

        int num_frames;

        Channel(vector<double> s) : samples(s) {}
        vector<array<double, FREQUENCIES> > frequencies;
        vector<double> amplitudes;
};


class Audio_Analyzer {

    public:
        vector<Channel> channels;
        int num_frames;

        // store audio information and samples
        AudioFile<double> audio;

        void render(Canvas& canvas, int frame);
        Audio_Analyzer(char* filepath);
        vector<array<double, 2> > locate_impulses(); // {{amplitude, time}};
};