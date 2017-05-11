// 
// File:   CalculatingUnit.cc
// Author: M.R.Eggleston
// 
// Created on 08 March 2012, 17:50
//

#include "CalculatingUnit.h"
#include "Utilities.h"
#include "mpreal.h"
#include "OrbitTraps.h"


//==============================================================================
// Specialisations
//==============================================================================

template<>
void CalculatingUnit<long double, LongComplex>::set_fractal_parameters()
{
    StringComplex zero;
    
    int p = StaticCalculatingUnit::s_config.getNumberOfComplexParameters();
    m_alpha = stringComplexToLongComplex((p > 0) ? StaticCalculatingUnit::s_config.getComplexParameter(0) : zero);
    m_beta = stringComplexToLongComplex((p > 1) ? StaticCalculatingUnit::s_config.getComplexParameter(1) : zero);
    m_gamma = stringComplexToLongComplex((p > 2) ? StaticCalculatingUnit::s_config.getComplexParameter(2) : zero);
    m_delta = stringComplexToLongComplex((p > 3) ? StaticCalculatingUnit::s_config.getComplexParameter(3) : zero);
    m_epsilon = stringComplexToLongComplex((p > 4) ? StaticCalculatingUnit::s_config.getComplexParameter(4) : zero);
    m_zeta = stringComplexToLongComplex((p > 5) ? StaticCalculatingUnit::s_config.getComplexParameter(5) : zero);
    m_eta = stringComplexToLongComplex((p > 6) ? StaticCalculatingUnit::s_config.getComplexParameter(6) : zero);
    m_theta = stringComplexToLongComplex((p > 7) ? StaticCalculatingUnit::s_config.getComplexParameter(7) : zero);
    m_iota = stringComplexToLongComplex((p > 8) ? StaticCalculatingUnit::s_config.getComplexParameter(8) : zero);
    //
    m_alpha_type = ((p > 0) ? StaticCalculatingUnit::s_config.getComplexParameterType(0) : PT_NUMBER);
    m_beta_type = ((p > 1) ? StaticCalculatingUnit::s_config.getComplexParameterType(1) : PT_NUMBER);
    m_gamma_type = ((p > 2) ? StaticCalculatingUnit::s_config.getComplexParameterType(2) : PT_NUMBER);
    m_delta_type = ((p > 3) ? StaticCalculatingUnit::s_config.getComplexParameterType(3) : PT_NUMBER);
    m_epsilon_type = ((p > 4) ? StaticCalculatingUnit::s_config.getComplexParameterType(4) : PT_NUMBER);
    m_zeta_type = ((p > 5) ? StaticCalculatingUnit::s_config.getComplexParameterType(5) : PT_NUMBER);
    m_eta_type = ((p > 6) ? StaticCalculatingUnit::s_config.getComplexParameterType(6) : PT_NUMBER);
    m_theta_type = ((p > 7) ? StaticCalculatingUnit::s_config.getComplexParameterType(7) : PT_NUMBER);
    m_iota_type = ((p > 8) ? StaticCalculatingUnit::s_config.getComplexParameterType(8) : PT_NUMBER);
   //
    p = StaticCalculatingUnit::s_config.getNumberOfParameters();
    m_p0 = stringToLongDouble((p > 0) ? StaticCalculatingUnit::s_config.getParameter(0) : "0");
    m_p1 = stringToLongDouble((p > 1) ? StaticCalculatingUnit::s_config.getParameter(1) : "0");
    m_p2 = stringToLongDouble((p > 2) ? StaticCalculatingUnit::s_config.getParameter(2) : "0");
    m_p3 = stringToLongDouble((p > 3) ? StaticCalculatingUnit::s_config.getParameter(3) : "0");
    m_p4 = stringToLongDouble((p > 4) ? StaticCalculatingUnit::s_config.getParameter(4) : "0");
    m_p5 = stringToLongDouble((p > 5) ? StaticCalculatingUnit::s_config.getParameter(5) : "0");
    m_p6 = stringToLongDouble((p > 6) ? StaticCalculatingUnit::s_config.getParameter(6) : "0");
    m_p7 = stringToLongDouble((p > 7) ? StaticCalculatingUnit::s_config.getParameter(7) : "0");
    //
    p = StaticCalculatingUnit::s_config.getNumberOfFunctionParameters();
    assignFunctionParameter(0, p);
    assignFunctionParameter(1, p);
    assignFunctionParameter(2, p);
    assignFunctionParameter(3, p);
    assignFunctionParameter(4, p);
    assignFunctionParameter(5, p);
    assignFunctionParameter(6, p);
    assignFunctionParameter(7, p);
    //
    p = StaticCalculatingUnit::s_config.getNumberOfComplexFunctionParameters();
    assignComplexFunctionParameter(0, p);
    assignComplexFunctionParameter(1, p);
    assignComplexFunctionParameter(2, p);
    assignComplexFunctionParameter(3, p);
    assignComplexFunctionParameter(4, p);
    assignComplexFunctionParameter(5, p);
    assignComplexFunctionParameter(6, p);
    assignComplexFunctionParameter(7, p);
}

template<>
void CalculatingUnit<MpReal, MpComplex>::set_fractal_parameters()
{
    int precision = StaticCalculatingUnit::s_precision;
    StringComplex zero;
    
    int p = StaticCalculatingUnit::s_config.getNumberOfComplexParameters();
    auto& conf = StaticCalculatingUnit::s_config;
    m_alpha = stringComplexToMpComplex((p > 0) ? conf.getComplexParameter(0) : zero, precision);
    m_beta = stringComplexToMpComplex((p > 1) ? conf.getComplexParameter(1) : zero, precision);
    m_gamma = stringComplexToMpComplex((p > 2) ? conf.getComplexParameter(2) : zero, precision);
    m_delta = stringComplexToMpComplex((p > 3) ? conf.getComplexParameter(3) : zero, precision);
    m_epsilon = stringComplexToMpComplex((p > 4) ? conf.getComplexParameter(4) : zero, precision);
    m_zeta = stringComplexToMpComplex((p > 5) ? conf.getComplexParameter(5) : zero, precision);
    m_eta = stringComplexToMpComplex((p > 6) ? conf.getComplexParameter(6) : zero, precision);
    m_theta = stringComplexToMpComplex((p > 7) ? conf.getComplexParameter(7) : zero, precision);
    m_iota = stringComplexToMpComplex((p > 8) ? conf.getComplexParameter(8) : zero, precision);
    //
    m_alpha_type = ((p > 0) ? conf.getComplexParameterType(0) : PT_NUMBER);
    m_beta_type = ((p > 1) ? conf.getComplexParameterType(1) : PT_NUMBER);
    m_gamma_type = ((p > 2) ? conf.getComplexParameterType(2) : PT_NUMBER);
    m_delta_type = ((p > 3) ? conf.getComplexParameterType(3) : PT_NUMBER);
    m_epsilon_type = ((p > 4) ? conf.getComplexParameterType(4) : PT_NUMBER);
    m_zeta_type = ((p > 5) ? conf.getComplexParameterType(5) : PT_NUMBER);
    m_eta_type = ((p > 6) ? conf.getComplexParameterType(6) : PT_NUMBER);
    m_theta_type = ((p > 7) ? conf.getComplexParameterType(7) : PT_NUMBER);
    m_theta_type = ((p > 8) ? conf.getComplexParameterType(8) : PT_NUMBER);
    //
    p = conf.getNumberOfParameters();
    m_p0 = MpReal((p > 0) ? conf.getParameter(0) : "0", precision);
    m_p1 = MpReal((p > 1) ? conf.getParameter(1) : "0", precision);
    m_p2 = MpReal((p > 2) ? conf.getParameter(2) : "0", precision);
    m_p3 = MpReal((p > 3) ? conf.getParameter(3) : "0", precision);
    m_p4 = MpReal((p > 4) ? conf.getParameter(4) : "0", precision);
    m_p5 = MpReal((p > 5) ? conf.getParameter(5) : "0", precision);
    m_p6 = MpReal((p > 6) ? conf.getParameter(6) : "0", precision);
    m_p7 = MpReal((p > 7) ? conf.getParameter(7) : "0", precision);
    //
    p = conf.getNumberOfFunctionParameters();
    assignFunctionParameter(0, p);
    assignFunctionParameter(1, p);
    assignFunctionParameter(2, p);
    assignFunctionParameter(3, p);
    assignFunctionParameter(4, p);
    assignFunctionParameter(5, p);
    assignFunctionParameter(6, p);
    assignFunctionParameter(7, p);
    //
    p = conf.getNumberOfComplexFunctionParameters();
    assignComplexFunctionParameter(0, p);
    assignComplexFunctionParameter(1, p);
    assignComplexFunctionParameter(2, p);
    assignComplexFunctionParameter(3, p);
    assignComplexFunctionParameter(4, p);
    assignComplexFunctionParameter(5, p);
    assignComplexFunctionParameter(6, p);
    assignComplexFunctionParameter(7, p);
}

template<>
void CalculatingUnit<long double, LongComplex>::setNumbers()
{
    m_zero = 0.0L;
    m_one = 1.0L;
    m_two = 2.0L;
    m_three = 3.0L;
    m_ln2 = std::log(m_two);
    m_max = std::numeric_limits<long double>::max();
    m_pi = mpfr::const_pi(128).toLDouble();
    m_inf = std::numeric_limits<long double>::infinity();
    m_ld_inf = m_inf;
}

template<>
void CalculatingUnit<MpReal, MpComplex>::setNumbers()
{
    int precision = StaticCalculatingUnit::s_precision;
    m_zero = MpReal("0", precision);
    m_one = MpReal("1", precision);
    m_two = MpReal("2", precision);
    m_three = MpReal("3", precision);
    m_max = mpfr::maxval(precision);
    m_ln2 = mpfr::log(m_two);
    m_pi = mpfr::const_pi(precision).toLDouble();
    m_inf = m_one/m_zero;
    m_ld_inf = std::numeric_limits<long double>::infinity();
}

template<>
LongComplex CalculatingUnit<long double, LongComplex>::unsign(const LongComplex& z)
{
    return LongComplex(std::abs(real(z)), std::abs(imag(z)));
}

template<>
MpComplex CalculatingUnit<MpReal, MpComplex>::unsign(const MpComplex& z)
{
    return MpComplex(mpfr::abs(real(z)), mpfr::abs(imag(z)));
}

template<>
LongComplex CalculatingUnit<long double, LongComplex>::unsigni(const LongComplex& z)
{
    return LongComplex(real(z), std::abs(imag(z)));
}

template<>
MpComplex CalculatingUnit<MpReal, MpComplex>::unsigni(const MpComplex& z)
{
    return MpComplex(real(z), mpfr::abs(imag(z)));
}

template<>
void CalculatingUnit<long double, LongComplex>::calculateLyapunovRowByRow()
{
    int row = StaticCalculatingUnit::nextRow();
    int width = StaticCalculatingUnit::s_width;
    int height = StaticCalculatingUnit::s_height;
    long double pitch = StaticCalculatingUnit::s_pitch.toLDouble();
    int settling_cycles = StaticCalculatingUnit::s_config.getSettlingCycles();
    int calculating_cycles = StaticCalculatingUnit::s_config.getCalculatingCycles();
    long double r;
    long double iterations = static_cast<long double>(calculating_cycles*m_num_in_sequence);
#ifndef BATCH
    LyapunovResultsSet* rs;
#else
    long double lyap = 0.0L;
#endif

    while (row < height)
    {
#ifndef BATCH
        rs = &(StaticCalculatingUnit::s_lyapunov_results[row*width]);
#endif
        long double base_a = StaticCalculatingUnit::s_topleft_r.toLDouble();
        long double base_b = StaticCalculatingUnit::s_topleft_i.toLDouble() - static_cast<long double>(row)*pitch;
        for (int col = 0; (col < width) && !StaticCalculatingUnit::s_stop; col++, base_a += pitch)
        {
            long double total = 0.0L;
            long double x = 0.5L;
            long double a;
            long double b;
            
            StaticCalculatingUnit::rotate(base_a, base_b, a, b);

            if ((a <= m_zero) || (b <= m_zero) || (std::abs(x) == m_inf))
            {
                continue;
            }
            int cycle = 0;
            while ((cycle < settling_cycles) && !StaticCalculatingUnit::s_stop)
            {
                for (auto k = 0; k < m_num_in_sequence; k++)
                {
                    r = (m_sequence[k] ? a : b);
                    x = r*x*(1.0L - x);
                    if (std::abs(x) == m_inf)
                    {
                        break;
                    }
                }
                cycle++;
            }
            cycle = 0;
            while ((cycle < calculating_cycles) && !StaticCalculatingUnit::s_stop)
            {
                for (auto j = 0; j < m_num_in_sequence; j++)
                {
                    r = (m_sequence[j] ? a : b);
                    x = r*x*(1.0L - x);
                    total += (std::log(std::abs(r - 2.0L*r*x)))/m_ln2;
                }
                cycle++;
            }
#ifdef BATCH
            lyap = total/iterations;
            StaticCalculatingUnit::updateImage(lyap, col, row);
#else
            rs->lyap = total/iterations;
            StaticCalculatingUnit::updateImage(rs->lyap, col, row);
            rs++;
#endif
        }
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
void CalculatingUnit<MpReal, MpComplex>::calculateLyapunovRowByRow()
{
    int precision = StaticCalculatingUnit::s_precision;
    MpReal ln2 = mpfr::log(m_two);
    int row = StaticCalculatingUnit::nextRow();
    int width = StaticCalculatingUnit::s_width;
    int height = StaticCalculatingUnit::s_height;
    MpReal pitch = StaticCalculatingUnit::s_pitch;
    int settling_cycles = StaticCalculatingUnit::s_config.getSettlingCycles();
    int calculating_cycles = StaticCalculatingUnit::s_config.getCalculatingCycles();
    MpReal x;
    MpReal r;
    long double iterations = static_cast<long double>(calculating_cycles*m_num_in_sequence);
#ifndef BATCH
    LyapunovResultsSet* rs;
#else
    long double lyap = 0.0L;
#endif

    while (row < height)
    {
#ifndef BATCH
        rs = &(StaticCalculatingUnit::s_lyapunov_results[row*width]);
#endif
        MpReal r(row, precision);
        MpReal base_a = StaticCalculatingUnit::s_topleft_r;
        MpReal base_b = StaticCalculatingUnit::s_topleft_i - r*pitch;
        for (int col = 0; (col < width) && !StaticCalculatingUnit::s_stop; col++, base_a += pitch)
        {
            MpReal total = m_zero;
            MpReal a;
            MpReal b;
            
            StaticCalculatingUnit::rotate(base_a, base_b, a, b);

            if ((a <= m_zero) || (b <= m_zero) || (mpfr::abs(x) == m_inf))
            {
                continue;
            }
            int cycle = 0;
            while ((cycle < settling_cycles) && !StaticCalculatingUnit::s_stop)
            {
                for (auto k = 0; k < m_num_in_sequence; k++)
                {
                    r = (m_sequence[k] ? a : b);
                    x = r*x*(m_one - x);
                    if (x == -m_max)
                    {
                        break;
                    }
                }
                cycle++;
            }
            cycle = 0;
            while ((cycle < calculating_cycles) && !StaticCalculatingUnit::s_stop)
            {
                for (auto j = 0; j < m_num_in_sequence; j++)
                {
                    r = (m_sequence[j] ? a : b);
                    x = r*x*(m_one - x);
                    total += (mpfr::log(mpfr::abs(r - m_two*r*x)))/ln2;
                }
                cycle++;
            }
#ifdef BATCH
            lyap = total.toLDouble()/iterations;
            StaticCalculatingUnit::updateImage(lyap, col, row);
#else
            rs->lyap = total.toLDouble()/iterations;
            StaticCalculatingUnit::updateImage(rs->lyap, col, row);
            rs++;
#endif
        }
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }

}

template<>
bool CalculatingUnit<MpReal, MpComplex>::calculateLyapunovSettlingCycle()
{
    // do nothing - should never be called
    return true;
}

template<>
bool CalculatingUnit<MpReal, MpComplex>::calculateLyapunovCalculatingCycle(unsigned int)
{
    // do nothing - should never be called
    return true;
}

