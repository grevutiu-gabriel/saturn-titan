//
// File:   FractalTab.cc
// Author: M.R.Eggleston
//
// Created on 06 July 2010, 14:02
//

#include <iostream>
#include <QVBoxLayout>
#include "Config.h"
#include "FractalTab.h"
#include "Utilities.h"

FractalTab::FractalTab(QWidget* parent)
:
QWidget(parent),
m_bailout_widget(new QWidget()),
m_single_orbit_widget(new QWidget()),
m_lyapunov_widget(new QWidget()),
m_parameter_defaults_button(new QPushButton("Defaults")),
m_so_parameter_defaults_button(new QPushButton("Defaults")),
m_formula_text(new QTextEdit()),
m_so_formula_text(new QTextEdit()),
m_parameters_container(new ParametersContainer()),
m_complex_parameters_container(new ComplexParametersContainer()),
m_function_parameters_container(new FunctionParametersContainer()),
m_complex_function_parameters_container(new ComplexFunctionParametersContainer()),
m_so_parameters_container(new ParametersContainer()),
m_so_function_parameters_container(new FunctionParametersContainer()),
m_orbit_check(new QCheckBox("plot")),
m_calculating_area_spin(new QSpinBox()),
m_orbit_plot_combo(new OrbitPlotCombobox()),
m_omit_spin(new QSpinBox()),
m_density_spin(new QSpinBox()),
m_settling_cycles_entry(new NumberEntry(NumberEntry::UINT)),
m_sequence_line(new QLineEdit),
m_lyapunov_defaults_button(new QPushButton("Defaults")),
m_bailout_condition(new BailoutCondition()),
m_fractal_type(Config::instance()->getFractalType()),
m_emit_colour_change(true),
m_enable_fractal_settings_changed_signal(false)
{
    m_density_spin->setRange(1, 400);
    m_config.SetFractalType(m_fractal_type);
    setup_ui_layout();
    connect_signals();
    
    display();
}

FractalTab::~FractalTab()
{
}

void FractalTab::setup_ui_layout()
{
    setup_bailout_layout();
    setup_single_orbit_layout();
    setup_lyapunov_layout();

    auto main_layout = new QVBoxLayout();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->addWidget(m_bailout_widget);
    main_layout->addWidget(m_single_orbit_widget);
    main_layout->addWidget(m_lyapunov_widget);
    setLayout(main_layout);
}

void FractalTab::setup_bailout_layout()
{
    // Background for location QTexyEdit fields
    auto background = palette().window().color();
    QPalette palette;
    palette.setColor(QPalette::Base, background);

    auto bailout_layout = new QVBoxLayout();
    bailout_layout->setSpacing(0);
    m_formula_text->setReadOnly(true);
    m_formula_text->setFrameShape(QFrame::NoFrame);
    m_formula_text->setFrameShadow(QFrame::Plain);
    m_formula_text->setPalette(palette);
    m_formula_text->setFixedHeight(120);
    bailout_layout->addWidget(m_formula_text);
    m_bailout_condition->load(m_config.GetFractalType());
    bailout_layout->addWidget(m_bailout_condition);
    auto tabs = new QTabWidget();
    tabs->setFixedHeight(250);
    tabs->addTab(m_complex_parameters_container, "Complex Parameters");
    tabs->addTab(m_parameters_container, "Parameters");
    tabs->addTab(m_complex_function_parameters_container, "F(z)");
    tabs->addTab(m_function_parameters_container, "f(x)");
    bailout_layout->addWidget(tabs);
    auto layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addStretch();
    layout->addWidget(m_parameter_defaults_button);
    bailout_layout->addLayout(layout);
    layout = new QHBoxLayout();
    layout->setSpacing(5);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_orbit_check);
    layout->addWidget(m_orbit_plot_combo);
    auto label = new QLabel("orbits omitting the first");
    layout->addWidget(label);
    layout->addWidget(m_omit_spin);
    m_omit_spin->setRange(0, (m_config.getMaxIterations() > 0 ? m_config.getMaxIterations() - 1 : 0));
    m_omit_spin->setValue(m_config.getStartOrbitIteration());
    label = new QLabel("iterations");
    layout->addWidget(label);
    layout->addStretch();
    bailout_layout->addLayout(layout);    
    layout = new QHBoxLayout();
    layout->setSpacing(5);
    layout->setContentsMargins(0, 0, 0, 0);
    label = new QLabel("Calculating area");
    layout->addWidget(label);
    m_calculating_area_spin->setRange(1, 1000);
    m_calculating_area_spin->setValue(9);
    layout->addWidget(m_calculating_area_spin);
    label = new QLabel("times display area");
    layout->addWidget(label);
    layout->addStretch();
    bailout_layout->addLayout(layout);
    layout = new QHBoxLayout();
    layout->setSpacing(5);
    layout->setContentsMargins(0, 0, 0, 0);
    label = new QLabel("Density");
    layout->addWidget(label);
    layout->addWidget(m_density_spin);
    layout->addStretch();
    bailout_layout->addLayout(layout);
    bailout_layout->addStretch();
    m_bailout_widget->setLayout(bailout_layout);
}

void FractalTab::setup_single_orbit_layout()
{
    // Background for location QTexyEdit fields
    auto background = palette().window().color();
    QPalette palette;
    palette.setColor(QPalette::Base, background);

    auto so_layout = new QVBoxLayout();
    so_layout->setSpacing(0);
    m_so_formula_text->setReadOnly(true);
    m_so_formula_text->setFrameShape(QFrame::NoFrame);
    m_so_formula_text->setFrameShadow(QFrame::Plain);
    m_so_formula_text->setPalette(palette);
    m_so_formula_text->setFixedHeight(120);
    so_layout->addWidget(m_so_formula_text);
    auto tabs = new QTabWidget();
    tabs->setFixedHeight(250);
    tabs->addTab(m_so_parameters_container, "Parameters");
    tabs->addTab(m_so_function_parameters_container, "f(x)");
    so_layout->addWidget(tabs);
    auto layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addStretch();
    layout->addWidget(m_so_parameter_defaults_button);
    so_layout->addLayout(layout);
    so_layout->addStretch();
    m_single_orbit_widget->setLayout(so_layout);
}

void FractalTab::setup_lyapunov_layout()
{
    auto lyapunov_layout = new QVBoxLayout();
    lyapunov_layout->setSpacing(0);
    auto label = new QLabel(m_config.getLyapunovFormula());
    label->setWordWrap(true);
    lyapunov_layout->addWidget(label);
    auto line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    lyapunov_layout->addWidget(line);
    auto grid_layout = new QGridLayout();
    grid_layout->addWidget(new QLabel("Sequence"), 0, 0);
    grid_layout->addWidget(m_sequence_line, 0, 1);
    grid_layout->addWidget(new QLabel("Number of Settling Cycles"), 1, 0);
    auto layout2 = new QHBoxLayout();
    m_settling_cycles_entry->setMaxLength(9);
    m_settling_cycles_entry->setFixedWidth(100);
    layout2->addWidget(m_settling_cycles_entry);
    layout2->addStretch();
    grid_layout->addLayout(layout2, 1, 1);
    lyapunov_layout->addLayout(grid_layout);
    layout2 = new QHBoxLayout();
    layout2->addStretch();
    layout2->addWidget(m_lyapunov_defaults_button);
    lyapunov_layout->addLayout(layout2);
    lyapunov_layout->addStretch();
    
    m_lyapunov_widget->setLayout(lyapunov_layout);
}

void FractalTab::connect_signals()
{
    connect(m_bailout_condition, SIGNAL(changed()),
            this,                SLOT(on_changed()));
    connect(m_parameters_container, SIGNAL(changed()),
            this,                SLOT(on_changed()));
    connect(m_so_parameters_container, SIGNAL(changed()),
            this,                SLOT(on_changed()));
    connect(m_complex_parameters_container, SIGNAL(changed()),
            this,                SLOT(on_changed()));
    connect(m_function_parameters_container, SIGNAL(changed()),
            this,                SLOT(on_changed()));
    connect(m_so_function_parameters_container, SIGNAL(changed()),
            this,                SLOT(on_changed()));
    connect(m_complex_function_parameters_container, SIGNAL(changed()),
            this,                SLOT(on_changed()));
    connect(m_calculating_area_spin, SIGNAL(valueChanged(int)),
            this,                SLOT(on_area_changed(int)));
    connect(m_omit_spin,         SIGNAL(valueChanged(int)),
            this,                SLOT(on_omit_changed(int)));
    connect(m_orbit_check,       SIGNAL(stateChanged(int)),
            this,                SLOT(on_orbit_check(int)));
    connect(m_orbit_plot_combo,  SIGNAL(currentIndexChanged(int)),
            this,                SLOT(on_orbit_plot_changed(int)));
    connect(m_settling_cycles_entry, SIGNAL(changed()),
            this,                SLOT(on_new_settling_value()));
    connect(m_sequence_line,     SIGNAL(editingFinished()),
            this,                SLOT(on_new_sequence_value()));
    connect(m_parameter_defaults_button, SIGNAL(pressed()),
            this,                SLOT(on_bailout_defaults()));
    connect(m_lyapunov_defaults_button, SIGNAL(pressed()),
            this,                SLOT(on_lyapunov_defaults()));
    connect(m_density_spin,      SIGNAL(valueChanged(int)),
            this,                SLOT(on_density_changed(int)));
    connect(m_so_parameter_defaults_button, SIGNAL(pressed()),
            this,                SLOT(on_bailout_defaults()));
}

void FractalTab::on_changed()
{
    emit config_changed();
}

void FractalTab::display()
{
    bool lyapunov = !m_config.isBailoutFractal();
    bool single_orbit = m_config.isSingleOrbit();
    m_enable_fractal_settings_changed_signal = false;
    if (single_orbit)
    {
        m_bailout_widget->hide();
        m_single_orbit_widget->show();
        m_lyapunov_widget->hide();
        display_single_orbit();
    }
    else if (lyapunov)
    {
        m_bailout_widget->hide();
        m_single_orbit_widget->hide();
        m_lyapunov_widget->show();
        display_lyapunov();
    }
    else
    {
        m_bailout_widget->show();
        m_single_orbit_widget->hide();
        m_lyapunov_widget->hide();
        display_bailout_fractal();
    }
    m_enable_fractal_settings_changed_signal = true;
}

void FractalTab::display_bailout_fractal()
{
    bool cp_transforms = (m_config.getNumberOfComplexPlaneTransforms() != 0);
    if (cp_transforms)
    {
        m_config.setOrbitPlotting(false);
    }
    m_formula_text->setHtml(m_config.getFormula());
    m_bailout_condition->load(m_fractal_type);
    bool orbit_plotting = m_config.isOrbitPlotting();
    m_orbit_check->setCheckState(orbit_plotting ? Qt::Checked : Qt::Unchecked);
    m_calculating_area_spin->setValue(orbit_plotting ? m_config.getCalculatingArea() : 9);
    m_omit_spin->setRange(0, (m_config.getMaxIterations() > 0 ? m_config.getMaxIterations() - 1 : 0));
    m_omit_spin->setValue(orbit_plotting ? m_config.getStartOrbitIteration() : 0);
    m_orbit_plot_combo->setValue(orbit_plotting ? m_config.getOrbitPlots() : OP_ALL);
    m_density_spin->setValue(m_config.getDensity());
    m_calculating_area_spin->setEnabled(orbit_plotting);
    m_omit_spin->setEnabled(orbit_plotting);
    m_orbit_plot_combo->setEnabled(orbit_plotting);
    m_density_spin->setEnabled(orbit_plotting);

    m_parameters_container->load(m_fractal_type);
    m_complex_parameters_container->load(m_fractal_type);
    m_function_parameters_container->load(m_fractal_type);
    m_complex_function_parameters_container->load(m_fractal_type);
}

void FractalTab::display_single_orbit()
{
    m_so_formula_text->setHtml(m_config.getFormula());
    m_so_parameters_container->load(m_fractal_type);
    m_so_function_parameters_container->load(m_fractal_type);
}

void FractalTab::display_lyapunov()
{
    m_sequence_line->setText(QString::fromStdString(m_config.getLyapunovSequence()));
    m_settling_cycles_entry->Set(intToString(m_config.getSettlingCycles()));
}

void FractalTab::setFractalType(FRACTAL_TYPE ft)
{
    m_fractal_type =  ft;
    m_config.SetFractalType(m_fractal_type);
//    m_emit_colour_change = false;
    display();
}

void FractalTab::on_bailout_defaults()
{
    m_config.resetFractalParameters();
    display();
    emit config_changed();
}

void FractalTab::on_lyapunov_defaults()
{
    m_config.resetLyapunovParameters();
    display();
    emit lyapunov_reset();
}

void FractalTab::on_new_sequence_value()
{
    std::string old_sequence = m_config.getLyapunovSequence();
    std::string sequence = m_sequence_line->text().toStdString();
    std::string new_sequence;
    bool a = false;
    bool b = false;
    for (auto it = sequence.begin(); it != sequence.end(); it++ )
    {
        char ch = *it;
        if ((ch == 'A') || (ch == 'a'))
        {
            new_sequence += 'A';
            a = true;
        }
        else
        {
            new_sequence += 'B';
            b = true;
        }
    }
    if (!(a && b))
    {
        new_sequence += (a ? 'B' : 'A');
    }
    if (new_sequence.length() < 2) new_sequence = "AB";
    m_config.setLyapunovSequence(new_sequence);
    if (m_enable_fractal_settings_changed_signal)
    {
        if (old_sequence != new_sequence)
        {
            m_sequence_line->setText(QString::fromStdString(new_sequence));
            emit config_changed();
        }
    }
}

void FractalTab::on_new_settling_value()
{
    if (m_enable_fractal_settings_changed_signal)
    {
        emit settling_cycles_changed(stringToInt(m_settling_cycles_entry->Get()));
    }
}

void FractalTab::on_orbit_check(int index)
{
    if (m_enable_fractal_settings_changed_signal)
    {
        bool orbit_plotting = (static_cast<Qt::CheckState>(index) == Qt::Checked);
        m_config.setOrbitPlotting(orbit_plotting);
        m_calculating_area_spin->setEnabled(orbit_plotting);
        m_omit_spin->setEnabled(orbit_plotting);
        m_orbit_plot_combo->setEnabled(orbit_plotting);
        m_density_spin->setEnabled(orbit_plotting);
        emit config_changed();
    }
}

void FractalTab::on_area_changed(int value)
{
    if (m_enable_fractal_settings_changed_signal)
    {
        m_config.setCalculatingArea(value);
        emit config_changed();
    }
}

void FractalTab::on_omit_changed(int value)
{
    if (m_enable_fractal_settings_changed_signal)
    {
        m_config.setStartOrbitIteration(value);
        emit config_changed();
    }
}

void FractalTab::on_density_changed(int value)
{
    if (m_enable_fractal_settings_changed_signal)
    {
        m_config.setDensity(value);
        emit config_changed();
    }
}

void FractalTab::on_orbit_plot_changed(int value)
{
    if (m_enable_fractal_settings_changed_signal)
    {
        auto old_value = m_config.getOrbitPlots();
        auto new_value = static_cast<ORBIT_PLOTS>(value);
        if (old_value != new_value)
        {
            m_config.setOrbitPlots(new_value);
            emit config_changed();
        }
    }
}

void FractalTab::startOrbitIterationRangeChanged(int value)
{
    m_enable_fractal_settings_changed_signal = false;
    m_omit_spin->setRange(0, value);
    m_enable_fractal_settings_changed_signal = true;
}

