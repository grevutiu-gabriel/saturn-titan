//
// File:   TransformsTab.h
// Author: M.R.Eggleston
//
// Created on 30 June 2011, 13:04
//

#pragma once

#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QTreeWidget>
#include "TransformDefinition.h"
#include "TransformTree.h"
//#include "FractalList.h"

class TransformsTab : public QWidget
{
    Q_OBJECT
signals:
    void transforms_changed();
    
private slots:
    void on_add_button(bool clicked);
    void on_delete_button(bool clicked);
    void on_up_button(bool clicked);
    void on_down_button(bool clicked);
    void on_add_set_button(bool clicked);
    void on_delete_set_button(bool clicked);
    void on_delete_all_button(bool clicked);
    void on_transform_changed();
    void on_cursor_changed(QTreeWidgetItem* current, QTreeWidgetItem* previous);
    void on_new_sequence_value();

public:
    TransformsTab(QWidget* parent = nullptr);
    virtual ~TransformsTab();

    void setFractalType(FRACTAL_TYPE ft);
    void display();

private:
    TransformsTab(const TransformsTab& orig);

    void setup_ui_layout();
    void connect_signals();

    QPushButton* m_add_button;
    QPushButton* m_delete_button;
    QPushButton* m_down_button;
    QPushButton* m_up_button;
    QPushButton* m_add_set_button;
    QPushButton* m_delete_set_button;
    QPushButton* m_delete_all_button;
    QLineEdit* m_sequence_line;
    TransformDefinition* m_transform;
    TransformTree* m_transforms_tree;

    std::string m_sequence;
    FractalsConfig m_config;
    bool m_ignore_signals;
    bool m_is_transform;
    int m_set;
    int m_row;
};
