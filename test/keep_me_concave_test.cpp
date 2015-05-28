#include "../keep_me_concave.hpp"
#include <iostream>

using namespace std;


int main()
{
    KeepMeConcave kmc( 0, 100);
    LineSegment l1( 0, 0, 0, 100, false);
    LineSegment l2( -50, 50, 0, 100, false);
    //LineSegment l3( 0, 0.5, -1, 1, false);
    //LineSegment l4( 0, 0.5, -1, 1, false);
//    LineSegment l4(1,-2,-1,1, false);

    kmc.addLineSegment(l1);
    kmc.addLineSegment(l2);
//    kmc.addLineSegment(l3);
//    kmc.addLineSegment(l4);

    cout<< kmc;

}

