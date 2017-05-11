//
// File:   TransformTree.h
// Author: M.R.Eggleston
//
// Created on 30 June 2011, 13:38
//
// Converted to Qt April 2013

#pragma once

#include <QTreeWidget>
//#include "FractalsConfig.h"

class TransformTree  : public QTreeWidget
{
public:
    TransformTree(QWidget* parent = nullptr);
    virtual ~TransformTree();

    void clear();
    void addTransformSet(unsigned int set);
    void addTransform(unsigned int set, const std::string& function);
    void setTransform(unsigned int set, int pos, const std::string& function);
    void changeTransform(const std::string& function);
    void moveTransformDown();
    void moveTransformUp();
    void deleteTransform();
    void deleteBranch(int set);
    void setCursor(int set, int pos);
    void getCursor(int &set, int &pos);
    int cursorPosition();
    bool isAtRoot();
    bool canMove();
    bool atStartOfBranch();
    bool atEndOfBranch(int size);
    unsigned int getTransformSet();

private:
    
};
