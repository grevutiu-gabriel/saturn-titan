//
// File:   TransformTree.cc
// Author: M.R.Eggleston
//
// Created on 30 June 2011, 13:38
//
// Converted to Qt April 2013

#include <iostream>
#include "TransformTree.h"
#include "Utilities.h"

TransformTree::TransformTree(QWidget* parent)
:
QTreeWidget(parent)
{
    setHeaderHidden(true);
}

TransformTree::~TransformTree()
{
}

void TransformTree::clear()
{
    QTreeWidget::clear();
    auto item = new QTreeWidgetItem();
    item->setText(0, "Complex Plane");
    addTopLevelItem(item);
}

void TransformTree::addTransformSet(unsigned int set)
{
    auto item = new QTreeWidgetItem();
    QString str = "Transforms ";
    str += QString(QChar(static_cast<char>(static_cast<int>('A') + set - 1)));
    item->setText(0, str);
    addTopLevelItem(item);
}

void TransformTree::addTransform(unsigned int set, const std::string& function)
{
    auto item = topLevelItem(set);
    auto child = new QTreeWidgetItem();
    child->setText(0, complexFunctionToString(function));
    item->addChild(child);
}

void TransformTree::setTransform(unsigned int set, int pos, const std::string& function)
{
    auto item = topLevelItem(set);
    auto child = item->child(pos);
    if (child != nullptr)
    {
        child->setText(0, complexFunctionToString(function));
    }
}

void TransformTree::changeTransform(const std::string& name)
{
    auto item = currentItem();
    if (item != nullptr)
    {
        item->setText(0, complexFunctionToString(name));
    }
}

void TransformTree::deleteTransform()
{
    auto item = currentItem();
    auto parent = item->parent();
    if (parent != nullptr)
    {
        int index = parent->indexOfChild(item);
        if (index != -1)
        {
            parent->takeChild(index);
        }
    }
}

void TransformTree::deleteBranch(int set)
{
    int rename_set = set;
    // Rename remaining sets
    rename_set++;
    QString base("Transforms ");
    auto item = topLevelItem(rename_set);
    while (item != nullptr)
    {
        char set_letter = 'A' + rename_set - 2; // Transform A is set 1
        QString str = base;
        str += QString(set_letter);
        item->setText(0, str);
        rename_set++;
        item = topLevelItem(rename_set);
    }
    auto set_item = topLevelItem(set);
    if (set_item != nullptr)
    {
        set_item->takeChildren();
        takeTopLevelItem(indexOfTopLevelItem(set_item));
    }
}

void TransformTree::setCursor(int set, int pos)
{
    auto item = topLevelItem(set);
    if (item != nullptr)
    {
        int number_of_children = item->childCount();
        if (pos >= number_of_children)
        {
            pos = number_of_children - 1;
        }
        auto child = item->child(pos);
        setCurrentItem(child != nullptr ? child : item);
    }
    else
    {
        setCurrentItem(nullptr);
    }
}

void TransformTree::getCursor(int &set, int &pos)
{
    pos = -1;
    set = 0;
    auto item = currentItem();
    if (item != nullptr)
    {
        auto parent = item->parent();
        if (parent != nullptr)
        {
            set = indexOfTopLevelItem(parent);
            pos = parent->indexOfChild(item);
        }
        else
        {
            set = indexOfTopLevelItem(item);
        }
    }
}


int TransformTree::cursorPosition()
{
    // Second level cursor position
    // Level one is the transform set, for each set there is a second level
    // listing the transforms for that set.
    int set = 0;
    int pos = -1;
    getCursor(set, pos);
    return pos;
}

bool TransformTree::isAtRoot()
{
    bool at_root = true;
    auto item = currentItem();
    if (item != nullptr)
    {
        at_root = (item->parent() == nullptr);
    }
    return at_root;
}

bool TransformTree::atStartOfBranch()
{
    bool at_start = false;
    auto item = currentItem();
    if (item != nullptr)
    {
        auto parent = item->parent();
        if (parent != nullptr)
        {
            at_start = (parent->indexOfChild(item) == 0);
        }
    }
    return at_start;
}

bool TransformTree::atEndOfBranch(int size)
{
    bool at_end = (size == 0);
    auto item = currentItem();
    if (item != nullptr)
    {
        auto parent = item->parent();
        if (parent != nullptr)
        {
            at_end = (parent->indexOfChild(item) >= (size - 1));
        }
    }
    return at_end;
}

unsigned int TransformTree::getTransformSet()
{
    int set = 0;
    int pos = -1;
    getCursor(set, pos);
    if (set == -1)
    {
        set = 0;
    }
    return static_cast<unsigned int>(set);
}

void TransformTree::moveTransformDown()
{
    auto item = currentItem();
    if (item != nullptr)
    {
        auto parent = item->parent();
        if (parent != nullptr)
        {
            int position = parent->indexOfChild(item);
            auto next_item = parent->child(position + 1);
            if (next_item != nullptr)
            {
                auto item_text = item->text(0);
                item->setText(0, next_item->text(0));
                next_item->setText(0, item_text);
                setCurrentItem(next_item);
            }
        }
    }
}

void TransformTree::moveTransformUp()
{
    auto item = currentItem();
    if (item != nullptr)
    {
        auto parent = item->parent();
        if (parent != nullptr)
        {
            int position = parent->indexOfChild(item);
            auto previous_item = parent->child(position - 1);
            if (previous_item != nullptr)
            {
                auto item_text = item->text(0);
                item->setText(0, previous_item->text(0));
                previous_item->setText(0, item_text);
                setCurrentItem(previous_item);
            }
        }
    }
}
