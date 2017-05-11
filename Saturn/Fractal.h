//
// File:   Fractal.h
// Author: M.R.Eggleston
//
// Created on <unknown>
//

#pragma once

#ifdef NOT_MOC
#include <boost/scoped_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#endif
#include <QStatusBar>
#include "mpreal.h"
#include "CalculatingUnitLD.h"
#include "CalculatingUnitMP.h"
#include "ColourMaps.h"
#include "Colours.h"
#include "FractalsConfig.h"
#include "FractalDrawing.h"
#include "TypesAndConstants.h"

class Fractal : public QObject
{
    Q_OBJECT
   
signals:
    void signal_row_by_row_progress();
    void signal_progressive_progress();
    void signal_so_progress(long plot, long no_plot);
    
private slots:
    void on_progress_signal(int row);
    void on_so_progress_signal(long plot, long no_plot);

public:
    Fractal(QLabel* status);
    virtual ~Fractal();
    void Centre(const QPoint& press);
    FRACTAL_TYPE GetFractalType();
    void Reset();
    void SetFractalType(FRACTAL_TYPE ft);
    void Start();
    void Stop();
    // px, p_y -> pres co-ordinates, r_x, r_y -> release co-ordinates
    void ZoomIn(const QPoint& press, const QPoint& release);
    void ZoomIn(const QPoint& centre);
    void ZoomIn(const QPoint& centre, int width);
    void ZoomOut(const QPoint& press);
    
    void changeColours();
    void changeCalculatingCycles(unsigned int cycles);
    void changeSettlingCycles(unsigned int cycles);
    void changeIterations(int iterations);
    void status();
    void update_progress();
    void update_so_progress(long plot, long no_plot);
    
private:    
    Fractal();
    void bailoutStatus();
    void lyapunovStatus();
   
    void waitForThreadsToFinish();
    void waitForOrbitThreadsToFinish();
    void signalStatus();
    void signalSOStatus();
    
    void QuickThread_control();
    void QuickThread(int thread_number);
    void LyapunovThread_control();
    void LyapunovThread(int thread_number);
    void EscapeThread_control();
    void EscapeThread(int thread_number);
    void OrbitThread_control();
    void OrbitThread(int thread_number, bool single_orbit);
  
    bool restartRequired();
    void Continue();

    QLabel* m_status;
    FractalsConfig m_config;

    boost::thread m_thread;
    int m_iteration;
    int m_max_iterations;
    int m_iterate_step_size;
    bool m_exitThread;

    bool m_finished;

    QString m_duration;

    // Multi-threading
    int m_number_of_threads;
    int m_number_of_orbit_threads;
    boost::scoped_array<boost::thread> m_work_threads;
    boost::mutex m_threads_mutex;
    boost::condition m_threads_condition;
    bool m_multi_precision;
    int m_precision;
    bool m_ignore_progress;
    std::string m_colouring_method[2];
    unsigned int m_row;
    unsigned int m_rows;
    boost::scoped_array<CalculatingUnitLD> m_unit;
    boost::scoped_array<CalculatingUnitMP> m_mp_unit;
    VectorBool m_unit_finished;
    bool m_settled;
    unsigned int m_settling_cycle;
    unsigned int m_calculating_cycle;
    unsigned int m_settling_cycles;
    unsigned int m_calculating_cycles;
    bool m_orbit_plotting;
    bool m_single_orbit;
    int m_number_of_active_threads;
    std::string m_colour_signature;
};

inline void Fractal::signalStatus()
{
    if (!StaticCalculatingUnit::s_stop)
    {
        emit signal_progressive_progress();
    }
}

inline void Fractal::signalSOStatus()
{
    if (!StaticCalculatingUnit::s_stop)
    {
        emit signal_so_progress(m_max_iterations, 0L);
    }
}
