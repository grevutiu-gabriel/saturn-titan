// 
// File:   FractalConfig.cc
// Author: M.R.Eggleston
// 
// Created on 13 April 2012, 10:33
//

#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <QFile>
#include "FractalConfig.h"
#include "KeyString.h"
#include "Utilities.h"

namespace io = boost::iostreams;

FractalConfig::FractalConfig()
:
m_ft(F_MANDELBROT),
m_number_of_complex_parameters(0),
m_number_of_parameters(0),
m_number_of_function_parameters(0),
m_number_of_complex_function_parameters(0),
m_limit(16.0L),
m_convergent(false),
m_bailout(B_NORM),
m_select_limit(4.0L),
m_settling_cycles(1),
m_calculating_cycles(1),
m_plot_type(OP_ALL),
m_orbit_plotting(false),
m_area(9),
m_omit(0),
m_width("0"),
m_rotation(0),
m_max_iterations(5000),
m_z0_type(TRANSFORMED),
m_interval(10000),
m_orbit_colour_type('a'),
m_red_orbit_offset(0),
m_green_orbit_offset(0),
m_blue_orbit_offset(0),
m_orbit_scale(1.0L),
m_density(1),
m_orbit_background(),
m_has_orbit_background(false),
m_width_in_pixels(0),
m_height_in_pixels(0),
m_index(0),
m_level(-1),
m_ok(false),
m_precision(0)
{
    for (int i = 0; i < 2; i++)
    {
        m_smooth[i] = false;
        m_abs_log[i] = false;
        m_scale[i] = 1.0L;
        m_red_offset[i] = 0;
        m_blue_offset[i] = 0;
        m_green_offset[i] = 0;
        m_order[i] = CO_RGB;
    }
}

FractalConfig::FractalConfig(FRACTAL_TYPE ft)
{
    FractalConfig();
    m_ft = ft;
}

FractalConfig::~FractalConfig()
{
}

FractalConfig::FractalConfig(const FractalConfig &other)
{
    operator=(other);
}

const FractalConfig &FractalConfig::operator=(const FractalConfig &other)
{
    m_name = other.m_name;
    m_ft = other.m_ft;
    m_number_of_complex_parameters = other.m_number_of_complex_parameters;
    m_number_of_parameters = other.m_number_of_parameters;
    m_number_of_function_parameters = other.m_number_of_function_parameters;
    m_number_of_complex_function_parameters = other.m_number_of_complex_function_parameters;
    for (int i = 0; i < MAX_PARAMETERS; i++)
    {
        m_cp[i] = other.m_cp[i];
        m_p[i] = other.m_p[i];
        m_fp[i] = other.m_fp[i];
        m_cfp[i] = other.m_cfp[i];
    }
    m_limit = other.m_limit;
    m_convergent = other.m_convergent;
    m_bailout = other.m_bailout;
    m_selection = other.m_selection;
    m_select_limit = other.m_select_limit;
    m_settling_cycles = other.m_settling_cycles;
    m_calculating_cycles = other.m_calculating_cycles;
    m_plot_type = other.m_plot_type;
    m_orbit_plotting = other.m_orbit_plotting;
    m_area = other.m_area;
    m_omit = other.m_omit;
    m_density = other.m_density;
    m_centre = other.m_centre;
    m_width = other.m_width;
    m_rotation = other.m_rotation;
    m_max_iterations = other.m_max_iterations;
    m_z0_type = other.m_z0_type;
    m_z0 = other.m_z0;
    m_interval = other.m_interval;
    m_lyapunov_sequence = other.m_lyapunov_sequence;
    m_transform_sequence = other.m_transform_sequence;
    for (int i = 0; i < 2; i++)
    {
        m_method[i] = other.m_method[i];
        m_colour_map_name[i] = other.m_colour_map_name[i];
        m_red_offset[i] = other.m_red_offset[i];
        m_green_offset[i] = other.m_green_offset[i];
        m_blue_offset[i] = other.m_blue_offset[i];
        m_scale[i] = other.m_scale[i];
        m_smooth[i] = other.m_smooth[i];
        m_abs_log[i] = other.m_abs_log[i];
        m_colour_map[i] = other.m_colour_map[i];
        m_order[i] = other.m_order[i];
    }
    m_orbit_colour_map = other.m_orbit_colour_map;
    m_orbit_colour_type = other.m_orbit_colour_type;
    m_red_orbit_offset = other.m_red_orbit_offset;
    m_green_orbit_offset = other.m_green_orbit_offset;
    m_blue_orbit_offset = other.m_blue_orbit_offset;
    m_orbit_scale = other.m_orbit_scale;
    m_ok = other.m_ok;
    m_level = other.m_level;
    m_transforms = other.m_transforms;
    m_cp_transforms = other.m_cp_transforms;
    m_width_in_pixels = other.m_width_in_pixels;
    m_height_in_pixels = other.m_height_in_pixels;
    m_width_in_pixels = other.m_width_in_pixels;
    m_height_in_pixels = other.m_height_in_pixels;
    m_has_orbit_background = other.m_has_orbit_background;
    m_orbit_background = other.m_orbit_background;
    m_precision = other.m_precision;
    return *this;
}

const QString& FractalConfig::getName()
{
    return m_name;
}

void FractalConfig::setName(const QString& name)
{
    m_name = name;
}

FRACTAL_TYPE FractalConfig::GetFractalType()
{
    return m_ft;
}

void FractalConfig::SetFractalType(FRACTAL_TYPE ft)
{
    m_ft = ft;
}

bool FractalConfig::isLyapunov()
{
    return (m_ft == F_LYAPUNOV);
}

unsigned int FractalConfig::getNumberOfComplexParameters()
{
    return m_number_of_complex_parameters;
}

void FractalConfig::setNumberOfComplexParameters(unsigned int value)
{
    m_number_of_complex_parameters = value;
}

const StringComplex FractalConfig::getComplexParameter(unsigned int index)
{
    return (index < MAX_PARAMETERS ? m_cp[index].p : StringComplex());
}

PARAMETER_TYPE FractalConfig::getComplexParameterType(unsigned int index)
{
    return (index < MAX_PARAMETERS ? m_cp[index].type : PT_NUMBER);
}

void FractalConfig::setComplexParameterType(unsigned int index, PARAMETER_TYPE value)
{
    if (index < MAX_PARAMETERS) m_cp[index].type = value;
}

void FractalConfig::setComplexParameter(unsigned int index, const StringComplex &value, PARAMETER_TYPE type )
{
    if (index < MAX_PARAMETERS)
    {
        ComplexParameter p = { value, type };
        m_cp[index] = p;
    }
}

unsigned int FractalConfig::getNumberOfParameters()
{
    return m_number_of_parameters;
}

void FractalConfig::setNumberOfParameters(unsigned int value)
{
    m_number_of_parameters = value;
}

const std::string FractalConfig::getParameter(unsigned int index)
{
    return (index < MAX_PARAMETERS ? m_p[index] : "0");
}

void FractalConfig::setParameter(unsigned int index, const std::string& value)
{
    if (index < MAX_PARAMETERS) m_p[index] = value;
}

unsigned int FractalConfig::getNumberOfFunctionParameters()
{
    return m_number_of_function_parameters;
}

void FractalConfig::setNumberOfFunctionParameters(unsigned int value)
{
    m_number_of_function_parameters = value;
}

std::string FractalConfig::getFunctionParameter(unsigned int index)
{
    return (index < MAX_PARAMETERS ? m_fp[index] : "id=0");
}

void FractalConfig::setFunctionParameter(unsigned int index, const std::string &value)
{
    if (index < MAX_PARAMETERS)
    {
        m_fp[index] = value;
    }
}

unsigned int FractalConfig::getNumberOfComplexFunctionParameters()
{
    return m_number_of_complex_function_parameters;
}

void FractalConfig::setNumberOfComplexFunctionParameters(unsigned int value)
{
    m_number_of_complex_function_parameters = value;
}

std::string FractalConfig::getComplexFunctionParameter(unsigned int index)
{
    return (index < MAX_PARAMETERS ? m_cfp[index] : "pair=n,id=0");
}

void FractalConfig::setComplexFunctionParameter(unsigned int index, const std::string& value)
{
    if (index < MAX_PARAMETERS)
    {
        m_cfp[index] = value;
    }
}

long double FractalConfig::getLimit()
{
    return m_limit;
}

void FractalConfig::setLimit(long double value)
{
    m_limit = value;
}

bool FractalConfig::isConvergent()
{
    return m_convergent;
}

void FractalConfig::setConvergent(bool value)
{
    m_convergent = value;
}

BAILOUT FractalConfig::getBailout()
{
    return m_bailout;
}

void FractalConfig::setBailout(BAILOUT value)
{
    m_bailout = value;
}

const std::string& FractalConfig::getSelection()
{
    return m_selection;
}

void FractalConfig::setSelection(const std::string& sel)
{
    if (sel.length() < 4)
    {
        m_selection = "normz";
    }
    else if (sel.length() == 4)
    {
        std::string comparison = sel.substr(2, 1);
        std::string selection = sel;
        selection.insert(2, comparison);
        m_selection = selection;
    }
    else
    {
        m_selection = sel;
    }
}

long double FractalConfig::getSelectLimit()
{
    return m_select_limit;
}

void FractalConfig::setSelectLimit(long double value)
{
    m_select_limit = value;
}

unsigned int FractalConfig::getSettlingCycles()
{
    return m_settling_cycles;
}

void FractalConfig::setSettlingCycles(unsigned int value)
{
    m_settling_cycles = value;
}

unsigned int FractalConfig::getCalculatingCycles()
{
    return m_calculating_cycles;
}

void FractalConfig::setCalculatingCycles(unsigned int value)
{
    m_calculating_cycles = value;
}

ORBIT_PLOTS FractalConfig::getOrbitPlot()
{
    return m_plot_type;
}

void FractalConfig::setOrbitPlot(ORBIT_PLOTS plot)
{
    m_plot_type = plot;
}

bool FractalConfig::isOrbitPlotting()
{
    return m_orbit_plotting;
}

void FractalConfig::setOrbitPlotting(bool plotting)
{
    m_orbit_plotting = plotting;
}

unsigned int FractalConfig::getArea()
{
    return m_area;
}

void FractalConfig::setArea(unsigned int area)
{
    m_area = area;
}

unsigned int FractalConfig::getStartOrbitIteration()
{
    return m_omit;
}

unsigned int FractalConfig::getOmit()
{
    return m_omit;
}

void FractalConfig::setOmit(unsigned int omit)
{
    m_omit = omit;
}

void FractalConfig::setDensity(unsigned int value)
{
    m_density = value;
}

unsigned int FractalConfig::getDensity()
{
    return m_density;
}

const StringComplex &FractalConfig::getImageCentre()
{
    return m_centre;
}

void FractalConfig::setImageCentre(const StringComplex &centre)
{
    m_centre = centre;
}

const std::string& FractalConfig::getImageWidth()
{
    return m_width;
}

void FractalConfig::setImageWidth(const std::string &value)
{
    m_width = value;
}

int FractalConfig::getRotation()
{
    return m_rotation;
}

void FractalConfig::setRotation(int value)
{
    m_rotation = value;
}

unsigned int FractalConfig::getMaxIterations()
{
    return m_max_iterations;
}

void FractalConfig::setMaxIterations(unsigned int value)
{
    m_max_iterations = value;
}
INITIAL_VALUE FractalConfig::getInitialZtype()
{
    return m_z0_type;
}

void FractalConfig::setInitialZtype(INITIAL_VALUE value)
{
    m_z0_type = value;
}

const StringComplex &FractalConfig::getInitalZ()
{
    return m_z0;
}

void FractalConfig::setInitialZ(const StringComplex &value)
{
    m_z0 = value;
}

unsigned long FractalConfig::getInterval()
{
    return m_interval;
}

void FractalConfig::setInterval(unsigned int value)
{
    m_interval = value;
}

const std::string &FractalConfig::getLyapunovSequence()
{
    return m_lyapunov_sequence;
}

void FractalConfig::setLyapunovSequence(const std::string &value)
{
    m_lyapunov_sequence = value;
}

bool FractalConfig::isSmooth(bool inner)
{
    return m_smooth[inner ? 1 : 0];
}

void FractalConfig::setSmooth(bool inner, bool value)
{
    m_smooth[inner ? 1 : 0] = value;
}

void FractalConfig::setSmooth(bool value)
{
    m_smooth[m_index] = value;
}

bool FractalConfig::isAbsLog(bool inner)
{
    return m_abs_log[inner ? 1 : 0];
}

void FractalConfig::setAbsLog(bool inner, bool value)
{
    m_abs_log[inner ? 1 : 0] = value;
}

void FractalConfig::setAbsLog(bool value)
{
    m_abs_log[m_index] = value;
}

const std::string &FractalConfig::getMethod(bool inner)
{
    return m_method[inner ? 1 : 0];
}

void FractalConfig::setMethod(bool inner, const std::string& value)
{
    m_method[inner ? 1 : 0] = value;
}

void FractalConfig::setMethod(const std::string& value)
{
    m_method[m_index] = value;
}

bool FractalConfig::isOrbitTrap(bool inner)
{
    return m_method[static_cast<bool>(inner)][0] == 't';
}

bool FractalConfig::transformsDefined()
{
    int count = 0;
    for (auto it = m_transforms.begin(); it != m_transforms.end(); it++)
    {
        count += it->second.size();
    }
    return (count > 0);
}

int FractalConfig::getNumberOfComplexPlaneTransforms()
{
    return m_cp_transforms.size();
}

void FractalConfig::addComplexPlaneTransform(const std::string &t)
{
    m_cp_transforms.push_back(t);
}

std::string FractalConfig::getComplexPlaneTransform(int i)
{
    return m_cp_transforms[i];
}

int FractalConfig::getNumberOfTransforms(int set)
{
    int size = 0;
    if (m_transforms.count(set) != 0)
    {
        size = m_transforms[set].size();
    }
    return size;
}

std::string FractalConfig::getTransform(int set, int i)
{
    return m_transforms[set][i];
}

void FractalConfig::addTransformSet(int set)
{
    TransformRecordVector v;
    m_transforms[set] = v;
}

void FractalConfig::addTransform(int set, const std::string &t)
{
    if (m_transforms.count(set) == 0)
    {
        TransformRecordVector v;
        v.push_back(t);
        m_transforms[set] = v;
    }
    else
    {
        m_transforms[set].push_back(t);
    }
}

void FractalConfig::swapTransforms(int set, int a, int b)
{
    std::string t = m_transforms[set][a];
    m_transforms[set][a] = m_transforms[set][b];
    m_transforms[set][b] = t;
}

void FractalConfig::deleteTransform(int set, int pos)
{
    TransformRecordVector &v = m_transforms[set];
    v.erase(v.begin()+pos);
}

void FractalConfig::deleteTransforms()
{
    m_cp_transforms.clear();
    m_transforms.clear();
}

int FractalConfig::getNumberOfTransformSets()
{
    return m_transforms.size();
}

void FractalConfig::setTransformSequence(const std::string &seq)
{
    m_transform_sequence = seq;
}

const std::string &FractalConfig::getTransformSequence()
{
    return m_transform_sequence;
}

bool FractalConfig::hasMultipleResults(bool inner)
{
    char type = getMethod(inner)[0];
    return (type == 'g') || (type == 'M') ||
           (type == 'A') || (type == 't') ||
           (type == 'r');
}

bool FractalConfig::hasTwoResultsSets()
{
    bool two_sets = false;
    std::string &outer_method = m_method[0];
    std::string &inner_method = m_method[1];
    bool outer_multiple = hasMultipleResults(false);
    bool inner_multiple = hasMultipleResults(true);
    if (outer_multiple && inner_multiple)
    {
        // Two sets if both are Gaussia Integer of differing types 
        two_sets = (outer_method[0] == 'g') && (outer_method[0] == 'g') &&
                   ((outer_method[1] != inner_method[1]) ||
                   (outer_method[2] != inner_method[2]));
        // Different colour method types
        if (!two_sets)
        {
            two_sets = (outer_method[0] != inner_method[0]);
        }
        // Same type, check for only being change in value indicated by a
        // difference in case of the option letters
        if (!two_sets)
        {
            bool both_angle = (outer_method[0] == 'A') && (inner_method[0] == 'A');
            bool both_magnitude = (outer_method[0] == 'M') && (inner_method[0] == 'M');
            if (both_angle || both_magnitude)
            {
                two_sets = ((outer_method[1] != inner_method[1]));
            }
            if (!two_sets && both_magnitude)
            {
                // Two sets of data required if Magnitude is set for both inner 
                // and outer and only one of them is Fractal Dimension
                two_sets = ((outer_method == "Mj") && (inner_method != "Mj"));
                two_sets = two_sets || ((outer_method != "Mj") && (inner_method == "Mj"));
            }
        }
        if (!two_sets)
        {
            // Two sets of data if both inner and outer are differing orbit traps
            two_sets = ((outer_method[0]== 't') &&
                        (inner_method[0] == 't') &&
                        (outer_method != inner_method));
        }
    }
    return two_sets;
}

//==============================================================================
// Code for setting fractal configuration from seed file metadata
//==============================================================================

int FractalConfig::saturnLevel()
{
    int level = -1;
    auto str = option("program");
    QString saturn("saturn");
    int saturn_length = saturn.length();
    int str_length = str.length();
    bool is_saturn = false;
    if (str_length >= saturn_length)
    {
        is_saturn = (saturn == str.left(saturn_length));
    }
    if (is_saturn)
    {
        if (str_length == saturn_length)
        {
            level = 0;
        }
        else
        {
            QString id = str.mid(saturn_length);
            int value = id.toInt();
            if (value > 0)
            {
                level = value;
            }
        }
    }
    auto ft = static_cast<OLD_FRACTAL_TYPE>(option("fractal_type").toInt());
    bool is_deleted_fractal = (((ft == FT_TZDRICPAC) || (ft ==FT_TZDRICPAC_J)) && (level < 6));
    m_ok = (((level >= 0) && (level <= LEVEL)) && !is_deleted_fractal);
    return level;
}

QString FractalConfig::option(const QString& name)
{
    QString value;
    if (m_map.count(name) == 1)
    {
        value = m_map[name];
    }
    return value;
}

std::string FractalConfig::std_option(const QString& name)
{
    return option(name).toStdString();
}

void FractalConfig::readKeys(const QString& name)
{
    // QImage on OS X and Windows fails to load all the seed file's metadata
    // reporting that there is no space in the chunk cache for tEXt.
    //
    // To get around this problem the file must be read and processed directly.
    //
    bool ok = false;
    unsigned char signature[8] = { 137, 80, 78, 71, 13, 10, 26, 10 };
    unsigned char header_id[4] = { 73, 72, 68, 82 };
    unsigned char data[8];
    qint64 number_of_bytes = 0;
    qint64 pos = 0;
    bool first_chunk = true;
    CHUNK_TYPE type = CT_IGNORE;
    QFile file(name);
    if (file.open(QIODevice::ReadOnly))
    {
        file.seek(0);
        number_of_bytes = file.read(reinterpret_cast<char*>(data), 8);
        if (number_of_bytes == 8)
        {
            for (int i = 0; i < 8 ; i++)
            {
                ok = (data[i] == signature[i]);
                if (!ok)
                {
                    break;
                }
            }
        }
        pos += number_of_bytes;
        while (ok && !file.atEnd() && (type != CT_IEND))
        {
            ok = file.seek(pos);
            if (ok)
            {
                // Read size of data
                number_of_bytes = file.read(reinterpret_cast<char*>(data), 4);
                ok = (number_of_bytes == 4);
                int size = convertFromNetworkFormat32(data);
                // update position for start of next chunk
                pos += (size + 12); // extra 12, length, type & for CRC
                // Read chunk id
                number_of_bytes = file.read(reinterpret_cast<char*>(data), 4);
                ok = (number_of_bytes == 4);
                if (first_chunk)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        ok = (data[i] == header_id[i]);
                        if (!ok)
                        {
                            break;
                        }
                    }
                    if (ok)
                    {
                        number_of_bytes = file.read(reinterpret_cast<char*>(data), 4);
                        ok = (number_of_bytes == 4);
                        m_width_in_pixels = convertFromNetworkFormat32(data);
                        number_of_bytes = file.read(reinterpret_cast<char*>(data), 4);
                        ok = (number_of_bytes == 4);
                        m_height_in_pixels = convertFromNetworkFormat32(data);
                        first_chunk = false;
                    }
                }
                else
                {
                    type = chunk_type(data);
                    if (type == CT_TEXT)
                    {
                        std::string key;
                        std::string value;
                        int i = 1;
                        ok = file.getChar(reinterpret_cast<char*>(data));
                        while ((i < size) && (*data != static_cast<unsigned char>(0)))
                        {
                            if (ok) key += *data;
                            ok = file.getChar(reinterpret_cast<char*>(data));
                            i++;
                        }
                        while (i < size)
                        {
                            ok = file.getChar(reinterpret_cast<char*>(data));
                            value += *data;
                            i++;
                        }
                        if (ok)
                        {
                            m_map[QString::fromStdString(key)] = QString::fromStdString(value);
                        }
                    }
                    else if (type == CT_ZTXT)
                    {
                        std::string key;
                        std::vector<char> compressed_value;
                        int i = 1;
                        ok = file.getChar(reinterpret_cast<char*>(data));
                        while ((i < size) && (*data != static_cast<unsigned char>(0)))
                        {
                            if (ok) key += *data;
                            ok = file.getChar(reinterpret_cast<char*>(data));
                            i++;
                        }
                        // skip compression method
                        ok = file.getChar(reinterpret_cast<char*>(data));
                        i++;
                        while (i < size)
                        {
                            ok = file.getChar(reinterpret_cast<char*>(data));
                            compressed_value.push_back(*data);
                            i++;
                        }
                        if (ok)
                        {
                            std::string value = uncompress(compressed_value);
                            m_map[QString::fromStdString(key)] = QString::fromStdString(value);
                        }
                        
                    }
                }
            }
        }
    }
    file.close();
    m_ok = ok;
}

void FractalConfig::setFromSeed(const QString& file_name)
{
    readKeys(file_name);
    if (m_ok)
    {
        int ft = option("fractal_type").toInt();
        m_level = saturnLevel();
        if (m_ok)
        {
            m_centre = StringComplex(std_option("centre_r"), std_option("centre_i"));
            m_width = std_option("longside");
            m_rotation = option("rotation").toInt();
            if (m_rotation > 180) m_rotation = m_rotation - 360;
            if (((ft == static_cast<int>(F_LYAPUNOV)) && (m_level > 4)) ||
                (ft == static_cast<int>(FT_LYAPUNOV) && (m_level < 5)))
            {
                getLyapunovMetadata();
            }
            else if (isPopcorn(static_cast<OLD_FRACTAL_TYPE>(ft)))
            {
                // Old seed files where Pickover Popcorn fractals were the only
                // orbit plotted fractals
                getPickoverPopcornMetadata(static_cast<OLD_FRACTAL_TYPE>(ft));
            }
            else
            {
                getBailoutFractalMetadata(ft);
            }
        }
    }
    m_map.clear(); // Data no longer required.
}

bool FractalConfig::isOk()
{
    return m_ok;
}    

void FractalConfig::getBailoutFractalMetadata(unsigned int ft)
{
    if (m_level < 6)
    {
        if (isOldPPMandelbrot(static_cast<OLD_FRACTAL_TYPE>(ft)) ||
            isOldPPJulia(static_cast<OLD_FRACTAL_TYPE>(ft)))
        {
            convertOldFractalTypes(static_cast<OLD_FRACTAL_TYPE>(ft));
            convertParametersToLevel6(static_cast<OLD_FRACTAL_TYPE>(ft));
        }
        else if (m_level < 6)
        {
            getParameterMetadata();
            convertParametersToLevel6(static_cast<OLD_FRACTAL_TYPE>(ft));
        }
    }
    else
    {
        m_ft = static_cast<FRACTAL_TYPE>(ft);
        getParameterMetadata();
    }
    m_orbit_plotting = (m_level > 2 ? (option("orbit").toUInt() == 1) : false);
    setSelection(std_option("select"));
    if (isSingleOrbit(m_ft))
    {
        getOrbitColourMethod();
    }
    else if (isOrbitPlotting())
    {
        m_area = option("area").toUInt();
        QString str = option("plot");
        ORBIT_PLOTS plot = OP_ALL;
        if (!str.isEmpty())
        {
            plot = static_cast<ORBIT_PLOTS>(str.toUInt());
        }
        m_plot_type = plot;
        m_omit = option("omit").toUInt();
        str = option("density");
        setDensity(str.isEmpty() ? 1 : str.toUInt());
        getOrbitColourMethod();
    }
    else
    {
        auto str = option("precision");
        setPrecision(str.isEmpty() ? 0 : str.toInt());
        getColourMethodMetadata(false); // Outer colouring
        getColourMethodMetadata(true); // Inner colouring
    }
    m_limit = stringToLongDouble(option("limit").toStdString());
    m_bailout = static_cast<BAILOUT>(option("bailout").toUInt());
    m_convergent = (option("convergent").toUInt() == 1);
    m_max_iterations = option("max_iterations").toUInt();
    m_select_limit = stringToLongDouble(std_option("select_limit"));
    KeyString z0_keys(std_option("z0"));
    m_z0 = StringComplex(z0_keys.GetKey("r", "0"), z0_keys.GetKey("i", "0"));
    m_z0_type = static_cast<INITIAL_VALUE>(z0_keys.GetKeyAsInt("type", 0));
    getTransforms();
    m_transform_sequence = std_option("sequence");
}

void FractalConfig::getTransforms()
{
    deleteTransforms();
    if (m_level < 5)
    {
        convertComplexPlaneTransforms("ctransform", option("ctransforms").toInt());
        convertTransforms(0, "atransform", option("atransforms").toInt());
        convertTransforms(1, "btransform", option("btransforms").toInt());
    }
    else
    {
        int number_of_transforms = option("set_cp").toInt();
        for (int i = 0; i < number_of_transforms; i++)
        {
            addComplexPlaneTransform(std_option("cp" + QString::number(i) + "t"));
        }
        int sets = option("transform_sets").toInt();
        for (int set = 0; set < sets; set++)
        {
            number_of_transforms = option("set" + QString::number(set)).toInt();
            addTransformSet(set);
            for (int i = 0; i < number_of_transforms; i++)
            {
                 addTransform(set, std_option("set" + QString::number(set) + "t" + QString::number(i)));
            }
        }
    }
}

bool FractalConfig::isOldPPMandelbrot(OLD_FRACTAL_TYPE ft)
{
    return ((ft == FT_PP_MANDELBROT) ||
            (ft == FT_PP_MANDELBROT_2) ||
            (ft == FT_PP_MANDELBROT_3) ||
            (ft == FT_PP_MANDELBROT_4) ||
            (ft == FT_PP_MANDELBROT_5));
}

bool FractalConfig::isOldPPJulia(OLD_FRACTAL_TYPE ft)
{
    return ((ft == FT_PP_JULIA) ||
            (ft == FT_PP_JULIA_2) ||
            (ft == FT_PP_JULIA_3) ||
            (ft == FT_PP_JULIA_4) ||
            (ft == FT_PP_JULIA_5));
}

void FractalConfig::convertComplexPlaneTransforms(const QString& base, int count)
{
    for (int i = 0; i < count; i++)
    {
        auto id = static_cast<TRANSFORM>(option(base + QString::number(i) + "t").toInt());
        long double re = stringToLongDouble(std_option(base + QString::number(i) + "r"));
        long double im = stringToLongDouble(std_option(base + QString::number(i) + "i"));
        int rotation = option(base + QString::number(i) + "rot").toInt();
        if (rotation > 180)
        {
            rotation -= 360;
        }
        long double size = stringToLongDouble(std_option(base + QString::number(i) + "s"));
        if (id == T_TRANSLATION)
        {
            if ((re != 0.0L) || (im != 0.0L))
            {
                addComplexPlaneTransform(convertTranslation(re, im));
            }
        }
        else if (id == T_ROTATION)
        {
            if (rotation != 0)
            {
                addComplexPlaneTransform(convertRotation(rotation));
            }
        }
        else if (id == T_SCALE)
        {
            if ((re != 1.0L) || (im != 1.0L))
            {
                addComplexPlaneTransform(convertScale(re, im));
            }
        }
        else if (id == T_POWER)
        {
            addComplexPlaneTransform(convertPower(re, im));
        }
        else if (id == T_EXP)
        {
            addComplexPlaneTransform(convertExp());
        }
        else if (id == T_LOG)
        {
            addComplexPlaneTransform(convertLog());
        }
        else
        {
            if ((re != 0.0L) || (im != 0.0L))
            {
                addComplexPlaneTransform(convertTranslation((re != 0.0L ? -re : 0.0L),(im != 0.0L ? -im : 0.0L)));
            }
            if (rotation != 0)
            {
                addComplexPlaneTransform(convertRotation(-rotation));
            }
            if (id == T_UNSIGN_REAL)
            {
                addComplexPlaneTransform(convertUnsignReal());
            }
            else if (id == T_SIGN_REAL)
            {
                addComplexPlaneTransform(convertSignReal());
            }
            else if (id == T_REVERSE_SIGN_REAL)
            {
                addComplexPlaneTransform(convertReverseSignReal());
            }
            else if (id == T_UNSIGN_IMAGINARY)
            {
                addComplexPlaneTransform(convertUnsignImaginary());
            }
            else if (id == T_SIGN_IMAGINARY)
            {
                addComplexPlaneTransform(convertSignImaginary());
            }
            else if (id == T_REVERSE_SIGN_IMAGINARY)
            {
                addComplexPlaneTransform(convertReverseSignImaginary());
            }
            else if ((id == T_CIRCLE_IN) || (id == T_INVERSE_FOLD_IN) ||
                     (id == T_CIRCLE_OUT) || (id == T_INVERSE_FOLD_OUT) ||
                     (id == T_CIRCLE_REFLECT) || (id == T_INVERSE_REFLECT))
            {
                addComplexPlaneTransform(convertCircleTransform(id, size));
            }
            else if (id == T_TOP_RIGHT)
            {
                addComplexPlaneTransform(convertTopRight());
            }
            else if (id == T_BOTTOM_RIGHT)
            {
                addComplexPlaneTransform(convertBottomRight());
            }
            else if (id == T_TOP_LEFT)
            {
                addComplexPlaneTransform(convertTopLeft());
            }
            else if (id == T_BOTTOM_LEFT)
            {
                addComplexPlaneTransform(convertBottomLeft());
            }
            if (rotation != 0)
            {
                addComplexPlaneTransform(convertRotation(rotation));
            }
            if ((re != 0.0L) || (im != 0.0L))
            {
                addComplexPlaneTransform(convertTranslation(re, im));
            }
        }
    }
}

void FractalConfig::convertTransforms(int set, const QString& base, int count)
{
    TransformRecordVector v;
    m_transforms[set] = v;
    for (int i = 0; i < count; i++)
    {
        auto id = static_cast<TRANSFORM>(option(base + QString::number(i) + "t").toUInt());
        long double re = stringToLongDouble(std_option(base + QString::number(i) + "r"));
        long double im = stringToLongDouble(std_option(base + QString::number(i) + "i"));
        int rotation = option(base + QString::number(i) + "rot").toInt();
        if (rotation > 180)
        {
            rotation -= 360;
        }
        long double size = stringToLongDouble(std_option(base + QString::number(i) + "s"));
        if (id == T_TRANSLATION)
        {
            if ((re != 0.0L) || (im != 0.0L))
            {
                addTransform(set, convertTranslation(re, im));
            }
        }
        else if (id == T_ROTATION)
        {
            if (rotation != 0)
            {
                addTransform(set, convertRotation(rotation));
            }
        }
        else if (id == T_SCALE)
        {
            if ((re != 1.0L) || (im != 1.0L))
            {
                addTransform(set, convertScale(re, im));
            }
        }
        else if (id == T_POWER)
        {
            addTransform(set, convertPower(re, im));
        }
        else if (id == T_EXP)
        {
            addTransform(set, convertExp());
        }
        else if (id == T_LOG)
        {
            addTransform(set, convertLog());
        }
        else
        {
            if ((re != 0.0L) || (im != 0.0L))
            {
                addTransform(set, convertTranslation((re != 0.0L ? -re : 0.0L),(im != 0.0L ? -im : 0.0L)));
            }
            if (rotation != 0)
            {
                addTransform(set, convertRotation(-rotation));
            }
            if (id == T_UNSIGN_REAL)
            {
                addTransform(set, convertUnsignReal());
            }
            else if (id == T_SIGN_REAL)
            {
                addTransform(set, convertSignReal());
            }
            else if (id == T_REVERSE_SIGN_REAL)
            {
                addTransform(set, convertReverseSignReal());
            }
            else if (id == T_UNSIGN_IMAGINARY)
            {
                addTransform(set, convertUnsignImaginary());
            }
            else if (id == T_SIGN_IMAGINARY)
            {
                addTransform(set, convertSignImaginary());
            }
            else if (id == T_REVERSE_SIGN_IMAGINARY)
            {
                addTransform(set, convertReverseSignImaginary());
            }
            else if ((id == T_CIRCLE_IN) || (id == T_INVERSE_FOLD_IN) ||
                     (id == T_CIRCLE_OUT) || (id == T_INVERSE_FOLD_OUT) ||
                     (id == T_CIRCLE_REFLECT) || (id == T_INVERSE_REFLECT))
            {
                addTransform(set, convertCircleTransform(id, size));
            }
            else if (id == T_TOP_RIGHT)
            {
                addTransform(set, convertTopRight());
            }
            else if (id == T_BOTTOM_RIGHT)
            {
                addTransform(set, convertBottomRight());
            }
            else if (id == T_TOP_LEFT)
            {
                addTransform(set, convertTopLeft());
            }
            else if (id == T_BOTTOM_LEFT)
            {
                addTransform(set, convertBottomLeft());
            }
            if (rotation != 0.0L)
            {
                addTransform(set, convertRotation(rotation));
            }
            if ((re != 0.0L) || (im != 0.0L))
            {
                addTransform(set, convertTranslation(re, im));
            }
        }
    }
}

bool FractalConfig::isPopcorn(OLD_FRACTAL_TYPE ft)
{
    // Old Pickover Popcorn identities are retained so that level 1 or 2 seed
    // can be recognised and converted into PP Julia 4F or 6F.
    bool is = false;
    if (m_level < 3)
    {
        switch (ft)
        {
        case FT_PICKOVER_POPCORN:
        case FT_PICKOVER_POPCORN_2:
        case FT_PICKOVER_POPCORN_3:
        case FT_PICKOVER_POPCORN_4:
        case FT_PICKOVER_POPCORN_4F:
        case FT_PICKOVER_POPCORN_5:
        case FT_PICKOVER_POPCORN_6F:
            is = true;
            break;
        default:
            is = false;
            break;
        }
    }
    return is;
}

void FractalConfig::getOrbitColourMethod()
{
    m_orbit_colour_type = static_cast<char>(std_option("method")[0]);
    m_interval = option("interval").toUInt();
    // Due to change
    if (m_level < 7)
    {
        m_red_orbit_offset = option("colour_offset").toUInt();
        m_green_orbit_offset = m_red_orbit_offset;
        m_blue_orbit_offset = m_red_orbit_offset;
        m_order[0] = CO_RGB;
    }
    else
    {
        m_red_orbit_offset = option("red_offset").toUInt();
        m_green_orbit_offset = option("green_offset").toUInt();
        m_blue_orbit_offset = option("blue_offset").toUInt();
        m_order[0] = static_cast<COMPONENT_ORDER>(option("order").toUInt());
        QString background = option("background");
        if (background.isEmpty())
        {
            m_has_orbit_background = false;
        }
        else
        {
            m_has_orbit_background = true;
            KeyString keys(background.toStdString());
            int r = keys.GetKeyAsInt("red", 0);
            int g = keys.GetKeyAsInt("green", 0);
            int b = keys.GetKeyAsInt("blue", 0);
            m_orbit_background = QColor(r, g, b);
        }
    }
    m_orbit_scale = stringToLongDouble(std_option("scale"));
    getColourMapMetadata(false);
}

void FractalConfig::getColourMethodMetadata(bool inner)
{
    int index = (inner ? 1 : 0);
    QString prefix = (inner ? "inner_" : "");
    m_method[index] = std_option(prefix + "method");
    if (m_method[index][0] != 'f')
    {
        if (m_method[index][0] != 'i')
        {
            std::string str = std_option(prefix + "divisions");
            if (str.empty()) str = std_option(prefix + "scale");
            m_scale[index] = stringToLongDouble(str);
        }
        m_smooth[index] = (option(prefix + "smooth").toUInt() == 1);
        getColourMapMetadata(inner);
        if (m_level < 7)
        {
            m_red_offset[index] = option(prefix + "colour_offset").toUInt();
            m_green_offset[index] = m_red_offset[index];
            m_blue_offset[index] = m_red_offset[index];
            m_order[index] = CO_RGB;
        }
        else
        {
            m_red_offset[index] = option(prefix + "red_offset").toUInt();
            m_green_offset[index] = option(prefix + "green_offset").toUInt();
            m_blue_offset[index] = option(prefix + "blue_offset").toUInt();
            m_order[index] = static_cast<COMPONENT_ORDER>(option(prefix + "order").toUInt());
        }
        m_abs_log[index] = (option(prefix + "abslog").toUInt() == 1);
    }
}

void FractalConfig::getLyapunovMetadata()
{
    m_ft = F_LYAPUNOV;
    m_method[0] = std_option("method");
    if (m_method[0][0] != 'f')
    {
        std::string str = std_option("divisions");
        if (str.empty()) str = std_option("scale");
        m_scale[0] = stringToLongDouble(str);
        m_smooth[0] = (option("smooth").toUInt() == 1);
    }
    getColourMapMetadata(false);
    if (m_level < 7)
    {
        m_red_offset[0] = option("colour_offset").toUInt();
        m_green_offset[0] = m_red_offset[0];
        m_blue_offset[0] = m_red_offset[0];
        m_order[0] = CO_RGB;
    }
    else
    {
        m_red_offset[0] = option("red_offset").toUInt();
        m_green_offset[0] = option("green_offset").toUInt();
        m_blue_offset[0] = option("blue_offset").toUInt();
        m_order[0] = static_cast<COMPONENT_ORDER>(option("order").toUInt());
    }
    if (m_method[1][0] != 'f')
    {
        std::string str = std_option("inner_divisions");
        if (str.empty()) str = std_option("inner_scale");
        m_scale[1] = stringToLongDouble(str);
        m_smooth[1] = (option("inner_smooth").toInt() == 1);
    }
    getColourMapMetadata(true);
    if (m_level < 7)
    {
        m_red_offset[1] = option("inner_colour_offset").toUInt();
        m_green_offset[1] = m_red_offset[1];
        m_blue_offset[1] = m_red_offset[1];
        m_order[1] = CO_RGB;
    }
    else
    {
        m_red_offset[1] = option("inner_red_offset").toUInt();
        m_green_offset[1] = option("inner_green_offset").toUInt();
        m_blue_offset[1] = option("inner_blue_offset").toUInt();
        m_order[1] = static_cast<COMPONENT_ORDER>(option("inner_order").toUInt());
    }
    // due to change
    m_red_offset[1] = option("inner_colour_offset").toUInt();
    m_green_offset[1] = option("inner_colour_offset").toUInt();
    m_blue_offset[1] = option("inner_colour_offset").toUInt();
    m_lyapunov_sequence = std_option("sequence");
    m_settling_cycles = option("settling_cycles").toInt();
    m_calculating_cycles = option("calculating_cycles").toInt();
}

void FractalConfig::getPickoverPopcornMetadata(OLD_FRACTAL_TYPE ft)
{
//    std::string smodifiers2 = std_option("modifiers2");
    if (m_level == 0)
    {
        std::string h = std_option("h_value");
        std::string a = std_option("a_value");
        std::string b = std_option("b_value");
        if (ft == FT_PICKOVER_POPCORN_5)
        {
            m_ft = F_PICKOVER_POPCORN_6F;
            setParameter(0, h);
            setParameter(1, a);
            setParameter(2, b);
            setParameter(3, h);
            setParameter(4, b);
            setParameter(5, a);
            for (int i = 0; i < 6; i++)
            {
                setFunctionParameter(i, FP_SIN);
            }
            m_number_of_parameters = 6;
            m_number_of_function_parameters = 6;
        }
        else
        {
            m_ft = F_PICKOVER_POPCORN_4F;
            setParameter(0, h);
            setParameter(1, a);
            setParameter(2, h);
            setParameter(3, b);
            m_number_of_parameters = 4;
            m_number_of_function_parameters = 4;
            switch (ft)
            {
            default:
            case FT_PICKOVER_POPCORN:
                setFunctionParameter(0, FP_SIN);                    
                setFunctionParameter(1, FP_TAN);                    
                setFunctionParameter(2, FP_SIN);                    
                setFunctionParameter(3, FP_TAN);
                break;
            case FT_PICKOVER_POPCORN_2:
                setFunctionParameter(0, FP_SIN);                    
                setFunctionParameter(1, FP_SIN);                    
                setFunctionParameter(2, FP_SIN);                    
                setFunctionParameter(3, FP_SIN);
                break;
            case FT_PICKOVER_POPCORN_3:
                setFunctionParameter(0, FP_SIN);                    
                setFunctionParameter(1, FP_COS);                    
                setFunctionParameter(2, FP_SIN);                    
                setFunctionParameter(3, FP_COS);
                break;
            case FT_PICKOVER_POPCORN_4:
                setFunctionParameter(0, FP_COS);                    
                setFunctionParameter(1, FP_COS);                    
                setFunctionParameter(2, FP_SIN);                    
                setFunctionParameter(3, FP_SIN);
                break;
            }
        }
    }
    else
    {
        getParameterMetadata();
    }
    convertParametersToLevel6(static_cast<OLD_FRACTAL_TYPE>(ft));
    m_bailout = B_NONE;
    m_area = 9;
    setComplexParameter(0, StringComplex(), PT_NUMBER);
    m_orbit_plotting = true;
    m_max_iterations = option("max_iterations").toUInt();
    getOrbitColourMethod();
}

void FractalConfig::setFunctionParameter(int index, FUNCTION_PARAMETER fp)
{
    KeyString keys;
    keys.SetKey("id", intToString(static_cast<int>(fp)));
    m_fp[index] = keys.String();
}

void FractalConfig::convertOldFractalTypes(OLD_FRACTAL_TYPE ft)
{
    if (isOldPPMandelbrot(ft))
    {
        if (ft == FT_PP_MANDELBROT_5)
        {
            SetFractalType(F_PICKOVER_POPCORN_6F);
        }
        else
        {
            SetFractalType(F_PICKOVER_POPCORN_4F);
        }
    }
    else if (isOldPPJulia(ft))
    {
        if (ft == FT_PP_JULIA_5)
        {
            SetFractalType(F_PICKOVER_POPCORN_6F);
        }
        else
        {
            SetFractalType(F_PICKOVER_POPCORN_4F);
        }
    }
    int modifiers = option("modifiers").toInt();
    m_number_of_complex_parameters = 1;
    if (isOldPPJulia(ft))
    {
        setComplexParameter(0, StringComplex(std_option("p" + QString::number(modifiers - 1) + "r"),
                                             std_option("p" + QString::number(modifiers - 1) + "i")),
                                             PT_NUMBER);
        modifiers--;
    }
    else
    {
        setComplexParameter(0, StringComplex(), PT_IS_C);
    }
    StringComplex cp[3];
    for (int i = 0; i < modifiers; i++)
    {
        cp[i] = StringComplex(std_option("p" + QString::number(i) + "r"), std_option("p" + QString::number(i) + "i"));
    }
    if ((ft == FT_PP_MANDELBROT_5) || (ft == FT_PP_JULIA_5))
    {
        setParameter(0, cp[0].r);
        setParameter(1, cp[1].r);
        setParameter(2, cp[2].r);
        setParameter(3, cp[0].i);
        setParameter(4, cp[1].i);
        setParameter(5, cp[2].i);
        m_number_of_parameters = 6;
    }
    else
    {
        setParameter(0, cp[0].r);
        setParameter(1, cp[1].r);
        setParameter(2, cp[0].i);
        setParameter(3, cp[1].i);
        m_number_of_parameters = 4;
    }
    m_number_of_function_parameters = 4;
    switch (ft)
    {
    default:
    case FT_PP_MANDELBROT:
    case FT_PP_JULIA:
        setFunctionParameter(0, FP_SIN);
        setFunctionParameter(1, FP_TAN);
        setFunctionParameter(2, FP_SIN);
        setFunctionParameter(3, FP_TAN);
        break;
    case FT_PP_MANDELBROT_2:
    case FT_PP_JULIA_2:
        setFunctionParameter(0, FP_SIN);
        setFunctionParameter(1, FP_SIN);
        setFunctionParameter(2, FP_SIN);
        setFunctionParameter(3, FP_SIN);
        break;
    case FT_PP_MANDELBROT_3:
    case FT_PP_JULIA_3:
        setFunctionParameter(0, FP_SIN);
        setFunctionParameter(1, FP_COS);
        setFunctionParameter(2, FP_SIN);
        setFunctionParameter(3, FP_COS);
        break;
    case FT_PP_MANDELBROT_4:
    case FT_PP_JULIA_4:
        setFunctionParameter(0, FP_COS);
        setFunctionParameter(1, FP_COS);
        setFunctionParameter(2, FP_SIN);
        setFunctionParameter(3, FP_SIN);
        break;
    case FT_PP_MANDELBROT_5:
    case FT_PP_JULIA_5:
        setFunctionParameter(0, FP_SIN);
        setFunctionParameter(1, FP_SIN);
        setFunctionParameter(2, FP_SIN);
        setFunctionParameter(3, FP_SIN);
        setFunctionParameter(4, FP_SIN);
        setFunctionParameter(5, FP_SIN);
        m_number_of_function_parameters = 6;
        break;
    }
}

void FractalConfig::getColourMapMetadata(bool inner)
{
    ColourMap &colours = m_colour_map[(inner ? 1 : 0)];
    colours.clear();
    QString prefix = (inner ? "inner_" : "");
    QString name = option(prefix + "colourmap");
    QRgb c;
    auto type = static_cast<ColourMap::MAP_TYPE>(option(prefix + "colour_map_type").toUInt());
    colours.setType(type);
    if (type == ColourMap::CM_MANUAL)
    {
        int number_of_colours = option(prefix + "number_of_colours").toInt();
        for (int i=0; i<number_of_colours; i++)
        {
            KeyString keys(std_option(prefix + "colour" + QString::number(i)));
            int index = keys.GetKeyAsInt("index", 0);
            c = qRgb(static_cast<int>(keys.GetKeyAsInt("red", 0)),
                     static_cast<int>(keys.GetKeyAsInt("green", 0)),
                     static_cast<int>(keys.GetKeyAsInt("blue", 0)));
            colours.setColour(index, c);
        }
    }
    else if (type == ColourMap::CM_COMPONENT)
    {
        getComponentColour(RGB_RED, prefix + "red", colours);
        getComponentColour(RGB_GREEN, prefix + "green", colours);
        getComponentColour(RGB_BLUE, prefix + "blue", colours);
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            KeyString keys(std_option(prefix + "colour" + QString::number(i)));
            Waveform::AutoColour auto_colour;
            auto_colour.hoffset = keys.GetKeyAsInt("hoffset", 0);
            auto_colour.voffset = keys.GetKeyAsInt("voffset", 0);
            auto_colour.maximum = keys.GetKeyAsInt("maximum", 255);
            auto_colour.wave = static_cast<Waveform::WAVE>(keys.GetKeyAsInt("wave", 0));
            auto_colour.cycles = keys.GetKeyAsInt("cycles", 1);
            colours.setAutoColour(static_cast<RGB>(i), auto_colour);
        }
    }
    if (m_orbit_plotting || isSingleOrbit(m_ft))
    {
        m_orbit_colour_map = name;
    }
    else
    {
        m_colour_map_name[inner ? 1 : 0] = name;
    }
}

void FractalConfig::getComponentColour(RGB colour, const QString& base_name, ColourMap& map)
{
    int number_of_colours = option(base_name + "_colours").toInt();
    for (int i = 0; i < number_of_colours; i++)
    {
        KeyString keys(std_option(base_name + QString::number(i)));
        unsigned int index = static_cast<unsigned int>(keys.GetKeyAsInt("index", 0));
        unsigned int value = static_cast<unsigned int>(keys.GetKeyAsInt("value", 0));
        if (colour == RGB_RED)
        {
            map.setRed(index, value);
        }
        else if (colour == RGB_GREEN)
        {
            map.setGreen(index, value);
        }
        else
        {
            map.setBlue(index, value);
        }
    }
}

void FractalConfig::getParameterMetadata()
{
    // Complex parameters are present in Saturn level 1 and 2 seed files
    QString smodifiers = option("modifiers");
    m_number_of_complex_parameters = smodifiers.toUInt();
    for (unsigned int i = 0; i < m_number_of_complex_parameters; i++)
    {
        QString re = "p" + QString::number(i) + "r";
        QString im = "p" + QString::number(i) + "i";
        QString c_type = "p" + QString::number(i) + "c";
        QString c(option(c_type));
        m_cp[i].p = StringComplex(std_option(re), std_option(im));
        m_cp[i].type = static_cast<PARAMETER_TYPE>(c.toUInt());
    }
    // Non-complex parameters and function parameters are only present in
    // Saturn level 2 and above seed files
    smodifiers = option("modifiers2");
    if (!smodifiers.isEmpty())
    {
        m_number_of_parameters = smodifiers.toUInt();
        for (unsigned int i = 0; i < m_number_of_parameters; i++)
        {
            m_p[i] = std_option("p" + QString::number(i));
        }
        smodifiers = option("modifiers3");
        m_number_of_function_parameters = smodifiers.toUInt();
        for (unsigned int i = 0; i < m_number_of_function_parameters; i++)
        {
            QString key = "f" + QString::number(i);
            KeyString keys(std_option(key));
            if (keys.GetKey("id", "?") == "?")
            {
                auto id = static_cast<OLD_FUNCTION_PARAMETER>(option(key).toUInt());
                m_fp[i] = convert(id);
            }
            else
            {
                // Version 3.0 and later have key strings
                m_fp[i] = std_option(key);
            }
        }
        // Complex Function parameters are available in level 4 seed files and above
        smodifiers = option("modifiers4");
        if (!smodifiers.isEmpty())
        {
            m_number_of_complex_function_parameters = smodifiers.toUInt();
            for (unsigned int i = 0; i < m_number_of_complex_function_parameters; i++)
            {
                QString key = "cf" + QString::number(i);
                KeyString keys(std_option(key));
                if (keys.GetKey("pair", "?") == "?")
                {
                    auto id = static_cast<OLD_COMPLEX_FUNCTION_PARAMETER>(option(key).toUInt());
                    m_cfp[i] = convert(id);
                }
                else
                {
                    // Version 3.0 and later have key strings
                    m_cfp[i] = std_option(key);
                }
            }
        }
    }
}

QString FractalConfig::getColourMapName(bool inner)
{
    return m_colour_map_name[(inner ? 1 : 0)];
}

QString FractalConfig::getOrbitColourMap()
{
    return m_orbit_colour_map;
}

long double FractalConfig::getScale(bool inner)
{
    return m_scale[inner];
}

void FractalConfig::setScale(bool inner, long double value)
{
    m_scale[inner] = value;
}

void FractalConfig::setScale(long double value)
{
    m_scale[m_index] = value;
}

bool FractalConfig::getSmooth(bool inner)
{
    return m_smooth[(inner ? 1 : 0)];
}

bool FractalConfig::getAbsLog(bool inner)
{
    return m_abs_log[(inner ? 1 : 0)];
}

void FractalConfig::setOrbitColourInterval(unsigned int interval)
{
    m_interval = interval;
}

unsigned int FractalConfig::getOrbitColourInterval()
{
    return m_interval;
}

void FractalConfig::setOrbitColourType(char type)
{
    m_orbit_colour_type = type;
}

char FractalConfig::getOrbitColourType()
{
    return m_orbit_colour_type;
}

void FractalConfig::setOrbitScale(long double scale)
{
    m_orbit_scale = scale;
}

long double FractalConfig::getOrbitScale()
{
    return m_orbit_scale;
}

void FractalConfig::setOrbitRedOffset(unsigned int offset)
{
    m_red_orbit_offset = offset;
}

unsigned int FractalConfig::getOrbitRedOffset()
{
    return m_red_orbit_offset;
}

void FractalConfig::setOrbitGreenOffset(unsigned int offset)
{
    m_green_orbit_offset = offset;
}

unsigned int FractalConfig::getOrbitGreenOffset()
{
    return m_green_orbit_offset;
}

void FractalConfig::setOrbitBlueOffset(unsigned int offset)
{
    m_blue_orbit_offset = offset;
}

unsigned int FractalConfig::getOrbitBlueOffset()
{
    return m_blue_orbit_offset;
}

bool FractalConfig::hasColourMaps()
{
    return (!m_colour_map[0].empty() || !m_colour_map[1].empty());
}

ColourMap FractalConfig::getColourMap(bool inner)
{
    return m_colour_map[(inner ? 1 : 0)];
}

void FractalConfig::setColourMap(const ColourMap& map, bool inner)
{
    m_colour_map[inner] = map;
}

unsigned int FractalConfig::widthInPixels()
{
    return m_width_in_pixels;
}

unsigned int FractalConfig::heightInPixels()
{
    return m_height_in_pixels;
}

int FractalConfig::getWidth()
{
    return m_width_in_pixels;
}

void FractalConfig::setWidth(int w)
{
    m_width_in_pixels = w;
}

int FractalConfig::getHeight()
{
    return m_height_in_pixels;
}

void FractalConfig::setHeight(int h)
{
    m_height_in_pixels = h;
}
    
const StringComplex &FractalConfig::getCentre()
{
    return m_centre;
}

void FractalConfig::setCentre(const StringComplex& value)
{
    m_centre = value;
}

void FractalConfig::convertParametersToLevel6(OLD_FRACTAL_TYPE ft)
{
    switch (ft)
    {
    case FT_MANDELBROT: convertSimple_6(F_MANDELBROT, false); break;
    case FT_JULIA: convertSimple_6(F_MANDELBROT, true); break;
    case FT_QUADRATIC: convertSimple_6(F_QUADRATIC, false); break;
    case FT_QUADRATIC_J: convertSimple_6(F_QUADRATIC, true); break;
    case FT_CUBIC: convertSimple_6(F_CUBIC, false); break;
    case FT_CUBIC_J: convertSimple_6(F_CUBIC, true); break;
    case FT_ALMOST_CUBIC: convertSimple_6(F_ALMOST_CUBIC, false); break;
    case FT_ALMOST_CUBIC_J: convertSimple_6(F_ALMOST_CUBIC, true); break;
    case FT_BAD_COMPLEX_POWER: convertBcp_6(false); break;
    case FT_BCP_J: convertBcp_6(true); break;
    case FT_BCP2: convertBcp2_6(false); break;
    case FT_BCP2_J: convertBcp2_6(true); break;
    case FT_COMPLEX_POWER_J: convertSimple_6(F_ZCPAC, true); break;
    case FT_COSCZ: convertCoscz_6(false); break;
    case FT_COSCZ_J: convertCoscz_6(true); break;
    case FT_SINCZ: convertSincz_6(false); break;
    case FT_SINCZ_J: convertSincz_6(true); break;
    case FT_TANCZ: convertTancz_6(false); break;
    case FT_TANCZ_J: convertTancz_6(true); break;
    case FT_ZCPAC: convertZcpac_6(false); break;
    case FT_ZCPAC_J: convertZcpac_6(true); break;
    case FT_Z_POWER_C: convertZpowerC_6(); break;
    case FT_SINCZ_COSCZ: convertSinczCoscz_6(false); break;
    case FT_SINCZ_COSCZ_J: convertSinczCoscz_6(true); break;
    case FT_C_POWER_Z: convertCpowerZ_6(); break;
    case FT_BIOMORPH_1: m_ft = F_BIOMORPH_1; break;
    case FT_BIOMORPH_2: m_ft = F_BIOMORPH_2; break;
    case FT_BIOMORPH_3: m_ft = F_BIOMORPH_3; break;
    case FT_BIOMORPH_4: m_ft = F_BIOMORPH_4; break;
    case FT_BIOMORPH_5: m_ft = F_BIOMORPH_5; break;
    case FT_NOVA: convertSimple_6(F_NOVA, false); break;
    case FT_NOVA_J: convertSimple_6(F_NOVA, true); break;
    case FT_NOVA_1: convertSimple_6(F_NOVA_1, false); break;
    case FT_NOVA_1_J: convertSimple_6(F_NOVA_1, true); break;
    case FT_NOVA_2: convertSimple_6(F_NOVA_2, false); break;
    case FT_NOVA_2_J: convertSimple_6(F_NOVA_2, true); break;
    case FT_QUARTIC: convertSimple_6(F_QUARTIC, false); break;
    case FT_QUARTIC_J: convertSimple_6(F_QUARTIC, true); break;
    case FT_QUINTIC: convertSimple_6(F_QUINTIC,false); break;
    case FT_QUINTIC_J: convertSimple_6(F_QUINTIC, true); break;
    case FT_MAGNET: convertSimple_6(F_MAGNET, false); break;
    case FT_MAGNET_J: convertSimple_6(F_MAGNET, true); break;
    case FT_MAGNET_2: convertSimple_6(F_MAGNET_2, false); break;
    case FT_MAGNET_2_J: convertSimple_6(F_MAGNET_2, true); break;
    case FT_SQRT_CPOWER: convertSimple_6(F_SQRT_CP, false); break;
    case FT_SQRT_CPOWER_J: convertSimple_6(F_SQRT_CP, true); break;
    case FT_COMPASSES: convertCompasses_6(false); break;
    case FT_COMPASSES_J: convertCompasses_6(true); break;
    case FT_PICKOVER_POPCORN_4F: 
    case FT_PP_MANDELBROT_4F: convertSimple_6(F_PICKOVER_POPCORN_4F, false); break;
    case FT_PP_JULIA_4F: convertSimple_6(F_PICKOVER_POPCORN_4F, true); break;
    case FT_PICKOVER_POPCORN_6F:
    case FT_PP_MANDELBROT_6F: convertSimple_6(F_PICKOVER_POPCORN_6F, false); break;
    case FT_PP_JULIA_6F: convertSimple_6(F_PICKOVER_POPCORN_6F, true); break;
    case FT_COMBINATION: convertSimple_6(F_COMBINATION, false); break;
    case FT_COMBINATION_J: convertSimple_6(F_COMBINATION, true); break;
    case FT_COMBINATION_2: convertCombination2_6(); break;
    case FT_COMBINATION_3: convertCombination3_6(); break;
    case FT_COMBINATION_4: convertCombination4_6(); break;
    case FT_UNNAMED: convertUnnamed_6(false); break;
    case FT_UNNAMED_J: convertUnnamed_6(true); break;
    case FT_UNNAMED_2: convertUnnamed2_6(false); break;
    case FT_UNNAMED_2_J: convertUnnamed2_6(true); break;
    case FT_TZACCP: convertTzaccp_6(false); break;
    case FT_TZACCP_J: convertTzaccp_6(true); break;
    case FT_ZACCP: convertZaccp_6(false); break;
    case FT_ZACCP_J: convertZaccp_6(true); break;
    case FT_CCZCPACZCP: convertCczcpaczcp_6(false); break;
    case FT_CCZCPACZCP_J: convertCczcpaczcp_6(true); break;
    case FT_LZCPAC: convertLzcpac_6(false); break;
    case FT_LZCPAC_J: convertLzcpac_6(true); break;
    case FT_LTZCPAC: convertLtzcpac_6(false); break;
    case FT_LTZCPAC_J: convertLtzcpac_6(true); break;
    case FT_TZCPAC: convertSimple_6(F_TZCPAC, false); break;
    case FT_TZCPAC_J: convertSimple_6(F_TZCPAC, true); break;
    case FT_MALLARD: convertMallard_6(false); break;
    case FT_MALLARD_J: convertMallard_6(true); break;
    case FT_TMALLARD: convertTmallard_6(false); break;
    case FT_TMALLARD_J: convertTmallard_6(true); break;
    case FT_ONION_4F: convertSimple_6(F_ONION_4F, false); break;
    case FT_ONION_4F_J: convertSimple_6(F_ONION_4F, true); break;
    case FT_SINGLE_3F_ONION: convertSimple_6(F_SINGLE_3F_ONION, false); break;
    case FT_SINGLE_3F_ONION_J: convertSimple_6(F_SINGLE_3F_ONION, true); break;
    case FT_DOUBLE_3F_ONION_M: convertSimple_6(F_DOUBLE_3F_ONION_M, false); break;
    case FT_DOUBLE_3F_ONION_M_J: convertSimple_6(F_DOUBLE_3F_ONION_M, true); break;
    case FT_DOUBLE_3F_ONION_D: convertSimple_6(F_DOUBLE_3F_ONION_D, false); break;
    case FT_DOUBLE_3F_ONION_D_J: convertSimple_6(F_DOUBLE_3F_ONION_D, true); break;
    case FT_ZCPTANZ: convertSimple_6(F_ZCPTANZ, false); break;
    case FT_ZCPTANZ_J: convertSimple_6(F_ZCPTANZ, true); break;
    case FT_C2MFCZAC: convertSimple_6(F_C2MFCZAC, false); break;
    case FT_C2MFCZAC_J: convertSimple_6(F_C2MFCZAC, true); break;
    case FT_C2DFCZAC: convertSimple_6(F_C2DFCZAC, false); break;
    case FT_C2DFCZAC_J: convertSimple_6(F_C2DFCZAC, true); break;
    case FT_Z_POWER_TANCZ: convertZptanczac_6(false); break;
    case FT_Z_POWER_TANCZ_J: convertZptanczac_6(true); break;
    case FT_RN_MANDELBROT: convertSimple_6(F_RN_MANDELBROT, false); break;
    case FT_RN_JULIA: convertSimple_6(F_RN_MANDELBROT, true); break;
    case FT_ZAZBCGD: convertZazbcgd_6(false); break;
    case FT_ZAZBCGD_J: convertZazbcgd_6(true); break;
    case FT_HYBRID: convertSimple_6(F_HYBRID, false); break;
    case FT_HYBRID_J: convertSimple_6(F_HYBRID, true); break;
    case FT_ZDUCCPAC: convertSimple_6(F_ZDUCCPAC, false); break;
    case FT_ZDUCCPAC_J: convertSimple_6(F_ZDUCCPAC, true); break;
    default: break;
    }
}   

void FractalConfig::convertBcp_6(bool julia)
{
    m_ft = F_SINGLE_FUNCTION;
    auto value = getComplexParameter(0);
    setComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    if (julia)
    {
        setComplexParameterType(1, PT_NUMBER);
    }
    else
    {
        setComplexParameter(1, StringComplex(), PT_IS_C);
        m_number_of_complex_parameters++;
    }
    std::string function_string = "pair=n,id=";
    function_string += intToString(static_cast<int>(CFP_BCP));
    function_string += ",r=" + value.r;
    function_string += ",i=" + value.i;
    setComplexFunctionParameter(0, function_string);
    m_number_of_complex_function_parameters = 1;
}

void FractalConfig::convertBcp2_6(bool julia)
{
    m_ft = F_SINGLE_FUNCTION;
    auto value = getComplexParameter(0);
    setComplexParameter(0, StringComplex("1", "0"), PT_NUMBER);
    if (julia)
    {
        setComplexParameterType(1, PT_NUMBER);
    }
    else
    {
        setComplexParameter(1, StringComplex(), PT_IS_C);
        m_number_of_complex_parameters++;
    }
    std::string function_string = "pair=n,id=";
    function_string += intToString(static_cast<int>(CFP_BCP2));
    function_string += ",r=" + value.r;
    function_string += ",i=" + value.i;
    setComplexFunctionParameter(0, function_string);
    m_number_of_complex_function_parameters = 1;
}

void FractalConfig::convertCoscz_6(bool julia)
{
    m_ft = F_SINGLE_FUNCTION;
    if (julia)
    {
        setComplexParameterType(0, PT_NUMBER);
    }
    else
    {
        setComplexParameter(0, StringComplex("1", "0"), PT_IS_C);
        m_number_of_complex_parameters++;
    }
    setComplexParameter(1, StringComplex(), PT_NUMBER);
    std::string function_string = "pair=n,id=";
    function_string += intToString(static_cast<int>(CFP_COS));
    setComplexFunctionParameter(0, function_string);
    m_number_of_complex_function_parameters = 1;
}

void FractalConfig::convertSincz_6(bool julia)
{
    m_ft = F_SINGLE_FUNCTION;
    if (julia)
    {
        setComplexParameterType(0, PT_NUMBER);
    }
    else
    {
        setComplexParameter(0, StringComplex("1", "0"), PT_IS_C);
        m_number_of_complex_parameters++;
    }
    setComplexParameter(1, StringComplex(), PT_NUMBER);
    std::string function_string = "pair=n,id=";
    function_string += intToString(static_cast<int>(CFP_SIN));
    setComplexFunctionParameter(0, function_string);
    m_number_of_complex_function_parameters = 1;
}

void FractalConfig::convertTancz_6(bool julia)
{
    m_ft = F_SINGLE_FUNCTION;
    if (julia)
    {
        setComplexParameterType(0, PT_NUMBER);
    }
    else
    {
        setComplexParameter(0, StringComplex("1", "0"), PT_IS_C);
        m_number_of_complex_parameters++;
    }
    setComplexParameter(1, StringComplex(), PT_NUMBER);
    std::string function_string = "pair=n,id=";
    function_string += intToString(static_cast<int>(CFP_TAN));
    setComplexFunctionParameter(0, function_string);
    m_number_of_complex_function_parameters = 1;
}

void FractalConfig::convertZcpac_6(bool julia)
{
    m_ft = F_ZCPAC;
    setComplexParameterType(0, PT_NUMBER);
    if (julia)
    {
        setComplexParameterType(1, PT_NUMBER);
    }
    else
    {
        setComplexParameter(1, StringComplex(), PT_IS_C);
        m_number_of_complex_parameters++;
    }
}

void FractalConfig::convertZpowerC_6()
{
    m_ft = F_ZCPAC;
    setComplexParameter(0, StringComplex(), PT_IS_C);
    setComplexParameter(1, StringComplex(), PT_IS_C);
    m_number_of_complex_parameters = 2;
}

void FractalConfig::convertSinczCoscz_6(bool julia)
{
    m_ft = F_2F_PRODUCT;
    auto p = getComplexParameter(0);
    if (julia)
    {
        setComplexParameter(0, p, PT_NUMBER);
        setComplexParameter(1, p, PT_NUMBER);
    }
    else
    {
        setComplexParameterType(0, PT_IS_C);
        setComplexParameterType(1, PT_IS_C);
        m_number_of_complex_parameters++;
    }
    setComplexParameter(2, StringComplex(), PT_NUMBER);
    std::string function_string = "pair=n,id=";
    setComplexFunctionParameter(0, function_string + intToString(static_cast<int>(CFP_SIN)));
    setComplexFunctionParameter(1, function_string + intToString(static_cast<int>(CFP_COS)));
    m_number_of_complex_function_parameters = 2;
}

void FractalConfig::convertCpowerZ_6()
{
    m_ft = F_C_POWER_Z;
    setComplexParameter(0, StringComplex("1", "0"), PT_IS_C);
    setComplexParameter(1, StringComplex("0", "0"), PT_IS_C);
    m_number_of_complex_parameters = 2;
}

void FractalConfig::convertCombination2_6()
{
    m_ft = F_COMBINATION_2;
    setComplexParameterType(4, PT_NUMBER);
    StringComplex p[4];
    for (int i = 0; i < 4; i++)
    {
        p[i] = getComplexParameter(i);
    }
    for (int i = 0; i < 4; i++)
    {
        setComplexParameter(i+1, p[i], PT_NUMBER);
    }
    setComplexParameter(0, StringComplex(), PT_IS_C);
    m_number_of_complex_parameters++;
}

void FractalConfig::convertCombination3_6()
{
    m_ft = F_COMBINATION_3;
    StringComplex p[6];
    for (int i = 0; i < 6; i++)
    {
        p[i] = getComplexParameter(i);
    }
    setComplexParameter(0, StringComplex("1", "0"), PT_IS_C);
    setComplexParameter(1, p[0], PT_NUMBER);
    setComplexParameter(2, p[1], PT_NUMBER);
    setComplexParameter(3, p[2], PT_NUMBER);
    setComplexParameter(4, StringComplex("1", "0"), PT_IS_C);
    setComplexParameter(5, p[3], PT_NUMBER);
    setComplexParameter(6, p[4], PT_NUMBER);
    setComplexParameter(7, p[5], PT_NUMBER);
    m_number_of_complex_parameters += 2;
}

void FractalConfig::convertCombination4_6()
{
    m_ft = F_COMBINATION_3;
    StringComplex p[6];
    for (int i = 0; i < 6; i++)
    {
        p[i] = getComplexParameter(i);
    }
    setComplexParameter(0, p[0], PT_NUMBER);
    setComplexParameter(1, p[1], PT_NUMBER);
    setComplexParameter(2, StringComplex("1", "0"), PT_IS_C);
    setComplexParameter(3, p[2], PT_NUMBER);
    setComplexParameter(4, p[3], PT_NUMBER);
    setComplexParameter(5, p[4], PT_NUMBER);
    setComplexParameter(6, StringComplex("1", "0"), PT_IS_C);
    setComplexParameter(7, p[5], PT_NUMBER);
    m_number_of_complex_parameters += 2;
}

void FractalConfig::convertUnnamed_6(bool julia)
{
    m_ft = F_UNNAMED;
    if (julia)
    {
        StringComplex p[4];
        for (int i = 0; i < 4; i++)
        {
            p[i] = getComplexParameter(i);
        }
        setComplexParameter(0, p[0], PT_NUMBER);
        setComplexParameter(1, p[3], PT_NUMBER);
        setComplexParameter(2, p[1], PT_NUMBER);
        setComplexParameter(3, p[2], PT_NUMBER);
    }
    else
    {
        StringComplex p[3];
        for (int i = 0; i < 3; i++)
        {
            p[i] = getComplexParameter(i);
        }
        setComplexParameter(0, p[0], PT_NUMBER);
        setComplexParameter(1, StringComplex("1", "0"), PT_IS_C);
        setComplexParameter(2, p[1], PT_NUMBER);
        setComplexParameter(3, p[2], PT_NUMBER);
        m_number_of_complex_parameters++;
    }
}

void FractalConfig::convertUnnamed2_6(bool julia)
{
    m_ft = F_UNNAMED_2;
    if (julia)
    {
        StringComplex p[6];
        for (int i = 0; i < 6; i++)
        {
            p[i] = getComplexParameter(i);
        }
        setComplexParameter(0, p[0], PT_NUMBER);
        setComplexParameter(1, p[5], PT_NUMBER);
        setComplexParameter(2, p[1], PT_NUMBER);
        setComplexParameter(3, p[2], PT_NUMBER);
        setComplexParameter(4, p[3], PT_NUMBER);
        setComplexParameter(5, p[4], PT_NUMBER);
    }
    else
    {
        StringComplex p[5];
        for (int i = 0; i < 5; i++)
        {
            p[i] = getComplexParameter(i);
        }
        setComplexParameter(0, p[0], PT_NUMBER);
        setComplexParameter(1, StringComplex("1", "0"), PT_IS_C);
        setComplexParameter(2, p[1], PT_NUMBER);
        setComplexParameter(3, p[2], PT_NUMBER);
        setComplexParameter(4, p[3], PT_NUMBER);
        setComplexParameter(5, p[4], PT_NUMBER);
        m_number_of_complex_parameters++;
    }
}

void FractalConfig::convertTzaccp_6(bool julia)
{
    m_ft = F_TZACCP;
    if (julia)
    {
        auto p = getComplexParameter(0);
        setComplexParameter(0, getComplexParameter(1), PT_NUMBER);
        setComplexParameter(1, p, PT_NUMBER);
    }
    else
    {
        setComplexParameterType(0, PT_IS_C);
        setComplexParameter(1, getComplexParameter(0), PT_NUMBER);
        m_number_of_complex_parameters++;
    }
}

void FractalConfig::convertZaccp_6(bool julia)
{
    m_ft = F_ZACCP;
    if (julia)
    {
        setComplexParameterType(0, PT_NUMBER);
    }
    else
    {
        setComplexParameterType(0, PT_IS_C);
        setComplexParameter(1, getComplexParameter(0), PT_NUMBER);
        m_number_of_complex_parameters++;
    }
}

void FractalConfig::convertCczcpaczcp_6(bool julia)
{
    m_ft = F_CCZCPACZCP;
    if (julia)
    {
        StringComplex p[5];
        for (int i = 0; i < 5; i++)
        {
            p[i] = getComplexParameter(i);
        }
        setComplexParameter(0, p[0], PT_NUMBER);
        setComplexParameter(1, p[1], PT_NUMBER);
        setComplexParameter(2, p[2], PT_NUMBER);
        setComplexParameter(3, p[3], PT_NUMBER);
        setComplexParameter(4, p[4], PT_NUMBER);
    }
    else
    {
        StringComplex p[4];
        for (int i = 0; i < 4; i++)
        {
            p[i] = getComplexParameter(i);
        }
        setComplexParameter(0, StringComplex("1", "0"), PT_IS_C);
        setComplexParameter(1, p[0], PT_NUMBER);
        setComplexParameter(2, p[1], PT_NUMBER);
        setComplexParameter(3, p[2], PT_NUMBER);
        setComplexParameter(4, p[3], PT_NUMBER);
        m_number_of_complex_parameters++;
    }
}

void FractalConfig::convertLzcpac_6(bool julia)
{
    m_ft = F_FZCPAC;
    if (julia)
    {
        setComplexParameterType(1, PT_NUMBER);
    }
    else
    {
        setComplexParameterType(1, PT_IS_C);
        m_number_of_complex_parameters++;
    }
    std::string function_string = "pair=n,id=";
    function_string += intToString(static_cast<int>(CFP_LOG));
    setComplexFunctionParameter(0, function_string);
    m_number_of_complex_function_parameters = 1;
}

void FractalConfig::convertLtzcpac_6(bool julia)
{
    m_ft = F_FTZCPAC;
    if (julia)
    {
        setComplexParameterType(1, PT_NUMBER);
    }
    else
    {
        setComplexParameterType(1, PT_IS_C);
        m_number_of_complex_parameters++;
    }
    std::string function_string = "pair=n,id=";
    function_string += intToString(static_cast<int>(CFP_LOG));
    setComplexFunctionParameter(0, function_string);
    m_number_of_complex_function_parameters = 1;
}

void FractalConfig::convertMallard_6(bool julia)
{
    m_ft = F_MALLARD;
    if (julia)
    {
        auto p = getComplexParameter(2);
        setComplexParameter(2, getComplexParameter(1), PT_NUMBER);
        setComplexParameter(1, p, PT_NUMBER);
    }
    else
    {
        setComplexParameter(2, getComplexParameter(1), PT_NUMBER);
        setComplexParameterType(1, PT_IS_C);
        m_number_of_complex_parameters++;
    }
    std::string function_string = "pair=n,id=";
    function_string += intToString(static_cast<int>(CFP_LOG));
    setComplexFunctionParameter(0, function_string);
    m_number_of_complex_function_parameters = 1;
}

void FractalConfig::convertTmallard_6(bool julia)
{
    m_ft = F_TMALLARD;
    if (julia)
    {
        setComplexParameterType(1, PT_NUMBER);
    }
    else
    {
        setComplexParameter(2, getComplexParameter(1), PT_NUMBER);
        setComplexParameterType(1, PT_IS_C);
        m_number_of_complex_parameters++;
    }
    std::string function_string = "pair=n,id=";
    function_string += intToString(static_cast<int>(CFP_LOG));
    setComplexFunctionParameter(0, function_string);
    m_number_of_complex_function_parameters = 1;
}

void FractalConfig::convertSimple_6(FRACTAL_TYPE ft, bool julia)
{
    m_ft = ft;
    if (!julia)
    {
        m_number_of_complex_parameters++;
    }
    setComplexParameterType(m_number_of_complex_parameters - 1, (julia ? PT_NUMBER : PT_IS_C));
}

void FractalConfig::convertZazbcgd_6(bool julia)
{
    m_ft = F_ZAZBCGD;
    if (julia)
    {
        setComplexParameterType(2, PT_NUMBER);
    }
    else
    {
        m_number_of_complex_parameters++;
        setComplexParameter(4, getComplexParameter(3), PT_NUMBER);
        setComplexParameter(3, getComplexParameter(2), PT_NUMBER);
        setComplexParameter(2, StringComplex("1", "0"), PT_IS_C);
    }
}

void FractalConfig::convertCompasses_6(bool julia)
{
    m_ft = F_COMPASSES;
    if (julia)
    {
        setComplexParameterType(1, PT_NUMBER);
    }
    else
    {
        m_number_of_complex_parameters++;
        setComplexParameter(2, getComplexParameter(1), PT_NUMBER);
        setComplexParameter(1, StringComplex("1", "0"), PT_IS_C);
    }
}

void FractalConfig::convertZptanczac_6(bool julia)
{
    m_ft = F_Z_POWER_TANCZ_AC;
    setComplexParameterType(0, (julia ? PT_NUMBER : PT_IS_C));
    setComplexParameter(1, StringComplex("0", "0"), PT_NUMBER);
}

void FractalConfig::setComponentOrder(COMPONENT_ORDER order, bool inner)
{
    m_order[inner ? 1 : 0] = order;
}

void FractalConfig::setComponentOrder(COMPONENT_ORDER order)
{
    m_order[m_index] = order;
}

COMPONENT_ORDER FractalConfig::getComponentOrder(bool inner)
{
    return m_order[inner ? 1 : 0];
}

void FractalConfig::setRedOffset(unsigned int red, bool inner)
{
    m_red_offset[(inner ? 1 : 0)] = red;
}

void FractalConfig::setGreenOffset(unsigned int green, bool inner)
{
    m_green_offset[(inner ? 1 : 0)] = green;
}

void FractalConfig::setBlueOffset(unsigned int blue, bool inner)
{
    m_blue_offset[(inner ? 1 : 0)] = blue;
}

void FractalConfig::setRedOffset(unsigned int red)
{
    m_red_offset[m_index] = red;
}

void FractalConfig::setGreenOffset(unsigned int green)
{
    m_green_offset[m_index] = green;
}

void FractalConfig::setBlueOffset(unsigned int blue)
{
    m_blue_offset[m_index] = blue;
}

unsigned int FractalConfig::getRedOffset(bool inner)
{
    return m_red_offset[(inner ? 1 : 0)];
}

unsigned int FractalConfig::getGreenOffset(bool inner)
{
    return m_green_offset[(inner ? 1 : 0)];
}

unsigned int FractalConfig::getBlueOffset(bool inner)
{
    return m_blue_offset[(inner ? 1 : 0)];
}

unsigned int FractalConfig::getRedOffset()
{
    return m_red_offset[m_index];
}

unsigned int FractalConfig::getGreenOffset()
{
    return m_green_offset[m_index];
}

unsigned int FractalConfig::getBlueOffset()
{
    return m_blue_offset[m_index];
}

void FractalConfig::setOrbitBackground(const QColor& colour)
{
    m_orbit_background = colour;
}

void FractalConfig::enableOrbitBackground(bool value)
{
    m_has_orbit_background = value;
}

const QColor &FractalConfig::getOrbitBackground()
{
    return m_orbit_background;
}

bool FractalConfig::hasOrbitBackground()
{
    return m_has_orbit_background;
}

std::string FractalConfig::uncompress(std::vector<char>& buffer)
{
    std::string str;
    io::filtering_ostream os;
    os.push(io::zlib_decompressor());
    os.push(io::back_inserter(str));
    int size = buffer.size();
    for (int i = 0; i < size; i++)
    {
        os.put(buffer[i]);
    }
    return str;
}

FractalConfig::CHUNK_TYPE FractalConfig::chunk_type(unsigned char* data)
{
    static std::string text_id = "tEXt";
    static std::string ztxt_id = "zTXt";
    static std::string end_id = "IEND";    // IEND
    CHUNK_TYPE type = CT_IGNORE;
    std::string id;
    id += data[0];
    id += data[1];
    id += data[2];
    id += data[3];
    if (id == text_id)
    {
        type = CT_TEXT;
    }
    else if (id == ztxt_id)
    {
        type = CT_ZTXT;
    }
    else if (id == end_id)
    {
        type = CT_IEND;
    }
    return type;
}

void FractalConfig::setInner(bool inner)
{
    m_index = (inner ? 1 : 0);
}

bool FractalConfig::isInner()
{
    return (m_index == 1);
}


void FractalConfig::setStartingCentre(const StringComplex& value)
{
    m_scentre = value;
}

void FractalConfig::setStartingWidth(const std::string& value)
{
    m_swidth = value;
}

void FractalConfig::setStartingRotation(const unsigned int value)
{
    m_srotation = value;
}

const StringComplex& FractalConfig::getStartingCentre()
{
    return m_scentre;
}

const std::string& FractalConfig::getStartingWidth()
{
    return m_swidth;
}

int FractalConfig::getStartingRotation()
{
    return m_srotation;
}

void FractalConfig::setColourMapName(const QString& name, bool inner)
{
    m_colour_map_name[(inner ? 1 : 0)] = name;    
}

void FractalConfig::setColourMapName(const QString& name)
{
    m_colour_map_name[m_index] = name;    
}

void FractalConfig::setOrbitColourMapName(const QString& name)
{
    m_orbit_colour_map = name;
}

int FractalConfig::getPrecision()
{
    return m_precision;
}

void FractalConfig::setPrecision(int value)
{
    m_precision = value;
}
