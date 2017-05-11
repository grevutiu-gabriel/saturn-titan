// 
// File:   Transform.h
// Author: M.R.Eggleston
//
// Created on 30 June 2011, 17:12
//

#pragma once


#include <vector>
#include "ComplexFunction.h"
#include "FractalConfig.h"
#include "TypesAndConstants.h"

template<class T, class Tc>
class Transform
{
public:
    Transform();
    virtual ~Transform();

    void setComplexPlaneTransforms(FractalConfig &config);
    void setTransforms(int set, FractalConfig &config);
    bool transformsDefined();
    Tc operator()(const Tc& z);

private:
    std::vector<ComplexFunction<T, Tc>> m_transforms;

    unsigned int m_number_of_transforms;
};

template<class T, class Tc>
Transform<T, Tc>::Transform()
:
m_number_of_transforms(0)
{
}

template<class T, class Tc>
Transform<T, Tc>::~Transform()
{
}

template<class T, class Tc>
void Transform<T, Tc>::setTransforms(int set, FractalConfig &config)
{
    m_number_of_transforms = config.getNumberOfTransforms(set);
    m_transforms.resize(m_number_of_transforms);
    if (m_number_of_transforms > 0)
    {
        for (unsigned int i = 0; i < m_number_of_transforms; i++)
        {
            m_transforms[i].setFunction(config.getTransform(set, i));
        }
    }
}

template<class T, class Tc>
void Transform<T, Tc>::setComplexPlaneTransforms(FractalConfig &config)
{
    m_number_of_transforms = config.getNumberOfComplexPlaneTransforms();
    m_transforms.resize(m_number_of_transforms);
    if (m_number_of_transforms > 0)
    {
        for (unsigned int i = 0; i < m_number_of_transforms; i++)
        {
            m_transforms[i].setFunction(config.getComplexPlaneTransform(i));
        }
    }
}

template<class T, class Tc>
inline Tc Transform<T, Tc>::operator()(const Tc& z)
{
    Tc value = z;
    for (unsigned int i = 0; i < m_number_of_transforms; i++)
    {
        value = m_transforms[i](value);
    }
    return value;
}

template<class T, class Tc>
bool Transform<T, Tc>::transformsDefined()
{
    return (m_number_of_transforms > 0);
}
