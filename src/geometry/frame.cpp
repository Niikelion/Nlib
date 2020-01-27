#include <nlib/geometry/frame.h>

namespace Nlib
{
    double getDet(double matrix[][3]) noexcept
    {
        return matrix[0][0]*matrix[1][1]*matrix[2][2]+
                matrix[1][0]*matrix[2][1]*matrix[0][2]+
                matrix[2][0]*matrix[0][1]*matrix[1][2]-
                matrix[2][0]*matrix[1][1]*matrix[0][2]-
                matrix[1][0]*matrix[0][1]*matrix[2][2]-
                matrix[0][0]*matrix[2][1]*matrix[1][2];
    }


    Point3D Frame::center() const noexcept
    {
        double matrix[3][3],submatrix[3][3];


        if (std::abs(x.vn().cos(y.vn()))<0.001 &&
            std::abs(x.vn().cos(z.vn()))<0.001 &&
            std::abs(y.vn().cos(z.vn()))<0.001)
        {
            matrix[0][0]=x.vn().x;
            matrix[1][0]=x.vn().y;
            matrix[2][0]=x.vn().z;

            matrix[0][1]=y.vn().x;
            matrix[1][1]=y.vn().y;
            matrix[2][1]=y.vn().z;

            matrix[0][2]=z.vn().x;
            matrix[1][2]=z.vn().y;
            matrix[2][2]=z.vn().z;

            double det=getDet(matrix);

            for (unsigned int i=0; i<3; ++i)
                for (unsigned int j=0; j<3; ++j)
                    submatrix[i][j]=matrix[i][j];

            submatrix[0][0]=x.ds();
            submatrix[0][1]=y.ds();
            submatrix[0][2]=z.ds();

            Point3D ret;
            ret.x=getDet(submatrix)/det;

            for (unsigned int i=0; i<3; ++i)
                for (unsigned int j=0; j<3; ++j)
                    submatrix[i][j]=matrix[i][j];

            submatrix[1][0]=x.ds();
            submatrix[1][1]=y.ds();
            submatrix[1][2]=z.ds();

            ret.y=getDet(submatrix)/det;

            for (unsigned int i=0; i<3; ++i)
                for (unsigned int j=0; j<3; ++j)
                    submatrix[i][j]=matrix[i][j];

            submatrix[2][0]=x.ds();
            submatrix[2][1]=y.ds();
            submatrix[2][2]=z.ds();

            ret.z=getDet(submatrix)/det;

            return ret;
        }
        return Point3D(0,0,0);
    }

    Point3D Frame::relative(const Point3D& a) const noexcept
    {
        return Point3D(x.offset(a),y.offset(a),z.offset(a));
    }

    Point3D Frame::outside(const Point3D& a)const noexcept
    {
        return x.vn()*a.x+y.vn()*a.y+z.vn()*a.z+center();
    }

    Frame::Frame() noexcept:    x(Plane(Point3D(0,0,0),Vec3(1,0,0))),
                                y(Plane(Point3D(0,0,0),Vec3(0,1,0))),
                                z(Plane(Point3D(0,0,0),Vec3(0,0,1)))
    {/**/}

    Frame::Frame(const Plane& a,const Plane& b,const Plane& c) noexcept: x(a), y(b), z(c)
    {/**/}
    Frame::Frame(const Vec3& a,const Vec3& b, const Vec3& c,const Point3D& center) noexcept: x(Plane(center,a)), y(Plane(center,b)), z(Plane(center,c))
    {/**/}
}

//
