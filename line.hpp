#pragma once

#define MINUS_INFINITY -9.9e20f

#define MAX(X,Y) ( (X)>(Y)?(X):(Y) )
#define MIN(X,Y) ( (X)>(Y)?(Y):(X) )

#include <cassert>
using namespace std;

typedef struct LineSegment
{
    float m;
    float b;
    float lambda_min;
    float lambda_max;
    bool isVertical;

    LineSegment(float m_, float b_, float lambda_min_, float lambda_max_, bool isVertical_ = false):m(m_),b(b_),lambda_min(lambda_min_), lambda_max(lambda_max_), isVertical(isVertical_)
    {
        assert( lambda_min <= lambda_max );
    }

    bool evaluate(float lambda, float& result)
    {//TODO: test
        if(isVertical)
        {
            result = MINUS_INFINITY;
            if(lambda == lambda_min)
                return true;
            else
                return false;
        }

        result = m*lambda+b;
        return (lambda >= lambda_min && lambda <= lambda_max)?true:false;
    }

    bool intersects(LineSegment& line, float& result_lambda)
    {
        if(isVertical && line.isVertical )
        {
            result_lambda = lambda_min;
            if( lambda_min == line.lambda_min)
                return true;
            else
                return false;
        }
        if(line.m == m)
        {
            if(line.b == b)
            {//two identical lines,TODO check if this happens!
                result_lambda = lambda_min;
                return true;
            }
            else
            {//two parallel lines
                result_lambda = MINUS_INFINITY;
                return false;
            }
        }

        result_lambda = ( line.b - b) / (m - line.m);
        float intersect_min_lambda = MAX( lambda_min, line.lambda_min );
        float intersect_max_lambda = MIN( lambda_max, line.lambda_max );
        if( result_lambda >= intersect_min_lambda && result_lambda <= intersect_max_lambda)
            return true;
        else return false;
    }
}LineSegment;

bool intersects(LineSegment& l1, LineSegment& l2, float& result)
{
    return l1.intersects( l2, result);
}
