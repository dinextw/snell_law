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

#warning Remember to change cell to constant type.
void CuboidPathTest(Cuboid             cell,
                    const TCoordinate &start,
                    const TVector     &direction,
                    const TCoordinate &target_end,
                    const TVector     &target_normal)
{
    cout << "Cuboid path calculate:" << endl;

    cout << "  Start point: " << ToString(start) << endl;
    cout << "  Direction: " << ToString(direction) << endl;

    auto result = cell.ComputePath(start, direction);

    TCoordinate end    = result.first;
    TVector     normal = result.second;
    cout << "  End point: "
         << ToString(end)
         << ", error: "
         << ( end - target_end ).Abs()
         << endl;
    cout << "  Normal vector: "
         << ToString(normal)
         << ", error: "
         << ( normal - target_normal ).Abs()
         << endl;

    cout << endl;
}

void TestPathTrack(const TMesh       &mesh,
                   const TCoordinate &start,
                   const TVector     &direction,
                   const TCoordinate &target_end)
{
    cout << "Track path test:" << endl;
    cout << "  Start point: " << ToString(start) << endl;
    cout << "  Direction: " << ToString(direction) << endl;

    auto path = TrackPath(mesh, start, direction);
    assert( path.size() );

    TCoordinate end = path.rbegin()->point;
    cout << "  End point: "
         << ToString(end)
         << ", error= "
         << ( end - target_end ).Abs()
         << endl;

    cout << "  Travel points:" << endl;
    for(auto iter = path.begin(); iter != path.end(); ++iter)
    {
        cout << "    point: "
             << ToString(iter->point)
             << ", speed: "
             << iter->speed_to_next
             << endl;
    }

    cout << endl;
}

int main(int argc, char *argv[])
{
    // Cuboid path test.
    Cuboid cell;
    cell.SetValue(10, 20, 20, 40, 5, 10, 1);
    CuboidPathTest(cell,
                   TCoordinate(10, 22, 6),
                   TVector(10, 16, 3),
                   TCoordinate(20, 38, 9),
                   TVector(1, 0, 0));
    CuboidPathTest(cell,
                   TCoordinate(20, 38, 9),
                   TVector(-10, -16, -3),
                   TCoordinate(10, 22, 6),
                   TVector(-1, 0, 0));

    // Load test mesh.
    TMesh mesh;
    cout << "Load mesh file : " << mesh.LoadFile("test_speed_profile", true) << endl;
    cout << "Mesh dimension : (" << mesh.CountCellsX() << ","
                                 << mesh.CountCellsY() << ","
                                 << mesh.CountCellsZ() << ")" << endl;
    cout << endl;

    // Travel path track test.
    TestPathTrack(mesh,
                  TCoordinate(0, 50, 15),
                  TVector(30, -40, -15),
                  TCoordinate(30, 10, 0));

    return 0;
}
