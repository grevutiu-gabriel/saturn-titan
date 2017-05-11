//
// File:   OptionComboboxes.cc
// Author: M.R.Eggleston
//
// Created on 24 May 2011, 14:56
//

#include <iostream>
#include "OptionComboboxes.h"

ColouringCombobox::ColouringCombobox(QWidget* parent)
: QComboBox(parent)
{
    addItem("Outer");
    addItem("Inner");
}

void ColouringCombobox::setValue(COLOURING value)
{
    setCurrentIndex(value == OUTER ? 0 : 1);
}

LyapunovColouringCombobox::LyapunovColouringCombobox(QWidget* parent)
: QComboBox(parent)
{
    addItem("Negative");
    addItem("Positive");
}

LyapunovMethodCombobox::LyapunovMethodCombobox(QWidget* parent)
: QComboBox(parent)
{
    addItem("One Colour");
    addItem("Multi-Colour");
}

MethodCombobox::MethodCombobox(QWidget* parent)
: QComboBox(parent)
{
    addItem("Fixed Colour");
    addItem("Iteration");
    addItem("Final Magnitude");
    addItem("Magnitude");
    addItem("Change in Magnitude");
    addItem("Final Angle");
    addItem("Angle");
    addItem("Change in angle");
    addItem("Gaussian Integer");
    addItem("Trap Distance");
    addItem("Change in Trap Distance");
    addItem("Ratio");
    addItem("Change of Ratio");
}

METHOD MethodCombobox::getValue()
{
    return static_cast<METHOD>(currentIndex());
}

void MethodCombobox::setValue(METHOD value)
{
    setCurrentIndex(static_cast<int>(value));
}

GaussianTypeCombobox::GaussianTypeCombobox(QWidget* parent)
: QComboBox(parent)
{
    addItem("Round");
    addItem("Ceiling");
    addItem("Floor");
    addItem("Truncate");
}

GAUSSIAN_TYPE GaussianTypeCombobox::getValue()
{
    return static_cast<GAUSSIAN_TYPE>(currentIndex());
}

void GaussianTypeCombobox::setValue(GAUSSIAN_TYPE value)
{
    setCurrentIndex(static_cast<int>(value));
}

GaussianMethodCombobox::GaussianMethodCombobox(QWidget* parent)
: QComboBox(parent)
{
    addItem("Minimum Distance");
    addItem("Iteration @ Minimum Distance");
    addItem("Angle @ Minimum Distance");
    addItem("Maximum Distance");
    addItem("Iteration @ Maximum Distance");
    addItem("Angle @ Maximum Distance");
    addItem("Average Distance");
    addItem("Minimum Angle");
    addItem("Average Angle");
    addItem("Maximum Angle");
    addItem("Max. Distance/Min. Distance");
    addItem("Range");
    addItem("Variance");
    addItem("Standard Deviation");
    addItem("Coefficient of Variation");
}

GAUSSIAN_METHOD GaussianMethodCombobox::getValue()
{
    return static_cast<GAUSSIAN_METHOD>(currentIndex());
}

void GaussianMethodCombobox::setValue(GAUSSIAN_METHOD value)
{
    setCurrentIndex(static_cast<int>(value));
}

FinalMagnitudeTypeCombobox::FinalMagnitudeTypeCombobox(QWidget* parent)
: QComboBox(parent)
{
    addItem("norm(z)");
    addItem("smaller of real(z), imag(z)");
    addItem("greater of real(z), imag(z)");
    addItem("real(z)");
    addItem("abs(real(z)");
    addItem("imag(z)");
    addItem("abs(imag(z))");
    addItem("real(z)+imag(z)");
    addItem("abs(real(z)+imag(z))");
    addItem("real(z)*imag(z)");
    addItem("abs(real(z)*imag(z))");
}

FINAL_MAGNITUDE_TYPE FinalMagnitudeTypeCombobox::getValue()
{
    return static_cast<FINAL_MAGNITUDE_TYPE>(currentIndex());
}

void FinalMagnitudeTypeCombobox::setValue(FINAL_MAGNITUDE_TYPE value)
{
    setCurrentIndex(static_cast<int>(value));
}

StatisticsOptionTypeCombobox::StatisticsOptionTypeCombobox(QWidget* parent)
: QComboBox(parent)
{
    addItem("Minimum");
    addItem("Iteration @ Minimum");
    addItem("Maximum");
    addItem("Iteration @ Maximum");
    addItem("Range");
    addItem("Average");
    addItem("Variance");
    addItem("Standard Deviation");
    addItem("Coefficient of Variation");
    addItem("Fractal Dimension");
    addItem("Exponential Sum");
    addItem("Exponential Inverse Change Sum");
}

STATISTICS_OPTION_TYPE StatisticsOptionTypeCombobox::getValue()
{
    return static_cast<STATISTICS_OPTION_TYPE>(currentIndex());
}

void StatisticsOptionTypeCombobox::setValue(STATISTICS_OPTION_TYPE value)
{
    setCurrentIndex(static_cast<int>(value));
}

OrbitColourCombobox::OrbitColourCombobox(QWidget* parent)
: QComboBox(parent)
{
    addItem("Accumulation");
    addItem("Square Root");
    addItem("Average");
    addItem("Logarithm");
}

OrbitTrapTypeCombobox::OrbitTrapTypeCombobox(QWidget* parent)
: QComboBox(parent)
{
    addItem("Point");
    addItem("4 Points");
    addItem("Line");
    addItem("Cross");
    addItem("Square");
    addItem("Circle");
    addItem("Triangle");
    addItem("Triform");
    addItem("Asterisk");
    addItem("Circle Line");
    addItem("Circle Cross");
    addItem("Circle Triform");
    addItem("Two Quarter Circles");
    addItem("Circle Triangle");
    addItem("Triangle Circle");
    addItem("Circle Square");
    addItem("Square Circle");
    addItem("Octothorpe");
    addItem("Running Track");
    addItem("Pinch");
    addItem("Steiner Chain");
    m_values.push_back(OrbitTrap::POINT);
    m_values.push_back(OrbitTrap::FOUR_POINTS);
    m_values.push_back(OrbitTrap::LINE);
    m_values.push_back(OrbitTrap::CROSS);
    m_values.push_back(OrbitTrap::SQUARE);
    m_values.push_back(OrbitTrap::CIRCLE);
    m_values.push_back(OrbitTrap::TRIANGLE);
    m_values.push_back(OrbitTrap::TRIFORM);
    m_values.push_back(OrbitTrap::ASTERISK);
    m_values.push_back(OrbitTrap::CIRCLE_LINE);
    m_values.push_back(OrbitTrap::CIRCLE_CROSS);
    m_values.push_back(OrbitTrap::CIRCLE_TRIFORM);
    m_values.push_back(OrbitTrap::QUARTER_CIRCLES);
    m_values.push_back(OrbitTrap::CIRCLE_TRIANGLE);
    m_values.push_back(OrbitTrap::TRIANGLE_CIRCLE);
    m_values.push_back(OrbitTrap::CIRCLE_SQUARE);
    m_values.push_back(OrbitTrap::SQUARE_CIRCLE);
    m_values.push_back(OrbitTrap::OCTOTHORPE);
    m_values.push_back(OrbitTrap::RUNNING_TRACK);
    m_values.push_back(OrbitTrap::PINCH);
    m_values.push_back(OrbitTrap::STEINER_CHAIN);
}

OrbitTrap::TRAP_TYPE OrbitTrapTypeCombobox::getValue()
{
    return m_values[currentIndex()];
}

void OrbitTrapTypeCombobox::setValue(OrbitTrap::TRAP_TYPE value)
{
    bool found = false;
    int ivalue = 0;
    for (auto it = m_values.begin(); it != m_values.end(); it++)
    {
        if (*it == value)
        {
            found = true;
            break;
        }
        ivalue++;
    };
    setCurrentIndex(found ? ivalue : 0);
}

RatioPartTypeCombobox::RatioPartTypeCombobox(QWidget* parent)
: QComboBox(parent)
{
    addItem("Smaller of real(z), imag(z)");
    addItem("Larger of real(z), imag(z)");
    addItem("abs(real(z))");
    addItem("abs(imag(z))");
    addItem("abs(real(z) + imag(z))");
    addItem("abs(real(z) - imag(z))");
    addItem("abs(real(z)) + abs(imag(z))");
    addItem("abs(abs(real(z)) - abs(imag(z)))");
    addItem("abs(real(z)*imag(z))");
    addItem("abs(z)");
    addItem("norm(z)");
}

RATIO_PART_TYPE RatioPartTypeCombobox::getValue()
{
    return static_cast<RATIO_PART_TYPE>(currentIndex());
}

void RatioPartTypeCombobox::setValue(RATIO_PART_TYPE value)
{
    setCurrentIndex(static_cast<int>(value));
}


DivergeBailoutConditionCombobox::DivergeBailoutConditionCombobox(QWidget* parent)
: QComboBox(parent)
{
    addItem("No Bailout");
    addItem("abs(z)");
    addItem("norm(z)");
    addItem("imag(z)");
    addItem("imag(z) squared");
    addItem("real(z)");
    addItem("real(z) squared");
    addItem("abs(real(z)*imag(z))");
    addItem("abs(real(z)) + abs(imag(z))");
    addItem("real(z) + imag(z)");
    addItem("abs(real(z) + image(z))");
    addItem("max(real(z), imag(z)) squared");
    addItem("min(real(z), imag(z)) squared");
    addItem("abs(real(z) - imag(z))");
}

BAILOUT DivergeBailoutConditionCombobox::getValue()
{
    return static_cast<BAILOUT>(currentIndex());
}

void DivergeBailoutConditionCombobox::setValue(BAILOUT value)
{
    setCurrentIndex(static_cast<int>(value));
}

ConvergeBailoutConditionCombobox::ConvergeBailoutConditionCombobox(QWidget* parent)
: QComboBox(parent)
{
    addItem("No Bailout");
    addItem(QString::fromUtf8("abs(Δz)"));
    addItem(QString::fromUtf8("norm(Δz)"));
    addItem(QString::fromUtf8("imag(Δz)"));
    addItem(QString::fromUtf8("imag(Δz) squared"));
    addItem(QString::fromUtf8("real(Δz)"));
    addItem(QString::fromUtf8("real(Δz) squared"));
    addItem(QString::fromUtf8("abs(real(Δz)*imag(Δz))"));
    addItem(QString::fromUtf8("abs(real(Δz)) + abs(imag(Δz))"));
    addItem(QString::fromUtf8("real(Δz) + imag(Δz)"));
    addItem(QString::fromUtf8("abs(real(Δz) + image(Δz))"));
    addItem(QString::fromUtf8("max(real(Δz), imag(Δz)) squared"));
    addItem(QString::fromUtf8("min(real(Δz), imag(Δz)) squared"));
    addItem(QString::fromUtf8("abs(real(Δz) - imag(Δz))"));
}

BAILOUT ConvergeBailoutConditionCombobox::getValue()
{
    return static_cast<BAILOUT>(currentIndex());
}

void ConvergeBailoutConditionCombobox::setValue(BAILOUT value)
{
    setCurrentIndex(static_cast<int>(value));
}

ComponentComparisonsImagCombobox::ComponentComparisonsImagCombobox(QWidget* parent)
: QComboBox(parent)
{
    addItem("imag(z) > lmit");
    addItem("abs(imag(z)) > limit");
    addItem("imag(z) < limit");
    addItem("abs(imag(z)) < limit");
}

COMPONENT_COMPARISONS_IMAG ComponentComparisonsImagCombobox::getValue()
{
    return static_cast<COMPONENT_COMPARISONS_IMAG>(currentIndex());
}

void ComponentComparisonsImagCombobox::setValue(COMPONENT_COMPARISONS_IMAG value)
{
    setCurrentIndex(static_cast<int>(value));
}

ComponentComparisonsRealCombobox::ComponentComparisonsRealCombobox(QWidget* parent)
: QComboBox(parent)
{
    addItem("real(z) > lmit");
    addItem("abs(real(z)) > limit");
    addItem("real(z) < limit");
    addItem("abs(real(z) < limit");
}

COMPONENT_COMPARISONS_REAL ComponentComparisonsRealCombobox::getValue()
{
    return static_cast<COMPONENT_COMPARISONS_REAL>(currentIndex());
}

void ComponentComparisonsRealCombobox::setValue(COMPONENT_COMPARISONS_REAL value)
{
    setCurrentIndex(static_cast<int>(value));
}

CombinationCombobox::CombinationCombobox(QWidget* parent)
: QComboBox(parent)
{
    addItem("AND");
    addItem("OR");
    addItem("XOR");
}

COMBINATION CombinationCombobox::getValue()
{
    return static_cast<COMBINATION>(currentIndex());
}

void CombinationCombobox::setValue(COMBINATION value)
{
    setCurrentIndex(static_cast<int>(value));
}


FunctionParameterCombobox::FunctionParameterCombobox(QWidget* parent)
: QComboBox(parent)
{
    addItem("no-op");
    addItem("+/-");
    addItem("abs");
    addItem("-abs");
    addItem("add");
    addItem("acos(fraction())");
    addItem("asin(fractaion())");
    addItem("atan");
    addItem("ceiling");
    addItem("cos");
    addItem("cosec");
    addItem("cosh");
    addItem("cotan");
    addItem("exp");
    addItem("floor");
    addItem("log(abs())");
    addItem("number");
    addItem("power");
    addItem("round");
    addItem("scale");
    addItem("sec");
    addItem("sin");
    addItem("sinh");
    addItem("tan");
    addItem("tanh");
    addItem("trunc");
}

FUNCTION_PARAMETER FunctionParameterCombobox::getValue()
{
    return static_cast<FUNCTION_PARAMETER>(currentIndex());
}

void FunctionParameterCombobox::setValue(FUNCTION_PARAMETER value)
{
    setCurrentIndex(static_cast<int>(value));
}

ComplexFunctionParameterCombobox::ComplexFunctionParameterCombobox(QWidget* parent)
: QComboBox(parent)
{
    addItem("no-op");
    addItem("acos");
    addItem("acosh");
    addItem("asin");
    addItem("asinh");
    addItem("atan");
    addItem("atanh");
    addItem("bcp");
    addItem("bcp2");
    addItem("circle fold in");
    addItem("circle fold out");
    addItem("circle reflect");
    addItem("cos");
    addItem("cosec");
    addItem("cosh");
    addItem("cotan");
    addItem("exp");
    addItem("inverse fold in");
    addItem("inverse fold out");
    addItem("inverse reflect");
    addItem("log");
    addItem("multiply");
    addItem("power");
    addItem("product");
    addItem("rotation");
    addItem("sec");
    addItem("sin");
    addItem("sinh");
    addItem("tan");
    addItem("tanh");
}

COMPLEX_FUNCTION_PARAMETER ComplexFunctionParameterCombobox::getValue()
{
    return static_cast<COMPLEX_FUNCTION_PARAMETER>(currentIndex());
}

void ComplexFunctionParameterCombobox::setValue(COMPLEX_FUNCTION_PARAMETER value)
{
    setCurrentIndex(static_cast<int>(value));
}


OrbitPlotCombobox::OrbitPlotCombobox(QWidget* parent)
: QComboBox(parent)
{
    addItem("All");
    addItem("Escaped");
    addItem("Captive");
//    set_active(0);
}

ORBIT_PLOTS OrbitPlotCombobox::getValue()
{
    return static_cast<ORBIT_PLOTS>(currentIndex());
}

void OrbitPlotCombobox::setValue(ORBIT_PLOTS value)
{
    setCurrentIndex(static_cast<int>(value));
}

ExportCombobox::ExportCombobox(QWidget* parent)
: QComboBox(parent)
{
    addItem(".scm");
    addItem(".ugr");
}

EXPORT_FILES ExportCombobox::getValue()
{
    return static_cast<EXPORT_FILES>(currentIndex());
}

void ExportCombobox::setValue(EXPORT_FILES value)
{
    setCurrentIndex(static_cast<int>(value));
}

NavigationCombobox::NavigationCombobox(QWidget* parent)
: QComboBox(parent)
{
    addItem("Quick Zoom");
    addItem("Zoom In");
    addItem("Centre In");
    addItem("Centre Out");
    addItem("Zoom Off");
}
    
NAVIGATION NavigationCombobox::getValue()
{
    return static_cast<NAVIGATION>(currentIndex());
}

void NavigationCombobox::setValue(NAVIGATION value)
{
    setCurrentIndex(static_cast<int>(value));
}

ColourMapEditComboBox::ColourMapEditComboBox(QWidget* parent)
: QComboBox(parent)
{
    addItem("Auto");
    addItem("Manual");
    addItem("Component");
}

COLOUR_MAP_EDIT ColourMapEditComboBox::getValue()
{
    return static_cast<COLOUR_MAP_EDIT>(currentIndex());
}

void ColourMapEditComboBox::setValue(COLOUR_MAP_EDIT value)
{
    setCurrentIndex(static_cast<int>(value));
}

WaveComboBox::WaveComboBox(QWidget* parent)
: QComboBox(parent)
{
    addItem("Sine");
    addItem("Saw");
    addItem("Parabolic");
}

Waveform::WAVE WaveComboBox::getValue()
{
    return static_cast<Waveform::WAVE>(currentIndex());
}

void WaveComboBox::setValue(Waveform::WAVE value)
{
    setCurrentIndex(static_cast<int>(value));
}

ComponentOrderComboBox::ComponentOrderComboBox(QWidget* parent)
: QComboBox(parent)
{
    addItem("RGB");
    addItem("RBG");
    addItem("GRB");
    addItem("GBR");
    addItem("BRG");
    addItem("BGR");
}

COMPONENT_ORDER ComponentOrderComboBox::getValue()
{
    return static_cast<COMPONENT_ORDER>(currentIndex());
}

void ComponentOrderComboBox::setValue(COMPONENT_ORDER value)
{
    setCurrentIndex(static_cast<int>(value));
}
