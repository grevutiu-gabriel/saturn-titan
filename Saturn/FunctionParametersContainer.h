// 
// File:   FunctionParametersContainer.h
// Author: M.R.Eggleston
//
// Created on 24 April 2012, 17:17
//

#pragma once

#include <QLabel>
#include <QListWidget>
//#include "mpreal.h"
#include "FractalsConfig.h"
#include "NumberEntry.h"
#include "OptionComboboxes.h"
#include "TypesAndConstants.h"

class FunctionParametersContainer : public QWidget
{
    Q_OBJECT
signals:
    void changed();

private slots:
    void on_row_changed(int row);
    void on_parameter_changed();
    void on_function_changed(int index);

public:
    FunctionParametersContainer(QWidget* parent = nullptr);
    virtual ~FunctionParametersContainer();

    void load(FRACTAL_TYPE ft);

private:
    FunctionParametersContainer(const FunctionParametersContainer &other);

    void setup_ui_layout();
    void connect_signals();
    
    void displayParameterInList(int row);
    void displayValueAtCursor();
    bool updateParameter();

    FractalsConfig m_config;
    QListWidget* m_list;
    NumberEntry* m_entry;
    FunctionParameterCombobox* m_f;
    QWidget* m_main_widget;
    QLabel *m_no_parameters_label;
    bool m_emit;
    int m_row;
};

