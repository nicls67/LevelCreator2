/*
 *Creation de niveau pour Sobokan
 *
 *v2.0
 *
 *14/05/2013
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QRadioButton>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <fstream>

#include "../../../SobokanV2/SobokanV2/common.h"

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void createMap();

private:
    int type_obj(QRadioButton *b[4]);

    QWidget *zoneCentrale;
    //QGroupBox *groupbox[H][W];
    //QVBoxLayout *vbox[H][W];
    //QRadioButton *radioButton[H][W][4];

    QGroupBox ***groupbox;
    QVBoxLayout ***vbox;
    QRadioButton ***radioButton[4];

    QSpinBox *spinBoxY;
    QSpinBox *spinBoxX;
    int w;
    int h;
};

#endif // MAINWINDOW_H
