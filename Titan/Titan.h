// 
// File:   Triton.h
// Author: M.R.Eggleston
//
// Created on 11 April 2014, 09:19
//

#pragma once

#include <iostream>
#include <QApplication>
#include <QMessageBox>


class Titan : public QApplication
{
    Q_OBJECT
public:
    Titan(int& argc, char** argv)
    :
    QApplication(argc, argv) {}
    ~Titan() {}
    
    bool notify(QObject* receiver, QEvent* event)
    {
        bool done = true;
        try
        {
            done = QApplication::notify(receiver, event);
        }
        catch (const std::bad_alloc&)
        {
            QMessageBox::warning(nullptr, "Titan Warning", "Can not enough allocate memory");
        }
        catch (const std::exception& ex)
        {
            QString error("Unexpected exception:\n\n");
            error += QString::fromStdString(ex.what());
            QMessageBox::critical(nullptr, "Titan Error", error);
        }
        catch (...)
        {
            QMessageBox::critical(nullptr, "Titan Error", "Unknown exception");
        }
        return done;
    }
};

