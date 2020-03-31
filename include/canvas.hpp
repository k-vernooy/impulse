#include <vector>
#include "system.hpp"

using std::vector;

class Canvas {
    vector<vector<int> > screen;

    public:
        Canvas();
        void draw();
        void clear();
        void add_system(System sys);
};