/*
 * Calculate and track path through a field.
 */
#ifndef _PATH_TRACKER_H_
#define _PATH_TRACKER_H_

#include <list>
#include "mesh.h"

class TTravelPoint
{
public:
    TCoordinate point;
    double      speed_to_next;

public:
    TTravelPoint()
        : speed_to_next(0)
    {
    }

    TTravelPoint(const TCoordinate &point, double speed)
        : point(point), speed_to_next(speed)
    {
    }

};

std::list<TTravelPoint> TrackPath(const TMesh       &mesh,
                                  const TCoordinate &start,
                                  const TVector     &direction);

#endif
