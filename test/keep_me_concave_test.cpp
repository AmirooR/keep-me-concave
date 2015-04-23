#include "../keep_me_concave.hpp"
#include <iostream>

using namespace std;


int main()
{
    KeepMeConcave kmc( -1, 1);
    LineSegment l1( 1, 1, -1, 1, false);
    LineSegment l2( -1, 1, -1, 1, false);
    LineSegment l3( 0, 0.5, -1, 1, false);

    kmc.addLineSegment(l1);
    kmc.addLineSegment(l2);
    kmc.addLineSegment(l3);

    cout<< kmc;

}

