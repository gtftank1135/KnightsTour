#include "Stack.h"

Stack::Stack()
{
    //ctor
    checked = 0;
}

int Stack::geti()
{
    return i;
}
void Stack::seti(int si)
{
    i = si;
}
int Stack::getj()
{
    return j;
}
void Stack::setj(int sj)
{
    j = sj;
}
int Stack::getchecked()
{
    return checked;
}
void Stack::setchecked(int schecked)
{
    checked = schecked;
}

