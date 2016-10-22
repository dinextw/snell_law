#include <assert.h>
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
    cout << endl;

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

        cout << endl;
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

        cout << endl;
    }

    // Travel path track test.
    {
        TCoordinate start(0, 0, 15);
        TCoordinate target_end(30, 10, 0);
        TVector     direction( target_end - start );

        auto path = TrackPath(mesh, start, direction);
        assert( path.size() );

        TCoordinate end = path.rbegin()->point;
        cout << "End point: "
             << ToString(end)
             << ", error= "
             << ( end - target_end ).Abs()
             << endl;

        cout << "Travel points:" << endl;
        for(auto iter = path.begin(); iter != path.end(); ++iter)
        {
            cout << "  point: "
                 << ToString(iter->point)
                 << ", speed: "
                 << iter->speed_to_next
                 << endl;
        }

        cout << endl;
    }

    return 0;
}
