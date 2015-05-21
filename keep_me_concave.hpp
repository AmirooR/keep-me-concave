#pragma once

#include "line.hpp"
#include <vector>
#include <iostream>


using namespace std;


class KeepMeConcave
{
        vector<LineSegment> segments;
        double lambda_min;
        double lambda_max;
        double min_lambda_min; // value at lambda_min
        double min_lambda_max; // value at lambda_max
    public:
        
        KeepMeConcave( double lambda_min_, double lambda_max_):lambda_min(lambda_min_),lambda_max(lambda_max_), min_lambda_min(-MINUS_INFINITY), min_lambda_max(-MINUS_INFINITY)
        {
            assert( lambda_min < lambda_max );
            LineSegment l1( 0, 0, lambda_min, lambda_min, true );
            LineSegment l2( 0, 0, lambda_max, lambda_max, true );

            segments.push_back(l1);
            segments.push_back(l2);
        }

        vector<LineSegment> getSegments() const
        {
            return segments;
        }

        void addLineSegment( LineSegment& l1 )
        {
            num_intersections = 0;
                        
            // find intersections
            for(size_t i = 0; i < segments.size(); i++)
            {
                double result;
                bool isValid;
                if( l1.isTheSame( segments[i] ) ) //Two same lines doesn't need to be checked, TODO check this
                {
                    //cerr<<"Two same Lines"<<endl;
                    return;
                }
                isValid = l1.intersects( segments[i], result );
                if( isValid )
                {
                    //cerr<<"Valid intersection: @lambda = "<<result<<endl;
                    if( result == lambda_min) // intersects at lambda_min
                    {
                        l1.evaluate( lambda_min, result );
                        //cerr<< "min_lambda_min: " << min_lambda_min << endl;
                        if( result <= min_lambda_min ) // it is smaller than the current value. So, we should choose it
                        {
                            //cerr<<"result <= min_lambda_min"<<endl;
                            intersecting_lambda[num_intersections] = lambda_min;
                            intersecting_energies[num_intersections] = result;
                            intersecting_indexes[num_intersections] = i;
                            min_lambda_min = result;
                            num_intersections++;
                        }
                    }
                    else if( result == lambda_max) // intersects at lambda_max
                    {
                        l1.evaluate( lambda_max, result );
                        //cerr<< "min_lambda_max: "<<min_lambda_max << endl;
                        if( result <= min_lambda_max ) // smaller than the current value. So, we should choose it
                        {
                            //cerr << "result <= min_lambda_max"<<endl;
                            intersecting_lambda[num_intersections] = lambda_max;
                            intersecting_energies[num_intersections] = result;
                            intersecting_indexes[num_intersections] = i;
                            min_lambda_max = result;
                            num_intersections++;
                        }
                    }
                    else // intersects with other lines
                    { 
                        double intersecting_energy;                       
                        l1.evaluate( result, intersecting_energy );
                        intersecting_lambda[num_intersections] = result;
                        intersecting_energies[num_intersections] = intersecting_energy;
                        intersecting_indexes[num_intersections] = i;
                        num_intersections++;
                    }
                }
            }

            // Intersections are found. Now, remove the line segments above and add the new line segment
            if( num_intersections > 1 && (intersecting_lambda[0] != intersecting_lambda[num_intersections -1]))//TODO check assuming no vertical line will be created
            { // find two unique intersecting points ( since I keep it sorted, the first and last indexes are OK )
                segments[ intersecting_indexes[0] ].lambda_max = intersecting_lambda[0];
                segments[ intersecting_indexes[ num_intersections - 1]].lambda_min = intersecting_lambda[ num_intersections - 1];
                if( intersecting_indexes[ num_intersections - 1] - intersecting_indexes[ 0 ] > 1 ) // there exist some lines to remove
                    segments.erase( segments.begin() + intersecting_indexes[0]+1, segments.begin() + intersecting_indexes[ num_intersections -1 ]);
                // insert the new segment
                LineSegment newLine( l1.m, l1.b, intersecting_lambda[0], intersecting_lambda[ num_intersections - 1], l1.isVertical);
                segments.insert( segments.begin() + intersecting_indexes[0] + 1, newLine );
            }

        }
    public: //These for variables might be needed from outside :-/ 
        int num_intersections;

        double intersecting_lambda[4]; // it should be two points, but some times it passes through the
                                          // vertex of the concave function. So, two intersections can be found 
                                          // at a single point (left, right line segments) TODO check this
        double intersecting_energies[4];
        int intersecting_indexes[4];
        friend ostream& operator<<(ostream& os, const KeepMeConcave& k);
};

ostream& operator<<(ostream& os, const KeepMeConcave& k)
{
    vector<LineSegment> segments = k.getSegments();
    for(size_t i = 0; i < segments.size(); i++)
        os<< segments[i] << endl;
    return os;
}

