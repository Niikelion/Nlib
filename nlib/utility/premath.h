#ifndef PREMATH_H_INCLUDED
#define PREMATH_H_INCLUDED

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif // _USE_MATH_DEFINES

#include <cmath>

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif // M_PI

namespace Nlib
{
    constexpr float __eps_sub(const float&,const float&,const float&) noexcept;
    constexpr double __eps_sub(const double&,const double&,const double&) noexcept;

    float Epsilon(const float&) noexcept;
    constexpr float Epsilon_c(const float&) noexcept;
    double Epsilon(const double&) noexcept;
    constexpr double Epsilon_c(const double&) noexcept;

    constexpr float __eps_sub(const float& m,const float& lastApprox,const float& approx) noexcept
    {
        return (m+approx == m) ? lastApprox : __eps_sub(m,approx,approx/2.0f);
    }

    constexpr double __eps_sub(const double& m,const double& lastApprox,const double& approx) noexcept
    {
        return (m+approx == m) ? lastApprox : __eps_sub(m,approx,approx/2.0d);
    }

    constexpr float Epsilon_c(const float& m) noexcept
    {
        return __eps_sub(m,0.0f,1.0f);
    }
    constexpr double Epsilon_c(const double& m) noexcept
    {
        return __eps_sub(m,0.0d,1.0d);
    }
}

#endif // PREMATH_H_INCLUDED
