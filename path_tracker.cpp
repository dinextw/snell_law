#include "path_tracker.h"

using namespace std;

static
Cuboid FindNextCell(const TMesh       &mesh,
                    const TCoordinate &point,
                    const TVector     &direction)
{
    /*
     * Find cell with a small position offset to
     * avoid critical problem on cell boundary.
     */
    static const double small_offset = 0.001;
    return mesh.GetCellByPoint( point + small_offset*direction );
}

list<TTravelPoint> TrackPath(const TMesh       &mesh,
                             const TCoordinate &start,
                             const TVector     &direction)
{
    list<TTravelPoint> path;
    path.push_back(TTravelPoint(start, 0));

    TCoordinate curr_point = start;
    TVector     curr_way   = direction;
    while(true)
    {
        Cuboid cell;
        try
        {
            cell = FindNextCell(mesh, curr_point, curr_way);
        }
        catch(out_of_range &e)
        {
            break;
        }

        auto next = cell.ComputePath(curr_point, curr_way);
        TCoordinate next_point = next.first;

        path.back().speed_to_next = cell.GetSpeed();
        path.push_back(TTravelPoint(next_point, 0));

        curr_point = next_point;
    }

    return path;
}
