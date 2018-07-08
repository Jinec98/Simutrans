#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowIcon(QIcon(":/traffic.png"));
    initWindow();
    createButton();
    setFixedSize(700,700);
    this->setWindowOpacity(0.9); //窗口整体透明度，0-1 从全透明到不透明
}

MainWindow::~MainWindow()
{

}

void MainWindow::initWindow()
{
    lights.push_back(light(400, 400, 0));
    lights.push_back(light(400, 280, 1));
    lights.push_back(light(280, 240, 2));
    lights.push_back(light(240, 400, 3));
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black,4));//设置画笔形式
    painter.drawLine(0, 300, 700, 300);
    painter.drawLine(0, 400, 700, 400);
    painter.drawLine(300, 0, 300, 700);
    painter.drawLine(400, 0, 400, 700);


    painter.setPen(QPen(Qt::gray,1));
    painter.drawLine(0, 350, 700, 350);//横
    painter.drawLine(350, 0, 350, 700);//竖

    for(unsigned int i=0; i<lights.size(); i++)  //画灯
    {
        painter.setBrush(QColor(Qt::black));
        if(lights[i].direct % 2 == 0)
            painter.drawRect(lights[i].x, lights[i].y, 20, 60);
        else
            painter.drawRect(lights[i].x, lights[i].y, 60, 20);

        painter.setBrush(QColor(Qt::red));
        if(lights[i].red)
        {
            if(lights[i].direct == 0 || lights[i].direct == 1)
                painter.drawEllipse(lights[i].x, lights[i].y, 20, 20);
            else if(lights[i].direct == 2)
                painter.drawEllipse(lights[i].x, lights[i].y+40, 20, 20);
            else
                painter.drawEllipse(lights[i].x+40, lights[i].y, 20, 20);
        }
        painter.setBrush(QColor(Qt::yellow));
        if(lights[i].yellow)
        {
            if(lights[i].direct % 2 == 0)
                painter.drawEllipse(lights[i].x, lights[i].y+20, 20, 20);
            else
                painter.drawEllipse(lights[i].x+20, lights[i].y, 20, 20);
        }
        painter.setBrush(QColor(Qt::green));
        if(lights[i].green)
        {
            if(lights[i].direct == 2 || lights[i].direct == 3)
                painter.drawEllipse(lights[i].x, lights[i].y, 20, 20);
            else if(lights[i].direct == 0)
                painter.drawEllipse(lights[i].x, lights[i].y+40, 20, 20);
            else
                painter.drawEllipse(lights[i].x+40, lights[i].y, 20, 20);
        }
    }
    for(int i=0; i<4; i++) //画车
    {
        for(unsigned int j=0; j<cars[i].size(); j++)
        {
            painter.setBrush(cars[i][j].color);
            painter.drawRect(cars[i][j].x, cars[i][j].y, car::carsize, car::carsize);
        }
    }
}

void MainWindow::createButton()
{
    beginBtn = new QPushButton(QIcon(":/begin.png"),tr("开始"),this);
    beginBtn->setGeometry(20,20,60,30);
    connect(beginBtn,&QPushButton::clicked,this,&MainWindow::beginSlot);
}


void MainWindow::beginSlot()
{
    while(true)
    {
        run();
        QThread::msleep(50);
        tim++;
        ytim++;
        repaint();
    }
}

void MainWindow::run()
{
    if(tim % 100 == 0)
    {
        for(unsigned int i=0; i<lights.size(); i++)
        {
            lights[i].toYellow();
        }
        light::change = !light::change;
        tim = 0;
        ytim = 0;
    }
    if(ytim == 10)
    {
        for(unsigned int i=0; i<lights.size(); i++)
        {
            lights[i].fromYellow();
        }
    }

    if(tim % 10 == 0)
    {
        int kind = qrand() % 4;
        if(kind == 0)
            cars[0].push_back(car(0, 360, 0, QColor(Qt::cyan)));
        else if(kind == 1)
            cars[1].push_back(car(360, 700, 1, QColor(Qt::yellow)));
        else if(kind == 2)
            cars[2].push_back(car(700, 310, 2, QColor(Qt::blue)));
        else if(kind == 3)
            cars[3].push_back(car(310, 0, 3, QColor(Qt::magenta)));
    }
    for(int i=0; i<4; i++)
    {
        for(unsigned int j=0; j<cars[i].size(); j++)
        {
            judge(cars[i][j]);
            int mode = 0;
            int dir = i;
            bool can_change = false;
            bool change = false;
            car nowcar;
            mode = qrand() % 2;
            if(mode == 0)
            {
                switch(dir)
                {
                case 0:
                    if(cars[i][j].x == 310 && cars[i][j].y == 360)
                        can_change = true;
                    break;
                case 1:
                    if(cars[i][j].x == 360 && cars[i][j].y == 360)
                        can_change = true;
                    break;
                case 2:
                    if(cars[i][j].x == 360 && cars[i][j].y == 310)
                        can_change = true;
                    break;
                case 3:
                    if(cars[i][j].x == 310 && cars[i][j].y == 310)
                        can_change = true;
                    break;
                }

                if(can_change)
                {
                    int kind = qrand() % 2;
                    if(kind == 0)
                        change = true;
                }
                cars[i][j].run(change, mode);
                if(change)
                {
                    nowcar = car(cars[i][j].x, cars[i][j].y, cars[i][j].direct, cars[i][j].color);
                    cars[i].erase(cars[i].begin()+j,cars[i].begin()+j+1);
                    cars[nowcar.direct].push_back(nowcar);
                }
            }
            else if(mode == 1)
            {
                switch(dir)
                {
                case 0:
                    if(cars[i][j].x == 360 && cars[i][j].y == 360)
                        can_change = true;
                    break;
                case 1:
                    if(cars[i][j].x == 360 && cars[i][j].y == 310)
                        can_change = true;
                    break;
                case 2:
                    if(cars[i][j].x == 310 && cars[i][j].y == 310)
                        can_change = true;
                    break;
                case 3:
                    if(cars[i][j].x == 310 && cars[i][j].y == 360)
                        can_change = true;
                    break;
                }

                if(can_change)
                {
                    int kind = qrand() % 2;
                    if(kind == 0)
                        change = true;
                }
                cars[i][j].run(change, mode);
                if(change)
                {
                    nowcar = car(cars[i][j].x, cars[i][j].y, cars[i][j].direct, cars[i][j].color);
                    cars[i].erase(cars[i].begin()+j,cars[i].begin()+j+1);
                    cars[nowcar.direct].push_back(nowcar);
                }
            }
            if(change)
                judge(cars[nowcar.direct][cars[nowcar.direct].size()-1]);
        }

    }
}

void MainWindow::judge(car &nowcar)
{
    int dir = nowcar.direct;
    switch(dir)
    {
    case 0:
        if(nowcar.x + car::carsize == 300 && (lights[0].red || lights[0].yellow))
            nowcar.carRun = false;
        for(unsigned int i=0; i<cars[0].size(); i++)
        {
            if(nowcar.x + car::carsize == cars[0][i].x-10 && cars[0][i].y == 360)
                nowcar.carRun = false;
        }
        if(nowcar.x > 700 || nowcar.y > 700)
            nowcar.isLive = false;
        break;
    case 1:
        if(nowcar.y == 400 && (lights[1].red || lights[1].yellow))
            nowcar.carRun = false;
        for(unsigned int i=0; i<cars[1].size(); i++)
        {
            if(nowcar.y - car::carsize == cars[1][i].y+10 && cars[1][i].x == 360)
                nowcar.carRun = false;
        }
        if(nowcar.y < 0 || nowcar.x > 700)
            nowcar.isLive = false;
        break;
    case 2:
        if(nowcar.x == 400 && (lights[2].red || lights[2].yellow))
            nowcar.carRun = false;
        for(unsigned int i=0; i<cars[2].size(); i++)
        {
            if(nowcar.x - car::carsize == cars[2][i].x+10 && cars[2][i].y == 310 )
                nowcar.carRun = false;
        }
        if(nowcar.x < 0 || nowcar.y < 0)
            nowcar.isLive = false;
        break;
    case 3:
        if(nowcar.y + car::carsize == 300 && (lights[3].red || lights[3].yellow))
            nowcar.carRun = false;
        for(unsigned int i=0; i<cars[3].size(); i++)
        {
            if(nowcar.y + car::carsize == cars[3][i].y-10 && cars[3][i].x == 310)
                nowcar.carRun = false;
        }
        if(nowcar.y > 700 || nowcar.x < 0)
            nowcar.isLive = false;
        break;
    }
    switch(dir)
    {
    case 0:
        if((nowcar.carRun == false && lights[0].green) || nowcar.x > 310)
            nowcar.carRun = true;
        for(unsigned int i=0; i<cars[0].size(); i++)
        {
            if(nowcar.x + car::carsize == cars[0][i].x && cars[0][i].y == 360)
                nowcar.carRun = false;
        }
        break;
    case 1:
        if((nowcar.carRun == false && lights[1].green) || nowcar.y < 360)
            nowcar.carRun = true;
        for(unsigned int i=0; i<cars[1].size(); i++)
        {
            if(nowcar.y - car::carsize == cars[1][i].y && cars[1][i].x == 360)
                nowcar.carRun = false;
        }
        break;
    case 2:
        if((nowcar.carRun == false && lights[2].green) || nowcar.x < 360)
            nowcar.carRun = true;
        for(unsigned int i=0; i<cars[2].size(); i++)
        {
            if(nowcar.x - car::carsize == cars[2][i].x && cars[2][i].y == 310 )
                nowcar.carRun = false;
        }
        break;
    case 3:
        if((nowcar.carRun == false && lights[3].green) || nowcar.y > 310)
            nowcar.carRun = true;
        for(unsigned int i=0; i<cars[3].size(); i++)
        {
            if(nowcar.y + car::carsize == cars[3][i].y && cars[3][i].x == 310)
                nowcar.carRun = false;
        }
        break;
    }
}

