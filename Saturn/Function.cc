// 
// File:   Function.cc
// Author: M.R.Eggleston
// 
// Created on 19 April 2012, 16:35
//

#include <iostream>

#include "mpreal.h"
#include "Function.h"
#include "KeyString.h"
#include "StaticCalculatingUnit.h"
#include "Utilities.h"

// Necessary specialisations of Function<T>

template<>
void Function<long double>::setFunction(const std::string &f)
{
    KeyString keys(f);
    setFunction(static_cast<FUNCTION_PARAMETER>(keys.GetKeyAsInt("id", 0)));
    if (hasParameter(m_id))
    {
        m_p = keys.GetKeyAsLongDouble("p", 0.0L);
    }
}

template <>
void Function<MpReal>::setFunction(const std::string &f)
{
    KeyString keys(f);
    setFunction(static_cast<FUNCTION_PARAMETER>(keys.GetKeyAsInt("id", 0)));
    if (hasParameter(m_id))
    {
        m_p = MpReal(keys.GetKey("p", "0"), m_precision);
    }
    m_precision = StaticCalculatingUnit::s_precision;
    m_one = MpReal("1", m_precision);
}

template <>
MpReal Function<MpReal>::fp_trunc(MpReal value)
{
    return mpfr::trunc(value);
}

template <>
long double Function<long double>::fp_trunc(long double value)
{
    // not std::trunc as it is not supported by MS C++
    return (value < 0.0L ? ceil(value) : floor(value));
}

template<>
long double Function<long double>::fp_round(long double value)
{
    return fp_trunc(value < 0.0L ? value - 0.5L : value + 0.5L);
}

template<>
MpReal Function<MpReal>::fp_round(MpReal value)
{
    return mpfr::round(value);
}

template <>
long double Function<long double>::fp_unsign(long double value)
{
    return std::abs(value);
}

template <>
MpReal Function<MpReal>::fp_unsign(MpReal value)
{
    return mpfr::abs(value);
}

template <>
long double Function<long double>::fp_sign(long double value)
{
    return -std::abs(value);
}

template <>
MpReal Function<MpReal>::fp_sign(MpReal value)
{
    return -mpfr::abs(value);
}

template <>
long double Function<long double>::fp_acos(long double value)
{
    return std::acos(value - fp_trunc(value));
}

template <>
MpReal Function<MpReal>::fp_acos(MpReal value)
{
    return mpfr::acos(value - fp_trunc(value));
}

template <>
long double Function<long double>::fp_asin(long double value)
{
    return std::asin(value - fp_trunc(value));
}

template <>
MpReal Function<MpReal>::fp_asin(MpReal value)
{
    return mpfr::asin(value - fp_trunc(value));
}

template <>
long double Function<long double>::fp_atan(long double value)
{
    return std::atan(value);
}

template <>
MpReal Function<MpReal>::fp_atan(MpReal value)
{
    return mpfr::atan(value);
}

template <>
long double Function<long double>::fp_ceiling(long double value)
{
    return std::ceil(value);
}

template <>
MpReal Function<MpReal>::fp_ceiling(MpReal value)
{
    return mpfr::ceil(value);
}

template <>
long double Function<long double>::fp_cos(long double value)
{
    return std::cos(value);
}

template <>
MpReal Function<MpReal>::fp_cos(MpReal value)
{
    return mpfr::cos(value);
}

template <>
long double Function<long double>::fp_cosec(long double value)
{
    return 1.0L/std::sin(value);
}

template <>
MpReal Function<MpReal>::fp_cosec(MpReal value)
{
    return m_one/mpfr::sin(value);
}

template <>
long double Function<long double>::fp_cosh(long double value)
{
    return std::cosh(value);
}

template <>
MpReal Function<MpReal>::fp_cosh(MpReal value)
{
    return mpfr::cosh(value);
}

template <>
long double Function<long double>::fp_cotan(long double value)
{
    return 1.0L/std::tan(value);
}

template <>
MpReal Function<MpReal>::fp_cotan(MpReal value)
{
    return m_one/mpfr::tan(value);
}

template <>
long double Function<long double>::fp_exp(long double value)
{
    return std::exp(value);
}

template <>
MpReal Function<MpReal>::fp_exp(MpReal value)
{
    return mpfr::exp(value);
}

template <>
long double Function<long double>::fp_floor(long double value)
{
    return std::floor(value);
}

template <>
MpReal Function<MpReal>::fp_floor(MpReal value)
{
    return mpfr::floor(value);
}

template <>
long double Function<long double>::fp_log(long double value)
{
    return std::log(std::abs(value));
}

template <>
MpReal Function<MpReal>::fp_log(MpReal value)
{
    return mpfr::log(mpfr::abs(value));
}

template <>
long double Function<long double>::fp_power(long double value)
{
    return std::pow(value, m_p);
}

template <>
MpReal Function<MpReal>::fp_power(MpReal value)
{
    return mpfr::pow(value, m_p);
}

template <>
long double Function<long double>::fp_sec(long double value)
{
    return 1.0L/std::cos(value);
}

template <>
MpReal Function<MpReal>::fp_sec(MpReal value)
{
    return m_one/mpfr::cos(value);
}

template <>
long double Function<long double>::fp_sin(long double value)
{
    return std::sin(value);
}

template <>
MpReal Function<MpReal>::fp_sin(MpReal value)
{
    return mpfr::sin(value);
}

template <>
long double Function<long double>::fp_sinh(long double value)
{
    return std::sinh(value);
}

template <>
MpReal Function<MpReal>::fp_sinh(MpReal value)
{
    return mpfr::sinh(value);
}

template <>
long double Function<long double>::fp_tan(long double value)
{
    return std::tan(value);
}

template <>
MpReal Function<MpReal>::fp_tan(MpReal value)
{
    return mpfr::tan(value);
}

template <>
long double Function<long double>::fp_tanh(long double value)
{
    return std::tanh(value);
}

template <>
MpReal Function<MpReal>::fp_tanh(MpReal value)
{
    return mpfr::tanh(value);
}

