// 
// File:   Saturn.h
// Author: M.R.Eggleston
//
// Created on 18 March 2013, 14:34
//

#pragma once

#include <QApplication>
#include <QMessageBox>
#include "Config.h"

class Saturn : public QApplication
{
    Q_OBJECT
public:
    Saturn(int & argc, char ** argv)
    :
    QApplication(argc, argv)
    {
        connect(this, SIGNAL(aboutToQuit()), this, SLOT(on_quit()));
    }
    ~Saturn(){}

    bool notify(QObject* receiver, QEvent* event)
    {
        bool done = true;
        try
        {
            done = QApplication::notify(receiver, event);
        }
        catch (const std::bad_alloc&)
        {
            QMessageBox::warning(nullptr, "Saturn Warning", "Can not enough allocate memory");
        }
        catch (const std::exception& ex)
        {
            QString error("Unexpected exception:\n\n");
            error += QString::fromStdString(ex.what());
            QMessageBox::critical(nullptr, "Saturn Error", error);
        }
        catch (...)
        {
            QMessageBox::critical(nullptr, "Saturn Error", "Unknown exception");
        }
        return done;
    }

public slots:
    void on_quit() { Config::instance()->save(); }
};


