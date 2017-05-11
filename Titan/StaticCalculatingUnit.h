//
// File:   StaticCalculatingUnit.h
// Author: M.R.Eggleston
//
// Created on 02 July 2012, 08:41
//

#pragma once

#ifdef NOT_MOC
#include <boost/thread/mutex.hpp>
#endif
#include <QPainter>
#include <QPixmap>
#include "mpcomplex.h"
#include "Colours.h"
#include "FractalConfig.h"
#include "OrbitTraps.h"
#include "Transform.h"
#include "TypesAndConstants.h"

class StaticCalculatingUnit
{
public:
    static void setFractal(const FractalConfig &config, bool quick);
    static void setConfig(const FractalConfig &config); // only updates the configuration object
    static void stop();
    static bool finished();
    static const QRgb *getColours();
    
    static int nextRow();
    static void firstRow();
    static void initialiseData();
    static void initialiseLyapunovData();
    static void initialiseResultsSet(ResultsSet& rs, const LongComplex& z);
    static void startingValues(int col, int row,
                               MpComplex& z,
                               MpComplex& c);
    static void setZandC(MpComplex& z,  // out
                         MpComplex& c); // in/out
    static void setZandC(LongComplex& z,  // out
                         LongComplex& c); // in/out
    static void setDimensions(int width, int height);
    static void updateImage(ResultsSet *rs, int col, int row);
    static void updateImage(long double lyap, int col, int row);
    static void updateImage();
    static void updateImageLine(int row);
    static void updateOrbitImage();
    static bool is_outer(ResultsSet *rs);
    static void setColourFunctions();
    static void setStatistics(bool inner, bool second, long double scale);
    static void setGaussian(bool inner, bool second, long double scale, long double angle_scale);
    static void setOrbitTrap(bool inner, bool second, long double scale);
    static void deltaResults(bool inner, bool second);
    static void numberOfResultsSetsRequired();
    static int getTransformSet(int i);
    
    static bool lt_value(long double value);
    static bool gt_value(long double value);
    static bool lt_abs_value(long double value);
    static bool gt_abs_value(long double value);

    static void assignTrap(bool inner, bool second);
    static QRgb GetColour(unsigned int r, unsigned int g, unsigned int b);
    static void allocateColours(unsigned int size);
    static void setOrbitColourMap();
    static void plot(const VectorLongComplex& orbit, int plot_length, bool escaped);
    static bool plot(long double x, long double y);
    
    static void setRotationMatrix();
    static void rotate(long double a, long double b, long double& ar, long double& br);
    static void rotate(const MpReal& a, const MpReal& b, MpReal& ar, MpReal& br);
    static void updateMaxIteration(int iterations);
    static void paintImage(QPainter& painter);

    static FRACTAL_TYPE s_type;
    static FractalConfig s_config;
    static VectorResultsSet s_results;
    static VectorLyapunovResultsSet s_lyapunov_results;
    static long double s_limit;
    static VectorInt s_sequence;
    static unsigned int s_sequence_length;
    static int s_number_of_sets; // transforms
    static bool s_convergent;
    static BAILOUT s_bailout_type;
    static int s_size;
    static int s_width;
    static int s_height;
    static int s_calculating_width;
    static int s_calculating_height;
    static int s_number_of_results_sets;
    enum RESULTS_SET
    {
        RS_ANGLE,
        RS_MAGNITUDE,
        RS_GAUSSIAN,
        RS_ORBIT_TRAP
    };
    static RESULTS_SET s_results_set[2];
    static bool s_change[2];
    static bool s_angle[2];
    static boost::mutex s_row_mutex;
    static int s_current_row;
    static bool s_stop;
    static INITIAL_VALUE s_value_type;
    static MpComplex s_z0;
    static LongComplex s_ld_z0;
    static int s_rotation;
    static MpReal s_topleft_r;
    static MpReal s_topleft_i;
    static MpReal s_pitch;
    static MpReal s_r11;
    static MpReal s_r21;
    static MpReal s_tx;
    static MpReal s_r12;
    static MpReal s_r22;
    static MpReal s_ty;
    static long double s_ld_topleft_r;
    static long double s_ld_topleft_i;
    static long double s_orbit_topleft_r;
    static long double s_orbit_topleft_i;
    static long double s_ld_r11;
    static long double s_ld_r21;
    static long double s_ld_tx;
    static long double s_ld_r12;
    static long double s_ld_r22;
    static long double s_ld_ty;
    static bool s_is_rotated;
    static bool s_has_cp_transforms;
    static Transform<long double, LongComplex> s_cp_transform;
    static Transform<MpReal, MpComplex> s_mp_cp_transform;
    static bool s_is_biomorph_selection;
    static QImage s_image;
    static unsigned int s_n_channels;
    static unsigned int s_rowstride;
    static Colours s_colours[2];
    static std::string s_colouring_method[2];
    static char s_magnitude_type[2];
    static char s_quotient[2];
    static char s_divisor[2];
    static long double s_select_limit;
    enum GAUSSIAN_INTEGER_TYPE
    {
        GI_CEIL,
        GI_FLOOR,
        GI_ROUND,
        GI_TRUNC
    };
    
    static GAUSSIAN_INTEGER_TYPE s_gaussian_type[2];
    // Biomorph colour selection
    static char s_variable1;
    static char s_variable2;
    static char s_comparison1;
    static char s_comparison2;
    static char s_combination;
    static boost::shared_ptr<OrbitTrap> s_trap[2];
    static boost::mutex s_colour_mutex;
    static bool s_retain_results;
    // Orbit plotting picture data
    static ORBIT_COLOUR s_colouring_type;
    static VectorInt s_hits;
    static VectorColourAccumulator s_colour_totals;
    static VectorInt s_orbit_reds;
    static VectorInt s_orbit_greens;
    static VectorInt s_orbit_blues;
    static unsigned int s_number_of_orbit_reds;
    static unsigned int s_number_of_orbit_greens;
    static unsigned int s_number_of_orbit_blues;
    static int s_omit;
    static ORBIT_PLOTS s_orbit_plot_type;
    static long s_interval;
    static long s_colour_change_interval;
    static int s_red;
    static int s_green;
    static int s_blue;
    static long double s_min_x;
    static long double s_max_x;
    static long double s_min_y;
    static long double s_max_y;
    static long double s_ld_pitch;
    static boost::mutex s_plot_mutex;
    static bool s_average_colouring;
    static int s_settling_cycles;
    static boost::mutex s_max_iteration_mutex;
    static int s_max_iteration;
    static int s_precision;
    static bool s_multi_precision;
    static long double s_density_factor;
    static QRgb s_background;
    static bool s_has_background;
};

inline void StaticCalculatingUnit::startingValues(int column,
                                                  int row,
                                                  MpComplex& z,
                                                  MpComplex& c)
{
    MpReal col(column, s_precision);
    MpReal r(row, s_precision);
    MpReal c_r = s_topleft_r + col*s_pitch;
    MpReal c_i = s_topleft_i - r*s_pitch;
    if (s_is_rotated)
    {
        MpReal new_c_r = c_r*s_r11 + c_i*s_r21 + s_tx;
        MpReal new_c_i = c_r*s_r12 + c_i*s_r22 + s_ty;
        c_r = new_c_r;
        c_i = new_c_i;
    }
    c = MpComplex(c_r, c_i);
    MpComplex t = c;
    if (s_has_cp_transforms)
    {
        t = s_mp_cp_transform(c);
    }
    if (s_value_type == FIXED)
    {
        z = s_z0;
    }
    else if (s_value_type == UNTRANSFORMED)
    {
        z = c;
    }
    else
    {
        z = t;
    }
    c = t;
}

inline void StaticCalculatingUnit::setZandC(MpComplex& z,
                                            MpComplex& c)
{
    if (s_is_rotated)
    {
        MpReal new_c_r = real(c)*s_r11 + imag(c)*s_r21 + s_tx;
        MpReal new_c_i = real(c)*s_r12 + imag(c)*s_r22 + s_ty;
        c = MpComplex(new_c_r, new_c_i);
    }
    MpComplex t = c;
    if (s_has_cp_transforms)
    {
        t = s_mp_cp_transform(c);
    }
    if (s_value_type == FIXED)
    {
        z = s_z0;
    }
    else if (s_value_type == UNTRANSFORMED)
    {
        z = c;
    }
    else
    {
        z = t;
    }
    c = t;
}

inline void StaticCalculatingUnit::setZandC(LongComplex& z,
                                            LongComplex& c)
{
    if (s_is_rotated)
    {
        long double new_c_r = real(c)*s_ld_r11 + imag(c)*s_ld_r21 + s_ld_tx;
        long double new_c_i = real(c)*s_ld_r12 + imag(c)*s_ld_r22 + s_ld_ty;
        c = LongComplex(new_c_r, new_c_i);
    }
    LongComplex t = c;
    if (s_has_cp_transforms)
    {
        t = s_cp_transform(c);
    }
    if (s_value_type == FIXED)
    {
        z = s_ld_z0;
    }
    else if (s_value_type == UNTRANSFORMED)
    {
        z = c;
    }
    else
    {
        z = t;
    }
    c = t;
}

inline bool StaticCalculatingUnit::finished()
{
    if (s_type == F_LYAPUNOV)
    {
        return false;
    }
    bool finished = true;
    for (int i = 0; i < s_size; i++)
    {
        if (!s_results[i].done)
        {
            finished = false;
            break;
        }
    }
    return finished;
}

inline void StaticCalculatingUnit::updateImage(ResultsSet *rs, int col, int row)
{
    int index = ((s_is_biomorph_selection ? is_outer(rs) : rs->done) ? 0 : 1);
    boost::mutex::scoped_lock lock(s_colour_mutex);
    s_image.setPixel(col, row, s_colours[index].getColour(rs));
}

inline void StaticCalculatingUnit::updateImage(long double lyap, int col, int row)
{
    int index = (lyap > 0.0L ? 1 : 0);
    boost::mutex::scoped_lock lock(s_colour_mutex);
    s_image.setPixel(col, row, s_colours[index].getColour(lyap));
}

inline void StaticCalculatingUnit::updateImageLine(int row)
{
    boost::mutex::scoped_lock lock(s_colour_mutex);
    ResultsSet* rs = &(s_results[row*s_width]);
    QRgb *pixel = reinterpret_cast<QRgb *>(s_image.scanLine(row));
    if (s_is_biomorph_selection)
    {
        for (int i = 0; i < s_width; i++, rs++)
        {
            pixel[i] = s_colours[!is_outer(rs)].getColour(rs);
        }
    }
    else
    {
        for (int i = 0; i < s_width; i++, rs++)
        {
            pixel[i] = s_colours[!rs->done].getColour(rs);
        }
    }
}

inline void StaticCalculatingUnit::updateImage()
{
    boost::mutex::scoped_lock lock(s_colour_mutex);
    if (s_type == F_LYAPUNOV)
    {
        if (s_lyapunov_results.size() > 0)
        {
            LyapunovResultsSet* rs = &s_lyapunov_results[0];
            for (int row = 0; row < s_height; row++)
            {
                QRgb *pixel = reinterpret_cast<QRgb *>(s_image.scanLine(row));
                for (int i = 0; i < s_width; i++, rs++)
                {
                    pixel[i] = s_colours[rs->lyap > 0.0L].getColour(rs->lyap);
                }
            }
        }
    }
    else if (s_is_biomorph_selection)
    {
        if (s_results.size() > 0)
        {
            ResultsSet* rs = &s_results[0];
            for (int row = 0; row < s_height; row++)
            {
                QRgb *pixel = reinterpret_cast<QRgb *>(s_image.scanLine(row));
                for (int i = 0; i < s_width; i++, rs++)
                {
                    pixel[i] = s_colours[!is_outer(rs)].getColour(rs);
                }
            }
        }
    }
    else
    {
        if (s_results.size() > 0)
        {
            ResultsSet* rs = &s_results[0];
            for (int row = 0; row < s_height; row++)
            {
                QRgb *pixel = reinterpret_cast<QRgb *>(s_image.scanLine(row));
                for (int i = 0; i < s_width; i++, rs++)
                {
                    pixel[i] = s_colours[!rs->done].getColour(rs);
                }
            }
        }
    }
}

inline bool StaticCalculatingUnit::is_outer(ResultsSet *rs)
{
    bool first = false;
    bool second = false;
    if (s_variable1 == 'a')
    {
        first = (s_comparison1 == '<' ? lt_abs_value(rs->z_r) : gt_abs_value(rs->z_r));
    }
    else
    {
        first = (s_comparison1 == '<' ? lt_value(rs->z_r) : gt_value(rs->z_r));
    }
    if (s_variable2 == 'a')
    {
        second = (s_comparison2 == '<' ? lt_abs_value(rs->z_i) : gt_abs_value(rs->z_i));
    }
    else
    {
        second = (s_comparison2 == '<' ? lt_value(rs->z_i) : gt_value(rs->z_i));
    }
    switch(s_combination)
    {
        default:
        case 'a': return first && second;
        case 'o': return first || second;
        case 'x': return first != second;
    }
}

inline bool StaticCalculatingUnit::lt_value(long double value)
{
    return (value < s_select_limit);
}

inline bool StaticCalculatingUnit::gt_value(long double value)
{
    return (value > s_select_limit);
}

inline bool StaticCalculatingUnit::lt_abs_value(long double value)
{
    return (std::abs(value) < s_select_limit);
}

inline bool StaticCalculatingUnit::gt_abs_value(long double value)
{
    return (std::abs(value) > s_select_limit);
}

inline void StaticCalculatingUnit::plot(const VectorLongComplex& orbit, int plot_length, bool escaped)
{
    boost::mutex::scoped_lock lock(s_colour_mutex);
    if ((((s_orbit_plot_type == OP_ALL) ||
         ((s_orbit_plot_type == OP_ESCAPED) && escaped) ||
         ((s_orbit_plot_type == OP_CAPTIVE) && !escaped))))
    {
        for (int orbit_index = 0; orbit_index < plot_length; orbit_index++)
        {
            long double x = orbit[orbit_index].real();
            long double y = orbit[orbit_index].imag();
            //
            // Need to reverse any image rotation here
            //
            if (s_average_colouring)
            {
                s_interval++;
                if (s_interval == s_colour_change_interval)
                {
                    s_interval = 0;
                    s_red = (s_red + 1) % s_number_of_orbit_reds;
                    s_green = (s_green + 1) % s_number_of_orbit_greens;
                    s_blue = (s_blue + 1) % s_number_of_orbit_blues;
                }
            }
            if ((x >= s_min_x) && (x < s_max_x) && (y >= s_min_y) && (y < s_max_y))
            {
                int i = static_cast<int>((x - s_min_x)/s_ld_pitch);
                int j = static_cast<int>((s_max_y - y)/s_ld_pitch);
                if ((i >= 0) && (i < s_width) && (j >= 0) && (j < s_height))
                {
                    int pos = i + j*s_width;
                    boost::mutex::scoped_lock lock(s_plot_mutex);
                    s_hits[pos]++;
                    if (s_average_colouring)
                    {
                        QRgb colour = GetColour(s_red, s_green, s_blue);
                        s_colour_totals[pos].red += qRed(colour);
                        s_colour_totals[pos].green += qGreen(colour);
                        s_colour_totals[pos].blue += qBlue(colour);
                    }
                }
            }
        }
    }
}

inline bool StaticCalculatingUnit::plot(long double x, long double y)
{
    bool visible = false;
    boost::mutex::scoped_lock lock(s_colour_mutex);
        //
        // Need to reverse any image rotation here ????
        //
    if (s_average_colouring)
    {
        s_interval++;
        if (s_interval == s_colour_change_interval)
        {
            s_interval = 0;
            s_red = (s_red + 1) % s_number_of_orbit_reds;
            s_green = (s_green + 1) % s_number_of_orbit_greens;
            s_blue = (s_blue + 1) % s_number_of_orbit_blues;
        }
    }
    if ((x >= s_min_x) && (x < s_max_x) && (y >= s_min_y) && (y < s_max_y))
    {
        int i = static_cast<int>((x - s_min_x)/s_ld_pitch);
        int j = static_cast<int>((s_max_y - y)/s_ld_pitch);
        if ((i >= 0) && (i < s_width) && (j >= 0) && (j < s_height))
        {
            visible = true;
            int pos = i + j*s_width;
            boost::mutex::scoped_lock lock(s_plot_mutex);
            s_hits[pos]++;
            if (s_average_colouring)
            {
                QRgb colour = GetColour(s_red, s_green, s_blue);
                s_colour_totals[pos].red += qRed(colour);
                s_colour_totals[pos].green += qGreen(colour);
                s_colour_totals[pos].blue += qBlue(colour);
            }
        }
    }
    return visible;
}

inline QRgb StaticCalculatingUnit::GetColour(unsigned int r, unsigned int g, unsigned int b)
{
    return qRgb(s_orbit_reds[r % s_number_of_orbit_reds],
                s_orbit_greens[g % s_number_of_orbit_greens],
                s_orbit_blues[b % s_number_of_orbit_blues]);
}

inline int StaticCalculatingUnit::getTransformSet(int i)
{
    return s_sequence[i];
}

inline void StaticCalculatingUnit::updateMaxIteration(int iteration)
{
    boost::mutex::scoped_lock lock(s_max_iteration_mutex);
    if (iteration > s_max_iteration)
    {
        s_max_iteration = iteration;
    }
}

inline void StaticCalculatingUnit::rotate(long double a, long double b, long double&ar, long double&br)
{
    if (s_is_rotated)
    {
        ar = a*s_ld_r11 + b*s_ld_r21 + s_ld_tx;
        br = a*s_ld_r12 + b*s_ld_r22 + s_ld_ty;
    }
    else
    {
        ar = a;
        br = b;
    }
}

inline void StaticCalculatingUnit::rotate(const MpReal& a, const MpReal& b, MpReal& ar, MpReal& br)
{
    if (s_is_rotated)
    {
        ar = a*s_r11 + b*s_r21 + s_tx;
        br = a*s_r12 + b*s_r22 + s_ty;
    }
    else
    {
        ar = a;
        br = b;
    }
}
