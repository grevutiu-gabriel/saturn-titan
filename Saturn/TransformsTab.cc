//
// File:   TransformsTab.cc
// Author: M.R.Eggleston
//
// Created on 30 June 2011, 13:04
//

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "Config.h"
#include "KeyString.h"
#include "TransformsTab.h"
#include "Utilities.h"

TransformsTab::TransformsTab(QWidget* parent)
:
QWidget(parent),
m_add_button(new QPushButton("Add")),
m_delete_button(new QPushButton("Delete")),
m_down_button(new QPushButton("Down")),
m_up_button(new QPushButton("Up")),
m_add_set_button(new QPushButton("Add Set")),
m_delete_set_button(new QPushButton("Delete Set")),
m_delete_all_button(new QPushButton("Delete All")),
m_sequence_line(new QLineEdit()),
m_transform(new TransformDefinition()),
m_transforms_tree(new TransformTree()),
m_ignore_signals(false),
m_is_transform(false),
m_set(0),
m_row(-1)
{
    setFractalType(Config::instance()->getFractalType());
    setup_ui_layout();
    connect_signals();
}

TransformsTab::~TransformsTab()
{
}

void TransformsTab::setup_ui_layout()
{
    auto main_layout = new QVBoxLayout();
    main_layout->setSpacing(0);
    auto label = new QLabel();
    label->setWordWrap(true);
    label->setText(
        "Transform sets (A, B etc.) are applied to iterations of the fractal "
        "formula. Only one transform set is applied at each iteration, the "
        "order in which transform sets are applied is controlled by the transform "
        "sequence, e.g. AB will apply transform set A for one iteration then "
        "set B for the next iteration. The sequence is repeated until "
        "completion.");
    main_layout->addWidget(label);
    auto hlayout = new QHBoxLayout();
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->addWidget(new QLabel("Sequence"));
    hlayout->addWidget(m_sequence_line);
    main_layout->addLayout(hlayout);
    auto widget = new QWidget();
    widget->setFixedHeight(400);
    auto vlayout = new QVBoxLayout();
    vlayout->setContentsMargins(0, 0, 0, 0);
    hlayout = new QHBoxLayout();
    hlayout->setSpacing(0);
    hlayout->setContentsMargins(0, 0, 0, 0);
    m_transforms_tree->setHeaderHidden(true);
    hlayout->addWidget(m_transforms_tree);
    auto vlayout2 = new QVBoxLayout();
    vlayout2->setSpacing(0);
    vlayout2->setContentsMargins(0, 0, 0, 0);
    vlayout2->addWidget(m_add_button);
    vlayout2->addWidget(m_delete_button);
    label = new QLabel("Move");
    label->setAlignment(Qt::AlignHCenter);
    vlayout2->addWidget(label);
    vlayout2->addWidget(m_up_button);
    vlayout2->addWidget(m_down_button);
    vlayout2->addStretch();
    vlayout2->addWidget(m_add_set_button);
    vlayout2->addWidget(m_delete_set_button);
    vlayout2->addWidget(m_delete_all_button);
    hlayout->addLayout(vlayout2);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(m_transform);
    widget->setLayout(vlayout);
    main_layout->addWidget(widget);
    
//    main_layout->addStretch();
    setLayout(main_layout);
}

void TransformsTab::connect_signals()
{
    connect(m_add_button,    SIGNAL(clicked(bool)),
            this,            SLOT(on_add_button(bool)));
    connect(m_delete_button, SIGNAL(clicked(bool)),
            this,            SLOT(on_delete_button(bool)));
    connect(m_up_button,     SIGNAL(clicked(bool)),
            this,            SLOT(on_up_button(bool)));
    connect(m_down_button,   SIGNAL(clicked(bool)),
            this,            SLOT(on_down_button(bool)));
    connect(m_add_set_button, SIGNAL(clicked(bool)),
            this,            SLOT(on_add_set_button(bool)));
    connect(m_delete_set_button, SIGNAL(clicked(bool)),
            this,            SLOT(on_delete_set_button(bool)));
    connect(m_delete_all_button, SIGNAL(clicked(bool)),
            this,            SLOT(on_delete_all_button(bool)));
    connect(m_transform ,    SIGNAL(transform_changed()),
            this,            SLOT(on_transform_changed()));
    connect(m_transforms_tree, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)),
            this,            SLOT(on_cursor_changed(QTreeWidgetItem*, QTreeWidgetItem*)));
    connect(m_sequence_line, SIGNAL(editingFinished()),
            this,            SLOT(on_new_sequence_value()));
}


void TransformsTab::setFractalType(FRACTAL_TYPE ft)
{
    m_ignore_signals = true;
    m_config.SetFractalType(ft);
    unsigned int number_of_transforms = m_config.getNumberOfComplexPlaneTransforms();
    m_transforms_tree->clear();
    std::string transform;
    for (unsigned int i = 0; i < number_of_transforms; i++)
    {
        transform = m_config.getComplexPlaneTransform(i);
        m_transforms_tree->addTransform(0, transform);
    }
    unsigned int sets = m_config.getNumberOfTransformSets();
    for (unsigned int i = 0; i < sets; i++)
    {
        // Transform tree sets include the Complex Plane set
        // so formula sets start at 1.
        int set = i + 1;
        m_transforms_tree->addTransformSet(set);
        number_of_transforms = m_config.getNumberOfTransforms(i);
        for (unsigned int j = 0; j < number_of_transforms; j++)
        {
            transform = m_config.getTransform(i, j);
            m_transforms_tree->addTransform(set, transform);
        }
    }
    m_sequence = m_config.getTransformSequence();
    m_sequence_line->setText(QString::fromStdString(m_sequence));
    m_ignore_signals = false;
    display();
}

void TransformsTab::display()
{
    bool has_transforms = m_config.isBailoutFractal();
    bool has_cp_transforms = (has_transforms && !m_config.isOrbitPlotting());
    if (m_config.isSingleOrbit())
    {
        // Transforms are not available to Single Orbit fractals.
        has_transforms = false;
        has_cp_transforms = false;
    }
    bool at_root = m_transforms_tree->isAtRoot();
    bool at_start = m_transforms_tree->atStartOfBranch();
    auto set = m_transforms_tree->getTransformSet();
    int size = (set == 0)
               ? m_config.getNumberOfComplexPlaneTransforms()
               : m_config.getNumberOfTransforms(set - 1);
    bool at_end = m_transforms_tree->atEndOfBranch(size);
    m_sequence_line->setEnabled(has_transforms);
    m_add_button->setEnabled(set == 0 ? has_cp_transforms : has_transforms);
    m_add_set_button->setEnabled(has_transforms);
    m_up_button->setEnabled(has_transforms && !at_start && !at_root);
    m_down_button->setEnabled(has_transforms && !at_end && !at_root);
    m_delete_button->setEnabled(m_is_transform && has_transforms && !at_root);
    m_delete_set_button->setEnabled(has_transforms && at_root && (set != 0));
    
    size = m_config.getNumberOfComplexPlaneTransforms();
    int sets = m_config.getNumberOfTransformSets() + 1; //Transform sets start at 1
    for (int i = 1; i < sets; i++)
    {
        size += m_config.getNumberOfTransforms(i);
    }
    m_delete_all_button->setEnabled(has_transforms && (size > 0));
    m_transform->enableEditing(m_is_transform && has_transforms);
}

void TransformsTab::on_add_button(bool)
{
    m_ignore_signals = true;
    auto set = m_transforms_tree->getTransformSet();
    KeyString keys;
    keys.SetKey("pair", "n");
    keys.SetKey("id", intToString(static_cast<int>(CFP_NO_OP)));
    int number_of_transforms = 0;
    if (set == 0)
    {
        // Complex plane transform set
        m_config.addComplexPlaneTransform(keys.String());
        number_of_transforms = m_config.getNumberOfComplexPlaneTransforms();
    }
    else
    {
        m_config.addTransform(set - 1, keys.String());
        number_of_transforms = m_config.getNumberOfTransforms(set - 1);
    }
    m_transform->setTransform(keys.String());
    m_transforms_tree->addTransform(set, keys.String());
    m_transforms_tree->setCursor(set, number_of_transforms - 1);
    m_set = m_transforms_tree->getTransformSet();
    m_row = m_transforms_tree->cursorPosition();
    display();
    m_ignore_signals = false;
}

void TransformsTab::on_add_set_button(bool)
{
    m_ignore_signals = true;
    m_config.addTranformSet();
    auto set = m_config.getNumberOfTransformSets();
    m_transforms_tree->addTransformSet(set);
    m_transforms_tree->setCursor(set, 0);
    m_set = m_transforms_tree->getTransformSet();
    m_row = m_transforms_tree->cursorPosition();
    display();
    m_ignore_signals = false;
}

void TransformsTab::on_delete_button(bool)
{
    int pos = m_transforms_tree->cursorPosition();
    if (pos != -1)
    {
        auto set = m_transforms_tree->getTransformSet();
        if (set == 0)
        {
            m_config.deleteComplexPlaneTransform(pos);
        }
        else
        {
            m_config.deleteTransform(set - 1, pos);
        }
        m_transforms_tree->deleteTransform();
        m_transforms_tree->setCursor(-1, 0); // remove cursor
        m_transforms_tree->setCursor(set, pos);
        m_set = m_transforms_tree->getTransformSet();
        m_row = -1;
        display();
        emit transforms_changed();
    }
}

void TransformsTab::on_transform_changed()
{
    if (!m_ignore_signals)
    {
        int pos = m_transforms_tree->cursorPosition();
        if (pos >= 0)
        {
            auto t = m_transform->getTransform();
            auto set = m_transforms_tree->getTransformSet();
            if (set == 0)
            {
                m_config.setComplexPlaneTransform(pos, t);
            }
            else
            {
                m_config.setTransform(set - 1, pos, m_transform->getTransform());
            }
            m_transforms_tree->changeTransform(t);
            emit transforms_changed();
        }
    }
}

void TransformsTab::on_cursor_changed(QTreeWidgetItem*, QTreeWidgetItem*)
{
    m_is_transform = !m_transforms_tree->isAtRoot();
    if (!m_ignore_signals)
    {
        int set = 0;
        int pos = 0;
        m_transforms_tree->getCursor(set, pos);
        if (m_is_transform)
        {
            if (pos >= 0)
            {
                if (set == 0)
                {
                    m_transform->setTransform(m_config.getComplexPlaneTransform(pos));
                }
                else
                {
                    m_transform->setTransform(m_config.getTransform(set - 1, pos));
                }
            }
        }
        m_set = set;
        m_row = pos;
        display();
    }
}

void TransformsTab::on_new_sequence_value()
{
    if (!m_ignore_signals)
    {
        std::string old_sequence = m_config.getTransformSequence();
        std::string sequence = m_sequence_line->text().toUpper().toStdString();
        std::string new_sequence;
        int sets = m_config.getNumberOfTransformSets();
        char max_ch = ('A' + sets - 1);

        for (auto it = sequence.begin(); it != sequence.end(); it++ )
        {
            char ch = *it;
            if ((ch >= 'A') && (ch <= max_ch))
            {
                new_sequence += ch;
            }
        }
        m_config.setTransformSequence(new_sequence);
        m_sequence_line->setText(QString::fromStdString(new_sequence));
        if (old_sequence != new_sequence)
        {
            emit transforms_changed();
        }
    }
}

void TransformsTab::on_up_button(bool)
{
    int set;
    int pos;
    m_transforms_tree->getCursor(set, pos);
    if (pos > 0)
    {
        if (set == 0)
        {
            m_config.swapComplexPlaneTransforms(pos, pos - 1);
        }
        else
        {
            m_config.swapTransforms(set - 1, pos, pos - 1);
        }
        m_row = -1; // stop old parameter being updated
        m_transforms_tree->moveTransformUp();
        emit transforms_changed();
    }
}

void TransformsTab::on_down_button(bool)
{
    int set;
    int pos;
    m_transforms_tree->getCursor(set, pos);
    int size = (set == 0)
               ? m_config.getNumberOfComplexPlaneTransforms()
               : m_config.getNumberOfTransforms(set - 1);
    if ((pos > -1) && (pos < (size - 1)))
    {
        if (set == 0)
        {
            m_config.swapComplexPlaneTransforms(pos, pos + 1);
        }
        else
        {
            m_config.swapTransforms(set - 1, pos, pos + 1);
        }
        m_row = -1; // stop old parameter being updated
        m_transforms_tree->moveTransformDown();
        emit transforms_changed();
    }
}

void TransformsTab::on_delete_set_button(bool)
{
    int set;
    int pos;
    m_transforms_tree->getCursor(set, pos);
    m_config.deleteTransformSet(set - 1);
    m_transforms_tree->deleteBranch(set);
    //
    // The transform sequence needs to be updated, the transform set letter
    // should be removed and all the letters of the later sets should be
    // adjusted
    //
    char set_letter = 'A' + set - 1;
    std::string sequence = m_sequence_line->text().toStdString();;
    std::string new_sequence;
    for (auto it = sequence.begin(); it != sequence.end(); it++ )
    {
        char ch = *it;
        if (ch != set_letter)
        {
            if (ch > set_letter)
            {
                ch--;
            }
            new_sequence += ch;
        }
    }
    m_ignore_signals = true;
    m_sequence_line->setText(QString::fromStdString(new_sequence));
    m_ignore_signals = false;
    emit transforms_changed();
}

void TransformsTab::on_delete_all_button(bool)
{
    m_config.deleteTransforms();
    m_config.setTransformSequence("");
    m_sequence_line->setText("");
    m_transforms_tree->clear();
    emit transforms_changed();
}