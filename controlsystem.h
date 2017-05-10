#ifndef CONTROLSYSTEM_H
#define CONTROLSYSTEM_H

#include "mobileplatform.h"
#include "mainwindow.h"

#include <QObject>

class ControlSystem : public QObject
{
    Q_OBJECT
public:
    explicit ControlSystem(MobilePlatform *mobilePlatform, MainWindow *mainWindow,QObject *parent = 0);

private:
    MobilePlatform *m_mobilePlatform;
    MainWindow *m_mainWindow;

    void setupConnection();

signals:

public slots:

};

#endif // CONTROLSYSTEM_H
