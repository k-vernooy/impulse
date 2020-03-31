#include <vector>
#include <array>

using std::vector;
using std::array;

typedef array<int, 2> coordinate;

class System {
    vector<coordinate> cells;

    public:
        // constructor provided cells
        System(vector<coordinate> c) : cells(c) {}
        // generate random cells near a center
        System(int number, coordinate center);

        void evolve();
};