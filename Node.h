#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

class Node
{
    public:
        Node();
        Node(int ipos, int jpos);
        Node* getnextnode();
        Node* gettempnode();
        int geti();
        int getj();
        void seti(int itemp);
        void setj(int jtemp);
        void setnextnode(Node* tempnextnode);
        void settempnode(Node* temptempnode);
        void destroy();
        void add();
        void insertnew(int inew, int jnew);

    private:
        Node* next;
        Node* temp;
        int i;
        int j;

};

#endif // NODE_H_INCLUDED

