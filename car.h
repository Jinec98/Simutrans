#ifndef CAR_H
#define CAR_H
#include <QColor>

class car
{
public:
    int x,y;
    int direct;
    QColor color;
    static int speed;
    static int carsize;
    bool carRun = true;//是否停车
    bool isLive = true; //判断是否还活着
    car();
    car(int,int,int,QColor);
    void run(bool change,int mode);

};

#endif // CAR_H
