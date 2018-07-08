#include "car.h"
int car::speed = 10;
int car::carsize = 30;
/*
 * 0 从左到右
 * 1 从下到上
 * 2 从右到左
 * 3 从上到下
 */
car::car()
{

}
car::car(int x,int y,int direct,QColor color)
{
    this->x=x;
    this->y=y;
    this->direct=direct;
    this->color = color;
}

void car::run(bool change, int mode)
{
    if(change)
    {
        if(mode == 0)
            direct = (direct + 3) % 4;
        else if(mode == 1)
            direct = (direct + 1) % 4;
    }

    if(carRun)
    {
        switch(this->direct)
        {
        case 0:
            this->x += speed;
            break;
        case 1:
            this->y -= speed;
            break;
        case 2:
            this->x -= speed;
            break;
        case 3:
            this->y += speed;
            break;
        }
    }
}
