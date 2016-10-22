#include <iostream>
#include <sstream>
#include "path_tracker.h"

using namespace std;

string ToString(const TVector &v)
{
    stringstream stream;
    stream << "(" << v.x << "," << v.y << "," << v.z << ")";
    return stream.str();
}

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
        cout << "  Source : " << ToString(source) << endl;
        cout << "  Direction : " << ToString(direction) << endl;

        auto result = cell.ComputePath(source, direction);

        TCoordinate destination = result.first;
        TVector plane = result.second;
        cout << "  Destination : " << ToString(destination) << endl;
        cout << "  Plane normal : " << ToString(plane) << endl;
    }
    {
        cout << "Cuboid path calculate:" << endl;

        TCoordinate source(20, 38, 9);
        TVector direction(-10, -16, -3);
        cout << "  Source : " << ToString(source) << endl;
        cout << "  Direction : " << ToString(direction) << endl;

        auto result = cell.ComputePath(source, direction);

        TCoordinate destination = result.first;
        TVector plane = result.second;
        cout << "  Destination : " << ToString(destination) << endl;
        cout << "  Plane normal : " << ToString(plane) << endl;
    }

    return 0;
}
