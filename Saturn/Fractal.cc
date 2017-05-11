// 
// File:   Fractal.cc
// Author: M.R.Eggleston
//
// Created on 8 October 2009, 09:04
//

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <iomanip>
#include "ColourMaps.h"
#include "Config.h"
#include "Fractal.h"
#include "FractalDrawing.h"
#include "StaticCalculatingUnit.h"
#include "Utilities.h"

using boost::posix_time::microsec_clock;
using boost::posix_time::ptime;
using namespace boost::posix_time;

Fractal::Fractal(QLabel* status)
:
m_status(status),
m_config(),
m_iterate_step_size(8),
m_exitThread(false),
m_finished(false),
#ifdef DEBUG
m_number_of_threads(1),
#else
m_number_of_threads(boost::thread::hardware_concurrency() == 0 ? 1 : boost::thread::hardware_concurrency()),
#endif
m_number_of_orbit_threads(m_number_of_threads),
m_work_threads(new boost::thread[m_number_of_threads]),
m_multi_precision(false),
m_ignore_progress(false),
m_row(0),
m_unit(new CalculatingUnitLD[m_number_of_threads]),
m_mp_unit(new CalculatingUnitMP[m_number_of_threads]),
m_unit_finished(m_number_of_threads),
m_settled(false),
m_settling_cycle(0),
m_calculating_cycle(0),
m_settling_cycles(120),
m_calculating_cycles(600),
m_orbit_plotting(m_config.isOrbitPlotting()),
m_number_of_active_threads(0)
{
    m_config.SetFractalType(Config::instance()->getFractalType());
   // The colour methods are the primary means of determining whether a
    // restart is required by comparing the last used methods with the
    // current methods so when the fractal type is set the methods must be set
    // to the current fractals methods so that comparison is not made with the
    // previous fractals methods.
    m_colouring_method[OUTER] = m_config.getMethod(false);
    m_colouring_method[INNER] = m_config.getMethod(true);

    m_unit[0].enableProgressSignals(true);
    connect(&m_unit[0], SIGNAL(signal_progress(int)), this, SLOT(on_progress_signal(int)));
    connect(&m_unit[0], SIGNAL(signal_so_progress(long, long)), this, SLOT(on_so_progress_signal(long, long)));
    m_mp_unit[0].enableProgressSignals(true);
    connect(&m_mp_unit[0], SIGNAL(signal_progress(int)), this, SLOT(on_progress_signal(int)));
    connect(&m_mp_unit[0], SIGNAL(signal_so_progress(long, long)), this, SLOT(on_so_progress_signal(long, long)));
}

Fractal::~Fractal()
{
    Stop();
}

void Fractal::ZoomIn(const QPoint& centre)
{
    int w = m_config.getWidth();
    int h = m_config.getHeight();
    QPoint press(centre.x() - w/4, centre.y() - h/4);
    QPoint release(press.x() + w/2, press.y() + h/2);
    ZoomIn(press, release);
}

void Fractal::ZoomIn(const QPoint& centre, int width)
{
    int height;
    double ratio = static_cast<double>(m_config.getWidth())/static_cast<double>(m_config.getHeight());
    height = static_cast<int>(static_cast<double>(width)/ratio + 0.5);
    QPoint press(centre.x() - width/2, centre.y() - height/2);
    QPoint release(press.x() + width, press.y() + height);
    ZoomIn(press, release);
}

void Fractal::ZoomIn(const QPoint& p, const QPoint& r)
{
    using std::abs;
    //
    // Determine new top left corner in widow co-ordinates
    // and the width and height in pixels of rectangle
    //
    int iwidth = r.x() - p.x();
    int iheight = r.y() - p.y();
    double x = static_cast<double>(p.x()); // Assume top left is button press
    double y = static_cast<double>(p.y());
    // adjust height of box so that aspect ratio is maintained
    double ratio = static_cast<double>(m_config.getWidth())/static_cast<double>(m_config.getHeight());
    double width = static_cast<double>(iwidth);
    double height = static_cast<double>(iheight);
    width = (width < 0.0 ? -abs(height)*ratio : abs(height)*ratio);
    if (abs(width) < 10.0)
    {
        width = (width < 0.0 ? -10.0 : 10.0);
        height = width/ratio;
    }
    if (abs(height) < 10.0)
    {
        height = (height < 0 ? -10.0 : 10.0);
        width = height*ratio;
    }
    if (width < 0.0) x = x + width;
    if (height < 0.0) y = y + height;
    width = abs(width);
    height = abs(height);
    int precision = StaticCalculatingUnit::s_precision;
    MpReal h(m_config.getHeight(), precision);
    MpReal two("2", precision);
    // Get complex plane co-ordinates of current top left of selection box
    auto c = m_config.getCentre();
    MpReal c_r(c.r, precision);
    MpReal c_i(c.i, precision);
    MpReal w(m_config.getWidth(), precision);
    MpReal mp_x(x, precision);
    MpReal mp_y(y, precision);
    MpReal current_width(m_config.getCurrentWidth(), precision);
    MpReal pitch = current_width/w;
    MpReal topLeft_r = c_r - (w/two - mp_x)*pitch;
    MpReal topLeft_i = c_i + (h/two - mp_y)*pitch;
    //
    // New centre width/2, height/2 relative to x, y
    //
    MpReal mp_width(width, precision);
    MpReal mp_height(height, precision);
    MpReal base_c_r = topLeft_r + (mp_width/two)*pitch;
    MpReal base_c_i = topLeft_i - (mp_height/two)*pitch;
    StaticCalculatingUnit::rotate(base_c_r, base_c_i, c_r, c_i);
    m_config.setCentre(StringComplex(c_r.toString(), c_i.toString()));
    m_config.setCurrentWidth((mp_width*pitch).toString());
    Stop();
    Start();
}
    
void Fractal::ZoomOut(const QPoint& r)
{
    double x = static_cast<double>(r.x());
    double y = static_cast<double>(r.y());
    x = (x < 0.0 ? 0.0 : x);
    x = (x >= m_config.width() ? static_cast<double>(m_config.width()) - 1.0 : x);
    y = (y < 0.0 ? 0.0 : y);
    y = (y >= m_config.height() ? static_cast<double>(m_config.height()) - 1.0 : y);
    int precision = StaticCalculatingUnit::s_precision;
    MpReal image_width(m_config.getWidth(), precision);
    MpReal image_height(m_config.getHeight(), precision);
    int relative_row = static_cast<int>(y) - m_config.getHeight()/2;
    int relative_column = static_cast<int>(x) - m_config.getWidth()/2;
    auto c = m_config.getCentre();
    MpReal c_r(c.r, precision);
    MpReal c_i(c.i, precision);
    MpReal current_width(m_config.getCurrentWidth(), precision);
    MpReal pitch = current_width/image_width;
    MpReal mp_relative_column(relative_column, precision);
    MpReal mp_relative_row(relative_row, precision);
    MpReal base_c_r = c_r + mp_relative_column*pitch;
    MpReal base_c_i = c_i - mp_relative_row*pitch;
    StaticCalculatingUnit::rotate(base_c_r, base_c_i, c_r, c_i);
    current_width += current_width;
    m_config.setCentre(StringComplex(c_r.toString(), c_i.toString()));
    m_config.setCurrentWidth(current_width.toString());
    Stop();
    Start();
}

void Fractal::Reset()
{
    Stop();
    m_config.setCentre(m_config.getStartingCentre());
    m_config.setCurrentWidth(m_config.getStartingWidth());
    m_config.setRotation(m_config.getStartingRotation());
    Start();
}

void Fractal::SetFractalType(FRACTAL_TYPE ft)
{
    Stop();
    m_config.SetFractalType(ft);
   // The colour methods are the primary means of determining whether a
    // restart is required by comparing the last used methods with the
    // current methods so when the fractal type is set the methods must be set
    // to the current fractals methods so that comparison is not made with the
    // previous fractals methods.
    m_colouring_method[OUTER] = m_config.getMethod(false);
    m_colouring_method[INNER] = m_config.getMethod(true);
    Start();
}

void Fractal::Stop()
{
    {
        boost::mutex::scoped_lock lock(m_threads_mutex);
        m_exitThread = true;
        m_ignore_progress = true;
        StaticCalculatingUnit::stop();
    }
    if (m_thread.joinable())
    {
        m_thread.join();
    }
    m_ignore_progress = false;
}

void Fractal::Centre(const QPoint& p)
{
    double x = static_cast<double>(p.x());
    double y = static_cast<double>(p.y());
    x = (x < 0.0 ? 0.0 : x);
    x = (x >= m_config.width() ? m_config.width() - 1.0 : x);
    y = (y < 0.0 ? 0.0 : y);
    y = (y >= m_config.height() ? m_config.height() - 1.0 : y);
    int precision = StaticCalculatingUnit::s_precision;
    MpReal row(y, precision);
    MpReal col(x, precision);
    auto c = m_config.getCentre();
    MpReal c_r(c.r, precision);
    MpReal c_i(c.i, precision);
    MpReal two("2", precision);
    MpReal w(m_config.getWidth(), precision); // in pixels
    MpReal h(m_config.getHeight(), precision); // in pixels
    MpReal current_image_width(m_config.getCurrentWidth(), precision);
    MpReal pitch = current_image_width/w;
    MpReal topLeft_r = c_r - (pitch*w)/two;
    MpReal topLeft_i = c_i + (pitch*h)/two;
    MpReal base_c_r = topLeft_r + col*pitch;
    MpReal base_c_i = topLeft_i - row*pitch;
    StaticCalculatingUnit::rotate(base_c_r, base_c_i, c_r, c_i);
    m_config.setCentre(StringComplex(c_r.toString(), c_i.toString()));
    Stop();
    Start();
}

FRACTAL_TYPE Fractal::GetFractalType()
{
    return m_config.GetFractalType();
}

void Fractal::waitForThreadsToFinish()
{
    for (int i = 0; i < m_number_of_threads; i++)
    {
        m_work_threads[i].join();
    }
}

void Fractal::lyapunovStatus()
{
    QString status;
    std::stringstream str;
    str << std::setfill(' ') << std::setw(8);
    if (m_settled)
    {
        status = "Calculating Cycles: ";
        str << (m_calculating_cycle + static_cast<uint>(m_calculating_cycle < m_calculating_cycles));
        StaticCalculatingUnit::updateImage();
    }
    else
    {
        status = "Settling Cycles: ";
        str << (m_settling_cycle + static_cast<uint>(m_settling_cycle < m_settling_cycles));
    }
    status += QString::fromStdString(str.str());
    if (!m_duration.isEmpty())
    {
        status += "   [" + m_duration + "]";
    }
    m_status->setText(status);
}

void Fractal::bailoutStatus()
{
    QString status;
    if (!m_duration.isEmpty())
    {
        // We must have finished, get an accurate count of the number of iterations
        m_iteration = 0;
        ResultsSet *rs = &StaticCalculatingUnit::s_results[0];
        int size = StaticCalculatingUnit::s_results.size();
        for (int i = 0; i < size; i++)
        {
            if (rs[i].escape > m_iteration)
            {
                m_iteration = rs[i].escape;
            }
        }       
    }
    std::stringstream str;
    str << "Iteration: " << std::setfill(' ') << std::setw(8) << m_iteration;
    status = QString::fromStdString(str.str());
    if (!m_duration.isEmpty())
    {
        status += "   [" + m_duration + "]";
    }
    m_status->setText(status);
}

void Fractal::status()
{
    if (m_config.isQuick() || m_orbit_plotting || m_single_orbit || m_multi_precision)
    {
        update_progress();
    }
    else
    {
        if (m_config.isBailoutFractal())
        {
            bailoutStatus();
        }
        else
        {
            lyapunovStatus();
        }
    }
}

void Fractal::update_progress()
{
    // Called when image is displayed a line at a time or orbit plotting
    if (!m_ignore_progress)
    {
        float r = static_cast<float>(m_row + 1);
        float h = static_cast<float>(m_rows);
        QString str = "Progress: ";
        if (m_orbit_plotting || m_single_orbit)
        {
            StaticCalculatingUnit::updateOrbitImage();
        }
        // When orbit plotting the progress signals are sent provided that no
        // update is in progress so the final may not have been sent so 
        // if duration string is set then calculation is complete.
        float percent = (m_duration.isEmpty() ? 100.0f*(r/h) : 100.0f);
        str += QString::fromStdString(longdoubleToString(percent, true, 2)) + "%  ";
        if (m_precision > BASE_PRECISION)
        {
            str += "Precision: " + QString::number(m_precision) + " bits";
        }
        if (!m_duration.isEmpty())
        {
            str += " [" + m_duration + "]";
            if (!m_orbit_plotting && m_config.isBailoutFractal())
            {
                str += " " + QString::number(StaticCalculatingUnit::s_max_iteration) + " iterations";
            }
        }
         m_status->setText(str);
    }
    if (m_multi_precision)
    {
        m_mp_unit[0].sendProgressSignals(true);
    }
    else
    {
        m_unit[0].sendProgressSignals(true);
    }
}

void Fractal::update_so_progress(long plot, long no_plot)
{
    if (!m_ignore_progress)
    {
        StaticCalculatingUnit::updateOrbitImage();
        QString str;
        if (!m_duration.isEmpty())
        {
            str += "Finished [" + m_duration + "]";
        }
        else
        {
            float p = static_cast<float>(plot);
            float n = static_cast<float>(no_plot);
            float m = static_cast<float>(m_max_iterations);
            str = "Plot: ";
            // When orbit plotting the progress signals are sent provided that no
            // update is in progress so the final may not have been sent so 
            // if duration string is set then calculation is complete.
            float percent = (m_duration.isEmpty() ? 100.0f*(p/m) : 100.0f);
            str += QString::fromStdString(longdoubleToString(percent, true, 2)) + "%  ";
            str += "No plot: ";
            percent = (m_duration.isEmpty() ? 100.0f*(n/m) : 100.0f);
            str += QString::fromStdString(longdoubleToString(percent, true, 2)) + "%  ";
        }
        m_status->setText(str);
    }
    if (m_multi_precision)
    {
        m_mp_unit[0].sendProgressSignals(true);
    }
    else
    {
        m_unit[0].sendProgressSignals(true);
    }
}

void Fractal::QuickThread(int thread_number)
{
    if (m_config.isBailoutFractal())
    {
        if (m_multi_precision)
        {
            m_mp_unit[thread_number].setValues(0, m_max_iterations);
            m_mp_unit[thread_number].calculate();
        }
        else
        {
            m_unit[thread_number].setValues(0, m_max_iterations);
            m_unit[thread_number].calculate();
        }
    }
    else
    {
        if (m_multi_precision)
        {
            m_mp_unit[thread_number].calculateLyapunovRowByRow();
        }
        else
        {
            m_unit[thread_number].calculateLyapunovRowByRow();
        }
    }
}

void Fractal::QuickThread_control()
{
    StaticCalculatingUnit::s_max_iteration = 0;
    ptime start_time(microsec_clock::local_time());
    m_unit[0].enableProgressSignals(true);
    m_mp_unit[0].enableProgressSignals(true);
    for (int j = 0; j < m_number_of_threads; j++)
    {
        m_work_threads[j] = boost::thread(boost::bind(&Fractal::QuickThread, this, j));
    }
    waitForThreadsToFinish();
    ptime end_time(microsec_clock::local_time());
    if (!m_exitThread)
    {
        m_duration = QString::fromStdString(to_simple_string(end_time - start_time));
        m_row = StaticCalculatingUnit::s_height;
        signalStatus();
    }
    m_finished = true;
}

void Fractal::on_progress_signal(int row)
{
    m_row = row;
    if (!StaticCalculatingUnit::s_stop)
    {
        emit signal_row_by_row_progress();
        if (m_multi_precision)
        {
            m_mp_unit[0].sendProgressSignals(true);
        }
        else
        {
            m_unit[0].sendProgressSignals(true);
        }
    }
}

void Fractal::on_so_progress_signal(long plot, long no_plot)
{
    if (!StaticCalculatingUnit::s_stop)
    {
        emit signal_so_progress(plot, no_plot);
        if (m_multi_precision)
        {
            m_mp_unit[0].sendProgressSignals(true);
        }
        else
        {
            m_unit[0].sendProgressSignals(true);
        }
    }
}

void Fractal::changeColours()
{
    std::string signature = m_config.colourSignature();
    if (m_colour_signature != signature)
    {
        m_colour_signature = signature;
        if (restartRequired())
        {
            Stop();
            Start();
        }
        else
        {
            StaticCalculatingUnit::setConfig(m_config.getFractalConfig());
            StaticCalculatingUnit::setColourFunctions();
            if (m_orbit_plotting || m_single_orbit)
            {
                StaticCalculatingUnit::updateOrbitImage();
            }
            else
            {
                StaticCalculatingUnit::updateImage();
            }
        }
    }
}

bool Fractal::restartRequired()
{
    bool reset;
    auto signature = m_config.colourSignature();
    if (m_orbit_plotting || m_single_orbit)
    {
        StaticCalculatingUnit::s_colouring_type = OC_ACCUMULATION;
        char ch = m_config.getOrbitColourType();
        if ((ch >= 'a') && (ch <= 'd'))
        {
            StaticCalculatingUnit::s_colouring_type = static_cast<ORBIT_COLOUR>(ch - 'a');
        }
        // If the current colouring type is average then any colour changed
        // requires a restart.
        reset = (StaticCalculatingUnit::s_colouring_type == OC_AVERAGE);
    }
    else
    {
        std::string method[2] = { m_config.getMethod(false), m_config.getMethod(true) };
        char old_inner_ch = m_colouring_method[INNER][0];
        char old_outer_ch = m_colouring_method[OUTER][0];
        char new_inner_ch = method[INNER][0];
        char new_outer_ch = method[OUTER][0];
        bool was_multiple = (old_inner_ch == 'g') || (old_outer_ch == 'g') ||
                            (old_inner_ch == 'M') || (old_outer_ch == 'M') ||
                            (old_inner_ch == 'A') || (old_outer_ch == 'A') ||
                            (old_inner_ch == 't') || (old_outer_ch == 't') ||
                            (old_inner_ch == 'r') || (old_outer_ch == 'r');
        bool is_multiple = (new_inner_ch == 'g') || (new_outer_ch == 'g') ||
                           (new_inner_ch == 'M') || (new_outer_ch == 'M') ||
                           (new_inner_ch == 'A') || (new_outer_ch == 'A') ||
                           (new_inner_ch == 't') || (new_outer_ch == 't') ||
                           (new_inner_ch == 'r') || (new_outer_ch == 'r');
        reset = (was_multiple != is_multiple);
         // If change from one multiple type to an other then reset calculations.
        if (!reset)
        {
            reset = reset || (was_multiple && is_multiple &&
                             ((old_inner_ch != new_inner_ch) ||
                              (old_outer_ch != new_outer_ch)));
        }
        // Check for change in method that would require a restart.
        // i. Change between angle and change in angle, magnitude and change in magnitude
        if (!reset)
        {
            if (((old_outer_ch == 'A') && (new_outer_ch == 'A')) ||
                ((old_outer_ch == 'M') && (new_outer_ch == 'M')) ||
                ((old_outer_ch == 'r') && (new_outer_ch == 'r')))
            {
                int index = (old_outer_ch == 'r' ? 3 : 1);
                reset = reset || ((m_colouring_method[OUTER][index] < 'a') != (method[OUTER][index] < 'a'));
            }
        }
        if (!reset)
        {
            if (((old_inner_ch == 'A') && (new_inner_ch == 'A')) ||
                ((old_inner_ch == 'M') && (new_inner_ch == 'M')) ||
                ((old_inner_ch == 'r') && (new_inner_ch == 'r')))
            {
                int index = (old_inner_ch == 'r' ? 3 : 1);
                reset = reset || ((m_colouring_method[INNER][index] < 'a') != (method[INNER][index] < 'a'));
            }
        }
        // ii. has gaussian integer type changed?
        if (!reset)
        {
            if ((old_inner_ch == 'g') && (new_inner_ch == 'g'))
            {
                reset = reset || (m_colouring_method[INNER][1] != method[INNER][1]);
            }
        }
        if (!reset)
        {
            if ((old_outer_ch == 'g') && (new_outer_ch == 'g'))
            {
                reset = reset || (m_colouring_method[OUTER][1] != method[OUTER][1]);
            }
        }
        // iii. has orbit trap definition changed
        if (!reset)
        {
            if ((old_outer_ch == 't') && (new_outer_ch == 't'))
            {
                reset = reset ||
                        ((m_colouring_method[OUTER][2] < 'a') != (method[OUTER][2] < 'a')) || // one value and one change in value
                         (m_colouring_method[OUTER][1] != method[OUTER][1]) || // trap type
                         (m_colouring_method[OUTER].substr(4) != method[OUTER].substr(4)); // trap definition
            }
        }
        if (!reset)
        {
            if ((old_inner_ch == 't') && (new_inner_ch == 't'))
            {
                reset = reset ||
                        ((m_colouring_method[INNER][2] < 'a') != (method[INNER][2] < 'a')) || // one value and one change in value
                         (m_colouring_method[INNER][1] != method[INNER][1]) || // trap type
                         (m_colouring_method[INNER].substr(4) != method[INNER].substr(4)); // trap definition
            }
        }
        // iv. has ratio changed
        if (!reset)
        {
            if ((old_outer_ch == 'r') && (new_outer_ch == 'r'))
            {
                reset = reset || (m_colouring_method[OUTER].substr(1, 2) != method[OUTER].substr(1, 2));
            }
        }
        if (!reset)
        {
            if ((old_inner_ch == 'r') && (new_inner_ch == 'r'))
            {
                reset = reset || (m_colouring_method[INNER].substr(1, 2) != method[INNER].substr(1, 2));
            }
        }
        m_colouring_method[INNER] = method[INNER];
        m_colouring_method[OUTER] = method[OUTER];
    }
    return reset;
}

void Fractal::changeCalculatingCycles(unsigned int cycles)
{
    bool restart = (cycles < m_calculating_cycle);
    bool continue_processing = m_finished && (cycles > m_calculating_cycles);
    m_config.setCalculatingCycles(cycles);
    m_calculating_cycles = cycles;
    if (restart)
    {
        Stop();
        Start();
    }
    else if (continue_processing)
    {
        Continue();
    }   
}

void Fractal::changeSettlingCycles(unsigned int cycles)
{
    bool restart = ((cycles < m_settling_cycles) ||
        (m_settled && (cycles != m_config.getSettlingCycles())));
    m_config.setSettlingCycles(cycles);
    m_settling_cycles = cycles;
    if (restart)
    {
        Stop();
        Start();
    }
}

void Fractal::Continue()
{
    m_settled = true;
    m_exitThread = false;
    if (m_config.isQuick())
    {
        m_thread = boost::thread(boost::bind(&Fractal::QuickThread_control, this));
    }
    else
    {
        m_thread = boost::thread(boost::bind(&Fractal::LyapunovThread_control, this));
    }
}

void Fractal::LyapunovThread_control()
{
    ptime start_time(microsec_clock::local_time());
    m_unit[0].enableProgressSignals(false);
    m_number_of_active_threads = m_number_of_threads;
    m_iterate_step_size = m_config.getIterationStepSize();
    StaticCalculatingUnit::firstRow();
    for (int j = 0; j < m_number_of_threads; j++)
    {
        m_unit_finished[j] = false;
        m_work_threads[j] = boost::thread(boost::bind(&Fractal::LyapunovThread, this, j));
    }
    waitForThreadsToFinish();
    ptime end_time(microsec_clock::local_time());
    if (!m_exitThread)
    {
        m_duration = QString::fromStdString(to_simple_string(end_time - start_time));
        signalStatus();
    }
    m_finished = true;
}

void Fractal::LyapunovThread(int number)
{
    bool finished = false;
    if (!m_settled)
    {
        for (auto i = m_settling_cycle; i < m_settling_cycles; i++)
        {
            m_unit_finished[number] = m_unit[number].calculateLyapunovSettlingCycle();
            if (m_number_of_threads == 1)
            {
                finished = m_unit_finished[number];
                m_settling_cycle++;
                signalStatus();
                StaticCalculatingUnit::firstRow();
            }
            else
            {
                boost::mutex::scoped_lock lock(m_threads_mutex);
                m_number_of_active_threads--;
                if (m_number_of_active_threads == 0)
                {
                    m_settling_cycle++;
                    StaticCalculatingUnit::firstRow();
                    signalStatus();
                    finished = true;
                    for (int i = 0; i < m_number_of_threads; i++)
                    {
                        finished = finished & m_unit_finished[i];
                    }
                    if (!finished)
                    {
                        m_number_of_active_threads = m_number_of_threads;
                    }
                    m_threads_condition.notify_all();
                }
                else
                {
                    m_threads_condition.wait(lock);
                }
                if (m_number_of_active_threads == 0)
                {
                    finished = true;
                    break;
                }
            }
        }
        m_settled = true;
    }
    if (!finished)
    {
        for (auto i = m_calculating_cycle; i < m_calculating_cycles; i++)
        {
            // m_calculating_cycle is a counter starting at 0, the
            // cycle number passed in starts at 1 hence the + 1.
            m_unit_finished[number] = m_unit[number].calculateLyapunovCalculatingCycle(m_calculating_cycle + 1);
            if (m_number_of_threads == 1)
            {
                StaticCalculatingUnit::updateImage();
                signalStatus();
                StaticCalculatingUnit::firstRow();
                m_calculating_cycle++;
                if (m_exitThread)
                {
                    break;
                }
            }
            else
            {
                boost::mutex::scoped_lock lock(m_threads_mutex);
                m_number_of_active_threads--;
                if (m_number_of_active_threads == 0)
                {
                    StaticCalculatingUnit::firstRow();
                    m_calculating_cycle++;
                    StaticCalculatingUnit::updateImage();
                    signalStatus();
                    finished = true;
                    for (int i = 0; i < m_number_of_threads; i++)
                    {
                        finished = finished & m_unit_finished[i];
                    }
                    if (!finished)
                    {
                        m_number_of_active_threads = m_number_of_threads;
                    }
                    m_threads_condition.notify_all();
                }
                else
                {
                    m_threads_condition.wait(lock);
                }
                if (m_number_of_active_threads == 0)
                {
                    break;
                }
            }
        }
    }
}

void Fractal::changeIterations(int iterations)
{
    auto max = m_config.getMaxIterations();
    if (max == iterations)
    {
        return;
    }
    bool restart = false;
    if (m_config.isOrbitPlotting() || m_single_orbit || m_config.isQuick() || m_multi_precision )
    {
        restart = true;
    }
    else
    {
        restart = (m_iteration > iterations);
    }
    m_config.setMaxIterations(iterations);
    if (restart)
    {
        Stop();
        Start();
    }
    else
    {
        m_duration.clear();
        m_max_iterations = iterations;
        if (m_finished && (iterations > max))
        {
            m_exitThread = false;
            m_thread = boost::thread(boost::bind(&Fractal::EscapeThread_control, this));
        }
    }
}

void Fractal::EscapeThread_control()
{
    ptime start_time(microsec_clock::local_time());
    m_unit[0].enableProgressSignals(false);
    m_iterate_step_size = m_config.getIterationStepSize();
    StaticCalculatingUnit::firstRow();
    m_number_of_active_threads = m_number_of_threads;
    for (int j = 0; j < m_number_of_threads; j++)
    {
        m_unit_finished[j] = false;
        m_work_threads[j] = boost::thread(boost::bind(&Fractal::EscapeThread, this, j));
    }
    waitForThreadsToFinish();
    ptime end_time(microsec_clock::local_time());
    if (!m_exitThread)
    {
        m_duration = QString::fromStdString(to_simple_string(end_time - start_time));
        signalStatus();
    }
    m_finished = true;
}

void Fractal::EscapeThread(int number)
{
    bool finished = false;
    for (int i = m_iteration; i < m_max_iterations; i += m_iterate_step_size)
    {
        int step = m_iterate_step_size;
        if ((i + step) > m_max_iterations)
        {
            step = m_max_iterations - i;
        }
        m_unit[number].setValues(m_iteration, step);
        m_unit_finished[number] = m_unit[number].calculate();
        if (m_number_of_threads == 1)
        {
            if (m_unit_finished[number])
            {
                break;
            }
            if ((m_max_iterations - m_iteration) < m_iterate_step_size)
            {
                m_iterate_step_size = m_max_iterations - m_iteration;
            }
            m_iteration += m_iterate_step_size;
            signalStatus();
            StaticCalculatingUnit::firstRow();
        }
        else
        {
            boost::mutex::scoped_lock lock(m_threads_mutex);
            m_number_of_active_threads--;
            if (m_number_of_active_threads == 0)
            {
                if ((m_max_iterations - m_iteration) < m_iterate_step_size)
                {
                    m_iterate_step_size = m_max_iterations - m_iteration;
                }
                m_iteration += m_iterate_step_size;
                signalStatus();
                StaticCalculatingUnit::firstRow();
                finished = true;
                for (int i = 0; i < m_number_of_threads; i++)
                {
                    finished = finished & m_unit_finished[i];
                }
                if (!finished)
                {
                    m_number_of_active_threads = m_number_of_threads;
                }
                m_threads_condition.notify_all();
            }
            else
            {
                m_threads_condition.wait(lock);
            }
            if (m_number_of_active_threads == 0)
            {
                break;
            }
        }
    }
}

void Fractal::waitForOrbitThreadsToFinish()
{
    for (int i = 0; i < m_number_of_orbit_threads; i++)
    {
        m_work_threads[i].join();
    }
}

void Fractal::OrbitThread_control()
{
    ptime start_time(microsec_clock::local_time());
    if (m_single_orbit)
    {
        m_number_of_orbit_threads = 1;
    }
    else
    {
        m_number_of_orbit_threads = (StaticCalculatingUnit::s_colouring_type == OC_AVERAGE ? 1 : m_number_of_threads);
    }
    m_unit[0].enableProgressSignals(true);
    for (int i = 0; i < m_number_of_orbit_threads; i++)
    {
        m_work_threads[i] = boost::thread(boost::bind(&Fractal::OrbitThread, this, i, m_single_orbit));
    }
    waitForOrbitThreadsToFinish();
    ptime end_time(microsec_clock::local_time());
    m_duration = QString::fromStdString(to_simple_string(end_time - start_time));
    if (m_single_orbit)
    {
        signalSOStatus();
    }
    else
    {
        signalStatus();
    }
    m_finished = true;
}

void Fractal::OrbitThread(int thread_number, bool single_orbit)
{
    m_unit[thread_number].setValues(0, m_max_iterations);
    if (single_orbit)
    {
        m_unit[thread_number].calculateOrbit();
    }
    else
    {
        m_unit[thread_number].calculateOrbits();
    }
}

void Fractal::Start()
{
    m_finished = false;
    auto config = m_config.getFractalConfig();
    StaticCalculatingUnit::setFractal(config, m_config.isQuick()); // Set common data
    m_orbit_plotting = m_config.isOrbitPlotting();
    m_single_orbit = m_config.isSingleOrbit();
    m_max_iterations = m_config.getMaxIterations();
    if (m_single_orbit || !m_orbit_plotting)
    {
        m_rows = StaticCalculatingUnit::s_height;
    }
    else
    {
        auto height = StaticCalculatingUnit::s_calculating_height;
        auto density_factor = StaticCalculatingUnit::s_density_factor;
        m_rows = static_cast<int>(static_cast<long double>(height)*density_factor);
    }

    for (int i = 0; i < m_number_of_threads; i++)
    {
        // set per unit data
        m_unit[i].setFractal();
        m_mp_unit[i].setFractal();
    }
    
    m_iteration = 0;
    
    if (!m_config.isBailoutFractal())
    {
        m_settling_cycles = m_config.getSettlingCycles();
        m_calculating_cycles = m_config.getCalculatingCycles();
        m_settled = false;
        m_settling_cycle = 0;
        m_calculating_cycle = 0;
        StaticCalculatingUnit::initialiseLyapunovData();
    }
    else if (!m_single_orbit && !m_orbit_plotting)
    {
        StaticCalculatingUnit::initialiseData();
    }

    m_duration.clear();
    m_precision = StaticCalculatingUnit::s_precision;
    m_multi_precision = (m_orbit_plotting ? false : StaticCalculatingUnit::s_multi_precision);
    if (!m_config.isBailoutFractal())
    {
        if (m_multi_precision)
        {
            for (auto i = 0; i < m_number_of_threads; i++)
            {
                m_mp_unit[i].setLyapunov();
            }
        }
        else
        {
            for (auto i = 0; i < m_number_of_threads; i++)
            {
                m_unit[i].setLyapunov();
            }   
        }
    }
    m_colour_signature = m_config.colourSignature();
    m_exitThread = false;
    StaticCalculatingUnit::s_stop = false;
    if (m_orbit_plotting || m_single_orbit)
    {
        m_status->setText(m_single_orbit ? "Plot: 0.00% No plot: 0.00%" : "Progress: 0.00%");
        m_thread = boost::thread(boost::bind(&Fractal::OrbitThread_control, this));
    }
    else if (m_config.isQuick())
    {
        QString str("Progress: 0.00%");
        if (m_precision > BASE_PRECISION)
        {
            str += " Precision: " + QString::number(m_precision) + "bits";
        }
        m_status->setText(str);
        StaticCalculatingUnit::firstRow();
        m_thread = boost::thread(boost::bind(&Fractal::QuickThread_control, this));
    }
    else if (m_config.isBailoutFractal())
    {
        status();
        m_thread = boost::thread(boost::bind(&Fractal::EscapeThread_control, this));
    }
    else
    {
        status();
        m_thread = boost::thread(boost::bind(&Fractal::LyapunovThread_control, this));
    }
}
