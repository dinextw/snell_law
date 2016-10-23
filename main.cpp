#include <assert.h>
#include <iostream>
#include <fstream>
#include "path_tracker.h"

using namespace std;


void PrintHelp()
{
    cout << "Usage:" << endl;
    cout << "snell_law <mesh_file> <path_file> <start_point> <start_direction>" << endl;
    cout << endl;
    cout << "For example:" << endl;
    cout << "  snell_law mesh.txt path.txt 0,50,15 30,-40,-15" << endl;
}

void WritePathToFile(const list<TTravelPoint> &path, const string &filename)
{
    fstream file;
    file.open(filename, ios::out);
    if( !file.is_open() ) throw runtime_error("Cannot open output file!");

    for(auto iter = path.begin(); iter != path.end(); ++iter)
        file << iter->point.ToString() << "\t" << iter->speed_to_next << endl;
}

int main(int argc, char *argv[])
{
    if( argc != 5 )
    {
        PrintHelp();
        return 0;
    }

    try
    {
        string meshfile = argv[1];
        string pathfile = argv[2];

        TCoordinate start_point;
        start_point.FromString(argv[3]);

        TVector start_direction;
        start_direction.FromString(argv[4]);

        TMesh mesh;
        if( !mesh.LoadFile(meshfile, true) )
            throw runtime_error("Load mesh failed!");

        auto path = TrackPath(mesh, start_point, start_direction);
        WritePathToFile(path, pathfile);
    }
    catch(exception &e)
    {
        cerr << "ERROR: " << e.what() << endl;
    }

    return 0;
}
