// 
// File:   Utilities.h
// Author: M.R.Eggleston
//
// Created on 03 January 2012, 19:49
//

#pragma once

#include "ldcomplex.h"
#include "mpcomplex.h"
#include "ColourMap.h"
#include "TypesAndConstants.h"

std::string intToString(int value);
std::string uintToString(unsigned int value);
std::string ulongToString(unsigned long value);
std::string longdoubleToString(long double value);
QString longdoubleToQString(long double value);
std::string longdoubleToString(long double value, bool fixed, int precision);
QString complexNumberToString(const StringComplex &z);
QString complexFunctionToString(const std::string& str);
QString functionToString(const std::string& str);
QString fractalTypeToString(FRACTAL_TYPE ft);

QColor stringToColour(const std::string& str);
unsigned int stringToUint(const std::string& str);
int stringToInt(const std::string& str);
long double stringToLongDouble(const std::string& str);
LongComplex stdStringToLongComplex(const std::string& s1, const std::string& s2);
LongComplex stringComplexToLongComplex(const StringComplex& z);
MpComplex stringComplexToMpComplex(const StringComplex& z, int precision);

long double trunc(long double value); // C++11 std::trunc not available in MS C++ yet...

std::string convert(OLD_FUNCTION_PARAMETER fp);
QString functionAsString(FUNCTION_PARAMETER fp);
QString complexFunctionAsString(COMPLEX_FUNCTION_PARAMETER fp);
std::string defaultComplexFunctionValues(COMPLEX_FUNCTION_PARAMETER fp);
std::string convert(OLD_COMPLEX_FUNCTION_PARAMETER cfp);
std::string convert(TRANSFORM t);
FRACTAL_TYPE convert(OLD_FRACTAL_TYPE ft);

bool hasParameter(COMPLEX_FUNCTION_PARAMETER p);
bool hasRotation(COMPLEX_FUNCTION_PARAMETER p);
bool hasSize(COMPLEX_FUNCTION_PARAMETER p);
bool hasParameter(FUNCTION_PARAMETER p);

std::string defaultValue(FUNCTION_PARAMETER p);

std::string abbreviate(const std::string& s);

int determinePrecision(const StringComplex& x, const std::string& width, int hpixels, int vpixels);

std::string convertTranslation(long double r, long double i);
std::string convertScale(long double re, long double im);
std::string convertRotation(int rotation);
std::string convertUnsignReal();
std::string convertSignReal();
std::string convertReverseSignReal();
std::string convertUnsignImaginary();
std::string convertSignImaginary();
std::string convertReverseSignImaginary();
std::string convertCircleTransform(TRANSFORM t, long double size);
std::string convertTopRight();
std::string convertBottomRight();
std::string convertTopLeft();
std::string convertBottomLeft();
std::string convertPower(long double re, long double im);
std::string convertExp();
std::string convertLog();

QString addExtension(const QString& path, const QString& extension);
QString name_only(const QString& name);

// Qt doesn't successfully load PNG metadata on OS X and Windows, the following
// utilities are required to extract the data.

// Conversion from network format 4 byte integer into host format used
// instead of ntohl to avoid header location problems
int convertFromNetworkFormat32(unsigned char *data);

bool isSingleOrbit(FRACTAL_TYPE ft);
bool inFormulaTransforms(FRACTAL_TYPE ft);