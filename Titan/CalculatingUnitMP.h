#pragma once
#include "mpreal.h"
#include "mpcomplex.h"
#include "CalculatingUnit.h"
#include "CalculatingUnitGeneric.h"

class CalculatingUnitMP : public CalculatingUnitGeneric
{
public:
    CalculatingUnitMP();
    virtual ~CalculatingUnitMP();

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
    CalculatingUnit<MpReal, MpComplex> m_unit;
};

inline void CalculatingUnitMP::setValues(int iteration, int chunk_size)
{
    m_unit.setValues(iteration, chunk_size);
}

inline void CalculatingUnitMP::setLyapunov()
{
    m_unit.setLyapunov();
}

inline bool CalculatingUnitMP::calculate()
{
    return m_unit.calculate();
}

inline bool CalculatingUnitMP::calculateLyapunovSettlingCycle()
{
    return m_unit.calculateLyapunovSettlingCycle();
}

inline bool CalculatingUnitMP::calculateLyapunovCalculatingCycle(unsigned int cycle)
{
    return m_unit.calculateLyapunovCalculatingCycle(cycle);
}
