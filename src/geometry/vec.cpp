#include <nlib/geometry/vec.h>
namespace Nlib
{
    ///------------------------------------------------------Vec2
    Vec2 Vec2::unit() const noexcept
    {
        return std::move((*this)/(!*this));
    }

    double Vec2::length() const noexcept
    {
        return std::move(sqrt(x*x+y*y));
    }

    double Vec2::dot(const Vec2& target) const noexcept
    {
        return std::move(x*target.x+y*target.y);
    }

    double Vec2::perpp(const Vec2& target) const noexcept
    {
        return std::move(x*target.y-y*target.x);
    }

    double Vec2::angle(const Vec2& target) const noexcept
    {
        return acos(dot(target)/(length()*!target));
    }

    double Vec2::cos(const Vec2& target) const noexcept
    {
        return dot(target)/(length()*!target);
    }

    double Vec2::sin(const Vec2& target) const noexcept
    {
        return perp(target)/(length()*!target);
    }

    bool Vec2::perp(const Vec2& target) const noexcept
    {
        return (x==target.y && y==-target.x) || (x==-target.y && y==target.x);
    }

    double Vec2::operator !() const noexcept
    {
        return std::move(sqrt(x*x+y*y));
    }

    bool Vec2::operator == (const Vec2& target) const noexcept
    {
        return x == target.x && y==target.y;
    }

    bool Vec2::operator != (const Vec2& target) const noexcept
    {
        return x != target.x || y != target.y;
    }

    bool Vec2::parallel(const Vec2& target) const noexcept
    {
        return target.unit() == unit();
    }

    Vec2 & Vec2::operator = (const std::initializer_list<double>& l) noexcept
    {
        const std::size_t size=l.size();
        const double* beg=l.begin();
        if (size>0)
        {
            x=beg[0];
            if (size>1)
                y=beg[1];
        }
        return *this;
    }

    Vec2 & Vec2::operator = (const std::vector<double>& l) noexcept
    {
        const std::size_t size = l.size();
        const double* beg = &(*l.begin());
        if (size>0)
        {
            x=beg[0];
            if (size>1)
                y=beg[1];
        }
        return *this;
    }

    Vec2 & Vec2::operator += (const Vec2& target) noexcept
    {
        x+=target.x;
        y+=target.y;
        return *this;
    }

    Vec2 Vec2::operator + (const Vec2& target) const noexcept
    {
        return std::move(Vec2(x+target.x,y+target.y));
    }

    Vec2 & Vec2::operator -= (const Vec2& target) noexcept
    {
        x-=target.x;
        y-=target.y;
        return *this;
    }

    Vec2 Vec2::operator - (const Vec2& target) const noexcept
    {
        return std::move(Vec2(x-target.x,y-target.y));
    }

    Vec2 Vec2::operator - () const noexcept
    {
        return std::move(Vec2(-x,-y));
    }

    Vec2 & Vec2::operator *= (const double& a) noexcept
    {
        x*=a;
        y*=a;
        return *this;
    }

    Vec2 Vec2::operator * (const double& a) const noexcept
    {
        return std::move(Vec2(x*a,y*a));
    }

    Vec2 & Vec2::operator /= (const double& a) noexcept
    {
        x/=a;
        y/=a;
        return *this;
    }
    Vec2 Vec2::operator / (const double& a) const noexcept
    {
        return std::move(Vec2(x/a,y/a));
    }

    Vec2::Vec2() noexcept
    {
        x=0;
        y=0;
    }
    Vec2::Vec2(const double& _x,const double& _y) noexcept
    {
        x=_x;
        y=_y;
    }

    Vec2::Vec2(const std::initializer_list<double>& l) noexcept
    {
        const std::size_t size=l.size();
        const double* beg=l.begin();
        if (size>0)
        {
            x=beg[0];
            if (size>1)
                y=beg[1];
        }
    }

    Vec2::Vec2(const std::vector<double>& l) noexcept
    {
        const std::size_t size = l.size();
        const double* beg = &(*l.begin());
        if (size>0)
        {
            x=beg[0];
            if (size>1)
                y=beg[1];
        }
    }


    ///------------------------------------------------------Vec3
    Vec3 Vec3::unit() const noexcept
    {
        return std::move((*this)/(!*this));
    }
    double Vec3::dot(const Vec3& target) const noexcept
    {
        return std::move(x*target.x+y*target.y+z*target.z);
    }
    double Vec3::length() const noexcept
    {
        return std::move(sqrt(x*x+y*y+z*z));
    }
    Vec3 Vec3::cross(const Vec3& target) const noexcept
    {
        return std::move(Vec3(y*target.z-z*target.y,z*target.x-x*target.z,x*target.y-y*target.x));
    }
    double Vec3::operator !() const noexcept
    {
        return std::move(sqrt(x*x+y*y+z*z));
    }

    bool Vec3::operator == (const Vec3& target) const noexcept
    {
        return x == target.x && y == target.y && z == target.z;
    }

    bool Vec3::operator != (const Vec3& target) const noexcept
    {
        return x != target.x || y != target.y || z != target.z;
    }

    bool Vec3::parallel(const Vec3& target) const noexcept
    {
        return target.unit() == unit();
    }

    bool Vec3::perp(const Vec3& target) const noexcept
    {
        return cos(target) == static_cast<double>(0);
    }

    double Vec3::angle(const Vec3& target) const noexcept
    {
        return std::acos(dot(target)/(length()*!target));
    }

    double Vec3::sin(const Vec3& target) const noexcept
    {
        return (!cross(target))/(length()*!target);
    }

    double Vec3::cos(const Vec3& target) const noexcept
    {
        return dot(target)/(length()*!target);
    }

    Vec3 & Vec3::operator = (const std::initializer_list<double>& l) noexcept
    {
        const std::size_t size=l.size();
        const double* beg=l.begin();
        if (size>0)
        {
            x=beg[0];
            if (size>1)
            {
                y=beg[1];
                if (size>2)
                    z=beg[2];
            }
        }
        return *this;
    }

    Vec3 & Vec3::operator = (const std::vector<double>& l) noexcept
    {
        const std::size_t size = l.size();
        const double* beg = &(*l.begin());
        if (size>0)
        {
            x=beg[0];
            if (size>1)
            {
                y=beg[1];
                if (size>2)
                    z=beg[2];
            }
        }
        return *this;
    }

    Vec3 & Vec3::operator += (const Vec3& target) noexcept
    {
        x+=target.x;
        y+=target.y;
        z+=target.z;
        return *this;
    }

    Vec3 Vec3::operator + (const Vec3& target) const noexcept
    {
        return std::move(Vec3(x+target.x,y+target.y,z+target.z));
    }

    Vec3 & Vec3::operator -= (const Vec3& target) noexcept
    {
        x-=target.x;
        y-=target.y;
        z-=target.z;
        return *this;
    }

    Vec3 Vec3::operator - (const Vec3& target) const noexcept
    {
        return std::move(Vec3(x-target.x,y-target.y,z-target.z));
    }

    Vec3 Vec3::operator - () const noexcept
    {
        return std::move(Vec3(-x,-y,-z));
    }

    Vec3 & Vec3::operator *= (const double& a) noexcept
    {
        x*=a;
        y*=a;
        z*=a;
        return *this;
    }

    Vec3 & Vec3::operator *= (const Vec3& target) noexcept
    {
        x*=target.x;
        y*=target.y;
        z*=target.z;
        return *this;
    }

    Vec3 Vec3::operator * (const double& a) const noexcept
    {
        return std::move(Vec3(x*a,y*a,z*a));
    }

    Vec3 Vec3::operator * (const Vec3& target) const noexcept
    {
        return std::move(Vec3(x*target.x,y*target.y,z*target.z));
    }

    Vec3 & Vec3::operator /= (const double& a) noexcept
    {
        x/=a;
        y/=a;
        z/=a;
        return *this;
    }
    Vec3 Vec3::operator / (const double& a) const noexcept
    {
        return std::move(Vec3(x/a,y/a,z/a));
    }

    Vec3::Vec3() noexcept :Vec2()
    {
        z=0;
    }
    Vec3::Vec3(const double& _x,const double& _y,const double& _z) noexcept :Vec2(_x,_y)
    {
        z=_z;
    }

    Vec3::Vec3(const std::initializer_list<double>& l) noexcept
    {
        const std::size_t size=l.size();
        const double* beg=l.begin();
        if (size>0)
        {
            x=beg[0];
            if (size>1)
            {
                y=beg[1];
                if (size>2)
                    z=beg[2];
            }
        }
    }

    Vec3::Vec3(const std::vector<double>& l) noexcept
    {
        const std::size_t size = l.size();
        const double* beg = &(*l.begin());
        if (size>0)
        {
            x=beg[0];
            if (size>1)
            {
                y=beg[1];
                if (size>2)
                    z=beg[2];
            }
        }
    }

    std::ostream& operator << (std::ostream& stream,const Vec2& a)
    {
        return stream << "[" << a.x << "," << a.y << "]";
    }
    std::ostream& operator << (std::ostream& stream,const Vec3& a)
    {
        return stream << "[" << a.x << "," << a.y << "," << a.z << "]";
    }
}

//
