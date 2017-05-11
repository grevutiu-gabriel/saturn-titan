// 
// File:   FunctionParametersContainer.cc
// Author: M.R.Eggleston
// 
// Created on 24 April 2012, 17:17
//

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "FunctionParametersContainer.h"
#include "Utilities.h"
#include "KeyString.h"

FunctionParametersContainer::FunctionParametersContainer(QWidget* parent)
:
QWidget(parent),
m_list(new QListWidget()),
m_entry(new NumberEntry(NumberEntry::FLOAT)),
m_f(new FunctionParameterCombobox()),
m_main_widget(new QWidget()),
m_no_parameters_label(new QLabel("no function parameters defined")),
m_emit(false),
m_row(0)
{
    setup_ui_layout();
    connect_signals();
}

FunctionParametersContainer::~FunctionParametersContainer()
{
}

void FunctionParametersContainer::setup_ui_layout()
{
    auto main_layout = new QVBoxLayout();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->addWidget(m_list);
    auto layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_f);
    layout->addWidget(new QLabel("p"));
    layout->addWidget(m_entry);
    main_layout->addLayout(layout);
    m_main_widget->setLayout(main_layout);
    auto vlayout = new QVBoxLayout();
    vlayout->setSpacing(0);
    vlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->addWidget(m_main_widget);
    m_no_parameters_label->hide();
    m_no_parameters_label->setAlignment(Qt::AlignCenter);
    vlayout->addWidget(m_no_parameters_label);
    setLayout(vlayout);
}

void FunctionParametersContainer::connect_signals()
{
    connect(m_list,  SIGNAL(currentRowChanged(int)),
            this,    SLOT(on_row_changed(int)));
    connect(m_entry, SIGNAL(changed()),
            this,    SLOT(on_parameter_changed()));
    connect(m_f,     SIGNAL(currentIndexChanged(int)),
            this,    SLOT(on_function_changed(int)));
}

void FunctionParametersContainer::load(FRACTAL_TYPE ft)
{
    m_row = m_list->currentRow();
    if (m_row < 0)
    {
        m_row = 0;
    }
    m_config.SetFractalType(ft);
    int number_of_function_parameters = m_config.getNumberOfFunctionParameters();
    if (number_of_function_parameters > 0)
    {
        m_main_widget->show();
        m_no_parameters_label->hide();
    }
    else
    {
        m_main_widget->hide();
        m_no_parameters_label->show();
    }
    m_list->clear();
    QString base_str = "f";
    for (int i = 0; i < number_of_function_parameters; i++)
    {
        QString str = base_str;
        str += QString::number(i+1);
        str += " = ";
        str += functionToString(m_config.getFunctionParameter(i));
        m_list->addItem(str);
    }
    if (number_of_function_parameters > 0)
    {
        m_emit = false;
        m_list->setCurrentRow(m_row);
        m_emit = true;
        displayValueAtCursor();
    }
}

void FunctionParametersContainer::displayValueAtCursor()
{
    m_emit = false;
    m_row = m_list->currentRow();
    KeyString keys(m_config.getFunctionParameter(m_row));
    auto function_id = static_cast<FUNCTION_PARAMETER>(keys.GetKeyAsInt("id", 0));
    m_f->setValue(function_id);
    bool has_parameter = hasParameter(function_id);
    m_entry->Set(has_parameter ? keys.GetKey("p", "0") : "0");
    m_entry->setEnabled(has_parameter);
    m_emit = true;
}

void FunctionParametersContainer::on_row_changed(int row)
{
    if (row != -1)
    {
        displayValueAtCursor();
    }
}

void FunctionParametersContainer::on_parameter_changed()
{
    if (m_emit)
    {
        if (updateParameter())
        {
            emit changed();
        }
    }
}

void FunctionParametersContainer::on_function_changed(int)
{
    if (m_emit)
    {
        FUNCTION_PARAMETER function = m_f->getValue();
        KeyString keys;
        keys.SetKey("id", static_cast<int>(function));
        keys.SetKey("p", defaultValue(function));
        m_config.setFunctionParameter(m_row, keys.String());
        displayParameterInList(m_row);
        displayValueAtCursor();
        emit changed();
    }
}

bool FunctionParametersContainer::updateParameter()
{
    auto p = m_config.getFunctionParameter(m_row);
    FUNCTION_PARAMETER function = m_f->getValue();
    KeyString keys;
    keys.SetKey("id", static_cast<int>(function));
    if (hasParameter(function))
    {
        keys.SetKey("p", m_entry->Get());
    }
    bool changed = (p != keys.String());
    if (changed)
    {
        m_config.setFunctionParameter(m_row, keys.String());
        displayParameterInList(m_row);
    }
    return changed;
}

void FunctionParametersContainer::displayParameterInList(int row)
{
    auto item = m_list->item(row);
    if (item != nullptr)
    {
        QString str = "f";
        str += QString::number(row+1);
        str += " = ";
        str += functionToString(m_config.getFunctionParameter(row));
        item->setText(str);
    }
}

