#include <nlib/utility/premath.h>

namespace Nlib
{
    float Epsilon(const float& m) noexcept
    {
        float approx = 1.0f;
        float lastApprox = 0.0f;
        while (m+approx != m)
        {
            lastApprox = approx;
            approx /= 2.0f;
        }
        return lastApprox;
    }
    double Epsilon(const double& m) noexcept
    {
        double approx = 1.0d;
        double lastApprox = 0.0d;
        while (m+approx != m)
        {
            lastApprox = approx;
            approx /= 2.0d;
        }
        return lastApprox;
    }
}
