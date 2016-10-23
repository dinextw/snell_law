#include <string.h>
#include <sstream>
#include "coordinate.hpp"

using namespace std;

static
void character_replace(char *str, char ch, char ch_new)
{
    for(; *str; ++str)
    {
        if( *str == ch )
            *str = ch_new;
    }
}

void TVector::FromString(const string &str)
{
    char buf[ str.length() + 1 ];
    memcpy(buf, str.c_str(), sizeof(buf));

    character_replace(buf, '(', ' ');
    character_replace(buf, ')', ' ');
    character_replace(buf, ',', ' ');

    double x, y, z;
    stringstream stream(buf);
    stream >> x >> y >> z;
    if( stream.fail() ) throw invalid_argument( string(__func__) + ": " + str );

    this->x = x;
    this->y = y;
    this->z = z;
}

string TVector::ToString() const
{
    stringstream stream;
    stream << "(" << x << "," << y << "," << z << ")";
    return stream.str();
}
