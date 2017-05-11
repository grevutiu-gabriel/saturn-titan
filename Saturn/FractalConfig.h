// 
// File:   FractalConfig.h
// Author: M.R.Eggleston
//
// Created on 13 April 2012, 10:33
//

#pragma once

#include <QImage>
#include "ColourMap.h"
#include "TypesAndConstants.h"

class FractalConfig
{
public:
    FractalConfig();
    FractalConfig(FRACTAL_TYPE ft);
    FractalConfig(const FractalConfig& orig);
    const FractalConfig &operator=(const FractalConfig &other);

    virtual ~FractalConfig();
    
    int getWidth();
    void setWidth(int w);
    int getHeight();
    void setHeight(int h);
    const StringComplex &getCentre();
    void setCentre(const StringComplex& value);
    
    void setFromSeed(const QString& file_name);
    bool isOk();
    
    const QString& getName();
    void setName(const QString& name);
    
    const QString& getFormula();
    void setFormula(const QString& value);

    FRACTAL_TYPE GetFractalType();
    void SetFractalType(FRACTAL_TYPE ft);
    bool isLyapunov();

    unsigned int getNumberOfComplexParameters();
    void setNumberOfComplexParameters(unsigned int value);
    const StringComplex getComplexParameter(unsigned int index);
    PARAMETER_TYPE getComplexParameterType(unsigned int index);
    void setComplexParameterType(unsigned int index, PARAMETER_TYPE value);
    void setComplexParameter(unsigned int index, const StringComplex &value, PARAMETER_TYPE type);

    unsigned int getNumberOfParameters();
    void setNumberOfParameters(unsigned int value);
    const std::string getParameter(unsigned int index);
    void setParameter(unsigned int index, const std::string& value);
    
    unsigned int getNumberOfFunctionParameters();
    void setNumberOfFunctionParameters(unsigned int value);
    std::string getFunctionParameter(unsigned int index);
    void setFunctionParameter(unsigned int index, const std::string& value);
    
    unsigned int getNumberOfComplexFunctionParameters();
    void setNumberOfComplexFunctionParameters(unsigned int value);
    std::string getComplexFunctionParameter(unsigned int index);
    void setComplexFunctionParameter(unsigned int index, const std::string& value);
    
    long double getLimit();
    void setLimit(long double value);
    bool isConvergent();
    void setConvergent(bool value);
    BAILOUT getBailout();
    void setBailout(BAILOUT VALUE);
    const std::string& getSelection();
    void setSelection(const std::string& selection);
    long double getSelectLimit();
    void setSelectLimit(long double value);
    unsigned int getSettlingCycles();
    void setSettlingCycles(unsigned int value);
    unsigned int getCalculatingCycles();
    void setCalculatingCycles(unsigned int value);
    ORBIT_PLOTS getOrbitPlot();
    void setOrbitPlot(ORBIT_PLOTS plot);
    bool isOrbitPlotting();
    void setOrbitPlotting(bool plotting);
    unsigned int getArea();
    void setArea(unsigned int area);
    unsigned int getStartOrbitIteration();
    unsigned int getOmit();
    void setOmit(unsigned int omit);
    void setDensity(unsigned int value);
    unsigned int getDensity();
    const StringComplex &getImageCentre();
    void setImageCentre(const StringComplex &centre);
    const std::string& getImageWidth();
    void setImageWidth(const std::string& value);
    int getRotation();
    void setRotation(int value);
    unsigned int getMaxIterations();
    void setMaxIterations(unsigned int value);
    INITIAL_VALUE getInitialZtype();
    void setInitialZtype(INITIAL_VALUE value);
    const StringComplex &getInitalZ();
    void setInitialZ(const StringComplex &value);
    unsigned long getInterval();
    void setInterval(unsigned int value);
    const std::string& getLyapunovSequence();
    void setLyapunovSequence(const std::string& value);
    bool isSmooth(bool inner);
    void setSmooth(bool inner, bool value);
    void setSmooth(bool value);
    bool isAbsLog(bool inner);
    void setAbsLog(bool inner, bool value);
    void setAbsLog(bool value);
    const std::string& getMethod(bool inner);
    void setMethod(bool inner, const std::string& value);
    void setMethod(const std::string& value);
    bool isOrbitTrap(bool inner);
    
    bool transformsDefined();
    int getNumberOfComplexPlaneTransforms();
    void addComplexPlaneTransform(const std::string& transform);
    std::string getComplexPlaneTransform(int i);
    int getNumberOfTransforms(int set);
    std::string getTransform(int set, int i);
    int getNumberOfTransformSets();
    void setTransformSequence(const std::string& seq);
    void addTransformSet(int set);
    void addTransform(int set, const std::string& transform);
    void swapTransforms(int set, int a, int b); 
    void deleteTransform(int set, int pos);
    void deleteTransforms();
    const std::string& getTransformSequence();
    
    bool hasMultipleResults(bool inner);
    bool hasTwoResultsSets();
    
    QString getColourMapName(bool inner);
    QString getOrbitColourMap();
    
    long double getScale(bool inner);
    void setScale(bool inner, long double value);
    void setScale(long double value);
    bool getSmooth(bool inner);
    bool getAbsLog(bool inner);
    
    unsigned int getOrbitColourInterval();
    void setOrbitColourInterval(unsigned int interval);
    char getOrbitColourType();
    void setOrbitColourType(char type);
    long double getOrbitScale();
    void setOrbitScale(long double scale);
    unsigned int getOrbitRedOffset();
    void setOrbitRedOffset(unsigned int offset);
    unsigned int getOrbitGreenOffset();
    void setOrbitGreenOffset(unsigned int offset);
    unsigned int getOrbitBlueOffset();
    void setOrbitBlueOffset(unsigned int offset);
    
    bool hasColourMaps();
    ColourMap getColourMap(bool inner);
    void setColourMap(const ColourMap& map, bool inner);
    
    unsigned int widthInPixels();
    unsigned int heightInPixels();
    
    void setComponentOrder(COMPONENT_ORDER order, bool inner);
    void setComponentOrder(COMPONENT_ORDER order);
    COMPONENT_ORDER getComponentOrder(bool inner);
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
    void setInner(bool inner);
    bool isInner();
    void setStartingCentre(const StringComplex& value);
    void setStartingWidth(const std::string& value);
    void setStartingRotation(const unsigned int value);
    const StringComplex& getStartingCentre();
    const std::string& getStartingWidth();
    int getStartingRotation();
    void setColourMapName(const QString& name, bool inner);
    void setColourMapName(const QString& name);
    void setOrbitColourMapName(const QString& name);
    int getPrecision();
    void setPrecision(int value);

private:
    void readKeys(const QString& file_name);
    int saturnLevel();
    QString option(const QString& name);
    std::string std_option(const QString& name);
    void getLyapunovMetadata();
    void getParameterMetadata();
    void getPickoverPopcornMetadata(OLD_FRACTAL_TYPE ft);
    void getBailoutFractalMetadata(unsigned int ft);
    void getColourMapMetadata(bool inner);
    void getComponentColour(RGB colour, const QString& base_name, ColourMap& map);
    void getColourMethodMetadata(bool inner);
    void getOrbitColourMethod();
    void getTransforms();
    
    void convertOldFractalTypes(OLD_FRACTAL_TYPE ft);
    bool isOldPPMandelbrot(OLD_FRACTAL_TYPE ft);
    bool isOldPPJulia(OLD_FRACTAL_TYPE ft);
    
    void convertComplexPlaneTransforms(const QString& base, int count);
    void convertTransforms(int set, const QString& base, int count);
    
    void convertParametersToLevel6(OLD_FRACTAL_TYPE ft);
    void convertBcp_6(bool julia);
    void convertBcp2_6(bool julia);
    void convertCoscz_6(bool julia);
    void convertSincz_6(bool julia);
    void convertTancz_6(bool julia);
    void convertZcpac_6(bool julia);
    void convertZpowerC_6();
    void convertSinczCoscz_6(bool julia);
    void convertCpowerZ_6();
    void convertBiomorph1_6();
    void convertBiomorph2_6();
    void convertBiomorph3_6();
    void convertBiomorph4_6();
    void convertBiomorph5_6();
    void convertSqrtCp_6(bool julia);
    void convertCombination2_6();
    void convertCombination3_6();
    void convertCombination4_6();
    void convertUnnamed_6(bool julia);
    void convertUnnamed2_6(bool julia);
    void convertTzaccp_6(bool julia);
    void convertZaccp_6(bool julia);
    void convertCczcpaczcp_6(bool julia);
    void convertLzcpac_6(bool julia);
    void convertLtzcpac_6(bool julia);
    void convertMallard_6(bool julia);
    void convertTmallard_6(bool julia);
    void convertZazbcgd_6(bool julia);
    void convertCompasses_6(bool julia);
    void convertZptanczac_6(bool julia);
    void convertSimple_6(FRACTAL_TYPE ft, bool julia);
    
    bool isPopcorn(OLD_FRACTAL_TYPE ft);
    
    void setFunctionParameter(int index, FUNCTION_PARAMETER fp);
    
    enum CHUNK_TYPE
    {
        CT_TEXT,
        CT_ZTXT,
        CT_IEND,
        CT_IGNORE
    };
    
    CHUNK_TYPE chunk_type(unsigned char* data);
    
    std::string uncompress(std::vector<char>& buffer);

    typedef std::map<int, TransformRecordVector> TransformsMap;

    int m_width_pixels;
    int m_height_pixels;
    QString m_name;
    QString m_formula;
    FRACTAL_TYPE m_ft;

    unsigned int m_number_of_complex_parameters;
    ComplexParameter m_cp[MAX_PARAMETERS];
    bool m_cp_substitute_with_c[MAX_PARAMETERS];
    
    unsigned int m_number_of_parameters;
    std::string m_p[MAX_PARAMETERS];
    
    unsigned int m_number_of_function_parameters;
    std::string m_fp[MAX_PARAMETERS];
    
    unsigned int m_number_of_complex_function_parameters;
    std::string m_cfp[MAX_PARAMETERS];
    
    long double m_limit;
    bool m_convergent;
    BAILOUT m_bailout;
    std::string m_selection;
    long double m_select_limit;
    unsigned int m_settling_cycles;
    unsigned int m_calculating_cycles;
    ORBIT_PLOTS m_plot_type;
    bool m_orbit_plotting;
    unsigned int m_area;
    unsigned int m_omit;
    StringComplex m_centre;
    std::string m_width;
    int m_rotation;
    unsigned int m_max_iterations;
    INITIAL_VALUE m_z0_type;
    StringComplex m_z0;
    unsigned int m_interval;
    std::string m_lyapunov_sequence;
    bool m_smooth[2];
    bool m_abs_log[2];
    std::string m_method[2];
    long double m_scale[2];
    
    std::string m_transform_sequence;
    TransformsMap m_transforms;
    TransformRecordVector m_cp_transforms;
    
    char m_orbit_colour_type;
    unsigned int m_red_orbit_offset;
    unsigned int m_green_orbit_offset;
    unsigned int m_blue_orbit_offset;
    long double m_orbit_scale;
    unsigned int m_density;
    
    QString m_colour_map_name[2];
    QString m_orbit_colour_map;
    QColor m_orbit_background;
    bool m_has_orbit_background;
    
    ColourMap m_colour_map[2];
    
    unsigned int m_width_in_pixels;
    unsigned int m_height_in_pixels;
    COMPONENT_ORDER m_order[2];
    unsigned int m_red_offset[2];
    unsigned int m_green_offset[2];
    unsigned int m_blue_offset[2];
    
    int m_index;
    StringComplex m_scentre;
    std::string m_swidth;
    int m_srotation;

    std::map<QString, QString> m_map;
    int m_level;
    bool m_ok;
    int m_precision;
};

