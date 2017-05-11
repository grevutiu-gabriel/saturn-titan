
#include "CalculatingUnitMP.h"

CalculatingUnitMP::CalculatingUnitMP()
{
    m_unit.set_generic(dynamic_cast<CalculatingUnitGeneric*>(this));
}

CalculatingUnitMP::~CalculatingUnitMP()
{
}

void CalculatingUnitMP::setFractal()
{
    m_unit.setFractal();
}

void CalculatingUnitMP::calculateLyapunovRowByRow()
{
    m_unit.calculateLyapunovRowByRow();
}

void CalculatingUnitMP::calculateOrbits()
{
    m_unit.calculateOrbits();
}

void CalculatingUnitMP::calculateOrbit()
{
    m_unit.calculateOrbit();
}

void CalculatingUnitMP::enableProgressSignals(bool value)
{
    m_unit.enableProgressSignals(value);
}

void CalculatingUnitMP::sendProgressSignals(bool value)
{
    m_unit.sendProgressSignals(value);
}
