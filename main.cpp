#include <assert.h>
#include <iostream>
#include <sstream>
#include "path_tracker.h"
#include "cuboid.hpp"
#include "snell_adjust.hpp"

using namespace std;

string ToString(const TVector &v)
{
    stringstream stream;
    stream << "(" << v.x << "," << v.y << "," << v.z << ")";
    return stream.str();
}

void CuboidPathTest(const Cuboid      &cell,
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

void PrintMeshData(const TMesh &mesh)
{
    cout << "Mesh data:" << endl;

    cout << "  Dimension : (" << mesh.CountCellsX() << ","
                              << mesh.CountCellsY() << ","
                              << mesh.CountCellsZ() << ")" << endl;

    cout << "  Points:" << endl;
    for(unsigned z = 0; z < mesh.CountCellsZ(); ++z)
    {
        for(unsigned y = 0; y < mesh.CountCellsY(); ++y)
        {
            for(unsigned x = 0; x < mesh.CountCellsX(); ++x)
            {
                Cuboid cell = mesh.GetCellByIndex(x, y, z);
                cout << "    Point " << x << ", " << y << ", " << z << endl;
                cout << "      Low bound: " << ToString(cell.GetLowBound()) << endl;
                cout << "      High bound: " << ToString(cell.GetHighBound()) << endl;
                cout << "      Speed: " << cell.GetSpeed() << endl;
            }
        }
    }

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
    CuboidPathTest(Cuboid(TCoordinate(10, 20, 5), TCoordinate(20, 40, 10), 1),
                   TCoordinate(10, 22, 6),
                   TVector(10, 16, 3),
                   TCoordinate(20, 38, 9),
                   TVector(1, 0, 0));
    CuboidPathTest(Cuboid(TCoordinate(10, 20, 5), TCoordinate(20, 40, 10), 1),
                   TCoordinate(20, 38, 9),
                   TVector(-10, -16, -3),
                   TCoordinate(10, 22, 6),
                   TVector(-1, 0, 0));

    // Load test mesh.
    TMesh mesh;
    cout << "Load mesh file : " << mesh.LoadFile("test_speed_profile", true) << endl;
    PrintMeshData(mesh);

    // Travel path track test.
    TestPathTrack(mesh,
                  TCoordinate(0, 50, 15),
                  TVector(30, -40, -15),
                  TCoordinate(30, 10, 0));
    /*
    // Cuboid test
    Cuboid test_cuboid;
    TCoordinate position_in(0,0,0);
    TVector velocity_in(0.8,0.6,0.5);
    pair<TCoordinate, TVector> result;
    test_cuboid.SetValue(0, 10, 0, 10, 0, 10, 3);
    result = test_cuboid.ComputePath(position_in, velocity_in);
    cout << result.first.x << "," << result.first.y << "," << result.first.z << endl;
    cout << result.second.x << "," << result.second.y << "," << result.second.z << endl;
    
    // Snell adjust test
    SnellAngleAdjust test;
    TVector velocity_in(5,5,10/sqrt(2)), norm_plane(0,0,-1), velocity_out;
    double speed_in = 3*sqrt(2), speed_out = 3;
    TVector test_vector;
    
    velocity_out = test.ComputeRefractedVelocity(velocity_in, norm_plane, speed_in, speed_out);
    cout << velocity_out.x << "," << velocity_out.y << "," << velocity_out.z <<endl;
    */
    return 0;
}
