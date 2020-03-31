#include <complex>
#include <iostream>
#include <cmath>
#include <iterator>
#include "../include/audio.hpp"

const double PI = 3.141592653589793238460;

// using std::array;
using std::cout;
using std::endl;
using std::complex;


unsigned int bitReverse(unsigned int x, int log2n) {
    int n = 0;
    int mask = 0x1;
    for (int i=0; i < log2n; i++) {
        n <<= 1;
        n |= (x & 1);
        x >>= 1;
    }

    return n;
}

void fft(complex<double> a[], complex<double> b[], int log2n) {
    typedef typename std::iterator_traits<complex<double>*>::value_type complex;
    const complex J(0, 1);
    int n = 1 << log2n;

    for (unsigned int i=0; i < n; ++i) {
        b[bitReverse(i, log2n)] = a[i];
    }

    for (int s = 1; s <= log2n; ++s) {
        int m = 1 << s;
        int m2 = m >> 1;
        complex w(1, 0);
        complex wm = exp(-J * (PI / m2));
        for (int j=0; j < m2; ++j) {
            for (int k=j; k < n; k += m) {
                complex t = w * b[k + m2];
                complex u = b[k];
                b[k] = u + t;
                b[k + m2] = u - t;
            }
            w *= wm;
        }
    }
}

// vector<double> fft(vector<double> a,  vector<double> b, int log2n) {    
//     const complex J(0, 1);
//     int n = 1 << log2n;
//     for (unsigned int i=0; i < n; ++i) {
//         b[bitReverse(i, log2n)] = a[i];
//     }
//     for (int s = 1; s <= log2n; ++s) {
//         int m = 1 << s;
//         int m2 = m >> 1;
//         complex w(1, 0);
//         complex wm = exp(-J * (PI / m2));
//         for (int j=0; j < m2; ++j) {
//         for (int k=j; k < n; k += m) {
//             complex t = w * b[k + m2];
//             complex u = b[k];
//             b[k] = u + t;
//             b[k + m2] = u - t;
//         }
//         w *= wm;
//         }
//     }
// }

Audio_Analyzer::Audio_Analyzer(char* pathname) {
    cout << "loading audio from " << pathname << endl;    
    audio.load(pathname);

    this->samples = vector<vector<double> > (
            audio.getNumChannels(), 
            vector<double> (audio.getNumSamplesPerChannel(), 0)
        );
    
    for (int x = 0; x < audio.getNumChannels(); x++) {
        for (int i = 0; i < audio.getNumSamplesPerChannel(); i++) {
            this->samples[x][i] = audio.samples[x][i];
        }
    }
}