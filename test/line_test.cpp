#include <iostream>
#include "../line.hpp"
#include <cassert>

using namespace std;

void test_simple()
{
    LineSegment l1(-1, 1, 0, 1, false);
    LineSegment l2(1, 0, 0, 2, false);
    float result;
    bool isValid;

    isValid = l1.evaluate( 0.5, result);
    assert( isValid == true );
    assert( result == 0.5 );

    isValid = l2.evaluate( 0.5, result);
    assert( isValid == true );
    assert( result == 0.5 );

    isValid = l1.intersects( l2, result);
    assert( isValid == true );
    assert( result == 0.5 );
}

void test_non_overlapping()
{
    LineSegment l1(-1, 1, 0, 1, false);
    LineSegment l2(1, 0, 3, 4, false);
    float result;
    bool isValid;

    isValid = l1.intersects(l2, result);

    assert( isValid == false );

}

void test_parallel()
{
    LineSegment l1(1, 1, 0, 1, false);
    LineSegment l2(1, 0, 0, 1, false);
    float result;
    bool isValid;

    isValid = l1.intersects(l2, result);
    assert( isValid == false );

    l2.b = 1;

    isValid = intersects(l1,l2, result);
    assert( isValid == true );
    assert( result == l2.lambda_min);


}

void test_vertical_non_vertical()
{
    LineSegment l1(1, 1, 0, 0, true);
    LineSegment l2(-1, 1, 0, 1, false);
    float result;
    bool isValid;

    isValid = l1.intersects(l2, result);
    assert( isValid == true );
    assert( result == 0 );
    
    isValid = l2.evaluate( 0.0f, result);
    assert( result == 1.0f );
    assert( isValid == true );

    isValid = l1.evaluate( 1.0f, result);
    assert( isValid == false );
    
    isValid = l1.evaluate( 1.0f, result);
    assert( isValid = true );
    assert( result == MINUS_INFINITY);

    cout<< l1 << endl;

}

void test_vertical_non_vertical2()
{
    LineSegment l1( 0, 0, -1, -1, true);
    LineSegment l2( 0, 0, 1, 1, true);
    LineSegment l3( 1, -1, -1, 1, false);
    LineSegment l4( -1, 1, -1, 1, false);

    bool isValid;
    float result;

    isValid = l3.intersects( l1, result );

    assert( isValid == true );
}

int main()
{
    cout<<"simple"<<endl;
    test_simple();
    cout<<"non_overlapping"<<endl;
    test_non_overlapping();
    cout<<"parallel"<<endl;
    test_parallel();
    cout<<"vertical non-vertical"<<endl;
    test_vertical_non_vertical();
    cout<<"vnv2"<<endl;
    test_vertical_non_vertical2();

    cout<<endl;
    cout<< "passed all tests :) "<< endl;
    return 0;
}
