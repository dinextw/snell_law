/*
 * Computation mesh.
 */
#ifndef _MESH_H_
#define _MESH_H_

#include <string>
#include "coordinate.hpp"
#include "cuboid.hpp"

class TMesh
{
public:
    bool LoadFile(const std::string &filename, bool verbose);
    bool GetCellByPoint(const TCoordinate &point, Cuboid &cell);

};

#endif
