#ifndef LIGHT_H
#define LIGHT_H

class light
{
public:
    int x, y;
    int direct;
    bool red = true, yellow = false, green = false;
    static bool change; //换颜色
    light();
    light(int, int, int);
    void toYellow();
    void fromYellow();
};

#endif // LIGHT_H
