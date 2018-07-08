#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QPainter>
#include <QtGlobal>
#include <QTime>
#include <QThread>
#include <QDebug>
#include <vector>
#include "car.h"
#include "light.h"

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void beginSlot();

private:
    void run();
    void judge(car &nowcar);
    void initWindow();
    void createButton();
    void paintEvent(QPaintEvent *);

    vector<car> cars[4];
    vector<light> lights;
    int tim = 0;
    int ytim = 0;

    QPushButton * beginBtn;
};

#endif // MAINWINDOW_H
