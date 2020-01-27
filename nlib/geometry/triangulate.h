#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED

#include<vector>
#include<cinttypes>

#include<nlib/geometry/vec.h>

namespace Nlib
{
    template<typename T>bool signu(T x)
    {
        return (x > 0) - (x < 0);
    }

    class Triangle2D
    {
    public:
        Vec2 points[3];
    };

    double sign (Vec2 p1, Vec2 p2, Vec2 p3);

    bool pointInTriangle (Vec2 pt, Vec2 v1, Vec2 v2, Vec2 v3);

    double getVectorsAngle(Vec2 vec1,Vec2 vec2);

    bool checkEar(Vec2 f1, Vec2 f2, Vec2 f3);

    std::size_t findEar(Vec2 poly[],std::size_t sizeOfPoly);

    std::vector<Triangle2D> triangulation (std::vector<Vec2>polygon);



    std::vector<Vec3> triangulate(std::vector<Vec3>poly);
    std::vector<Vec3> triangulateFace(std::vector<Vec3>poly);
}

#endif // PHYSICS_H_INCLUDED
