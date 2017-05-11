// 
// File:   ParametersContainer.h
// Author: M.R.Eggleston
//
// Split out from FractalTab on 11 April 2012, 09:58
//

#pragma once

#include <QLabel>
#include <QListWidget>
#include "Utilities.h"
#include "FractalsConfig.h"
#include "NumberEntry.h"
#include "OptionComboboxes.h"

class ParametersContainer : public QWidget
{
    Q_OBJECT
signals:
    void changed();

private slots:
    void on_row_changed(int row);
    void on_parameter_changed();

public:
    ParametersContainer(QWidget* parent = nullptr);
    ~ParametersContainer();

    void load(FRACTAL_TYPE ft);

private:
    ParametersContainer(const ParametersContainer &other);

    void setup_ui_layout();
    void connect_signals();

    void displayParameterInList(int row);
    void displayValueAtCursor();
    
    bool updateParameter();

    FractalsConfig m_config;
    QListWidget* m_list;
    NumberEntry* m_p;
    QWidget* m_main_widget;
    QLabel* m_no_parameters_label;
    bool m_emit;
    int m_row;
    bool m_single_orbit;
};
