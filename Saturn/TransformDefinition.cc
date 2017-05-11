//
// File:   TransformDefinition.cc
// Author: M.R.Eggleston
//
// Created on 30 June 2011, 14:08
//

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include "TransformDefinition.h"
#include "KeyString.h"
#include "Utilities.h"

TransformDefinition::TransformDefinition(QWidget* parent)
:
QWidget(parent),
m_complex_function_combo(new ComplexFunctionParameterCombobox()),
m_real_function_combo(new FunctionParameterCombobox()),
m_imaginary_function_combo(new FunctionParameterCombobox()),
m_real_entry(new NumberEntry(NumberEntry::FLOAT)),
m_imaginary_entry(new NumberEntry(NumberEntry::FLOAT)),
m_size_entry(new NumberEntry(NumberEntry::FLOAT)),
m_rotation_spin(new QSpinBox()),
m_pair_check(new QCheckBox("function pair")),
m_rotation_widget(new QWidget()),
m_size_widget(new QWidget()),
m_parameter_widget(new QWidget()),
m_function_pair_widget(new QWidget()),
m_id(CFP_NO_OP),
m_size(1.0L),
m_rotation(0),
m_ignore_signals(false)
{
    setup_ui_layout();
    connect_signals();

    m_rotation_spin->setRange(-179, 180);
    m_rotation_spin->setWrapping(true);
//    m_rotation_spin->setDefault(0);
//    enableEditing(false);
}

TransformDefinition::~TransformDefinition()
{
}

void TransformDefinition::setup_ui_layout()
{
    auto main_layout = new QVBoxLayout();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    auto hlayout = new QHBoxLayout();
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->addWidget(m_complex_function_combo);
    auto vlayout = new QVBoxLayout();
    vlayout->setSpacing(0);
    vlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->addWidget(m_real_function_combo);
    vlayout->addWidget(m_imaginary_function_combo);
    m_function_pair_widget->setLayout(vlayout);
    m_function_pair_widget->hide();
    hlayout->addWidget(m_function_pair_widget);
    hlayout->addWidget(m_pair_check);
    hlayout->addStretch();
    main_layout->addLayout(hlayout);
    hlayout = new QHBoxLayout();
    hlayout->setSpacing(5);
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->addWidget(new QLabel("r"));
    hlayout->addWidget(m_real_entry);
    hlayout->addWidget(new QLabel("i"));
    hlayout->addWidget(m_imaginary_entry);
    m_parameter_widget->setLayout(hlayout);
    main_layout->addWidget(m_parameter_widget);
    hlayout = new QHBoxLayout();
    hlayout->setSpacing(5);
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->addWidget(new QLabel("Size"));
    hlayout->addWidget(m_size_entry);
    hlayout->addStretch();
    m_size_widget->setLayout(hlayout);
    m_size_widget->hide();
    main_layout->addWidget(m_size_widget);
    hlayout = new QHBoxLayout();
    hlayout->setSpacing(5);
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->addWidget(new QLabel("Rotation"));
    hlayout->addWidget(m_rotation_spin);
    hlayout->addStretch();
    m_rotation_widget->setLayout(hlayout);
    m_rotation_widget->hide();
    main_layout->addWidget(m_rotation_widget);

    setLayout(main_layout);
}

void TransformDefinition::connect_signals()
{
    connect(m_complex_function_combo, SIGNAL(currentIndexChanged(int)),
            this,                     SLOT(on_complex_function_changed(int)));
    connect(m_real_function_combo,    SIGNAL(currentIndexChanged(int)),
            this,                     SLOT(on_real_function_changed(int)));
    connect(m_imaginary_function_combo, SIGNAL(currentIndexChanged(int)),
            this,                     SLOT(on_imaginary_function_changed(int)));
    connect(m_real_entry,             SIGNAL(changed()),
            this,                     SLOT(on_parameter_changed()));
    connect(m_imaginary_entry,        SIGNAL(changed()),
            this,                     SLOT(on_parameter_changed()));
    connect(m_size_entry,             SIGNAL(changed()),
            this,                     SLOT(on_parameter_changed()));
    connect(m_rotation_spin,          SIGNAL(valueChanged(int)),
            this,                     SLOT(on_rotation_changed(int)));
    connect(m_pair_check,             SIGNAL(stateChanged(int)),
            this,                     SLOT(on_pair_changed(int)));
}

void TransformDefinition::display()
{
    m_ignore_signals = true;
    bool pair = (m_transform.GetKey("pair", "n") == "y");
    m_pair_check->setCheckState(pair ? Qt::Checked : Qt::Unchecked);
    m_pair_check->setEnabled(true);
    if (pair)
    {
        auto rid = static_cast<FUNCTION_PARAMETER>(m_transform.GetKeyAsInt("rid", 0));
        bool has_real = (hasParameter(rid));
        auto iid = static_cast<FUNCTION_PARAMETER>(m_transform.GetKeyAsInt("iid", 0));
        bool has_imag = (hasParameter(iid));
        m_real_entry->Set(has_real ? m_transform.GetKey("r", "0") : "0");
        m_imaginary_entry->Set(has_imag ? m_transform.GetKey("i", "0") : "0");
        m_real_function_combo->setValue(rid);
        m_imaginary_function_combo->setValue(iid);
        m_function_pair_widget->show();
        m_size_widget->hide();
        m_rotation_widget->hide();
        m_complex_function_combo->hide();
        m_real_entry->setEnabled(has_real);
        m_imaginary_entry->setEnabled(has_imag);
        m_parameter_widget->show();
    }
    else
    {
        auto id = static_cast<COMPLEX_FUNCTION_PARAMETER>(m_transform.GetKeyAsInt("id", 0));
        bool has_parameter = hasParameter(id);
        bool has_size = hasSize(id);
        bool has_rotation = hasRotation(id);
        m_complex_function_combo->setValue(id);
        m_complex_function_combo->setEnabled(true);
        m_complex_function_combo->show();
        m_function_pair_widget->hide();
        m_real_entry->Set(has_parameter ? m_transform.GetKey("r", "0") : "0");
        m_imaginary_entry->Set(has_parameter ? m_transform.GetKey("i", "0") : "0");
        m_real_entry->setEnabled(has_parameter);
        m_imaginary_entry->setEnabled(has_parameter);
        if (has_size)
        {
            m_size_entry->Set(m_transform.GetKey("size", "0"));
            m_size_widget->show();
            m_rotation_widget->hide();
        }
        else if (has_rotation)
        {
            int r = m_transform.GetKeyAsInt("rotation", 0);
            m_rotation_spin->setValue(r > 180 ? r - 360 : r);
            m_rotation_widget->show();
            m_size_widget->hide();
        }
        if (has_size || has_rotation)
        {
            m_parameter_widget->hide();
        }
        else
        {
            m_real_entry->setEnabled(has_parameter);
            m_imaginary_entry->setEnabled(has_parameter);
            m_parameter_widget->show();
            m_rotation_widget->hide();
            m_size_widget->hide();
        }
    }
    m_ignore_signals = false;
}

std::string TransformDefinition::getTransform()
{
    KeyString keys;
    if (m_pair_check->checkState() == Qt::Checked)
    {
        keys.SetKey("pair", "y");
        auto rid = m_real_function_combo->getValue();
        auto iid = m_imaginary_function_combo->getValue();
        keys.SetKey("rid", static_cast<int>(rid));
        if (hasParameter(rid))
        {
            keys.SetKey("r", m_real_entry->Get());
        }
        keys.SetKey("iid", static_cast<int>(iid));
        if (hasParameter(iid))
        {
            keys.SetKey("i", m_imaginary_entry->Get());
        }
    }
    else
    {
        keys.SetKey("pair", "n");
        auto id = m_complex_function_combo->getValue();
        keys.SetKey("id", static_cast<int>(id));
        if (hasParameter(id))
        {
            keys.SetKey("r", m_real_entry->Get());
            keys.SetKey("i", m_imaginary_entry->Get());
        }
        else if (hasSize(id))
        {
            keys.SetKey("size", m_size_entry->Get());
        }
        else if (hasRotation(id))
        {
            keys.SetKey("rotation", intToString(m_rotation_spin->value()));
        }
    }
    return keys.String();
}

void TransformDefinition::setTransform(const std::string &t)
{
    m_ignore_signals = true;
    m_transform = t;
    display();
    m_ignore_signals = false;
}

void TransformDefinition::enableEditing(bool enabled)
{
    if (enabled)
    {
        display();
    }
    else
    {
        m_ignore_signals = true;
        m_complex_function_combo->setValue(CFP_NO_OP);
        m_pair_check->setCheckState(Qt::Unchecked);
        m_real_entry->Set("0");
        m_imaginary_entry->Set("0");
        m_complex_function_combo->show();
        m_function_pair_widget->hide();
        m_parameter_widget->show();
        m_size_widget->hide();
        m_rotation_widget->hide();
        m_complex_function_combo->setEnabled(false);
        m_pair_check->setEnabled(false);
        m_real_entry->setEnabled(false);
        m_imaginary_entry->setEnabled(false);
        m_ignore_signals = false;
    }
}

void TransformDefinition::on_complex_function_changed(int)
{
    if (!m_ignore_signals)
    {
        auto id = m_complex_function_combo->getValue();
        m_transform = KeyString(defaultComplexFunctionValues(id));
        display();
        emit transform_changed();
    }
}

void TransformDefinition::on_real_function_changed(int)
{
    if (!m_ignore_signals)
    {
        auto rid = m_real_function_combo->getValue();
        auto iid = m_imaginary_function_combo->getValue();
        KeyString keys;
        keys.SetKey("pair", "y");
        keys.SetKey("rid", static_cast<int>(rid));
        if (hasParameter(rid))
        {
            keys.SetKey("r", defaultValue(rid));
        }
        keys.SetKey("iid", static_cast<int>(iid));
        if (hasParameter(iid))
        {
            keys.SetKey("i", m_imaginary_entry->Get());
        }
        m_transform = keys;
        display();
        emit transform_changed();
    }
}

void TransformDefinition::on_imaginary_function_changed(int)
{
    if (!m_ignore_signals)
    {
        auto rid = m_real_function_combo->getValue();
        auto iid = m_imaginary_function_combo->getValue();
        KeyString keys;
        keys.SetKey("pair", "y");
        keys.SetKey("rid", static_cast<int>(rid));
        if (hasParameter(rid))
        {
            keys.SetKey("r", m_real_entry->Get());
        }
        keys.SetKey("iid", static_cast<int>(iid));
        if (hasParameter(iid))
        {
            keys.SetKey("i", defaultValue(iid));
        }
        m_transform = keys;
        display();
        emit transform_changed();
    }
}

void TransformDefinition::on_pair_changed(int state)
{
    if (!m_ignore_signals)
    {
        KeyString keys;
        if (state == Qt::Checked)
        {
            keys.SetKey("pair", "y");
            keys.SetKey("rid", static_cast<int>(FP_NO_OP));
            keys.SetKey("rid", static_cast<int>(FP_NO_OP));
        }
        else
        {
            keys.SetKey("pair", "n");
            keys.SetKey("id", static_cast<int>(CFP_NO_OP));
        }
        m_transform = keys;
        display();
        emit transform_changed();
    }
}

void TransformDefinition::on_parameter_changed()
{
    if (!m_ignore_signals)
    {
        KeyString keys;
        if (m_pair_check->checkState() == Qt::Checked)
        {
            auto rid = m_real_function_combo->getValue();
            auto iid = m_imaginary_function_combo->getValue();
            keys.SetKey("pair", "y");
            keys.SetKey("rid", intToString(static_cast<int>(rid)));
            keys.SetKey("iid", intToString(static_cast<int>(iid)));
            if (hasParameter(rid))
            {
                keys.SetKey("r", m_real_entry->Get());
            }
            if (hasParameter(iid))
            {
                keys.SetKey("i", m_imaginary_entry->Get());
            }
        }
        else
        {
            auto id = m_complex_function_combo->getValue();
            keys.SetKey("pair", "n");
            keys.SetKey("id", intToString(static_cast<int>(id)));
            if (hasParameter(id))
            {
                keys.SetKey("r", m_real_entry->Get());
                keys.SetKey("i", m_imaginary_entry->Get());
            }
            else if (hasSize(id))
            {
                keys.SetKey("size", m_size_entry->Get());
            }
            else if (hasRotation(id))
            {
                keys.SetKey("rotation", intToString(m_rotation_spin->value()));
            }
        }
        m_transform = keys;
        display();
        emit transform_changed();
    }
}

void TransformDefinition::on_rotation_changed(int)
{
    on_parameter_changed();
}