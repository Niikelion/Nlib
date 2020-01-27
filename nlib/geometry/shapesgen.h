#ifndef SHAPESGEN_H
#define SHAPESGEN_H

#include <nlib\geometry\triangle.h>

#include <vector>

namespace Nlib
{
    namespace Sgen
    {
        std::vector<Triangle> subdivide(std::vector<Triangle>);
        std::vector<Triangle> smoothsubdivide(std::vector<Triangle>,const Point3D&);

        std::vector<Triangle> icosahedron   (const double& scale);
        std::vector<Triangle> geosphere     (const double& scale,const unsigned int& depth);
    }
}

#endif // SHAPESGEN_H
