//
// File:   OuterSelection.cc
// Author: trevone
//
// Created on 03 April 2013, 11:21
//

#include <QLabel>
#include <QVBoxLayout>
#include "Config.h"
#include "OuterSelection.h"


OuterSelection::OuterSelection(QWidget* parent)
:
QWidget(parent),
m_imag_comparison_combo(new ComponentComparisonsImagCombobox()),
m_real_comparison_combo(new ComponentComparisonsRealCombobox()),
m_combination_combo(new CombinationCombobox()),
m_norm_radio(new QRadioButton("bailout")),
m_components_radio(new QRadioButton("components")),
m_component_limit_entry(new NumberEntry(NumberEntry::FLOAT)),
m_ignore_signals(false)
{
    setup_ui_layout();
    connect_signals();

//    m_norm_radio->signal_clicked().connect(sigc::mem_fun(*this, &OuterSelection::on_bailout_radio_changed));
//    m_components_radio->signal_clicked().connect(sigc::mem_fun(*this, &OuterSelection::on_components_radio_changed));
//    m_real_comparison_combo->signal_changed().connect(sigc::mem_fun(*this, &OuterSelection::on_real_comparison_changed));
//    m_imag_comparison_combo->signal_changed().connect(sigc::mem_fun(*this, &OuterSelection::on_imag_comparison_changed));
//    m_combination_combo->signal_changed().connect(sigc::mem_fun(*this, &OuterSelection::on_combination_changed));
//    m_component_limit_entry->signal_notify_new_value().connect(sigc::mem_fun(*this, &OuterSelection::on_component_limit_changed));
//    display();
}

OuterSelection::~OuterSelection()
{
}

void OuterSelection::setup_ui_layout()
{
    auto main_layout = new QVBoxLayout();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->addWidget(new QLabel("<b>Select outer using ...</b>"));
    auto grid = new QGridLayout();
    grid->setHorizontalSpacing(5);
    grid->setContentsMargins(0, 0, 0, 0);
    grid->addWidget(m_norm_radio, 0, 0);
    grid->addWidget(m_components_radio, 1, 0);
    grid->addWidget(new QLabel("Component limit"), 2, 0);
    auto hlayout = new QHBoxLayout();
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->addWidget(m_real_comparison_combo);
    hlayout->addWidget(m_combination_combo);
    hlayout->addWidget(m_imag_comparison_combo);
    hlayout->addStretch();
    grid->addLayout(hlayout, 1, 1);
    hlayout = new QHBoxLayout();
    hlayout->setSpacing(5);
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->addWidget(m_component_limit_entry);
    hlayout->addStretch();
    grid->addLayout(hlayout, 2, 1);
    main_layout->addLayout(grid);
    auto line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    main_layout->addWidget(line);
    
    setLayout(main_layout);
}

void OuterSelection::connect_signals()
{
    connect(m_norm_radio, SIGNAL(clicked(bool)),
            this,         SLOT(on_bailout_radio_changed(bool)));
    connect(m_components_radio, SIGNAL(clicked(bool)),
            this,         SLOT(on_components_radio_changed(bool)));
    connect(m_real_comparison_combo, SIGNAL(currentIndexChanged(int)),
            this,         SLOT(on_real_comparison_changed(int)));
    connect(m_imag_comparison_combo, SIGNAL(currentIndexChanged(int)),
            this,         SLOT(on_imag_comparison_changed(int)));
    connect(m_combination_combo, SIGNAL(currentIndexChanged(int)),
            this,         SLOT(on_combination_changed(int)));
    connect(m_component_limit_entry, SIGNAL(changed()),
            this,         SLOT(on_component_limit_changed()));
}

void OuterSelection::display()
{
    m_ignore_signals = true;
    m_config.SetFractalType(Config::instance()->getFractalType());
    m_select = m_config.getSelection();
    bool bailout = (m_select[0] == 'n');
    m_norm_radio->setChecked(bailout);
    m_component_limit_entry->Set(bailout ? "0" : longdoubleToString(m_config.getSelectLimit()));
    m_component_limit_entry->setEnabled(!bailout);
    m_components_radio->setChecked(!bailout);
    m_real_comparison_combo->setEnabled(!bailout);
    m_imag_comparison_combo->setEnabled(!bailout);
    m_combination_combo->setEnabled(!bailout);
    if (m_select[0] == 'a')
    {
        m_real_comparison_combo->setValue(m_select[2] == '>' ? CCR_ABS_GT_LIMIT : CCR_ABS_LT_LIMIT);
    }
    else
    {
        m_real_comparison_combo->setValue(m_select[2] == '>' ? CCR_GT_LIMIT : CCR_LT_LIMIT);
    }
    if (m_select[1] == 'a')
    {
        m_imag_comparison_combo->setValue(m_select[3] == '>' ? CCI_ABS_GT_LIMIT : CCI_ABS_LT_LIMIT);
    }
    else
    {
        m_imag_comparison_combo->setValue(m_select[3] == '>' ? CCI_GT_LIMIT : CCI_LT_LIMIT);
    }
    if (m_select[4] == 'a')
    {
        m_combination_combo->setValue(C_AND);
    }
    else if (m_select[4] == 'o')
    {
        m_combination_combo->setValue(C_OR);
    }
    else
    {
        m_combination_combo->setValue(C_XOR);
    }
    m_ignore_signals = false;
}

void OuterSelection::on_bailout_radio_changed(bool checked)
{
    if (!m_ignore_signals)
    {
        if (checked)
        {
            // Only the first character is processed for this selection
            // type, the string is extended to match the length of the string
            // used for selection by component values.
            m_select = "normz";
            m_config.setSelection(m_select);
            display();
            emit outer_selection_changed();
        }
    }
}

void OuterSelection::on_components_radio_changed(bool checked)
{
    if (!m_ignore_signals)
    {
        if (checked)
        {
            m_select = "aa<<a";
            m_config.setSelection(m_select);
            display();
            emit outer_selection_changed();
        }
    }
}

void OuterSelection::on_real_comparison_changed(int value)
{
    if (!m_ignore_signals)
    {
        std::string ch1;
        std::string ch2;
        switch (static_cast<COMPONENT_COMPARISONS_REAL>(value))
        {
        default:
        case CCR_GT_LIMIT:
            ch1 = "r";
            ch2 = ">";
            break;
        case CCR_ABS_GT_LIMIT:
            ch1 = "a";
            ch2 = ">";
            break;
        case CCR_LT_LIMIT:
            ch1 = "r";
            ch2 = "<";
            break;
        case CCR_ABS_LT_LIMIT:
            ch1 = "a";
            ch2 = "<";
            break;
        }
        m_select.replace(0, 1, ch1);
        m_select.replace(2, 1, ch2);
        m_config.setSelection(m_select);
        display();
        emit outer_selection_changed();
    }
}

void OuterSelection::on_imag_comparison_changed(int value)
{
    if (!m_ignore_signals)
    {
        std::string ch1;
        std::string ch2;
        switch (static_cast<COMPONENT_COMPARISONS_IMAG>(value))
        {
        default:
        case CCI_GT_LIMIT:
            ch1 = "r";
            ch2 = ">";
            break;
        case CCI_ABS_GT_LIMIT:
            ch1 = "a";
            ch2 = ">";
            break;
        case CCI_LT_LIMIT:
            ch1 = "r";
            ch2 = "<";
            break;
        case CCI_ABS_LT_LIMIT:
            ch1 = "a";
            ch2 = "<";
            break;
        }
        m_select.replace(1, 1, ch1);
        m_select.replace(3, 1, ch2);
        m_config.setSelection(m_select);
        display();
        emit outer_selection_changed();
    }
}

void OuterSelection::on_combination_changed(int value)
{
    if (!m_ignore_signals)
    {
        switch (static_cast<COMBINATION>(value))
        {
        case C_AND:
            m_select.replace(4, 1, "a");
            break;
        case C_OR:
            m_select.replace(4, 1, "o");
            break;
        case C_XOR:
            m_select.replace(4, 1, "x");
            break;
        };
        m_config.setSelection(m_select);
        display();
        emit outer_selection_changed();
   }
}

void OuterSelection::on_component_limit_changed()
{
    if (!m_ignore_signals)
    {
        m_config.setSelectLimit(stringToLongDouble(m_component_limit_entry->Get()));
        emit outer_selection_changed();
    }
}