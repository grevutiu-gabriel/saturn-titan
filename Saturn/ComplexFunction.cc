// 
// File:   ComplexFunction.cc
// Author: M.R.Eggleston
// 
// Created on 19 April 2012, 14:11
//

#include <iostream>
#include <boost/math/complex/details.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include "mpreal.h"
#include "ComplexFunction.h"
#include "KeyString.h"
#include "StaticCalculatingUnit.h"
#include "Utilities.h"

using namespace boost::math;

template<>
void ComplexFunction<long double, LongComplex>::setNumbers()
{
    m_zero = 0.0L;
    m_one = 1.0L;
    m_two = 2.0L;
    m_half = 0.5L;
    m_four = 4.0L;
    m_eight = 8.0L;
    m_a_crossover = 1.5L;
    m_b_crossover = 0.6417L;
    m_pi = 3.141592653589793238462643383279502884197L;
    m_half_pi = 1.57079632679489661923132169163975144L;
    m_log_two = 0.69314718055994530941723212145817657L;
    m_quarter_pi = 0.78539816339744830961566084581987572L;
    m_inf = mpfr::const_infinity(1, BASE_PRECISION).toDouble();
    m_neg_inf = mpfr::const_infinity(-1, BASE_PRECISION).toLDouble();
}

template<>
void ComplexFunction<MpReal, MpComplex>::setNumbers()
{
    m_precision = StaticCalculatingUnit::s_precision;
    m_zero = MpReal("0", m_precision);
    m_one = MpReal("1", m_precision);
    m_two = MpReal("2", m_precision);
    m_half = MpReal("0.5", m_precision);
    m_four = MpReal("4", m_precision);
    m_eight = MpReal("8", m_precision);
    m_a_crossover = MpReal("1.5", m_precision);
    m_b_crossover = MpReal("0.6417", m_precision);
    m_pi = mpfr::const_pi(m_precision);
    m_half_pi = m_pi/MpReal("2", m_precision);
    m_log_two = mpfr::log(m_two);
    m_quarter_pi = m_pi/m_four;
    m_inf = mpfr::const_infinity(1, m_precision);
    m_neg_inf = mpfr::const_infinity(-1, m_precision);
}

template<>
LongComplex ComplexFunction<long double, LongComplex>::cfp_asin(const LongComplex& z)
{
    // adapted from boost's complex asin function
    //
    // This implementation is a transcription of the pseudo-code in:
    //
    // "Implementing the complex Arcsine and Arccosine Functions using Exception Handling."
    // T E Hull, Thomas F Fairgrieve and Ping Tak Peter Tang.
    // ACM Transactions on Mathematical Software, Vol 23, No 3, Sept 1997.
    //

    //
    // Get real and imaginary parts, discard the signs as we can 
    // figure out the sign of the result later:
    //
    long double x = std::abs(z.real());
    long double y = std::fabs(z.imag());
    long double real, imag;  // our results

    //
    // Begin by handling the special cases for infinities and nan's
    // specified in C99, most of this is handled by the regular logic
    // below, but handling it as a special case prevents overflow/underflow
    // arithmetic which may trip up some machines:
    //
    if (x != x)
    {
        if (y != y)
        {
            return LongComplex(x, x);
        }
        if (y == std::numeric_limits<long double>::infinity())
        {
            real = x;
            imag = m_inf;
        }
        else
        {
            return LongComplex(x, x);
        }
    }
    else if (y != y)
    {
        if (x == 0.0L)
        {
            real = 0.0L;
            imag = y;
        }
        else if (x != x)
        {
            real = y;
            imag = m_inf;
        }
        else
        {
            return LongComplex(y, y);
        }
    }
    else if (x != x)
    {
        if (y != y)
        {
            real = m_quarter_pi;
            imag = m_inf;
        }
        else
        {
            real = m_half_pi;
            imag = m_inf;
        }
    }
    else if (y == std::numeric_limits<long double>::infinity())
    {
        real = 0.0L;
        imag = m_inf;
   }
   else
   {
        //
        // special case for real numbers:
        //
        if ((y == 0.0L) && (x <= 1.0L))
        {
            return LongComplex(std::asin(z.real()), 0.0L);
        }
        long double safe_max = detail::safe_max(8.0L);
        long double safe_min = detail::safe_min(4.0L);

        long double xp1 = 1.0L + x;
        long double xm1 = x - 1.0L;

        if ((x < safe_max) && (x > safe_min) && (y < safe_max) && (y > safe_min))
        {
            long double yy = y * y;
            long double r = std::sqrt(xp1*xp1 + yy);
            long double s = std::sqrt(xm1*xm1 + yy);
            long double a = m_half * (r + s);
            long double b = x / a;

            if (b <= m_b_crossover)
            {
                real = std::asin(b);
            }
            else
            {
                long double apx = a + x;
                if (x <= 1.0L)
                {
                    real = std::atan(x/std::sqrt(0.5L * apx * (yy /(r + xp1) + (s-xm1))));
                }
                else
                {
                    real = std::atan(x/(y * std::sqrt(0.5L * (apx/(r + xp1) + apx/(s+xm1)))));
                }
            }

            if(a <= m_a_crossover)
            {
                long double am1;
                if (x < 1.0L)
                {
                    am1 = 0.5L * (yy/(r + xp1) + yy/(s - xm1));
                }
                else
                {
                    am1 = 0.5L * (yy/(r + xp1) + (s + xm1));
                }
                imag = log1p(am1 + std::sqrt(am1 * (a + 1.0L)));
            }
            else
            {
                imag = std::log(a + std::sqrt(a*a - 1.0L));
            }
        }
        else
        {
            //
            // This is the Hull et al exception handling code from Fig 3 of their paper:
            //
            if (y <= (std::numeric_limits<long double>::epsilon() * std::abs(xm1)))
            {
                if (x < 1.0L)
                {
                    real = std::asin(x);
                    imag = y / std::sqrt(xp1*xm1);
                }
                else
                {
                    real = m_half_pi;
                    if ((std::numeric_limits<long double>::max() / xp1) > xm1)
                    {
                        // xp1 * xm1 won't overflow:
                        imag = log1p(xm1 + std::sqrt(xp1*xm1));
                    }
                    else
                    {
                        imag = 2.0L + std::log(x);
                    }
                }
            }
            else if (y <= safe_min)
            {
                // There is an assumption in Hull et al's analysis that
                // if we get here then x == 1.  This is true for all "good"
                // machines where :
                // 
                // E^2 > 8*sqrt(u); with:
                //
                // E =  std::numeric_limits<T>::epsilon()
                // u = (std::numeric_limits<T>::min)()
                //
                // Hull et al provide alternative code for "bad" machines
                // but we have no way to test that here, so for now just assert
                // on the assumption:
                //
                BOOST_ASSERT(x == 1);
                real = m_half_pi - std::sqrt(y);
                imag = std::sqrt(y);
            }
            else if ((std::numeric_limits<long double>::epsilon() * y - 1.0L) >= x)
            {
                real = x/y; // This can underflow!
                imag = m_log_two + std::log(y);
            }
            else if(x > 1.0L)
            {
                real = std::atan(x/y);
                long double xoy = x/y;
                imag = m_log_two + std::log(y) + 0.5L * log1p(xoy*xoy);
            }
            else
            {
                long double a = std::sqrt(1.0L + y*y);
                real = x/a; // This can underflow!
                imag = m_half * log1p(2.0L*y*(y+a));
            }
        }
    }

    //
    // Finish off by working out the sign of the result:
    //
    if (z.real() < 0.0L)
    {
        real = -real;
    }
    if (z.imag() < 0.0L)
    {
        imag = -imag;
    }
    return LongComplex(real, imag);
}

template<>
LongComplex ComplexFunction<long double, LongComplex>::cfp_asinh(const LongComplex& z)
{
    // adapted from boost's complex asin function
    LongComplex r = cfp_asin(LongComplex(z.imag(),
                             isnan(z.real() != z.real()) ? z.real() : -z.real()));
    return LongComplex(r.imag() != r.imag() ? r.imag() : -r.imag(), r.real());
}

template<>
LongComplex ComplexFunction<long double, LongComplex>::cfp_atanh(const LongComplex& z)
{
     // adapted from boost's complex atanh function
    //

    long double x = std::abs(z.real());
    long double y = std::abs(z.imag());

    long double real = 0.0L;
    long double imag = 0.0L;

    long double safe_upper = detail::safe_max(2.0L);
    long double safe_lower = detail::safe_min(2.0L);

    //
    // Begin by handling the special cases specified in C99:
    //
    if (x != x)
    {
        if (y != y)
        {
            return LongComplex(x, x);
        }
        else if (y != y)
        {
            return LongComplex(0.0L, ((z.imag() < 0.0L) ? -m_half_pi : m_half_pi));
        }
        else
        {
            return LongComplex(x, x);
        }
    }
    else if (y != y)
    {
        if (x == 0.0L)
        {
            return LongComplex(x, y);
        }
        if (mpfr::isinf(x))
        {
            return LongComplex(0.0L, y);
        }
        else
        {
            return LongComplex(y, y);
        }
    }
    else if ((x > safe_lower) && (x < safe_upper) && (y > safe_lower) && (y < safe_upper))
    {
        long double xx = x*x;
        long double yy = y*y;
        long double x2 = x * 2.0L;
        ///
        // The real part is given by:
        // 
        // real(atanh(z)) == log((1 + x^2 + y^2 + 2x) / (1 + x^2 + y^2 - 2x))
        // 
        // However, when x is either large (x > 1/E) or very small
        // (x < E) then this effectively simplifies
        // to log(1), leading to wildly inaccurate results.  
        // By dividing the above (top and bottom) by (1 + x^2 + y^2) we get:
        //
        // real(atanh(z)) == log((1 + (2x / (1 + x^2 + y^2))) / (1 - (-2x / (1 + x^2 + y^2))))
        //
        // which is much more sensitive to the value of x, when x is not near 1
        // (remember we can compute log(1+x) for small x very accurately).
        //
        // The cross-over from one method to the other has to be determined
        // experimentally, the value used below appears correct to within a 
        // factor of 2 (and there are larger errors from other parts
        // of the input domain anyway).
        //
        long double alpha = 2.0L*x / (1.0L + xx + yy);
        if (alpha < m_a_crossover)
        {
            real = log1p(alpha) - log1p(-alpha);
        }
        else
        {
            auto xm1 = x - 1.0;
            real = log1p(x2 + xx + yy) - std::log(xm1*xm1 + yy);
        }
        real /= m_four;
        if (z.real() < 0.0L)
        {
            real = -real;
        }
        imag = std::atan2((y * 2.0L), (1.0L - xx - yy));
        imag /= 2.0L;
        if(z.imag() < 0.0L)
        {
            imag = -imag;
        }
    }
    else
    {
        //
        // This section handles exception cases that would normally cause
        // underflow or overflow in the main formulas.
        //
        // Begin by working out the real part, we need to approximate
        //    alpha = 2x / (1 + x^2 + y^2)
        // without either overflow or underflow in the squared terms.
        //
        auto alpha = 1.0L;
        if (x >= safe_upper)
        {
            // this is really a test for infinity, 
            // but we may not have the necessary numeric_limits support:
            if ((x > std::numeric_limits<long double>::max()) ||
                (y > std::numeric_limits<long double>::max()))
            {
                alpha = m_zero;
            }
            else if (y >= safe_upper)
            {
                // Big x and y: divide alpha through by x*y:
                alpha = (2.0L/y) / (x/y + y/x);
            }
            else if(y > 1.0L)
            {
                // Big x: divide through by x:
                alpha = 2.0L / (x + y*y/x);
            }
            else
            {
                // Big x small y, as above but neglect y^2/x:
                alpha = 2.0L/x;
            }
        }
        else if (y >= safe_upper)
        {
            if (x > 1.0L)
            {
                // Big y, medium x, divide through by y:
                alpha = (2.0L*x/y) / (y + x*x/y);
            }
            else
            {
                // Small x and y, whatever alpha is, it's too small to calculate:
                alpha = 0.0L;
            }
        }
        else
        {
            // one or both of x and y are small, calculate divisor carefully:
            auto div = 1.0L;
            if (x > safe_lower)
            {
                div += x*x;
            }
            if (y > safe_lower)
            {
                div += y*y;
            }
            alpha = 2.0L*x/div;
        }
        if (alpha < m_a_crossover)
        {
            real = log1p(alpha) - log1p(-alpha);
        }
        else
        {
            // We can only get here as a result of small y and medium sized x,
            // we can simply neglect the y^2 terms:
            BOOST_ASSERT(x >= safe_lower);
            BOOST_ASSERT(x <= safe_upper);
            //BOOST_ASSERT(y <= safe_lower);
            auto xm1 = x - 1.0L;
            real = std::log(1.0L + 2.0L*x + x*x) - std::log(xm1*xm1);
        }
        real /= m_four;
        if (z.real() < 0.0L)
        {
            real = -real;
        }
        //
        // Now handle imaginary part, this is much easier,
        // if x or y are large, then the formula:
        //    atan2(2y, 1 - x^2 - y^2)
        // evaluates to +-(PI - theta) where theta is negligible compared to PI.
        //
        if ((x >= safe_upper) || (y >= safe_upper))
        {
            imag = m_pi;
        }
        else if (x <= safe_lower)
        {
            //
            // If both x and y are small then atan(2y),
            // otherwise just x^2 is negligible in the divisor:
            //
            if (y <= safe_lower)
            {
                imag = std::atan2(2.0L*y, 1.0L);
            }
            else
            {
                if ((y == 0.0L) && (x == 0.0L))
                {
                    imag = 0.0L;
                }
                else
                {
                    imag = std::atan2(2.0L*y, 1.0L - y*y);
                }
            }
        }
        else
        {
            //
            // y^2 is negligible:
            //
            if ((y == 0.0L) && (x == 1.0L))
            {
                imag = 0.0L;
            }
            else
            {
                imag = std::atan2(2.0L*y, 1.0L - x*x);
            }
        }
        imag /= 2.0L;
        if (z.imag() < 0.0L)
        {
            imag = -imag;
        }
    }
   return LongComplex(real, imag);
}

template<>
LongComplex ComplexFunction<long double, LongComplex>::cfp_atan(const LongComplex& z)
{
    // adapted from boost's complex atan function
    //
    // We're using the C99 definition here; atan(z) = -i atanh(iz):
    //
    if (z.real() == 0.0L)
    {
        if (z.imag() == 1.0L)
        {
            return LongComplex(1.0, std::numeric_limits<long double>::infinity());
        }
        if (z.imag() == -1.0L)
        {
            return LongComplex(1.0, -std::numeric_limits<long double>::infinity());
        }
    }
    auto r = cfp_atanh(LongComplex(z.imag() != z.imag() ? z.imag() : -z.imag(), z.real()));
    return LongComplex(r.imag(), r.real() != r.real() ? r.real() : -r.real());
}


template<>
void ComplexFunction<long double, LongComplex>::setSize(long double size)
{
    m_size = size/2.0L;
    m_size_squared = m_size*m_size;
}

template<>
void ComplexFunction<MpReal, MpComplex>::setSize(MpReal size)
{
    m_size = size/m_two;
    m_size_squared = m_size*m_size;
}

template<>
void ComplexFunction<long double, LongComplex>::setRotation(int r)
{
    // convert to radians ...
    m_rotation = m_two*m_pi*(static_cast<long double>(r)/360.0L);
    m_sintheta = sin(m_rotation);
    m_costheta = cos(m_rotation);
}

template<>
void ComplexFunction<MpReal, MpComplex>::setRotation(int r)
{
    // convert to radians ...
    int precision = StaticCalculatingUnit::s_precision;
    MpReal rotation(r, precision);
    MpReal threesixty("360", precision);
    m_rotation = (m_two*m_pi*rotation)/threesixty;
    m_sintheta = sin(m_rotation);
    m_costheta = cos(m_rotation);
}

template<>
void ComplexFunction<long double, LongComplex>::setFunction(const std::string &f)
{
    if (!f.empty())
    {
        KeyString keys(f);
        m_pair = (keys.GetKey("pair", "n") == "y");
        if (m_pair)
        {
            auto rid = static_cast<FUNCTION_PARAMETER>(keys.GetKeyAsInt("rid", 0));
            auto iid = static_cast<FUNCTION_PARAMETER>(keys.GetKeyAsInt("iid", 0));
            setFunction(rid, iid);
            if (hasParameter(rid))
            {
                m_real.setParameter(keys.GetKeyAsLongDouble("r", 0.0L));
            }
            m_imaginary.setFunction(iid);
            if (hasParameter(iid))
            {
                m_imaginary.setParameter(keys.GetKeyAsLongDouble("i", 0.0L));
            }
        }
        else
        {
            setFunction(static_cast<COMPLEX_FUNCTION_PARAMETER>(keys.GetKeyAsInt("id", 0)));
            if (hasParameter(m_id))
            {
                long double real = keys.GetKeyAsLongDouble("r", 0.0L);
                long double imaginary = keys.GetKeyAsLongDouble("i", 0.0L);
                m_cp = LongComplex(real, imaginary);
            }
            else if (hasSize(m_id))
            {
                setSize(keys.GetKeyAsLongDouble("size", 1.0L));
            }
            else if (hasRotation(m_id))
            {
                setRotation(keys.GetKeyAsInt("rotation", 0));
            }
        }
    }
    else
    {
        setFunction(CFP_NO_OP);
    }
}

template<>
void ComplexFunction<MpReal, MpComplex>::setFunction(const std::string &f)
{
    setNumbers();
    if (!f.empty())
    {
        KeyString keys(f);
        m_pair = (keys.GetKey("pair", "n") == "n");
        if (m_pair)
        {
            setFunction(static_cast<COMPLEX_FUNCTION_PARAMETER>(keys.GetKeyAsInt("id", 0)));
            if (hasParameter(m_id))
            {
                MpReal real(keys.GetKey("r", "0"), m_precision);
                MpReal imaginary(keys.GetKey("i", "0"), m_precision);
                m_cp = MpComplex(real, imaginary);
            }
            else if (hasSize(m_id))
            {
                MpReal size(keys.GetKey("size", "1"), m_precision);
                setSize(size);
            }
            else if (hasRotation(m_id))
            {
                setRotation(keys.GetKeyAsInt("rotation", 0));
            }
        }
        else
        {
            auto rid = static_cast<FUNCTION_PARAMETER>(keys.GetKeyAsInt("rid", 0));
            auto iid = static_cast<FUNCTION_PARAMETER>(keys.GetKeyAsInt("iid", 0));
            setFunction(rid, iid);
            if (hasParameter(rid))
            {
                MpReal r(keys.GetKey("r", "0"), m_precision);
                m_real.setParameter(r);
            }
            m_imaginary.setFunction(iid);
            if (hasParameter(iid))
            {
                MpReal i(keys.GetKey("i", "0"), m_precision);
                m_imaginary.setParameter(i);
            }
        }
    }
    else
    {
        setFunction(CFP_NO_OP);
    }
}

template<>            
LongComplex ComplexFunction<long double, LongComplex>::cfp_acos(const LongComplex& z)
{
    // Based on boost complex acos.hpp

    long double x = std::abs(real(z));
    long double y = std::abs(imag(z));

    long double real;
    long double imag; // these hold our result

    // 
    // Handle special cases specified by the C99 standard,
    // many of these special cases aren't really needed here,
    // but doing it this way prevents overflow/underflow arithmetic
    // in the main body of the logic, which may trip up some machines:
    //
    if (x != x)
    {
        if (y != y)
        {
            real = m_quarter_pi;
            imag = m_inf;
        }
        else if (y != y)
        {
            return LongComplex(y, m_neg_inf);
        }
        else
        {
            // y is not infinity or nan:
            real = m_zero;
            imag = m_inf;
        }
    }
    else if (x != x)
    {
        if (y != y)
        {
            return LongComplex(x, (z.imag() < 0.0L) ? m_inf : m_neg_inf);
        }
        return LongComplex(x, x);
    }
    else if (y == std::numeric_limits<long double>::infinity())
    {
        real = m_half_pi;
        imag = m_inf;
    }
    else if (y != y)
    {
        return LongComplex((x == 0.0L) ? m_half_pi : y, y);
    }
    else
    {
        //
        // What follows is the regular Hull et al code,
        // begin with the special case for real numbers:
        //
        if((y == 0.0L) && (x <= 1.0L))
        {
            return LongComplex((x == 0.0L) ? m_half_pi : std::acos(z.real()), 0.0L);
        }
        //
        // Figure out if our input is within the "safe area" identified by Hull et al.
        // This would be more efficient with portable floating point exception handling;
        // fortunately the quantities M and u identified by Hull et al (figure 3), 
        // match with the max and min methods of numeric_limits<T>.
        //
        long double safe_max = detail::safe_max(8.0L);
        long double safe_min = detail::safe_min(4.0L);

        long double xp1 = 1.0L + x;
        long double xm1 = x - 1.0L;

        if ((x < safe_max) && (x > safe_min) && (y < safe_max) && (y > safe_min))
        {
            long double yy = y * y;
            long double r = std::sqrt(xp1*xp1 + yy);
            long double s = std::sqrt(xm1*xm1 + yy);
            long double a = 0.5L*(r + s);
            long double b = x / a;

            if(b <= m_b_crossover)
            {
                real = std::acos(b);
            }
            else
            {
                long double apx = a + x;
                if (x <= 1.0L)
                {
                    real = std::atan(std::sqrt(0.5L*apx*(yy /(r + xp1) + (s-xm1)))/x);
                }
                else
                {
                    real = std::atan((y * std::sqrt(0.5L*(apx/(r + xp1) + apx/(s+xm1))))/x);
                }
            }

            if (a <= m_a_crossover)
            {
                long double am1;
                if (x < 1.0L)
                {
                    am1 = m_half * (yy/(r + xp1) + yy/(s - xm1));
                }
                else
                {
                    am1 = m_half * (yy/(r + xp1) + (s + xm1));
                }
                imag = log1p(am1 + std::sqrt(am1 * (a + 1.0L)));
            }
            else
            {
                imag = std::log(a + std::sqrt(a*a - 1.0L));
            }
        }
        else
        {
            //
            // This is the Hull et al exception handling code from Fig 6 of their paper:
            //
            if (y <= (std::numeric_limits<long double>::epsilon()*std::abs(xm1)))
            {
                if (x < 1.0L)
                {
                    real = std::acos(x);
                    imag = y / std::sqrt(xp1*(1.0L - x));
                }
                else
                {
                    real = 0.0L;
                    if ((std::numeric_limits<long double>::max()/ xp1) > xm1)
                    {
                        // xp1 * xm1 won't overflow:
                        imag = log1p(xm1 + std::sqrt(xp1*xm1));
                    }
                    else
                    {
                        imag = 2.0L + std::log(x);
                    }
                }
            }
            else if(y <= safe_min)
            {
                // There is an assumption in Hull et al's analysis that
                // if we get here then x == 1.  This is true for all "good"
                // machines where :
                // 
                // E^2 > 8*sqrt(u); with:
                //
                // E =  std::numeric_limits<T>::epsilon()
                // u = (std::numeric_limits<T>::min)()
                //
                // Hull et al provide alternative code for "bad" machines
                // but we have no way to test that here, so for now just assert
                // on the assumption:
                //
                BOOST_ASSERT(x == 1);
                real = std::sqrt(y);
                imag = std::sqrt(y);
            }
            else if ((std::numeric_limits<long double>::epsilon() * y - 1.0L) >= x)
            {
                real = m_half_pi;
                imag = 2.0L + std::log(y);
            }
            else if(x > 1.0L)
            {
                real = std::atan(y/x);
                long double xoy = x/y;
                imag = 2.0L + std::log(y) + 0.5L*log1p(xoy*xoy);
            }
            else
            {
                real = m_half_pi;
                long double a = std::sqrt(m_one + y*y);
                imag = m_half * log1p(m_two*y*(y+a));
            }
        }
    }
    //
    // Finish off by working out the sign of the result:
    //
    if (z.real() < 0.0L)
    {
        real = m_pi - real;
    }
    if (z.imag() > 0.0L)
    {
        imag = -imag;
    }

   return LongComplex(real, imag);
}

template<>
LongComplex ComplexFunction<long double, LongComplex>::cfp_acosh(const LongComplex& z)
{
    // adapted from boost's complex acosh function
    //
    // We use the relation acosh(z) = +-i acos(z)
    // Choosing the sign of multiplier to give real(acosh(z)) >= 0
    // as well as compatibility with C99.
    //
    LongComplex r = cfp_acos(z);
    if (!(r.imag() != r.imag()) && r.imag() <= 0.0L)
    {
        return LongComplex(-r.imag(), r.real());
    }
    return LongComplex(r.imag(), r.real() != r.real() ? r.real() : -r.real());
}

template<>
MpComplex ComplexFunction<MpReal, MpComplex>::cfp_acos(const MpComplex& z)
{
    // Based on boost complex acos.hpp

    MpReal x = mpfr::abs(real(z));
    MpReal y = mpfr::abs(imag(z));

    MpReal real;
    MpReal imag; // these hold our result

    // 
    // Handle special cases specified by the C99 standard,
    // many of these special cases aren't really needed here,
    // but doing it this way prevents overflow/underflow arithmetic
    // in the main body of the logic, which may trip up some machines:
    //
    if (mpfr::isinf(x))
    {
        if (mpfr::isinf(y))
        {
            real = m_quarter_pi;
            imag = m_inf;
        }
        else if (mpfr::isnan(y))
        {
            return MpComplex(y, m_neg_inf);
        }
        else
        {
            // y is not infinity or nan:
            real = m_zero;
            imag = m_inf;
        }
    }
    else if (mpfr::isnan(x))
    {
        if (mpfr::isinf(y))
        {
            return MpComplex(x, (z.imag() < m_zero) ? m_inf : m_neg_inf);
        }
        return MpComplex(x, x);
    }
    else if (mpfr::isinf(y))
    {
        real = m_half_pi;
        imag = m_inf;
    }
    else if (mpfr::isnan(y))
    {
        return MpComplex((x == m_zero) ? m_half_pi : y, y);
    }
    else
    {
        //
        // What follows is the regular Hull et al code,
        // begin with the special case for real numbers:
        //
        if((y == 0) && (x <= m_one))
        {
            return MpComplex((x == m_zero) ? m_half_pi : mpfr::acos(z.real()), m_zero);
        }
        //
        // Figure out if our input is within the "safe area" identified by Hull et al.
        // This would be more efficient with portable floating point exception handling;
        // fortunately the quantities M and u identified by Hull et al (figure 3), 
        // match with the max and min methods of numeric_limits<T>.
        //
        MpReal safe_max = mpfr::sqrt(mpfr::maxval())/MpReal("8");
        MpReal safe_min = mpfr::sqrt(mpfr::minval())*MpReal("4");

        MpReal xp1 = m_one + x;
        MpReal xm1 = x - m_one;

        if ((x < safe_max) && (x > safe_min) && (y < safe_max) && (y > safe_min))
        {
            MpReal yy = y * y;
            MpReal r = mpfr::sqrt(xp1*xp1 + yy);
            MpReal s = mpfr::sqrt(xm1*xm1 + yy);
            MpReal a = m_half * (r + s);
            MpReal b = x / a;

            if(b <= m_b_crossover)
            {
                real = mpfr::acos(b);
            }
            else
            {
                MpReal apx = a + x;
                if (x <= m_one)
                {
                    real = mpfr::atan(mpfr::sqrt(m_half * apx * (yy /(r + xp1) + (s-xm1)))/x);
                }
                else
                {
                    real = mpfr::atan((y * mpfr::sqrt(m_half * (apx/(r + xp1) + apx/(s+xm1))))/x);
                }
            }

            if (a <= m_a_crossover)
            {
                MpReal am1;
                if (x < m_one)
                {
                    am1 = m_half * (yy/(r + xp1) + yy/(s - xm1));
                }
                else
                {
                    am1 = m_half * (yy/(r + xp1) + (s + xm1));
                }
                imag = mpfr::log1p(am1 + mpfr::sqrt(am1 * (a + m_one)));
            }
            else
            {
                imag = mpfr::log(a + mpfr::sqrt(a*a - m_one));
            }
        }
        else
        {
            //
            // This is the Hull et al exception handling code from Fig 6 of their paper:
            //
            if (y <= (mpfr::machine_epsilon() * mpfr::abs(xm1)))
            {
                if (x < m_one)
                {
                    real = mpfr::acos(x);
                    imag = y / mpfr::sqrt(xp1*(m_one - x));
                }
                else
                {
                    real = m_zero;
                    if ((mpfr::maxval()/ xp1) > xm1)
                    {
                        // xp1 * xm1 won't overflow:
                        imag = mpfr::log1p(xm1 + mpfr::sqrt(xp1*xm1));
                    }
                    else
                    {
                        imag = m_log_two + mpfr::log(x);
                    }
                }
            }
            else if(y <= safe_min)
            {
                // There is an assumption in Hull et al's analysis that
                // if we get here then x == 1.  This is true for all "good"
                // machines where :
                // 
                // E^2 > 8*sqrt(u); with:
                //
                // E =  std::numeric_limits<T>::epsilon()
                // u = (std::numeric_limits<T>::min)()
                //
                // Hull et al provide alternative code for "bad" machines
                // but we have no way to test that here, so for now just assert
                // on the assumption:
                //
                BOOST_ASSERT(x == 1);
                real = mpfr::sqrt(y);
                imag = mpfr::sqrt(y);
            }
            else if(mpfr::machine_epsilon() * y - m_one >= x)
            {
                real = m_half_pi;
                imag = m_log_two + mpfr::log(y);
            }
            else if(x > m_one)
            {
                real = mpfr::atan(y/x);
                MpReal xoy = x/y;
                imag = m_log_two + mpfr::log(y) + m_half * mpfr::log1p(xoy*xoy);
            }
            else
            {
                real = m_half_pi;
                MpReal a = mpfr::sqrt(m_one + y*y);
                imag = m_half * mpfr::log1p(m_two*y*(y+a));
            }
        }
    }
    //
    // Finish off by working out the sign of the result:
    //
    if (z.real() < m_zero)
    {
        real = m_pi - real;
    }
    if (z.imag() > m_zero)
    {
        imag = -imag;
    }

   return MpComplex(real, imag);
}

template<>
MpComplex ComplexFunction<MpReal, MpComplex>::cfp_acosh(const MpComplex& z)
{
    // adapted from boost's complex acosh function
    //
    // We use the relation acosh(z) = +-i acos(z)
    // Choosing the sign of multiplier to give real(acosh(z)) >= 0
    // as well as compatibility with C99.
    //
    MpComplex r = cfp_acos(z);
    if (!mpfr::isnan(r.imag()) && r.imag() <= m_zero)
    {
        return MpComplex(-r.imag(), r.real());
    }
    return MpComplex(r.imag(), mpfr::isnan(r.real()) ? r.real() : -r.real());
}

template<>
MpComplex ComplexFunction<MpReal, MpComplex>::cfp_asin(const MpComplex& z)
{
    // adapted from boost's complex asin function
    //
    // This implementation is a transcription of the pseudo-code in:
    //
    // "Implementing the complex Arcsine and Arccosine Functions using Exception Handling."
    // T E Hull, Thomas F Fairgrieve and Ping Tak Peter Tang.
    // ACM Transactions on Mathematical Software, Vol 23, No 3, Sept 1997.
    //

    //
    // Get real and imaginary parts, discard the signs as we can 
    // figure out the sign of the result later:
    //
    MpReal x = mpfr::abs(z.real());
    MpReal y = mpfr::fabs(z.imag());
    MpReal real, imag;  // our results

    //
    // Begin by handling the special cases for infinities and nan's
    // specified in C99, most of this is handled by the regular logic
    // below, but handling it as a special case prevents overflow/underflow
    // arithmetic which may trip up some machines:
    //
    if (mpfr::isnan(x))
    {
        if (mpfr::isnan(y))
        {
            return MpComplex(x, x);
        }
        if (mpfr::isinf(y))
        {
            real = x;
            imag = m_inf;
        }
        else
        {
            return MpComplex(x, x);
        }
    }
    else if (mpfr::isnan(y))
    {
        if (x == m_zero)
        {
            real = m_zero;
            imag = y;
        }
        else if (mpfr::isinf(x))
        {
            real = y;
            imag = m_inf;
        }
        else
        {
            return MpComplex(y, y);
        }
    }
    else if (mpfr::isinf(x))
    {
        if (mpfr::isinf(y))
        {
            real = m_quarter_pi;
            imag = m_inf;
        }
        else
        {
            real = m_half_pi;
            imag = m_inf;
        }
    }
    else if (mpfr::isinf(y))
    {
        real = m_zero;
        imag = m_inf;
   }
   else
   {
        //
        // special case for real numbers:
        //
        if ((y == m_zero) && (x <= m_one))
        {
            return MpComplex(mpfr::asin(z.real()), m_zero);
        }
        MpReal safe_max = mpfr::sqrt(mpfr::maxval())/m_eight;
        MpReal safe_min = mpfr::sqrt(mpfr::minval())*m_four;

        MpReal xp1 = m_one + x;
        MpReal xm1 = x - m_one;

        if ((x < safe_max) && (x > safe_min) && (y < safe_max) && (y > safe_min))
        {
            MpReal yy = y * y;
            MpReal r = mpfr::sqrt(xp1*xp1 + yy);
            MpReal s = mpfr::sqrt(xm1*xm1 + yy);
            MpReal a = m_half * (r + s);
            MpReal b = x / a;

            if (b <= m_b_crossover)
            {
                real = mpfr::asin(b);
            }
            else
            {
                MpReal apx = a + x;
                if (x <= m_one)
                {
                    real = mpfr::atan(x/mpfr::sqrt(m_half * apx * (yy /(r + xp1) + (s-xm1))));
                }
                else
                {
                    real = mpfr::atan(x/(y * mpfr::sqrt(m_half * (apx/(r + xp1) + apx/(s+xm1)))));
                }
            }

            if(a <= m_a_crossover)
            {
                MpReal am1;
                if (x < m_one)
                {
                    am1 = m_half * (yy/(r + xp1) + yy/(s - xm1));
                }
                else
                {
                    am1 = m_half * (yy/(r + xp1) + (s + xm1));
                }
                imag = mpfr::log1p(am1 + mpfr::sqrt(am1 * (a + m_one)));
            }
            else
            {
                imag = mpfr::log(a + mpfr::sqrt(a*a - m_one));
            }
        }
        else
        {
            //
            // This is the Hull et al exception handling code from Fig 3 of their paper:
            //
            if (y <= (mpfr::machine_epsilon() * mpfr::abs(xm1)))
            {
                if (x < m_one)
                {
                    real = mpfr::asin(x);
                    imag = y / mpfr::sqrt(xp1*xm1);
                }
                else
                {
                    real = m_half_pi;
                    if ((mpfr::maxval() / xp1) > xm1)
                    {
                        // xp1 * xm1 won't overflow:
                        imag = mpfr::log1p(xm1 + mpfr::sqrt(xp1*xm1));
                    }
                    else
                    {
                        imag = m_log_two + mpfr::log(x);
                    }
                }
            }
            else if (y <= safe_min)
            {
                // There is an assumption in Hull et al's analysis that
                // if we get here then x == 1.  This is true for all "good"
                // machines where :
                // 
                // E^2 > 8*sqrt(u); with:
                //
                // E =  std::numeric_limits<T>::epsilon()
                // u = (std::numeric_limits<T>::min)()
                //
                // Hull et al provide alternative code for "bad" machines
                // but we have no way to test that here, so for now just assert
                // on the assumption:
                //
                BOOST_ASSERT(x == 1);
                real = m_half_pi - mpfr::sqrt(y);
                imag = mpfr::sqrt(y);
            }
            else if(mpfr::machine_epsilon() * y - m_one >= x)
            {
                real = x/y; // This can underflow!
                imag = m_log_two + mpfr::log(y);
            }
            else if(x > m_one)
            {
                real = mpfr::atan(x/y);
                MpReal xoy = x/y;
                imag = m_log_two + mpfr::log(y) + m_half * mpfr::log1p(xoy*xoy);
            }
            else
            {
                MpReal a = mpfr::sqrt(m_one + y*y);
                real = x/a; // This can underflow!
                imag = m_half * mpfr::log1p(m_two*y*(y+a));
            }
        }
    }

    //
    // Finish off by working out the sign of the result:
    //
    if (z.real() < m_zero)
    {
        real = -real;
    }
    if (z.imag() < m_zero)
    {
        imag = -imag;
    }
    return MpComplex(real, imag);
}

template<>
MpComplex ComplexFunction<MpReal, MpComplex>::cfp_asinh(const MpComplex& z)
{
    // adapted from boost's complex asin function
    MpComplex r = cfp_asin(MpComplex(z.imag(),
                           mpfr::isnan(z.real()) ? z.real() : -z.real()));
    return MpComplex(mpfr::isnan(r.imag()) ? r.imag() : -r.imag(), r.real());
}

template<>
MpComplex ComplexFunction<MpReal, MpComplex>::cfp_atanh(const MpComplex& z)
{
    // adapted from boost's complex atanh function
    //

    MpReal x = mpfr::abs(z.real());
    MpReal y = mpfr::abs(z.imag());

    MpReal real;
    MpReal imag;

    MpReal safe_upper = mpfr::sqrt(mpfr::maxval())/m_two;
    MpReal safe_lower = mpfr::sqrt(mpfr::minval())*m_two;

    //
    // Begin by handling the special cases specified in C99:
    //
    if (mpfr::isnan(x))
    {
        if (mpfr::isnan(y))
        {
            return MpComplex(x, x);
        }
        else if (mpfr::isinf(y))
        {
            return MpComplex(m_zero, ((z.imag() < m_zero) ? -m_half_pi : m_half_pi));
        }
        else
        {
            return MpComplex(x, x);
        }
    }
    else if (mpfr::isnan(y))
    {
        if (x == 0)
        {
            return MpComplex(x, y);
        }
        if (mpfr::isinf(x))
        {
            return MpComplex(m_zero, y);
        }
        else
        {
            return MpComplex(y, y);
        }
    }
    else if ((x > safe_lower) && (x < safe_upper) && (y > safe_lower) && (y < safe_upper))
    {
        MpReal xx = x*x;
        MpReal yy = y*y;
        MpReal x2 = x * m_two;
        ///
        // The real part is given by:
        // 
        // real(atanh(z)) == log((1 + x^2 + y^2 + 2x) / (1 + x^2 + y^2 - 2x))
        // 
        // However, when x is either large (x > 1/E) or very small
        // (x < E) then this effectively simplifies
        // to log(1), leading to wildly inaccurate results.  
        // By dividing the above (top and bottom) by (1 + x^2 + y^2) we get:
        //
        // real(atanh(z)) == log((1 + (2x / (1 + x^2 + y^2))) / (1 - (-2x / (1 + x^2 + y^2))))
        //
        // which is much more sensitive to the value of x, when x is not near 1
        // (remember we can compute log(1+x) for small x very accurately).
        //
        // The cross-over from one method to the other has to be determined
        // experimentally, the value used below appears correct to within a 
        // factor of 2 (and there are larger errors from other parts
        // of the input domain anyway).
        //
        MpReal alpha = m_two*x / (m_one + xx + yy);
        if (alpha < m_a_crossover)
        {
            real = mpfr::log1p(alpha) - mpfr::log1p(-alpha);
        }
        else
        {
            MpReal xm1 = x - m_one;
            real = mpfr::log1p(x2 + xx + yy) - mpfr::log(xm1*xm1 + yy);
        }
        real /= m_four;
        if (z.real() < m_zero)
        {
            real = -real;
        }
        imag = mpfr::atan2((y * m_two), (m_one - xx - yy));
        imag /= m_two;
        if(z.imag() < m_zero)
        {
            imag = -imag;
        }
    }
    else
    {
        //
        // This section handles exception cases that would normally cause
        // underflow or overflow in the main formulas.
        //
        // Begin by working out the real part, we need to approximate
        //    alpha = 2x / (1 + x^2 + y^2)
        // without either overflow or underflow in the squared terms.
        //
        MpReal alpha = m_zero;
        if (x >= safe_upper)
        {
            // this is really a test for infinity, 
            // but we may not have the necessary numeric_limits support:
            if ((x > mpfr::maxval()) || (y > mpfr::maxval()))
            {
                alpha = m_zero;
            }
            else if (y >= safe_upper)
            {
                // Big x and y: divide alpha through by x*y:
                alpha = (m_two/y) / (x/y + y/x);
            }
            else if(y > m_one)
            {
                // Big x: divide through by x:
                alpha = m_two / (x + y*y/x);
            }
            else
            {
                // Big x small y, as above but neglect y^2/x:
                alpha = m_two/x;
            }
        }
        else if (y >= safe_upper)
        {
            if (x > m_one)
            {
                // Big y, medium x, divide through by y:
                alpha = (m_two*x/y) / (y + x*x/y);
            }
            else
            {
                // Small x and y, whatever alpha is, it's too small to calculate:
                alpha = m_zero;
            }
        }
        else
        {
            // one or both of x and y are small, calculate divisor carefully:
            MpReal div = m_one;
            if (x > safe_lower)
            {
                div += x*x;
            }
            if (y > safe_lower)
            {
                div += y*y;
            }
            alpha = m_two*x/div;
        }
        if (alpha < m_a_crossover)
        {
            real = mpfr::log1p(alpha) - mpfr::log1p(-alpha);
        }
        else
        {
            // We can only get here as a result of small y and medium sized x,
            // we can simply neglect the y^2 terms:
            BOOST_ASSERT(x >= safe_lower);
            BOOST_ASSERT(x <= safe_upper);
            //BOOST_ASSERT(y <= safe_lower);
            MpReal xm1 = x - m_one;
            real = mpfr::log(m_one + m_two*x + x*x) - mpfr::log(xm1*xm1);
        }
        real /= m_four;
        if (z.real() < m_zero)
        {
            real = -real;
        }
        //
        // Now handle imaginary part, this is much easier,
        // if x or y are large, then the formula:
        //    atan2(2y, 1 - x^2 - y^2)
        // evaluates to +-(PI - theta) where theta is negligible compared to PI.
        //
        if ((x >= safe_upper) || (y >= safe_upper))
        {
            imag = m_pi;
        }
        else if (x <= safe_lower)
        {
            //
            // If both x and y are small then atan(2y),
            // otherwise just x^2 is negligible in the divisor:
            //
            if (y <= safe_lower)
            {
                imag = mpfr::atan2(m_two*y, m_one);
            }
            else
            {
                if ((y == m_zero) && (x == m_zero))
                {
                    imag = m_zero;
                }
                else
                {
                    imag = mpfr::atan2(m_two*y, m_one - y*y);
                }
            }
        }
        else
        {
            //
            // y^2 is negligible:
            //
            if ((y == m_zero) && (x == m_one))
            {
                imag = m_zero;
            }
            else
            {
                imag = mpfr::atan2(m_two*y, m_one - x*x);
            }
        }
        imag /= m_two;
        if (z.imag() < m_zero)
        {
            imag = -imag;
        }
    }
   return MpComplex(real, imag);
}

template<>
MpComplex ComplexFunction<MpReal, MpComplex>::cfp_atan(const MpComplex& z)
{
    // adapted from boost's complex atan function
    //
    // We're using the C99 definition here; atan(z) = -i atanh(iz):
    //
    if (z.real() == m_zero)
    {
        if (z.imag() == m_one)
        {
            return MpComplex(m_one, m_inf);
        }
        if (z.imag() == -m_one)
        {
            return MpComplex(m_one, m_neg_inf);
        }
    }
    MpComplex r = cfp_atanh(MpComplex(mpfr::isnan(z.imag()) ? z.imag() : -z.imag(),
                                                                          z.real()));
    return MpComplex(r.imag(), mpfr::isnan(r.real()) ? r.real() : -r.real());
}   
