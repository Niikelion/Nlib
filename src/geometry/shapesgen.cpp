#include "shapesgen.h"

namespace Nlib
{
    namespace Sgen
    {
        std::vector<Triangle> subdivide(std::vector<Triangle>g)
        {
            Vec3 a,b,c;
            std::vector<Triangle>ret;
            ret.reserve(g.size()*3);
            for (const auto& i:g)
            {
                a=i.points[0].v3();
                b=i.points[1].v3();
                c=i.points[2].v3();

                ret.push_back(Triangle(a,(a+b)/2,(a+c)/2));
                ret.push_back(Triangle(b,(a+b)/2,(b+c)/2));
                ret.push_back(Triangle(c,(a+c)/2,(b+c)/2));
                ret.push_back(Triangle((b+c)/2,(a+b)/2,(a+c)/2));
            }
            return std::move(ret);
        }
        std::vector<Triangle> smoothsubdivide(std::vector<Triangle>g,const Point3D& center)
        {
            Vec3 a,b,c,a1,b1,c1;
            std::vector<Triangle>ret;
            ret.reserve(g.size()*3);
            for (const auto& i:g)
            {
                a=i.points[0].v3();
                b=i.points[1].v3();
                c=i.points[2].v3();

                a1=((a+b)/2).unit()*(center.dist(a)+center.dist(b))/2;
                b1=((b+c)/2).unit()*(center.dist(b)+center.dist(c))/2;
                c1=((c+a)/2).unit()*(center.dist(c)+center.dist(a))/2;

                ret.push_back(Triangle(a,a1,c1));
                ret.push_back(Triangle(b,a1,b1));
                ret.push_back(Triangle(c,c1,b1));
                ret.push_back(Triangle(b1,a1,c1));
            }
            return std::move(ret);
        }

        std::vector<Triangle> icosahedron(const double &scale)
        {
            std::vector<Triangle> ret;

            const double X = 0.525731112119133606d;
            const double Z = 0.850650808352039932d;
            const double N = 0.0d;

            static const std::vector<Point3D> vertices=
            {
              {-X,N,Z}, {X,N,Z}, {-X,N,-Z}, {X,N,-Z},
              {N,Z,X}, {N,Z,-X}, {N,-Z,X}, {N,-Z,-X},
              {Z,X,N}, {-Z,X, N}, {Z,-X,N}, {-Z,-X, N}
            };
            static const std::vector<Point3D> triangles=
            {
              {0,4,1},{0,9,4},{9,5,4},{4,5,8},{4,8,1},
              {8,10,1},{8,3,10},{5,3,8},{5,2,3},{2,7,3},
              {7,10,3},{7,6,10},{7,11,6},{11,0,6},{0,1,6},
              {6,1,10},{9,0,11},{9,11,2},{9,2,5},{7,2,11}
            };

            ret.reserve(triangles.size());

            for (const auto& i:triangles)
            {
                ret.push_back(Triangle(vertices[(int)i.x] * scale,vertices[(int)i.y] * scale,vertices[(int)i.z] * scale));
            }
            return std::move(ret);
        }

        std::vector<Triangle> geosphere(const double& scale,const unsigned int& depth)
        {
            std::vector<Triangle>ret = std::move(icosahedron(scale));
            for (unsigned int i=0; i<depth; ++i)
            {
                ret = std::move(smoothsubdivide(ret,Point3D()));
            }
            return std::move(ret);
        }
    }
}
