#include <vector>

using std::vector;

class Canvas {
    vector<vector<int> > screen;

    public:
        Canvas();
        void draw();
        void clear();
};