#include <nlib/geometry/triangulate.h>

namespace Nlib
{

    double sign (Vec2 p1, Vec2 p2, Vec2 p3)
    {
        Vec2 pdif1 = p1-p3,pdif2=p2-p3;
        return pdif1.x * pdif2.y - pdif2.x * pdif1.y;
    }
    bool pointInTriangle (Vec2 pt, Vec2 v1, Vec2 v2, Vec2 v3)
    {
        bool b1, b2, b3;

        b1 = sign(pt, v1, v2) < 0.0d;
        b2 = sign(pt, v2, v3) < 0.0d;
        b3 = sign(pt, v3, v1) < 0.0d;

        return ((b1 == b2) && (b1 == b3));
    }
    double getVectorsAngle(Vec2 v1,Vec2 v2)
    {
        return acos( v1.dot(v2) / ( (!v1) * (!v2) ) );
    }
    bool checkEar(Vec2 f1, Vec2 f2, Vec2 f3)
    {
        Vec2 vec1=f3-f2,vec2=f1-f2;
        return (vec1.x*vec2.y > vec1.y*vec2.x);
    }
    std::size_t findEar(Vec2 poly[],std::size_t sizeOfPoly)
    {
        bool inp=false;
        for(std::size_t i=0; i<sizeOfPoly-2; ++i)
            if(!checkEar(poly[i], poly[i+1], poly[i+2]))
            {
                for(std::size_t j=0; j<sizeOfPoly; ++j)
                    if(pointInTriangle(poly[j], poly[i], poly[i+1], poly[i+2]) && (j<i || j>i+2))
                        inp = true;
                if(!inp)
                    return i+1;
            }
        return 0;
    }
    std::vector<Triangle2D> triangulation (std::vector<Vec2>polygon)
    {
        std::vector<Triangle2D> triangles;
        Triangle2D triangle;
        std::size_t index=0;
        while(polygon.size() > 3)
        {
            index = findEar(polygon.data(), polygon.size());
            if(index)
            {
                triangle.points[0] = polygon[index - 1];
                triangle.points[1] = polygon[index    ];
                triangle.points[2] = polygon[index + 1];
                triangles.push_back(triangle);

                polygon.erase(polygon.begin() +index);
            }
        }
        triangle.points[0] = polygon[0];
        triangle.points[1] = polygon[1];
        triangle.points[2] = polygon[2];
        triangles.push_back(triangle);

        return triangles;
    }

    std::vector<Vec3> triangulateFace(std::vector<Vec3>poly)
    {
        std::vector<Vec3>tris;
        if (poly.size()<=3)
            return std::move(poly);
        Vec3 norm=(poly[1]-poly[0]).cross(poly[2]-poly[0]).unit();
        double d=-norm.dot(poly[0]);
        double dd=0;
        Vec3 crs,v[3];
        //direction

        double deg=0;
        for (unsigned int i=0; i<poly.size(); ++i)
        {
            v[0]=poly[i];
            v[1]=poly[(i+1)%poly.size()];
            v[2]=poly[(i+2)%poly.size()];
            crs=(v[1]-v[0]).cross(v[2]-v[1]);
            dd=(norm.dot(crs))/norm.length();

            dd=(v[1]-v[0]).dot(v[2]-v[1]) / (!(v[1]-v[0]) + !(v[2]-v[1]));



            deg+=std::acos( signu(dd) * ( (v[1]-v[0]).dot(v[2]-v[1]) / (!(v[1]-v[0]) + !(v[2]-v[1])) ) );
        }
        if (deg<0)
        {
            norm*=-1;
            d*=-1;
        }

        bool rep=true;
        //cut irregular triangles, make convex shape
        while (rep)
        {
            rep=false;
            for (unsigned int i=0; i<poly.size(); ++i)
            {
                v[0]=poly[i];
                v[1]=poly[(i+1)%poly.size()];
                v[2]=poly[(i+2)%poly.size()];
                crs=(v[1]-v[0]).cross(v[2]-v[1]);
                dd=(norm.dot(crs))/norm.length();

                if (dd>0.00001)
                {
                    rep=true;
                    tris.insert(tris.begin(),v,v+3);
                    poly.erase(poly.begin()+(i+1)%poly.size());
                }
            }
        }
        int i=0;
        while (poly.size()>3)
        {
            v[0]=poly[i];
            v[1]=poly[(i+1)%poly.size()];
            v[2]=poly[(i+2)%poly.size()];

            tris.insert(tris.begin(),v,v+3);
            poly.erase(poly.begin()+(i+1)%poly.size());
            ++i;
            i%=poly.size();
        }
        return std::move(tris);
    }

    std::vector<Vec3> triangulate(std::vector<Vec3>poly)
    {
        if (poly.size()<=3)
        {
            return std::move(poly);
        }

        std::vector< std::vector<Vec3> >faces;

        std::vector<Vec3>tris;

        Vec3 norm=(poly[1]-poly[0]).cross(poly[2]-poly[0]).unit();
        double d=-norm.dot(poly[0]);
        int in=-1;
        double dd=0;
        for (unsigned int i=2; i<poly.size(); ++i)
        {
            dd=(norm.dot(poly[(i+1)%poly.size()])+d)/norm.length();
            if (std::abs(dd)<=0.0001 && in>=0)
            {
                //cut&&separate
                faces.push_back(std::vector<Vec3>(poly.begin()+in,poly.begin()+i));
                faces[faces.size()-1].push_back(poly[(i+1)%poly.size()]);
                if (static_cast<unsigned int>(in+1)==i)
                    poly.erase(poly.begin()+i);
                else
                    poly.erase(poly.begin()+in+1,poly.begin()+i);
                in=-1;
            }
            else if (std::abs(dd)>0.0001)
            {
                if (in==-1)
                    in=i;
            }
        }
        if (faces.size()==0)
            return std::move(triangulateFace(std::move(poly)));
        faces.push_back(std::move(poly));

        for (auto &i:faces)
        {
            const std::vector<Vec3>&tmp=std::move(triangulateFace(std::move(i)));
            tris.insert(tris.end(),tmp.begin(),tmp.end());
        }
        return std::move(tris);
    }
}
