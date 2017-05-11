//
// File:   TypesAndConstants.h
// Author: M.R.Eggleston
//
// Created on 22 July 2011, 17:16
//

#pragma once

#include <map>
#include <vector>
#include <QString>
#include <QColor>
#include "ldcomplex.h"
#include "mpcomplex.h"

enum FRACTAL_TYPE
{
    F_MANDELBROT,
    F_QUADRATIC,
    F_CUBIC,
    F_ALMOST_CUBIC,
    F_SINGLE_FUNCTION,
    F_ZCPAC,
    F_C_POWER_Z,
    F_2F_PRODUCT,
    F_ZPFCZ_AC,
    F_COMBINATION,
    F_BIOMORPH_1,
    F_BIOMORPH_2,
    F_BIOMORPH_3,
    F_BIOMORPH_4,
    F_BIOMORPH_5,
    F_NOVA,
    F_NOVA_1,
    F_NOVA_2,
    F_QUARTIC,
    F_QUINTIC,
    F_MAGNET,
    F_MAGNET_2,
    F_SQRT_CP,
    F_COMPASSES,
    F_PICKOVER_POPCORN_4F,
    F_PICKOVER_POPCORN_6F,
    F_COMBINATION_2,
    F_COMBINATION_3,
    F_UNNAMED,
    F_UNNAMED_2,
    F_TZACCP,
    F_ZACCP,
    F_CCZCPACZCP,
    F_FZCPAC,
    F_FTZCPAC,
    F_TZCPAC,
    F_MALLARD,
    F_TMALLARD,
    F_LYAPUNOV,
    F_ONION_4F,
    F_SINGLE_3F_ONION,
    F_DOUBLE_3F_ONION_M,
    F_DOUBLE_3F_ONION_D,
    F_ZCPTANZ,
    F_C2MFCZAC,
    F_C2DFCZAC,
    F_Z_POWER_TANCZ_AC,
    F_RN_MANDELBROT,
    F_ZAZBCGD,
    F_HYBRID,
    F_ZDUCCPAC,
    F_M3,
    F_M4,
    F_M5,
    F_M6,
    F_M7,
    F_M8,
    F_M9,
    F_M10,
    F_ATTRACTORS,
    F_GENERAL_MIXTURE,
    F_MIXTURE,
    F_MIXTURE_2,
    F_MIXTURE_3,
    F_MIXTURE_4,
    F_PR_MANDELBROT_2,
    F_PR_MANDELBROT_3,
    F_PR_SINGLE_FUNCTION_2,
    F_HOP,
    F_QUADRUP_2,
    F_THREEPLY,
    F_THREEPLY_2,
    F_CHIP,
    F_GUMOWSKI_MIRA,
    F_ATTRACTORS_SO,
    F_HOP_SO,
    F_QUADRUP_2_SO,
    F_THREEPLY_SO,
    F_THREEPLY_2_SO,
    F_CHIP_SO,
    F_GUMOWSKI_MIRA_SO,
    F_HEXIC,
    F_HEPTIC,
    F_MANDELBROT_DIVISION,
    F_OCTIC
};
    

enum OLD_FRACTAL_TYPE
{
    FT_MANDELBROT,         // -> F_MANDELBROT
    FT_QUADRATIC,          // -> F_QUADRATIC
    FT_CUBIC,              // -> F_CUBIC
    FT_ALMOST_CUBIC,       // -> F_ALMOST_CUBIC
    FT_BAD_COMPLEX_POWER,  // -> F_SINGLE_FUNCTION
    FT_JULIA,              // -> F_MANDELBROT
    FT_Z_POWER_C,          // -> F_ZCPAC
    FT_C_POWER_Z,          // -> F_C_POWER_Z
    FT_SINCZ,              // -> F_SINGLE_FUNCTION
    FT_COSCZ,              // -> F_SINGLE_FUNCTION
    FT_SINCZ_COSCZ,        // -> F_2F_PRODUCT
    FT_TANCZ,              // -> F_SINGLE_FUNCTION
    FT_UNNAMED,            // -> F_UNNAMED
    FT_Z_POWER_TANCZ,      // -> F_Z_POWER_TANCZ
    FT_COMBINATION,        // -> F_COMBINATION
    FT_BCP2,               // -> F_SINGLE_FUNCTION
    FT_TZACCP,             // -> F_TZACCP
    FT_BIOMORPH_1,         // -> F_BIOMORPH_1
    FT_BIOMORPH_2,         // -> F_BIOMORPH_2
    FT_BIOMORPH_3,         // -> F_BIOMORPH_3
    FT_BIOMORPH_4,         // -> F_BIOMORPH_4
    FT_BIOMORPH_5,         // -> F_BIOMORPH_5
    FT_MAGNET,             // -> F_MAGNET
    FT_MAGNET_2,           // -> F_MAGNET_2
    FT_ZAZBCGD,            // -> F_ZAZBCGD
    FT_COMBINATION_2,      // -> F_COMBINATION
    FT_NOVA,               // -> F_NOVA
    FT_QUADRATIC_J,        // -> F_QUADRATIC
    FT_CUBIC_J,            // -> F_CUBIC
    FT_ALMOST_CUBIC_J,     // -> F_ALMOST_CUBIC
    FT_BCP_J,              // -> F_SINGLE_FUNCTION
    FT_COMPLEX_POWER_J,    // -> F_ZCPAC
    FT_SINCZ_J,            // -> F_SINGLE_FUNCTION
    FT_COSCZ_J,            // -> F_SINGLE_FUNCTION
    FT_SINCZ_COSCZ_J,      // -> F_2F_PRODUCT
    FT_TANCZ_J,            // -> F_SINGLE_FUNCTION
    FT_UNNAMED_J,          // -> F_UNNAMED
    FT_Z_POWER_TANCZ_J,    // -> F_Z_POWER_TANCZ
    FT_COMBINATION_J,      // -> F_COMBINATION
    FT_BCP2_J,             // -> F_SINGLE_FUNCTION
    FT_TZACCP_J,           // -> F_TZACCP
    FT_MAGNET_J,           // -> F_MAGNET
    FT_MAGNET_2_J,         // -> F_MAGNET_2
    FT_ZAZBCGD_J,          // -> F_ZAZBCGD
    FT_SQRT_CPOWER,        // -> F_SQRT_CP
    FT_SQRT_CPOWER_J,      // -> F_SQRT_CP
    FT_NOVA_J,             // -> F_NOVA
    FT_NOVA_1,             // -> F_NOVA_1
    FT_NOVA_1_J,           // -> F_NOVA_1
    FT_NOVA_2,             // -> F_NOVA_2
    FT_NOVA_2_J,           // -> F_NOVA_2
    FT_UNNAMED_2,          // -> F_UNNAMED_2
    FT_UNNAMED_2_J,        // -> F_UNNAMED_2
    FT_QUARTIC,            // -> F_QUARTIC
    FT_QUARTIC_J,          // -> F_QUARTIC
    FT_QUINTIC,            // -> F_QUINTIC
    FT_QUINTIC_J,          // -> F_QUINTIC
    FT_ZCPTANZ,            // -> F_ZCPTANZ
    FT_ZCPTANZ_J,          // -> F_ZCPTANZ
    FT_LYAPUNOV,           // -> F_LYAPUNOV
    FT_PICKOVER_POPCORN,   // -> F_PICKOVER_POPCORN_4F
    FT_COMPASSES,          // -> F_COMPASSES
    FT_COMPASSES_J,        // -> F_COMPASES
    FT_RN_MANDELBROT,      // -> F_RN_MANDELBROT
    FT_RN_JULIA,           // -> F_RN_MANDELBROT
    FT_PP_MANDELBROT,      // -> F_PICKOVER_POPCORN_4F
    FT_PP_JULIA,           // -> F_PICKOVER_POPCORN_4F
    FT_HYBRID,             // -> F_HYBRID
    FT_HYBRID_J,           // -> F_HYBRID
    FT_PICKOVER_POPCORN_2, // -> F_PICKOVER_POPCORN_4F
    FT_PICKOVER_POPCORN_3, // -> F_PICKOVER_POPCORN_4F
    FT_PICKOVER_POPCORN_4, // -> F_PICKOVER_POPCORN_4F
    FT_PP_MANDELBROT_2,    // -> F_PICKOVER_POPCORN_4F
    FT_PP_MANDELBROT_3,    // -> F_PICKOVER_POPCORN_4F
    FT_PP_MANDELBROT_4,    // -> F_PICKOVER_POPCORN_4F
    FT_PP_JULIA_2,         // -> F_PICKOVER_POPCORN_4F
    FT_PP_JULIA_3,         // -> F_PICKOVER_POPCORN_4F
    FT_PP_JULIA_4,         // -> F_PICKOVER_POPCORN_4F
    FT_ZDUCCPAC,           // -> F_ZDUCCPAC
    FT_ZDUCCPAC_J,         // -> F_ZDUCCPAC
    FT_MALLARD = 82,       // -> F_MALLARD
    FT_MALLARD_J,          // -> F_MALLARD
    FT_ZCPAC,              // -> F_ZCPAC
    FT_ZCPAC_J,            // -> F_ZCPAC
    FT_PICKOVER_POPCORN_5, // -> F_PICKOVER_POPCORN_6F
    FT_PP_MANDELBROT_5,    // -> F_PICKOVER_POPCORN_6F
    FT_PP_JULIA_5,         // -> F_PICKOVER_POPCORN_6F
    FT_TZDRICPAC,          // -> deleted
    FT_TZDRICPAC_J,        // -> deleted
    FT_TZCPAC,             // -> F_TZCPAC
    FT_TZCPAC_J,           // -> F_TZCPAC
    FT_TMALLARD,           // -> F_TMALLARD
    FT_TMALLARD_J,         // -> F_TMALLARD
    FT_LZCPAC,             // -> F_FZCPAC
    FT_LZCPAC_J,           // -> F_FZCPAC
    FT_LTZCPAC,            // -> F_FTZCPAC
    FT_LTZCPAC_J,          // -> F_FTZCPAC
    FT_ZACCP,              // -> F_ZACCP
    FT_ZACCP_J,            // -> F_ZACCP
    FT_PP_MANDELBROT_4F,   // -> F_PICKOVER_POPCORN_4F
    FT_PP_MANDELBROT_6F,   // -> F_PICKOVER_POPCORN_6F
    FT_PP_JULIA_4F,        // -> F_PICKOVER_POPCORN_4F
    FT_PP_JULIA_6F,        // -> F_PICKOVER_POPCORN_6F
    FT_PICKOVER_POPCORN_4F, // -> F_PICKOVER_POPCORN_4F
    FT_PICKOVER_POPCORN_6F, // -> F_PICKOVER_POPCORN_6F
    FT_CCZCPACZCP,          // -> F_CCZCPACZCP
    FT_CCZCPACZCP_J,        // -> F_CCZCPACZCP
    FT_ONION_4F,            // -> F_ONION_4F
    FT_ONION_4F_J,          // -> F_ONION_4F
    FT_COMBINATION_3,       // -> F_COMBINATION_3
    FT_COMBINATION_4,       // -> F_COMBINATION_3
    FT_C2MFCZAC,            // -> F_C2MFCZAC
    FT_C2MFCZAC_J,          // -> F_C2MFCZAC
    FT_C2DFCZAC,            // -> F_C2DFCZAC
    FT_C2DFCZAC_J,          // -> F_C2DFCZAC
    FT_SINGLE_3F_ONION,     // -> F_SINGLE_3F_ONION
    FT_SINGLE_3F_ONION_J,   // -> F_SINGLE_3F_ONION
    FT_DOUBLE_3F_ONION_M,   // -> F_DOUBLE_3F_ONION_M
    FT_DOUBLE_3F_ONION_M_J, // -> F_DOUBLE_3F_ONION_M
    FT_DOUBLE_3F_ONION_D,   // -> F_DOUBLE_3F_ONION_D
    FT_DOUBLE_3F_ONION_D_J  // -> F_DOUBLE_3F_ONION_D
};


enum TRANSFORM
{
    T_TRANSLATION,
    T_ROTATION,
    T_SCALE,
    T_UNSIGN_REAL,
    T_SIGN_REAL,
    T_REVERSE_SIGN_REAL,
    T_UNSIGN_IMAGINARY,
    T_SIGN_IMAGINARY,
    T_REVERSE_SIGN_IMAGINARY,
    T_CIRCLE_IN,
    T_CIRCLE_OUT,
    T_CIRCLE_REFLECT,
    T_TOP_RIGHT = 18,
    T_BOTTOM_RIGHT,
    T_TOP_LEFT,
    T_BOTTOM_LEFT,
    T_INVERSE_FOLD_IN = 25,
    T_INVERSE_FOLD_OUT,
    T_INVERSE_REFLECT,
    T_POWER,
    T_LOG,
    T_EXP
};

enum INITIAL_VALUE
{
    FIXED,
    UNTRANSFORMED,
    TRANSFORMED
};

enum TRANSFORM_SET
{
    COMPLEX_PLANE,
    TRANSFORMS_A,
    TRANSFORMS_B
};

enum BAILOUT
{
    B_NONE,
    B_ABS,
    B_NORM,
    B_IMAG,
    B_IMAG_SQUARED,
    B_REAL,
    B_REAL_SQUARED,
    B_ABS_PRODUCT,
    B_MANHATTAN,
    B_MANHATTANISH,
    B_ABS_MANHATTANISH,
    B_MAX_SQUARED,
    B_MIN_SQUARED,
    B_ABS_DIFF
};

// earlier than version 3.0

enum OLD_FUNCTION_PARAMETER
{
    OLD_FP_COS,
    OLD_FP_SIN,
    OLD_FP_TAN,
    OLD_FP_SEC,
    OLD_FP_COSEC,
    OLD_FP_COTAN,
    OLD_FP_NO_OP
};

// version 3.0 FUNCTION_PARAMETER replacement

enum FUNCTION_PARAMETER
{
    FP_NO_OP,
    FP_REVERSE_SIGN, // "+/-"
    FP_UNSIGN,       // "abs"
    FP_SIGN,         // "-abs"
    FP_ADD,
    FP_ACOS,
    FP_ASIN,
    FP_ATAN,
    FP_CEILING,
    FP_COS,
    FP_COSEC,
    FP_COSH,
    FP_COTAN,
    FP_EXP,
    FP_FLOOR,
    FP_LOG,
    FP_NUMBER,
    FP_POWER,
    FP_ROUND,
    FP_SCALE,
    FP_SEC,
    FP_SIN,
    FP_SINH,
    FP_TAN,
    FP_TANH,
    FP_TRUNC
};

enum ORBIT_PLOTS
{
    OP_ALL,
    OP_ESCAPED,
    OP_CAPTIVE
};

// earlier than version 3.0

enum OLD_COMPLEX_FUNCTION_PARAMETER
{
    OLD_CFP_NO_OP,
    OLD_CFP_ACOS,
    OLD_CFP_ASIN,
    OLD_CFP_ATAN,
    OLD_CFP_COS,
    OLD_CFP_COSEC,
    OLD_CFP_COSH,
    OLD_CFP_COTAN,
    OLD_CFP_CUBE,
    OLD_CFP_CUBE_ROOT,
    OLD_CFP_EXP,
    OLD_CFP_INVERSE,
    OLD_CFP_INVERSE_SQUARE,
    OLD_CFP_LOG,
    OLD_CFP_SEC,
    OLD_CFP_SIN,
    OLD_CFP_SINH,
    OLD_CFP_SQUARE,
    OLD_CFP_SQUARE_ROOT,
    OLD_CFP_TAN,
    OLD_CFP_TANH,
};

// Version 3.0

enum COMPLEX_FUNCTION_PARAMETER
{
    CFP_NO_OP,
    CFP_ACOS,
    CFP_ACOSH,
    CFP_ASIN,
    CFP_ASINH,
    CFP_ATAN,
    CFP_ATANH,
    CFP_BCP,
    CFP_BCP2,
    CFP_CIRCLE_FOLD_IN,
    CFP_CIRCLE_FOLD_OUT,
    CFP_CIRCLE_REFLECT,
    CFP_COS,
    CFP_COSEC,
    CFP_COSH,
    CFP_COTAN,
    CFP_EXP,
    CFP_INVERSE_FOLD_IN,
    CFP_INVERSE_FOLD_OUT,
    CFP_INVERSE_REFLECT,
    CFP_LOG,
    CFP_MULTIPLY,
    CFP_POWER,
    CFP_PRODUCT,
    CFP_ROTATION,
    CFP_SEC,
    CFP_SIN,
    CFP_SINH,
    CFP_TAN,
    CFP_TANH
};

enum ORBIT_COLOUR
{
    OC_ACCUMULATION,
    OC_SQRT,
    OC_AVERAGE,
    OC_LOG
};

enum COLOURING
{
    OUTER,
    INNER
};

enum RGB
{
    RGB_RED,
    RGB_GREEN,
    RGB_BLUE
};

enum COLOUR_TYPE
{
    CT_RED,
    CT_GREEN,
    CT_BLUE,
    CT_ALL
};

enum COMPONENT_ORDER
{
    CO_RGB,
    CO_RBG,
    CO_GRB,
    CO_GBR,
    CO_BRG,
    CO_BGR
};

typedef std::vector<QRgb> VectorColour;
typedef std::vector<int> VectorInt;
typedef std::vector<unsigned int> VectorUInt;
typedef std::map<int, int> IntMap;

typedef ld::complex LongComplex;
typedef mpfr::mpcomplex MpComplex;
typedef mpfr::mpreal MpReal;
typedef std::vector<LongComplex> VectorLongComplex;

typedef std::vector<bool> VectorBool;

struct StringComplex
{
    StringComplex() : r("0"), i("0") {};
    StringComplex(const std::string& s1, const std::string& s2) : r(s1), i(s2) {};
    std::string r;
    std::string i;
};

typedef std::map<int, long double> LongDoubleMap;
typedef std::map<int, LongComplex> ComplexMap;
typedef std::vector<std::string> TransformRecordVector;
typedef std::map<OLD_FUNCTION_PARAMETER, QString> FunctionStringMap;

struct Statistics
{
    LongComplex min_dist;
    LongComplex max_dist;
    long double minimum;
    long double maximum;
    long double angle_total;
    long double square_total;
    long double total;
    int iteration_at_min;
    int iteration_at_max;
    long double es_sum1;
    long double es_sum2;
    long double last;     // Last value as a magnitude or an angle, first multiple data
    long double es2_last;
};

struct ResultsSet
{
    bool done;
    long escape;
    long double z_r;
    long double z_i;
    long double c_r;
    long double c_i;
    Statistics set[2];
};

typedef std::vector<ResultsSet> VectorResultsSet;
// Only used for cycle by cycle calculation

struct LyapunovResultsSet
{
    long double a;
    long double b;
    long double x;
    long double total;
    long double lyap; 
    bool skip; // calculation finished, a or b is zero or x is +/-inf
};

typedef std::vector<LyapunovResultsSet> VectorLyapunovResultsSet;

enum COLOURING_TYPE // for orbit plotting
{
    ACCUMULATION,
    LAST,
    AVERAGE
};

struct ColourAccumulator    // for orbit plotting
{
    unsigned int red;
    unsigned int green;
    unsigned int blue;
};

typedef std::vector<ColourAccumulator> VectorColourAccumulator;

enum PARAMETER_TYPE
{
    PT_NUMBER,
    PT_IS_C,
    PT_IS_NEG_C
};

struct ComplexParameter
{
   StringComplex  p;
   PARAMETER_TYPE type;
};

#define MAX_PARAMETERS 9

#define BASE_PRECISION (sizeof(long double) == 8 ? 64 : 80)

#define LEVEL 9
