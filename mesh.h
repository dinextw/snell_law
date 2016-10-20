/*
 * Computation mesh.
 */
#ifndef _MESH_H_
#define _MESH_H_

#include <string>
#include <vector>
#include "coordinate.hpp"
#include "cuboid.hpp"

class TMesh
{
protected:
    std::vector<double> boundaries_x;
    std::vector<double> boundaries_y;
    std::vector<double> boundaries_z;
    std::vector<double> speed_list;  // Treat this as a 3D array that save speed values.

protected:
    unsigned GetSpeedIndexByPositionIndex(unsigned x, unsigned y, unsigned z) const;

public:
    void Clear();

    inline unsigned GetCountX() const { return boundaries_x.size() ? boundaries_x.size() - 1 : 0; }
    inline unsigned GetCountY() const { return boundaries_y.size() ? boundaries_y.size() - 1 : 0; }
    inline unsigned GetCountZ() const { return boundaries_z.size() ? boundaries_z.size() - 1 : 0; }

    bool LoadFile(const std::string &filename, bool verbose);
    bool GetCellByIndex(unsigned x, unsigned y, unsigned z, Cuboid &cell) const;
    bool GetCellByPoint(const TCoordinate &point, Cuboid &cell) const;

};

#endif
