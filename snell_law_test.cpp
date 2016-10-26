#include <assert.h>
#include <iostream>
#include "path_tracker.h"
#include "cuboid.hpp"
#include "snell_adjust.hpp"

using namespace std;

void CuboidPathTest(const Cuboid      &cell,
                    const TCoordinate &start,
                    const TVector     &direction,
                    const TCoordinate &target_end,
                    const TVector     &target_normal)
{
    cout << "Cuboid path calculate:" << endl;

    cout << "  Start point: " << start.ToString() << endl;
    cout << "  Direction: " << direction.ToString() << endl;

    auto result = cell.ComputePath(start, direction);

    TCoordinate end    = result.first;
    TVector     normal = result.second;
    cout << "  End point: "
         << end.ToString()
         << ", error: "
         << ( end - target_end ).Abs()
         << endl;
    cout << "  Normal vector: "
         << normal.ToString()
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
                cout << "      Low bound: " << cell.GetLowBound().ToString() << endl;
                cout << "      High bound: " << cell.GetHighBound().ToString() << endl;
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
    cout << "  Start point: " << start.ToString() << endl;
    cout << "  Direction: " << direction.ToString() << endl;

    auto path = TrackPath(mesh, start, direction);
    assert( path.size() );

    TCoordinate end = path.rbegin()->point;
    cout << "  End point: "
         << end.ToString()
         << ", error= "
         << ( end - target_end ).Abs()
         << endl;

    cout << "  Travel points:" << endl;
    for(auto iter = path.begin(); iter != path.end(); ++iter)
    {
        cout << "    point: "
             << iter->point.ToString()
             << ", speed: "
             << iter->speed_from_prev
             << endl;
    }

    cout << endl;
}

int main(int argc, char *argv[])
{
    // Snell adjust test
    {
        SnellAngleAdjust test;
        TVector velocity_in(5,5,10/sqrt(2)), norm_plane(0,0,-1), velocity_out;
        double speed_in = 3*sqrt(2), speed_out = 3;
        TVector test_vector;

        velocity_out = test.ComputeRefractedVelocity(velocity_in, norm_plane, speed_in, speed_out);
        cout << velocity_out.x << "," << velocity_out.y << "," << velocity_out.z <<endl;
    }

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
    CuboidPathTest(Cuboid(TCoordinate(0, 0, 0), TCoordinate(10, 10, 10), 3),
                   TCoordinate(0, 0, 0),
                   TVector(0.8, 0.6, 0.5),
                   TCoordinate(10, 7.5, 6.25),
                   TVector(1, 0, 0));
    CuboidPathTest(Cuboid(TCoordinate(0, 20, 10), TCoordinate(10, 10, 15), 1),
                   TCoordinate(7.5, 40, 11.25),
                   TVector(30, -40, -15),
                   TCoordinate(10, 36.667, 10),
                   TVector(1, 0, 0));

    // Load test mesh.
    TMesh mesh;
    cout << "Load mesh file : " << mesh.LoadFile("test_speed_profile", true) << endl;
    PrintMeshData(mesh);

    // Travel path track test.
    TestPathTrack(mesh,
                  TCoordinate(0, 50, 15),
                  TVector(30, -40, -15),
                  TCoordinate(30, 10, 0));

    return 0;
}
