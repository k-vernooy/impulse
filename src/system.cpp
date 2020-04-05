#include <math.h>
#include "../include/system.hpp"


int System::get_neighboors(int x, int y) {
    return 0;
}


void System::evolve() {
    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[i].size(); j++) {
            int n = get_neighboors(i, j);
            if (n < 2 || n > 3) cells[i][j] = -1;
            else if (n == 3) cells[i][j] = 0;
        }
    }

    return;
}

System::System(int x, int y, int number, int centerx, int centery) {
    cells.clear();

    for (int i = 0; i < y; i++) {
        vector<int> row(x);
        cells.push_back(row);
    }

    // pow(round(sqrt(number)), 2);
}