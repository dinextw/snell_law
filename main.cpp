#include <iostream>
#include "mesh.h"

using namespace std;

int main(int argc, char *argv[])
{
    TMesh mesh;
    cout << "Load mesh file : " << mesh.LoadFile("test_speed_profile", true) << endl;
    cout << "Mesh dimension : (" << mesh.CountCellsX() << ","
                                 << mesh.CountCellsY() << ","
                                 << mesh.CountCellsZ() << ")" << endl;

    return 0;
}
