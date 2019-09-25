#include <iostream>
#define METHOD_PROLOGUE(theClass, localClass) \
    theClass* pThis = ((theClass*)((char*)(this) - \
    offsetof(theClass, m_x##localClass))); \

using namespace std;

class Outer
{
public:
    Outer(){m_outerInt=0;}
private:
    int m_outerInt;
public:
    //内部类定义开始
    class Inner
    {
    public:
        Inner(){m_innerInt=1;}
    private:
        int m_innerInt;
    public:
        void DisplayIn(){cout<<m_innerInt<<endl;}
        // 在此函数中访问外部类实例数据
        void setOut()
        {
            METHOD_PROLOGUE(Outer,Inner);
            pThis->m_outerInt=10;
        }
    } m_xInner;
    //End内部类
public:
    void DisplayOut(){cout<<m_outerInt<<endl;}
};

int main()
{
    Outer out;
    out.DisplayOut();
    out.m_xInner.setOut();
    out.DisplayOut();
    return 0;
}
