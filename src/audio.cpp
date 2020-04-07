/*=====================================
 audio.cpp                modified 3/31
 k-vernooy

 Implementation of audio class with fft
 and music analysis code for detection
=======================================*/

#include <complex>
#include <iostream>
#include <cmath>
#include <iterator>
#include <string>
#include <fstream>
#include <unistd.h>
#include <ncurses.h>
#include <sys/ioctl.h>

#include "../include/audio.hpp"
#include "../lib/fft/fft.hpp"

const double PI = 3.141592653589793238460;

// using std::array;
using std::cout;
using std::endl;
using std::complex;
using std::string;
using std::ofstream;


Audio_Analyzer::Audio_Analyzer(char* pathname) {
    /*
        @desc: reads audio file from path and saves data
        @params: `char*` pathname: file to read
        @return: `constructor`
    */

    cout << "loading audio from " << pathname << endl;    
    audio.load(pathname);
    
    // get samples from audio
    for (int x = 0; x < audio.getNumChannels(); x++) {
        vector<double> s;
        for (int i = 0; i < audio.getNumSamplesPerChannel(); i++) {
            s.push_back(audio.samples[x][i]);
        }

        // create channel from samples
        Channel c(s);
        c.num_frames = audio.getNumSamplesPerChannel() / FRAMERATE;
        channels.push_back(c);
    }

    // the amount of time needed to play each frame
    this->time_per_frame = (1.0 / (double) audio.getSampleRate()) * (double) FRAMERATE;
    this->num_frames = audio.getNumSamplesPerChannel() / FRAMERATE;
    return;
}


void writef(string contents, string path) {
    /*
        @desc:
            Write a string to a file. This method appends
            to the file rather than overwriting contents just in case.

        @param:
            `string` contents: string to write to file
            `string` path: path to write to

        @return: `void`
    */

    ofstream of(path);
    of << contents;
    of.close();
}


double Channel::get_amplitude(int frame) {
    /*
        @desc: Sums samples at a rate to determine amplitudes
        @params: none
        @return: `void`
    */

    double total = 0;
    for (int i = frame * FRAMERATE; i < FRAMERATE + (frame * FRAMERATE); i++) {
        total += abs(this->samples[i]);
    }
    total /= FRAMERATE;

    return total;
}


array<double, FREQUENCIES> Channel::get_frequencies(int frame) {
    /*
        @desc:
            uses a Fast Fourier Transform to determine power
            of frequencies for each frame and saves to a list
        
        @params: none
        @return: `void`
    */

    int i = frame;//, i < frame + FRAMERATE;
    // get the right subset of samples
    vector<double> cs = this->samples;
    vector<double> slice;
    
    if (*cs.begin() + i + FRAMERATE > cs.size()) {
        slice = vector<double>(cs.begin() + i, cs.end());
        for (int i = 0; i < FRAMERATE - slice.size(); i++) {
            slice.push_back(0.0);
        }
    }
    else {
        slice = vector<double> (cs.begin() + i, cs.begin() + i + FRAMERATE);
    }

    vector<complex<double> > ss;
    for (double s : slice) ss.push_back(complex<double> (s, 0));

    Fft::transform(ss);
    array<double, FREQUENCIES> freq;
    freq.fill(0);

    for (int i = 0; i < FRAMERATE / 2 - 1; i++) {
        freq[floor((double)i / ((double)FRAMERATE / (double)FREQUENCIES))] += abs(ss[i]);
    }

    return freq;
}


void Audio_Analyzer::render(Canvas& canvas, int frame) {
    return;
}


array<double, 2> Channel::get_impulse(int frame) {
    if (frame + 1 >= this->num_frames) return array<double, 2> {-1,-1};

    double amp, freq;

    double ampa = this->get_amplitude(frame), ampb = get_amplitude(frame + 1);
    array<double, FREQUENCIES> freqa = this->get_frequencies(frame),
        freqb = this->get_frequencies(frame + 1);

    
    if (ampb > 1.6 * ampa) {
        amp = ampb / ampa;

        // determine frequency that increases the most
        auto it = std::max_element(freqb.begin(), freqb.end());
        int dist = std::distance(freqb.begin(), it);
        freq = dist;
        cout << "impulse" << endl;
    }

    return (array<double, 2> {amp, freq});
}
