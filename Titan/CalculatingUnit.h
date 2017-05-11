//
// File:   CalculatingUnit.h
// Author: M.R.Eggleston
//
// Created on 08 March 2012, 17:50
//

#pragma once

#include <iostream>
#include <limits>
#include "CalculatingUnitGeneric.h"
#include "ComplexFunction.h"
#include "FractalConfig.h"
#include "Function.h"
#include "StaticCalculatingUnit.h"
#include "Transform.h"
#include "Utilities.h"

// template with MpReal or long double passed as the type T ...
// the interface however will have MpReal in and long double out.


template<class T1, class T2>
class CalculatingUnit
{
public:
    CalculatingUnit();
    virtual ~CalculatingUnit();
    
    void setFractal();
    
    void setValues(long iteration, long chunk_size);
    void setLyapunov();
    bool calculate();
    bool calculateLyapunovSettlingCycle();
    bool calculateLyapunovCalculatingCycle(unsigned int cycle);
    void calculateLyapunovRowByRow();
    void calculateOrbits();
    void calculateOrbit();
    void enableProgressSignals(bool value);
    void sendProgressSignals(bool value);

    void set_generic(CalculatingUnitGeneric *p);

private:
    CalculatingUnit(const CalculatingUnit& orig);
    
    void updateParameters(); // Substitute parameters with c as required

    // There are several versions of the calculate routines one set is called
    // if there are transforms and results are not retained, transforms and
    // results retained, no transforms with results retained and no transforms
    // without results reatined.
    // Where results are retained different colouring options
    // can be used without recalculating the fractal
    void calculate0r(); // collect no extra data
    void calculate1r(); // collect 1 results set
    void calculate2r(); // collect 2 results set
    void calculate0tr(); // collect no extra data
    void calculate1tr(); // collect 1 results set
    void calculate2tr(); // collect 2 results set
    
    // These routines use a local ResultsSet which is reused
    void calculate0(); // collect no extra data
    void calculate1(); // collect 1 results set
    void calculate2(); // collect 2 results set
    void calculate0t(); // collect no extra data
    void calculate1t(); // collect 1 results set
    void calculate2t(); // collect 2 results set
    
    void calculateOrbitsT(); // with transforms
    void calculateOrbitsNT(); // without transforms

    void calculateOrbitT(); // with transforms
    void calculateOrbitNT(); // without transforms

    void collectResults1();
    void collectResults2();
    
    void set_fractal_parameters();
    void set_transforms();
    
    T2 transform(const T2& z);
    
    // Function parameters
    void assignFunctionParameter(int index, int  number_of_parameters);
    
    // Complex Function parameters
    void assignComplexFunctionParameter(int index, int number_of_parameters);

    void formula();
    void formula_so();
    void mandelbrot();
    void quadratic();
    void cubic();
    void almost_cubic();
    void single_function();
    void zcpac();
    void cpowerz();
    void two_function_product();
    void unnamed();
    void zptanczac();
    void combination();
    void tzaccp();
    void biomorph1();
    void biomorph2();
    void biomorph3();
    void biomorph4();
    void biomorph5();
    void magnet();
    void magnet2();
    void zazbcgd();
    void combination2();
    void nova();
    void sqrtcp();
    void nova_1();
    void nova_2();
    void unnamed_2();
    void quartic();
    void quintic();
    void zcptanz();
    void compasses();
    void rn_mandelbrot();
    void pickover_popcorn_4_function();
    void hybrid();
    void zduccpac();
    void mallard();
    void pickover_popcorn_6_function();
    void tzcpac();
    void tmallard();
    void fzcpac();
    void ftzcpac();
    void zaccp();
    void cczcpaczcp();
    void onion_4_function();
    void combination3();
    void c2mfczac();
    void c2dfczac();
    void single_3f_onion();
    void double_3f_onion_m();
    void double_3f_onion_d();
    void m3();
    void m4();
    void m5();
    void m6();
    void m7();
    void m8();
    void m9();
    void m10();
    void attractors();
    void general_mixture();
    void mixture();
    void mixture2();
    void mixture3();
    void mixture4();
    void pr_mandelbrot_2();
    void pr_mandelbrot_3();
    void pr_single_function_2();
    void hop();
    void quadrup_2();
    void threeply();
    void threeply2();
    void chip();
    void gumowski_mira();
    void hexic();
    void heptic();
    void mandelbrot_division();
    void octic();
    
    T2 unsign(const T2& z);
    T2 unsigni(const T2& z);
    T1 signum(const T1& x);

    bool bailout();
    bool convergent_bailout();
    bool divergent_bailout();
    bool gt_abs();
    bool gt_norm();
    bool gt_imag();
    bool gt_imag2();
    bool gt_real();
    bool gt_real2();
    bool gt_manhattan();
    bool gt_manhattanish();
    bool gt_abs_manhattanish();
    bool gt_max2();
    bool gt_min2();
    bool gt_absproduct();
    bool gt_absdiff();
    bool lt_abs();
    bool lt_norm();
    bool lt_imag();
    bool lt_imag2();
    bool lt_real();
    bool lt_real2();
    bool lt_manhattan();
    bool lt_manhattanish();
    bool lt_abs_manhattanish();
    bool lt_max2();
    bool lt_min2();
    bool lt_absproduct();
    bool lt_absdiff();
    
    void setNumbers();
    
    void angleResults1();
    void angleResults2();
    void magnitudeResults1();
    void magnitudeResults2();
    void gaussianResults1();
    void gaussianResults2();
    void orbitTrapResults1();
    void orbitTrapResults2();
    void resultStatistics1(long double value);
    void resultStatistics2(long double value);
    long double magnitude(const LongComplex& z, bool second);
    long double magnitude_option(const LongComplex& z, char option);
    LongComplex gi_ceil(const LongComplex& z);
    LongComplex gi_floor(const LongComplex& z);
    LongComplex gi_round(const LongComplex& z);
    LongComplex gi_trunc(const LongComplex& z);
    void progress(int row);
    void so_progress(long plot, long no_plot);

    T2 m_z;
    T2 m_z2; // z squared
    T2 m_z3; // z cubed
    T2 m_z4; // z to the fourth power
    T2 m_old_z;
    T2 m_c;
    T1 m_c_r;
    T1 m_c_i;
    
    // These must not be static as any complex parameter may be set to c
    T2 m_alpha;
    T2 m_beta;
    T2 m_gamma;
    T2 m_delta;
    T2 m_epsilon;
    T2 m_zeta;
    T2 m_eta;
    T2 m_theta;
    T2 m_iota;
    
    // Working variables for sub values in fractal formula
    T2 m_a;
    T2 m_b;
    T2 m_q; // quotient
    T2 m_d; // divisor, can also be used as a spare working variable
    
    // Non complex Working variables in fractal formula 
    T1 m_x;
    T1 m_y;
    T1 m_r;
    T1 m_i;

    PARAMETER_TYPE m_alpha_type;
    PARAMETER_TYPE m_beta_type;
    PARAMETER_TYPE m_gamma_type;
    PARAMETER_TYPE m_delta_type;
    PARAMETER_TYPE m_epsilon_type;
    PARAMETER_TYPE m_zeta_type;
    PARAMETER_TYPE m_eta_type;
    PARAMETER_TYPE m_theta_type;
    PARAMETER_TYPE m_iota_type;

    T1 m_p0;
    T1 m_p1;
    T1 m_p2;
    T1 m_p3;
    T1 m_p4;
    T1 m_p5;
    T1 m_p6;
    T1 m_p7;
    
    Function<T1> m_f0;
    Function<T1> m_f1;
    Function<T1> m_f2;
    Function<T1> m_f3;
    Function<T1> m_f4;
    Function<T1> m_f5;
    Function<T1> m_f6;
    Function<T1> m_f7;
   
    ComplexFunction<T1, T2> m_cf0;
    ComplexFunction<T1, T2> m_cf1;
    ComplexFunction<T1, T2> m_cf2;
    ComplexFunction<T1, T2> m_cf3;
    ComplexFunction<T1, T2> m_cf4;
    ComplexFunction<T1, T2> m_cf5;
    ComplexFunction<T1, T2> m_cf6;
    ComplexFunction<T1, T2> m_cf7;
    
    std::vector<Transform<T1, T2>> m_transform;
    
    unsigned int m_sequence_index;
    
    // Numbers these will need to be reset every time the configuration is loaded
    // by calling setNumbers, this will ensure the correct precision is used
    // when the class is instantiated with the multi-precision type.
    T1 m_zero;
    T1 m_one;
    T1 m_two;
    T1 m_three;
    T1 m_max;
    T1 m_ln2;
    T1 m_inf;
    long double m_ld_inf;
    long double m_pi;

    // Statistics
    ResultsSet *m_rs;
    
    long m_iteration;
    long m_max_iteration;
    
    bool m_has_transforms;
    long double m_z_r;
    long double m_z_i;
    long double m_old_z_r;
    long double m_old_z_i;
    long double m_limit;
    bool m_convergent;
    char m_quotient[2];
    char m_divisor[2];
    char m_magnitude_type[2];
    //
    // Orbit data
    VectorLongComplex m_orbit;
    int m_orbit_length;
    
    // Lyapunov data
    VectorBool m_sequence;
    int m_num_in_sequence;
    //
    boost::mutex m_progress_signal_mutex;
    bool m_progress_signals_enabled;
    bool m_send_progress;

    CalculatingUnitGeneric *m_generic;
    bool m_finished;
};

template<class T1, class T2>
CalculatingUnit<T1, T2>::CalculatingUnit()
:
m_alpha_type(PT_NUMBER),
m_beta_type(PT_NUMBER),
m_gamma_type(PT_NUMBER),
m_delta_type(PT_NUMBER),
m_epsilon_type(PT_NUMBER),
m_zeta_type(PT_NUMBER),
m_eta_type(PT_NUMBER),
m_theta_type(PT_NUMBER),
m_sequence_index(0),
m_iteration(0),
m_num_in_sequence(0),
m_progress_signals_enabled(false),
m_send_progress(false),
m_finished(true)
{
}

template<class T1, class T2>
CalculatingUnit<T1, T2>::~CalculatingUnit()
{
}

template<class T1, class T2>
void CalculatingUnit<T1, T2>::setFractal()
{
    setNumbers();
    set_fractal_parameters();
    set_transforms();
    m_convergent = StaticCalculatingUnit::s_convergent;
    for (int i = 0; i < 2; i++)
    {
        m_divisor[i] = StaticCalculatingUnit::s_divisor[i];
        m_quotient[i] =  StaticCalculatingUnit::s_quotient[i];
        m_magnitude_type[i] = StaticCalculatingUnit::s_magnitude_type[i];
    }
}

template<class T1, class T2>
void CalculatingUnit<T1, T2>::setValues(long iteration, long chunk_size)
{
    m_iteration = iteration;
    m_max_iteration = iteration + chunk_size;
}

template<class T1, class T2>
void CalculatingUnit<T1, T2>::setLyapunov()
{
   // set lyapunov sequence buffer
    std::string sequence_string = StaticCalculatingUnit::s_config.getLyapunovSequence();
    if (sequence_string.empty())
    {
        sequence_string = "AB";
    }
    m_num_in_sequence = sequence_string.length();
    m_sequence.resize(m_num_in_sequence);
    for (auto i = 0; i < m_num_in_sequence; i++)
    {
        m_sequence[i] = (sequence_string[i] == 'A');
    }
}

template<class T1, class T2>
void CalculatingUnit<T1, T2>::assignFunctionParameter(int index, int  number_of_parameters)
{
    if (index < number_of_parameters)
    {
        auto function = StaticCalculatingUnit::s_config.getFunctionParameter(index);
        switch (index)
        {
        case 0:
            m_f0.setFunction(function);
            break;
        case 1:
            m_f1.setFunction(function);
            break;
        case 2:
            m_f2.setFunction(function);
            break;
        case 3:
            m_f3.setFunction(function);
            break;
        case 4:
            m_f4.setFunction(function);
            break;
        case 5:
            m_f5.setFunction(function);
            break;
        case 6:
            m_f6.setFunction(function);
            break;
        case 7:
            m_f7.setFunction(function);
            break;
        default:
            break;
        }
    }
}

template<class T1, class T2>
void CalculatingUnit<T1, T2>::assignComplexFunctionParameter(int index, int number_of_parameters)
{
    if (index < number_of_parameters)
    {
        auto id = StaticCalculatingUnit::s_config.getComplexFunctionParameter(index);
        switch (index)
        {
        case 0:
            m_cf0.setFunction(id);
            break;
        case 1:
            m_cf1.setFunction(id);
            break;
        case 2:
            m_cf2.setFunction(id);
            break;
        case 3:
            m_cf3.setFunction(id);
            break;
        case 4:
            m_cf4.setFunction(id);
            break;
        case 5:
            m_cf5.setFunction(id);
            break;
        default:
            break;
        }
    }
}

//==============================================================================
// Formulae
//==============================================================================


template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::formula()
{
    switch (StaticCalculatingUnit::s_type)
    {
    default:
    case F_MANDELBROT: mandelbrot(); break;
    case F_QUADRATIC: quadratic(); break;
    case F_CUBIC: cubic(); break;
    case F_ALMOST_CUBIC: almost_cubic(); break;
    case F_SINGLE_FUNCTION: single_function(); break;
    case F_ZCPAC: zcpac(); break;
    case F_2F_PRODUCT: two_function_product(); break;
    case F_C_POWER_Z: cpowerz(); break;
    case F_UNNAMED: unnamed(); break;
    case F_Z_POWER_TANCZ_AC: zptanczac(); break;
    case F_COMBINATION: combination(); break;
    case F_TZACCP: tzaccp(); break;
    case F_BIOMORPH_1: biomorph1(); break;
    case F_BIOMORPH_2: biomorph2(); break;
    case F_BIOMORPH_3: biomorph3(); break;
    case F_BIOMORPH_4: biomorph4(); break;
    case F_BIOMORPH_5: biomorph5(); break;
    case F_MAGNET: magnet(); break;
    case F_MAGNET_2: magnet2(); break;
    case F_ZAZBCGD: zazbcgd(); break;
    case F_COMBINATION_2: combination2(); break;
    case F_NOVA: nova(); break;
    case F_NOVA_1: nova_1(); break;
    case F_NOVA_2: nova_2(); break;
    case F_SQRT_CP: sqrtcp(); break;
    case F_UNNAMED_2: unnamed_2(); break;
    case F_QUARTIC: quartic(); break;
    case F_QUINTIC: quintic(); break;
    case F_ZCPTANZ: zcptanz(); break;
    case F_COMPASSES: compasses(); break;
    case F_RN_MANDELBROT: rn_mandelbrot(); break;
    case F_PICKOVER_POPCORN_6F: pickover_popcorn_6_function(); break;
    case F_HYBRID: hybrid(); break;
    case F_ZDUCCPAC: zduccpac(); break;
    case F_MALLARD: mallard(); break;
    case F_TZCPAC: tzcpac(); break;
    case F_TMALLARD: tmallard(); break;
    case F_FZCPAC: fzcpac(); break;
    case F_FTZCPAC: ftzcpac(); break;
    case F_ZACCP: zaccp(); break;
    case F_PICKOVER_POPCORN_4F: pickover_popcorn_4_function(); break;
    case F_CCZCPACZCP: cczcpaczcp(); break;
    case F_ONION_4F: onion_4_function(); break;
    case F_COMBINATION_3: combination3(); break;
    case F_C2MFCZAC: c2mfczac(); break;
    case F_C2DFCZAC: c2dfczac(); break;
    case F_SINGLE_3F_ONION: single_3f_onion(); break;
    case F_DOUBLE_3F_ONION_M: double_3f_onion_m(); break;
    case F_DOUBLE_3F_ONION_D: double_3f_onion_d(); break;
    case F_M3: m3(); break;
    case F_M4: m4(); break;
    case F_M5: m5(); break;
    case F_M6: m6(); break;
    case F_M7: m7(); break;
    case F_M8: m8(); break;
    case F_M9: m9(); break;
    case F_M10: m10(); break;
    case F_ATTRACTORS: attractors(); break;
    case F_GENERAL_MIXTURE: general_mixture(); break;
    case F_MIXTURE: mixture(); break;
    case F_MIXTURE_2: mixture2(); break;
    case F_MIXTURE_3: mixture3(); break;
    case F_MIXTURE_4: mixture4(); break;
    case F_PR_MANDELBROT_2: pr_mandelbrot_2(); break;
    case F_PR_MANDELBROT_3: pr_mandelbrot_3(); break;
    case F_PR_SINGLE_FUNCTION_2: pr_single_function_2(); break;
    case F_HOP: hop(); break;
    case F_QUADRUP_2: quadrup_2(); break;
    case F_THREEPLY: threeply(); break;
    case F_THREEPLY_2: threeply2(); break;
    case F_CHIP: chip(); break;
    case F_GUMOWSKI_MIRA: gumowski_mira(); break;
    case F_HEXIC: hexic(); break;
    case F_HEPTIC: heptic(); break;
    case F_MANDELBROT_DIVISION: mandelbrot_division(); break;
    case F_OCTIC: octic(); break;
    }
}

template<class T1, class T2>
inline void CalculatingUnit<T1,T2>::formula_so()
{
    switch (StaticCalculatingUnit::s_type)
    {
    case F_ATTRACTORS_SO: attractors(); break;
    case F_HOP_SO: hop(); break;
    case F_QUADRUP_2_SO: quadrup_2(); break;
    case F_THREEPLY_SO: threeply(); break;
    case F_THREEPLY_2_SO: threeply2(); break;
    case F_CHIP_SO: chip(); break;
    case F_GUMOWSKI_MIRA_SO: gumowski_mira(); break;
    default: break;
    }
}

// The formula functions support both Mandelbrot and Julia algorithms if none
// of the parameters is c (by substitution) then it's Julia.

template<class T1, class T2>
inline void CalculatingUnit<T1,T2>::mandelbrot()
{
    m_z = m_z*m_z + m_alpha;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::quadratic()
{
    m_z = (m_alpha*m_z + m_beta)*m_z + m_gamma;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::cubic()
{
    m_z = (m_alpha*m_z*m_z + m_beta*m_z + m_gamma)*m_z + m_delta;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::almost_cubic()
{
    // CalculatingUnit found due to a mistake in implementation in assembler, mistake
    // shown at bottom of comment.
    //
    // z = Azzz + Bzz + Cz + const
    //
    // z = a + b*i  A = c + d*i  B = e + f*i  C = g + hi
    //
    // z*z = a*a + a*b*i + a*b*i + b*i*b*i = (a*a - b*b) + 2*a*b*i
    // z*z*z = a*(a*a - b*b) + a*(2*a*b*i) + b*i*(2*a*b*i) + b*i*(a*a - b*b)
    //       = (a*a*a - a*b*b) + 2*a*a*b*i + 2*a*b*i*b*i + a*a*b*i - b*b*b*i
    //       = (a*a*a - a*b*b - 2*a*b*b) + (2*a*a*b + a*a*b - b*b*b)*i
    //       = (a*a*a - 3*a*b*b) + (3*a*a*b - b*b*b)*i
    // z*z*z*A = ((aaa - 3abb) + (3aab - bbb)i )(c + di)
    //         = (aaa - 3abb)c - (3aab - bbb)d + ((3aab - bbb)c + (aaa - 3abb)d)i
    // z*z*B = ((aa - bb) + 2abi)(e + fi)
    //       = (aa - bb)e + (aa - bb)fi + 2abei +2abfii
    //       = (aa - bb)e - 2abf + ((aa - bb)f + 2abe)i
    // z*C   = (a + bi)(g + hi)
    //       = ag - bh + (ah + bg)i
    //
    // z real = (aaa - 3abb)c - (3aab - bbb)d + (aa - bb)e - 2abf + ag - bh
    // z imag = (3aab - bbb)c + (aaa - 3abb)d + (aa - bb)f + 2abe + ah + bg
    //                                         Mistake here: 2abc

    T1 c = real(m_alpha), d = imag(m_alpha);
    T1 e = real(m_beta), f = imag(m_beta);
    T1 g = real(m_gamma), h = imag(m_gamma);
    T1 z_r = real(m_z), z_i = imag(m_z);
    T1 epsilon_r = real(m_delta), epsilon_i = imag(m_delta);
    T1 a = z_r;
    T1 b = z_i;
    T1 aaam3abb = a*a*a - m_three*a*b*b;
    T1 aab3mbbb = m_three*a*a*b - b*b*b;
    T1 aambb = a*a - b*b;
    z_r = aaam3abb*c - aab3mbbb*d + aambb*e - m_two*a*b*f + a*g - b*h + epsilon_r;
    z_i = aaam3abb*d + aab3mbbb*c + aambb*f + m_two*a*b*c + a*h + b*g + epsilon_i;
    //                          Differs from cubic here ^
    m_z = T2(z_r, z_i);
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::single_function()
{
    m_z = m_cf0(m_alpha*m_z) + m_beta;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::zcpac()
{
    m_z = pow(m_z, m_alpha) + m_beta;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::cpowerz()
{
    m_z = pow(m_alpha, m_z) + m_beta;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::two_function_product()
{
    m_z = m_cf0(m_alpha*m_z)*m_cf1(m_beta*m_z) + m_gamma;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::unnamed()
{
    m_a = pow(m_z, m_alpha) + m_beta;
    m_b = pow(m_z, m_alpha) - m_beta;
    m_z = pow(m_a, m_gamma)/(m_z*pow(m_b, m_delta));
}

template<class T1, class T2>
inline void CalculatingUnit<T1,  T2>::unnamed_2()
{
    m_a = pow(m_z, m_alpha) + m_beta;
    m_b = pow(m_z, m_epsilon) - m_beta;
    m_z = pow(m_a, m_gamma)/(pow(m_z, m_delta)*pow(m_b, m_zeta));
}

template<class T1, class T2>
inline void CalculatingUnit<T1,  T2>::combination()
{
    m_z = m_alpha*pow(m_z, m_beta) + m_gamma*pow(m_z, m_delta) + m_epsilon;
}

template<class T1, class T2>
inline void CalculatingUnit<T1,  T2>::tzaccp()
{
    if (m_has_transforms)
    {
        m_z = pow(transform(m_z + m_alpha), m_beta);
    }
    else
    {
        m_z = pow(m_z + m_alpha, m_beta);
    }
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::zaccp()
{
    m_z = pow(m_z + m_alpha, m_beta);
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::biomorph1()
{
    m_z = pow(m_z, m_alpha) + pow(m_z, m_z) + m_beta;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::biomorph2()
{
    m_z = sin(m_z) + pow(m_z, m_alpha) + m_beta;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::biomorph3()
{
    m_z = exp(m_z) + pow(m_z, m_alpha) + m_beta;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::biomorph4()
{
    m_z = sin(m_z) + exp(m_z) + m_alpha;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::biomorph5()
{
    m_z = sinh(m_z) + m_alpha;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::zazbcgd()
{
    m_z = pow((pow(m_z, m_alpha) + pow(m_z, m_beta)*pow(m_gamma, m_delta)), m_epsilon);
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::combination2()
{
    m_z = m_alpha*m_beta*pow(m_z, m_gamma) + m_delta*pow(m_z, m_epsilon);
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::nova()
{
    m_old_z_r = m_z_r;
    m_old_z_i = m_z_i;
    if (m_has_transforms) m_z = transform(m_z);
    m_a = pow(m_z, m_beta - m_one);
    m_z = m_z - m_alpha*(m_a*m_z - m_one)/(m_beta*m_a) + m_gamma;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::zptanczac()
{
    m_z = pow(m_z, tan(m_alpha*m_z)) + m_beta;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::magnet()
{
    m_z = (m_z*m_z + m_alpha - m_one)/(m_two*m_z + m_alpha - m_two);
    m_z = m_z*m_z;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::magnet2()
{
    //
    // z = ((z^3 + 3(alpha - 1)z + (alpha - 1)(q - 2)/(3z^2 + 3(alpha - 2)z + alpha^2 - 3alpha + 3))^2
    //
    m_a = m_alpha - m_one;
    m_b = m_alpha - m_two;
    m_q = (m_z*m_z + m_three*m_a)*m_z + m_a*m_b;
    m_d = m_three*(m_z + m_b)*m_z + (m_alpha - m_three)*m_alpha + m_three;
    m_z = m_q/m_d;
    m_z = m_z*m_z;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::sqrtcp()
{
    m_z = sqrt(pow(m_z, m_alpha)) + m_beta;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::nova_1()
{
    m_old_z_r = m_z_r;
    m_old_z_i = m_z_i;
    if (m_has_transforms) m_z = transform(m_z);
    m_a = m_beta*pow(m_z, m_gamma - m_one);
    m_b = m_delta*pow(m_z, m_epsilon - m_one);
    m_q = (m_a - m_b)*m_z - m_one;
    m_d = m_gamma*m_a - m_epsilon*m_b;
    m_z = m_z - m_alpha*(m_q/m_d) + m_zeta;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::nova_2()
{
    m_old_z_r = m_z_r;
    m_old_z_i = m_z_i;
    if (m_has_transforms) m_z = transform(m_z);
    m_a = pow(m_z, m_beta - m_one);
    m_b = (m_delta - m_one)*pow(m_z, m_gamma - m_one);
    m_q = (m_a - m_b)*m_z - m_delta;
    m_d = m_beta*m_a - m_gamma*m_b;
    m_z = m_z - m_alpha*(m_q/m_d) + m_delta;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::quartic()
{
    m_z2 = m_alpha*m_z;
    m_z2 = (m_z2 + m_beta)*m_z;
    m_z2 = (m_z2 + m_gamma)*m_z;
    m_z = (m_z2 + m_delta)*m_z + m_epsilon;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::quintic()
{
    m_z2 = m_alpha*m_z;
    m_z2 = (m_z2 + m_beta)*m_z;
    m_z2 = (m_z2 + m_gamma)*m_z;
    m_z2 = (m_z2 + m_delta)*m_z;
    m_z = (m_z2 + m_epsilon)*m_z + m_zeta;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::hexic()
{
    m_z2 = m_alpha*m_z;
    m_z2 = (m_z2 + m_beta)*m_z;
    m_z2 = (m_z2 + m_gamma)*m_z;
    m_z2 = (m_z2 + m_delta)*m_z;
    m_z2 = (m_z2 + m_epsilon)*m_z;
    m_z = (m_z2 + m_zeta)*m_z + m_eta;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::heptic()
{
    m_z2 = m_alpha*m_z;
    m_z2 = (m_z2 + m_beta)*m_z;
    m_z2 = (m_z2 + m_gamma)*m_z;
    m_z2 = (m_z2 + m_delta)*m_z;
    m_z2 = (m_z2 + m_epsilon)*m_z;
    m_z2 = (m_z2 + m_zeta)*m_z;
    m_z = (m_z2 + m_eta)*m_z + m_theta;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::octic()
{
    m_z2 = m_alpha*m_z;
    m_z2 = (m_z2 + m_beta)*m_z;
    m_z2 = (m_z2 + m_gamma)*m_z;
    m_z2 = (m_z2 + m_delta)*m_z;
    m_z2 = (m_z2 + m_epsilon)*m_z;
    m_z2 = (m_z2 + m_zeta)*m_z;
    m_z2 = (m_z2 + m_eta)*m_z;
    m_z = (m_z2 + m_theta)*m_z + m_iota;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::zcptanz()
{
    m_z = pow(m_z, m_alpha)*tan(m_z) + m_beta;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::zduccpac()
{
    m_z = pow(m_z/unsign(m_beta), m_alpha) + m_beta;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::compasses()
{
    m_z = pow(m_z, m_alpha) - m_alpha*pow(m_beta, m_alpha - m_one)*m_z + m_gamma;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::rn_mandelbrot()
{
    m_x = real(m_z);
    m_y = imag(m_z);
    m_z = T2(m_x*m_x + real(m_alpha), m_y*m_y + imag(m_alpha));
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::pickover_popcorn_4_function()
{
    m_x = real(m_z);
    m_y = imag(m_z);
    m_r = m_x - m_p0*m_f0(m_y + m_f1(m_p1*m_y)) + real(m_alpha);
    m_i = m_y - m_p2*m_f2(m_x + m_f3(m_p3*m_x)) + imag(m_alpha);
    m_z = T2(m_r, m_i);
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::pickover_popcorn_6_function()
{
    m_x = real(m_z);
    m_y = imag(m_z);
    m_r = m_x - m_p0*m_f0(m_y + m_f1(m_p1*(m_y + m_f2(m_p2*m_y)))) + real(m_alpha);
    m_i = m_y - m_p3*m_f3(m_x + m_f4(m_p4*(m_x + m_f5(m_p5*m_x)))) + imag(m_alpha);
    m_z = T2(m_r, m_i);
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::hybrid()
{
    static T2 complex_i(T1(0), T1(1));
    T1 normz(norm(m_z) == 0.0L ? 1.0L : norm(m_z));
    if (m_has_transforms) m_z = transform(m_z);
    m_x = real(m_z)/normz;
    m_y = imag(m_z)/normz;
    m_z = m_alpha*pow(m_x, m_beta) + m_gamma*pow(m_y, m_delta)*complex_i + m_epsilon;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::mallard()
{
    m_z = pow(m_cf0(pow(m_z, m_alpha) + m_beta), m_gamma);
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::fzcpac()
{
    m_z = m_cf0(pow(m_z, m_alpha) + m_beta);
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::ftzcpac()
{
    if (m_has_transforms)
    {
        m_z = m_cf0(transform(pow(m_z, m_alpha)) + m_beta);
    }
    else
    {
        m_z = m_cf0(pow(m_z, m_alpha) + m_beta);
    }
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::tzcpac()
{
    if (m_has_transforms)
    {
        m_z = transform(pow(m_z, m_alpha)) + m_beta;
    }
    else
    {
        m_z = pow(m_z, m_alpha) + m_beta;
    }
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::tmallard()
{
    if (m_has_transforms)
    {
        m_z = pow(m_cf0(transform(pow(m_z, m_alpha)) + m_beta), m_gamma);
    }
    else
    {
        m_z = pow(m_cf0(pow(m_z, m_alpha) + m_beta), m_gamma);
    }
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::cczcpaczcp()
{
    m_z = m_alpha*(m_beta*pow(m_z, m_gamma) + m_delta*pow(m_z, m_epsilon));
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::onion_4_function()
{
    m_z = m_cf0((m_alpha*m_z)/m_cf1((m_beta*m_z)/m_cf2((m_gamma*m_z)/m_cf3(m_delta*m_z)))) + m_epsilon;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::combination3()
{
    m_z = pow((m_alpha*pow(m_z, m_beta) + m_gamma), m_delta) + pow((m_epsilon*pow(m_z, m_zeta) + m_eta), m_theta);
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::c2mfczac()
{
    m_z = m_alpha*m_cf0(m_beta*m_z + m_gamma)*m_cf1(m_delta*m_z + m_epsilon);
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::c2dfczac()
{
    m_z = (m_alpha*m_cf0(m_beta*m_z + m_gamma))/m_cf1(m_delta*m_z + m_epsilon);
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::single_3f_onion()
{
    m_z = m_alpha*(m_cf0(m_cf1(m_cf2(m_beta*m_z + m_gamma)))) + m_delta;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::double_3f_onion_m()
{
    m_z = m_alpha*m_cf0(m_cf1(m_cf2(m_beta*m_z + m_gamma)))*
                  m_cf3(m_cf4(m_cf5(m_delta*m_z + m_epsilon))) + m_zeta;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::double_3f_onion_d()
{
    m_z = (m_alpha*m_cf0(m_cf1(m_cf2(m_beta*m_z + m_gamma))))/
                   m_cf3(m_cf4(m_cf5(m_delta*m_z + m_epsilon))) + m_zeta;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::m3()
{
    m_z = m_z*m_z*m_z + m_alpha;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::m4()
{
    m_z2 = m_z*m_z;
    m_z = m_z2*m_z2 + m_alpha;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::m5()
{
    m_z2 = m_z*m_z;
    m_z = m_z2*m_z2*m_z + m_alpha;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::m6()
{
    m_z2 = m_z*m_z;
    m_z3 = m_z2*m_z;
    m_z = m_z3*m_z3 + m_alpha;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::m7()
{
    m_z2 = m_z*m_z;
    m_z3 = m_z2*m_z;
    m_z = m_z3*m_z3*m_z + m_alpha;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::m8()
{
    m_z2 = m_z*m_z;
    m_z4 = m_z2*m_z2;
    m_z = m_z4*m_z4 + m_alpha;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::m9()
{
    m_z2 = m_z*m_z;
    m_z4 = m_z2*m_z2;
    m_z = m_z4*m_z4*m_z + m_alpha;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::m10()
{
    m_z2 = m_z*m_z;
    m_z4 = m_z2*m_z2;
    m_z = m_z4*m_z4*m_z2 + m_alpha;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::attractors()
{
    m_x = real(m_z);
    m_y = imag(m_z);
    m_r = m_p0*m_f0(m_p1*m_y) + m_p2*m_f1(m_p3*m_x) + real(m_alpha);
    m_i = m_p4*m_f2(m_p5*m_x) + m_p6*m_f3(m_p7*m_y) + imag(m_alpha);
    m_z = T2(m_r, m_i);
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::general_mixture()
{
    m_z = pow(m_alpha*(m_beta*pow(m_z, m_gamma) + m_delta*pow(m_z, m_epsilon)) + m_zeta, m_eta);
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::mixture()
{
    m_z = m_alpha*(m_z + m_z - m_z*m_z) + m_beta;
    m_z = m_z*m_z;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::mixture2()
{
    m_z = m_alpha*(m_z - m_z*m_z) + m_beta;
    m_z = m_z*m_z*m_z;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::mixture3()
{
    m_z = m_alpha*(m_z - m_z*m_z) + m_beta;
    m_z2 = m_z*m_z;
    m_z = m_z2*m_z2;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::mixture4()
{
    m_z2 = m_z*m_z;
    m_z = m_alpha*(m_z2*m_z - m_z2*m_z2) + m_beta;
    m_z2 = m_z*m_z;
    m_z = m_z2*m_z2*m_z;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::pr_mandelbrot_2()
{
    m_z2 = m_z*m_z;
    m_a = m_z2 + m_alpha + m_gamma;
    m_b = m_z2 + m_beta + m_delta;
    m_z = m_a*m_b/(m_a + m_b);
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::pr_mandelbrot_3()
{
    m_z2 = m_z*m_z;
    m_a = m_z2 + m_alpha + m_delta;
    m_b = m_z2 + m_beta + m_epsilon;
    m_d = m_z2 + m_gamma + m_zeta;
    m_z = m_a*m_b*m_d/((m_a + m_b)*m_d + m_a*m_b);
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::pr_single_function_2()
{
    m_a = m_cf0(m_alpha*m_z) + m_beta;
    m_b = m_cf1(m_gamma*m_z) + m_delta;
    m_z = m_one/(m_a + m_epsilon) + m_one/(m_b + m_zeta);
    m_z = m_one/m_z;
}

template<>
inline void CalculatingUnit<long double, LongComplex>::hop()
{
    m_x = real(m_z);
    m_y = imag(m_z);
    m_r = m_y + m_p1*signum(m_x)*m_f0(std::abs(m_p2*std::pow(m_x, m_p3) + m_p4));
    m_i = m_p0 - m_x;
    m_z = LongComplex(m_r, m_i) + m_alpha;
}

template<>
inline void CalculatingUnit<MpReal, MpComplex>::hop()
{
    m_x = real(m_z);
    m_y = imag(m_z);
    m_r = m_y + m_p1*signum(m_x)*m_f0(mpfr::abs(m_p2*mpfr::pow(m_x, m_p3) + m_p4));
    m_i = m_p0 - m_x;
    m_z = MpComplex(m_r, m_i) + m_alpha;
}

template<>
inline void CalculatingUnit<long double, LongComplex>::quadrup_2()
{
    m_x = real(m_z);
    m_y = imag(m_z);
    // Re-use vacant parameters as working variables
    m_p3 = std::log(std::abs(m_p1*m_x - m_p2));
    m_p4 = std::log(std::abs(m_p2*m_x - m_p1));
    m_r = m_y - signum(m_x)*std::sin(m_p3)*std::atan(m_p4*m_p4);
    m_i = m_p0 - m_x;
    m_z = LongComplex(m_r, m_i) + m_alpha;
}

template<>
inline void CalculatingUnit<MpReal, MpComplex>::quadrup_2()
{
    m_x = real(m_z);
    m_y = imag(m_z);
    // Re-use vacant parameters as working variables
    m_p3 = mpfr::log(mpfr::abs(m_p1*m_x - m_p2));
    m_p4 = mpfr::log(mpfr::abs(m_p2*m_x - m_p1));
    m_r = m_y - signum(m_x)*mpfr::sin(m_p3)*mpfr::atan(m_p4*m_p4);
    m_i = m_p0 - m_x;
    m_z = MpComplex(m_r, m_i) + m_alpha;
}

template<>
inline void CalculatingUnit<long double, LongComplex>::threeply()
{
    m_x = real(m_z);
    m_y = imag(m_z);
    // Re-use vacant parameters as working variables
    m_p3 = m_p0 + m_p1 + m_p2;
    m_r = m_y - signum(m_x)*std::abs(sin(m_x)*cos(m_p1) + m_p2 - m_x*sin(m_p3));
    m_i = m_p0 - m_x;
    m_z = LongComplex(m_r, m_i) + m_alpha;
}

template<>
inline void CalculatingUnit<MpReal, MpComplex>::threeply()
{
    m_x = real(m_z);
    m_y = imag(m_z);
    // Re-use vacant parameters as working variables
    m_p3 = m_p0 + m_p1 + m_p2;
    m_r = m_y - signum(m_x)*mpfr::abs(sin(m_x)*cos(m_p1) + m_p2 - m_x*sin(m_p3));
    m_i = m_p0 - m_x;
    m_z = MpComplex(m_r, m_i) + m_alpha;
}

template<>
inline void CalculatingUnit<long double, LongComplex>::threeply2()
{
    m_x = real(m_z);
    m_y = imag(m_z);
    // Re-use vacant parameters as working variables
    m_p3 = m_p0 + m_p1 + m_p2;
    m_r = m_y - signum(m_x)*std::abs(sin(m_x)*cos(m_p1) + m_p2 + m_x*sin(m_p3));
    m_i = m_p0 - m_x;
    m_z = LongComplex(m_r, m_i) + m_alpha;
}

template<>
inline void CalculatingUnit<MpReal, MpComplex>::threeply2()
{
    m_x = real(m_z);
    m_y = imag(m_z);
    // Re-use vacant parameters as working variables
    m_p3 = m_p0 + m_p1 + m_p2;
    m_r = m_y - signum(m_x)*mpfr::abs(sin(m_x)*cos(m_p1) + m_p2 + m_x*sin(m_p3));
    m_i = m_p0 - m_x;
    m_z = MpComplex(m_r, m_i) + m_alpha;
}

template<>
inline void CalculatingUnit<long double, LongComplex>::chip()
{
    m_x = real(m_z);
    m_y = imag(m_z);
    // Re-use vacant parameters as working variables
    m_p3 = std::log(std::abs(m_p1*m_x - m_p2));
    m_p4 = std::log(std::abs(m_p2*m_x - m_p1));
    m_r = m_y - signum(m_x)*std::cos(m_p3*m_p3)*std::atan(m_p4*m_p4);
    m_i = m_p0 - m_x;
    m_z = LongComplex(m_r, m_i) + m_alpha;
}

template<>
inline void CalculatingUnit<MpReal, MpComplex>::chip()
{
    m_x = real(m_z);
    m_y = imag(m_z);
    // Re-use vacant parameters as working variables
    m_p3 = mpfr::log(mpfr::abs(m_p1*m_x - m_p2));
    m_p4 = mpfr::log(mpfr::abs(m_p2*m_x - m_p1));
    m_r = m_y - signum(m_x)*mpfr::cos(m_p3*m_p3)*mpfr::atan(m_p4*m_p4);
    m_i = m_p0 - m_x;
    m_z = MpComplex(m_r, m_i) + m_alpha;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::gumowski_mira()
{
    m_x = real(m_z);
    m_y = imag(m_z);
    // Re-use vacant parameters as working variables
    m_p3 = m_x*m_x;
    m_p4 = m_one - m_p0;
    m_p5 = m_p0*m_x + (m_two*m_p4*m_p3)/(m_one + m_p3);
    m_r = m_p1*m_y + m_p5;
    m_i = m_p2*m_x;
    m_x = m_r;
    m_p3 = m_x*m_x;
    m_p5 = m_p0*m_x + (m_two*m_p4*m_p3)/(m_one + m_p3);
    m_i += m_p5;
    m_z = T2(m_r, m_i) + m_alpha;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::mandelbrot_division()
{
    m_z = (pow(m_z, m_alpha) + m_beta)/(pow(m_z, m_gamma) + m_delta) + m_epsilon + m_zeta;
}

//==============================================================================
// Bailouts - all except no_bailout are specialised
//==============================================================================

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::bailout()
{
    if (m_convergent)
    {
        return convergent_bailout();
    }
    else
    {
        return divergent_bailout();
    }
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::convergent_bailout()
{
    switch (StaticCalculatingUnit::s_bailout_type)
    {
    case B_NONE:
        return false;
    case B_ABS:
        return lt_abs();
    default:
    case B_NORM:
        return lt_norm();
    case B_IMAG:
        return lt_imag();
    case B_IMAG_SQUARED:
        return lt_imag2();
    case B_REAL:
        return lt_real();
    case B_REAL_SQUARED:
        return lt_real2();
    case B_MANHATTAN:
        return lt_manhattan();
    case B_MANHATTANISH:
        return lt_manhattanish();
    case B_ABS_MANHATTANISH:
        return lt_abs_manhattanish();
    case B_MAX_SQUARED:
        return lt_max2();
    case B_MIN_SQUARED:
        return lt_min2();
    case B_ABS_PRODUCT:
        return lt_absproduct();
    case B_ABS_DIFF:
        return lt_absdiff();
    }
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::divergent_bailout()
{
    switch (StaticCalculatingUnit::s_bailout_type)
    {
    case B_NONE:
        return false;
    case B_ABS:
        return gt_abs();
    default:
    case B_NORM:
        return gt_norm();
    case B_IMAG:
        return gt_imag();
    case B_IMAG_SQUARED:
        return gt_imag2();
    case B_REAL:
        return gt_real();
    case B_REAL_SQUARED:
        return gt_real2();
    case B_MANHATTAN:
        return gt_manhattan();
    case B_MANHATTANISH:
        return gt_manhattanish();
    case B_ABS_MANHATTANISH:
        return gt_abs_manhattanish();
    case B_MAX_SQUARED:
        return gt_max2();
    case B_MIN_SQUARED:
        return gt_min2();
    case B_ABS_PRODUCT:
        return gt_absproduct();
    case B_ABS_DIFF:
        return gt_absdiff();
    }
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::gt_abs()
{
    if (std::abs(m_z_r) == m_ld_inf)
    {
        return true;
    }
    else if (m_z_r != m_z_r)
    {
        return true;
    }
    else if (std::abs(m_z_i) == m_ld_inf)
    {
        return true;
    }
    else if (m_z_i != m_z_i)
    {
        return true;
    }
    return (std::sqrt(m_z_r*m_z_r + m_z_i*m_z_i) > m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::gt_norm()
{
    if (std::abs(m_z_r) == m_ld_inf)
    {
        return true;
    }
    else if (m_z_r != m_z_r)
    {
        return true;
    }
    else if (std::abs(m_z_i) == m_ld_inf)
    {
        return true;
    }
    else if (m_z_i != m_z_i)
    {
        return true;
    }
    return ((m_z_r*m_z_r + m_z_i*m_z_i) > m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::gt_imag()
{
    return (m_z_i == m_ld_inf) || (m_z_i != m_z_i) || (m_z_i > m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::gt_imag2()
{
    return (m_z_i == m_ld_inf) || (m_z_i != m_z_i) || (m_z_i*m_z_i > m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::gt_real()
{
    return (m_z_r == m_ld_inf) || (m_z_r != m_z_r) || (m_z_r > m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::gt_real2()
{
    return (m_z_r == m_ld_inf) || (m_z_r != m_z_r) || (m_z_r*m_z_r > m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::gt_manhattanish()
{
    if (std::abs(m_z_r) == m_ld_inf)
    {
        return true;
    }
    else if (m_z_r != m_z_r)
    {
        return true;
    }
    else if (std::abs(m_z_i) == m_ld_inf)
    {
        return true;
    }
    else if (m_z_i != m_z_i)
    {
        return true;
    }
    return ((m_z_r + m_z_i) > m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::gt_max2()
{
    if (std::abs(m_z_r) == m_ld_inf)
    {
        return true;
    }
    else if (m_z_r != m_z_r)
    {
        return true;
    }
    else if (std::abs(m_z_i) == m_ld_inf)
    {
        return true;
    }
    else if (m_z_i != m_z_i)
    {
        return true;
    }
    long double r2 = m_z_r*m_z_r;
    long double i2 = m_z_i*m_z_i;
    return ((r2 > i2 ? r2 : i2) > m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::gt_min2()
{
    if (std::abs(m_z_r) == m_ld_inf)
    {
        return true;
    }
    else if (m_z_r != m_z_r)
    {
        return true;
    }
    else if (std::abs(m_z_i) == m_ld_inf)
    {
        return true;
    }
    else if (m_z_i != m_z_i)
    {
        return true;
    }
    long double r2 = m_z_r*m_z_r;
    long double i2 = m_z_i*m_z_i;
    return ((r2 < i2 ? r2 : i2) > m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::gt_manhattan()
{
    if (std::abs(m_z_r) == m_ld_inf)
    {
        return true;
    }
    else if (m_z_r != m_z_r)
    {
        return true;
    }
    else if (std::abs(m_z_i) == m_ld_inf)
    {
        return true;
    }
    else if (m_z_i != m_z_i)
    {
        return true;
    }
    return ((std::abs(m_z_r) + std::abs(m_z_i)) > m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::gt_abs_manhattanish()
{
    if (std::abs(m_z_r) == m_ld_inf)
    {
        return true;
    }
    else if (m_z_r != m_z_r)
    {
        return true;
    }
    else if (std::abs(m_z_i) == m_ld_inf)
    {
        return true;
    }
    else if (m_z_i != m_z_i)
    {
        return true;
    }
    return (std::abs(m_z_r + m_z_i) > m_limit );
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::gt_absproduct()
{
    if (std::abs(m_z_r) == m_ld_inf)
    {
        return true;
    }
    else if (m_z_r != m_z_r)
    {
        return true;
    }
    else if (std::abs(m_z_i) == m_ld_inf)
    {
        return true;
    }
    else if (m_z_i != m_z_i)
    {
        return true;
    }
    return (std::abs(m_z_r*m_z_i) > m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::gt_absdiff()
{
    if (std::abs(m_z_r) == m_ld_inf)
    {
        return true;
    }
    else if (m_z_r != m_z_r)
    {
        return true;
    }
    else if (std::abs(m_z_i) == m_ld_inf)
    {
        return true;
    }
    else if (m_z_i != m_z_i)
    {
        return true;
    }
    return (std::abs(m_z_r - m_z_i) > m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::lt_abs()
{
    long double d_r = m_z_r - m_old_z_r;
    long double d_i = m_z_i - m_old_z_i;
    return (sqrt(d_r*d_r + d_i*d_i) < m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::lt_norm()
{
    long double d_r = m_z_r - m_old_z_r;
    long double d_i = m_z_i - m_old_z_i;
    return ((d_r*d_r + d_i*d_i) < m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::lt_imag()
{
    return (std::abs(m_z_i - m_old_z_i) < m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::lt_imag2()
{
    return (std::abs(m_z_i*m_z_i - m_old_z_i*m_old_z_i) < m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::lt_real()
{
    return (std::abs(m_z_r - m_old_z_r) < m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::lt_real2()
{
    return (std::abs(m_z_r*m_z_r - m_old_z_r*m_old_z_r) < m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::lt_manhattan()
{
    long double m = std::abs(m_z_r) + std::abs(m_z_i);
    long double last_m = std::abs(m_old_z_r) + std::abs(m_old_z_i);
    return (std::abs(m - last_m) < m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::lt_manhattanish()
{
    long double m = m_z_r + m_z_i;
    long double last_m = m_old_z_r + m_old_z_i;
    return (std::abs(m - last_m) < m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::lt_abs_manhattanish()
{
    long double m = std::abs(m_z_r + m_z_i);
    long double last_m = std::abs(m_old_z_r + m_old_z_i);
    return (std::abs(m - last_m) < m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::lt_max2()
{
    long double r2 = std::abs(m_z_r*m_z_r - m_old_z_r*m_old_z_r);
    long double i2 = std::abs(m_z_i*m_z_i - m_old_z_i*m_old_z_i);
    return ((r2 > i2 ? r2 : i2) < m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::lt_min2()
{
    long double r2 = std::abs(m_z_r*m_z_r - m_old_z_r*m_old_z_r);
    long double i2 = std::abs(m_z_i*m_z_i - m_old_z_i*m_old_z_i);
    return ((r2 < i2 ? r2 : i2) < m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::lt_absdiff()
{
    long double absdiff = std::abs(m_z_r - m_z_i);
    long double last_absdiff = std::abs(m_old_z_r - m_old_z_i);
    return (std::abs(absdiff - last_absdiff) > m_limit);
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::lt_absproduct()
{
    long double r_diff = m_z_r - m_old_z_r;
    long double i_diff = m_z_i - m_old_z_i;
    return (std::abs(r_diff*i_diff) < m_limit);
}

template<class T1, class T2>
T2 CalculatingUnit<T1, T2>::transform(const T2& z)
{
    m_sequence_index = (StaticCalculatingUnit::s_sequence_length > 1
                        ? static_cast<int>(m_iteration) % StaticCalculatingUnit::s_sequence_length
                        : 0);
    return m_transform[StaticCalculatingUnit::getTransformSet(m_sequence_index)](z);
}

template<class T1, class T2>
void CalculatingUnit<T1, T2>::set_transforms()
{
    m_has_transforms = false;
    int number_of_sets = StaticCalculatingUnit::s_config.getNumberOfTransformSets();
    m_transform.resize(number_of_sets);
    // Note although there maybe transform sets defined if they are
    // all empty then no there are no transforms to apply.
    bool has_transforms = StaticCalculatingUnit::s_config.transformsDefined();
    if (has_transforms && (number_of_sets > 0) && (StaticCalculatingUnit::s_sequence_length > 0))
    {
        for (int i = 0; i < number_of_sets; i++)
        {
            m_transform[i].setTransforms(i, StaticCalculatingUnit::s_config);
        }
        m_has_transforms = true;
    }
}


//==============================================================================
// calculateN routines are essentially the same, the code is duplicated with
// the variations in the number of results sets collected purely for performance
// reasons.
//==============================================================================


template<>
inline void CalculatingUnit<long double, LongComplex>::calculate0r()
{
    int row = StaticCalculatingUnit::nextRow();
    int width = StaticCalculatingUnit::s_width;
    int height = StaticCalculatingUnit::s_height;
    while (row < height)
    {
        m_rs = &(StaticCalculatingUnit::s_results[row*width]);
        for (int col = 0; (col < width) && !StaticCalculatingUnit::s_stop; col++)
        {
            m_z = LongComplex(m_rs->z_r, m_rs->z_i);
            m_c = LongComplex(m_rs->c_r, m_rs->c_i);
            m_z_r = real(m_z);
            m_z_i = imag(m_z);
            updateParameters();
            if (!m_rs->done)
            {
                m_iteration = m_rs->escape;
                while ((m_iteration < m_max_iteration) && !StaticCalculatingUnit::s_stop)
                {
                    formula();
                    m_z_r = real(m_z);
                    m_z_i = imag(m_z);
                    m_iteration++;
                    if (bailout())
                    {
                        m_rs->done = true;
                        break;
                    }
                }
                m_finished = m_finished && m_rs->done;
                m_rs->escape = m_iteration;
                m_rs->z_r = m_z_r;
                m_rs->z_i = m_z_i;
                StaticCalculatingUnit::updateImage(m_rs, col, row);
            }
            m_rs++;
        }
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<long double, LongComplex>::calculate0tr()
{
    int row = StaticCalculatingUnit::nextRow();
    int width = StaticCalculatingUnit::s_width;
    int height = StaticCalculatingUnit::s_height;
    while (row < height)
    {
        m_rs = &(StaticCalculatingUnit::s_results[row*width]);
        for (int col = 0; (col < width) && !StaticCalculatingUnit::s_stop; col++)
        {
            m_z = LongComplex(m_rs->z_r, m_rs->z_i);
            m_c = LongComplex(m_rs->c_r, m_rs->c_i);
            m_z_r = real(m_z);
            m_z_i = imag(m_z);
            updateParameters();
            if (!m_rs->done)
            {
                m_iteration = m_rs->escape;
                while ((m_iteration < m_max_iteration) && !StaticCalculatingUnit::s_stop)
                {
                    m_z = transform(m_z);
                    formula();
                    m_z_r = real(m_z);
                    m_z_i = imag(m_z);
                    m_iteration++;
                    if (bailout())
                    {
                        m_rs->done = true;
                        break;
                    }
                }
                m_finished = m_finished && m_rs->done;
                m_rs->escape = m_iteration;
                m_rs->z_r = m_z_r;
                m_rs->z_i = m_z_i;
                StaticCalculatingUnit::updateImage(m_rs, col, row);
            }
            m_rs++;
        }
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<long double, LongComplex>::calculate1r()
{
    int row = StaticCalculatingUnit::nextRow();
    while (row < StaticCalculatingUnit::s_height)
    {
        m_rs = &(StaticCalculatingUnit::s_results[row*StaticCalculatingUnit::s_width]);
        for (int col = 0; (col < StaticCalculatingUnit::s_width) && !StaticCalculatingUnit::s_stop; col++)
        {
            m_z = LongComplex(m_rs->z_r, m_rs->z_i);
            m_c = LongComplex(m_rs->c_r, m_rs->c_i);
            m_z_r = real(m_z);
            m_z_i = imag(m_z);
            updateParameters();
            if (!m_rs->done)
            {
                m_iteration = m_rs->escape;
                while ((m_iteration < m_max_iteration) && !StaticCalculatingUnit::s_stop)
                {
                    formula();
                    m_z_r = real(m_z);
                    m_z_i = imag(m_z);
                    m_iteration++;
                    collectResults1();
                    if (bailout())
                    {
                        m_rs->done = true;
                        break;
                    }
                }
                m_finished = m_finished && m_rs->done;
                m_rs->escape = m_iteration;
                m_rs->z_r = m_z_r;
                m_rs->z_i = m_z_i;
                StaticCalculatingUnit::updateImage(m_rs, col, row);
            }
            m_rs++;
        }
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<long double, LongComplex>::calculate1tr()
{
    int row = StaticCalculatingUnit::nextRow();
    while (row < StaticCalculatingUnit::s_height)
    {
        m_rs = &(StaticCalculatingUnit::s_results[row*StaticCalculatingUnit::s_width]);
        for (int col = 0; (col < StaticCalculatingUnit::s_width) && !StaticCalculatingUnit::s_stop; col++)
        {
            m_z = LongComplex(m_rs->z_r, m_rs->z_i);
            m_c = LongComplex(m_rs->c_r, m_rs->c_i);
            m_z_r = real(m_z);
            m_z_i = imag(m_z);
            updateParameters();
            if (!m_rs->done)
            {
                m_iteration = m_rs->escape;
                while ((m_iteration < m_max_iteration) && !StaticCalculatingUnit::s_stop)
                {
                    m_z = transform(m_z);
                    formula();
                    m_z_r = real(m_z);
                    m_z_i = imag(m_z);
                    m_iteration++;
                    collectResults1();
                    if (bailout())
                    {
                        m_rs->done = true;
                        break;
                    }
                }
                m_finished = m_finished && m_rs->done;
                m_rs->escape = m_iteration;
                m_rs->z_r = m_z_r;
                m_rs->z_i = m_z_i;
                StaticCalculatingUnit::updateImage(m_rs, col, row);
            }
            m_rs++;
        }
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<long double, LongComplex>::calculate2r()
{
    int row = StaticCalculatingUnit::nextRow();
    while (row < StaticCalculatingUnit::s_height)
    {
        m_rs = &(StaticCalculatingUnit::s_results[row*StaticCalculatingUnit::s_width]);
        for (int col = 0; (col < StaticCalculatingUnit::s_width) && !StaticCalculatingUnit::s_stop; col++)
        {
            m_z = LongComplex(m_rs->z_r, m_rs->z_i);
            m_c = LongComplex(m_rs->c_r, m_rs->c_i);
            m_z_r = real(m_z);
            m_z_i = imag(m_z);
            updateParameters();
            if (!m_rs->done)
            {
                m_iteration = m_rs->escape;
                while ((m_iteration < m_max_iteration) && !StaticCalculatingUnit::s_stop)
                {
                    formula();
                    m_z_r = real(m_z);
                    m_z_i = imag(m_z);
                    m_iteration++;
                    collectResults1();
                    collectResults2();
                    if (bailout())
                    {
                        m_rs->done = true;
                        break;
                    }
                }
                m_finished = m_finished && m_rs->done;
                m_rs->escape = m_iteration;
                m_rs->z_r = m_z_r;
                m_rs->z_i = m_z_i;
                StaticCalculatingUnit::updateImage(m_rs, col, row);
            }
            m_rs++;
        }
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<long double, LongComplex>::calculate2tr()
{
    int row = StaticCalculatingUnit::nextRow();
    while (row < StaticCalculatingUnit::s_height)
    {
        m_rs = &(StaticCalculatingUnit::s_results[row*StaticCalculatingUnit::s_width]);
        for (int col = 0; (col < StaticCalculatingUnit::s_width) && !StaticCalculatingUnit::s_stop; col++)
        {
            m_z = LongComplex(m_rs->z_r, m_rs->z_i);
            m_c = LongComplex(m_rs->c_r, m_rs->c_i);
            m_z_r = real(m_z);
            m_z_i = imag(m_z);
            updateParameters();
            if (!m_rs->done)
            {
                m_iteration = m_rs->escape;
                while ((m_iteration < m_max_iteration) && !StaticCalculatingUnit::s_stop)
                {
                    m_z = transform(m_z);
                    formula();
                    m_z_r = real(m_z);
                    m_z_i = imag(m_z);
                    m_iteration++;
                    collectResults1();
                    collectResults2();
                    if (bailout())
                    {
                        m_rs->done = true;
                        break;
                    }
                }
                m_finished = m_finished && m_rs->done;
                m_rs->escape = m_iteration;
                m_rs->z_r = m_z_r;
                m_rs->z_i = m_z_i;
                StaticCalculatingUnit::updateImage(m_rs, col, row);
            }
            m_rs++;
        }
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<MpReal, MpComplex>::calculate0r()
{
    int row = StaticCalculatingUnit::nextRow();
    int width = StaticCalculatingUnit::s_width;
    int precision = StaticCalculatingUnit::s_precision;
    MpReal pitch = StaticCalculatingUnit::s_pitch;
    while (row < StaticCalculatingUnit::s_height)
    {
        MpReal r(row, precision);
        m_c_r = StaticCalculatingUnit::s_topleft_r;
        m_c_i = StaticCalculatingUnit::s_topleft_i - r*pitch;
        m_rs = &(StaticCalculatingUnit::s_results[row*width]);
        for (int col = 0; (col < width) && !StaticCalculatingUnit::s_stop; col++)
        {
            m_c = MpComplex(m_c_r, m_c_i);
            StaticCalculatingUnit::setZandC(m_z, m_c);
            m_z_r = real(m_z).toLDouble();
            m_z_i = imag(m_z).toLDouble();
            updateParameters();
            m_iteration = m_rs->escape;
            while ((m_iteration < m_max_iteration) && !StaticCalculatingUnit::s_stop)
            {
                formula();
                m_z_r = real(m_z).toLDouble();
                m_z_i = imag(m_z).toLDouble();
                m_iteration++;
                if (bailout())
                {
                    m_rs->done = true;
                    break;
                }
            }
            m_finished = m_finished && m_rs->done;
            m_rs->escape = m_iteration;
            m_rs->z_r = m_z_r;
            m_rs->z_i = m_z_i; 
            StaticCalculatingUnit::updateImage(m_rs, col, row);
            m_rs++;
            m_c_r += pitch;
        }
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<MpReal, MpComplex>::calculate0tr()
{
    int row = StaticCalculatingUnit::nextRow();
    int width = StaticCalculatingUnit::s_width;
    int precision = StaticCalculatingUnit::s_precision;
    MpReal pitch = StaticCalculatingUnit::s_pitch;
    while (row < StaticCalculatingUnit::s_height)
    {
        MpReal r(row, precision);
        m_c_r = StaticCalculatingUnit::s_topleft_r;
        m_c_i = StaticCalculatingUnit::s_topleft_i - r*pitch;
        m_rs = &(StaticCalculatingUnit::s_results[row*width]);
        for (int col = 0; (col < width) && !StaticCalculatingUnit::s_stop; col++)
        {
            m_c = MpComplex(m_c_r, m_c_i);
            StaticCalculatingUnit::setZandC(m_z, m_c);
            m_z_r = real(m_z).toLDouble();
            m_z_i = imag(m_z).toLDouble();
            updateParameters();
            m_iteration = m_rs->escape;
            while ((m_iteration < m_max_iteration) && !StaticCalculatingUnit::s_stop)
            {
                m_z = transform(m_z);
                formula();
                m_z_r = real(m_z).toLDouble();
                m_z_i = imag(m_z).toLDouble();
                m_iteration++;
                if (bailout())
                {
                    m_rs->done = true;
                    break;
                }
            }
            m_finished = m_finished && m_rs->done;
            m_rs->escape = m_iteration;
            m_rs->z_r = m_z_r;
            m_rs->z_i = m_z_i; 
            StaticCalculatingUnit::updateImage(m_rs, col, row);
            m_rs++;
            m_c_r += pitch;
        }
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<MpReal, MpComplex>::calculate1r()
{
    int row = StaticCalculatingUnit::nextRow();
    while (row < StaticCalculatingUnit::s_height)
    {
        m_rs = &(StaticCalculatingUnit::s_results[row*StaticCalculatingUnit::s_width]);
        for (int col = 0; (col < StaticCalculatingUnit::s_width) && !StaticCalculatingUnit::s_stop; col++)
        {
            StaticCalculatingUnit::startingValues(col, row, m_z, m_c);
            m_z_r = real(m_z).toLDouble();
            m_z_i = imag(m_z).toLDouble();
            updateParameters();
            m_iteration = m_rs->escape;
            while ((m_iteration < m_max_iteration) && !StaticCalculatingUnit::s_stop)
            {
                formula();
                m_z_r = real(m_z).toLDouble();
                m_z_i = imag(m_z).toLDouble();
                m_iteration++;
                collectResults1();
                if (bailout())
                {
                    m_rs->done = true;
                    break;
                }
            }
            m_finished = m_finished && m_rs->done;
            m_rs->escape = m_iteration;
            m_rs->z_r = m_z_r;
            m_rs->z_i = m_z_i; 
            StaticCalculatingUnit::updateImage(m_rs, col, row);
            m_rs++;
        }
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<MpReal, MpComplex>::calculate1tr()
{
    int row = StaticCalculatingUnit::nextRow();
    while (row < StaticCalculatingUnit::s_height)
    {
        m_rs = &(StaticCalculatingUnit::s_results[row*StaticCalculatingUnit::s_width]);
        for (int col = 0; (col < StaticCalculatingUnit::s_width) && !StaticCalculatingUnit::s_stop; col++)
        {
            StaticCalculatingUnit::startingValues(col, row, m_z, m_c);
            m_z_r = real(m_z).toLDouble();
            m_z_i = imag(m_z).toLDouble();
            updateParameters();
            m_iteration = m_rs->escape;
            while ((m_iteration < m_max_iteration) && !StaticCalculatingUnit::s_stop)
            {
                m_z = transform(m_z);
                formula();
                m_z_r = real(m_z).toLDouble();
                m_z_i = imag(m_z).toLDouble();
                m_iteration++;
                collectResults1();
                if (bailout())
                {
                    m_rs->done = true;
                    break;
                }
            }
            m_finished = m_finished && m_rs->done;
            m_rs->escape = m_iteration;
            m_rs->z_r = m_z_r;
            m_rs->z_i = m_z_i; 
            StaticCalculatingUnit::updateImage(m_rs, col, row);
            m_rs++;
        }
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<MpReal, MpComplex>::calculate2r()
{
    int row = StaticCalculatingUnit::nextRow();
    while (row < StaticCalculatingUnit::s_height)
    {
        m_rs = &(StaticCalculatingUnit::s_results[row*StaticCalculatingUnit::s_width]);
        for (int col = 0; (col < StaticCalculatingUnit::s_width) && !StaticCalculatingUnit::s_stop; col++)
        {
            StaticCalculatingUnit::startingValues(col, row, m_z, m_c);
            m_z_r = real(m_z).toLDouble();
            m_z_i = imag(m_z).toLDouble();
            updateParameters();
            m_iteration = m_rs->escape;
            while ((m_iteration < m_max_iteration) && !StaticCalculatingUnit::s_stop)
            {
                formula();
                m_z_r = real(m_z).toLDouble();
                m_z_i = imag(m_z).toLDouble();
                m_iteration++;
                collectResults1();
                collectResults2();
                if (bailout())
                {
                    m_rs->done = true;
                    break;
                }
            }
            m_finished = m_finished && m_rs->done;
            m_rs->escape = m_iteration;
            m_rs->z_r = m_z_r;
            m_rs->z_i = m_z_i; 
            StaticCalculatingUnit::updateImage(m_rs, col, row);
            m_rs++;
        }
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<MpReal, MpComplex>::calculate2tr()
{
    int row = StaticCalculatingUnit::nextRow();
    while (row < StaticCalculatingUnit::s_height)
    {
        m_rs = &(StaticCalculatingUnit::s_results[row*StaticCalculatingUnit::s_width]);
        for (int col = 0; (col < StaticCalculatingUnit::s_width) && !StaticCalculatingUnit::s_stop; col++)
        {
            StaticCalculatingUnit::startingValues(col, row, m_z, m_c);
            m_z_r = real(m_z).toLDouble();
            m_z_i = imag(m_z).toLDouble();
            updateParameters();
            m_iteration = m_rs->escape;
            while ((m_iteration < m_max_iteration) && !StaticCalculatingUnit::s_stop)
            {
                m_z = transform(m_z);
                formula();
                m_z_r = real(m_z).toLDouble();
                m_z_i = imag(m_z).toLDouble();
                m_iteration++;
                collectResults1();
                collectResults2();
                if (bailout())
                {
                    m_rs->done = true;
                    break;
                }
            }
            m_finished = m_finished && m_rs->done;
            m_rs->escape = m_iteration;
            m_rs->z_r = m_z_r;
            m_rs->z_i = m_z_i; 
            StaticCalculatingUnit::updateImage(m_rs, col, row);
            m_rs++;
        }
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<long double, LongComplex>::calculate0()
{
    int row = StaticCalculatingUnit::nextRow();
    int width = StaticCalculatingUnit::s_width;
    long double pitch = StaticCalculatingUnit::s_pitch.toLDouble();
#ifdef BATCH
    ResultsSet rs;
    m_rs = &rs;
#endif
    int max_iteration = 0;
    while (row < StaticCalculatingUnit::s_height)
    {
#ifndef BATCH
        m_rs = &(StaticCalculatingUnit::s_results[row*width]);
#endif
        m_c_r = StaticCalculatingUnit::s_topleft_r.toLDouble();
        m_c_i = StaticCalculatingUnit::s_topleft_i.toLDouble() - static_cast<long double>(row)*pitch;
        for (int col = 0; (col < width) && !StaticCalculatingUnit::s_stop; col++)
        {
            m_c = LongComplex(m_c_r, m_c_i);
            StaticCalculatingUnit::setZandC(m_z, m_c);
            m_z_r = real(m_z);
            m_z_i = imag(m_z);
            StaticCalculatingUnit::initialiseResultsSet(*m_rs, m_z);
            updateParameters();
            m_iteration = 0;
            while (m_iteration < m_max_iteration)
            {
                formula();
                m_z_r = real(m_z);
                m_z_i = imag(m_z);
                m_iteration++;
                if (bailout())
                {
                    m_rs->done = true;
                    if (m_iteration > max_iteration)
                    {
                        max_iteration = m_iteration;
                    }
                    break;
                }
            }
            if (!m_rs->done)
            {
                max_iteration = m_max_iteration;
            }
            m_finished = m_finished && m_rs->done;
            m_rs->escape = m_iteration;
            m_rs->z_r = m_z_r;
            m_rs->z_i = m_z_i;
            StaticCalculatingUnit::updateImage(m_rs, col, row);
            m_c_r += pitch;
#ifndef BATCH
            m_rs++;
#endif
        }
        StaticCalculatingUnit::updateMaxIteration(max_iteration);
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<long double, LongComplex>::calculate0t()
{
    int row = StaticCalculatingUnit::nextRow();
    int width = StaticCalculatingUnit::s_width;
    long double pitch = StaticCalculatingUnit::s_pitch.toLDouble();
#ifdef BATCH
    ResultsSet rs;
    m_rs = &rs;
#endif
    int max_iteration = 0;
    while (row < StaticCalculatingUnit::s_height)
    {
#ifndef BATCH
        m_rs = &(StaticCalculatingUnit::s_results[row*width]);
#endif
        m_c_r = StaticCalculatingUnit::s_topleft_r.toLDouble();
        m_c_i = StaticCalculatingUnit::s_topleft_i.toLDouble() - static_cast<long double>(row)*pitch;
        for (int col = 0; (col < width) && !StaticCalculatingUnit::s_stop; col++)
        {
            m_c = LongComplex(m_c_r, m_c_i);
            StaticCalculatingUnit::setZandC(m_z, m_c);
            m_z_r = real(m_z);
            m_z_i = imag(m_z);
            StaticCalculatingUnit::initialiseResultsSet(*m_rs, m_z);
            updateParameters();
            m_iteration = 0;
            while (m_iteration < m_max_iteration)
            {
                m_z = transform(m_z);
                formula();
                m_z_r = real(m_z);
                m_z_i = imag(m_z);
                m_iteration++;
                if (bailout())
                {
                    m_rs->done = true;
                    if (m_iteration > max_iteration)
                    {
                        max_iteration = m_iteration;
                    }
                    break;
                }
            }
            if (!m_rs->done)
            {
                max_iteration = m_max_iteration;
            }
            m_finished = m_finished && m_rs->done;
            m_rs->escape = m_iteration;
            m_rs->z_r = m_z_r;
            m_rs->z_i = m_z_i;
            StaticCalculatingUnit::updateImage(m_rs, col, row);
            m_c_r += pitch;
#ifndef BATCH
            m_rs++;
#endif
        }
        StaticCalculatingUnit::updateMaxIteration(max_iteration);
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<long double, LongComplex>::calculate1()
{
    int row = StaticCalculatingUnit::nextRow();
    int width = StaticCalculatingUnit::s_width;
    long double pitch = StaticCalculatingUnit::s_pitch.toLDouble();
#ifdef BATCH
    ResultsSet rs;
    m_rs = &rs;
#endif
    int max_iteration = 0;
    while (row < StaticCalculatingUnit::s_height)
    {
#ifndef BATCH
        m_rs = &(StaticCalculatingUnit::s_results[row*width]);
#endif
        m_c_r = StaticCalculatingUnit::s_topleft_r.toLDouble();
        m_c_i = StaticCalculatingUnit::s_topleft_i.toLDouble() - static_cast<long double>(row)*pitch;
        for (int col = 0; (col < width) && !StaticCalculatingUnit::s_stop; col++)
        {
            m_c = LongComplex(m_c_r, m_c_i);
            StaticCalculatingUnit::setZandC(m_z, m_c);
            m_z_r = real(m_z);
            m_z_i = imag(m_z);
            StaticCalculatingUnit::initialiseResultsSet(*m_rs, m_z);
            updateParameters();
            m_iteration = m_rs->escape;
            while ((m_iteration < m_max_iteration) && !StaticCalculatingUnit::s_stop)
            {
                formula();
                m_z_r = real(m_z);
                m_z_i = imag(m_z);
                m_iteration++;
                collectResults1();
                if (bailout())
                {
                    m_rs->done = true;
                    if (m_iteration > max_iteration)
                    {
                        max_iteration = m_iteration;
                    }
                    break;
                }
            }
            if (!m_rs->done)
            {
                max_iteration = m_max_iteration;
            }
            m_finished = m_finished && m_rs->done;
            m_rs->escape = m_iteration;
            m_rs->z_r = m_z_r;
            m_rs->z_i = m_z_i; 
            StaticCalculatingUnit::updateImage(m_rs, col, row);
            m_c_r += pitch;
#ifndef BATCH
            m_rs++;
#endif
        }
        StaticCalculatingUnit::updateMaxIteration(max_iteration);
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<long double, LongComplex>::calculate1t()
{
    int row = StaticCalculatingUnit::nextRow();
    int width = StaticCalculatingUnit::s_width;
    long double pitch = StaticCalculatingUnit::s_pitch.toLDouble();
#ifdef BATCH
    ResultsSet rs;
    m_rs = &rs;
#endif
    int max_iteration = 0;
    while (row < StaticCalculatingUnit::s_height)
    {
#ifndef BATCH
        m_rs = &(StaticCalculatingUnit::s_results[row*width]);
#endif
        m_c_r = StaticCalculatingUnit::s_topleft_r.toLDouble();
        m_c_i = StaticCalculatingUnit::s_topleft_i.toLDouble() - static_cast<long double>(row)*pitch;
        for (int col = 0; (col < width) && !StaticCalculatingUnit::s_stop; col++)
        {
            m_c = LongComplex(m_c_r, m_c_i);
            StaticCalculatingUnit::setZandC(m_z, m_c);
            m_z_r = real(m_z);
            m_z_i = imag(m_z);
            StaticCalculatingUnit::initialiseResultsSet(*m_rs, m_z);
            updateParameters();
            m_iteration = m_rs->escape;
            while ((m_iteration < m_max_iteration) && !StaticCalculatingUnit::s_stop)
            {
                m_z = transform(m_z);
                formula();
                m_z_r = real(m_z);
                m_z_i = imag(m_z);
                m_iteration++;
                collectResults1();
                if (bailout())
                {
                    m_rs->done = true;
                    if (m_iteration > max_iteration)
                    {
                        max_iteration = m_iteration;
                    }
                    break;
                }
            }
            if (!m_rs->done)
            {
                max_iteration = m_max_iteration;
            }
            m_finished = m_finished && m_rs->done;
            m_rs->escape = m_iteration;
            m_rs->z_r = m_z_r;
            m_rs->z_i = m_z_i; 
            StaticCalculatingUnit::updateImage(m_rs, col, row);
            m_c_r += pitch;
#ifndef BATCH
            m_rs++;
#endif
        }
        StaticCalculatingUnit::updateMaxIteration(max_iteration);
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<long double, LongComplex>::calculate2()
{
    int row = StaticCalculatingUnit::nextRow();
    int width = StaticCalculatingUnit::s_width;
    long double pitch = StaticCalculatingUnit::s_pitch.toLDouble();
#ifdef BATCH
    ResultsSet rs;
    m_rs = &rs;
#endif
    int max_iteration = 0;
    while (row < StaticCalculatingUnit::s_height)
    {
#ifndef BATCH
        m_rs = &(StaticCalculatingUnit::s_results[row*width]);
#endif
        m_c_r = StaticCalculatingUnit::s_topleft_r.toLDouble();
        m_c_i = StaticCalculatingUnit::s_topleft_i.toLDouble() - static_cast<long double>(row)*pitch;
        for (int col = 0; (col < width) && !StaticCalculatingUnit::s_stop; col++)
        {
            m_c = LongComplex(m_c_r, m_c_i);
            StaticCalculatingUnit::setZandC(m_z, m_c);
            m_z_r = real(m_z);
            m_z_i = imag(m_z);
            StaticCalculatingUnit::initialiseResultsSet(*m_rs, m_z);
            updateParameters();
            m_iteration = m_rs->escape;
            while ((m_iteration < m_max_iteration) && !StaticCalculatingUnit::s_stop)
            {
                formula();
                m_z_r = real(m_z);
                m_z_i = imag(m_z);
                m_iteration++;
                collectResults1();
                collectResults2();
                if (bailout())
                {
                    m_rs->done = true;
                    if (m_iteration > max_iteration)
                    {
                        max_iteration = m_iteration;
                    }
                    break;
                }
            }
            if (!m_rs->done)
            {
                max_iteration = m_max_iteration;
            }
            m_finished = m_finished && m_rs->done;
            m_rs->escape = m_iteration;
            m_rs->z_r = m_z_r;
            m_rs->z_i = m_z_i; 
            StaticCalculatingUnit::updateImage(m_rs, col, row);
            m_c_r += pitch;
#ifndef BATCH
            m_rs++;
#endif
        }
        StaticCalculatingUnit::updateMaxIteration(max_iteration);
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<long double, LongComplex>::calculate2t()
{
    int row = StaticCalculatingUnit::nextRow();
    int width = StaticCalculatingUnit::s_width;
    long double pitch = StaticCalculatingUnit::s_pitch.toLDouble();
#ifdef BATCH
    ResultsSet rs;
    m_rs = &rs;
#endif
    int max_iteration = 0;
    while (row < StaticCalculatingUnit::s_height)
    {
#ifndef BATCH
        m_rs = &(StaticCalculatingUnit::s_results[row*width]);
#endif
        m_c_r = StaticCalculatingUnit::s_topleft_r.toLDouble();
        m_c_i = StaticCalculatingUnit::s_topleft_i.toLDouble() - static_cast<long double>(row)*pitch;
        for (int col = 0; (col < width) && !StaticCalculatingUnit::s_stop; col++)
        {
            m_c = LongComplex(m_c_r, m_c_i);
            StaticCalculatingUnit::setZandC(m_z, m_c);
            m_z_r = real(m_z);
            m_z_i = imag(m_z);
            StaticCalculatingUnit::initialiseResultsSet(*m_rs, m_z);
            updateParameters();
            m_iteration = m_rs->escape;
            while ((m_iteration < m_max_iteration) && !StaticCalculatingUnit::s_stop)
            {
                m_z = transform(m_z);
                formula();
                m_z_r = real(m_z);
                m_z_i = imag(m_z);
                m_iteration++;
                collectResults1();
                collectResults2();
                if (bailout())
                {
                    m_rs->done = true;
                    if (m_iteration > max_iteration)
                    {
                        max_iteration = m_iteration;
                    }
                    break;
                }
            }
            if (!m_rs->done)
            {
                max_iteration = m_max_iteration;
            }
            m_finished = m_finished && m_rs->done;
            m_rs->escape = m_iteration;
            m_rs->z_r = m_z_r;
            m_rs->z_i = m_z_i; 
            StaticCalculatingUnit::updateImage(m_rs, col, row);
            m_c_r += pitch;
#ifndef BATCH
            m_rs++;
#endif
        }
        StaticCalculatingUnit::updateMaxIteration(max_iteration);
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<MpReal, MpComplex>::calculate0()
{
    int row = StaticCalculatingUnit::nextRow();
    int width = StaticCalculatingUnit::s_width;
    int precision = StaticCalculatingUnit::s_precision;
    MpReal pitch = StaticCalculatingUnit::s_pitch;
#ifdef BATCH
    ResultsSet rs;
    m_rs = &rs;
#endif
    int max_iteration = 0;
    while (row < StaticCalculatingUnit::s_height)
    {
        MpReal r(row, precision);
#ifndef BATCH
        m_rs = &(StaticCalculatingUnit::s_results[row*width]);
#endif
        m_c_r = StaticCalculatingUnit::s_topleft_r;
        m_c_i = StaticCalculatingUnit::s_topleft_i - r*pitch;
        for (int col = 0; (col < width) && !StaticCalculatingUnit::s_stop; col++)
        {
            m_c = MpComplex(m_c_r, m_c_i);
            StaticCalculatingUnit::setZandC(m_z, m_c);
            m_z_r = real(m_z).toLDouble();
            m_z_i = imag(m_z).toLDouble();
            StaticCalculatingUnit::initialiseResultsSet(*m_rs, LongComplex(real(m_z).toLDouble(), imag(m_z).toLDouble()));
            updateParameters();
            m_iteration = m_rs->escape;
            while (m_iteration < m_max_iteration)
            {
                formula();
                m_z_r = real(m_z).toLDouble();
                m_z_i = imag(m_z).toLDouble();
                m_iteration++;
                if (bailout())
                {
                    m_rs->done = true;
                    if (m_iteration > max_iteration)
                    {
                        max_iteration = m_iteration;
                    }
                    break;
                }
            }
            if (!m_rs->done)
            {
                max_iteration = m_max_iteration;
            }
            m_finished = m_finished && m_rs->done;
            m_rs->escape = m_iteration;
            m_rs->z_r = m_z_r;
            m_rs->z_i = m_z_i; 
            StaticCalculatingUnit::updateImage(m_rs, col, row);
            m_c_r += pitch;
#ifndef BATCH
            m_rs++;
#endif
        }
        StaticCalculatingUnit::updateMaxIteration(max_iteration);
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<MpReal, MpComplex>::calculate0t()
{
    int row = StaticCalculatingUnit::nextRow();
    int width = StaticCalculatingUnit::s_width;
    int precision = StaticCalculatingUnit::s_precision;
    MpReal pitch = StaticCalculatingUnit::s_pitch;
#ifdef BATCH
    ResultsSet rs;
    m_rs = &rs;
#endif
    int max_iteration = 0;
    while (row < StaticCalculatingUnit::s_height)
    {
        MpReal r(row, precision);
#ifndef BATCH
        m_rs = &(StaticCalculatingUnit::s_results[row*width]);
#endif
        m_c_r = StaticCalculatingUnit::s_topleft_r;
        m_c_i = StaticCalculatingUnit::s_topleft_i - r*pitch;
        for (int col = 0; (col < width) && !StaticCalculatingUnit::s_stop; col++)
        {
            m_c = MpComplex(m_c_r, m_c_i);
            StaticCalculatingUnit::setZandC(m_z, m_c);
            m_z_r = real(m_z).toLDouble();
            m_z_i = imag(m_z).toLDouble();
            StaticCalculatingUnit::initialiseResultsSet(*m_rs, LongComplex(real(m_z).toLDouble(), imag(m_z).toLDouble()));
            updateParameters();
            m_iteration = m_rs->escape;
            while (m_iteration < m_max_iteration)
            {
                m_z = transform(m_z);
                formula();
                m_z_r = real(m_z).toLDouble();
                m_z_i = imag(m_z).toLDouble();
                m_iteration++;
                if (bailout())
                {
                    m_rs->done = true;
                    if (m_iteration > max_iteration)
                    {
                        max_iteration = m_iteration;
                    }
                    break;
                }
            }
            if (!m_rs->done)
            {
                max_iteration = m_max_iteration;
            }
            m_finished = m_finished && m_rs->done;
            m_rs->escape = m_iteration;
            m_rs->z_r = m_z_r;
            m_rs->z_i = m_z_i; 
            StaticCalculatingUnit::updateImage(m_rs, col, row);
            m_c_r += pitch;
#ifndef BATCH
            m_rs++;
#endif
        }
        StaticCalculatingUnit::updateMaxIteration(max_iteration);
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<MpReal, MpComplex>::calculate1()
{
    int row = StaticCalculatingUnit::nextRow();
    int width = StaticCalculatingUnit::s_width;
    MpReal pitch = StaticCalculatingUnit::s_pitch;
#ifdef BATCH
    ResultsSet rs;
    m_rs = &rs;
#endif
    int max_iteration = 0;
    while (row < StaticCalculatingUnit::s_height)
    {
#ifndef BATCH
        m_rs = &(StaticCalculatingUnit::s_results[row*width]);
#endif
        m_c_r = StaticCalculatingUnit::s_topleft_r;
        m_c_i = StaticCalculatingUnit::s_topleft_i - row*pitch;
        for (int col = 0; (col < width) && !StaticCalculatingUnit::s_stop; col++)
        {
            m_c = MpComplex(m_c_r, m_c_i);
            StaticCalculatingUnit::setZandC(m_z, m_c);
            m_z_r = real(m_z).toLDouble();
            m_z_i = imag(m_z).toLDouble();
            StaticCalculatingUnit::initialiseResultsSet(*m_rs, LongComplex(real(m_z).toLDouble(), imag(m_z).toLDouble()));
            updateParameters();
            m_iteration = m_rs->escape;
            while (m_iteration < m_max_iteration)
            {
                formula();
                m_z_r = real(m_z).toLDouble();
                m_z_i = imag(m_z).toLDouble();
                m_iteration++;
                collectResults1();
                if (bailout())
                {
                    m_rs->done = true;
                    if (m_iteration > max_iteration)
                    {
                        max_iteration = m_iteration;
                    }
                    break;
                }
            }
            if (!m_rs->done)
            {
                max_iteration = m_max_iteration;
            }
            m_finished = m_finished && m_rs->done;
            m_rs->escape = m_iteration;
            m_rs->z_r = m_z_r;
            m_rs->z_i = m_z_i; 
            StaticCalculatingUnit::updateImage(m_rs, col, row);
            m_c_r += pitch;
#ifndef BATCH
            m_rs++;
#endif
        }
        StaticCalculatingUnit::updateMaxIteration(max_iteration);
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<MpReal, MpComplex>::calculate1t()
{
    int row = StaticCalculatingUnit::nextRow();
    int width = StaticCalculatingUnit::s_width;
    MpReal pitch = StaticCalculatingUnit::s_pitch;
#ifdef BATCH
    ResultsSet rs;
    m_rs = &rs;
#endif
    int max_iteration = 0;
    while (row < StaticCalculatingUnit::s_height)
    {
#ifndef BATCH
        m_rs = &(StaticCalculatingUnit::s_results[row*width]);
#endif
        m_c_r = StaticCalculatingUnit::s_topleft_r;
        m_c_i = StaticCalculatingUnit::s_topleft_i - row*pitch;
        for (int col = 0; (col < width) && !StaticCalculatingUnit::s_stop; col++)
        {
            m_c = MpComplex(m_c_r, m_c_i);
            StaticCalculatingUnit::setZandC(m_z, m_c);
            m_z_r = real(m_z).toLDouble();
            m_z_i = imag(m_z).toLDouble();
            StaticCalculatingUnit::initialiseResultsSet(*m_rs, LongComplex(real(m_z).toLDouble(), imag(m_z).toLDouble()));
            updateParameters();
            m_iteration = m_rs->escape;
            while (m_iteration < m_max_iteration)
            {
                m_z = transform(m_z);
                formula();
                m_z_r = real(m_z).toLDouble();
                m_z_i = imag(m_z).toLDouble();
                m_iteration++;
                collectResults1();
                if (bailout())
                {
                    m_rs->done = true;
                    if (m_iteration > max_iteration)
                    {
                        max_iteration = m_iteration;
                    }
                    break;
                }
            }
            if (!m_rs->done)
            {
                max_iteration = m_max_iteration;
            }
            m_finished = m_finished && m_rs->done;
            m_rs->escape = m_iteration;
            m_rs->z_r = m_z_r;
            m_rs->z_i = m_z_i; 
            StaticCalculatingUnit::updateImage(m_rs, col, row);
            m_c_r += pitch;
#ifndef BATCH
            m_rs++;
#endif
        }
        StaticCalculatingUnit::updateMaxIteration(max_iteration);
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<MpReal, MpComplex>::calculate2()
{
    int row = StaticCalculatingUnit::nextRow();
    int width = StaticCalculatingUnit::s_width;
    MpReal pitch = StaticCalculatingUnit::s_pitch;
#ifdef BATCH
    ResultsSet rs;
    m_rs = &rs;
#endif
    int max_iteration = 0;
    while (row < StaticCalculatingUnit::s_height)
    {
#ifndef BATCH
        m_rs = &(StaticCalculatingUnit::s_results[row*width]);
#endif
        m_c_r = StaticCalculatingUnit::s_topleft_r;
        m_c_i = StaticCalculatingUnit::s_topleft_i - row*pitch;
        for (int col = 0; (col < width) && !StaticCalculatingUnit::s_stop; col++)
        {
            m_c = MpComplex(m_c_r, m_c_i);
            StaticCalculatingUnit::setZandC(m_z, m_c);
            m_z_r = real(m_z).toLDouble();
            m_z_i = imag(m_z).toLDouble();
            StaticCalculatingUnit::initialiseResultsSet(*m_rs, LongComplex(real(m_z).toLDouble(), imag(m_z).toLDouble()));
            updateParameters();
            m_iteration = m_rs->escape;
            while (m_iteration < m_max_iteration)
            {
                formula();
                m_z_r = real(m_z).toLDouble();
                m_z_i = imag(m_z).toLDouble();
                m_iteration++;
                collectResults1();
                if (bailout())
                {
                    m_rs->done = true;
                    if (m_iteration > max_iteration)
                    {
                        max_iteration = m_iteration;
                    }
                    break;
                }
            }
            if (!m_rs->done)
            {
                max_iteration = m_max_iteration;
            }
            m_finished = m_finished && m_rs->done;
            m_rs->escape = m_iteration;
            m_rs->z_r = m_z_r;
            m_rs->z_i = m_z_i; 
            StaticCalculatingUnit::updateImage(m_rs, col, row);
            m_c_r += pitch;
#ifndef BATCH
            m_rs++;
#endif
        }
        StaticCalculatingUnit::updateMaxIteration(max_iteration);
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<MpReal, MpComplex>::calculate2t()
{
    int row = StaticCalculatingUnit::nextRow();
    int width = StaticCalculatingUnit::s_width;
    MpReal pitch = StaticCalculatingUnit::s_pitch;
#ifdef BATCH
    ResultsSet rs;
    m_rs = &rs;
#endif
    int max_iteration = 0;
    while (row < StaticCalculatingUnit::s_height)
    {
#ifndef BATCH
        m_rs = &(StaticCalculatingUnit::s_results[row*width]);
#endif
        m_c_r = StaticCalculatingUnit::s_topleft_r;
        m_c_i = StaticCalculatingUnit::s_topleft_i - row*pitch;
        for (int col = 0; (col < width) && !StaticCalculatingUnit::s_stop; col++)
        {
            m_c = MpComplex(m_c_r, m_c_i);
            StaticCalculatingUnit::setZandC(m_z, m_c);
            m_z_r = real(m_z).toLDouble();
            m_z_i = imag(m_z).toLDouble();
            StaticCalculatingUnit::initialiseResultsSet(*m_rs, LongComplex(real(m_z).toLDouble(), imag(m_z).toLDouble()));
            updateParameters();
            m_iteration = m_rs->escape;
            while (m_iteration < m_max_iteration)
            {
                m_z = transform(m_z);
                formula();
                m_z_r = real(m_z).toLDouble();
                m_z_i = imag(m_z).toLDouble();
                m_iteration++;
                collectResults1();
                collectResults2();
                if (bailout())
                {
                    m_rs->done = true;
                    if (m_iteration > max_iteration)
                    {
                        max_iteration = m_iteration;
                    }
                    break;
                }
            }
            if (!m_rs->done)
            {
                max_iteration = m_max_iteration;
            }
            m_finished = m_finished && m_rs->done;
            m_rs->escape = m_iteration;
            m_rs->z_r = m_z_r;
            m_rs->z_i = m_z_i; 
            StaticCalculatingUnit::updateImage(m_rs, col, row);
            m_c_r += pitch;
#ifndef BATCH
            m_rs++;
#endif
        }
        StaticCalculatingUnit::updateMaxIteration(max_iteration);
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<class T1, class T2>
inline bool CalculatingUnit<T1, T2>::calculate()
{
    m_finished = true; // Assume finished cleared if calculation hasn't finished
    m_limit = StaticCalculatingUnit::s_limit;
    if (!inFormulaTransforms(StaticCalculatingUnit::s_type) && m_has_transforms)
    {
#ifndef BATCH
        if (StaticCalculatingUnit::s_retain_results)
        {
            switch (StaticCalculatingUnit::s_number_of_results_sets)
            {
            case 0: calculate0tr(); break;
            case 1: calculate1tr(); break;
            case 2: calculate2tr();
            default: break;
            }
        }
        else
        {
#endif
            switch (StaticCalculatingUnit::s_number_of_results_sets)
            {
            case 0: calculate0t(); break;
            case 1: calculate1t(); break;
            case 2: calculate2t();
            default: break;
            }
#ifndef BATCH
        }
#endif
    }
    else
    {
#ifndef BATCH
        if (StaticCalculatingUnit::s_retain_results)
        {
            switch (StaticCalculatingUnit::s_number_of_results_sets)
            {
            case 0: calculate0r(); break;
            case 1: calculate1r(); break;
            case 2: calculate2r();
            default: break;
            }
        }
        else
        {
#endif
            switch (StaticCalculatingUnit::s_number_of_results_sets)
            {
            case 0: calculate0(); break;
            case 1: calculate1(); break;
            case 2: calculate2();
            default: break;
            }
#ifndef BATCH
        }
#endif
    }
    return m_finished;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::collectResults1()
{
    switch (StaticCalculatingUnit::s_results_set[0])
    {
    case StaticCalculatingUnit::RS_ANGLE: angleResults1(); return;
    case StaticCalculatingUnit::RS_MAGNITUDE: magnitudeResults1(); return;
    case StaticCalculatingUnit::RS_GAUSSIAN: gaussianResults1(); return;
    case StaticCalculatingUnit::RS_ORBIT_TRAP: orbitTrapResults1(); return;
    default: return;
    }
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::angleResults1()
{
    if (m_z_r != m_z_r)
    {
        return;
    }
    if (m_z_i != m_z_i)
    {
        return;
    }
    long double angle = arg(LongComplex(m_z_r, m_z_i));
    angle = (angle < 0.0 ? angle + 2.0L*m_pi : angle);
    resultStatistics1(angle);
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::magnitudeResults1()
{
    if (m_z_r != m_z_r)
    {
        return;
    }
    if (m_z_i != m_z_i)
    {
        return;
    }
    resultStatistics1(magnitude(LongComplex(m_z_r, m_z_i), false));
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::gaussianResults1()
{
    if (m_z_r != m_z_r)
    {
        return;
    }
    if (m_z_i != m_z_i)
    {
        return;
    }
    using std::abs;
    Statistics &s = m_rs->set[0];
    LongComplex z(m_z_r, m_z_i);
    LongComplex distance;
    switch(StaticCalculatingUnit::s_gaussian_type[0])
    {
    case StaticCalculatingUnit::GI_CEIL:
        distance = gi_ceil(z);
        break;
    case StaticCalculatingUnit::GI_FLOOR:
        distance = gi_floor(z);
        break;
    case StaticCalculatingUnit::GI_ROUND:
        distance = gi_round(z);
        break;
    case StaticCalculatingUnit::GI_TRUNC:
        distance = gi_trunc(z);
        break;
    }
    long double normd = norm(distance);
    long double absd = sqrt(normd);
    s.square_total += normd;
    s.total += absd;
    if (normd < norm(s.min_dist))
    {
        s.min_dist = distance;
        s.iteration_at_min = m_iteration;
    }
    if (normd > norm(s.max_dist))
    {
        s.max_dist = distance;
        s.iteration_at_max = m_iteration;
    }
    long double angle = arg(distance) + m_pi;
    s.angle_total += angle;
    if (angle < s.minimum)
    {
        s.minimum = angle;
    }
    if (angle > s.maximum)
    {
        s.maximum = angle;
    }
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::orbitTrapResults1()
{
    if (m_z_r != m_z_r)
    {
        return;
    }
    if (m_z_i != m_z_i)
    {
        return;
    }
    resultStatistics1(StaticCalculatingUnit::s_trap[0]->distance(LongComplex(m_z_r, m_z_i)));
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::collectResults2()
{
    switch (StaticCalculatingUnit::s_results_set[1])
    {
    case StaticCalculatingUnit::RS_ANGLE: angleResults2(); return;
    case StaticCalculatingUnit::RS_MAGNITUDE: magnitudeResults2(); return;
    case StaticCalculatingUnit::RS_GAUSSIAN: gaussianResults2(); return;
    case StaticCalculatingUnit::RS_ORBIT_TRAP: orbitTrapResults2(); return;
    default: return;
    }
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::angleResults2()
{
    if (m_z_r != m_z_r)
    {
        return;
    }
    if (m_z_i != m_z_i)
    {
        return;
    }
    long double angle = arg(LongComplex(m_z_r, m_z_i));
    angle = (angle < 0.0 ? angle + 2.0L*m_pi : angle);
    resultStatistics2(angle);
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::magnitudeResults2()
{
    if (m_z_r != m_z_r)
    {
        return;
    }
    if (m_z_i != m_z_i)
    {
        return;
    }
    resultStatistics2(magnitude(LongComplex(m_z_r, m_z_i), true));
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::resultStatistics1(long double value)
{
    if (m_z_r != m_z_r)
    {
        return;
    }
    if (m_z_i != m_z_i)
    {
        return;
    }
    bool& change = StaticCalculatingUnit::s_change[0];
    Statistics &s = m_rs->set[0];
    long double value2 = (change ? std::abs(value - s.last) : value);
    long double normd = value2*value2;
    s.total += value2;
    s.square_total += normd;
    if (value2 < s.minimum)
    {
        s.minimum = value2;
        s.iteration_at_min = m_iteration;
    }
    if (value2 > s.maximum)
    {
        s.maximum = value2;
        s.iteration_at_max = m_iteration;
    }
    s.es_sum1 += (change ? std::abs(exp(-value) - exp(-s.last)) : exp(-value));
    long double exp_inverse_change = exp(-1.0L/(std::abs(value - s.last)));
    s.es_sum2 += (change ? std::abs(exp_inverse_change - s.es2_last) : exp_inverse_change);
    s.last = value;
    s.es2_last = exp_inverse_change;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::gaussianResults2()
{
    if (m_z_r != m_z_r)
    {
        return;
    }
    if (m_z_i != m_z_i)
    {
        return;
    }
    using std::abs;
    Statistics &s = m_rs->set[1];
    LongComplex z(m_z_r, m_z_i);
    LongComplex distance;
    switch(StaticCalculatingUnit::s_gaussian_type[1])
    {
    case StaticCalculatingUnit::GI_CEIL:
        distance = gi_ceil(z);
        break;
    case StaticCalculatingUnit::GI_FLOOR:
        distance = gi_floor(z);
        break;
    case StaticCalculatingUnit::GI_ROUND:
        distance = gi_round(z);
        break;
    case StaticCalculatingUnit::GI_TRUNC:
        distance = gi_trunc(z);
        break;
    }
    long double normd = norm(distance);
    long double absd = sqrt(normd);
    s.square_total += normd;
    s.total += absd;
    if (normd < norm(s.min_dist))
    {
        s.min_dist = distance;
        s.iteration_at_min = m_iteration;
    }
    if (normd > norm(s.max_dist))
    {
        s.max_dist = distance;
        s.iteration_at_max = m_iteration;
    }
    long double angle = arg(distance) + m_pi;
    s.angle_total += angle;
    if (angle < s.minimum)
    {
        s.minimum = angle;
    }
    if (angle > s.maximum)
    {
        s.maximum = angle;
    }
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::orbitTrapResults2()
{
    if (m_z_r != m_z_r)
    {
        return;
    }
    if (m_z_i != m_z_i)
    {
        return;
    }
    resultStatistics2(StaticCalculatingUnit::s_trap[1]->distance(LongComplex(m_z_r, m_z_i)));
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::resultStatistics2(long double value)
{
    if (m_z_r != m_z_r)
    {
        return;
    }
    if (m_z_i != m_z_i)
    {
        return;
    }
    bool& change = StaticCalculatingUnit::s_change[1];
    Statistics &s = m_rs->set[1];
    long double value2 = (change ? std::abs(value - s.last) : value);
    long double normd = value2*value2;
    s.total += value2;
    s.square_total += normd;
    if (value2 < s.minimum)
    {
        s.minimum = value2;
        s.iteration_at_min = m_iteration;
    }
    if (value2 > s.maximum)
    {
        s.maximum = value2;
        s.iteration_at_max = m_iteration;
    }
    s.es_sum1 += (change ? std::abs(exp(-value) - exp(-s.last)) : exp(-value));
    long double exp_inverse_change = exp(-1.0L/(std::abs(value - s.last)));
    s.es_sum2 += (change ? std::abs(exp_inverse_change - s.es2_last) : exp_inverse_change);
    s.last = value;
    s.es2_last = exp_inverse_change;
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::updateParameters()
{
    m_alpha = (m_alpha_type == PT_NUMBER ? m_alpha : (m_alpha_type == PT_IS_C ? m_c : -m_c));
    m_beta = (m_beta_type == PT_NUMBER ? m_beta : (m_beta_type == PT_IS_C ? m_c : -m_c));
    m_gamma = (m_gamma_type == PT_NUMBER ? m_gamma : (m_gamma_type == PT_IS_C ? m_c : -m_c));
    m_delta = (m_delta_type == PT_NUMBER ? m_delta : (m_delta_type == PT_IS_C ? m_c : -m_c));
    m_epsilon = (m_epsilon_type == PT_NUMBER ? m_epsilon : (m_epsilon_type == PT_IS_C ? m_c : -m_c));
    m_zeta = (m_zeta_type == PT_NUMBER ? m_zeta : (m_zeta_type == PT_IS_C ? m_c : -m_c));
    m_eta = (m_eta_type == PT_NUMBER ? m_eta : (m_eta_type == PT_IS_C ? m_c : -m_c));
    m_theta = (m_theta_type == PT_NUMBER ? m_theta : (m_theta_type == PT_IS_C ? m_c : -m_c));
    m_iota = (m_iota_type == PT_NUMBER ? m_iota : (m_iota_type == PT_IS_C ? m_c : -m_c));
}

template<class T1, class T2>
inline long double CalculatingUnit<T1, T2>::magnitude(const LongComplex& z, bool second)
{
    if (m_magnitude_type[second] == 'M')
    {
        return ld::abs(z);
    }
    else
    {
        return magnitude_option(z, m_quotient[second]) /
               magnitude_option(z, m_divisor[second]);
    }
}

template<class T1, class T2>
inline long double CalculatingUnit<T1, T2>::magnitude_option(const LongComplex& z, char option)
{
    switch (option)
    {
    case 'a': // smaller
        return (std::abs(real(z)) < std::abs(imag(z)) ? std::abs(real(z)) : std::abs(imag(z)));
    case 'b': // larger
        return (std::abs(real(z)) > std::abs(imag(z)) ? std::abs(real(z)) : std::abs(imag(z)));
    case 'c': // abs real
        return std::abs(real(z));
    case 'd': // abs imag
        return std::abs(imag(z));
    case 'e': // sum
        return std::abs(real(z) + imag(z));
    case 'f': // abs diff
        return std::abs(real(z) - imag(z));
    case 'g': // sum abs
        return std::abs(real(z)) + std::abs(imag(z));
    case 'h': // abs diff abs
        return std::abs(std::abs(real(z)) - std::abs(imag(z)));
    case 'i': // product
        return std::abs(real(z)*imag(z));
    default:  // abs
    case 'j':
        return ld::abs(z);
    case 'k': // norm
        return ld::norm(z);
    }
}

template<class T1, class T2>
inline LongComplex CalculatingUnit<T1, T2>::gi_round(const LongComplex& z)
{
    long double int_r, int_i;
    long double z_r = real(z);
    z_r += (z_r < 0.0L ? -0.5 : 0.5);
    long double z_i = imag(z);
    z_i += (z_i < 0.0L ? -0.5 : 0.5);
    std::modf(z_r, &int_r); // discard return value
    std::modf(z_i, &int_i); // discard return value
    LongComplex gi = LongComplex(int_r, int_i);
    return (z - gi);
}

template<class T1, class T2>
inline LongComplex CalculatingUnit<T1, T2>::gi_ceil(const LongComplex& z)
{
    LongComplex gi(ceil(real(z)), ceil(imag(z)));
    return (z - gi);
}

template<class T1, class T2>
inline LongComplex CalculatingUnit<T1, T2>::gi_floor(const LongComplex& z)
{
    LongComplex gi(floor(real(z)), floor(imag(z)));
    return (z - gi);
}

template<class T1, class T2>
inline LongComplex CalculatingUnit<T1, T2>::gi_trunc(const LongComplex& z)
{
    LongComplex gi;
    long double int_r, int_i;
    long double z_r = real(z);
    long double z_i = imag(z);
    std::modf(z_r, &int_r); // discard return value
    std::modf(z_i, &int_i); // discard return value
    gi = LongComplex(int_r, int_i);
    return (z - gi);
}

template<class T1, class T2>
void CalculatingUnit<T1, T2>::enableProgressSignals(bool value)
{
    boost::mutex::scoped_lock lock(m_progress_signal_mutex);
    m_progress_signals_enabled = value;
    m_send_progress = value;
}

template<class T1, class T2>
void CalculatingUnit<T1, T2>::sendProgressSignals(bool value)
{
    boost::mutex::scoped_lock lock(m_progress_signal_mutex);
    if (m_progress_signals_enabled)
    {
        m_send_progress = value;
    }
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::calculateOrbits()
{
    if (!inFormulaTransforms(StaticCalculatingUnit::s_type) && m_has_transforms)
    {
        calculateOrbitsT();
    }
    else
    {
        calculateOrbitsNT();
    }
}

template<>
inline void CalculatingUnit<long double, LongComplex>::calculateOrbitsT()
{
    // Although this method has a template type parameter it isn't used,
    // only long double precision calculations will be performed i.e. it
    // is not intended that the method will be called on an object instantiated
    // with a type other than long double.
    long double density_factor = StaticCalculatingUnit::s_density_factor;
    int row = StaticCalculatingUnit::nextRow();
    int width = StaticCalculatingUnit::s_calculating_width;
    int height = StaticCalculatingUnit::s_calculating_height;
    // adjust number of elements calculated based on density
    height = static_cast<int>(static_cast<long double>(height)*density_factor);
    width = static_cast<int>(static_cast<long double>(width)*density_factor);
    long double pitch = StaticCalculatingUnit::s_pitch.toLDouble()/density_factor;
    int omit_number = StaticCalculatingUnit::s_omit;
    int orbit_length = m_max_iteration;
    m_orbit.resize(orbit_length - omit_number);
    m_limit = StaticCalculatingUnit::s_limit;
    while (row < height)
    {
        m_c_r = StaticCalculatingUnit::s_orbit_topleft_r;
        m_c_i = StaticCalculatingUnit::s_orbit_topleft_i - static_cast<long double>(row)*pitch;
        for (int col = 0; (col < width) && !StaticCalculatingUnit::s_stop; col++)
        {
            m_c = LongComplex(m_c_r, m_c_i);
            StaticCalculatingUnit::setZandC(m_z, m_c);
            updateParameters();
            int count = 0;
            m_iteration = 0;
            bool escaped = false;
            while (m_iteration < orbit_length)
            {
                m_z = transform(m_z);
                formula();
                m_z_r = real(m_z);
                m_z_i = imag(m_z); 
                if (m_iteration >= omit_number)
                {
                    m_orbit[count] = m_z;
                    count++;
                }
                m_iteration++;
                if (bailout())
                {
                    escaped = true;
                    break;
                }
            }
            if (count > 0)
            {
                StaticCalculatingUnit::plot(m_orbit, count, escaped);
            }
            m_c_r += pitch;
        }
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<long double, LongComplex>::calculateOrbitsNT()
{
    // Although this method has a template type parameter it isn't used,
    // only long double precision calculations will be performed i.e. it
    // is not intended that the method will be called on an object instantiated
    // with a type other than long double.
    long double density_factor = StaticCalculatingUnit::s_density_factor;
    int row = StaticCalculatingUnit::nextRow();
    int width = StaticCalculatingUnit::s_calculating_width;
    int height = StaticCalculatingUnit::s_calculating_height;
    // adjust number of elements calculated based on density
    height = static_cast<int>(static_cast<long double>(height)*density_factor);
    width = static_cast<int>(static_cast<long double>(width)*density_factor);
    long double pitch = StaticCalculatingUnit::s_pitch.toLDouble()/density_factor;
    int omit_number = StaticCalculatingUnit::s_omit;
    int orbit_length = m_max_iteration;
    m_orbit.resize(orbit_length - omit_number);
    m_limit = StaticCalculatingUnit::s_limit;
    while (row < height)
    {
        m_c_r = StaticCalculatingUnit::s_orbit_topleft_r;
        m_c_i = StaticCalculatingUnit::s_orbit_topleft_i - static_cast<long double>(row)*pitch;
        for (int col = 0; (col < width) && !StaticCalculatingUnit::s_stop; col++)
        {
            m_c = LongComplex(m_c_r, m_c_i);
            StaticCalculatingUnit::setZandC(m_z, m_c);
            updateParameters();
            int count = 0;
            int iteration = 0;
            bool escaped = false;
            while (iteration < orbit_length)
            {
                formula();
                m_z_r = real(m_z);
                m_z_i = imag(m_z); 
                if (iteration >= omit_number)
                {
                    m_orbit[count] = m_z;
                    count++;
                }
                iteration++;
                if (bailout())
                {
                    escaped = true;
                    break;
                }
            }
            if (count > 0)
            {
                StaticCalculatingUnit::plot(m_orbit, count, escaped);
            }
            m_c_r += pitch;
        }
        progress(row);
        row = StaticCalculatingUnit::nextRow();
    }
}

template<>
inline void CalculatingUnit<MpReal, MpComplex>::calculateOrbitsT()
{
    // does nothing, should never be called.
}

template<>
inline void CalculatingUnit<MpReal, MpComplex>::calculateOrbitsNT()
{
    // does nothing, should never be called.
}

template<class T1, class T2>
inline void CalculatingUnit<T1, T2>::calculateOrbit()
{
    if (!inFormulaTransforms(StaticCalculatingUnit::s_type) && m_has_transforms)
    {
        calculateOrbitT();
    }
    else
    {
        calculateOrbitNT();
    }
}

template<>
inline void CalculatingUnit<long double, LongComplex>::calculateOrbitT()
{
    // Although this method has a template type parameter it isn't used,
    // only long double precision calculations will be performed i.e. it
    // is not intended that the method will be called on an object instantiated
    // with a type other than long double.
    int plots = m_max_iteration;
    //
    m_z = StaticCalculatingUnit::s_ld_z0;
    m_iteration = 0;
    long plot = 0;
    long no_plot = 0;
    while ((plot < plots) && (no_plot < plots) && !StaticCalculatingUnit::s_stop)
    {
         m_z = transform(m_z);
         formula_so();
         m_z_r = real(m_z);
         m_z_i = imag(m_z);
         // Check for nan
         if (m_z_r != m_z_r)
         {
             break;
         }
         if (m_z_i != m_z_i)
         {
             break;
         }
         if (StaticCalculatingUnit::plot(m_z_r, m_z_i))
         {
             plot++;
             no_plot = 0;
         }
         else
         {
             no_plot++;
         }
         // plot
         m_iteration++;
         if ((m_iteration % 10000) == 0)
         {
             so_progress(plot, no_plot);
         }
    }
}

template<>
inline void CalculatingUnit<MpReal, MpComplex>::calculateOrbitT()
{
     // does nothing, should never be called.
}
template<>
inline void CalculatingUnit<long double, LongComplex>::calculateOrbitNT()
{
    // Although this method has a template type parameter it isn't used,
    // only long double precision calculations will be performed i.e. it
    // is not intended that the method will be called on an object instantiated
    // with a type other than long double.
    int plots = m_max_iteration;
    //
    m_z = StaticCalculatingUnit::s_ld_z0;
    m_iteration = 0;
    long plot = 0;
    long no_plot = 0;
    while ((plot < plots) && (no_plot < plots) && !StaticCalculatingUnit::s_stop)
    {
         formula_so();
         m_z_r = real(m_z);
         m_z_i = imag(m_z);
         // Check for nan
         if (m_z_r != m_z_r)
         {
             break;
         }
         if (m_z_i != m_z_i)
         {
             break;
         }
         if (StaticCalculatingUnit::plot(m_z_r, m_z_i))
         {
             plot++;
             no_plot = 0;
         }
         else
         {
             no_plot++;
         }
         // plot
         m_iteration++;
         if ((m_iteration % 10000) == 0)
         {
             so_progress(plot, no_plot);
         }
    }
}

template<>
inline void CalculatingUnit<MpReal, MpComplex>::calculateOrbitNT()
{
     // does nothing, should never be called.
}

template<class T1, class T2>
inline void CalculatingUnit<T1,  T2>::progress(int row)
{
    if (m_send_progress && m_progress_signals_enabled && !StaticCalculatingUnit::s_stop)
    {
        m_send_progress = false;
        m_generic->send_signal_progress(row);
    }
}

template<class T1, class T2>
inline void CalculatingUnit<T1,  T2>::so_progress(long plot, long no_plot)
{
    if (m_send_progress && m_progress_signals_enabled && !StaticCalculatingUnit::s_stop)
    {
        m_send_progress = false;
        m_generic->send_signal_so_progress(plot, no_plot);
    }
}

template<class T1, class T2>
void CalculatingUnit<T1,  T2>::set_generic(CalculatingUnitGeneric *p)
{
    m_generic = p;
}

template<>
inline bool CalculatingUnit<long double, LongComplex>::calculateLyapunovSettlingCycle()
{
    int width = StaticCalculatingUnit::s_width;
    int height = StaticCalculatingUnit::s_height;
    int row = StaticCalculatingUnit::nextRow();
    long double r;

    while (row < height)
    {
        auto rs = &(StaticCalculatingUnit::s_lyapunov_results[row*width]);
        for (int col = 0; (col < width) && !StaticCalculatingUnit::s_stop; col++, rs++)
        {
            long double& a = rs->a;
            long double& b = rs->b;
            long double& x = rs->x;

            if (rs->skip)
            {
                continue;
            }
            for (auto k = 0; k < m_num_in_sequence; k++)
            {
                r = (m_sequence[k] ? a : b);
                x = r*x*(m_one - x);
                if (std::abs(x) == m_inf)
                {
                    break;
                }
            }
        }
        row = StaticCalculatingUnit::nextRow();
    }
    return StaticCalculatingUnit::s_stop;
}

template<>
inline bool CalculatingUnit<long double, LongComplex>::calculateLyapunovCalculatingCycle(unsigned int cycle)
{
    int width = StaticCalculatingUnit::s_width;
    int height = StaticCalculatingUnit::s_height;
    int row = StaticCalculatingUnit::nextRow();
    long double r;
    long double iterations = cycle*m_num_in_sequence;
 
    while (row < height)
    {
       auto rs = &(StaticCalculatingUnit::s_lyapunov_results[row*width]);
       for (int col = 0; (col < width) && !StaticCalculatingUnit::s_stop; col++, rs++)
        {
            long double& a = rs->a;
            long double& b = rs->b;
            long double& x = rs->x;

            if (rs->skip)
            {
                continue;
            }
            for (auto k = 0; k < m_num_in_sequence; k++)
            {
                r = (m_sequence[k] ? a : b);
                x = r*x*(m_one - x);
                rs->total += (std::log(std::abs(r - m_two*r*x)))/m_ln2;
            }
            rs->lyap = rs->total/iterations;
        }
        row = StaticCalculatingUnit::nextRow();
    }
    return StaticCalculatingUnit::s_stop;
}

template<class T1, class T2>
inline T1 CalculatingUnit<T1, T2>::signum(const T1& x)
{
    if (x == m_zero)
    {
        return m_zero;
    }
    else if (x < m_zero)
    {
        return -m_one;
    }
    else
    {
        return m_one;
    }
}