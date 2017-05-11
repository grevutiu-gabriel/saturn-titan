//
// File:   FractalsConfig.cc
// Author: M.R.Eggleston
//
// Created on 16 November 2009, 11:01
//
// Renamed 19th April 2012, formerly FractalConfig.cc

#include <iostream>
#include <limits>
#include "Config.h"
#include "Utilities.h"
#include "FractalsConfig.h"
#include "KeyString.h"
#include "Utilities.h"
#include "TypesAndConstants.h"

QString config_file("~/.saturn/config");

FractalsConfig::UintMap FractalsConfig::m_number_of_complex_parameters;
FractalsConfig::StringComplexParameterMapMap FractalsConfig::m_complex_parameters;
FractalsConfig::StringComplexParameterMapMap FractalsConfig::m_default_complex_parameters;
FractalsConfig::UintMap FractalsConfig::m_number_of_parameters;
FractalsConfig::ParameterMapMap FractalsConfig::m_parameters;
FractalsConfig::ParameterMapMap FractalsConfig::m_default_parameters;
FractalsConfig::QStringMap FractalsConfig::m_formula;
FractalsConfig::QStringMap FractalsConfig::m_name;
FractalsConfig::StringComplexMap FractalsConfig::m_scentre;
FractalsConfig::StdStringMap FractalsConfig::m_swidth;
FractalsConfig::StringComplexMap FractalsConfig::m_ccentre;
FractalsConfig::StdStringMap FractalsConfig::m_cwidth;
FractalsConfig::StringComplexMap FractalsConfig::m_default_scentre;
FractalsConfig::StdStringMap FractalsConfig::m_default_swidth;
FractalsConfig::LongDoubleMap FractalsConfig::m_limit;
FractalsConfig::QStringMap FractalsConfig::m_colour_map[2];
FractalsConfig::UintMap FractalsConfig::m_red_offset[2];
FractalsConfig::UintMap FractalsConfig::m_green_offset[2];
FractalsConfig::UintMap FractalsConfig::m_blue_offset[2];
FractalsConfig::StdStringMap FractalsConfig::m_select;
FractalsConfig::LongDoubleMap FractalsConfig::m_select_limit;
FractalsConfig::StdStringMap FractalsConfig::m_method[2];
FractalsConfig::LongDoubleMap FractalsConfig::m_colour_scale[2];
FractalsConfig::InitialValueMap FractalsConfig::m_zero_initial_values;
FractalsConfig::InitialValueMap FractalsConfig::m_default_zero_initial_values;
FractalsConfig::IntMap FractalsConfig::m_max_iterations;
FractalsConfig::IntMap FractalsConfig::m_default_max_iterations;
FractalsConfig::UintMap FractalsConfig::m_iteration_step_size;
FractalsConfig::StringComplexMap FractalsConfig::m_z0;
FractalsConfig::StringComplexMap FractalsConfig::m_default_z0;
FractalsConfig::BoolMap FractalsConfig::m_smooth[2];
FractalsConfig::BoolMap FractalsConfig::m_abs_log[2];
FractalsConfig::IntMap FractalsConfig::m_srotation;
FractalsConfig::IntMap FractalsConfig::m_crotation;
std::string FractalsConfig::m_sequence = "AB";
long double FractalsConfig::m_width = 750.0L;
long double FractalsConfig::m_height = 500.0L;
unsigned int FractalsConfig::m_settling_cycles = 120;
unsigned int FractalsConfig::m_calculating_cycles = 600;
FractalsConfig::IntMap FractalsConfig::m_interval;
FractalsConfig::CharMap FractalsConfig::m_orbit_colour_type;
FractalsConfig::UintMap FractalsConfig::m_default_interval;
FractalsConfig::CharMap FractalsConfig::m_default_orbit_colour_type;
FractalsConfig::BailoutMap FractalsConfig::m_default_bailout;
FractalsConfig::BailoutMap FractalsConfig::m_bailout;
FractalsConfig::BoolMap FractalsConfig::m_converging;
FractalsConfig::StdStringMap FractalsConfig::m_transform_sequence;
FractalsConfig::TransformVectorMap FractalsConfig::m_cp_transforms;
FractalsConfig::TransformVectorVectorMap FractalsConfig::m_transforms;
FractalsConfig::FunctionParameterMapMap FractalsConfig::m_functions;
FractalsConfig::FunctionParameterMapMap FractalsConfig::m_default_functions;
FractalsConfig::ComplexFunctionParameterMapMap FractalsConfig::m_complex_functions;
FractalsConfig::ComplexFunctionParameterMapMap FractalsConfig::m_default_complex_functions;
FractalsConfig::UintMap FractalsConfig::m_number_of_function_parameters;
FractalsConfig::UintMap FractalsConfig::m_number_of_complex_function_parameters;
FractalsConfig::BoolMap FractalsConfig::m_orbit_plotting;
FractalsConfig::QStringMap FractalsConfig::m_orbit_colour;
FractalsConfig::UintMap FractalsConfig::m_red_orbit_offset;
FractalsConfig::UintMap FractalsConfig::m_green_orbit_offset;
FractalsConfig::UintMap FractalsConfig::m_blue_orbit_offset;
FractalsConfig::IntMap FractalsConfig::m_calculating_area;
FractalsConfig::LongDoubleMap FractalsConfig::m_orbit_scale;
FractalsConfig::OrbitPlotsMap FractalsConfig::m_orbit_plots;
FractalsConfig::IntMap FractalsConfig::m_start_orbit_iteration;
FractalsConfig::BoolMap FractalsConfig::m_quick;
FractalsConfig::ComponentOrderMap FractalsConfig::m_order[2];
FractalsConfig::ComponentOrderMap FractalsConfig::m_orbit_order;
FractalsConfig::UintMap FractalsConfig::m_density;
FractalsConfig::BoolMap FractalsConfig::m_has_orbit_background;
FractalsConfig::QColorMap FractalsConfig::m_background_colour;
FractalsConfig::IntMap FractalsConfig::m_precision;

FractalConfig FractalsConfig::m_fractal;


FractalsConfig::FractalsConfig()
:
m_type(F_MANDELBROT),
m_index(0),
m_colour_maps(ColourMaps::instance())
{
    if (m_name.empty())
    {
        defineMandelbrot();
        defineQuadratic();
        defineCubic();
        defineAlmostCubic();
        defineSingleFunction();
        defineZcpac();
        defineTwoFunctionProduct();
        defineCpowerZ();
        defineUnnamed();
        defineZpowerTancz();
        defineCombination();
        defineTzaccp();
        defineBiomorph1();
        defineBiomorph2();
        defineBiomorph3();
        defineBiomorph4();
        defineBiomorph5();
        defineMagnet();
        defineMagnet2();
        defineZazbcgd();
        defineCombination2();
        defineNova();
        defineNova1();
        defineNova2();
        defineSqrtCP();
        defineUnnamed2();
        defineQuartic();
        defineQuintic();
        defineHexic();
        defineHeptic();
        defineOctic();
        defineZcpTanz();
        defineLyapunov();
        defineCompasses();
        defineRealNumberMandelbrot();
        defineHybrid();
        defineZduccpac();
        defineMallard();
        definePickoverPopcorn6Function();
        defineTzcpac();
        defineTmallard();
        defineFzcpac();
        defineFtzcpac();
        defineZaccp();
        definePickoverPopcorn4Function();
        defineCczcpazcp();
        defineOnion4F();
        defineCombination3();
        defineC2mfczac();
        defineC2dfczac();
        defineSingle3fOnion();
        defineDouble3fOnionM();
        defineDouble3fOnionD();
        defineM3();
        defineM4();
        defineM5();
        defineM6();
        defineM7();
        defineM8();
        defineM9();
        defineM10();
        defineAttractors();
        defineGeneralMixture();
        defineMixture();
        defineMixture2();
        defineMixture3();
        defineMixture4();
        definePrMandelbrot2();
        definePrMandelbrot3();
        definePrSingleFunction2();
        defineHop();
        defineQuadrup_2();
        defineThreeply();
        defineThreeply2();
        defineChip();
        defineGumowskiMira();
        defineAttractorsSO();
        defineHopSO();
        defineQuadrup_2_SO();
        defineThreeplySO();
        defineThreeply2_SO();
        defineChipSO();
        defineGumowskiMiraSO();
        defineMandelbrotDivision();
    }
}

void FractalsConfig::SetFractalType(FRACTAL_TYPE value)
{
    m_type = value;
}

void FractalsConfig::SetFractal(FractalConfig &f)
{
    setWidth(f.getWidth());
    setHeight(f.getHeight());
    SetFractalType(f.GetFractalType());
    setCentre(f.getImageCentre());
    setCurrentWidth(f.getImageWidth());
    setRotation(f.getRotation());
    auto starting_width = f.getStartingWidth();
    if (!starting_width.empty())
    {
        // If FractalConfig object was loaded from a seed file it won't
        // have starting location data.
        setStartingCentre(f.getStartingCentre());
        setStartingWidth(f.getStartingWidth());
        setStartingRotation(f.getStartingRotation());
    }
    setCalculatingArea(f.getArea());
    setBailout(f.getBailout());
    setLimit(f.getLimit());

    int parameters = getNumberOfComplexParameters();
    for (int i = 0; i < parameters; i++)
    {
        setComplexParameter(i, f.getComplexParameter(i), f.getComplexParameterType(i));
    }
    parameters = getNumberOfParameters();
    for (int i = 0; i < parameters; i++)
    {
        setParameter(i, f.getParameter(i));
    }
    parameters = getNumberOfFunctionParameters();
    for (int i = 0; i < parameters; i++)
    {
        setFunctionParameter(i, f.getFunctionParameter(i));
    }
    parameters = getNumberOfComplexFunctionParameters();
    for (int i = 0; i < parameters; i++)
    {
        setComplexFunctionParameter(i, f.getComplexFunctionParameter(i));
    }
    setInitialValues(f.getInitialZtype());
    setFixedInitialValue(f.getInitalZ());
    setOrbitPlotting(f.isOrbitPlotting());
    if (isOrbitPlotting() || isSingleOrbit())
    {
        if (isOrbitPlotting())
        {
            setStartOrbitIteration(f.getOmit());
            setOrbitPlots(f.getOrbitPlot());
            setDensity(f.getDensity());
        }
        setOrbitColourInterval(f.getOrbitColourInterval());
        setOrbitColourType(f.getOrbitColourType());
        setColourMap(f.getOrbitColourMap(), false);
        setOrbitScale(f.getOrbitScale());
        QString name = f.getOrbitColourMap();
        auto map = f.getColourMap(false);
        if (map.empty())
        {
            // We only have the map's name as the FractalConfig object
            // was created from a <fractal> child in the config file
            bool exists = m_colour_maps->nameExists(name);
            setColourMap(exists ? name : "Default");
        }
        else
        {
            // FractalConfig created from a seed file or an spf file
            setColourMap(m_colour_maps->setColours(name, map, true));
        }
        setRedOffset(f.getOrbitRedOffset());
        setGreenOffset(f.getOrbitGreenOffset());
        setBlueOffset(f.getOrbitBlueOffset());
        setOrbitBackground(f.getOrbitBackground());
        enableOrbitBackground(f.hasOrbitBackground());
        setComponentOrder(f.getComponentOrder(false));
    }
    else
    {
        setSelectLimit(f.getSelectLimit());
        setSelection(f.getSelection());
        for (int i = 0; i < 2; i++)
        {
            bool inner = (i == 1);
            setMethod(inner, f.getMethod(inner));
            QString name = f.getColourMapName(inner);
            auto map = f.getColourMap(inner);
            if (f.getMethod(inner)[0] != 'f')
            {
                if (map.empty())
                {
                    // We only have the map's name as the FractalConfig object
                    // was created from a <fractal> child in the config file
                    bool exists = m_colour_maps->nameExists(name);
                    setColourMap(exists ? name : "Default", inner);
                }
                else
                {
                    // FractalConfig created from a seed file or an spf file
                    setColourMap(m_colour_maps->setColours(name, map, true), inner);
                }
            }
            setColourScale(inner, f.getScale(inner));
            setSmooth(inner, f.getSmooth(inner));
            setAbsLog(inner, f.getAbsLog(inner));
            setRedOffset(f.getRedOffset(inner), inner);
            setGreenOffset(f.getGreenOffset(inner), inner);
            setBlueOffset(f.getBlueOffset(inner), inner);
            setComponentOrder(f.getComponentOrder(inner), inner);
        }
    }
    setMaxIterations(f.getMaxIterations());
    //
    if (m_type == F_LYAPUNOV)
    {
        setLyapunovSequence(f.getLyapunovSequence());
        setSettlingCycles(f.getSettlingCycles());
        setCalculatingCycles(f.getCalculatingCycles());
    }
    setTransformSequence(f.getTransformSequence());
    deleteTransforms();
    int transforms = f.getNumberOfComplexPlaneTransforms();
    for (int i = 0; i < transforms; i++)
    {
        addComplexPlaneTransform(f.getComplexPlaneTransform(i));
    }
    int sets = f.getNumberOfTransformSets();
    for (int j = 0; j < sets; j++)
    {
        TransformVector v;
        m_transforms[m_type].push_back(v);
        int transforms = f.getNumberOfTransforms(j);
        for (int i = 0; i < transforms; i++)
        {
            addTransform(j, f.getTransform(j, i));
        }
    }
    setPrecision(f.getPrecision());
}

FRACTAL_TYPE FractalsConfig::GetFractalType()
{
    return m_type;
}

void FractalsConfig::setComplexParameter(int i, const StringComplex &value, PARAMETER_TYPE type)
{
    ComplexParameter p = { value, type };
    m_complex_parameters[m_type][i] = p;
}

void FractalsConfig::setComplexParameterType(int i, PARAMETER_TYPE type)
{
    m_complex_parameters[m_type][i].type = type;
}

const StringComplex &FractalsConfig::getComplexParameter(int i)
{
    return m_complex_parameters[m_type][i].p;
}

PARAMETER_TYPE FractalsConfig::getComplexParameterType(int i)
{
    return m_complex_parameters[m_type][i].type;
}

void FractalsConfig::setParameter(int i, const std::string &value)
{
    m_parameters[m_type][i] = value;
}

const std::string &FractalsConfig::getParameter(int i)
{
    return m_parameters[m_type][i];
}

void FractalsConfig::setFunctionParameter(int index, const std::string &f)
{
    m_functions[m_type][index] = f;
}

std::string FractalsConfig::getFunctionParameter(int index)
{
    return m_functions[m_type][index];
}

void FractalsConfig::setComplexFunctionParameter(int index, const std::string &f)
{
    m_complex_functions[m_type][index] = f;
}

std::string FractalsConfig::getComplexFunctionParameter(int index)
{
    return m_complex_functions[m_type][index];
}


void FractalsConfig::resetFractalParameters()
{
    int modifiers;
    modifiers = m_number_of_complex_parameters[m_type];
    for (int i = 0; i < modifiers; i++)
    {
        m_complex_parameters[m_type][i] = m_default_complex_parameters[m_type][i];
    }
    modifiers = m_number_of_parameters[m_type];
    for (int i = 0; i < modifiers; i++)
    {
        m_parameters[m_type][i] = m_default_parameters[m_type][i];
    }
    modifiers = m_number_of_function_parameters[m_type];
    for (int i = 0; i < modifiers; i++)
    {
        m_functions[m_type][i] = m_default_functions[m_type][i];
    }
    modifiers = m_number_of_complex_function_parameters[m_type];
    for (int i = 0; i < modifiers; i++)
    {
        m_complex_functions[m_type][i] = m_default_complex_functions[m_type][i];
    }
    m_z0[m_type] = m_default_z0[m_type];
    m_zero_initial_values[m_type] = m_default_zero_initial_values[m_type];
}

void FractalsConfig::resetLyapunovParameters()
{
    m_sequence = "AB";
    m_settling_cycles = 120;
    m_calculating_cycles = 600;
}
    
unsigned int FractalsConfig::getNumberOfComplexParameters()
{
    return m_number_of_complex_parameters[m_type];
}

unsigned int FractalsConfig::getNumberOfParameters()
{
    return m_number_of_parameters[m_type];
}

unsigned int FractalsConfig::getNumberOfFunctionParameters()
{
    return m_number_of_function_parameters[m_type];
}

unsigned int FractalsConfig::getNumberOfComplexFunctionParameters()
{
    return m_number_of_complex_function_parameters[m_type];
}

bool FractalsConfig::hasParameters()
{
    return ((m_number_of_parameters[m_type] +
             m_number_of_complex_parameters[m_type] +
             m_number_of_function_parameters[m_type] +
             m_number_of_complex_function_parameters[m_type]) != 0);
}

const QString &FractalsConfig::getFormula()
{
    return m_formula[m_type];
}

const QString &FractalsConfig::getLyapunovFormula()
{
    return m_formula[F_LYAPUNOV];
}

const QString &FractalsConfig::getName()
{
    return m_name[m_type];
}

void FractalsConfig::setStartingCentre(const StringComplex &value)
{
    m_scentre[m_type] = value;
}

void FractalsConfig::setStartingWidth(const std::string &value)
{
    m_swidth[m_type] = value;
}

void FractalsConfig::setStartingRotation(const unsigned int value)
{
    m_srotation[m_type] = value;
}

const StringComplex &FractalsConfig::getStartingCentre()
{
    return m_scentre[m_type];
}

const std::string &FractalsConfig::getStartingWidth()
{
    return m_swidth[m_type];
}

int FractalsConfig::getStartingRotation()
{
    return m_srotation[m_type];
}

void FractalsConfig::setCentre(const StringComplex &value)
{
    m_ccentre[m_type] = value;
}

void FractalsConfig::setCentre(const StringComplex &value, bool& changed)
{
    changed = (value.r != m_ccentre[m_type].r) ||
              (value.i != m_ccentre[m_type].i);
    if (changed)
    {
        m_ccentre[m_type] = value;
    }
}

void FractalsConfig::setCurrentWidth(const std::string &value)
{
    m_cwidth[m_type] = value;
}

void FractalsConfig::setRotation(const int value)
{
    m_crotation[m_type] = value;
}

const StringComplex &FractalsConfig::getCentre()
{
    return m_ccentre[m_type];
}

const std::string &FractalsConfig::getCurrentWidth()
{
    return m_cwidth[m_type];
}

int FractalsConfig::getRotation()
{
    return m_crotation[m_type];
}

void FractalsConfig::setColourMap(const QString& id)
{
    if (isOrbitPlotting() || isSingleOrbit())
    {
        m_orbit_colour[m_type] = id;
    }
    else
    {
        m_colour_map[m_index][m_type] = id;
    }
}

void FractalsConfig::setColourMap(const QString& id, bool inner)
{
    if (isOrbitPlotting() || isSingleOrbit())
    {
        m_orbit_colour[m_type] = id;
    }
    else
    {
        m_colour_map[(inner ? 1 : 0)][m_type] = id;
    }
}

QString &FractalsConfig::getColourMap()
{
    return ((isOrbitPlotting() || isSingleOrbit()) ? m_orbit_colour[m_type] : m_colour_map[m_index][m_type]);
}

QString &FractalsConfig::getColourMap(bool inner)
{
    return m_colour_map[(inner ? 1 : 0)][m_type];
}

void FractalsConfig::setSelection(const std::string &sel)
{
    if (sel.length() < 4)
    {
        m_select[m_type] = "normz";
    }
    else if (sel.length() == 4)
    {
        std::string comparison = sel.substr(2, 1);
        std::string selection = sel;
        selection.insert(2, comparison);
        m_select[m_type] = selection;
    }
    else
    {
        m_select[m_type] = sel;
    }
}

const std::string &FractalsConfig::getSelection()
{
    return m_select[m_type];
}

void FractalsConfig::setSelectLimit(long double limit)
{
    m_select_limit[m_type] = limit;
}

long double FractalsConfig::getSelectLimit()
{
    return m_select_limit[m_type];
}


void FractalsConfig::setMethod(const std::string& method)
{
    m_method[m_index][m_type] = method;
}

void FractalsConfig::setMethod(bool inner, const std::string& method)
{
    m_method[(inner ? 1 : 0)][m_type] = method;
}

const std::string &FractalsConfig::getMethod()
{
    return m_method[m_index][m_type];
}

const std::string &FractalsConfig::getMethod(bool inner)
{
    return m_method[(inner ? 1 : 0)][m_type];
}

void FractalsConfig::setColourScale(long double scale)
{
    m_colour_scale[m_index][m_type] = scale;
}

void FractalsConfig::setColourScale(bool inner, long double scale)
{
    m_colour_scale[(inner ? 1 : 0)][m_type] = scale;
}

long double FractalsConfig::getColourScale()
{
    return m_colour_scale[m_index][m_type];
}

void FractalsConfig::setMaxIterations(int value)
{
    m_max_iterations[m_type] = value;
}

int FractalsConfig::getMaxIterations()
{
    return m_max_iterations[m_type];
}

void FractalsConfig::setDefaultMaxIterations()
{
    m_max_iterations[m_type] = m_default_max_iterations[m_type];
}

unsigned int FractalsConfig::getIterationStepSize()
{
    return m_iteration_step_size[m_type];
}

void FractalsConfig::setInitialValues(INITIAL_VALUE value)
{
    m_zero_initial_values[m_type] = value;
}

void FractalsConfig::setFixedInitialValue(const StringComplex &value)
{
    m_z0[m_type] = value;
}

INITIAL_VALUE FractalsConfig::getInitialValues()
{
    return m_zero_initial_values[m_type];
}

INITIAL_VALUE FractalsConfig::getDefaultInitialValues()
{
    return m_default_zero_initial_values[m_type];
}

const StringComplex &FractalsConfig::getDefaultFixedInitialValues()
{
    return m_default_z0[m_type];
}

const StringComplex &FractalsConfig::getFixedInitialValue()
{
    return m_z0[m_type];
}

void FractalsConfig::defaultStartingComplexPlane()
{
    m_scentre[m_type] = m_default_scentre[m_type];
    m_swidth[m_type] = m_default_swidth[m_type];
    m_srotation[m_type] = 0;
}

void FractalsConfig::setWidth(unsigned int value)
{
    if (value != 0)
    {
        m_width = static_cast<long double>(value);
    }
}

long double FractalsConfig::width()
{
    return m_width;
}

void FractalsConfig::setHeight(unsigned int value)
{
    if (value != 0)
    {
        m_height = static_cast<long double>(value);
    }
}

long double FractalsConfig::height()
{
    return m_height;
}

FractalsConfig::VectorFractalId &FractalsConfig::getAllFractals()
{
    FractalId id;
    m_fractal_ids.clear();
    for (auto it=m_name.begin(); it != m_name.end(); it++)
    {
        id.type = it->first;
        id.name = it->second;
        m_fractal_ids.push_back(id);
    }
    return m_fractal_ids;
}

void FractalsConfig::setLimit(long double value)
{
    m_limit[m_type] = value;
}

long double FractalsConfig::getLimit()
{
    return m_limit[m_type];
}

void FractalsConfig::setSmooth(bool value)
{
    m_smooth[m_index][m_type] = value;
}

void FractalsConfig::setSmooth(bool inner, bool value)
{
    m_smooth[(inner ? 1 : 0)][m_type] = value;
}

bool FractalsConfig::getSmooth()
{
    return m_smooth[m_index][m_type];
}

void FractalsConfig::setAbsLog(bool value)
{
    m_abs_log[m_index][m_type] = value;
}

void FractalsConfig::setAbsLog(bool inner, bool value)
{
    m_abs_log[(inner ? 1 : 0)][m_type] = value;
}

bool FractalsConfig::getAbsLog()
{
    return m_abs_log[m_index][m_type];
}

const std::string &FractalsConfig::getLyapunovSequence()
{
    return m_sequence;
}

unsigned int FractalsConfig::getSettlingCycles()
{
    return m_settling_cycles;
}

unsigned int FractalsConfig::getCalculatingCycles()
{
    return m_calculating_cycles;
}

void FractalsConfig::setLyapunovSequence(const std::string& sequence)
{
    m_sequence = sequence;
}

void FractalsConfig::setSettlingCycles(unsigned int value)
{
    m_settling_cycles = value;
}

void FractalsConfig::setCalculatingCycles(unsigned int value)
{
    m_calculating_cycles = value;
}

int FractalsConfig::getOrbitColourInterval()
{
    return m_interval[m_type];
}

char FractalsConfig::getOrbitColourType()
{
    return m_orbit_colour_type[m_type];
}

void FractalsConfig::setOrbitColourInterval(unsigned int value)
{
    m_interval[m_type] = value;
}

void FractalsConfig::setOrbitColourType(char value)
{
    m_orbit_colour_type[m_type] = value;
}

bool FractalsConfig::isBailoutFractal()
{
    return (m_type != F_LYAPUNOV);
}

void FractalsConfig::setInner(bool inner)
{
    m_index = (inner ? 1 : 0);
}

bool FractalsConfig::isInner()
{
    return (m_index == 1);
}

void FractalsConfig::setBailout(BAILOUT value)
{
    m_bailout[m_type] = value;
}

BAILOUT FractalsConfig::getBailout()
{
    return m_bailout[m_type];
}

void FractalsConfig::setConvergent(bool value)
{
    m_converging[m_type] = value;
}

bool FractalsConfig::isConvergent()
{
    return m_converging[m_type];
}

bool FractalsConfig::transformsDefined()
{
    int count = m_cp_transforms[m_type].size();
    if (m_transforms.count(m_type) != 0)
    {
        auto start = m_transforms[m_type].begin();
        auto end = m_transforms[m_type].end();
        for (auto it = start; it != end; it++)
        {
            count += it->size();
        }
    }
    return (count > 0);
}

int FractalsConfig::getNumberOfComplexPlaneTransforms()
{
    return m_cp_transforms[m_type].size();
}

void FractalsConfig::setComplexPlaneTransform(int i, const std::string& t)
{
    m_cp_transforms[m_type][i] = t;
}

std::string FractalsConfig::getComplexPlaneTransform(int i)
{
    return m_cp_transforms[m_type][i];
}

void FractalsConfig::addComplexPlaneTransform(const std::string& t)
{
    m_cp_transforms[m_type].push_back(t);
}

void FractalsConfig::swapComplexPlaneTransforms(int a, int b)
{
    std::string a_str = m_cp_transforms[m_type][a];
    m_cp_transforms[m_type][a] = m_cp_transforms[m_type][b];
    m_cp_transforms[m_type][b] = a_str;
}

void FractalsConfig::deleteComplexPlaneTransforms()
{
    m_cp_transforms[m_type].clear();
}

int FractalsConfig::getNumberOfTransformSets()
{
    auto &map = m_transforms[m_type];
    return map.size();
}

int FractalsConfig::getNumberOfTransforms(int set)
{
    int size = m_transforms[m_type].size();
    if (set < size)
    {
        size =  m_transforms[m_type][set].size();
    }
    return size;
}

void FractalsConfig::setTransform(int set, int i, const std::string& t)
{
    m_transforms[m_type][set][i] = t;
}

std::string FractalsConfig::getTransform(int set, int i)
{
    return m_transforms[m_type][set][i];
}

void FractalsConfig::addTranformSet()
{
    TransformVector v;
    m_transforms[m_type].push_back(v);
}

void FractalsConfig::deleteTransformSet(size_t set)
{
    auto& v = m_transforms[m_type];
    if (v.size() > set)
    {
        v.erase(v.begin()+set);
    }
}

void FractalsConfig::addTransform(int set, const std::string &t)
{
    m_transforms[m_type][set].push_back(t);
}

void FractalsConfig::swapTransforms(int set, int a, int b)
{
    std::string t = m_transforms[m_type][set][a];
    m_transforms[m_type][set][a] = m_transforms[m_type][set][b];
    m_transforms[m_type][set][b] = t;
}

void FractalsConfig::deleteTransform(int set, size_t pos)
{
    TransformVector &v = m_transforms[m_type][set];
    if (v.size() > pos)
    {
        v.erase(v.begin()+pos);
    }
}

void FractalsConfig::deleteComplexPlaneTransform(size_t pos)
{
    TransformVector &v = m_cp_transforms[m_type];
    if (v.size() > pos)
    {
        v.erase(v.begin()+pos);
    }
}

void FractalsConfig::deleteTransforms()
{
    m_transforms[m_type].clear();
    m_cp_transforms[m_type].clear();
}

void FractalsConfig::setTransformSequence(const std::string& seq)
{
    m_transform_sequence[m_type] = seq;
}

const std::string &FractalsConfig::getTransformSequence()
{
    return m_transform_sequence[m_type];
}

void FractalsConfig::setInitialValuesFromString(const std::string value)
{
    KeyString keys(value);
    auto type = static_cast<INITIAL_VALUE>(keys.GetKeyAsInt("type", 0));
    setInitialValues(type);
    StringComplex initial_value(keys.GetKey("r", "0"), keys.GetKey("i", "0"));
    setFixedInitialValue(initial_value);
}

void FractalsConfig::setCommon(const StringComplex& centre,
                              const std::string& side,
                              int iterations,
                              int step_size,
                              INITIAL_VALUE init_type)
{
    m_name[m_type] = fractalTypeToString(m_type);
    m_default_scentre[m_type] = centre;
    m_scentre[m_type] = centre;
    m_ccentre[m_type] = centre;
    m_ccentre[m_type] = centre;
    m_default_swidth[m_type] = side;
    m_swidth[m_type] = side;
    m_cwidth[m_type] = side;
    defineBailout(B_NORM);
    m_bailout[m_type] = m_default_bailout[m_type];
    m_colour_map[0][m_type] = "Default";
    m_order[0][m_type] = CO_RGB;
    m_red_offset[0][m_type] = 0;
    m_green_offset[0][m_type] = 0;
    m_blue_offset[0][m_type] = 0;
    m_select[m_type] = "normz";
    m_method[0][m_type] = "i";
    m_colour_map[1][m_type] = "Default";
    m_order[1][m_type] = CO_RGB;
    m_red_offset[1][m_type] = 0;
    m_green_offset[1][m_type] = 0;
    m_blue_offset[1][m_type] = 0;
    m_method[1][m_type] = "f,0,0,0";
    m_limit[m_type] = 16.0L;
    m_select_limit[m_type] = 4.0L;
    m_converging[m_type] = false;
    m_zero_initial_values[m_type] = init_type;
    m_default_zero_initial_values[m_type] = init_type;
    defineZ0(StringComplex("0", "0"));
    m_max_iterations[m_type] = iterations;
    m_default_max_iterations[m_type] = iterations;
    m_iteration_step_size[m_type] = step_size;
    m_number_of_complex_parameters[m_type] = 0;
    m_number_of_parameters[m_type]= 0;
    m_number_of_function_parameters[m_type] = 0;
    m_number_of_complex_function_parameters[m_type] = 0;
    m_default_interval[m_type] = 32000;
    m_default_orbit_colour_type[m_type] = 'a';
    m_interval[m_type] = m_default_interval[m_type];
    m_orbit_colour_type[m_type] = m_default_orbit_colour_type[m_type];
    m_calculating_area[m_type] = 9;
    m_density[m_type] = 1;
    m_quick[m_type] = false;
}

void FractalsConfig::defineBailout(BAILOUT type)
{
    m_default_bailout[m_type] = type;
    m_bailout[m_type] = type;
}

void FractalsConfig::defineComplexParameter(int index, const StringComplex &value, PARAMETER_TYPE type)
{
    m_complex_parameters[m_type][index].p = value;
    m_complex_parameters[m_type][index].type = type;
    m_default_complex_parameters[m_type][index].p = value;
    m_default_complex_parameters[m_type][index].type = type;
}

void FractalsConfig::defineParameter(int index, const std::string &value)
{
    m_parameters[m_type][index] = value;
    m_default_parameters[m_type][index] = value;
}

void FractalsConfig::defineFunctionParameter(int index, FUNCTION_PARAMETER f, const std::string &p)
{
    KeyString key_string;
    key_string.SetKey("id", intToString(static_cast<int>(f)));
    if (!p.empty())
    {
       key_string.SetKey("p", p);
    }
    m_functions[m_type][index] = key_string.String();
    m_default_functions[m_type][index] = key_string.String();
}

void FractalsConfig::defineComplexFunctionParameter(int index, COMPLEX_FUNCTION_PARAMETER f, const std::string &p)
{
    KeyString key_string;
    key_string.SetKey("pair", "n");
    key_string.SetKey("id", intToString(static_cast<int>(f)));
    if (!p.empty())
    {
        key_string.SetKey("r", p);
        key_string.SetKey("i", "0");
    }
    m_complex_functions[m_type][index] = key_string.String();
    m_default_complex_functions[m_type][index] = key_string.String();
}

void FractalsConfig::defineZ0(const StringComplex &z)
{
    m_default_z0[m_type] = z;
    m_z0[m_type] = z;
}

void FractalsConfig::defineMandelbrot()
{
    m_type = F_MANDELBROT;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = z</big><sup>2</sup><big> + α</big></b>");
    setCommon(StringComplex("-0.25", "0"), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex("0", "0"), PT_IS_C);
}

void FractalsConfig::defineQuadratic()
{
    m_type = F_QUADRATIC;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = αz</big><sup>2</sup><big> + βz + γ</big></b>");
    setCommon(StringComplex("-0.75", "0"), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 3;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("0", "0"), PT_IS_C);
}

void FractalsConfig::defineCubic()
{
    m_type = F_CUBIC;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = αz</big><sup>3</sup><big> + βz</big><sup>2</sup><big> + γz + δ</big></b>");
    setCommon(StringComplex("-0.25", "0"), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 4;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex("0", "0"), PT_IS_C);
}

void FractalsConfig::defineAlmostCubic()
{
    m_type = F_ALMOST_CUBIC;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = αz</big><sup>3</sup><big> + βz</big><sup>2</sup><big> + γz + δ</big></b><br><br>"
        "<b><big>There is an error in the calculation of the imaginary part</big></b>");
    setCommon(StringComplex("-0.25", "0"), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 4;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex("1", "0"), PT_IS_C);
}

void FractalsConfig::defineSingleFunction()
{
    m_type = F_SINGLE_FUNCTION;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = F1(αz) + β</big></b>");
    setCommon(StringComplex(), "4", 5000, 5, FIXED);
    m_number_of_complex_parameters[m_type] = 2;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("0", "0"), PT_IS_C);
    m_number_of_complex_function_parameters[m_type] = 1;
    defineComplexFunctionParameter(0, CFP_NO_OP);
}

void FractalsConfig::defineZcpac()
{
    m_type = F_ZCPAC;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = z</big><sup>α</sup><big> + β</big></b>");
    setCommon(StringComplex(), "4", 5000, 5, FIXED);
    m_number_of_complex_parameters[m_type] = 2;
    defineComplexParameter(0, StringComplex("4", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("0", "0"), PT_IS_C);
}

void FractalsConfig::defineTwoFunctionProduct()
{
    m_type = F_2F_PRODUCT;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = F1(αz)*F2(βz) + γ</big></b>");
    setCommon(StringComplex(), "4", 5000, 5, FIXED);
    m_number_of_complex_parameters[m_type] = 3;
    defineComplexParameter(0, StringComplex("1", "0"), PT_IS_C);
    defineComplexParameter(1, StringComplex("1", "0"), PT_IS_C);
    defineComplexParameter(2, StringComplex(), PT_NUMBER);
    m_number_of_complex_function_parameters[m_type] = 2;
    defineComplexFunctionParameter(0, CFP_NO_OP);
    defineComplexFunctionParameter(1, CFP_NO_OP);
}

void FractalsConfig::defineCpowerZ()
{
    m_type = F_C_POWER_Z;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = α</big><sup>z</sup><big> + β</big></b>");
    setCommon(StringComplex(), "4", 5000, 5, FIXED);
    m_number_of_complex_parameters[m_type] = 2;
    defineComplexParameter(0, StringComplex("2", "0"), PT_IS_C);
    defineComplexParameter(1, StringComplex("0", "0"), PT_IS_C);
}

void FractalsConfig::defineUnnamed()
{
    m_type = F_UNNAMED;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = (z<sup>α</sup>+β)<sup>γ</sup>/z(z<sup>α</sup>-β)<sup>δ</sup></big></b>");
    setCommon(StringComplex(), "4", 5000, 5, UNTRANSFORMED);
    m_number_of_complex_parameters[m_type] = 4;
    defineComplexParameter(0, StringComplex("2", "0"), PT_NUMBER);
    defineComplexParameter(0, StringComplex("1", "0"), PT_IS_C);
    defineComplexParameter(1, StringComplex("2", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("1", "0"), PT_NUMBER);
}

void FractalsConfig::defineCombination()
{
    m_type = F_COMBINATION;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = αz</big><sup>β</sup><big> + γz</big><sup>δ</sup><big> + ε</big></b>");
    setCommon(StringComplex("-4", "0"), "5", 5000, 5, FIXED);
    m_number_of_complex_parameters[m_type] = 5;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("2", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("2", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex("-1", "0"), PT_NUMBER);
    defineComplexParameter(4, StringComplex(), PT_IS_C);
    defineZ0(StringComplex("1", "0"));
}

void FractalsConfig::defineBiomorph1()
{
    m_type = F_BIOMORPH_1;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = z</big><sup>α</sup><big> + z</big><sup>z</sup><big> + β</big></b>");
    setCommon(StringComplex(), "4", 10, 5, TRANSFORMED);
    m_number_of_complex_parameters[m_type] = 2;
    defineComplexParameter(0, StringComplex("2", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("0", "0"), PT_NUMBER);
    m_select[m_type] = "aa<<o";
    m_method[0][m_type] = "mn";
    m_colour_scale[0][m_type] = 100.0L;
    m_limit[m_type] = 100.0L;
    m_select_limit[m_type] = 10.0L;
}

void FractalsConfig::defineBiomorph2()
{
    m_type = F_BIOMORPH_2;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = sin(z) + z</big><sup>α</sup><big> + β</big></b>");
    setCommon(StringComplex(), "4", 10, 5, TRANSFORMED);
    m_number_of_complex_parameters[m_type] = 2;
    defineComplexParameter(0, StringComplex("2", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex(), PT_NUMBER);
    m_select[m_type] = "aa<<o";
    m_method[0][m_type] = "mn";
    m_colour_scale[0][m_type] = 100.0L;
    m_limit[m_type] = 100.0L;
    m_select_limit[m_type] = 10.0L;
}

void FractalsConfig::defineBiomorph3()
{
    m_type = F_BIOMORPH_3;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = e</big><sup>z</sup><big> + z</big><sup>α</sup><big> + β</big></b>");
    setCommon(StringComplex(), "4", 10, 5, TRANSFORMED);
    m_number_of_complex_parameters[m_type] = 2;
    defineComplexParameter(0, StringComplex("2", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex(), PT_NUMBER);
    m_select[m_type] = "aa<<o";
    m_method[0][m_type] = "mn";
    m_colour_scale[0][m_type] = 100.0L;
    m_limit[m_type] = 100.0L;
    m_select_limit[m_type] = 10.0L;
}

void FractalsConfig::defineBiomorph4()
{
    m_type = F_BIOMORPH_4;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = sin(z) + e</big><sup>z</sup><big> + α</big></b>");
    setCommon(StringComplex(), "4", 10, 5, TRANSFORMED);
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex(), PT_NUMBER);
    m_select[m_type] = "aa<<o";
    m_method[0][m_type] = "mn";
    m_colour_scale[0][m_type] = 100.0L;
    m_limit[m_type] = 100.0L;
    m_select_limit[m_type] = 10.0L;
}

void FractalsConfig::defineBiomorph5()
{
    m_type = F_BIOMORPH_5;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = sinh(z) + α</big></b>");
    setCommon(StringComplex(), "4", 10, 5, TRANSFORMED);
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex(), PT_NUMBER);
    m_select[m_type] = "aa<<o";
    m_method[0][m_type] = "mn";
    m_colour_scale[0][m_type] = 100.0L;
    m_limit[m_type] = 100.0L;
    m_select_limit[m_type] = 10.0L;
}

void FractalsConfig::defineCombination2()
{
    m_type = F_COMBINATION_2;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = αβz</big><sup>γ</sup><big> + δz</big><sup>ε</sup></b>");
    setCommon(StringComplex(), "4", 5000, 5, UNTRANSFORMED);
    m_number_of_complex_parameters[m_type] = 5;
    defineComplexParameter(0, StringComplex(), PT_IS_C);
    defineComplexParameter(1, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("-1", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(4, StringComplex("2", "0"), PT_NUMBER);
}

void FractalsConfig::defineCombination3()
{
    m_type = F_COMBINATION_3;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = (αz</big><sup>β</sup><big> + γ)</big><sup>δ</sup>"
            "<big> + (εz</big><sup>ζ</sup><big> + η)</big><sup>θ</sup></b>");
    setCommon(StringComplex(), "6", 5000, 5, FIXED);
    m_number_of_complex_parameters[m_type] = 8;
    defineComplexParameter(0, StringComplex(),PT_IS_C);
    defineComplexParameter(1, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("2", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(4, StringComplex(), PT_IS_C);
    defineComplexParameter(5, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(6, StringComplex("2", "0"), PT_NUMBER);
    defineComplexParameter(7, StringComplex("-1", "0"), PT_NUMBER);
}

void FractalsConfig::defineNova()
{
    m_type = F_NOVA;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = z - α(f(z)/f'(z)) + γ</big></b><br>"
        "<b><big>f(z) = z</big><sup>β</sup><big> - 1</big></b>");
    setCommon(StringComplex(), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 3;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("3", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex(), PT_IS_C);
    m_limit[m_type] = 0.01L;
    m_converging[m_type] = true;
    m_select[m_type] = "normz";
    m_select_limit[m_type] = 0.1L;
    defineZ0(StringComplex("1", "0"));
}

void FractalsConfig::defineZpowerTancz()
{
    m_type = F_Z_POWER_TANCZ_AC;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = z<sup>tan(αz)</sup></big> + β</b>");
    setCommon(StringComplex(), "4", 5000, 5, TRANSFORMED);
    m_number_of_complex_parameters[m_type] = 2;
    defineComplexParameter(0, StringComplex("1", "0"), PT_IS_C);
    defineComplexParameter(1, StringComplex("0", "0"), PT_NUMBER);
}

void FractalsConfig::defineTzaccp()
{
    m_type = F_TZACCP;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = (transform(z + α))</big><sup>β</sup></b>");
    setCommon(StringComplex(), "4", 5000, 5, FIXED);
    m_number_of_complex_parameters[m_type] = 2;
    defineComplexParameter(0, StringComplex("1", "0"), PT_IS_C);
    defineComplexParameter(1, StringComplex("2", "0"), PT_NUMBER);
}

void FractalsConfig::defineMagnet()
{
    m_type = F_MAGNET;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = ((z</big><sup>2</sup><big> + α - 1)/(2z + α - 2))</big><sup>2</sup></b>");
    setCommon(StringComplex("0.5", "0"), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex(), PT_IS_C);
}

void FractalsConfig::defineMagnet2()
{
    m_type = F_MAGNET_2;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>q = z</big><sup>3</sup><big> + 3(α - 1)z + (α -1 )(α - 2)</big></b><br>"
        "<b><big>d = 3z<sup>2</sup> + 3(α - 2) + α<sup>2</sup> - 3α + 3</big></b><br>"
        "<b><big>z = (q/d)<sup>2</sup></big></b>");
    setCommon(StringComplex("-0.5", "0"), "4", 5000, 10,FIXED);
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex(), PT_IS_C);
}

void FractalsConfig::defineZazbcgd()
{
    m_type = F_ZAZBCGD;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = (z</big><sup>α</sup><big> + z</big><sup>β</sup><big>γ</big><sup>δ</sup><big>)</big><sup>ε</sup></b>");
    setCommon(StringComplex("-0.3", "0"), "1.6", 5000, 5, TRANSFORMED);
    m_number_of_complex_parameters[m_type] = 5;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("-1", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("2", "0"), PT_IS_C);
    defineComplexParameter(3, StringComplex("2", "0"), PT_NUMBER);
    defineComplexParameter(4, StringComplex("2", "0"), PT_NUMBER);
}

void FractalsConfig::defineSqrtCP()
{
    m_type = F_SQRT_CP;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = sqrt(z</big><sup>α</sup><big>) + β</big></b>");
    setCommon(StringComplex(), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 2;
    defineComplexParameter(0, StringComplex("4", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("1", "0"), PT_IS_C);
}

void FractalsConfig::defineNova1()
{
    m_type = F_NOVA_1;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = z - α(f(z)/f'(z)) + ζ</big></b><br>"
        "<b><big>f(z) = βz</big><sup>γ</sup><big> - δz</big><sup>ε</sup><big> - 1</big></b>");
    setCommon(StringComplex(), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 6;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex(longdoubleToString(1.0L/30.0L), "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("6.0", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex("0.5", "0"), PT_NUMBER);
    defineComplexParameter(4, StringComplex("2", "0"), PT_NUMBER);
    defineComplexParameter(5, StringComplex(), PT_IS_C);
    m_limit[m_type] = 0.01L;
    m_converging[m_type] = true;
    m_select[m_type] = "normz";
    m_select_limit[m_type] = 0.1L;
    defineZ0(StringComplex("1", "0"));
    m_converging[m_type] = true;
}

void FractalsConfig::defineNova2()
{
    m_type = F_NOVA_2;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = z - α(f(z)/f'(z)) + δ</big></b><br>"
        "<b><big>f(z) = z</big><sup>β</sup><big> - (δ-1)z</big><sup>γ</sup><big> - δ</big></b>");
    setCommon(StringComplex(), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 4;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("3", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex(), PT_IS_C);
    m_limit[m_type] = 0.01L;
    m_converging[m_type] = true;
    m_select[m_type] = "normz";
    m_select_limit[m_type] = 0.1L;
    defineZ0(StringComplex("1", "0"));
}

void FractalsConfig::defineUnnamed2()
{
    m_type = F_UNNAMED_2;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = (z<sup>α</sup>+β)<sup>γ</sup>/z<sup>δ</sup>(z<sup>ε</sup>-β)<sup>ζ</sup></big></b>");
    setCommon(StringComplex(), "4", 5000, 5, UNTRANSFORMED);
    m_number_of_complex_parameters[m_type] = 6;
    defineComplexParameter(0, StringComplex("2", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("1", "0"), PT_IS_C);
    defineComplexParameter(2, StringComplex("2", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(4, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(5, StringComplex("1", "0"), PT_NUMBER);
}

void FractalsConfig::defineQuartic()
{
    m_type = F_QUARTIC;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = αz<sup>4</sup> + βz<sup>3</sup> + γz<sup>2</sup> + δz + ε</big></b>");
    setCommon(StringComplex(), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 5;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(4, StringComplex(), PT_IS_C);
}

void FractalsConfig::defineQuintic()
{
    m_type = F_QUINTIC;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = αz<sup>5</sup> + βz<sup>4</sup> + γz<sup>3</sup> + δz<sup>2</sup> + εz + ζ</big></b>");
    setCommon(StringComplex(), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 6;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(4, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(5, StringComplex(), PT_IS_C);
}

void FractalsConfig::defineHexic()
{
    m_type = F_HEXIC;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = αz<sup>6</sup> + βz<sup>5</sup> + γz<sup>4</sup> +"
                    "δz<sup>3</sup> + εz<sup>2</sup> + ζz + η</big></b>");
    setCommon(StringComplex(), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 7;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(4, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(5, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(6, StringComplex(), PT_IS_C);
}

void FractalsConfig::defineHeptic()
{
    m_type = F_HEPTIC;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = αz<sup>7</sup> + βz<sup>6</sup> + γz<sup>5</sup> +"
                    "δz<sup>4</sup> + εz<sup>3</sup> + ζz<sup>2</sup> +"
                    "ηz + θ</big></b>");
    setCommon(StringComplex(), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 8;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(4, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(5, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(6, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(7, StringComplex(), PT_IS_C);
}

void FractalsConfig::defineOctic()
{
    m_type = F_OCTIC;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = αz<sup>8</sup> + βz<sup>7</sup> + γz<sup>6</sup> +"
                    "δz<sup>5</sup> + εz<sup>4</sup> + ζz<sup>3</sup> +"
                    "ηz<sup>2</sup> + θz + ι</big></b>");
    setCommon(StringComplex(), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 9;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(4, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(5, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(6, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(7, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(8, StringComplex(), PT_IS_C);
}

void FractalsConfig::defineZcpTanz()
{
    m_type = F_ZCPTANZ;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>z = transform(z)</big></b><br>"
            "<b><big>z = z</big><sup>α</sup><big>tan(z) + β</big></b>");
    setCommon(StringComplex(), "4", 5000, 10, TRANSFORMED);
    m_number_of_complex_parameters[m_type] = 2;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("0.1", "0"), PT_IS_C);
}

void FractalsConfig::defineLyapunov()
{
    m_type = F_LYAPUNOV;
    m_formula[m_type] = QString::fromUtf8(
            "<big>Lyapunov</big><br><br>"
            "The Lyapunov fractal is a forced cyclic system, the value used for "
            "each iteration is determined by the sequence. Each letter in "
            "the sequence determines the value used, for A use the real component and "
            "for B use the imaginary component. This sequence is completed for each 'cycle', "
            "there is a settling period before the Lyapunov coefficient is calculated "
            "specified by the number of settling cycles. The number of iteration used "
            "is the number of cycles multiplied by the length of the sequence."
            "<br><br>"
            "The sequence must contain at least one A and one B. Any character "
            "entered in the sequence that isn't A, B, a or b will "
            "automatically be changed to B, if all the characters are the same either "
            "an A or a B will be added.");
    setCommon(StringComplex("3", "2"), "6", 0, 0, FIXED);
    m_method[0][m_type] = "v";
    m_colour_scale[0][m_type] = 1000.0L;
}

void FractalsConfig::defineCompasses()
{
    m_type = F_COMPASSES;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>z = transform(z)</big></b><br>"
            "<b><big>z = z</big><sup>α</sup><big> - αβ</big><sup>α - 1</sup><big>z + γ</big></b>");
    setCommon(StringComplex(), "4", 5000, 5, TRANSFORMED);
    m_number_of_complex_parameters[m_type] = 3;
    defineComplexParameter(0, StringComplex("2", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("1", "0"), PT_IS_C);
    defineComplexParameter(2, StringComplex(), PT_NUMBER);
}

void FractalsConfig::defineRealNumberMandelbrot()
{
    m_type = F_RN_MANDELBROT;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>z = transform(z)</big></b><br>"
            "<b><big>z</big><sub>r</sub><big> = z</big><sub>r</sub><sup>2</sup><big> + α</big><sub>r</sub></b><br>"
            "<b><big>z</big><sub>i</sub><big> = z</big><sub>i</sub><sup>2</sup><big> + α</big><sub>i</sub></b>");
    setCommon(StringComplex(), "4", 5000, 10, TRANSFORMED);
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex("-2", "-2"), PT_IS_C);
    m_limit[m_type] = 2.0L;
    m_select_limit[m_type] = 1.0L;
    defineBailout(B_ABS_DIFF);
}

void FractalsConfig::definePickoverPopcorn4Function()
{
    m_type = F_PICKOVER_POPCORN_4F;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>z = transform(z)<br>"
            "x =  z</big><sub>r</sub><big><br>"
            "y =  z</big><sub>i</sub><big><br>"
            "a = x - A*f1(y + f2(B*y))<br>"
            "b = y - C*f3(x + f4(D*x))<br>"
            "z = a + bi + α</b>");
    setCommon(StringComplex(), "90", 5000, 10, FIXED);
    m_number_of_parameters[m_type] = 4;
    defineParameter(0, "0.05");
    defineParameter(1, "3.0");
    defineParameter(2, "0.05");
    defineParameter(3, "3.0");
    m_number_of_function_parameters[m_type] = 4;
    defineFunctionParameter(0, FP_SIN);
    defineFunctionParameter(1, FP_TAN);
    defineFunctionParameter(2, FP_SIN);
    defineFunctionParameter(3, FP_TAN);
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex(), PT_IS_C);
}

void FractalsConfig::definePickoverPopcorn6Function()
{
    m_type = F_PICKOVER_POPCORN_6F;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>z = transform(z)<br>"
            "x = z</big><sub>r</sub><big><br>"
            "y = z</big><sub>i</sub><big><br>"
            "a = x - A*f1(y + f2(B*(y + f3(C*y))))<br>"
            "b = y - D*f4(x + f5(E*(x + f6(F*x))))<br>"
            "z = a +bi  + α</b>");
    setCommon(StringComplex(), "90", 5000, 10, FIXED);
    m_number_of_parameters[m_type] = 6;
    defineParameter(0, "0.05");
    defineParameter(1, "3");
    defineParameter(2, "3");
    defineParameter(3, "0.05");
    defineParameter(4, "3");
    defineParameter(5, "3");
    m_number_of_function_parameters[m_type] = 6;
    defineFunctionParameter(0, FP_SIN);
    defineFunctionParameter(1, FP_SIN);
    defineFunctionParameter(2, FP_SIN);
    defineFunctionParameter(3, FP_SIN);
    defineFunctionParameter(4, FP_SIN);
    defineFunctionParameter(5, FP_SIN);
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex(), PT_IS_C);
}

void FractalsConfig::defineHybrid()
{
    m_type = F_HYBRID;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>n = norm(z)</big></b><br>"
            "<b><big>z = transform(z)</big></b><br>"
            "<b><big>z = α(z</big><sub>r</sub><big>/n)</big><sup>β</sup><big> + "
            "γ(z</big><sub>i</sub><big>/n)</big><sup>δ</sup><big> + ε</big></b>");
    setCommon(StringComplex(), "4", 5000, 5, TRANSFORMED);
    m_number_of_complex_parameters[m_type] = 5;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(4, StringComplex(), PT_IS_C);
}

void FractalsConfig::defineZduccpac()
{
    m_type = F_ZDUCCPAC;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>z = transform(z)</big></b><br>"
            "<b><big>z = (z/unsign(β))</big><sup>α</sup><big> + β</big></b>");
    setCommon(StringComplex(), "4", 5000, 5, TRANSFORMED);
    m_number_of_complex_parameters[m_type] = 2;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("-0.85", "-0.23"), PT_IS_C);
}

void FractalsConfig::defineMallard()
{
    m_type = F_MALLARD;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>z = transform(z)</big></b><br>"
            "<b><big>z = (F1(z</big><sup>α</sup><big> + β</big>))<sup>γ</sup></b>");
    setCommon(StringComplex(), "4", 5000, 5, UNTRANSFORMED);
    m_number_of_complex_parameters[m_type] = 3;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("0.5", "0.5"), PT_IS_C);
    defineComplexParameter(2, StringComplex("1", "0"), PT_NUMBER);
    defineBailout(B_NONE);
    m_number_of_complex_function_parameters[m_type] = 1;
    defineComplexFunctionParameter(0, CFP_LOG);
}

void FractalsConfig::defineTzcpac()
{
    m_type = F_TZCPAC;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>z = transform(z</big><sup>α</sup><big>) + β</big></b>");
    setCommon(StringComplex(), "4", 5000, 5, FIXED);
    m_number_of_complex_parameters[m_type] = 2;
    defineComplexParameter(0, StringComplex("2", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("0", "0"), PT_IS_C);
}

void FractalsConfig::defineTmallard()
{
    m_type = F_TMALLARD;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>z = (F1(transform(z</big><sup>α</sup><big>) + β))</big><sup>γ</sup></b>");
    setCommon(StringComplex(), "4", 100, 5, UNTRANSFORMED);
    m_number_of_complex_parameters[m_type] = 3;
    defineComplexParameter(0, StringComplex("2", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("0.5", "0.5"), PT_IS_C);
    defineComplexParameter(2, StringComplex("1", "0"), PT_NUMBER);
    defineBailout(B_NONE);
    m_number_of_complex_function_parameters[m_type] = 1;
    defineComplexFunctionParameter(0, CFP_LOG);
}

void FractalsConfig::defineFzcpac()
{
    m_type = F_FZCPAC;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>z = transform(z)</big></b><br>"
            "<b><big>z = F1(z</big><sup>α</sup><big> + β)</big></b>");
    setCommon(StringComplex(), "4", 5000, 5, FIXED);
    m_number_of_complex_parameters[m_type] = 2;
    defineComplexParameter(0, StringComplex("2", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("0.5", "0.5"), PT_IS_C);
    m_number_of_complex_function_parameters[m_type] = 1;
    defineComplexFunctionParameter(0, CFP_LOG);
}

void FractalsConfig::defineFtzcpac()
{
    m_type = F_FTZCPAC;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>z = F1(transform(z</big><sup>α</sup><big>) + β)</big></b>");
    setCommon(StringComplex(), "4", 5000, 5, FIXED);
    m_number_of_complex_parameters[m_type] = 2;
    defineComplexParameter(0, StringComplex("2", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("0.5", "0.5"), PT_IS_C);
    m_number_of_complex_function_parameters[m_type] = 1;
    defineComplexFunctionParameter(0, CFP_LOG);
}

void FractalsConfig::defineZaccp()
{
    m_type = F_ZACCP;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>z = transform(z)</big></b><br>"
            "<b><big>z = (z + α)</big><sup>β</sup></b>");
    setCommon(StringComplex(), "4", 5000, 5, FIXED);
    m_number_of_complex_parameters[m_type] = 2;
    defineComplexParameter(0, StringComplex("0.5", "0.5"), PT_IS_C);
    defineComplexParameter(1, StringComplex("2", "0"), PT_NUMBER);
}

void FractalsConfig::defineCczcpazcp()
{
    m_type = F_CCZCPACZCP;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = α(βz</big><sup>γ</sup><big> + δz</big><sup>ε</sup>)</b>");
    setCommon(StringComplex(), "2.5", 5000, 5, TRANSFORMED);
    defineZ0(StringComplex("1.0", "0"));
    m_number_of_complex_parameters[m_type] = 5;
    defineComplexParameter(0, StringComplex("1", "0"), PT_IS_C);
    defineComplexParameter(1, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("2", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(4, StringComplex("-2", "0"), PT_NUMBER);
}

void FractalsConfig::defineOnion4F()
{
    m_type = F_ONION_4F;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = F1(a) + ε</big></b><br>"
        "<b><big>a = αz/F2(b)</big></b><br>"
        "<b><big>b = βz/F3(c)</big></b><br>"
        "<b><big>c = γz/F4(δz)</big></b>");
    setCommon(StringComplex("-0.5", "0"), "4", 5000, 5, TRANSFORMED);
    m_limit[m_type] = 4.0L;
    m_select_limit[m_type] = 2.0L;
    m_number_of_complex_parameters[m_type] = 5;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(4, StringComplex(), PT_IS_C);
    m_number_of_complex_function_parameters[m_type] = 4;
    defineComplexFunctionParameter(0, CFP_LOG);
    defineComplexFunctionParameter(1, CFP_NO_OP);
    defineComplexFunctionParameter(2, CFP_SIN);
    defineComplexFunctionParameter(3, CFP_COS);
}

void FractalsConfig::defineC2mfczac()
{
    m_type = F_C2MFCZAC;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = αF1(βz + γ)F2(δz + ε)</big></b>");
    setCommon(StringComplex("0.5", "0"), "4", 5000, 5, TRANSFORMED);
    m_number_of_complex_parameters[m_type] = 5;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(4, StringComplex(), PT_IS_C);
    m_number_of_complex_function_parameters[m_type] = 2;
    defineComplexFunctionParameter(0, CFP_POWER, "2");
    defineComplexFunctionParameter(1, CFP_POWER, "-1");
}

void FractalsConfig::defineC2dfczac()
{
    m_type = F_C2DFCZAC;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = αF1(βz + γ)/F2(δz + ε)</big></b>");
    setCommon(StringComplex("0.5", "0"), "4", 5000, 5, TRANSFORMED);
    m_number_of_complex_parameters[m_type] = 5;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(4, StringComplex(), PT_IS_C);
    m_number_of_complex_function_parameters[m_type] = 2;
    defineComplexFunctionParameter(0, CFP_NO_OP);
    defineComplexFunctionParameter(1, CFP_POWER, "-1");
}

void FractalsConfig::defineSingle3fOnion()
{
    m_type = F_SINGLE_3F_ONION;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = αF1(F2(F3(βz + γ))) + δ</big></b>");
    setCommon(StringComplex(), "4", 5000, 5, TRANSFORMED);
    m_number_of_complex_parameters[m_type] = 4;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex(), PT_IS_C);
    m_number_of_complex_function_parameters[m_type] = 3;
    defineComplexFunctionParameter(0, CFP_POWER, "2");
    defineComplexFunctionParameter(1, CFP_SIN);
    defineComplexFunctionParameter(2, CFP_POWER, "2");
}

void FractalsConfig::defineDouble3fOnionM()
{
    m_type = F_DOUBLE_3F_ONION_M;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = αF1(F2(F3(βz + γ)))F4(F5(F6(δz + ε))) + ζ</big></b>");
    setCommon(StringComplex(), "4", 5000, 5, TRANSFORMED);
    m_number_of_complex_parameters[m_type] = 6;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(4, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(5, StringComplex(), PT_IS_C);
    m_number_of_complex_function_parameters[m_type] = 6;
    defineComplexFunctionParameter(0, CFP_POWER, "2");
    defineComplexFunctionParameter(1, CFP_SIN);
    defineComplexFunctionParameter(2, CFP_POWER, "2");
    defineComplexFunctionParameter(3, CFP_POWER, "2");
    defineComplexFunctionParameter(4, CFP_SIN);
    defineComplexFunctionParameter(5, CFP_POWER, "2");
}

void FractalsConfig::defineDouble3fOnionD()
{
    m_type = F_DOUBLE_3F_ONION_D;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = αF1(F2(F3(βz + γ)))/F4(F5(F6(δz + ε))) + ζ</big></b>");
    setCommon(StringComplex(), "4", 5000, 5, TRANSFORMED);
    m_number_of_complex_parameters[m_type] = 6;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(4, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(5, StringComplex(), PT_IS_C);
    m_number_of_complex_function_parameters[m_type] = 6;
    defineComplexFunctionParameter(0, CFP_POWER, "2");
    defineComplexFunctionParameter(1, CFP_SIN);
    defineComplexFunctionParameter(2, CFP_POWER, "2");
    defineComplexFunctionParameter(3, CFP_POWER, "2");
    defineComplexFunctionParameter(4, CFP_SIN);
    defineComplexFunctionParameter(5, CFP_TAN);
}

void FractalsConfig::defineM3()
{
    m_type = F_M3;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = z</big><sup>3</sup><big> + β</big></b>");
    setCommon(StringComplex("0", "0"), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex("0", "0"), PT_IS_C);
}

void FractalsConfig::defineM4()
{
    m_type = F_M4;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = z</big><sup>4</sup><big> + β</big></b>");
    setCommon(StringComplex("0", "0"), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex("0", "0"), PT_IS_C);
}

void FractalsConfig::defineM5()
{
    m_type = F_M5;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = z</big><sup>5</sup><big> + β</big></b>");
    setCommon(StringComplex("0", "0"), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex("0", "0"), PT_IS_C);
}

void FractalsConfig::defineM6()
{
    m_type = F_M6;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = z</big><sup>6</sup><big> + β</big></b>");
    setCommon(StringComplex("0", "0"), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex("0", "0"), PT_IS_C);
}

void FractalsConfig::defineM7()
{
    m_type = F_M7;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = z</big><sup>7</sup><big> + β</big></b>");
    setCommon(StringComplex("0", "0"), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex("0", "0"), PT_IS_C);
}

void FractalsConfig::defineM8()
{
    m_type = F_M8;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = z</big><sup>8</sup><big> + β</big></b>");
    setCommon(StringComplex("0", "0"), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex("0", "0"), PT_IS_C);
}

void FractalsConfig::defineM9()
{
    m_type = F_M9;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = z</big><sup>9</sup><big> + β</big></b>");
    setCommon(StringComplex("0", "0"), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex("0", "0"), PT_IS_C);
}

void FractalsConfig::defineM10()
{
    m_type = F_M10;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = z</big><sup>10</sup><big> + β</big></b>");
    setCommon(StringComplex("0", "0"), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex("0", "0"), PT_IS_C);
}

void FractalsConfig::defineAttractors()
{
    m_type = F_ATTRACTORS;
    m_name[m_type] = fractalTypeToString(m_type);
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>z = transform(z)</big></b><br>"
            "<b><big>x = z</big><sub>r</sub><b><br>"
            "<b><big>y = z</big><sub>i</sub><b><br>"
            "<b><big>a = Af1(By) + Cf2(Dx)</big><b><br>"
            "<b><big>b = Ef3(Fx) + Gf4(Hy)</big><b><br>"
            "<b><big>z = a +bi + α</big></b>");
    setCommon(StringComplex(), "6", 50, 5, TRANSFORMED);
    setOrbitPlotting(true);
    m_number_of_parameters[m_type] = 8;
    defineParameter(0, "1");
    defineParameter(1, "2");
    defineParameter(2, "-1");
    defineParameter(3, "-2");
    defineParameter(4, "1");
    defineParameter(5, "2");
    defineParameter(6, "-1");
    defineParameter(7, "-2");
    m_number_of_function_parameters[m_type] = 4;
    defineFunctionParameter(0, FP_SIN);
    defineFunctionParameter(1, FP_COS);
    defineFunctionParameter(2, FP_SIN);
    defineFunctionParameter(3, FP_COS);
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex(), PT_NUMBER);
}

void FractalsConfig::defineGeneralMixture()
{
    m_type = F_GENERAL_MIXTURE;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = (α(βz</big><sup>γ</sup><big> + δz</big><sup>ε</sup><big>) + ζ)</big><sup>η</sup></b>");
    setCommon(StringComplex("-1", "0"), "4", 5000, 10, FIXED);
    defineZ0(StringComplex("1", "0"));
    m_number_of_complex_parameters[m_type] = 7;
    defineComplexParameter(0, StringComplex("1", "0"), PT_IS_C);
    defineComplexParameter(1, StringComplex("2", "0"), PT_NUMBER);
    defineComplexParameter(2, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex("-1", "0"), PT_NUMBER);
    defineComplexParameter(4, StringComplex("2", "0"), PT_NUMBER);
    defineComplexParameter(5, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(6, StringComplex("2", "0"), PT_NUMBER);
}


void FractalsConfig::defineMixture()
{
    m_type = F_MIXTURE;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = (α(2z - z</big><sup>2</sup><big>) + β)</big><sup>2</sup></b>");
    setCommon(StringComplex("-1", "0"), "4", 5000, 10, FIXED);
    defineZ0(StringComplex("1", "0"));
    m_number_of_complex_parameters[m_type] = 2;
    defineComplexParameter(0, StringComplex("1", "0"), PT_IS_C);
    defineComplexParameter(1, StringComplex("1", "0"), PT_NUMBER);
}

void FractalsConfig::defineMixture2()
{
    m_type = F_MIXTURE_2;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = (α(z - z</big><sup>2</sup><big>) + β)</big><sup>3</sup></b>");
    setCommon(StringComplex("-1.75", "0"), "12", 5000, 10, FIXED);
    defineZ0(StringComplex("0.5", "0"));
    m_number_of_complex_parameters[m_type] = 2;
    defineComplexParameter(0, StringComplex("1", "0"), PT_IS_C);
    defineComplexParameter(1, StringComplex("1", "0"), PT_NUMBER);
}

void FractalsConfig::defineMixture3()
{
    m_type = F_MIXTURE_3;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = (α(z - z</big><sup>2</sup><big>) + β)</big><sup>4</sup></b>");
    setCommon(StringComplex("-1.75", "0"), "12", 5000, 10, FIXED);
    defineZ0(StringComplex("0.5", "0"));
    m_number_of_complex_parameters[m_type] = 2;
    defineComplexParameter(0, StringComplex("1", "0"), PT_IS_C);
    defineComplexParameter(1, StringComplex("1", "0"), PT_NUMBER);
}

void FractalsConfig::defineMixture4()
{
    m_type = F_MIXTURE_4;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big><br>"
        "<big>z = (α(z</big><sup>3</sup><big> - z</big><sup>4</sup><big>) + β)</big><sup>5</sup></b>");
    setCommon(StringComplex("-1.75", "0"), "12", 5000, 10, FIXED);
    defineZ0(StringComplex("0.5", "0"));
    m_number_of_complex_parameters[m_type] = 2;
    defineComplexParameter(0, StringComplex("1", "0"), PT_IS_C);
    defineComplexParameter(1, StringComplex("1", "0"), PT_NUMBER);
}

void FractalsConfig::definePrMandelbrot2()
{
    m_type = F_PR_MANDELBROT_2;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)<br>"
        "a = z</big><sup>2</sup><big> + α<br>"
        "b = z</big><sup>2</sup><big> + β<br>"
        "z = ((a + γ)</big><sup>-1</sup><big> + (b + δ)</big><sup>-1</sup><big>)</big><sup>-1</sup></b>");
    setCommon(StringComplex("-1.75", "0"), "12", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 4;
    defineComplexParameter(0, StringComplex("1", "0"), PT_IS_C);
    defineComplexParameter(1, StringComplex("1", "0"), PT_IS_C);
    defineComplexParameter(2, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex("-1", "0"), PT_NUMBER);
}

void FractalsConfig::definePrMandelbrot3()
{
    m_type = F_PR_MANDELBROT_3;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)<br>"
        "a = z</big><sup>2</sup><big> + α<br>"
        "b = z</big><sup>2</sup><big> + β<br>"
        "c = z</big><sup>2</sup><big> + γ<br>"
        "z = ((a + δ)</big><sup>-1</sup><big> + (b + ε)</big><sup>-1</sup><big>"
        " + (c + ζ)</big><sup>-1</sup><big>)</big><sup>-1</sup></b>");
    setCommon(StringComplex("-1.75", "0"), "12", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 6;
    defineComplexParameter(0, StringComplex("1", "0"), PT_IS_C);
    defineComplexParameter(1, StringComplex("1", "0"), PT_IS_C);
    defineComplexParameter(2, StringComplex("1", "0"), PT_IS_C);
    defineComplexParameter(3, StringComplex("-1", "0"), PT_NUMBER);
    defineComplexParameter(4, StringComplex("0", "0"), PT_NUMBER);
    defineComplexParameter(5, StringComplex("1", "0"), PT_NUMBER);
}

void FractalsConfig::definePrSingleFunction2()
{
    m_type = F_PR_SINGLE_FUNCTION_2;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)<br>"
        "a = F1(αz) + β<br>"
        "b = F2(γz) + δ<br>"
        "z = ((a + ε)</big><sup>-1</sup><big> + (b + ζ)</big><sup>-1</sup><big>)</big><sup>-1</sup></b>");
    setCommon(StringComplex("-1.75", "0"), "12", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 6;
    defineComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex("1", "0"), PT_IS_C);
    defineComplexParameter(2, StringComplex("1", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex("1", "0"), PT_IS_C);
    defineComplexParameter(4, StringComplex("-1", "0"), PT_NUMBER);
    defineComplexParameter(5, StringComplex("1", "0"), PT_NUMBER);
    m_number_of_complex_function_parameters[m_type] = 2;
    defineComplexFunctionParameter(0, CFP_POWER, "2");
    defineComplexFunctionParameter(1, CFP_POWER, "3");
}

void FractalsConfig::defineHop()
{
    m_type = F_HOP;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>z = transform(z)<br>"
            "x =  z</big><sub>r</sub><big><br>"
            "y =  z</big><sub>i</sub><big><br>"
            "a = y + B*signum(x)*f1(abs(C*x</big><sup>D</sup><big> + E))<br>"
            "y = A - x<br>"
            "z = a + yi + α</b>");
    setCommon(StringComplex(), "7", 5000, 10, UNTRANSFORMED);
    m_number_of_parameters[m_type] = 5;
    defineParameter(0, "0.4");
    defineParameter(1, "-1.0");
    defineParameter(2, "1.0");
    defineParameter(3, "1.0");
    defineParameter(4, "0.0");
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex(), PT_NUMBER);
    m_number_of_function_parameters[m_type] = 1;
    defineFunctionParameter(0, FP_POWER, "0.5");
}

void FractalsConfig::defineQuadrup_2()
{
    m_type = F_QUADRUP_2;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>z = transform(z)<br>"
            "x = z</big><sub>r</sub><big><br>"
            "y = z</big><sub>i</sub><big><br>"
            "p = log</big><sub>e</sub><big>(abs(Bx - C))<br>"
            "q = log</big><sub>e</sub><big>(abs(Cx - B))<br>"
            "a = y - signum(x)*sin(p)*atan(q</big><sup>2</sup><big>)<br>"
            "b = A - x<br>"
            "z = a + bi + α</b>");
    setCommon(StringComplex(), "200", 5000, 10, UNTRANSFORMED);
    m_number_of_parameters[m_type] = 3;
    defineParameter(0, "8.0");
    defineParameter(1, "1.0");
    defineParameter(2, "5.0");
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex(), PT_NUMBER);
    defineBailout(B_NONE);
    m_method[1][m_type] = "Mh";
    setColourScale(true, 100.0L);
    setSmooth(true,true);
    setAbsLog(true, true);
}

void FractalsConfig::defineThreeply()
{
    m_type = F_THREEPLY;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>z = transform(z)<br>"
            "x = z</big><sub>r</sub><big><br>"
            "y = z</big><sub>i</sub><big><br>"
            "a = y - signum(x)*abs(sin(x)*cos(B) + C - x*sin(A+B+C))<br>"
            "b = A - x<br>"
            "z = a + bi + α</b>");
    setCommon(StringComplex(), "300", 5000, 10, UNTRANSFORMED);
    m_limit[m_type] = 1600000.0L;
    m_number_of_parameters[m_type] = 3;
    defineParameter(0, "-55.0");
    defineParameter(1, "-1.0");
    defineParameter(2, "-5.0");
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex(), PT_NUMBER);
    defineBailout(B_NONE);
    m_method[1][m_type] = "Ml";
    setColourScale(true, 1000.0L);
    setSmooth(true,true);
    setAbsLog(true, true);
}

void FractalsConfig::defineThreeply2()
{
    m_type = F_THREEPLY_2;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>z = transform(z)<br>"
            "x = z</big><sub>r</sub><big><br>"
            "y = z</big><sub>i</sub><big><br>"
            "a = y - signum(x)*abs(sin(x)*cos(B) + C + x*sin(A+B+C))<br>"
            "b = A - x<br>"
            "z = a + bi + α</b>");
    setCommon(StringComplex(), "1000", 5000, 10, UNTRANSFORMED);
    m_limit[m_type] = 1600000.0L;
    m_number_of_parameters[m_type] = 3;
    defineParameter(0, "-55.0");
    defineParameter(1, "-1.0");
    defineParameter(2, "-5.0");
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex(), PT_NUMBER);
    defineBailout(B_NONE);
    m_method[1][m_type] = "Ml";
    setColourScale(true, 1000.0L);
    setSmooth(true,true);
    setAbsLog(true, true);
}

void FractalsConfig::defineChip()
{
    m_type = F_CHIP;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>z = transform(z)<br>"
            "x = z</big><sub>r</sub><big><br>"
            "y = z</big><sub>i</sub><big><br>"
            "p = log</big><sub>e</sub><big>(abs(Bx - C))<br>"
            "q = log</big><sub>e</sub><big>(abs(Cx - B))<br>"
            "a = y - signum(x)*cos(p</big><sup>2</sup><big>)*atan(q</big><sup>2</sup><big>)<br>"
            "b = A - x<br>"
            "z = a + bi + α</b>");
    setCommon(StringComplex(), "200", 50, 10, UNTRANSFORMED);
    m_number_of_parameters[m_type] = 3;
    defineParameter(0, "8.0");
    defineParameter(1, "1.0");
    defineParameter(2, "5.0");
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex(), PT_NUMBER);
    m_default_orbit_colour_type[m_type] = 'c';
    m_orbit_colour_type[m_type] = m_default_orbit_colour_type[m_type];
    m_calculating_area[m_type] = 2;
    defineBailout(B_NONE);
    setOrbitPlotting(true);
    
}

void FractalsConfig::defineGumowskiMira()
{
    m_type = F_GUMOWSKI_MIRA;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>z = transform(z)<br>"
            "x = z</big><sub>r</sub><big><br>"
            "y = z</big><sub>i</sub><big><br>"
            "a = By + (2(1 - A)x</big><sup>2</sup><big>)/(1 + x</big><sup>2</sup><big>)<br>"
            "b = Cx + (2(1 - A)x</big><sup>2</sup><big>)/(1 + x</big><sup>2</sup><big>)<br>"
            "z = a + bi + α</b>");
    setCommon(StringComplex(), "80", 5000, 10, UNTRANSFORMED);
    m_number_of_parameters[m_type] = 3;
    defineParameter(0, "0.2");
    defineParameter(1, "1.0");
    defineParameter(2, "-1.0");
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex(), PT_NUMBER);
    m_method[1][m_type] = "Ma";
    m_colour_scale[1][m_type] = 100.0L;
    m_abs_log[1][m_type] = true;
    m_smooth[1][m_type] = true;
    defineBailout(B_NONE);
}

void FractalsConfig::defineAttractorsSO()
{
    m_type = F_ATTRACTORS_SO;
    m_name[m_type] = fractalTypeToString(m_type);
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>a = Af1(By) + Cf2(Dx)</big><b><br>"
            "<b><big>b = Ef3(Fx) + Gf4(Hy)</big><b><br>"
            "<b><big>x = a</big></b><br>"
            "<b><big>y = b</big></b>");
    setCommon(StringComplex(), "6", 500000, 5, FIXED);
    setOrbitPlotting(true);
    m_number_of_parameters[m_type] = 8;
    defineParameter(0, "1");
    defineParameter(1, "2");
    defineParameter(2, "-1");
    defineParameter(3, "-2");
    defineParameter(4, "1");
    defineParameter(5, "2");
    defineParameter(6, "-1");
    defineParameter(7, "-2");
    m_number_of_function_parameters[m_type] = 4;
    defineFunctionParameter(0, FP_SIN);
    defineFunctionParameter(1, FP_COS);
    defineFunctionParameter(2, FP_SIN);
    defineFunctionParameter(3, FP_COS);
    defineZ0(StringComplex("0.5", "0"));
}

void FractalsConfig::defineHopSO()
{
    m_type = F_HOP_SO;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>a = y + B*signum(x)*f1(abs(C*x</big><sup>D</sup><big> + E))<br>"
            "y = A - x<br>"
            "x = a<b><big>");
    setCommon(StringComplex(), "7", 500000, 10, FIXED);
    m_number_of_parameters[m_type] = 5;
    defineParameter(0, "0.4");
    defineParameter(1, "-1.0");
    defineParameter(2, "1.0");
    defineParameter(3, "1.0");
    defineParameter(4, "0.0");
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex(), PT_NUMBER);
    m_number_of_function_parameters[m_type] = 1;
    defineFunctionParameter(0, FP_POWER, "0.5");
}

void FractalsConfig::defineQuadrup_2_SO()
{
    m_type = F_QUADRUP_2_SO;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>p = log</big><sub>e</sub><big>(abs(Bx - C))<br>"
            "q = log</big><sub>e</sub><big>(abs(Cx - B))<br>"
            "a = y - signum(x)*sin(p)*atan(q</big><sup>2</sup><big>)<br>"
            "b = A - x</big></b>");
    setCommon(StringComplex(), "200", 500000, 10, FIXED);
    m_number_of_parameters[m_type] = 3;
    defineParameter(0, "8.0");
    defineParameter(1, "1.0");
    defineParameter(2, "5.0");
    m_number_of_complex_parameters[m_type] = 1;
    defineComplexParameter(0, StringComplex(), PT_NUMBER);
}

void FractalsConfig::defineThreeplySO()
{
    m_type = F_THREEPLY_SO;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>a = y - signum(x)*abs(sin(x)*cos(B) + C - x*sin(A+B+C))<br>"
            "b = A - x"
            "x = a<br>"
            "y = b</big></b>");
    setCommon(StringComplex(), "1200", 500000, 10, FIXED);
    m_limit[m_type] = 1600000.0L;
    m_number_of_parameters[m_type] = 3;
    defineParameter(0, "-55.0");
    defineParameter(1, "-1.0");
    defineParameter(2, "-5.0");
}

void FractalsConfig::defineThreeply2_SO()
{
    m_type = F_THREEPLY_2_SO;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>a = y - signum(x)*abs(sin(x)*cos(B) + C + x*sin(A+B+C))<br>"
            "b = A - x<br>"
            "x = a<br>"
            "y = b</big></b>");
    setCommon(StringComplex(), "1200", 500000, 10, FIXED);
    m_limit[m_type] = 1600000.0L;
    m_number_of_parameters[m_type] = 3;
    defineParameter(0, "-55.0");
    defineParameter(1, "-1.0");
    defineParameter(2, "-5.0");
}

void FractalsConfig::defineChipSO()
{
    m_type = F_CHIP_SO;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>p = log</big><sub>e</sub><big>(abs(Bx - C))<br>"
            "q = log</big><sub>e</sub><big>(abs(Cx - B))<br>"
            "a = y - signum(x)*cos(p</big><sup>2</sup><big>)*atan(q</big><sup>2</sup><big>)<br>"
            "b = A - x<br>"
            "x = a<br>"
            "y = b</big></b>");
    setCommon(StringComplex(), "800", 500000, 10, FIXED);
    m_number_of_parameters[m_type] = 3;
    defineParameter(0, "8.0");
    defineParameter(1, "1.0");
    defineParameter(2, "5.0");
}

void FractalsConfig::defineGumowskiMiraSO()
{
    m_type = F_GUMOWSKI_MIRA_SO;
    m_formula[m_type] = QString::fromUtf8(
            "<b><big>a = By + (2(1 - A)x</big><sup>2</sup><big>)/(1 + x</big><sup>2</sup><big>)<br>"
            "b = Cx + (2(1 - A)x</big><sup>2</sup><big>)/(1 + x</big><sup>2</sup><big>)<br>"
            "x = a<br>"
            "y = b</big></b>");
    setCommon(StringComplex(), "80", 500000, 10, FIXED);
    m_number_of_parameters[m_type] = 3;
    defineParameter(0, "0.2");
    defineParameter(1, "1.0");
    defineParameter(2, "-1.0");
    defineZ0(StringComplex("12", "0"));
}

void FractalsConfig::defineMandelbrotDivision()
{
    m_type = F_MANDELBROT_DIVISION;
    m_formula[m_type] = QString::fromUtf8(
        "<b><big>z = transform(z)</big></b><br>"
        "<b><big>z = (z<sup>α</sup> + β)/(z<sup>γ</sup> + δ) + ε + ζ");
    setCommon(StringComplex("0.5", "0"), "4", 5000, 10, FIXED);
    m_number_of_complex_parameters[m_type] = 6;
    defineComplexParameter(0, StringComplex("10", "0"), PT_NUMBER);
    defineComplexParameter(1, StringComplex(), PT_IS_C);
    defineComplexParameter(2, StringComplex("8", "0"), PT_NUMBER);
    defineComplexParameter(3, StringComplex(), PT_IS_C);
    defineComplexParameter(4, StringComplex(), PT_IS_C);
    defineComplexParameter(5, StringComplex("-2", "0"), PT_NUMBER);
}

void FractalsConfig::setOrbitPlotting(bool plotting)
{
    m_orbit_plotting[m_type] = plotting;
}

bool FractalsConfig::isOrbitPlotting()
{
    return m_orbit_plotting[m_type];
}

bool FractalsConfig::isSingleOrbit()
{
    return ::isSingleOrbit(m_type);
}

void FractalsConfig::setCalculatingArea(unsigned int size)
{
    m_calculating_area[m_type] = size;
}

int FractalsConfig::getCalculatingArea()
{
    return m_calculating_area[m_type];
}

bool FractalsConfig::isJulia()
{
    bool is_julia = true;
    int parameters = getNumberOfComplexParameters();
    for (int i = 0; (i < parameters) && is_julia; i++)
    {
        is_julia = (is_julia && (getComplexParameterType(i) == PT_NUMBER));
    }
    return is_julia;
}

void FractalsConfig::setOrbitScale(long double scale)
{
    m_orbit_scale[m_type] = scale;
}

long double FractalsConfig::getOrbitScale()
{
    return (m_orbit_scale.count(m_type) == 0.0L ? 10.0L : m_orbit_scale[m_type]);
}

void FractalsConfig::setOrbitPlots(ORBIT_PLOTS value)
{
    m_orbit_plots[m_type] = value;
}

ORBIT_PLOTS FractalsConfig::getOrbitPlots()
{
    return ((m_orbit_plots.count(m_type) == 0) || !m_orbit_plotting[m_type] ? OP_ALL : m_orbit_plots[m_type]);
}

void FractalsConfig::setDensity(unsigned int value)
{
    m_density[m_type] = value;
}

unsigned int FractalsConfig::getDensity()
{
    return m_density[m_type];
}

int FractalsConfig::getWidth()
{
    return static_cast<int>(m_width);
}

int FractalsConfig::getHeight()
{
    return static_cast<int>(m_height);
}

void FractalsConfig::setStartOrbitIteration(int value)
{
    m_start_orbit_iteration[m_type] = value;
}

int FractalsConfig::getStartOrbitIteration()
{
    return m_start_orbit_iteration[m_type];
}

void FractalsConfig::setQuick(bool value)
{
    m_quick[m_type] = (isOrbitPlotting() ? false : value);
}

bool FractalsConfig::isQuick()
{
    return ((m_quick[m_type] || StaticCalculatingUnit::s_multi_precision) && !isOrbitPlotting());
}

const FractalConfig &FractalsConfig::getFractalConfig()
{
    FractalConfig fractal(m_type);
    m_fractal = fractal;
    m_fractal.setName(getName());
    m_fractal.setImageCentre(getCentre());
    m_fractal.setImageWidth(getCurrentWidth());
    m_fractal.setRotation(getRotation());
    m_fractal.setInitialZtype(getInitialValues());
    m_fractal.setInitialZ(getFixedInitialValue());
    m_fractal.setNumberOfParameters(getNumberOfParameters());
    m_fractal.setNumberOfComplexParameters(getNumberOfComplexParameters());
    m_fractal.setNumberOfFunctionParameters(getNumberOfFunctionParameters());
    m_fractal.setNumberOfComplexFunctionParameters(getNumberOfComplexFunctionParameters());
    for (int i = 0; i < MAX_PARAMETERS; i++)
    {
        m_fractal.setParameter(i, getParameter(i));
        m_fractal.setComplexParameter(i, getComplexParameter(i), getComplexParameterType(i));
        m_fractal.setFunctionParameter(i, getFunctionParameter(i));
        m_fractal.setComplexFunctionParameter(i, getComplexFunctionParameter(i));
    }
    m_fractal.setLimit(getLimit());
    m_fractal.setSelection(getSelection());
    m_fractal.setSelectLimit(getSelectLimit());
    m_fractal.setConvergent(isConvergent());
    m_fractal.setBailout(getBailout());
    int number_of_transforms = getNumberOfComplexPlaneTransforms();
    for (int i = 0; i < number_of_transforms; i++)
    {
        m_fractal.addComplexPlaneTransform(getComplexPlaneTransform(i));
    }
    int sets = getNumberOfTransformSets();
    for (int set = 0; set < sets; set++)
    {
        int number_of_transforms = getNumberOfTransforms(set);
        m_fractal.addTransformSet(set);
        for (int i = 0; i < number_of_transforms; i++)
        {
            m_fractal.addTransform(set, getTransform(set, i));
        }
    }
    m_fractal.setTransformSequence(getTransformSequence());
    m_fractal.setWidth(getWidth());
    m_fractal.setHeight(getHeight());
    m_fractal.setCentre(getCentre());
    setInner(false);
    m_fractal.setAbsLog(false, getAbsLog());
    m_fractal.setSmooth(false, getSmooth());
    m_fractal.setScale(false, this->getColourScale());
    m_fractal.setMethod(false, getMethod());
    m_fractal.setColourMap(m_colour_maps->getColourMap(getColourMap()), false);
    m_fractal.setRedOffset(getRedOffset(), false);
    m_fractal.setGreenOffset(getGreenOffset(), false);
    m_fractal.setBlueOffset(getBlueOffset(), false);
    m_fractal.setComponentOrder(getComponentOrder(false), false);
    setInner(true);
    m_fractal.setAbsLog(true, getAbsLog());
    m_fractal.setSmooth(true, getSmooth());
    m_fractal.setScale(true, getColourScale());
    m_fractal.setMethod(true, getMethod());
    m_fractal.setColourMap(m_colour_maps->getColourMap(getColourMap()), true);
    m_fractal.setRedOffset(getRedOffset(), true);
    m_fractal.setGreenOffset(getGreenOffset(), true);
    m_fractal.setBlueOffset(getBlueOffset(), true);
    m_fractal.setComponentOrder(getComponentOrder(true), true);
    // Orbit plotting
    m_fractal.setOrbitPlotting(isOrbitPlotting());
    if (isOrbitPlotting() || isSingleOrbit())
    {
        if (!isSingleOrbit())
        {
            m_fractal.setOrbitPlot(getOrbitPlots());
            m_fractal.setOmit(getStartOrbitIteration());
            m_fractal.setArea(getCalculatingArea());
            m_fractal.setDensity(getDensity());
        }
        m_fractal.setOrbitScale(getOrbitScale());
        m_fractal.setOrbitColourType(getOrbitColourType());
        m_fractal.setOrbitColourInterval(getOrbitColourInterval());
        m_fractal.setOrbitRedOffset(getRedOffset());
        m_fractal.setOrbitGreenOffset(getGreenOffset());
        m_fractal.setOrbitBlueOffset(getBlueOffset());
        m_fractal.setOrbitBackground(getOrbitBackground());
        m_fractal.enableOrbitBackground(hasOrbitBackground());
        m_fractal.setComponentOrder(getComponentOrder(), false);
   }
    if (m_type == F_LYAPUNOV)
    {
        m_fractal.setLyapunovSequence(getLyapunovSequence());
        m_fractal.setSettlingCycles(getSettlingCycles());
        m_fractal.setCalculatingCycles(getCalculatingCycles());
    }
    m_fractal.setPrecision(getPrecision());
    return m_fractal;
}

void FractalsConfig::MetaData(QImage& image)
{
    QString program = "saturn" + QString::number(LEVEL);
    image.setText("program", program);
    if (GetFractalType() == F_LYAPUNOV)
    {
        addLyapunovMetadata(image);
    }
    else
    {
        addBailoutFractalMetadata(image);
    }
}

void FractalsConfig::addBailoutFractalMetadata(QImage& image)
{
    image.setText("fractal_type", QString::number(static_cast<int>(GetFractalType())));
    image.setText("fractal_name", getName());
    image.setText("z0", QString::fromStdString(GetInitialValuesAsString()));
    image.setText("centre_r", QString::fromStdString(getCentre().r));
    image.setText("centre_i", QString::fromStdString(getCentre().i));
    image.setText("longside", QString::fromStdString(getCurrentWidth()));
    image.setText("rotation", QString::number(getRotation()));
    image.setText("convergent", QString::number(static_cast<unsigned int>(isConvergent())));
    image.setText("bailout", QString::number(static_cast<unsigned int>(getBailout())));
    image.setText("limit", longdoubleToQString(getLimit()));
    image.setText("max_iterations", QString::number(getMaxIterations()));
    image.setText("orbit", QString::number(static_cast<unsigned int>(isOrbitPlotting())));
    image.setText("precision", QString::number(static_cast<int>(getPrecision())));
    if (isOrbitPlotting())
    {
        image.setText("omit", QString::number(getStartOrbitIteration()));
        image.setText("area", QString::number(getCalculatingArea()));
        image.setText("plot", QString::number(static_cast<int>(getOrbitPlots())));
        image.setText("density", QString::number(getDensity()));
    }
    addParameterMetadata(image);
    addTransformsMetadata(image);
    image.setText("select", QString::fromStdString(getSelection()));
    image.setText("select_limit", longdoubleToQString(getSelectLimit()));
    bool orbit = isOrbitPlotting() || isSingleOrbit();
    (orbit ? addOrbitColoursMetadata(image) : addColoursMetadata(image));
}

void FractalsConfig::addColoursMetadata(QImage& image)
{
    setInner(false);
    std::string method = getMethod();
    image.setText("method", QString::fromStdString(method));
    if (method[0] != 'f')
    {
        image.setText("smooth", QString::number(static_cast<int>(getSmooth())));
        if (method[0] != 'i')
        {
            image.setText("scale", longdoubleToQString(getColourScale()));
        }
        // due to change
        image.setText("red_offset", QString::number(getRedOffset()));
        image.setText("green_offset", QString::number(getGreenOffset()));
        image.setText("blue_offset", QString::number(getBlueOffset()));
        image.setText("order", QString::number(static_cast<int>(getComponentOrder())));
        image.setText("abslog", QString::number(static_cast<int>(getAbsLog())));
        addColourMapMetadata(image, "", getColourMap());
    }
    setInner(true);
    method = getMethod();
    image.setText("inner_method", QString::fromStdString(method));
    if (method[0] != 'f')
    {
        image.setText("inner_smooth", QString::number(static_cast<int>(getSmooth())));
        if (method[0] != 'i')
        {
            image.setText("inner_scale", longdoubleToQString(getColourScale()));
        }
        image.setText("inner_red_offset", QString::number(getRedOffset()));
        image.setText("inner_green_offset", QString::number(getGreenOffset()));
        image.setText("inner_blue_offset", QString::number(getBlueOffset()));
        image.setText("inner_order", QString::number(static_cast<int>(getComponentOrder())));
        image.setText("inner_abslog", QString::number(static_cast<int>(getAbsLog())));
        addColourMapMetadata(image, "inner_", getColourMap());
    }
}

void FractalsConfig::addOrbitColoursMetadata(QImage& image)
{
    QChar ch(getOrbitColourType());
    QString method(ch);
    image.setText("method", method);
    image.setText("interval", QString::number(getOrbitColourInterval()));
    image.setText("scale", longdoubleToQString(getOrbitScale()));
    image.setText("order", QString::number(static_cast<int>(getComponentOrder())));
    image.setText("red_offset", QString::number(getRedOffset()));
    image.setText("green_offset", QString::number(getGreenOffset()));
    image.setText("blue_offset", QString::number(getBlueOffset()));
    if (hasOrbitBackground())
    {
        QColor colour = getOrbitBackground();
        KeyString keys;
        keys.SetKey("red", colour.red());
        keys.SetKey("green", colour.green());
        keys.SetKey("blue", colour.blue());
        image.setText("background", QString::fromStdString(keys.String()));
    }
    addColourMapMetadata(image, "", getColourMap());
}

void FractalsConfig::addColourMapMetadata(QImage& image, QString prefix, QString map_name)
{
    ColourMap &colours = m_colour_maps->getColourMap(map_name);
    ColourMap::MAP_TYPE type = colours.getType();
    image.setText(prefix + "colourmap", map_name);
    image.setText(prefix + "colour_map_type", QString::number(static_cast<int>(type)));
    if (type == ColourMap::CM_MANUAL)
    {
        int count = 0;
        const ColoursMap &all_colours = colours.getColoursMap();
        int size = all_colours.size();
        image.setText(prefix + "number_of_colours", QString::number(size));
        for (auto it = all_colours.begin(); it != all_colours.end(); it++, count++)
        {
            int index = it->first;
            QColor c = it->second;
            KeyString metakeys;
            metakeys.SetKey("index", index);
            metakeys.SetKey("red", c.red());
            metakeys.SetKey("green", c.green());
            metakeys.SetKey("blue", c.blue());
            image.setText(prefix + "colour" + QString::number(count), QString::fromStdString(metakeys.String()));
        }
    }
    else if (type == ColourMap::CM_COMPONENT)
    {
        addComponentColours(image, RGB_RED, prefix, colours);
        addComponentColours(image, RGB_GREEN, prefix, colours);
        addComponentColours(image, RGB_BLUE, prefix, colours);
    }
    else
    {
        // auto colour meta data
        Waveform::AutoColour auto_colour;
        for (int i = 0; i < 3; i++)
        {
            colours.getAutoColour(static_cast<RGB>(i), auto_colour);
            KeyString metakeys;
            metakeys.SetKey("hoffset", auto_colour.hoffset);
            metakeys.SetKey("voffset", auto_colour.voffset);
            metakeys.SetKey("maximum", auto_colour.maximum);
            metakeys.SetKey("wave", static_cast<int>(auto_colour.wave));
            metakeys.SetKey("cycles", auto_colour.cycles);
            image.setText(prefix + "colour" + QString::number(i), QString::fromStdString(metakeys.String()));
        }
    }
}

void FractalsConfig::addComponentColours(QImage& image, RGB colour, const QString& prefix, ColourMap& colours)
{
    ::IntMap map;
    QString str(prefix);
    switch (colour)
    {
    case RGB_RED:
        map = colours.getRedMap();
        str += "red";
        break;
    case RGB_GREEN:
        map = colours.getGreenMap();
        str += "green";
        break;
    case RGB_BLUE:
        map = colours.getBlueMap();
        str += "blue";
        break;
    }
    image.setText(str + "_colours", QString::number(map.size()));
    int count = 0;
    for (auto it = map.begin(); it != map.end(); it++, count++)
    {
        KeyString metakeys;
        metakeys.SetKey("index", it->first);
        metakeys.SetKey("value", it->second);
        image.setText(str + QString::number(count), QString::fromStdString(metakeys.String()));
    }
}

void FractalsConfig::addParameterMetadata(QImage& image)
{
    image.setText("modifiers", QString::number(getNumberOfComplexParameters()));
    for (unsigned int i = 0; i < getNumberOfComplexParameters(); i++)
    {
        QString real = "p" + QString::number(i) + "r";
        QString imag = "p" + QString::number(i) + "i";
        QString is_c = "p" + QString::number(i) + "c";
        image.setText(real, QString::fromStdString(getComplexParameter(i).r));
        image.setText(imag, QString::fromStdString(getComplexParameter(i).i));
        image.setText(is_c, QString::number(static_cast<int>(getComplexParameterType(i))));
    }
    image.setText("modifiers2", QString::number(getNumberOfParameters()));
    for (unsigned int i = 0; i < getNumberOfParameters(); i++)
    {
        QString key = "p" + QString::number(i);
        image.setText(key, QString::fromStdString(getParameter(i)));
    }
    image.setText("modifiers3", QString::number(getNumberOfFunctionParameters()));
    for (unsigned int i = 0; i < getNumberOfFunctionParameters(); i++)
    {
        QString key = "f" + QString::number(i);
        image.setText(key, QString::fromStdString(getFunctionParameter(i)));
    }
    image.setText("modifiers4", QString::number(getNumberOfComplexFunctionParameters()));
    for (unsigned int i = 0; i < getNumberOfComplexFunctionParameters(); i++)
    {
        QString key = "cf" + QString::number(i);
        image.setText(key, QString::fromStdString(getComplexFunctionParameter(i)));
    }
}

void FractalsConfig::addTransformsMetadata(QImage& image)
{
    image.setText("sequence", QString::fromStdString(getTransformSequence()));
    addComplexPlaneTransformsMetadata(image);
    int sets = getNumberOfTransformSets();
    image.setText("transform_sets", QString::number(sets));
    char id = 'a';
    for (int set = 0; set < sets; set++)
    {
        unsigned int transforms = getNumberOfTransforms(set);
        QString base_string = "set" + QString::number(set);
        image.setText(base_string, QString::number(transforms));
        for (unsigned int i = 0; i < transforms; i++)
        {
            QString transform = base_string + "t" + QString::number(i);
            image.setText(transform, QString::fromStdString(getTransform(set, i)));
        }
        id++;
    }
}

void FractalsConfig::addComplexPlaneTransformsMetadata(QImage& image)
{
    unsigned int transforms = getNumberOfComplexPlaneTransforms();
    QString base_string = "cp";
    image.setText("set_cp", QString::number(transforms));
    for (unsigned int i = 0; i < transforms; i++)
    {
        QString transform = base_string + QString::number(i) + "t";
        image.setText(transform, QString::fromStdString(getComplexPlaneTransform(i)));
    }
}

void FractalsConfig::addLyapunovMetadata(QImage& image)
{
    image.setText("fractal_type", QString::number(static_cast<int>(GetFractalType())));
    image.setText("fractal_name", "\"" + getName() + "\"");
    image.setText("centre_r", QString::fromStdString(getCentre().r));
    image.setText("centre_i", QString::fromStdString(getCentre().i));
    image.setText("longside", QString::fromStdString(getCurrentWidth()));
    image.setText("rotation", QString::number(getRotation()));
    image.setText("sequence", QString::fromStdString(getLyapunovSequence()));
    image.setText("settling_cycles", QString::number(getSettlingCycles()));
    image.setText("calculating_cycles", QString::number(getCalculatingCycles()));
    addColoursMetadata(image);
}

void FractalsConfig::setComponentOrder(COMPONENT_ORDER order, bool inner)
{
    if (order > CO_BGR)
    {
        order = CO_RGB;
    }
    m_order[(inner ? 1 : 0)][m_type] = order;
}

COMPONENT_ORDER FractalsConfig::getComponentOrder(bool inner)
{
    if (isOrbitPlotting() || isSingleOrbit())
    {
        return m_orbit_order[m_type];
    }
    else
    {
        return m_order[(inner ? 1 : 0)][m_type];
    }
}

void FractalsConfig::setComponentOrder(COMPONENT_ORDER order)
{
    if (order > CO_BGR)
    {
        order = CO_RGB;
    }
    if (isOrbitPlotting() || isSingleOrbit())
    {
        m_orbit_order[m_type] = order;
    }
    else
    {
        m_order[m_index][m_type] = order;
    }
}

COMPONENT_ORDER FractalsConfig::getComponentOrder()
{
    if (isOrbitPlotting() || isSingleOrbit())
    {
        return m_orbit_order[m_type];
    }
    else
    {
        return m_order[m_index][m_type];
    }
}

void FractalsConfig::setRedOffset(unsigned int value, bool inner)
{
    m_red_offset[(inner ? 1 : 0)][m_type] = (value % 512);
}

void FractalsConfig::setGreenOffset(unsigned int value, bool inner)
{
    m_green_offset[(inner ? 1 : 0)][m_type] = (value % 512);
}

void FractalsConfig::setBlueOffset(unsigned int value, bool inner)
{
    m_blue_offset[(inner ? 1 : 0)][m_type] = (value % 512);
}

void FractalsConfig::setRedOffset(unsigned int value)
{
    if (isOrbitPlotting() || isSingleOrbit())
    {
        m_red_orbit_offset[m_type] = (value % 512);
    }
    else
    {
        m_red_offset[m_index][m_type] = (value % 512);
    }
}

void FractalsConfig::setGreenOffset(unsigned int value)
{
    if (isOrbitPlotting() || isSingleOrbit())
    {
        m_green_orbit_offset[m_type] = (value % 512);
    }
    else
    {
        m_green_offset[m_index][m_type] = (value % 512);
    }
}

void FractalsConfig::setBlueOffset(unsigned int offset)
{
    if (isOrbitPlotting() || isSingleOrbit())
    {
        m_blue_orbit_offset[m_type] = (offset % 512);
    }
    else
    {
        m_blue_offset[m_index][m_type] = (offset % 512);
    }
}

unsigned int FractalsConfig::getRedOffset(bool inner)
{
    if (isOrbitPlotting() || isSingleOrbit())
    {
        return m_red_orbit_offset[m_type];
    }
    else
    {
        return m_red_offset[(inner ? 1 : 0)][m_type];
    }
}

unsigned int FractalsConfig::getGreenOffset(bool inner)
{
    if (isOrbitPlotting() || isSingleOrbit())
    {
        return m_green_orbit_offset[m_type];
    }
    else
    {
        return m_green_offset[(inner ? 1 : 0)][m_type];
    }
}

unsigned int FractalsConfig::getBlueOffset(bool inner)
{
    if (isOrbitPlotting() || isSingleOrbit())
    {
        return m_blue_orbit_offset[m_type];
    }
    else
    {
        return m_blue_offset[(inner ? 1 : 0)][m_type];
    }
}

unsigned int FractalsConfig::getRedOffset()
{
    return (isOrbitPlotting() || isSingleOrbit() ? m_red_orbit_offset[m_type] : m_red_offset[m_index][m_type]);
}

unsigned int FractalsConfig::getGreenOffset()
{
    return (isOrbitPlotting() || isSingleOrbit() ? m_green_orbit_offset[m_type] : m_green_offset[m_index][m_type]);
}

unsigned int FractalsConfig::getBlueOffset()
{
    return (isOrbitPlotting() || isSingleOrbit() ? m_blue_orbit_offset[m_type] : m_blue_offset[m_index][m_type]);
}

void FractalsConfig::setOrbitBackground(const QColor& colour)
{
    m_background_colour[m_type] = colour;
}

void FractalsConfig::enableOrbitBackground(bool value)
{
    m_has_orbit_background[m_type] = value;
}

const QColor &FractalsConfig::getOrbitBackground()
{
    return m_background_colour[m_type];
}

bool FractalsConfig::hasOrbitBackground()
{
    return m_has_orbit_background[m_type];
}

int FractalsConfig::getPrecision()
{
    return m_precision[m_type];
}

void FractalsConfig::setPrecision(int value)
{
    m_precision[m_type] = value;
}

//==============================================================================
// Utility methods
//==============================================================================

std::string FractalsConfig::GetInitialValuesAsString()
{
    KeyString keys;
    keys.SetKey("type", static_cast<int>(m_zero_initial_values[m_type]));
    if (m_zero_initial_values[m_type] == FIXED)
    {
        keys.SetKey("r", m_z0[m_type].r);
        keys.SetKey("i", m_z0[m_type].i);
    }
    return keys.String();
}

std::string FractalsConfig::colourSignature()
{
    std::string signature;
    if (isOrbitPlotting() || isSingleOrbit())
    {
        char ch = getOrbitColourType();
        auto type = static_cast<ORBIT_COLOUR>(ch - 'a');
        KeyString keys;
        keys.SetKey("method", std::string(1, getOrbitColourType()));
        keys.SetKey("map", getColourMap().toStdString());
        keys.SetKey("order", static_cast<int>(getComponentOrder()));
        switch (type)
        {
        case OC_SQRT:
        case OC_LOG:
            keys.SetKey("scale", getOrbitScale());
            break;
        case OC_AVERAGE:
            keys.SetKey("interval", getOrbitColourInterval());
            break;
        default:
            break;
        }
        keys.SetKey("red_offset", static_cast<int>(getRedOffset(false)));
        keys.SetKey("green_offset", static_cast<int>(getGreenOffset(false)));
        keys.SetKey("blue_offset", static_cast<int>(getBlueOffset(false)));
        if (hasOrbitBackground())
        {
            keys.SetKey("background", getOrbitBackground().name().toStdString());
        }
        // background colour ....
        signature = keys.String();
    }
    else
    {
        KeyString keys[2];
        for (int i = 0; i < 2; i++)
        {
            signature += m_method[i][m_type];
            if (m_method[i][m_type][0] != 'f')
            {
                signature += ":";
                keys[i].SetKey("smooth", static_cast<int>(m_smooth[i][m_type]));
                if (m_method[i][m_type][0] != 'i')
                {
                    keys[i].SetKey("abslog", static_cast<int>(m_abs_log[i][m_type]));
                }
                keys[i].SetKey("map", m_colour_map[i][m_type].toStdString());
                keys[i].SetKey("order", static_cast<int>(m_order[i][m_type]));
                keys[i].SetKey("scale", m_colour_scale[i][m_type]);
                keys[i].SetKey("red_offset", static_cast<int>(m_red_offset[i][m_type]));
                keys[i].SetKey("green_offset", static_cast<int>(m_green_offset[i][m_type]));
                keys[i].SetKey("blue_offset", static_cast<int>(m_blue_offset[i][m_type]));
                signature += keys[i].String();
            }
            signature += ":";
            signature += m_select[m_type];
            signature += ":";
            signature += longdoubleToString(m_select_limit[m_type]);
        }
    }
    return signature;
}