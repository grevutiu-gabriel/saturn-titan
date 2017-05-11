//
// File:   OuterSelection.h
// Author: trevone
//
// Created on 03 April 2013, 11:11
//

#pragma once

#include <QRadioButton>
#include "NumberEntry.h"
#include "OptionComboboxes.h"

class OuterSelection : public QWidget
{
    Q_OBJECT
signals:
    void outer_selection_changed();

private slots:
    void on_bailout_radio_changed(bool checked);
    void on_components_radio_changed(bool checked);
    void on_real_comparison_changed(int value);
    void on_imag_comparison_changed(int value);
    void on_combination_changed(int value);
    void on_component_limit_changed();
    
public:
    OuterSelection(QWidget* parent = nullptr);
    virtual ~OuterSelection();

    void display();

private:
    void setup_ui_layout();
    void connect_signals();

    FractalsConfig m_config;
    ComponentComparisonsImagCombobox *m_imag_comparison_combo;
    ComponentComparisonsRealCombobox *m_real_comparison_combo;
    CombinationCombobox *m_combination_combo;
    QRadioButton *m_norm_radio;
    QRadioButton *m_components_radio;
    NumberEntry* m_component_limit_entry;
    std::string m_select;
    bool m_ignore_signals;
};