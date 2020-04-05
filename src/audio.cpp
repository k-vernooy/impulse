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
        channels.push_back(c);
    }

    cout << "extracting frequency and amplitude information..." << endl;

    for (int i = 0; i < channels.size(); i++) {
        channels[i].get_frequencies();
        channels[i].get_amplitudes();
        channels[i].num_frames = audio.getNumSamplesPerChannel() / FRAMERATE;
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


void Channel::get_amplitudes() {
    /*
        @desc: Sums samples at a rate to determine amplitudes
        @params: none
        @return: `void`
    */

    for (int i = 0; i < samples.size(); i += FRAMERATE) {
        double total = 0;
        for (int val = i; val <= i + FRAMERATE; val++)
            total += abs(this->samples[i]);
        total /= FRAMERATE;
        amplitudes.push_back(total);
    }
}


void Channel::get_frequencies() {
    /*
        @desc:
            uses a Fast Fourier Transform to determine power
            of frequencies for each frame and saves to a list
        
        @params: none
        @return: `void`
    */


    for (int i = 0; i < samples.size(); i += FRAMERATE) {
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

        this->frequencies.push_back(freq);
    }

}


void Audio_Analyzer::render(Canvas& canvas, int frame) {

    array<int, 2> dim = canvas.get_terminal_dimensions();
    canvas.screen = vector<vector<int> > (dim[0], vector<int>(dim[1]));

    string str = "";
    for (double x : this->channels[0].frequencies[frame]) str += std::to_string(x) + ", ";
    str = str.substr(0, str.size() - 2) + "\n";

    for (int j = 0; j < this->channels[0].frequencies[frame].size(); j++) {
        
        int x = round(this->channels[0].frequencies[frame][j] * 3.0);
        if (x < 0) x = 0;
        x *= (double) dim[0] / 100.0;

        for (int i = 0; i < x; i ++) {
            int m = dim[0] - i - 1;
            if (m < 0) m = 0;
            canvas.screen[m][j] = 1;
        }
    }

    return;
}


void Channel::locate_impulses() {
    vector<array<double, 2> > imp;

    for (int i = 0; i < this->amplitudes.size(); i++) {
        if (i + IMPULSE_TIME < this->amplitudes.size()) {
            double amp = 0, freq = 0;
            vector<double> ampslice;
            vector<array<double, FREQUENCIES> > freqslice;

            ampslice = vector<double> (this->amplitudes.begin() + i, this->amplitudes.begin() + i + IMPULSE_TIME);
            freqslice = vector<array<double, FREQUENCIES> > (this->frequencies.begin() + i, this->frequencies.begin() + i + IMPULSE_TIME);

            vector<double> ampav(2, 0);

            for (int x = 0; x < IMPULSE_TIME; x++) {
                if (x < IMPULSE_TIME / 2) {
                    ampav[0] += ampslice[x];
                }
                else {
                    ampav[1] += ampslice[x];
                }
            }
            
            if (ampav[1] > 2 * ampav[0]) {
                amp = ampav[1] / ampav[0];

                // determine frequency that increases the most
                auto it = std::max_element(freqslice[IMPULSE_TIME - 1].begin(), freqslice[IMPULSE_TIME - 1].end());
                int dist = std::distance(freqslice[IMPULSE_TIME - 1].begin(), it);
                freq = dist;
            }

            this->impulses.push_back({amp, freq});
        }
    }
}


void Audio_Analyzer::locate_impulses() {
    for (int i = 0; i < channels.size(); i++) {
        channels[i].locate_impulses();
    }
}