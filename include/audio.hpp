#include <vector>
#include <array>
#include <complex>
#include "../lib/AudioFile/AudioFile.h"

using std::vector;
using std::array;

void fft(std::complex<double> a[], std::complex<double> b[], int log2n);

class Audio_Analyzer {
    // store audio information and samples
    AudioFile<double> audio;
    vector<vector<double> > samples;

    // collect frequency information at regular intervals
    vector<array<double, 64> > frequencies;
    // vector<double> fft(vector<double> a, vector<double> b, int log2n);
    
    // get amplitude information
    vector<double> amplitudes;

    public:
        Audio_Analyzer(char* filepath);
        vector<array<double, 2> > locate_impulses(); // {{amplitude, time}};

    // vector<double> amplitudes();
    // vector<double> frequencies();
};


// #include <iostream>
// #include <complex>
// #include <cmath>
// #include <iterator>

// using namespace std;

// unsigned int bitReverse(unsigned int x, int log2n) {
//   int n = 0;
//   int mask = 0x1;
//   for (int i=0; i < log2n; i++) {
//     n <<= 1;
//     n |= (x & 1);
//     x >>= 1;
//   }
//   return n;
// }

// const double PI = 3.1415926536;

// template<class Iter_T>
// void fft(Iter_T a, Iter_T b, int log2n)
// {
//   typedef typename iterator_traits<Iter_T>::value_type complex;
//   const complex J(0, 1);
//   int n = 1 << log2n;
//   for (unsigned int i=0; i < n; ++i) {
//     b[bitReverse(i, log2n)] = a[i];
//   }
//   for (int s = 1; s <= log2n; ++s) {
//     int m = 1 << s;
//     int m2 = m >> 1;
//     complex w(1, 0);
//     complex wm = exp(-J * (PI / m2));
//     for (int j=0; j < m2; ++j) {
//       for (int k=j; k < n; k += m) {
//         complex t = w * b[k + m2];
//         complex u = b[k];
//         b[k] = u + t;
//         b[k + m2] = u - t;
//       }
//       w *= wm;
//     }
//   }
// }

// int main() {
//   typedef complex<double> cx;
//   cx a[] = { cx(0,0), cx(1,1), cx(3,3), cx(4,4), 
//     cx(4, 4), cx(3, 3), cx(1,1), cx(0,0) };
//   cx b[8];
//   fft(a, b, 3);
//   for (int i=0; i<8; ++i) 
//     cout << b[i] << "\n";
// }