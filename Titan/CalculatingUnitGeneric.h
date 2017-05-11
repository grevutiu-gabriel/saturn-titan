#pragma once

#include "FractalConfig.h"

class CalculatingUnitGeneric : public QObject
{
    Q_OBJECT
signals:
    void signal_progress(int);
    void signal_so_progress(long, long);

public:
    CalculatingUnitGeneric() {};
    virtual ~CalculatingUnitGeneric() {};

    virtual void setFractal() = 0;

    virtual void setValues(int iteration, int chunk_size) = 0;
    virtual void setLyapunov() = 0;
    virtual bool calculate() = 0;
    virtual bool calculateLyapunovSettlingCycle() = 0;
    virtual bool calculateLyapunovCalculatingCycle(unsigned int cycle) = 0;
    virtual void calculateLyapunovRowByRow() = 0;
    virtual void calculateOrbits() = 0;
    virtual void calculateOrbit() = 0;
    virtual void enableProgressSignals(bool value) = 0;
    virtual void sendProgressSignals(bool value) = 0;

    void send_signal_progress(int row)
    {
        emit signal_progress(row);
    }
    
    void send_signal_so_progress(long plot, long no_plot)
    {
        emit signal_so_progress(plot, no_plot);
    }

protected:
    CalculatingUnitGeneric(const CalculatingUnitGeneric& orig);

};

