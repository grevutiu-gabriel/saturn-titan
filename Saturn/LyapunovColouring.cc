// 
// File:   LyapunovColouring.h
// Author: M.R.Eggleston
//
// Created on 04 April 2013, 09:27
//


#include <QHBoxLayout>
#include <QVBoxLayout>
#include "Config.h"
#include "LyapunovColouring.h"

LyapunovColouring::LyapunovColouring(QWidget* parent)
:
QWidget(parent),
m_colour_combo(new LyapunovColouringCombobox()),
m_method_combo(new LyapunovMethodCombobox()),
m_multi_colour_widget(new QWidget()),
m_red_offset_spin(new QSpinBox()),
m_green_offset_spin(new QSpinBox()),
m_blue_offset_spin(new QSpinBox()),
m_lockstep_check(new QCheckBox("lock step")),
m_scale_entry(new NumberEntry(NumberEntry::FLOAT)),
m_single_colour(new SingleColour(CT_ALL)),
m_component_order_combo(new ComponentOrderComboBox()),
m_component_order_widget(new QWidget()),
m_inner(false),
m_colour_maps(ColourMaps::instance()),
m_ignore_signals(false),
m_lockstep(true)
{
    m_config.SetFractalType(Config::instance()->getFractalType());
    m_config.setInner(m_inner);
    m_red_offset_spin->setRange(0, 511);
    m_red_offset_spin->setWrapping(true);
    m_green_offset_spin->setRange(0, 511);
    m_green_offset_spin->setWrapping(true);
    m_blue_offset_spin->setRange(0, 511);
    m_blue_offset_spin->setWrapping(true);
    m_lockstep_check->setCheckState(Qt::Checked);
    setup_ui_layout();
    connect_signals();
}

LyapunovColouring::~LyapunovColouring()
{
}

void LyapunovColouring::setup_ui_layout()
{
    auto main_layout = new QVBoxLayout();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    auto hlayout = new QHBoxLayout();
    hlayout->setSpacing(5);
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->addWidget(m_colour_combo);
    hlayout->addStretch();
    main_layout->addLayout(hlayout);
    hlayout = new QHBoxLayout();
    hlayout->setSpacing(5);
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->addWidget(m_method_combo);
    hlayout->addStretch();
    auto hlayout2 = new QHBoxLayout();
    hlayout2->setSpacing(5);
    hlayout2->setContentsMargins(0, 0, 0, 0);
    hlayout2->addWidget(new QLabel("Colour Component Order"));
    hlayout2->addWidget(m_component_order_combo);
    m_component_order_widget->setLayout(hlayout2);
    hlayout->addWidget(m_component_order_widget);
    main_layout->addLayout(hlayout);
    auto vlayout = new QVBoxLayout();
    vlayout->setSpacing(0);
    vlayout->setContentsMargins(0, 0, 0, 0);
    hlayout = new QHBoxLayout();
    hlayout->setSpacing(5);
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->addWidget(new QLabel("Offsets  red"));
    hlayout->addWidget(m_red_offset_spin);
    hlayout->addWidget(new QLabel("green"));
    hlayout->addWidget(m_green_offset_spin);
    hlayout->addWidget(new QLabel("blue"));
    hlayout->addWidget(m_blue_offset_spin);
    hlayout->addWidget(m_lockstep_check);
    hlayout->addStretch();
    vlayout->addLayout(hlayout);
    hlayout = new QHBoxLayout();
    hlayout->setSpacing(5);
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->addWidget(new QLabel("Scale"));
    hlayout->addWidget(m_scale_entry);
    hlayout->addStretch();
    vlayout->addLayout(hlayout);
    m_multi_colour_widget->setLayout(vlayout);
    main_layout->addWidget(m_multi_colour_widget);
    main_layout->addWidget(m_single_colour);
    
    setLayout(main_layout);
}

void LyapunovColouring::connect_signals()
{
    connect(m_colour_combo, SIGNAL(currentIndexChanged(int)),
            this,           SLOT(on_colouring_changed(int)));
    connect(m_method_combo, SIGNAL(currentIndexChanged(int)),
            this,           SLOT(on_method_changed(int)));
    connect(m_red_offset_spin, SIGNAL(valueChanged(int)),
            this,          SLOT(on_red_offset_changed(int)));
    connect(m_green_offset_spin, SIGNAL(valueChanged(int)),
            this,          SLOT(on_green_offset_changed(int)));
    connect(m_blue_offset_spin, SIGNAL(valueChanged(int)),
            this,          SLOT(on_blue_offset_changed(int)));
    connect(m_lockstep_check, SIGNAL(stateChanged(int)),
            this,          SLOT(on_lockstep_changed(int)));
    connect(m_scale_entry, SIGNAL(changed()),
            this,          SLOT(on_scale_changed()));
    connect(m_component_order_combo, SIGNAL(currentIndexChanged(int)),    
            this,          SLOT(on_component_colour_order_changed(int)));
}

void LyapunovColouring::setFractalType(FRACTAL_TYPE ft)
{
    m_config.SetFractalType(ft);
}

void LyapunovColouring::display()
{
    m_ignore_signals = true;
    m_config.setInner(m_inner);
    auto method = m_config.getMethod();
    bool fixed_colour = (method[0] == 'f');
    m_method_combo->setCurrentIndex(static_cast<int>(!fixed_colour));
    m_colour_combo->setCurrentIndex(static_cast<int>(m_inner));
    if (fixed_colour)
    {
        m_multi_colour_widget->hide();
        m_single_colour->setColour(stringToColour(method.substr(2)));
        m_single_colour->show();
        m_component_order_widget->hide();
    }
    else
    {
        m_multi_colour_widget->show();
        m_single_colour->hide();
        setOffset();
        setScale();
        m_component_order_combo->setValue(m_config.getComponentOrder());
        m_component_order_widget->show();
//        m_smooth_check->set_active(m_config.getSmooth());
    }
    m_ignore_signals = false;
}

void LyapunovColouring::setOffset()
{
    m_red_offset_spin->setValue(m_config.getRedOffset());
    m_green_offset_spin->setValue(m_config.getGreenOffset());
    m_blue_offset_spin->setValue(m_config.getBlueOffset());
}

void LyapunovColouring::setScale()
{
    m_scale_entry->setEnabled(true);
    m_scale_entry->Set(longdoubleToString(m_config.getColourScale()));
}

void LyapunovColouring::on_colouring_changed(int value)
{
    if (!m_ignore_signals)
    {
        m_inner = (value == POSITIVE);
        m_config.setInner(m_inner);
        auto method = m_config.getMethod();
        emit colouring_changed(value);
//        display();
    }
}

void LyapunovColouring::on_method_changed(int value)
{
    if (!m_ignore_signals)
    {
        long double scale = 1000.0L;
        bool multi_colour = static_cast<bool>(value);
        std::string method_string;
        if (multi_colour)
        {
            method_string = "v";
        }
        else
        {
            method_string = "f,0,0,0";
            scale = 1.0L;
        }
        m_config.setMethod(method_string);
        m_config.setColourScale(scale);
        emit colouring_changed(static_cast<int>(m_inner));
    }
}

void LyapunovColouring::on_scale_changed()
{
    if (!m_ignore_signals)
    {
        long double scale = stringToLongDouble(m_scale_entry->Get());
        m_config.setColourScale(scale);
        emit colouring_changed(static_cast<int>(m_inner));
    }
}

const SingleColour* LyapunovColouring::single_colour()
{
    return m_single_colour;
}

void LyapunovColouring::on_red_offset_changed(int value)
{
    if (!m_ignore_signals)
    {
        int r = m_config.getRedOffset();
        int g = m_config.getGreenOffset();
        int b = m_config.getBlueOffset();
        int change = value - r;
        if (change < 0)
        {
            change += 512;
        }
        m_config.setRedOffset(value);
        if (m_lockstep)
        {
            m_config.setGreenOffset(g + change);
            m_config.setBlueOffset(b + change);
        }
        display();
        emit colouring_changed(static_cast<int>(m_inner));
    }
}

void LyapunovColouring::on_blue_offset_changed(int value)
{
    if (!m_ignore_signals)
    {
        int r = m_config.getRedOffset();
        int g = m_config.getGreenOffset();
        int b = m_config.getBlueOffset();
        int change = value - b;
        if (change < 0)
        {
            change += 512;
        }
        m_config.setBlueOffset(value);
        if (m_lockstep)
        {
            m_config.setGreenOffset(g + change);
            m_config.setRedOffset(r + change);
        }
        display();
        emit colouring_changed(static_cast<int>(m_inner));
    }
}

void LyapunovColouring::on_green_offset_changed(int value)
{
    if (!m_ignore_signals)
    {
        int r = m_config.getRedOffset();
        int g = m_config.getGreenOffset();
        int b = m_config.getBlueOffset();
        int change = value - g;
        if (change < 0)
        {
            change += 512;
        }
        m_config.setGreenOffset(value);
        if (m_lockstep)
        {
            m_config.setBlueOffset(b + change);
            m_config.setRedOffset(r + change);
        }
        display();
        emit colouring_changed(static_cast<int>(m_inner));
    }
}

void LyapunovColouring::on_lockstep_changed(int state)
{
    m_lockstep = (state == Qt::Checked);
}

void LyapunovColouring::on_component_colour_order_changed(int)
{
    if (!m_ignore_signals)
    {
        m_config.setComponentOrder(m_component_order_combo->getValue());
        emit colouring_changed(static_cast<int>(m_inner));
    }
}

