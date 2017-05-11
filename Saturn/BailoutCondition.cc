//
// File:   BailoutCondition.cc
// Author: M.R.Eggleston
//
// Created on 27 June 2011, 12:51
//

#include <iostream>
#include <QHBoxLayout>
#include "BailoutCondition.h"
#include "Utilities.h"

BailoutCondition::BailoutCondition(QWidget* parent)
:
QWidget(parent),
m_limit_entry(new NumberEntry(NumberEntry::FLOAT)),
m_converge_combo(new ConvergeBailoutConditionCombobox()),
m_diverge_combo(new DivergeBailoutConditionCombobox()),
m_gt_label(new QLabel(">")),
m_lt_label(new QLabel("<")),
m_emit(false)
{
    setup_ui_layout();
    connect_signals();
}

BailoutCondition::~BailoutCondition()
{
}

void BailoutCondition::setup_ui_layout()
{
    auto layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    auto label = new QLabel("Bailout");
    layout->addWidget(label);
    layout->addWidget(m_converge_combo);
    layout->addWidget(m_diverge_combo);
    m_diverge_combo->hide();
    layout->addWidget(m_gt_label);
    layout->addWidget(m_lt_label);
    m_lt_label->hide();
    layout->addWidget(m_limit_entry);
    layout->addStretch();
    setLayout(layout);
}

void BailoutCondition::connect_signals()
{
    connect(m_limit_entry, SIGNAL(changed()),
            this,          SLOT(on_limit_changed()));
    connect(m_converge_combo, SIGNAL(currentIndexChanged(int)),
            this,          SLOT(on_condition_changed(int)));
    connect(m_diverge_combo, SIGNAL(currentIndexChanged(int)),
            this,          SLOT(on_condition_changed(int)));
}

void BailoutCondition::load(FRACTAL_TYPE ft)
{
    m_emit = false;
    m_config.SetFractalType(ft);
    m_limit_entry->Set(longdoubleToString(m_config.getLimit()));
    auto bailout = m_config.getBailout();
    bool convergent = m_config.isConvergent();
    (convergent ? m_converge_combo->setValue(bailout) : m_diverge_combo->setValue(bailout));
    (convergent ? m_diverge_combo->hide() : m_diverge_combo->show());
    (convergent ? m_converge_combo->show() : m_converge_combo->hide());
    displayLimit();
    m_emit = true;
}

void BailoutCondition::on_limit_changed()
{
    m_config.setLimit(stringToLongDouble(m_limit_entry->Get()));
    if (m_emit)
    {
        emit changed();
    }
}

void BailoutCondition::on_condition_changed(int)
{
    bool convergent = m_config.isConvergent();
    auto condition = (convergent ? m_converge_combo->getValue() : m_diverge_combo->getValue());
    m_config.setBailout(condition);
    displayLimit();
    if (m_emit)
    {
        emit changed();
    }
}

void BailoutCondition::displayLimit()
{
    bool none = (m_config.getBailout() == B_NONE);
    if (m_config.isConvergent())
    {
        (none ? m_lt_label->hide() : m_lt_label->show());
        m_gt_label->hide();
    }
    else
    {
        (none ? m_gt_label->hide() : m_gt_label->show());
        m_lt_label->hide();
    }
    (none ? m_limit_entry->hide() : m_limit_entry->show());
}
        

