//
// File:   TransformDefinition.h
// Author: M.R.Eggleston
//
// Created on 30 June 2011, 14:08
//

#pragma once

#include <QCheckBox>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QVBoxLayout>
#include "NumberEntry.h"
#include "OptionComboboxes.h"
#include "FractalsConfig.h"
#include "KeyString.h"

class TransformDefinition : public QWidget
{
    Q_OBJECT
signals:
    void transform_changed();

private slots:
    void on_complex_function_changed(int index);
    void on_real_function_changed(int index);
    void on_imaginary_function_changed(int index);
    void on_pair_changed(int state);
    void on_parameter_changed();
    void on_rotation_changed(int value);
   
public:
    TransformDefinition(QWidget* parent = nullptr);
    virtual ~TransformDefinition();

    std::string getTransform();
    void setTransform(const std::string &t);

    void enableEditing(bool value);
    void display();

private:
    TransformDefinition(const TransformDefinition& orig);
    
    void setup_ui_layout();
    void connect_signals();

    ComplexFunctionParameterCombobox *m_complex_function_combo;
    FunctionParameterCombobox* m_real_function_combo;
    FunctionParameterCombobox* m_imaginary_function_combo;
    NumberEntry* m_real_entry;
    NumberEntry* m_imaginary_entry;
    NumberEntry* m_size_entry;
    QSpinBox* m_rotation_spin;
    QCheckBox* m_pair_check;
    QWidget* m_rotation_widget;
    QWidget* m_size_widget;
    QWidget* m_parameter_widget;
    QWidget* m_function_pair_widget;

    COMPLEX_FUNCTION_PARAMETER m_id;
    KeyString m_transform;
    LongComplex m_parameter;
    long double m_size;
    unsigned int m_rotation;
    bool m_ignore_signals;
};
