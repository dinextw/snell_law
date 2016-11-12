#include <assert.h>
#include <iostream>
#include "path_tracker.h"
#include "cuboid.hpp"
#include "snell_adjust.hpp"

using namespace std;

void SnellAdjustTest(const TVector &plane_normal,
                     double         speed_in,
                     double         speed_out,
                     const TVector &vector_in,
                     const TVector &target_vector_out)
{
    cout << "Snell adjust test:" << endl;

    SnellAngleAdjust snell;
    TVector vector_out = snell.ComputeRefractedVelocity(vector_in,
                                                        plane_normal,
                                                        speed_in,
                                                        speed_out);

    cout << "  Plane normal: " << plane_normal.ToString() << endl;
    cout << "  Speed in: " << speed_in << endl;
    cout << "  Speed out: " << speed_out << endl;
    cout << "  Vector in: " << vector_in.ToString() << endl;
    cout << "  Vector out: "
         << vector_out.ToString()
         << ", error: "
         << ( target_vector_out - vector_out ).Abs()
         << endl;

    cout << endl;
}

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
        const TVector plane_normal(0, 1, 0);
        const double speed_in  = 3;
        const double speed_out = 6;

        SnellAdjustTest(plane_normal,
                        speed_in,
                        speed_out,
                        TVector(0, -1, 0),
                        TVector(0, -1, 0));
        SnellAdjustTest(plane_normal,
                        speed_in,
                        speed_out,
                        TVector(0.3, -0.953939, 0),
                        TVector(0.6, -0.8, 0));
        SnellAdjustTest(plane_normal,
                        speed_in,
                        speed_out,
                        TVector(0.6, -0.8, 0),
                        TVector(0.6, 0.8, 0));
        SnellAdjustTest(plane_normal,
                        speed_in,
                        speed_out,
                        TVector(1, 0, 0),
                        TVector(1, 0, 0));
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
    CuboidPathTest(Cuboid(TCoordinate(0, 0.1, 0), TCoordinate(5, 0.3, 1), 8.77),
                   TCoordinate(0.03,0.1,0.96),
                   TVector(0.03, 0.1, 0.96),
                   TCoordinate(10, 36.667, 10),
                   TVector(0, 0, 1));

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
