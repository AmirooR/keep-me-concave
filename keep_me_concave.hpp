#pragma once

#include "line.hpp"
#include <vector>

using namespace std;


class KeepMeConcave
{
        vector<LineSegment&> segments;
        float lambda_min;
        float lambda_max;
        float min_lambda_min; // value at lambda_min
        float min_lambda_max; // value at lambda_max
    public:
        
        KeepMeConcave( float lambda_min_, float lambda_max_):lambda_min(lambda_min_),lambda_max(lambda_max_), min_lambda_min(-MINUS_INFINITY), min_lambda_max(-MINUS_INFINITY)
        {
            LineSegment l1( 0, 0, lambda_min, lambda_min, true );
            LineSegment l2( 0, 0, lambda_max, lambda_max, true );

            segments.push_back(l1);
            segments.push_back(l2);
        }

        vector<LineSegment&> getSegments()
        {
            return segments;
        }

        void addLineSegment( LineSegment& l1 )
        {
            num_intersections = 0;
                        
            // find intersections
            for(size_t i = 0; i < segments.size(); i++)
            {
                float result;
                bool isValid;
                if( l1.isTheSame( segements[i] ) ) //Two same lines doesn't need to be checked, TODO check this
                    return;
                isValid = l1.intersects( segments[i], result );
                if( isValid )
                {
                    if( result == lambda_min) // intersects at lambda_min
                    {
                        l1.evaluate( lambda_min, result );
                        if( result <= min_lambda_min ) // it is smaller than the current value. So, we should choose it
                        {
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
                        if( result <= min_lambda_max ) // smaller than the current value. So, we should choose it
                        {
                            intersecting_lambda[num_intersections] = lambda_max;
                            intersecting_energies[num_intersections] = result;
                            intersecting_indexes[num_intersections] = i;
                            min_lambda_max = result;
                            num_intersections++;
                        }
                    }
                    else // intersects with other lines
                    { 
                        float intersecting_energy;                       
                        l1.evaluate( result, intersecting_energy );
                        intersecting_lambda[num_intersections] = result;
                        intersecting_energy[num_intersections] = intersecting_energy;
                        intersecting_indexes[num_intersections] = i;
                        num_intersections++;
                    }
                }
            }

            // Intersections are found. Now, remove the line segments above and add the new line segment
            if( num_intersections > 1 )
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

        float intersecting_lambda[4]; // it should be two points, but some times it passes through the
                                          // vertex of the concave function. So, two intersections can be found 
                                          // at a single point (left, right line segments) TODO check this
        float intersecting_energies[4];
        int intersecting_indexes[4];

};