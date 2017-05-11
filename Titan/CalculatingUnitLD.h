//
// File:   CalculatingUnitLD.h
// Author: M.R.Eggleston
//
// Wrapper for a template class required because Qt doesn't support templates.
//


#pragma once

#include "ldcomplex.h"
#include "CalculatingUnit.h"
#include "CalculatingUnitGeneric.h"

class CalculatingUnitLD : public CalculatingUnitGeneric
{
public:
    CalculatingUnitLD();
    virtual ~CalculatingUnitLD();

    void setFractal();

    void setValues(int iteration, int chunk_size);
    void setLyapunov();
    bool calculate();
    bool calculateLyapunovSettlingCycle();
    bool calculateLyapunovCalculatingCycle(unsigned int cycle);
    void calculateLyapunovRowByRow();
    void calculateOrbits();
    void calculateOrbit();
    void enableProgressSignals(bool value);
    void sendProgressSignals(bool value);

private:
    CalculatingUnit<long double,LongComplex> m_unit;
};

inline void CalculatingUnitLD::setValues(int iteration, int chunk_size)
{
    m_unit.setValues(iteration, chunk_size);
}

inline void CalculatingUnitLD::setLyapunov()
{
    m_unit.setLyapunov();
}

inline bool CalculatingUnitLD::calculate()
{
    return m_unit.calculate();
}

inline bool CalculatingUnitLD::calculateLyapunovSettlingCycle()
{
    return m_unit.calculateLyapunovSettlingCycle();
}

inline bool CalculatingUnitLD::calculateLyapunovCalculatingCycle(unsigned int cycle)
{
    return m_unit.calculateLyapunovCalculatingCycle(cycle);
}

