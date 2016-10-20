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

    inline unsigned CountCellsX() const { return boundaries_x.size() ? boundaries_x.size() - 1 : 0; }
    inline unsigned CountCellsY() const { return boundaries_y.size() ? boundaries_y.size() - 1 : 0; }
    inline unsigned CountCellsZ() const { return boundaries_z.size() ? boundaries_z.size() - 1 : 0; }

    bool LoadFile(const std::string &filename, bool verbose);

    Cuboid GetCellByIndex(unsigned x, unsigned y, unsigned z) const;
    Cuboid GetCellByPoint(const TCoordinate &point) const;

};

#endif
