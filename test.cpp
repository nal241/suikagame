#include <stdio.h>


class Itest{
    public:
    Itest() = default;
    virtual ~Itest() = default;
    virtual void print() = 0;
};

class Atest{
protected:
    Itest* implItest;
public:
    Atest(Itest* impl):implItest(impl)
    {};
    virtual ~Atest() = default;
    void (*displayFunc)(void) ;
    void (*idleFunc)(void);
};

class tA:public Atest
{
public:
    tA(Itest* impl);
    virtual ~tA() = default;
    void ttt();
};

tA::tA(Itest* impl):Atest(impl){}

void tA::ttt(){
    implItest->print();
}

int main(){
    tA T;
    T.ttt();
}