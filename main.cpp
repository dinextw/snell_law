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

    // Cuboid path test.
    Cuboid cell = mesh.GetCellByPoint(TVector(15, 30, 8));
    {
        cout << "Cuboid path calculate:" << endl;

        TCoordinate source(10, 22, 6);
        TVector direction(10, 16, 3);
        cout << "  Source : (" << source.x << "," << source.y << "," << source.z << ")" << endl;
        cout << "  Direction : (" << direction.x << "," << direction.y << "," << direction.z << ")" << endl;

        auto result = cell.ComputePath(source, direction);

        TCoordinate destination = result.first;
        TVector plane = result.second;
        cout << "  Destination : (" << destination.x << "," << destination.y << "," << destination.z << ")" << endl;
        cout << "  Plane normal : (" << plane.x << "," << plane.y << "," << plane.z << ")" << endl;
    }
    {
        cout << "Cuboid path calculate:" << endl;

        TCoordinate source(20, 38, 9);
        TVector direction(-10, -16, -3);
        cout << "  Source : (" << source.x << "," << source.y << "," << source.z << ")" << endl;
        cout << "  Direction : (" << direction.x << "," << direction.y << "," << direction.z << ")" << endl;

        auto result = cell.ComputePath(source, direction);

        TCoordinate destination = result.first;
        TVector plane = result.second;
        cout << "  Destination : (" << destination.x << "," << destination.y << "," << destination.z << ")" << endl;
        cout << "  Plane normal : (" << plane.x << "," << plane.y << "," << plane.z << ")" << endl;
    }

    return 0;
}
