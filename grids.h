/*
 * Computation grids.
 */
#ifndef _GRIDS_H_
#define _GRIDS_H_

#include <string>
#include "coordinate.hpp"
#include "cuboid.hpp"

class TGrids
{
public:
    bool LoadFile(const std::string &filename, bool verbose);
    bool GetCellByPoint(const TCoordinate &point, Cuboid &cell);

};

#endif
