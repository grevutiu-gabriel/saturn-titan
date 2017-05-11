// 
// File:   Function.h
// Author: M.R.Eggleston
//
// Created on 19 April 2012, 16:35
//

#pragma once

#include "KeyString.h"
#include "TypesAndConstants.h"

template<class T>
class Function
{
public:
    Function();
    Function(const Function &other);
    const Function &operator=(const Function &other);
    virtual ~Function();
    
    T operator()(T x);
    
    void setFunction(const std::string& f);
    void setFunction(FUNCTION_PARAMETER f);
    void setParameter(T p);

    bool hasParameter(FUNCTION_PARAMETER p);

private:
    void loadFunctions();
    void assignFunction(FUNCTION_PARAMETER F);
    T (Function::*m_f)(T value);
    T fp_no_op(T value);
    T fp_reverse_sign(T value);
    T fp_unsign(T value);
    T fp_sign(T value);
    T fp_add(T value);
    T fp_acos(T value);
    T fp_asin(T value);
    T fp_atan(T value);
    T fp_ceiling(T value);
    T fp_cos(T value);
    T fp_cosec(T value);
    T fp_cosh(T value);
    T fp_cotan(T value);
    T fp_exp(T value);
    T fp_floor(T value);
    T fp_log(T value);
    T fp_number(T value);
    T fp_power(T value);
    T fp_round(T value);
    T fp_scale(T value);
    T fp_sec(T value);
    T fp_sin(T value);
    T fp_sinh(T value);
    T fp_tan(T value);
    T fp_tanh(T value);
    T fp_trunc(T value);
    
    FUNCTION_PARAMETER m_id;

    typedef std::map<FUNCTION_PARAMETER, T (Function::*)(T)> FunctionMap;

    int m_precision;
    T m_one;
    T m_p;
    FunctionMap m_functions;
};

template <class T>
Function<T>::Function()
:
m_id(FP_NO_OP),
m_precision(BASE_PRECISION),
m_p(T(0.0L))
{
    loadFunctions();
}

template<typename T>
Function<T>::Function(const Function& other)
{
    operator=(other);
}

template <class T>
Function<T>::~Function()
{
}

template<class T>
const Function<T> &Function<T>::operator=(const Function& other)
{
    loadFunctions();
    m_id = other.m_id;
    m_precision = other.m_precision;
    m_one = other.m_one;
    m_p = other.m_p;
    return *this;
}

template <class T>
T Function<T>::operator()(T x)
{
    return (this->*m_f)(x);
}

template <class T>
bool Function<T>::hasParameter(FUNCTION_PARAMETER p)
{
    return (p == FP_ADD) || (p == FP_SCALE) || (p == FP_NUMBER) || (p == FP_POWER);
}

template <class T>
void Function<T>::setFunction(FUNCTION_PARAMETER f)
{
    m_id = f;
    assignFunction(f);
}
    
template <class T>
void Function<T>::setParameter(T p)
{
    m_p = p;
}

template <class T>
void Function<T>::loadFunctions()
{
    m_functions[FP_NO_OP] = &Function<T>::fp_no_op;
    m_functions[FP_REVERSE_SIGN] = &Function<T>::fp_reverse_sign;
    m_functions[FP_UNSIGN] = &Function<T>::fp_unsign;
    m_functions[FP_SIGN] = &Function<T>::fp_sign;
    m_functions[FP_ADD] = &Function<T>::fp_add;
    m_functions[FP_ACOS] = &Function<T>::fp_acos;
    m_functions[FP_ASIN] = &Function<T>::fp_asin;
    m_functions[FP_ATAN] = &Function<T>::fp_atan;
    m_functions[FP_CEILING] = &Function<T>::fp_ceiling;
    m_functions[FP_COS] = &Function<T>::fp_cos;
    m_functions[FP_COSEC] = &Function<T>::fp_cosec;
    m_functions[FP_COSH] = &Function<T>::fp_cosh;
    m_functions[FP_COTAN] = &Function<T>::fp_cotan;
    m_functions[FP_EXP] = &Function<T>::fp_exp;
    m_functions[FP_FLOOR] = &Function<T>::fp_floor;
    m_functions[FP_LOG] = &Function<T>::fp_log;
    m_functions[FP_NUMBER] = &Function<T>::fp_number;
    m_functions[FP_POWER] = &Function<T>::fp_power;
    m_functions[FP_ROUND] = &Function<T>::fp_round;
    m_functions[FP_SCALE] = &Function<T>::fp_scale;
    m_functions[FP_SEC] = &Function<T>::fp_sec;
    m_functions[FP_SIN] = &Function<T>::fp_sin;
    m_functions[FP_SINH] = &Function<T>::fp_sinh;
    m_functions[FP_TAN] = &Function<T>::fp_tan;
    m_functions[FP_TANH] = &Function<T>::fp_tanh;
    m_functions[FP_TRUNC] = &Function<T>::fp_trunc;
}

template <class T>
void Function<T>::assignFunction(FUNCTION_PARAMETER f)
{
    m_f = (m_functions.count(f) != 1 ? &Function::fp_no_op : m_functions[f]);
}

//==============================================================================
// Function Parameters
//==============================================================================

template <class T>
T Function<T>::fp_no_op(T value)
{
    return value;
}

template <class T>
T Function<T>::fp_reverse_sign(T value)
{
    return -value;
}

template <class T>
T Function<T>::fp_add(T value)
{
    return value + m_p;
}

template <class T>
T Function<T>::fp_number(T)
{
    // Input parameter deliberately ignored
    return m_p;
}

template <class T>
T Function<T>::fp_scale(T value)
{
    return value*m_p;
}

