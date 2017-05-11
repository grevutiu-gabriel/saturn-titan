// 
// File:   ParametersContainer.cc
// Author: M.R.Eggleston
// 
// Split from FractalTab on 11 April 2012, 09:58
//

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include "ParametersContainer.h"
#include "Utilities.h"

ParametersContainer::ParametersContainer(QWidget* parent)
:
QWidget(parent),
m_list(new QListWidget()),
m_p(new NumberEntry(NumberEntry::FLOAT)),
m_main_widget(new QWidget()),
m_no_parameters_label(new QLabel("no parameters defined")),
m_emit(false),
m_row(0)
{
    setup_ui_layout();
    connect_signals();
}

ParametersContainer::~ParametersContainer()
{
}


void ParametersContainer::setup_ui_layout()
{
    auto main_layout = new QVBoxLayout();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->addWidget(m_list);
    auto layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(new QLabel("value"));
    layout->addWidget(m_p);
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

void ParametersContainer::connect_signals()
{
    connect(m_list, SIGNAL(currentRowChanged(int)),
            this,   SLOT(on_row_changed(int)));
    connect(m_p,    SIGNAL(changed()),
            this,   SLOT(on_parameter_changed()));
}

void ParametersContainer::load(FRACTAL_TYPE ft)
{
    m_single_orbit = isSingleOrbit(ft);
    m_row = m_list->currentRow();
    if (m_row < 0)
    {
        m_row = 0;
    }
    m_config.SetFractalType(ft);
    int number_of_parameters = m_config.getNumberOfParameters();
    if (number_of_parameters > 0)
    {
        m_main_widget->show();
        m_no_parameters_label->hide();
    }
    else
    {
        m_main_widget->hide();
        m_no_parameters_label->show();
    }
    uint base = static_cast<uint>('A');
    StringComplex z = m_config.getFixedInitialValue();
    m_list->clear();
    if (m_single_orbit)
    {
        m_list->addItem("x0 = " + QString::fromStdString(z.r));
        m_list->addItem("y0 = " + QString::fromStdString(z.i));
    }
    for (int i = 0; i < number_of_parameters; i++, base++)
    {
        QString str = QChar(base);
        str += " = ";
        str += QString::fromStdString(m_config.getParameter(i));
        m_list->addItem(str);
    }
    if ((number_of_parameters > 0) || m_single_orbit)
    {
        m_emit = false;
        m_list->setCurrentRow(m_row);
        m_emit = true;
        displayValueAtCursor();
    }
}

void ParametersContainer::on_parameter_changed()
{
    if (m_emit)
    {
        if (updateParameter())
        {
            emit changed();
        }
    }
}

void ParametersContainer::displayValueAtCursor()
{
    m_emit = false;
    m_row = m_list->currentRow();
    if (m_single_orbit)
    {
        if (m_row > 1)
        {
            m_p->Set(m_config.getParameter(m_row-2));
        }
        else
        {
            auto z = m_config.getFixedInitialValue();
            m_p->Set(m_row == 0 ? z.r : z.i);
        }
    }
    else
    {
        m_p->Set(m_config.getParameter(m_row));
    }
    m_emit = true;
}

void ParametersContainer::on_row_changed(int row)
{
    if (row != -1)
    {
        displayValueAtCursor();
    }
}

bool ParametersContainer::updateParameter()
{
    std::string new_p = m_p->Get();
    std::string p;
    StringComplex z;
    auto row = m_row;
    if (m_single_orbit)
    {
        row -= 2;
    }
    if (row < 0)
    {
        z = m_config.getFixedInitialValue();
        p = (row == -2 ? z.r : z.i);
    }
    p = m_config.getParameter(row);
    bool changed = (p != new_p);
    if (changed)
    {
        if (row < 0)
        {
            if (row == -2)
            {
                z.r = new_p;
            }
            else
            {
                z.i = new_p;
            }
            m_config.setFixedInitialValue(z);
        }
        else
        {
            m_config.setParameter(row, new_p);
        }
        displayParameterInList(m_row);
    }
    return changed;
}

void ParametersContainer::displayParameterInList(int row)
{
    auto item = m_list->item(row);
    int base = static_cast<int>('A');
    QString str;
    QString p;
    if (m_single_orbit)
    {
        row -= 2;
    }
    if (row < 0)
    {
        str = (row == -2 ? "x0 = " : "y0 = ");
        auto z = m_config.getFixedInitialValue();
        str += QString::fromStdString(row == -2 ? z.r : z.i);
    }
    else
    {
        str = QChar(base + row);
        str += " = ";
        p = QString::fromStdString(m_config.getParameter(row));
    }
    str += p;
    item->setText(str);
}

