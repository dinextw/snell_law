#include <assert.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include "mesh.h"

using namespace std;

unsigned TMesh::GetSpeedIndexByPositionIndex(unsigned x, unsigned y, unsigned z) const
{
    return ( z*CountCellsY() + y )*CountCellsX() + x;
}

void TMesh::Clear()
{
    boundaries_x.clear();
    boundaries_y.clear();
    boundaries_z.clear();
    speed_list.clear();
}

static
void ReadBoundriesPoints(stringstream &stream, vector<double> &points)
{
    points.clear();

    while( !stream.fail() )
    {
        double value;
        stream >> value;
        if( stream.fail() ) break;

        points.push_back(value);
    }
}

static
void ReadBoundries(fstream        &file,
                   vector<double> &boundaries_x,
                   vector<double> &boundaries_y,
                   vector<double> &boundaries_z)
{
    while( !file.fail() &&
          ( boundaries_x.empty() || boundaries_y.empty() || boundaries_z.empty() ))
    {
        string linestr;
        getline(file, linestr);
        if( linestr.empty() ) continue;

        stringstream linestream(linestr, ios::in);

        string label;
        linestream >> label;
        if( label == "boundary-points-x:" )
            ReadBoundriesPoints(linestream, boundaries_x);
        else if( label == "boundary-points-y:" )
            ReadBoundriesPoints(linestream, boundaries_y);
        else if( label == "boundary-points-z:" )
            ReadBoundriesPoints(linestream, boundaries_z);
    }

    if( boundaries_x.empty() ) throw runtime_error("No boundary points (X) information!");
    if( boundaries_y.empty() ) throw runtime_error("No boundary points (Y) information!");
    if( boundaries_z.empty() ) throw runtime_error("No boundary points (Z) information!");
}

static
void ReadSpeeds(fstream        &file,
                unsigned        count_x,
                unsigned        count_y,
                unsigned        count_z,
                vector<double> &speed_list)
{
    if( !count_x ) throw runtime_error("Cells count (x) zero!");
    if( !count_y ) throw runtime_error("Cells count (y) zero!");
    if( !count_z ) throw runtime_error("Cells count (z) zero!");
    speed_list.resize( count_x * count_y * count_z );

    unsigned total_count = count_x * count_y * count_z;
    for(unsigned i=0; i<total_count; ++i)
    {
        double value;
        file >> value;
        if( file.fail() ) throw runtime_error("Speed value count error!");

        speed_list.at(i) = value;
    }
}

bool TMesh::LoadFile(const string &filename, bool verbose)
{
    try
    {
        fstream file;
        file.open(filename, ios::in);
        if( !file.is_open() ) throw runtime_error( "Cannot open file: " + filename );

        ReadBoundries(file, boundaries_x, boundaries_y, boundaries_z);
        assert( boundaries_x.size() && boundaries_y.size() && boundaries_z.size() );

        unsigned count_x = boundaries_x.size() - 1;
        unsigned count_y = boundaries_y.size() - 1;
        unsigned count_z = boundaries_z.size() - 1;
        ReadSpeeds(file, count_x, count_y, count_z, speed_list);
    }
    catch(exception &e)
    {
        if( verbose ) cerr << "ERROR: " << e.what() << endl;
        Clear();

        return false;
    }

    return true;
}

Cuboid TMesh::GetCellByIndex(unsigned x, unsigned y, unsigned z) const
{
}

Cuboid TMesh::GetCellByPoint(const TCoordinate &point) const
{
}
