#include <vector>
#include "system.hpp"

using std::vector;

class Canvas {

    public:
        Canvas();
        ~Canvas();
        
        vector<vector<int> > screen;
        array<int, 2> get_terminal_dimensions();
        void draw();
        void clear();
        void add_system(System sys);
};