#ifndef SCREEN_H
#define SCREEN_H

class Screen
{
public:
    Screen(){};
    virtual void kresli()=0;
    virtual void  klik(int MysX,int MysY)=0;
};

#endif // SCREEN_H
