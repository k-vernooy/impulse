#include <vector>
#include <array>

using std::vector;
using std::array;


class System {
    vector<vector<int> > cells;

    public:
        int get_neighboors(int x, int y);
        
        // constructor provided cells
        System(int x, int y, vector<vector<int> > c);

        // generate random cells near a center
        System(int x, int y, int number, int centerx, int centery);

        void evolve();
};