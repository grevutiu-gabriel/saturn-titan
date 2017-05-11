// 
// File:   ComplexFunctionParametersContainer.cc
// Author: M.R.Eggleston
// 
// Created on 13 December 2012, 10:36
//

#include <QHBoxLayout>
#include <QVBoxLayout>
#include "ComplexFunctionParametersContainer.h"
#include "Utilities.h"
#include "KeyString.h"

ComplexFunctionParametersContainer::ComplexFunctionParametersContainer(QWidget* parent)
:
QWidget(parent),
m_list(new QListWidget()),
m_f(new ComplexFunctionParameterCombobox()),
m_function_pair_widget(new QWidget()),
m_f_r(new FunctionParameterCombobox()),
m_f_i(new FunctionParameterCombobox()),
m_pair_check(new QCheckBox("function pair")),
m_size_widget(new QWidget()),
m_size_entry(new NumberEntry(NumberEntry::FLOAT)),
m_rotation_widget(new QWidget()),
m_rotation_spin(new QSpinBox()),
m_parameter_widget(new QWidget()),
m_real_entry(new NumberEntry(NumberEntry::FLOAT)),
m_imag_entry(new NumberEntry(NumberEntry::FLOAT)),
m_main_widget(new QWidget()),
m_no_parameters_label(new QLabel("no complex function parameters defined")),
m_emit(false),
m_row(0)
{
    setup_ui_layout();
    connect_signals();
}

ComplexFunctionParametersContainer::~ComplexFunctionParametersContainer()
{
}

void ComplexFunctionParametersContainer::setup_ui_layout()
{
    auto main_layout = new QVBoxLayout();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->addWidget(m_list);
    auto layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_f);
    auto layout2 = new QVBoxLayout();
    layout2->setSpacing(0);
    layout2->setContentsMargins(0, 0, 0, 0);
    layout2->addWidget(m_f_r);
    layout2->addWidget(m_f_i);
    m_function_pair_widget->setLayout(layout2);
    m_function_pair_widget->hide();
    layout->addWidget(m_function_pair_widget);
    layout->addWidget(m_pair_check);
    main_layout->addLayout(layout);
    layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(new QLabel("r"));
    layout->addWidget(m_real_entry);
    layout->addWidget(new QLabel("i"));
    layout->addWidget(m_imag_entry);
    m_parameter_widget->setLayout(layout);
    main_layout->addWidget(m_parameter_widget);
    layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(new QLabel("Size"));
    layout->addWidget(m_size_entry);
    layout->addStretch();
    m_size_widget->setLayout(layout);
    m_size_widget->hide();
    main_layout->addWidget(m_size_widget);
    layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(new QLabel("Rotation"));
    layout->addWidget(m_rotation_spin);
    layout->addStretch();
    m_rotation_widget->setLayout(layout);
    m_rotation_widget->hide();
    main_layout->addWidget(m_rotation_widget);
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

void ComplexFunctionParametersContainer::connect_signals()
{
    connect(m_list, SIGNAL(currentRowChanged(int)),
            this,   SLOT(on_row_changed(int)));
    connect(m_f,    SIGNAL(currentIndexChanged(int)),
            this,   SLOT(on_function_changed(int)));
    connect(m_pair_check, SIGNAL(stateChanged(int)),
            this,   SLOT(on_pair_changed(int)));
    connect(m_f_r,  SIGNAL(currentIndexChanged(int)),
            this,   SLOT(on_real_function_changed(int)));
    connect(m_f_i,  SIGNAL(currentIndexChanged(int)),
            this,   SLOT(on_imag_function_changed(int)));
    connect(m_size_entry, SIGNAL(changed()),
            this,   SLOT(on_parameter_changed()));
    connect(m_rotation_spin, SIGNAL(valueChanged(int)),
            this,   SLOT(on_rotation_changed(int)));
    connect(m_real_entry, SIGNAL(changed()),
            this,   SLOT(on_parameter_changed()));
    connect(m_imag_entry, SIGNAL(changed()),
            this,   SLOT(on_parameter_changed()));
}

void ComplexFunctionParametersContainer::load(FRACTAL_TYPE ft)
{
    m_row = m_list->currentRow();
    if (m_row < 0)
    {
        m_row = 0;
    }
    m_config.SetFractalType(ft);
    int number_of_function_parameters = m_config.getNumberOfComplexFunctionParameters();
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
    QString base_str = "F";
    m_list->clear();
    for (int i = 0; i < number_of_function_parameters; i++)
    {
        QString str = base_str;
        str += QString::number(i+1);
        str += " = ";
        str += complexFunctionToString(m_config.getComplexFunctionParameter(i));
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

void ComplexFunctionParametersContainer::displayValueAtCursor()
{
    m_emit = false;
    m_row = m_list->currentRow();
    std::string str = m_config.getComplexFunctionParameter(m_row);
    KeyString keys(str);
    bool is_pair = (keys.GetKey("pair", "n") == "y");
    m_pair_check->setCheckState(is_pair ? Qt::Checked : Qt::Unchecked);
    if (is_pair)
    {
        m_function_pair_widget->show();
        m_f->hide();
        auto rid = static_cast<FUNCTION_PARAMETER>(keys.GetKeyAsInt("rid", 0));
        auto iid = static_cast<FUNCTION_PARAMETER>(keys.GetKeyAsInt("iid", 0));
        m_f_r->setValue(rid);
        m_f_i->setValue(iid);
        bool has_parameter = hasParameter(rid);
        m_real_entry->Set(has_parameter ? keys.GetKey("r", "0") : "0");
        m_real_entry->setEnabled(has_parameter);
        has_parameter = hasParameter(iid);
        m_imag_entry->Set(has_parameter ? keys.GetKey("i", "0") : "0");
        m_imag_entry->setEnabled(has_parameter);
        m_rotation_widget->hide();
        m_size_widget->hide();
    }
    else
    {
        m_function_pair_widget->hide();
        m_f->show();
        auto id = static_cast<COMPLEX_FUNCTION_PARAMETER>(keys.GetKeyAsInt("id", 0));
        m_f->setValue(id);
        if (hasParameter(id))
        {
            m_real_entry->Set(keys.GetKey("r", "0"));
            m_imag_entry->Set(keys.GetKey("i", "0"));
            m_parameter_widget->show();
            m_real_entry->setEnabled(true);
            m_imag_entry->setEnabled(true);
            m_rotation_widget->hide();
            m_size_widget->hide();
        }
        else
        {
            m_parameter_widget->hide();
            if (hasRotation(id))
            {
                m_rotation_widget->show();
                m_size_widget->hide();
                int r = keys.GetKeyAsInt("rotation", 0);
                m_rotation_spin->setValue(r > 180 ? r - 360 : r);
            }
            else if (hasSize(id))
            {
                m_size_widget->show();
                m_rotation_widget->hide();
                m_size_entry->Set(keys.GetKey("size", "0"));
            }
            else
            {
                m_rotation_widget->hide();
                m_size_widget->hide();
                m_parameter_widget->show();
                m_real_entry->setEnabled(false);
                m_imag_entry->setEnabled(false);
            }
        }
    }
    m_emit = true;
}

void ComplexFunctionParametersContainer::on_row_changed(int row)
{
    if (row != -1)
    {
        displayValueAtCursor();
    }
}

void ComplexFunctionParametersContainer::on_function_changed(int)
{
    if (m_emit)
    {
        int index = m_list->currentRow();
        COMPLEX_FUNCTION_PARAMETER id = m_f->getValue();
        m_config.setComplexFunctionParameter(index, defaultComplexFunctionValues(id));
        displayParameterInList(index);
        displayValueAtCursor();
        emit changed();
        displayValueAtCursor();
    }
}

void ComplexFunctionParametersContainer::on_real_function_changed(int)
{
    if (m_emit)
    {
        int index = m_list->currentRow();
        KeyString keys;
        keys.SetKey("pair", "y");
        auto rid = m_f_r->getValue();
        keys.SetKey("rid", static_cast<int>(rid));
        auto iid = m_f_i->getValue();
        keys.SetKey("iid", static_cast<int>(iid));
        if (hasParameter(rid))
        {
            keys.SetKey("r", defaultValue(rid));
        }
        if (hasParameter(iid))
        {
            keys.SetKey("i", m_imag_entry->Get());
        }
        m_config.setComplexFunctionParameter(index, keys.String());
        displayParameterInList(index);
        updateInputFields();
        emit changed();
        displayValueAtCursor();
    }
}

void ComplexFunctionParametersContainer::on_imag_function_changed(int)
{
    if (m_emit)
    {
        int index = m_list->currentRow();
        KeyString keys;
        keys.SetKey("pair", "y");
        auto rid = m_f_r->getValue();
        keys.SetKey("rid", static_cast<int>(rid));
        auto iid = m_f_i->getValue();
        keys.SetKey("iid", static_cast<int>(iid));
        if (hasParameter(iid))
        {
            keys.SetKey("i", defaultValue(iid));
        }
        if (hasParameter(rid))
        {
            keys.SetKey("r", m_real_entry->Get());
        }
        m_config.setComplexFunctionParameter(index, keys.String());
        displayParameterInList(index);
        updateInputFields();
        emit changed();
        displayValueAtCursor();
    }
}

void ComplexFunctionParametersContainer::on_pair_changed(int)
{
    if (m_emit)
    {
        int index = m_list->currentRow();
        KeyString keys;
        bool pair = m_pair_check->checkState();
        keys.SetKey("pair", pair ? "y" : "n");
        if (pair)
        {
            keys.SetKey("rid", static_cast<int>(FP_NO_OP));
            keys.SetKey("iid", static_cast<int>(FP_NO_OP));
        }
        else
        {
            keys.SetKey("id", static_cast<int>(CFP_NO_OP));
        }
        m_config.setComplexFunctionParameter(index, keys.String());
        displayParameterInList(index);
        updateInputFields();
        displayValueAtCursor();
        emit changed();
    }
}

void ComplexFunctionParametersContainer::on_parameter_changed()
{
    if (m_emit)
    {
        if (updateParameter())
        {
            emit changed();
        }
    }
}

void ComplexFunctionParametersContainer::on_rotation_changed(int)
{
    on_parameter_changed();
}

bool ComplexFunctionParametersContainer::updateParameter()
{
    auto p = m_config.getComplexFunctionParameter(m_row);
    KeyString keys;
    bool pair = (m_pair_check->checkState() == Qt::Checked);
    keys.SetKey("pair", pair ? "y" : "n");
    if (pair)
    {
        auto rid = m_f_r->getValue();
        auto iid = m_f_i->getValue();
        keys.SetKey("rid", static_cast<int>(rid));
        keys.SetKey("iid", static_cast<int>(iid));
        if (hasParameter(rid))
        {
            keys.SetKey("r", m_real_entry->Get());
        }
        if (hasParameter(iid))
        {
            keys.SetKey("i", m_imag_entry->Get());
        }
    }
    else
    {
        auto id = m_f->getValue();
        keys.SetKey("id", static_cast<int>(id));
        if (hasParameter(id))
        {
            keys.SetKey("r", m_real_entry->Get());
            keys.SetKey("i", m_imag_entry->Get());
        }
        else if (hasSize(id))
        {
            keys.SetKey("size", m_size_entry->Get());
        }
        else if (hasRotation(id))
        {
            keys.SetKey("rotation", m_rotation_spin->value());
        }
    }
    bool value_changed = (p != keys.String());
    if (value_changed)
    {
        m_config.setComplexFunctionParameter(m_row, keys.String());
        displayParameterInList(m_row);
        updateInputFields();
        emit changed();
    }
    return value_changed;
}

void ComplexFunctionParametersContainer::displayParameterInList(int index)
{
    auto item = m_list->item(index);
    QString str = "F";
    str += QString::number(index+1);
    str += " = ";
    str += complexFunctionToString(m_config.getComplexFunctionParameter(index));
    item->setText(str);
}

void ComplexFunctionParametersContainer::updateInputFields()
{
    std::string str = m_config.getComplexFunctionParameter(m_row);
    KeyString keys(str);
    bool is_pair = (keys.GetKey("pair", "n") == "y");
    if (is_pair)
    {
        m_function_pair_widget->show();
        m_f->hide();
        auto rid = static_cast<FUNCTION_PARAMETER>(keys.GetKeyAsInt("rid", 0));
        auto iid = static_cast<FUNCTION_PARAMETER>(keys.GetKeyAsInt("iid", 0));
        bool has_parameter = hasParameter(rid);
        m_real_entry->setEnabled(has_parameter);
        has_parameter = hasParameter(iid);
        m_imag_entry->setEnabled(has_parameter);
        m_rotation_widget->hide();
        m_size_widget->hide();
    }
    else
    {
        auto id = static_cast<COMPLEX_FUNCTION_PARAMETER>(keys.GetKeyAsInt("id", 0));
        m_function_pair_widget->hide();
        m_f->show();
        if (hasParameter(id))
        {
            m_parameter_widget->show();
            m_real_entry->setEnabled(true);
            m_imag_entry->setEnabled(true);
            m_rotation_widget->hide();
            m_size_widget->hide();
        }
        else
        {
            m_parameter_widget->hide();
            if (hasRotation(id))
            {
                m_rotation_widget->show();
                m_size_widget->hide();
            }
            else if (hasSize(id))
            {
                m_size_widget->show();
                m_rotation_widget->hide();
            }
            else
            {
                m_rotation_widget->hide();
                m_size_widget->hide();
                m_parameter_widget->show();
                m_real_entry->setEnabled(false);
                m_imag_entry->setEnabled(false);
            }
        }
    }
}
