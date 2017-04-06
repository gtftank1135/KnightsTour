#ifndef STACK_H
#define STACK_H


class Stack
{
    public:
        Stack();

        int getchecked();
        int geti();
        int getj();
        void setchecked(int schecked);
        void seti(int si);
        void setj(int sj);




    private:
        int i;
        int j;
        int checked;
};

#endif // STACK_H

