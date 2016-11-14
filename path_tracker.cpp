#include <stdexcept>
#include "snell_adjust.hpp"
#include "path_tracker.h"

using namespace std;

static
bool FindNextCell(const TMesh       &mesh,
                  const TCoordinate &point,
                  const TVector     &direction,
                  Cuboid            &cell)
{
    /*
     * Find cell with a small position offset to
     * avoid critical problem on cell boundary.
     */
    try
    {
        static const double small_offset = 0.001;
        cell = mesh.GetCellByPoint( point + small_offset*direction );

        return true;
    }
    catch(out_of_range &e)
    {
        // Nothing to do.
    }

    return false;
}

#include <iostream>

list<TTravelPoint> TrackPath(const TMesh       &mesh,
                             const TCoordinate &start,
                             const TVector     &direction)
{
    static const double default_speed = 1;  // A dummy value, it can be any positive but zero.
    list<TTravelPoint> path;
    path.push_back(TTravelPoint(start, default_speed));

    TCoordinate curr_point  = start;
    TVector     curr_way    = direction;
    TVector     curr_normal = direction;  // Normal have no effect if it is equal as incoming vector.
    double      curr_speed  = default_speed;
    while(true)
    {
        // Get the next cell.
        Cuboid cell;
        if( !FindNextCell(mesh, curr_point, curr_way, cell) )
            break;

        // Calculate and adjust the incoming vector.
        SnellAngleAdjust snell;
        TVector next_way = snell.ComputeRefractedVelocity(curr_way,
                                                          curr_normal,
                                                          curr_speed,
                                                          cell.GetSpeed());

        // Position the next cell again,
        // because the next cell may not be the one we just found
        // in the total refraction case.
        if( !FindNextCell(mesh, curr_point, next_way, cell) )
            break;

        // Calculate next point.
        auto next = cell.ComputePath(curr_point, next_way);
        TCoordinate next_point = next.first;

        // Log point information.
        path.push_back(TTravelPoint(next_point, cell.GetSpeed()));

        // Update information as the current for next round.
        curr_point  = next_point;
        curr_way    = next_way;
        curr_normal = next.second;
        curr_speed  = cell.GetSpeed();
    }

    return path;
}
