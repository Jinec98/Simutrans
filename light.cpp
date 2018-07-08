#include "light.h"

bool light::change = true; //换颜色
light::light()
{

}

light::light(int x,int y,int direct)
{
    this->x=x;
    this->y=y;
    this->direct=direct;
}
void light::toYellow()
{
    this->green = false;
    this->yellow = true;
    this->red = false;
}

void light::fromYellow()
{
    if(change)
    {
        if(this->direct % 2 == 0)
        {
            this->green = false;
            this->yellow = false;
            this->red = true;
        }
        else
        {
            this->green = true;
            this->yellow = false;
            this->red = false;
        }
    }
    else
    {
        if(this->direct % 2 == 0)
        {
            this->green = true;
            this->yellow = false;
            this->red = false;
        }
        else
        {
            this->green = false;
            this->yellow = false;
            this->red = true;
        }
    }
}
