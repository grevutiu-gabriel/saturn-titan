// 
// File:   ComplexFunctionParameterContainer.h
// Author: M.R.Eggleston
//
// Created on 13 December 2012, 10:30
//

#pragma once

#include <QCheckBox>
#include <QLabel>
#include <QListWidget>
#include <QSpinBox>
//#include "mpreal.h"
#include "FractalsConfig.h"
#include "NumberEntry.h"
#include "OptionComboboxes.h"
#include "TypesAndConstants.h"

class ComplexFunctionParametersContainer : public QWidget
{
    Q_OBJECT
signals:
    void changed();

private slots:
    void on_row_changed(int row);
    void on_function_changed(int index);
    void on_real_function_changed(int index);
    void on_imag_function_changed(int index);
    void on_pair_changed(int state);
    void on_parameter_changed();
    void on_rotation_changed(int);

public:
    ComplexFunctionParametersContainer(QWidget* parent = nullptr);
    virtual ~ComplexFunctionParametersContainer();

    void load(FRACTAL_TYPE ft);

private:
    ComplexFunctionParametersContainer(const ComplexFunctionParametersContainer &other);

    void setup_ui_layout();
    void connect_signals();

    void displayParameterInList(int row);
    void updateInputFields();
    void displayValueAtCursor();
    bool updateParameter();

    FractalsConfig m_config;
    QListWidget* m_list;
    ComplexFunctionParameterCombobox* m_f;
    QWidget* m_function_pair_widget;
    FunctionParameterCombobox* m_f_r;
    FunctionParameterCombobox* m_f_i;
    QCheckBox* m_pair_check;
    QWidget* m_size_widget;
    NumberEntry* m_size_entry;
    QWidget* m_rotation_widget;
    QSpinBox* m_rotation_spin;
    QWidget* m_parameter_widget;
    NumberEntry* m_real_entry;
    NumberEntry* m_imag_entry;
    QWidget* m_main_widget;
    QLabel* m_no_parameters_label;
    bool m_emit;
    int m_row;
};

