// 
// File:   ComplexFunction.h
// Author: M.R.Eggleston
//
// Created on 19 April 2012, 14:11
//

#pragma once

#include "Function.h"

template<class T, class Tc>
class ComplexFunction
{
public:
    ComplexFunction();
    ComplexFunction(const ComplexFunction &other);
    const ComplexFunction &operator=(const ComplexFunction &other);
    virtual ~ComplexFunction();
    
    Tc operator()(const Tc& z);
    
    void setFunction(const std::string& f);
    void setFunction(COMPLEX_FUNCTION_PARAMETER f);
    void setFunction(FUNCTION_PARAMETER fr, FUNCTION_PARAMETER fi);
    void setParameter(const Tc& p);
    void setRealParameter(T p);
    void setImaginaryParameter(T p);
    void setRotation(int r);
    void setSize(T size);

private:
    void loadFunctions();

    void assignFunction(COMPLEX_FUNCTION_PARAMETER F);
    Tc (ComplexFunction::*m_f)(const Tc &value);
    Tc cfp_no_op(const Tc& value);
    Tc cfp_acos(const Tc& value);
    Tc cfp_acosh(const Tc& value);
    Tc cfp_asin(const Tc& value);
    Tc cfp_asinh(const Tc& value);
    Tc cfp_atan(const Tc& value);
    Tc cfp_atanh(const Tc& value);
    Tc cfp_bcp(const Tc& value);
    Tc cfp_bcp2(const Tc& value);
    Tc cfp_circle_fold_in(const Tc& value);
    Tc cfp_circle_fold_out(const Tc& value);
    Tc cfp_circle_reflect(const Tc& value);
    Tc cfp_cos(const Tc& value);
    Tc cfp_cosec(const Tc& value);
    Tc cfp_cosh(const Tc& value);
    Tc cfp_cotan(const Tc& value);
    Tc cfp_exp(const Tc& value);
    Tc cfp_inverse_fold_in(const Tc& value);
    Tc cfp_inverse_fold_out(const Tc& value);
    Tc cfp_inverse_reflect(const Tc& value);
    Tc cfp_log(const Tc& value);
    Tc cfp_multiply(const Tc& value);
    Tc cfp_power(const Tc& value);
    Tc cfp_product(const Tc& value);
    Tc cfp_rotation(const Tc& value);
    Tc cfp_sec(const Tc& value);
    Tc cfp_sin(const Tc& value);
    Tc cfp_sinh(const Tc& value);
    Tc cfp_tan(const Tc& value);
    Tc cfp_tanh(const Tc& value);
    Tc pair(const Tc& value);
    
    void setNumbers();

    COMPLEX_FUNCTION_PARAMETER m_id;
    bool m_pair;
    
    Function<T> m_real;
    Function<T> m_imaginary;
    Tc m_cp;
    T m_size;
    T m_size_squared;
    T m_rotation;
    T m_pi;
    T m_zero;
    T m_one;
    T m_two;
    T m_four;
    T m_eight;
    T m_half;
    T m_a_crossover;
    T m_b_crossover;
    T m_half_pi;
    T m_log_two;
    T m_quarter_pi;
    T m_costheta;
    T m_sintheta;
    T m_inf;
    T m_neg_inf;

    typedef std::map<COMPLEX_FUNCTION_PARAMETER, Tc (ComplexFunction::*)(const Tc&)> FunctionMap;
    FunctionMap m_functions;
    int m_precision;
};

template<typename T, typename Tc>
ComplexFunction<T, Tc>::ComplexFunction()
:
m_pair(false),
m_costheta(static_cast<T>(1)),
m_sintheta(static_cast<T>(0)),
m_precision(BASE_PRECISION)
{
    setNumbers();
    loadFunctions();
}

template<typename T, typename Tc>
ComplexFunction<T, Tc>::ComplexFunction(const ComplexFunction& other)
{
    operator=(other);
}

template<class T, typename Tc>
ComplexFunction<T, Tc>::~ComplexFunction()
{
}

template<class T, typename Tc>
const ComplexFunction<T, Tc> &ComplexFunction<T, Tc>::operator=(const ComplexFunction& other)
{
    setNumbers();
    loadFunctions();
    m_id = other.m_id;
    m_pair = other.m_pair;
    m_real = other.m_real;
    m_imaginary = other.m_imaginary;
    m_cp = other.m_cp;
    m_size = other.m_size;
    m_size_squared = other.m_size_squared;
    m_rotation = other.m_rotation;
    m_costheta = other.m_costheta;
    m_sintheta = other.m_sintheta;
    return *this;
}

template<class T, class Tc>
inline Tc ComplexFunction<T, Tc>::operator()(const Tc& z)
{
    return (this->*m_f)(z);
}


template<class T, class Tc>
void ComplexFunction<T, Tc>::setFunction(COMPLEX_FUNCTION_PARAMETER f)
{
    m_pair = false;
    m_id = f;
    assignFunction(f);
}

template<class T, class Tc>
void ComplexFunction<T, Tc>::setFunction(FUNCTION_PARAMETER fr, FUNCTION_PARAMETER fi)
{
    m_pair = true;
    m_real.setFunction(fr);
    m_imaginary.setFunction(fi);
    m_f = &ComplexFunction::pair;
}

template<class T, class Tc>
void ComplexFunction<T, Tc>::setParameter(const Tc& p)
{
    m_cp = p;
}

template<class T, class Tc>
void ComplexFunction<T, Tc>::setRealParameter(T p)
{
    m_real.setParameter(p);
}

template<class T, class Tc>
void ComplexFunction<T, Tc>::setImaginaryParameter(T p)
{
    m_imaginary.setParameter(p);
}

template<class T, class Tc>
void ComplexFunction<T, Tc>::loadFunctions()
{
    m_functions[CFP_NO_OP] = &ComplexFunction<T, Tc>::cfp_no_op;
    m_functions[CFP_ACOS] = &ComplexFunction<T, Tc>::cfp_acos;
    m_functions[CFP_ACOSH] = &ComplexFunction<T, Tc>::cfp_acosh;
    m_functions[CFP_ASIN] = &ComplexFunction<T, Tc>::cfp_asin;
    m_functions[CFP_ASINH] = &ComplexFunction<T, Tc>::cfp_asinh;
    m_functions[CFP_ATAN] = &ComplexFunction<T, Tc>::cfp_atan;
    m_functions[CFP_ATANH] = &ComplexFunction<T, Tc>::cfp_atanh;
    m_functions[CFP_BCP] = &ComplexFunction<T, Tc>::cfp_bcp;
    m_functions[CFP_BCP2] = &ComplexFunction<T, Tc>::cfp_bcp2;
    m_functions[CFP_CIRCLE_FOLD_OUT] = &ComplexFunction<T, Tc>::cfp_circle_fold_out;
    m_functions[CFP_CIRCLE_FOLD_IN] = &ComplexFunction<T, Tc>::cfp_circle_fold_in;
    m_functions[CFP_CIRCLE_REFLECT] = &ComplexFunction<T, Tc>::cfp_circle_reflect;
    m_functions[CFP_COS] = &ComplexFunction<T, Tc>::cfp_cos;
    m_functions[CFP_COSEC] = &ComplexFunction<T, Tc>::cfp_cosec;
    m_functions[CFP_COSH] = &ComplexFunction<T, Tc>::cfp_cosh;
    m_functions[CFP_COTAN] = &ComplexFunction<T, Tc>::cfp_cotan;
    m_functions[CFP_EXP] = &ComplexFunction<T, Tc>::cfp_exp;
    m_functions[CFP_INVERSE_FOLD_OUT] = &ComplexFunction<T, Tc>::cfp_inverse_fold_out;
    m_functions[CFP_INVERSE_FOLD_IN] = &ComplexFunction<T, Tc>::cfp_inverse_fold_in;
    m_functions[CFP_INVERSE_REFLECT] = &ComplexFunction<T, Tc>::cfp_inverse_reflect;
    m_functions[CFP_MULTIPLY] = &ComplexFunction<T, Tc>::cfp_multiply;
    m_functions[CFP_LOG] = &ComplexFunction<T, Tc>::cfp_log;
    m_functions[CFP_POWER] = &ComplexFunction<T, Tc>::cfp_power;
    m_functions[CFP_PRODUCT] = &ComplexFunction<T, Tc>::cfp_product;
    m_functions[CFP_ROTATION] = &ComplexFunction<T, Tc>::cfp_rotation;
    m_functions[CFP_SEC] = &ComplexFunction<T, Tc>::cfp_sec;
    m_functions[CFP_SIN] = &ComplexFunction<T, Tc>::cfp_sin;
    m_functions[CFP_SINH] = &ComplexFunction<T, Tc>::cfp_sinh;
    m_functions[CFP_TAN] = &ComplexFunction<T, Tc>::cfp_tan;
    m_functions[CFP_TANH] = &ComplexFunction<T, Tc>::cfp_tanh;
}

template<class T, class Tc>
void ComplexFunction<T, Tc>::assignFunction(COMPLEX_FUNCTION_PARAMETER f)
{
    m_f = (m_functions.count(f) != 1 ? &ComplexFunction::cfp_no_op : m_functions[f]);
}

//==============================================================================
// Complex Function Parameters
//==============================================================================

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_no_op(const Tc& z)
{
    return z;
}


template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_bcp(const Tc& value)
{
    Tc z = value;
    T z_m = abs(z); // complex abs
    T z_a;
    T z_r = real(z);
    T z_i = imag(z);
    if (z_m != m_zero)
    {
        // z_m has to be non-zero ln of zero is invalid.
        z_a = atan(z_i/z_r);
        if (z_r < m_zero)
        {
            //if (z_i > 0))
            // angle is in the wrong quadrant add PI to correct
            z_a += m_pi;
        }
        // ln(z^A)
        z_r = real(m_cp)*log(z_m) - imag(m_cp)*z_a;
        z_i = imag(m_cp)*log(z_m) + real(m_cp)*z_a;
        // exp(ln(z^A)) in polar form
        z_m = exp(z_r);
        z_a = z_i;
        // Convert to cartesian form and add constant
        z_r = z_m*cos(z_i);
        z_i = z_m*sin(z_i);
        z = Tc(z_r, z_i);
    }
    return z;
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_bcp2(const Tc& value)
{
    Tc z = value;
    T z_m = abs(z); // complex abs
    T z_a;
    T z_r = real(z);
    T z_i = imag(z);
    if (z_m != m_zero)
    {
        // z_m has to be non-zero ln of zero is invalid.
        z_a = atan(z_i/z_r);
        // Omit angle adjustment for the correct quadrant
        // ln(z^A)
        z_r = real(m_cp)*log(z_m) - imag(m_cp)*z_a;
        z_i = imag(m_cp)*log(z_m) + real(m_cp)*z_a;
        // exp(ln(z^A)) in polar form
        z_m = exp(z_r);
        z_a = z_i;
        // Convert to cartesian form and add constant
        z_r = z_m*cos(z_i);
        z_i = z_m*sin(z_i);
        z = Tc(z_r, z_i);
    }
    return z;
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_circle_fold_in(const Tc& z)
{
    T normz = norm(z);
    return (normz > m_size_squared ? Tc(m_size_squared*real(z), m_size_squared*imag(z))/normz : z);
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_circle_fold_out(const Tc& z)
{
    T normz = norm(z);
    return (normz < m_size_squared ? Tc(m_size_squared*real(z), m_size_squared*imag(z))/normz : z);
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_circle_reflect(const Tc& z)
{
    T normz = norm(z);
    return Tc(m_size_squared*real(z), m_size_squared*imag(z))/normz;
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_cos(const Tc& z)
{
    return cos(z);
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_cosec(const Tc& z)
{
    return m_one/sin(z);
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_cosh(const Tc& z)
{
    return cosh(z);
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_cotan(const Tc& z)
{
    return m_one/tan(z);
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_exp(const Tc& z)
{
    return exp(z);
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_inverse_fold_in(const Tc& z)
{
    return (norm(z) > m_size_squared ? m_size_squared/z : z);
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_inverse_fold_out(const Tc& z)
{
    return (norm(z) < m_size_squared ? m_size_squared/z : z);
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_inverse_reflect(const Tc& z)
{
    return m_size_squared/z;
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_log(const Tc& z)
{
    return log(z);
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_multiply(const Tc& z)
{
    return z*m_cp;
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_power(const Tc& z)
{
    return pow(z, m_cp);
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_product(const Tc& z)
{
    return Tc(z.real()*z.imag(), m_zero);
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_rotation(const Tc& z)
{
    // Rotate about the origin
    T z_r = z.real()*m_costheta - z.imag()*m_sintheta;
    T z_i = z.real()*m_sintheta + z.imag()*m_costheta;
    return Tc(z_r, z_i);
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_sec(const Tc& z)
{
    return m_one/cos(z);
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_sin(const Tc& z)
{
    return sin(z);
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_sinh(const Tc& z)
{
    return sinh(z);
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_tan(const Tc& z)
{
    return tan(z);
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::cfp_tanh(const Tc& z)
{
    return tanh(z);
}

template<class T, class Tc>
Tc ComplexFunction<T, Tc>::pair(const Tc& z)
{
    return Tc(m_real(z.real()), m_imaginary(z.imag()));
}

