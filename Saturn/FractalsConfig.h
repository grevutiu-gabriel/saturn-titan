//
// File:   FractalsConfig.h
// Author: M.R.Eggleston
//
// Created on 16 November 2009, 10:38
//
// Renamed 19th April 2012, formerly FractalConfig.h

//
// This Class uses a configuration file in a hidden directory in the user's
// home directory i.e.
//
// ~/.Saturn/config.xml
//

#pragma once

#ifdef NOT_MOC
#include <boost/shared_ptr.hpp>
#endif
#include "ldcomplex.h"
#include <map>
#include <string>
#include <QImage>
#include <QString>
#include "ColourMaps.h"
#include "FractalConfig.h"
#include "TypesAndConstants.h"

class FractalsConfig
{
public:
    struct FractalId
    {
        FRACTAL_TYPE type;
        QString name;
    };
        
    typedef std::vector<FractalId> VectorFractalId;

    FractalsConfig();

    void MetaData(QImage& image);

    VectorFractalId &getAllFractals();
    
    const FractalConfig &getFractalConfig();

    void SetFractal(FractalConfig& f);
    void SetFractalType(FRACTAL_TYPE value);
    FRACTAL_TYPE GetFractalType();

    // Fractal parameters
    void setLimit(long double value);
    long double getLimit();

    void setComplexParameter(int index, const StringComplex &value, PARAMETER_TYPE type);
    void setComplexParameterType(int index, PARAMETER_TYPE type);
    const StringComplex &getComplexParameter(int index);
    PARAMETER_TYPE getComplexParameterType(int index);
    void setParameter(int index,const std::string &value);
    const std::string &getParameter(int index);
    void setFunctionParameter(int index, const std::string &f);
    std::string getFunctionParameter(int index);
    void setComplexFunctionParameter(int index, const std::string &f);
    std::string getComplexFunctionParameter(int index);

    void resetFractalParameters();
    void resetLyapunovParameters();
    //
    unsigned int getNumberOfComplexParameters();
    unsigned int getNumberOfParameters();
    unsigned int getNumberOfFunctionParameters();
    unsigned int getNumberOfComplexFunctionParameters();
    bool hasParameters();
    //
    const QString &getLyapunovFormula();
    const QString &getFormula();
    const QString &getName();
    //
    void defaultStartingComplexPlane();
    //
    void setStartingCentre(const StringComplex &value);
    void setStartingWidth(const std::string &value);
    void setStartingRotation(const unsigned int value);
    const StringComplex &getStartingCentre();
    const std::string &getStartingWidth();
    int getStartingRotation();
    //
    void setCentre(const StringComplex &value);
    void setCentre(const StringComplex &value, bool& changed);
    void setCurrentWidth(const std::string &value);
    void setRotation(const int value);
    const StringComplex &getCentre();
    const std::string &getCurrentWidth();
    int getRotation();

    // Colouring
    void setColourMap(const QString& id);
    void setColourMap(const QString& id, bool inner);
    QString &getColourMap();
    QString &getColourMap(bool inner);
    void setSelection(const std::string &sel);
    const std::string &getSelection();
    void setSelectLimit(long double limit);
    long double getSelectLimit();
    void setMethod(const std::string &method);
    void setMethod(bool inner, const std::string &method);
    const std::string &getMethod();
    const std::string &getMethod(bool inner);
    void setColourScale(long double divisions);
    void setColourScale(bool  inner, long double scale);
    long double getColourScale();
    void setOrbitScale(long double scale);
    long double getOrbitScale();
    void setSmooth(bool value);
    void setSmooth(bool inner, bool value);
    bool getSmooth();
    void setAbsLog(bool value);
    void setAbsLog(bool inner, bool value);
    bool getAbsLog();

    void setMaxIterations(int value);
    int getMaxIterations();
    void setDefaultMaxIterations();
    unsigned int getIterationStepSize();
    //
    void setInitialValuesFromString(const std::string value);
    void setInitialValues(INITIAL_VALUE value);
    void setFixedInitialValue(const StringComplex &value);
    INITIAL_VALUE getInitialValues();
    INITIAL_VALUE getDefaultInitialValues();
    const StringComplex &getDefaultFixedInitialValues();
    const StringComplex &getFixedInitialValue();
    // Current fractal dimensions - not tied to fractal type.
    void setWidth(unsigned int value);
    long double width();
    int getWidth();
    void setHeight(unsigned int value);
    long double height();
    int getHeight();
    //
    const std::string& getLyapunovSequence();
    unsigned int getSettlingCycles();
    unsigned int getCalculatingCycles();
    void setLyapunovSequence(const std::string &sequence);
    void setSettlingCycles(unsigned int value);
    void setCalculatingCycles(unsigned int value);

    int getOrbitColourInterval();
    char getOrbitColourType();
    void setOrbitColourInterval(unsigned int value);
    void setOrbitColourType(char value);

    void setOrbitPlotting(bool plotting);
    bool isOrbitPlotting();
    bool isSingleOrbit();
    void setStartOrbitIteration(int value);
    int getStartOrbitIteration();
    
    bool isBailoutFractal();

    void setInner(bool inner);
    bool isInner();
    
    bool isJulia();

    void setBailout(BAILOUT value);
    BAILOUT getBailout();
    void setConvergent(bool value);
    bool isConvergent();

    bool transformsDefined();
    int getNumberOfComplexPlaneTransforms();
    void setComplexPlaneTransform(int i, const std::string &transform);
    std::string getComplexPlaneTransform(int i);
    void addComplexPlaneTransform(const std::string &transform);
    void swapComplexPlaneTransforms(int a, int b); 
    void deleteComplexPlaneTransforms();
    int getNumberOfTransformSets();
    int getNumberOfTransforms(int set);
    void setTransform(int set, int i, const std::string &transform);
    std::string getTransform(int set, int i);
    void setTransformSequence(const std::string &seq);
    void addTransform(int set, const std::string &transform);
    void addTranformSet();
    void deleteTransformSet(size_t set);
    void swapTransforms(int set, int a, int b); 
    void deleteTransform(int set, size_t pos);
    void deleteComplexPlaneTransform(size_t pos);
    void deleteTransforms();
    const std::string &getTransformSequence();
    
    void setCalculatingArea(unsigned int size);
    int getCalculatingArea();
    void setOrbitPlots(ORBIT_PLOTS value);
    ORBIT_PLOTS getOrbitPlots();
    void setDensity(unsigned int value);
    unsigned int getDensity();
    
    void setQuick(bool value);
    bool isQuick();

    void setComponentOrder(COMPONENT_ORDER order, bool inner);
    COMPONENT_ORDER getComponentOrder(bool inner);
    void setComponentOrder(COMPONENT_ORDER order);
    COMPONENT_ORDER getComponentOrder();
    void setRedOffset(unsigned int red, bool inner);
    void setGreenOffset(unsigned int green, bool inner);
    void setBlueOffset(unsigned int blue, bool inner);
    void setRedOffset(unsigned int red);
    void setGreenOffset(unsigned int green);
    void setBlueOffset(unsigned int blue);
    unsigned int getRedOffset(bool inner);
    unsigned int getGreenOffset(bool inner);
    unsigned int getBlueOffset(bool inner);
    unsigned int getRedOffset();
    unsigned int getGreenOffset();
    unsigned int getBlueOffset();
    void setOrbitBackground(const QColor& colour);
    void enableOrbitBackground(bool value);
    const QColor &getOrbitBackground();
    bool hasOrbitBackground();
    int getPrecision();
    void setPrecision(int value);
    
    std::string colourSignature();
    
private:
    typedef std::map<FRACTAL_TYPE, LongComplex> ComplexMap;
    typedef std::map<FRACTAL_TYPE, StringComplex> StringComplexMap;
    typedef std::map<int, ComplexParameter> StringComplexParameterMap;
    typedef std::map<FRACTAL_TYPE, StringComplexParameterMap> StringComplexParameterMapMap;
    typedef std::map<FRACTAL_TYPE, QString> QStringMap;
    typedef std::map<FRACTAL_TYPE, std::string> StdStringMap;
    typedef std::map<FRACTAL_TYPE, long double> LongDoubleMap;
    typedef std::map<int, std::string> ParameterMap;
    typedef std::map<FRACTAL_TYPE, ParameterMap> ParameterMapMap;
    typedef std::map<FRACTAL_TYPE, unsigned int> UintMap;
    typedef std::map<FRACTAL_TYPE, int> IntMap;
    typedef std::map<FRACTAL_TYPE, bool> BoolMap;
    typedef std::map<FRACTAL_TYPE, char> CharMap;
    typedef std::map<FRACTAL_TYPE, BAILOUT> BailoutMap;
    typedef std::vector<std::string> TransformVector;
    typedef std::map<FRACTAL_TYPE, TransformVector> TransformVectorMap;
    typedef std::vector<TransformVector> TransformVectorVector;
    typedef std::map<FRACTAL_TYPE, TransformVectorVector> TransformVectorVectorMap;
    typedef std::map<FRACTAL_TYPE, INITIAL_VALUE> InitialValueMap;
    typedef std::map<int, std::string> ParameterStringMap;
    typedef std::map<FRACTAL_TYPE, ParameterStringMap> FunctionParameterMapMap;
    typedef std::map<FRACTAL_TYPE, ParameterStringMap> ComplexFunctionParameterMapMap;
    typedef std::map<FRACTAL_TYPE, ORBIT_PLOTS> OrbitPlotsMap;
    typedef std::map<FRACTAL_TYPE, FractalConfig> FractalConfigMap;
    typedef std::map<FRACTAL_TYPE, COMPONENT_ORDER> ComponentOrderMap;
    typedef std::map<FRACTAL_TYPE, QColor> QColorMap;

    void setCommon(const StringComplex& centre,
                   const std::string& side,
                   int iterations,
                   int step_size,
                   INITIAL_VALUE init_type);
    void defineComplexParameter(int index, const StringComplex &value, PARAMETER_TYPE type);
    void defineParameter(int index, const std::string &value);
    void defineFunctionParameter(int index, FUNCTION_PARAMETER f, const std::string &p = "");
    void defineComplexFunctionParameter(int index, COMPLEX_FUNCTION_PARAMETER f, const std::string &p = "");
    void defineBailout(BAILOUT type);
    void defineZ0(const StringComplex &z);

    void defineMandelbrot();
    void defineQuadratic();
    void defineCubic();
    void defineAlmostCubic();
    void defineSingleFunction();
    void defineZcpac();
    void defineTwoFunctionProduct();
    void defineCpowerZ();
    void defineUnnamed();
    void defineZpowerTancz();
    void defineCombination();
    void defineTzaccp();
    void defineBiomorph1();
    void defineBiomorph2();
    void defineBiomorph3();
    void defineBiomorph4();
    void defineBiomorph5();
    void defineNova();
    void defineNova1();
    void defineNova2();
    void defineMagnet();
    void defineMagnet2();
    void defineZazbcgd();
    void defineCombination2();
    void defineSqrtCP();
    void defineUnnamed2();
    void defineQuartic();
    void defineQuintic();
    void defineHexic();
    void defineHeptic();
    void defineOctic();
    void defineZcpTanz();
    void defineLyapunov();
    void defineCompasses();
    void defineRealNumberMandelbrot();
    void defineHybrid();
    void definePickoverPopcorn4Function();
    void defineZduccpac();
    void defineMallard();
    void definePickoverPopcorn6Function();
    void defineTzcpac();
    void defineTmallard();
    void defineFzcpac();
    void defineFtzcpac();
    void defineZaccp();
    void defineCczcpazcp();
    void defineOnion4F();
    void defineCombination3();
    void defineC2mfczac();
    void defineC2dfczac();
    void defineSingle3fOnion();
    void defineDouble3fOnionM();
    void defineDouble3fOnionD();
    void defineM3();
    void defineM4();
    void defineM5();
    void defineM6();
    void defineM7();
    void defineM8();
    void defineM9();
    void defineM10();
    void defineMandelbrotDivision();
    void defineAttractors();
    void defineGeneralMixture();
    void defineMixture();
    void defineMixture2();
    void defineMixture3();
    void defineMixture4();
    void definePrMandelbrot2();
    void definePrMandelbrot3();
    void definePrSingleFunction2();
    void defineHop();
    void defineQuadrup_2();
    void defineThreeply();
    void defineThreeply2();
    void defineChip();
    void defineGumowskiMira();
    void defineAttractorsSO();
    void defineHopSO();
    void defineQuadrup_2_SO();
    void defineThreeplySO();
    void defineThreeply2_SO();
    void defineChipSO();
    void defineGumowskiMiraSO();

    void addBailoutFractalMetadata(QImage& image);
    void addLyapunovMetadata(QImage& image);
    void addColoursMetadata(QImage& image);
    void addOrbitColoursMetadata(QImage& image);
    void addColourMapMetadata(QImage& image, QString prefix, QString map_name);
    void addComponentColours(QImage& image, RGB colour, const QString& prefix, ColourMap& map);
    void addParameterMetadata(QImage& image);
    void addComplexPlaneTransformsMetadata(QImage& image);
    void addTransformsMetadata(QImage& image);
    
    std::string GetInitialValuesAsString();


    static UintMap m_number_of_complex_parameters;
    static UintMap m_number_of_parameters;
    static UintMap m_number_of_function_parameters;
    static UintMap m_number_of_complex_function_parameters;
    
    static StringComplexParameterMapMap m_complex_parameters;
    static StringComplexParameterMapMap m_default_complex_parameters;
    static ParameterMapMap m_parameters;
    static ParameterMapMap m_default_parameters;
    static FunctionParameterMapMap m_functions;
    static FunctionParameterMapMap m_default_functions;
    static ComplexFunctionParameterMapMap m_complex_functions;
    static ComplexFunctionParameterMapMap m_default_complex_functions;
    static QStringMap m_formula;
    static QStringMap m_name;

    // Default starting complex plane
    static StringComplexMap m_default_scentre;
    static StdStringMap m_default_swidth;
    // Starting complex plane
    static StringComplexMap m_scentre;
    static StdStringMap m_swidth;
    // Current complex plane
    static StringComplexMap m_ccentre;
    static StdStringMap m_cwidth;
    // Limit
    static LongDoubleMap m_limit;

    static InitialValueMap m_zero_initial_values;
    static InitialValueMap m_default_zero_initial_values;

    static long double m_width;
    static long double m_height;

    static StdStringMap m_select;
    static LongDoubleMap m_select_limit;
    // Colouring outer -> index 0 inner -> index 1
    static QStringMap m_colour_map[2];
    static StdStringMap m_method[2];
    static LongDoubleMap m_colour_scale[2];
    static BoolMap m_abs_log[2];
    static BoolMap m_smooth[2];

    static IntMap m_max_iterations;
    static IntMap m_default_max_iterations;
    static UintMap m_iteration_step_size;

    // Fixed initial value.
    static StringComplexMap m_z0;
    static StringComplexMap m_default_z0;

    // Rotation values.
    static IntMap m_crotation;
    static IntMap m_srotation;

    // Bailout
    static BailoutMap m_bailout;
    static BailoutMap m_default_bailout;
    static BailoutMap m_converge_bailout;
    static BailoutMap m_converge_default_bailout;
    static BoolMap m_converging;

    static StdStringMap m_transform_sequence;
    static TransformVectorMap m_cp_transforms;
    static TransformVectorVectorMap m_transforms;

    static IntMap m_interval;
    static CharMap m_orbit_colour_type;
    static UintMap m_default_interval;
    static CharMap m_default_orbit_colour_type;
    static BoolMap m_orbit_plotting;
    static QStringMap m_orbit_colour_map;
    static ComponentOrderMap m_order[2];
    static ComponentOrderMap m_orbit_order;
    static UintMap m_red_offset[2];
    static UintMap m_green_offset[2];
    static UintMap m_blue_offset[2];

    static QStringMap m_orbit_colour;
    static UintMap m_red_orbit_offset;
    static UintMap m_green_orbit_offset;
    static UintMap m_blue_orbit_offset;
    static IntMap m_calculating_area;
    static LongDoubleMap m_orbit_scale;
    static OrbitPlotsMap m_orbit_plots;
    static IntMap m_start_orbit_iteration;
    static UintMap m_density;
    static BoolMap m_has_orbit_background;
    static QColorMap m_background_colour;
    
    static FractalConfig m_fractal;
    
    static BoolMap m_quick;
    static IntMap m_precision;
    
    // Data for non-bailout fractals

    // Lyapunov
    static std::string m_sequence;
    static unsigned int m_settling_cycles;
    static unsigned int m_calculating_cycles;

    FRACTAL_TYPE m_type;
    int m_index;
    VectorFractalId m_fractal_ids;
    boost::shared_ptr<ColourMaps> m_colour_maps;
};

