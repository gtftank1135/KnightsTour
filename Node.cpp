#include "Node.h"
 using namespace std;

 Node::Node(){
 }

 Node::Node(int itemp, int jtemp)
 {
     i = itemp;
     j = jtemp;


 }

 void Node::destroy()
 {
     settempnode(next);
     setnextnode(next->getnextnode());
     delete temp;

 }

 void Node::insertnew(int inew, int jnew)
 {
     temp = next;
     setnextnode(new Node(inew, jnew));
     next->setnextnode(temp);
 }
 int Node::geti()
 {
     return i;
 }

 int Node::getj()
 {
     return j;
 }

 void Node::seti(int itemp)
 {

     i = itemp;
 }

 void Node::setj(int jtemp)
 {

     j = jtemp;
 }

 Node* Node::getnextnode()
 {
     return next;
 }

 Node* Node::gettempnode()
 {

     return temp;
 }

 void Node::setnextnode(Node* tempnextnode)
 {

     next = tempnextnode;
 }

 void Node::settempnode(Node* temptempnode)
 {

     temp = temptempnode;
 }


