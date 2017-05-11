// 
// File:   Utilities.cc
// Author: M.R.Eggleston
//
// Created on 04 January 2012, 11:26
//

#include <boost/lexical_cast.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <QDir>
#include "KeyString.h"
#include "Utilities.h"

std::string intToString(int value)
{
    return boost::lexical_cast<std::string>(value);
}

std::string intToString(bool value)
{
    return boost::lexical_cast<std::string>(value);
}

std::string uintToString(unsigned int value)
{
    return boost::lexical_cast<std::string>(value);
}

std::string ulongToString(unsigned long value)
{
    return boost::lexical_cast<std::string>(value);
}

std::string longdoubleToString(long double value)
{
    std::stringstream str;
    str << std::setprecision(std::numeric_limits<long double>::digits10) << value;
    return std::string(str.str());
}

QString longdoubleToQString(long double value)
{
    return QString::fromStdString(longdoubleToString(value));
}

std::string longdoubleToString(long double value, bool fixed, int precision)
{
    std::stringstream str;
    if (fixed)
    {
        str << std::fixed;
    }
    str << std::setprecision(precision) << value;
    return str.str();
}

QString complexNumberToString(const StringComplex &z)
{
    bool neg_i = (z.i[0] == '-');
    QString str = QString::fromStdString(z.r) + (neg_i ? " - " : " + ");
    str += QString::fromStdString((neg_i ? z.i.substr(1) : z.i)) + "i";
    return str;
}

QColor stringToColour(const std::string& str)
{
    QColor c;
    try
    {
        std::istringstream input(str);
        int value;
        char junk;
        input >> value;
        int red = value;
        input >> junk;
        input >> value;
        int green = value;
        input >> junk;
        input >> value;
        int blue = value;
        c = QColor(red, green, blue);
    }
    catch (std::exception&)
    {
        c = QColor(0, 0, 0);
    }
    return c;
}

unsigned int stringToUint(const std::string& str)
{
    unsigned int value = 0;
    try
    {
        value = boost::lexical_cast<unsigned int>(str);
    }
    catch (...)
    {
        // ignore
    }
    return value;
}

int stringToInt(const std::string& str)
{
    int value = 0;
    try
    {
        value = boost::lexical_cast<int>(str);
    }
    catch (...)
    {
        // ignore
    }
    return value;
}

long double stringToLongDouble(const std::string& str)
{
    long double value = 0.0L;
    try
    {
        value = boost::lexical_cast<long double>(str);
    }
    catch (...)
    {
        // ignore
    }
    return value;
}

LongComplex stdStringToLongComplex(const std::string& s1, const std::string& s2)
{
    long double r = stringToLongDouble(s1);
    long double i = stringToLongDouble(s2);
    return LongComplex(r, i);
}

LongComplex stringComplexToLongComplex(const StringComplex &z)
{
    return LongComplex(stringToLongDouble(z.r), stringToLongDouble(z.i));
}

MpComplex stringComplexToMpComplex(const StringComplex &z, int precision)
{
    return MpComplex(MpReal(z.r, precision), MpReal(z.i, precision));
}

long double trunc(long double value)
{
    // not std::trunc as it is not supported by MS C++
    return (value < 0.0L ? ceil(value) : floor(value));
}

std::string convert(OLD_FUNCTION_PARAMETER fp)
{
    struct pair
    {
        OLD_FUNCTION_PARAMETER old_function;
        FUNCTION_PARAMETER new_function;
    };
    static pair pairs[7] = { { OLD_FP_COS, FP_COS },
                             { OLD_FP_SIN, FP_SIN },
                             { OLD_FP_TAN, FP_TAN },
                             { OLD_FP_SEC, FP_SEC },
                             { OLD_FP_COSEC, FP_COSEC },
                             { OLD_FP_COTAN, FP_COTAN },
                             { OLD_FP_NO_OP, FP_NO_OP }};
    int id = 6;
    for (int i = 0; i < 7; i++)
    {
        if (fp == pairs[i].old_function)
        {
            id = i;
            break;
        }
    }
    return "id=" + intToString(static_cast<int>(pairs[id].new_function));
}

std::string convert(OLD_COMPLEX_FUNCTION_PARAMETER fp)
{
    struct pair
    {
        OLD_COMPLEX_FUNCTION_PARAMETER old_function;
        COMPLEX_FUNCTION_PARAMETER new_function;
    };
    static pair pairs[21] = { { OLD_CFP_NO_OP, CFP_NO_OP },
                              { OLD_CFP_ACOS, CFP_ACOS },
                              { OLD_CFP_ASIN, CFP_ASIN },
                              { OLD_CFP_ATAN, CFP_ATAN },
                              { OLD_CFP_COS, CFP_COS },
                              { OLD_CFP_COSEC, CFP_COSEC },
                              { OLD_CFP_COSH, CFP_COSH },
                              { OLD_CFP_COTAN, CFP_COTAN },
                              { OLD_CFP_CUBE, CFP_POWER },
                              { OLD_CFP_CUBE_ROOT, CFP_POWER },
                              { OLD_CFP_EXP, CFP_EXP },
                              { OLD_CFP_INVERSE, CFP_POWER },
                              { OLD_CFP_INVERSE_SQUARE, CFP_POWER },
                              { OLD_CFP_LOG, CFP_LOG },
                              { OLD_CFP_SEC, CFP_SEC },
                              { OLD_CFP_SIN, CFP_SIN },
                              { OLD_CFP_SINH, CFP_SINH },
                              { OLD_CFP_SQUARE, CFP_POWER },
                              { OLD_CFP_SQUARE_ROOT, CFP_POWER },
                              { OLD_CFP_TAN, CFP_TAN },
                              { OLD_CFP_TANH, CFP_TANH } };
    std::string value;
    std::string parameter;
    if (fp == OLD_CFP_CUBE)
    {
        parameter = ",r=3.0";
    }
    else if (fp == OLD_CFP_CUBE_ROOT)
    {
        parameter = ",r=" + longdoubleToString(1.0L/3.0L);
    }
    else if (fp == OLD_CFP_INVERSE)
    {
        parameter = ",r=-1.0";
    }
    else if (fp == OLD_CFP_INVERSE_SQUARE)
    {
        parameter = ",r=-2.0";
    }
    else if (fp == OLD_CFP_SQUARE)
    {
        parameter = ",r=2.0";
    }
    else if (fp == OLD_CFP_SQUARE_ROOT)
    {
        parameter = ",r=0.5";
    }
    for (int i = 0; i < 21; i++)
    {
        if (fp == pairs[i].old_function)
        {
            value = "pair=n,id=";
            value += intToString(static_cast<int>(pairs[i].new_function));
            value += parameter;
            value += ",i=0";
        }
    }
    return value;
}

FRACTAL_TYPE convert(OLD_FRACTAL_TYPE ft)
{
    switch (ft)
    {
    default:
    case FT_MANDELBROT: return F_MANDELBROT;
    case FT_QUADRATIC: return F_QUADRATIC;
    case FT_CUBIC: return F_CUBIC;
    case FT_ALMOST_CUBIC: return F_ALMOST_CUBIC;
    case FT_BAD_COMPLEX_POWER: return F_SINGLE_FUNCTION;
    case FT_JULIA: return F_MANDELBROT;
    case FT_Z_POWER_C: return F_ZCPAC;
    case FT_C_POWER_Z: return F_C_POWER_Z;
    case FT_SINCZ: return F_SINGLE_FUNCTION;
    case FT_COSCZ: return F_SINGLE_FUNCTION;
    case FT_SINCZ_COSCZ: return F_2F_PRODUCT;
    case FT_TANCZ: return F_SINGLE_FUNCTION;
    case FT_UNNAMED: return F_UNNAMED;
    case FT_Z_POWER_TANCZ: return F_Z_POWER_TANCZ_AC;
    case FT_COMBINATION: return F_COMBINATION;
    case FT_BCP2: return F_SINGLE_FUNCTION;
    case FT_TZACCP: return F_TZACCP;
    case FT_BIOMORPH_1: return F_BIOMORPH_1;
    case FT_BIOMORPH_2: return F_BIOMORPH_2;
    case FT_BIOMORPH_3: return F_BIOMORPH_3;
    case FT_BIOMORPH_4: return F_BIOMORPH_4;
    case FT_BIOMORPH_5: return F_BIOMORPH_5;
    case FT_MAGNET: return F_MAGNET;
    case FT_MAGNET_2: return F_MAGNET_2;
    case FT_ZAZBCGD: return F_ZAZBCGD;
    case FT_COMBINATION_2: return F_COMBINATION_2;
    case FT_NOVA: return F_NOVA;
    case FT_QUADRATIC_J: return F_QUADRATIC;
    case FT_CUBIC_J: return F_CUBIC;
    case FT_ALMOST_CUBIC_J: return F_ALMOST_CUBIC;
    case FT_BCP_J: return F_SINGLE_FUNCTION;
    case FT_COMPLEX_POWER_J: return F_ZCPAC;
    case FT_SINCZ_J: return F_SINGLE_FUNCTION;
    case FT_COSCZ_J: return F_SINGLE_FUNCTION;
    case FT_SINCZ_COSCZ_J: return F_2F_PRODUCT;
    case FT_TANCZ_J: return F_SINGLE_FUNCTION;
    case FT_UNNAMED_J: return F_UNNAMED;
    case FT_Z_POWER_TANCZ_J: return F_Z_POWER_TANCZ_AC;
    case FT_COMBINATION_J: return F_COMBINATION;
    case FT_BCP2_J: return F_SINGLE_FUNCTION;
    case FT_TZACCP_J: return F_TZACCP;
    case FT_MAGNET_J: return F_MAGNET;
    case FT_MAGNET_2_J: return F_MAGNET_2;
    case FT_ZAZBCGD_J: return F_ZAZBCGD;
    case FT_SQRT_CPOWER: return F_SQRT_CP;
    case FT_SQRT_CPOWER_J: return F_SQRT_CP;
    case FT_NOVA_J: return F_NOVA;
    case FT_NOVA_1: return F_NOVA_1;
    case FT_NOVA_1_J: return F_NOVA_1;
    case FT_NOVA_2: return F_NOVA_2;
    case FT_NOVA_2_J: return F_NOVA_2;
    case FT_UNNAMED_2: return F_UNNAMED_2;
    case FT_UNNAMED_2_J: return F_UNNAMED_2;
    case FT_QUARTIC: return F_QUARTIC;
    case FT_QUARTIC_J: return F_QUARTIC;
    case FT_QUINTIC: return F_QUINTIC;
    case FT_QUINTIC_J: return F_QUINTIC;
    case FT_ZCPTANZ: return F_ZCPTANZ;
    case FT_ZCPTANZ_J: return F_ZCPTANZ;
    case FT_LYAPUNOV: return F_LYAPUNOV;
    case FT_PICKOVER_POPCORN: return F_PICKOVER_POPCORN_4F;
    case FT_COMPASSES: return F_COMPASSES;
    case FT_COMPASSES_J: return F_COMPASSES;
    case FT_RN_MANDELBROT: return F_RN_MANDELBROT;
    case FT_RN_JULIA: return F_RN_MANDELBROT;
    case FT_PP_MANDELBROT: return F_PICKOVER_POPCORN_4F;
    case FT_PP_JULIA: return F_PICKOVER_POPCORN_4F;
    case FT_HYBRID: return F_HYBRID;
    case FT_HYBRID_J: return F_HYBRID;
    case FT_PICKOVER_POPCORN_2: return F_PICKOVER_POPCORN_4F;
    case FT_PICKOVER_POPCORN_3: return F_PICKOVER_POPCORN_4F;
    case FT_PICKOVER_POPCORN_4: return F_PICKOVER_POPCORN_4F;
    case FT_PP_MANDELBROT_2: return F_PICKOVER_POPCORN_4F;
    case FT_PP_MANDELBROT_3: return F_PICKOVER_POPCORN_4F;
    case FT_PP_MANDELBROT_4: return F_PICKOVER_POPCORN_4F;
    case FT_PP_JULIA_2: return F_PICKOVER_POPCORN_4F;
    case FT_PP_JULIA_3: return F_PICKOVER_POPCORN_4F;
    case FT_PP_JULIA_4: return F_PICKOVER_POPCORN_4F;
    case FT_ZDUCCPAC: return F_ZDUCCPAC;
    case FT_ZDUCCPAC_J: return F_ZDUCCPAC;
    case FT_MALLARD: return F_MALLARD;
    case FT_MALLARD_J: return F_MALLARD;
    case FT_ZCPAC: return F_ZCPAC;
    case FT_ZCPAC_J: return F_ZCPAC;
    case FT_PICKOVER_POPCORN_5: return F_PICKOVER_POPCORN_6F;
    case FT_PP_MANDELBROT_5: return F_PICKOVER_POPCORN_6F;
    case FT_PP_JULIA_5: return F_PICKOVER_POPCORN_6F;
    case FT_TZCPAC: return F_TZCPAC;
    case FT_TZCPAC_J: return F_TZCPAC;
    case FT_TMALLARD: return F_TMALLARD;
    case FT_TMALLARD_J: return F_TMALLARD;
    case FT_LZCPAC: return F_FZCPAC;
    case FT_LZCPAC_J: return F_FZCPAC;
    case FT_LTZCPAC: return F_FTZCPAC;
    case FT_LTZCPAC_J: return F_FTZCPAC;
    case FT_ZACCP: return F_ZACCP;
    case FT_ZACCP_J: return F_ZACCP;
    case FT_PP_MANDELBROT_4F: return F_PICKOVER_POPCORN_4F;
    case FT_PP_MANDELBROT_6F: return F_PICKOVER_POPCORN_6F;
    case FT_PP_JULIA_4F: return F_PICKOVER_POPCORN_4F;
    case FT_PP_JULIA_6F: return F_PICKOVER_POPCORN_6F;
    case FT_PICKOVER_POPCORN_4F: return F_PICKOVER_POPCORN_4F;
    case FT_PICKOVER_POPCORN_6F: return F_PICKOVER_POPCORN_4F;
    case FT_CCZCPACZCP: return F_CCZCPACZCP;
    case FT_CCZCPACZCP_J: return F_CCZCPACZCP;
    case FT_ONION_4F: return F_ONION_4F;
    case FT_ONION_4F_J: return F_ONION_4F;
    case FT_COMBINATION_3: return F_COMBINATION_3;
    case FT_COMBINATION_4: return F_COMBINATION_3;
    case FT_C2MFCZAC: return F_C2MFCZAC;
    case FT_C2MFCZAC_J: return F_C2MFCZAC;
    case FT_C2DFCZAC: return F_C2DFCZAC;
    case FT_C2DFCZAC_J: return F_C2DFCZAC;
    case FT_SINGLE_3F_ONION: return F_SINGLE_3F_ONION;
    case FT_SINGLE_3F_ONION_J: return F_SINGLE_3F_ONION;
    case FT_DOUBLE_3F_ONION_M: return F_DOUBLE_3F_ONION_M;
    case FT_DOUBLE_3F_ONION_M_J: return F_DOUBLE_3F_ONION_M;
    case FT_DOUBLE_3F_ONION_D: return F_DOUBLE_3F_ONION_D;
    case FT_DOUBLE_3F_ONION_D_J: return F_DOUBLE_3F_ONION_D;
    }
}

QString functionAsString(FUNCTION_PARAMETER fp)
{
    static std::map<FUNCTION_PARAMETER, QString> function;
    if (function.empty())
    {
        function[FP_NO_OP] = "no-op";
        function[FP_REVERSE_SIGN] = "+/-";
        function[FP_UNSIGN] = "abs";
        function[FP_SIGN] = "-abs";
        function[FP_ADD] = "add";
        function[FP_ACOS] = "acos(fraction())";
        function[FP_ASIN] = "asin(fraction())";
        function[FP_ATAN] = "atan";
        function[FP_CEILING] = "ceiling";
        function[FP_COS] = "cos";
        function[FP_COSEC] = "cosec";
        function[FP_COSH] = "cosh";
        function[FP_COTAN] = "cotan";
        function[FP_EXP] = "exp";
        function[FP_FLOOR] = "floor";
        function[FP_LOG] = "log(abs())";
        function[FP_NUMBER] = "number";
        function[FP_POWER] = "power";
        function[FP_ROUND] = "round";
        function[FP_SCALE] = "scale";
        function[FP_SEC] = "sec";
        function[FP_SIN] = "sin";
        function[FP_SINH] = "sinh";
        function[FP_TAN] = "tan";
        function[FP_TANH] = "tanh";
        function[FP_TRUNC] = "trunc";
    }
    return (function.count(fp) != 1 ? "unknown" : function[fp]);
}

QString complexFunctionAsString(COMPLEX_FUNCTION_PARAMETER fp)
{
    static std::map<COMPLEX_FUNCTION_PARAMETER, QString> function;
    if (function.empty())
    {
        function[CFP_NO_OP] = "no-op";
        function[CFP_ACOS] = "acos";
        function[CFP_ASIN] = "asin";
        function[CFP_ATAN] = "atan";
        function[CFP_ACOSH] = "acosh";
        function[CFP_ASINH] = "asinh";
        function[CFP_ATANH] = "atanh";
        function[CFP_BCP] = "bcp";
        function[CFP_BCP2] = "bcp2";
        function[CFP_CIRCLE_FOLD_IN] = "circle fold in";
        function[CFP_CIRCLE_FOLD_OUT] = "circle fold out";
        function[CFP_CIRCLE_REFLECT] = "circle reflect";
        function[CFP_COS] = "cos";
        function[CFP_COSEC] = "cosec";
        function[CFP_COSH] = "cosh";
        function[CFP_COTAN] = "cotan";
        function[CFP_EXP] = "exp";
        function[CFP_INVERSE_FOLD_IN] = "inverse fold in";
        function[CFP_INVERSE_FOLD_OUT] = "inverse fold out";
        function[CFP_INVERSE_REFLECT] = "inverse reflect";
        function[CFP_LOG] = "log";
        function[CFP_MULTIPLY] = "multiply";
        function[CFP_POWER] = "power";
        function[CFP_PRODUCT] = "product";
        function[CFP_ROTATION] = "rotation";
        function[CFP_SEC] = "sec";
        function[CFP_SIN] = "sin";
        function[CFP_SINH] = "sinh";
        function[CFP_TAN] = "tan";
        function[CFP_TANH] = "tanh";
    }
    return (function.count(fp) != 1 ? "unknown" : function[fp]);
}

bool hasParameter(COMPLEX_FUNCTION_PARAMETER p)
{
    return (p == CFP_POWER) || (p == CFP_BCP) || (p == CFP_BCP2) || (p == CFP_MULTIPLY);
}

bool hasRotation(COMPLEX_FUNCTION_PARAMETER p)
{
    return (p == CFP_ROTATION);
}

bool hasSize(COMPLEX_FUNCTION_PARAMETER p)
{
    return (p == CFP_CIRCLE_FOLD_IN) || (p == CFP_CIRCLE_FOLD_OUT) ||
           (p == CFP_CIRCLE_REFLECT) || (p == CFP_INVERSE_FOLD_IN) ||
           (p == CFP_INVERSE_FOLD_OUT) || (p == CFP_INVERSE_REFLECT);
}

bool hasParameter(FUNCTION_PARAMETER p)
{
    return (p == FP_ADD) || (p == FP_SCALE) || (p == FP_NUMBER) || (p == FP_POWER);
}

int determinePrecision(const StringComplex& c, const std::string& w, int hpixels, int vpixels)
{
    // c is the position of the centre of the image and width is added to it
    // a point horizontally relative to it. The number of pixels from x to y
    // should be the same as the number of pixels specified. The height is
    // determined and the number of pixels is a gain determined.
    //
    // A tolerance of +/- 0.05 pixels is deemed acceptable.
    //
    // This won't work if if x is close to or at zero, so add 2.0L just in case
    //
    // First try long doubles
    //
    mp_prec_t precision = BASE_PRECISION;
    // check horizontal
    long double error = 0.05L;
    long double ld_pixels = static_cast<long double>(hpixels);
    long double pos1 = std::abs(stringToLongDouble(c.r)) + 10.0L;
    std::string base_x = longdoubleToString(pos1);
    long double length = stringToLongDouble(w);
    long double pitch = length/ld_pixels;
    long double pos2 = pos1 + length;
    long double check = (pos2 - pos1)/pitch;
    bool acceptable = (check > (ld_pixels - error)) && (check < (ld_pixels + error));
    if (acceptable)
    {
        // Check vertical
        long double ld_pixels = static_cast<long double>(vpixels);
        long double pos1 = std::abs(stringToLongDouble(c.i)) + 10.0L;
        long double length = stringToLongDouble(w);
        length = (length*static_cast<long double>(vpixels))/static_cast<long double>(hpixels);
        long double pitch = length/ld_pixels;
        long double pos2 = pos1 + length;
        long double check = (pos2 - pos1)/pitch;
        acceptable = (check > (ld_pixels - error)) && (check < (ld_pixels + error));
    }
    
    while (!acceptable)
    {
        // do it again increasing precision until it is acceptable
        precision += 16;
        MpReal pos1 = MpReal(c.r) + MpReal(10, precision);
        MpReal length(w, precision);
        MpReal mp_pixels(hpixels, precision); // width in pixels
        MpReal pitch = length/mp_pixels;
        MpReal pos2 = pos1 + length;
        MpReal mp_check = (pos2 - pos1)/pitch;
        long double check = mp_check.toLDouble();
        acceptable = (check > (ld_pixels - error)) && (check < (ld_pixels + error));
        if (acceptable)
        {
            // Check vertical
            MpReal mp_pixels(vpixels, precision);
            MpReal pos1 = MpReal(c.i) + MpReal(10, precision);
            MpReal length = MpReal(w, precision);
            length = (length*MpReal(vpixels, precision))/MpReal(hpixels, precision);
            MpReal pitch = length/ld_pixels;
            MpReal pos2 = pos1 + length;
            MpReal mp_check = (pos2 - pos1)/pitch;
            long double check = mp_check.toLDouble();
            acceptable = (check > (ld_pixels - error)) && (check < (ld_pixels + error));
        }
    }
    return precision;
}

QString complexFunctionToString(const std::string& func)
{
    QString str;
    KeyString keys(func);
    if (keys.GetKey("pair", "n") == "n")
    {
        // Complex function
        auto id = static_cast<COMPLEX_FUNCTION_PARAMETER>(keys.GetKeyAsInt("id", 0));
        str += complexFunctionAsString(id);
        if (hasParameter(id))
        {
            StringComplex p;
            p.r = abbreviate(keys.GetKey("r", "0"));
            p.i = abbreviate(keys.GetKey("i", "0"));
            str += "(";
            str += complexNumberToString(p);
            str += ")";
        }
        if (hasRotation(id))
        {
            str += "(";
            str += QString::fromStdString(keys.GetKey("rotation", "0"));
            str += " degrees)";
        }
        if (hasSize(id))
        {
            str += "(";
            str += QString::fromStdString(abbreviate(keys.GetKey("size", "0")));
            str += ")";
        }
    }
    else
    {
        // Functions applied individually to each component
        auto rid = static_cast<FUNCTION_PARAMETER>(keys.GetKeyAsInt("rid", 0));
        auto iid = static_cast<FUNCTION_PARAMETER>(keys.GetKeyAsInt("iid", 0));
        str += functionAsString(rid);
        if (hasParameter(rid))
        {
            str += "(";
            str += QString::fromStdString(abbreviate(keys.GetKey("r", "0")));
            str += ")";
        }
        str += ", ";
        str += functionAsString(iid);
        if (hasParameter(iid))
        {
            str += "(";
            str += QString::fromStdString(abbreviate(keys.GetKey("i", "0")));
            str += ")";
        }
    }
    return str;
}

QString functionToString(const std::string &func)
{
    QString str;
    KeyString keys(func);
    auto id = static_cast<FUNCTION_PARAMETER>(keys.GetKeyAsInt("id", 0));
    str += functionAsString(id);
    if (hasParameter(id))
    {
        str += ", ";
        str += QString::fromStdString(keys.GetKey("p", "0"));
    }
    return str;
}

std::string convertTranslation(long double r, long double i)
{
    KeyString keys;
    keys.SetKey("pair","y");
    keys.SetKey("rid", static_cast<int>(FP_ADD));
    keys.SetKey("r", r);
    keys.SetKey("iid", static_cast<int>(FP_ADD));
    keys.SetKey("i", i);
    return keys.String();
}

std::string convertScale(long double r, long double i)
{
    KeyString keys;
    keys.SetKey("pair", "y");
    keys.SetKey("rid", static_cast<int>(FP_SCALE));
    keys.SetKey("r", r);
    keys.SetKey("iid", static_cast<int>(FP_SCALE));
    keys.SetKey("i", i);
    return keys.String();
}

std::string convertRotation(int rotation)
{
    KeyString keys;
    keys.SetKey("pair", "n");
    keys.SetKey("id", static_cast<int>(CFP_ROTATION));
    keys.SetKey("rotation", rotation);
    return keys.String();
}

std::string convertUnsignReal()
{
    KeyString keys;
    keys.SetKey("pair", "y");
    keys.SetKey("rid", static_cast<int>(FP_UNSIGN));
    keys.SetKey("iid", static_cast<int>(FP_NO_OP));
    return keys.String();
}

std::string convertSignReal()
{
    KeyString keys;
    keys.SetKey("pair", "y");
    keys.SetKey("rid", static_cast<int>(FP_SIGN));
    keys.SetKey("iid", static_cast<int>(FP_NO_OP));
    return keys.String();
}

std::string convertReverseSignReal()
{
    KeyString keys;
    keys.SetKey("pair", "y");
    keys.SetKey("rid", static_cast<int>(FP_REVERSE_SIGN));
    keys.SetKey("iid", static_cast<int>(FP_NO_OP));
    return keys.String();
}

std::string convertUnsignImaginary()
{
    std::string transform("pair=y");
    transform += ",rid=" + intToString(static_cast<int>(FP_NO_OP));
    transform += ",iid=" + intToString(static_cast<int>(FP_UNSIGN));
    return transform;
}

std::string convertSignImaginary()
{
    KeyString keys;
    keys.SetKey("pair","y");
    keys.SetKey("rid", static_cast<int>(FP_NO_OP));
    keys.SetKey("iid", static_cast<int>(FP_SIGN));
    return keys.String();
}

std::string convertReverseSignImaginary()
{
    KeyString keys;
    keys.SetKey("pair","y");
    keys.SetKey("rid", static_cast<int>(FP_NO_OP));
    keys.SetKey("iid", static_cast<int>(FP_REVERSE_SIGN));
    return keys.String();
}

std::string convertCircleTransform(TRANSFORM t, long double size)
{
    COMPLEX_FUNCTION_PARAMETER p;
    switch (t)
    {
    default:
    case T_CIRCLE_IN: p = CFP_CIRCLE_FOLD_IN; break;
    case T_CIRCLE_OUT: p = CFP_CIRCLE_FOLD_OUT; break;
    case T_CIRCLE_REFLECT: p = CFP_CIRCLE_REFLECT; break;
    case T_INVERSE_FOLD_IN: p = CFP_INVERSE_FOLD_IN; break;
    case T_INVERSE_FOLD_OUT: p = CFP_INVERSE_FOLD_OUT; break;
    case T_INVERSE_REFLECT: p = CFP_INVERSE_REFLECT; break;
    }
    KeyString keys;
    keys.SetKey("pair", "n");
    keys.SetKey("id", static_cast<int>(p));
    keys.SetKey("size", longdoubleToString(size));
    return keys.String();
}

std::string convertTopRight()
{
    KeyString keys;
    keys.SetKey("pair", "y");
    keys.SetKey("rid", static_cast<int>(FP_UNSIGN));
    keys.SetKey("iid", static_cast<int>(FP_UNSIGN));
    return keys.String();
}

std::string convertBottomRight()
{
    KeyString keys;
    keys.SetKey("pair", "y");
    keys.SetKey("rid", static_cast<int>(FP_UNSIGN));
    keys.SetKey("iid", static_cast<int>(FP_SIGN));
    return keys.String();
}

std::string convertTopLeft()
{
    KeyString keys;
    keys.SetKey("pair", "y");
    keys.SetKey("rid", static_cast<int>(FP_SIGN));
    keys.SetKey("iid", static_cast<int>(FP_UNSIGN));
    return keys.String();
}

std::string convertBottomLeft()
{
    KeyString keys;
    keys.SetKey("pair", "y");
    keys.SetKey("rid", static_cast<int>(FP_SIGN));
    keys.SetKey("iid", static_cast<int>(FP_SIGN));
    return keys.String();
}

std::string convertPower(long double re, long double im)
{
    KeyString keys;
    keys.SetKey("pair", "n");
    keys.SetKey("id", static_cast<int>(CFP_POWER));
    keys.SetKey("r", re);
    keys.SetKey("i", im);
    return keys.String();
}

std::string convertExp()
{
    KeyString keys;
    keys.SetKey("pair","n");
    keys.SetKey("id", static_cast<int>(CFP_EXP));
    return keys.String();
}

std::string convertLog()
{
    KeyString keys;
    keys.SetKey("pair","n");
    keys.SetKey("id", static_cast<int>(CFP_LOG));
    return keys.String();
}

std::string defaultValue(FUNCTION_PARAMETER p)
{
    std::string str;
    if ((p == FP_ADD) || (p == FP_NUMBER))
    {
        str = "0";
    }
    else if (p == FP_SCALE)
    {
        str = "1";
    }
    else if (p == FP_POWER)
    {
        str = "2";
    }
    return str;
}

std::string abbreviate(const std::string& s)
{
    std::string str(s);
    if (s.length() > 10)
    {
        str = s.substr(0, 10);
        str += "...";
    }
    return str;
}

std::string defaultComplexFunctionValues(COMPLEX_FUNCTION_PARAMETER id)
{
    KeyString keys;
    keys.SetKey("pair", "n");
    keys.SetKey("id", static_cast<int>(id));
    if (hasParameter(id))
    {
        StringComplex cp;
        switch (id)
        {
        case CFP_POWER: cp = StringComplex("2", "0"); break;
        case CFP_BCP: 
        case CFP_BCP2: cp = StringComplex("0", "1"); break;
        case CFP_MULTIPLY: cp = StringComplex("1", "0"); break;
        default: break;
        }
        keys.SetKey("r", cp.r);
        keys.SetKey("i", cp.i);
    }
    else
    {
        if (hasSize(id))
        {
             keys.SetKey("size", "1");
        }
        else if (hasRotation(id))
        {
            keys.SetKey("rotation", "0");
        }
    }
    return keys.String();
}

QString fractalTypeToString(FRACTAL_TYPE ft)
{
    QString name("Unknown");
    switch (ft)
    {
    default: break;
    case F_MANDELBROT: name = "Mandelbrot"; break;
    case F_QUADRATIC: name = "Quadratic"; break;
    case F_CUBIC: name = "Cubic"; break;
    case F_ALMOST_CUBIC: name = "Almost Cubic"; break;
    case F_SINGLE_FUNCTION: name = "Single Function"; break;
    case F_ZCPAC: name = "Zcpac"; break;
    case F_C_POWER_Z: name = "C power Z"; break;
    case F_2F_PRODUCT: name = "Two Function Product"; break;
    case F_COMBINATION: name = "Combination"; break;
    case F_BIOMORPH_1: name = "Biomorph 1"; break;
    case F_BIOMORPH_2: name = "Biomorph 2"; break;
    case F_BIOMORPH_3: name = "Biomorph 3"; break;
    case F_BIOMORPH_4: name = "Biomorph 4"; break;
    case F_BIOMORPH_5: name = "Biomorph 5"; break;
    case F_NOVA: name = "Generalised Nova"; break;
    case F_NOVA_1: name = "Nova 1"; break;
    case F_NOVA_2: name = "Nova 2"; break;
    case F_QUARTIC: name = "Quartic"; break;
    case F_QUINTIC: name = "Quintic"; break;
    case F_MAGNET: name = "Magnet Model 1"; break;
    case F_MAGNET_2: name = "Magnet Model 2"; break;
    case F_SQRT_CP: name = "Sqrt of Complex Power"; break;
    case F_COMPASSES: name = "Compasses"; break;
    case F_PICKOVER_POPCORN_4F: name = "Pickover Popcorn 4F"; break;
    case F_PICKOVER_POPCORN_6F: name = "Pickover Popcorn 6F"; break;
    case F_COMBINATION_2: name = "Combination 2"; break;
    case F_COMBINATION_3: name = "Combination 3"; break;
    case F_UNNAMED: name = "Unnamed"; break;
    case F_UNNAMED_2: name = "Unnamed 2"; break;
    case F_TZACCP: name = "Tzaccp"; break;
    case F_ZACCP: name = "Zaccp"; break;
    case F_CCZCPACZCP: name = "Cczcpaczcp"; break;
    case F_FZCPAC: name = "Fzcpac"; break;
    case F_FTZCPAC: name = "Ftzcpac"; break;
    case F_TZCPAC: name = "Tzcpac"; break;
    case F_MALLARD: name = "Mallard"; break;
    case F_TMALLARD: name = "T-Mallard"; break;
    case F_LYAPUNOV: name = "Lyapunov"; break;
    case F_ONION_4F: name = "Onion 4F"; break;
    case F_SINGLE_3F_ONION: name = "Single 3F Onion"; break;
    case F_DOUBLE_3F_ONION_M: name = "Double 3F Onion M"; break;
    case F_DOUBLE_3F_ONION_D: name = "Double 3F Onion D"; break;
    case F_ZCPTANZ: name = "ZcpTanz"; break;
    case F_C2MFCZAC: name = "C2mfczac"; break;
    case F_C2DFCZAC: name = "C2dfczac"; break;
    case F_Z_POWER_TANCZ_AC: name = "ZpowerTanczac"; break;
    case F_RN_MANDELBROT: name = "Real Number Mandelbrot"; break;
    case F_ZAZBCGD: name = "Zazbcgd"; break;
    case F_HYBRID: name = "Hybrid"; break;
    case F_ZDUCCPAC: name = "Zduccpac"; break;
    case F_M3: name = "Mandelbrot M03"; break;
    case F_M4: name = "Mandelbrot M04"; break;
    case F_M5: name = "Mandelbrot M05"; break;
    case F_M6: name = "Mandelbrot M06"; break;
    case F_M7: name = "Mandelbrot M07"; break;
    case F_M8: name = "Mandelbrot M08"; break;
    case F_M9: name = "Mandelbrot M09"; break;
    case F_M10: name = "Mandelbrot M10"; break;
    case F_ATTRACTORS: name = "Attractors"; break;
    case F_GENERAL_MIXTURE: name = "Generalised Mixture"; break;
    case F_MIXTURE: name = "Mixture"; break;
    case F_MIXTURE_2: name = "Mixture 2"; break;
    case F_MIXTURE_3: name = "Mixture 3"; break;
    case F_MIXTURE_4: name = "Mixture 4"; break;
    case F_PR_MANDELBROT_2: name = "PR Mandelbrot 2"; break;
    case F_PR_MANDELBROT_3: name = "PR Mandelbrot 3"; break;
    case F_PR_SINGLE_FUNCTION_2: name = "PR Single Function 2"; break;
    case F_HOP: name = "Hop"; break;
    case F_QUADRUP_2: name = "Quadrup 2"; break;
    case F_THREEPLY: name = "Threeply"; break;
    case F_THREEPLY_2: name = "Threeply 2"; break;
    case F_CHIP: name = "Chip"; break;
    case F_GUMOWSKI_MIRA: name = "Gumowski-Mira"; break;
    case F_ATTRACTORS_SO: name = "Attractors SO"; break;
    case F_HOP_SO: name = "Hop SO"; break;
    case F_QUADRUP_2_SO: name = "Quadrup 2 SO"; break;
    case F_THREEPLY_SO: name = "Threeply SO"; break;
    case F_THREEPLY_2_SO: name = "Threeply 2 SO"; break;
    case F_CHIP_SO: name = "Chip SO"; break;
    case F_GUMOWSKI_MIRA_SO: name = "Gumowski-Mira SO"; break;
    case F_HEXIC: name = "Hexic"; break;
    case F_HEPTIC: name = "Heptic"; break;
    case F_MANDELBROT_DIVISION: name = "Mandelbrot Division"; break;
    case F_OCTIC: name = "Octic"; break;
    }
    return name;
}

QString addExtension(const QString& path, const QString& extension)
{
    // This method ensures that the file has the appropriate extension
    bool add = true;
    QString str = path;
    QString home = QDir::homePath();
    auto length = path.length() - (home.length() + 1); // length of home doesn't include the separating /
    QString last = path.right(1);
    if (length > 4)
    {
        QString ext = path.right(4);
        add = (extension.toUpper() != ext.toUpper());
    }
    if (add)
    {
        if (last != ".")
        {
            str += extension;
        }
        else
        {
            str += extension.mid(1);
        }
    }
    return str;
}

QString name_only(const QString& path)
{
    int pos = path.lastIndexOf('/');
    return (pos == -1 ? path : path.mid(pos + 1));
}

int convertFromNetworkFormat32(unsigned char *data)
{
    int value = 0;
    value += (static_cast<int>(data[0]) & 0x000000ff);
    value = value << 8;
    value += (static_cast<int>(data[1]) & 0x000000ff);
    value = value << 8;
    value += (static_cast<int>(data[2]) & 0x000000ff);
    value = value << 8;
    value += (static_cast<int>(data[3]) & 0x000000ff);
    return value;
}

bool isSingleOrbit(FRACTAL_TYPE ft)
{
    switch (ft)
    {
    default:
        return false;
    case F_ATTRACTORS_SO:
    case F_HOP_SO:
    case F_QUADRUP_2_SO:
    case F_THREEPLY_SO:
    case F_THREEPLY_2_SO:
    case F_CHIP_SO:
    case F_GUMOWSKI_MIRA_SO:
        return true;
    }
}

bool inFormulaTransforms(FRACTAL_TYPE ft)
{
        switch (ft)
    {
    default:
        return false;
    case F_NOVA:
    case F_NOVA_1:
    case F_NOVA_2:
    case F_FTZCPAC:
    case F_HYBRID:
    case F_TMALLARD:
    case F_TZACCP:
    case F_TZCPAC:
        return true;
    }
}
