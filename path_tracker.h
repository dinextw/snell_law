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
    double      speel_to_next;
};

std::list<TTravelPoint> TrackPath(const TMesh       &mesh,
                                  const TCoordinate &start,
                                  const TVector     &direction);

#endif
