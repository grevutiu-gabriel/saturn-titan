// 
// File:   LyapunovColouring.h
// Author: M.R.Eggleston
//
// Created on 04 April 2013, 09:18
//

#pragma once

#include <QCheckBox>
#include <QLabel>
#include <QSpinBox>
#include "FractalsConfig.h"
#include "NumberEntry.h"
#include "OptionComboboxes.h"
#include "SingleColour.h"

class LyapunovColouring : public QWidget
{
    Q_OBJECT
signals:
    void colouring_changed(int index);

private slots:
    void on_method_changed(int value);
    void on_colouring_changed(int value);
    void on_red_offset_changed(int value);
    void on_green_offset_changed(int value);
    void on_blue_offset_changed(int value);
    void on_lockstep_changed(int state);
    void on_scale_changed();
    void on_component_colour_order_changed(int index);
  
public:
    LyapunovColouring(QWidget* parent = nullptr);
    virtual ~LyapunovColouring();

    void setFractalType(FRACTAL_TYPE ft);
    void display();
    const SingleColour* single_colour();
    
private:
    LyapunovColouring(const LyapunovColouring&);
    
    void setup_ui_layout();
    void connect_signals();
    
    void setScale();
    void setOffset();
    
    FractalsConfig m_config;
    LyapunovColouringCombobox* m_colour_combo;
    LyapunovMethodCombobox* m_method_combo;
    QWidget* m_multi_colour_widget;
    QSpinBox* m_red_offset_spin;
    QSpinBox* m_green_offset_spin;
    QSpinBox* m_blue_offset_spin;
    QCheckBox* m_lockstep_check;
    NumberEntry* m_scale_entry;
    SingleColour* m_single_colour;
    ComponentOrderComboBox* m_component_order_combo;
    QWidget* m_component_order_widget;
    bool m_inner;
    boost::shared_ptr<ColourMaps> m_colour_maps;
    bool m_ignore_signals;
    bool m_lockstep;
};
