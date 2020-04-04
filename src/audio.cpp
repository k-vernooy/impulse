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
#include "../include/audio.hpp"
#include "../lib/fft/fft.hpp"

const double PI = 3.141592653589793238460;

// using std::array;
using std::cout;
using std::endl;
using std::complex;
using std::string;
using std::ofstream;


void writef(string contents, string path) {
    /*
        Write a string to a file. This method appends
        to the file rather than overwriting contents just in case.
    */

    ofstream of(path);
    of << contents;
    of.close();
}


string to_string(array<double, FRAMERATE> v) {
    string s;
    for (double t : v) s += std::to_string(t) + ", ";

    s = s.substr(0, s.size() - 2);
    return s;
}

string to_string(vector<double> v) {
    string s;
    for (double t : v) s += std::to_string(t) + ", ";

    s = s.substr(0, s.size() - 2);
    return s;
}

// unsigned int bitReverse(unsigned int x, int log2n) {
//     int n = 0;
//     int mask = 0x1;
//     for (int i=0; i < log2n; i++) {
//         n <<= 1;
//         n |= (x & 1);
//         x >>= 1;
//     }

//     return n;
// }


// void fft(complex<double> a[], complex<double> b[], int log2n) {
//     typedef complex<double> complex;
//     const complex J(0, 1);
//     int n = 1 << log2n;

//     for (unsigned int i=0; i < n; i++) {
//         b[bitReverse(i, log2n)] = a[i];
//     }

//     for (int s = 1; s <= log2n; s++) {
//         int m = 1 << s;
//         int m2 = m >> 1;
//         complex w(1, 0);
//         complex wm = exp(-J * (PI / m2));
//         for (int j = 0; j < m2; j++) {
//             for (int k = j; k < n; k += m) {
//                 complex t = w * b[k + m2];
//                 complex u = b[k];
//                 b[k] = u + t;
//                 b[k + m2] = u - t;
//             }
//             w *= wm;
//         }
//     }
// }


void Channel::get_amplitudes() {
    for (int i = 0; i < samples.size(); i += FRAMERATE) {
        double total = 0;
        for (int val = i; val <= i + FRAMERATE; val++)
            total += abs(this->samples[i]);
        total /= FRAMERATE;
        amplitudes.push_back(total);
    }
}


void Channel::get_frequencies() {
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

        for (int i = 0; i < FRAMERATE; i++) {
            freq[floor((double)i / ((double)FRAMERATE / (double)FREQUENCIES))] += abs(ss[i]);
        }

        this->frequencies.push_back(freq);
    }

}


Audio_Analyzer::Audio_Analyzer(char* pathname) {
    cout << "loading audio from " << pathname << endl;    
    audio.load(pathname);

    for (int x = 0; x < audio.getNumChannels(); x++) {
        vector<double> s;
        for (int i = 0; i < audio.getNumSamplesPerChannel(); i++) {
            s.push_back(audio.samples[x][i]);
        }

        Channel c(s);
        channels.push_back(c);
    }

    cout << "extracting frequency and amplitude information..." << endl;

    for (int i = 0; i < channels.size(); i++) {
        channels[i].get_frequencies();
        channels[i].get_amplitudes();
        channels[i].num_frames = audio.getNumSamplesPerChannel() / FRAMERATE;
    }

    this->num_frames = audio.getNumSamplesPerChannel() / FRAMERATE;
    cout << this->num_frames << endl;
    return;
}