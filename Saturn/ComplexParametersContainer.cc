// 
// File:   ComplexParameterContainers.cc
// Author: M.R.Eggleston
// 
// Created on 24 April 2012, 16:16
//

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include "ComplexParametersContainer.h"
#include "Utilities.h"

ComplexParametersContainer::ComplexParametersContainer(QWidget* parent)
:
QWidget(parent),
m_list(new QListWidget()),
m_real_entry(new NumberEntry(NumberEntry::FLOAT)),
m_imag_entry(new NumberEntry(NumberEntry::FLOAT)),
m_substitute_check(new QCheckBox("location in the complex plane")),
m_ignore_transforms_check(new QCheckBox("ignore transforms")),
m_negative_c_check(new QCheckBox("-ve")),
m_main_widget(new QWidget),
m_no_complex_parameters_label(new QLabel("no complex parameters defined")),
m_emit(false),
m_row(0)
{
    setup_ui_layout();
    connect_signals();
}

ComplexParametersContainer::~ComplexParametersContainer()
{
}

void ComplexParametersContainer::setup_ui_layout()
{
    auto main_layout = new QVBoxLayout();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->addWidget(m_list);
    auto layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(new QLabel("r"));
    layout->addWidget(m_real_entry);
    layout->addWidget(new QLabel("i"));
    layout->addWidget(m_imag_entry);
    main_layout->addLayout(layout);
    layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_substitute_check);
    layout->addWidget(m_ignore_transforms_check);
    layout->addWidget(m_negative_c_check);
    main_layout->addLayout(layout);
    m_main_widget->setLayout(main_layout);
    auto vlayout = new QVBoxLayout();
    vlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->addWidget(m_main_widget);
    m_no_complex_parameters_label->hide();
    vlayout->addWidget(m_no_complex_parameters_label);
    setLayout(vlayout);
}

void ComplexParametersContainer::connect_signals()
{
    connect(m_list, SIGNAL(currentRowChanged(int)),
            this,   SLOT(on_row_changed(int)));
    connect(m_real_entry, SIGNAL(changed()),
            this,   SLOT(on_parameter_changed()));
    connect(m_imag_entry, SIGNAL(changed()),
            this,   SLOT(on_parameter_changed()));
    connect(m_substitute_check, SIGNAL(stateChanged(int)),
            this,   SLOT(on_parameter_state_changed(int)));
    connect(m_ignore_transforms_check, SIGNAL(stateChanged(int)),
            this,   SLOT(on_parameter_state_changed(int)));
    connect(m_negative_c_check, SIGNAL(stateChanged(int)),
            this,   SLOT(on_parameter_state_changed(int)));
}


void ComplexParametersContainer::load(FRACTAL_TYPE ft)
{
    m_load_in_progress = true;
    m_row = m_list->currentRow();
    if (m_row < 0)
    {
        m_row = 0;
    }
    m_list->clear();
    m_config.SetFractalType(ft);
    int number_of_complex_parameters = m_config.getNumberOfComplexParameters();
    if (number_of_complex_parameters > 0)
    {
        m_main_widget->show();
        m_no_complex_parameters_label->hide();
    }
    else
    {
        m_main_widget->hide();
        m_no_complex_parameters_label->show();
    }
    uint complex_base = 0x03b1; // 'α'
    QString str("z0 = ");
    auto z0_type = m_config.getInitialValues();
    auto z0 = m_config.getFixedInitialValue();
    switch(z0_type)
    {
    case FIXED:
        str += complexNumberToString(z0);
        break;
    case UNTRANSFORMED:
        str += "location in the complex plane, ignore transforms";
        break;
    case TRANSFORMED:
        str += "location in the complex plane";
        break;
    }
    m_list->addItem(str);
    for (int i = 0; i < number_of_complex_parameters; i++, complex_base++)
    {
        str = " ";
        str += QChar(complex_base);
        str += " = ";
        if (m_config.getComplexParameterType(i) == PT_IS_C)
        {
            str += "location in the complex plane";
        }
        else if (m_config.getComplexParameterType(i) == PT_IS_NEG_C)
        {
            str += "negative location in the complex plane";
        }
        else
        {
            str += complexNumberToString(m_config.getComplexParameter(i));
        }
        m_list->addItem(str);
    }
    if (number_of_complex_parameters > 0)
    {
        m_emit = false;
        m_list->setCurrentRow(m_row);
        m_emit = true;
        displayValueAtCursor();
    }
    m_load_in_progress = false;
}

void ComplexParametersContainer::displayValueAtCursor()
{
    m_emit = false;
    int row = m_list->currentRow();
    if (row >= 0)
    {
        m_row = row;
        PARAMETER_TYPE type;
        bool ignore_transforms = false;
        bool is_julia = m_config.isJulia();
        StringComplex p;
        if (m_row == 0)
        {
            p = m_config.getFixedInitialValue();
            auto z0_type = m_config.getInitialValues();
            type = (z0_type == FIXED ? PT_NUMBER : PT_IS_C);
            ignore_transforms = (z0_type == UNTRANSFORMED);
            m_substitute_check->setEnabled(!is_julia);
        }
        else
        {
            int index = m_row - 1;
            p = m_config.getComplexParameter(index);
            type = m_config.getComplexParameterType(index);
            m_substitute_check->setEnabled(true);
        }
        m_real_entry->Set(p.r);
        m_imag_entry->Set(p.i);
        if (type == PT_NUMBER)
        {
            m_substitute_check->setCheckState(Qt::Unchecked);
            m_negative_c_check->setCheckState(Qt::Unchecked);
        }
        else if (type == PT_IS_C)
        {
            m_substitute_check->setCheckState(Qt::Checked);
            m_negative_c_check->setCheckState(Qt::Unchecked);
        }
        else
        {
            m_substitute_check->setCheckState(Qt::Checked);
            m_negative_c_check->setCheckState(Qt::Checked);
        }
        m_real_entry->setEnabled(type == PT_NUMBER);
        m_imag_entry->setEnabled(type == PT_NUMBER);
        if ((type != PT_NUMBER)  && (m_row == 0))
        {
            m_ignore_transforms_check->setCheckState(ignore_transforms ? Qt::Checked : Qt::Unchecked);
        }
        updateInputFields();
    }
    m_emit = true;
}

void ComplexParametersContainer::on_row_changed(int row)
{
    if (row != -1)
    {
        displayValueAtCursor();
    }
}


void ComplexParametersContainer::on_parameter_changed()
{
    if (m_emit)
    {
        if (updateParameter())
        {
            emit changed();
        }
    }
}

void ComplexParametersContainer::on_parameter_state_changed(int)
{
    on_parameter_changed();
}

bool ComplexParametersContainer::updateParameter()
{
    bool changed = false;
    bool is_c = (m_substitute_check->checkState() == Qt::Checked);
    bool is_neg_c = (m_negative_c_check->checkState() == Qt::Checked);
    PARAMETER_TYPE is_type = (!is_c ? PT_NUMBER : (is_neg_c ? PT_IS_NEG_C : PT_IS_C));
    if (m_row == 0)
    {
        auto was_type = m_config.getInitialValues();
        auto p = m_config.getFixedInitialValue();
        bool ignore_transforms = (m_ignore_transforms_check->checkState() == Qt::Checked);
        INITIAL_VALUE z0_type = FIXED;
        if (is_c)
        {
            z0_type = (ignore_transforms ? UNTRANSFORMED : TRANSFORMED);
        }
        changed = (was_type != z0_type);
        if (changed)
        {
            m_config.setInitialValues(z0_type);
        }
        bool fixed_value_changed = false;
        if (z0_type == FIXED)
        {
            std::string real = m_real_entry->Get();
            std::string imag = m_imag_entry->Get();
            fixed_value_changed = ((real != p.r) || (imag != p.i));
            if (fixed_value_changed)
            {
                m_config.setFixedInitialValue(StringComplex(real, imag));
            }
        }
        changed = (changed || fixed_value_changed); 
    }
    else
    {
        int index = m_row - 1;
        auto p = m_config.getComplexParameter(index);
        PARAMETER_TYPE was_type = m_config.getComplexParameterType(index);
        std::string real = m_real_entry->Get();
        std::string imag = m_imag_entry->Get();
        changed = ((real != p.r) || (imag != p.i) || (was_type != is_type));
        if (changed)
        {
            m_config.setComplexParameter(index, StringComplex(real, imag), is_type);
            if (m_config.isJulia())
            {
                m_config.setInitialValues(TRANSFORMED);
            }
        }
    }
    if (changed)
    {
        displayParameterInList(m_row);
        if (m_config.isJulia())
        {
            displayParameterInList(0);
        }
        updateInputFields();
    }
    displayValueAtCursor();
    return changed;
}

void ComplexParametersContainer::displayParameterInList(int row)
{
    auto item = m_list->item(row);
    if (item != nullptr)
    {
        if (row == 0)
        {
            QString str("z0 = ");
            auto z0_type = m_config.getInitialValues();
            auto z0 = m_config.getFixedInitialValue();
            switch(z0_type)
            {
            case FIXED:
                str += complexNumberToString(z0);
                break;
            case UNTRANSFORMED:
                str += "location in the complex plane, ignore transforms";
                break;
            case TRANSFORMED:
                str += "location in the complex plane";
                break;
            }
            item->setText(str);
        }
        else
        {
            uint index = m_row - 1;
            uint complex_base = 0x03b1; // 'α'
            QString str = " ";
            str += QChar(complex_base + index);
            str += " = ";
            if (m_config.getComplexParameterType(index) == PT_IS_C)
            {
                str += "location in the complex plane";
            }
            else if (m_config.getComplexParameterType(index) == PT_IS_NEG_C)
            {
                str += "negative location in the complex plane";
            }
            else
            {
                str += complexNumberToString(m_config.getComplexParameter(index));
            }
            item->setText(str);
        }
    }
}

void ComplexParametersContainer::updateInputFields()
{
    bool type = PT_NUMBER;
    if (m_row == 0)
    {
        bool is_julia = m_config.isJulia();
        auto z0_type = m_config.getInitialValues();
        type = (z0_type != FIXED ? PT_IS_C : PT_NUMBER);
        m_substitute_check->setEnabled(!is_julia);
        m_ignore_transforms_check->setEnabled(!is_julia);
        if (is_julia)
        {
            m_ignore_transforms_check->hide();
        }
        else
        {
            m_ignore_transforms_check->show();
        }
        m_negative_c_check->hide();
    }
    else
    {
        int index = m_row - 1;
        type = m_config.getComplexParameterType(index);
        m_substitute_check->setEnabled(true);
        m_negative_c_check->setEnabled(type != PT_NUMBER);
        m_ignore_transforms_check->hide();
        m_negative_c_check->show();
    }
    m_real_entry->setEnabled(type == PT_NUMBER);
    m_imag_entry->setEnabled(type == PT_NUMBER);
}
