//These include statements are for my headers
#include "Node.h"
#include "Stack.h"

//The following allow me to include output files as well as perform input output.
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

//Global variables
stringstream ss;
bool keepgoing = true;

//This variable will keep track of where I am at in my array of stacks.
int counter = 0;

//This array will hold instances of my stack class
Stack* des = new Stack[64];

//This 2d array will hold the values of the positions I visit and keep track of
//What has not been visited
int posholder [8][8];

//These three global variables are pointers to Nodes that will allow me to move
//Through the linked list.
Node* headnode = new Node();
Node* currentnode = headnode;
Node* tempernode = headnode;
//This keeps track of the total ammount of nodes.
int totalnodes = 1;
//Allows me to output
ofstream Outfile;

//Debugging purposes
int tester;
int stacktester;

//Start function is the main UI of the program.
void Start()
{
    int position;

    //I had to run this for loop because my initilization of the stacks in my array
    //Did not set the checked values.
    for(int a = 0; a < 64; a++)
    {
        des[a].setchecked(0);
    }
    //These function variables will be useful for keeping track of node values.
    bool keepgoing2 = true;
    int ival;
    int jval;
    int answer1;
    //This is for initial adding phase
    while(keepgoing2 == true)
    {
        cout << "Enter starting row";
        cin >> ival;
        cout << "Enter starting col";
        cin >> jval;
        //Sets i and j values in the node to the users input.
        currentnode->seti(ival);
        currentnode->setj(jval);
        //Loops to keep adding
        cout << "Would you like to add another? 1.yes or 2.no.";
        cin >> answer1;
        if(answer1 == 2)
        {
            keepgoing2 = false;
        }
        else
        {
            //Incriments total nodes and makes a new node.
            totalnodes++;
            currentnode->setnextnode(new Node());
            currentnode = currentnode->getnextnode();
        }
    }
    //Have to reset node
    currentnode = headnode;
    bool keepgoinga = true;
    //This loop if for changes in the user input.
    while(keepgoinga == true)
    {
        currentnode = headnode;
        //Outputs all the existing positions
        for(int b = 0; b < totalnodes; b++)
        {
	    if(b == totalnodes -1)
	    {
            cout << "(";
            cout << currentnode->geti();
            cout << ",";
            cout << currentnode->getj();
            cout << ")";
            cout << " ";
	    }

	    else
	    {
	    cout << "(";
	    cout << currentnode->geti();
	    cout << ",";
	    cout << currentnode->getj();
	    cout << ")";
	    cout << " ";
            currentnode = currentnode->getnextnode();
        }
        }
        currentnode = headnode;
        cout << "Would you like to 1.) insert 2.) add 3.) delete or 4.) start program ";
        cin >> answer1;
        //For inserting
        if(answer1 == 1)
        {
            cout << "Where would you like to insert";
            cin >> position;
            if (position <= totalnodes)
            {
                //Goes to proper node
                for(int c = 1; c < position; c++)
                {
                    currentnode = currentnode->getnextnode();
                }
                totalnodes++;
                cout << "new row:";
                cin >> ival;
                cout << "new col:";
                cin >> jval;
                currentnode->insertnew(ival,jval);//Calls insert function of Node.
            }
        }
        //For Adding
        if(answer1 == 2)
        {
            //Goes to last node
            for(int d = 1; d < totalnodes; d++)
            {
                currentnode = currentnode->getnextnode();
            }
            totalnodes++;
            cout << "row:";
            cin >> ival;
            cout << "col";
            cin >> jval;
            //Just makes  a new node at end of list with user input values.
            currentnode->setnextnode(new Node(ival, jval));
        }
        //For deletion
        if(answer1 == 3)
        {
            cout << "Where would you like to delete";
            cin >> position;
            totalnodes = totalnodes -1;
            //Goes to proper node.
            for(int e = 1; e < position-1; e++)
            {
                currentnode = currentnode->getnextnode();
            }
            //Calls the destroy function of the node.
            currentnode->destroy();
        }
        //This answer will start the program.
        if(answer1 == 4)
        {

            keepgoinga = false;

        }

    }
}
//This Function Checks to see if a space is movable by returning either a 1 or 0.
//Only checks if the range is off the board. Not if value is already taken.
int movable(int movi,int movj)
{
    int rval = 0;
    if(movi >= 8)
    {
        rval = 1;
    }
    else if(movj >= 8)
    {
        rval = 1;
    }
    else if(movi < 0)
    {
        rval = 1;
    }
    else if(movj < 0)
    {
        rval = 1;
    }
    return rval;
}
int movable2(int mov2i, int mov2j)
{
    int rval2;
    if(posholder[mov2i][mov2j] != -1)
    {
        rval2 = 1;
    }
    return rval2;
}
//This is my backtracking method.
void Stacktry()
{


    bool keepgoing4 = true;
    //This will make all the moves unlike the huristic algorithm.
    while(keepgoing4 == true)
    {


        //These two values help reduce code clutter
        int tempi = des[counter].geti();
        int tempj = des[counter].getj();
        //For testing positions
        int testing = 0;
        //Each Stack has a checked variable that hold the "positions" that have been checked.
        if(des[counter].getchecked() == 0)
        {
            //This incraments the checked variable to say don't check this value again.
            des[counter].setchecked(1);
            //Tests if position can be moved to.
            testing = movable(tempi + 2, tempj + 1);
            if(testing == 0)
            //if(((tempj +1 >= 0 && tempj + 1 < 8 )&& (tempi + 2 >= 0 && tempi + 2 < 8)) && (posholder[tempi+2][tempj+1] == -1));
            {
                //Checks to see if position was already landed on.
                if(posholder[tempi +2][tempj +1] == -1)
                {


                    counter++;
                    des[counter].seti(tempi + 2);
                    des[counter].setj(tempj + 1);
                    des[counter].setchecked(0);
                    posholder[tempi + 2][tempj + 1] = counter;
                }
            }
        }
        //This process is repeated for every position that they could move.
        else if(des[counter].getchecked() == 1)
        {
            des[counter].setchecked(2);
            testing = movable(tempi +2, tempj-1);
            if(testing == 0)
            //if(tempj -1 >= 0 && tempj - 1 < 8 && tempi + 2 >= 0 && tempi + 2 < 8 && posholder[tempi+2][tempj-1] == -1);
            {
                if(posholder[tempi +2][tempj -1]==-1)
                {


                    counter++;
                    des[counter].seti(tempi + 2);
                    des[counter].setj(tempj - 1);
                    des[counter].setchecked(0);
                    posholder[tempi + 2][tempj - 1] = counter;
                }
            }
        }
        else if(des[counter].getchecked() == 2)
        {
            des[counter].setchecked(3);
            testing = movable(tempi -2, tempj -1);
            //if(tempj-1 >= 0 && tempj-1 < 8 && tempi-2 >= 0 && tempi-2 < 8 && posholder[tempi-2][tempj-1] == -1);
            if(testing == 0)
            {

                if(posholder[tempi-2][tempj-1]== -1)
                {


                    counter++;
                    des[counter].seti(tempi - 2);
                    des[counter].setj(tempj - 1);
                    des[counter].setchecked(0);
                    posholder[tempi - 2][tempj - 1] = counter;
                }
            }
        }

        else if(des[counter].getchecked() == 3)
        {
            des[counter].setchecked(4);
            testing = movable(tempi -2, tempj+1);
            if(testing == 0)
            //if(tempj+1 >= 0 && tempj+1 < 8 && tempi-2 >= 0 && tempi-2 < 8 && posholder[tempi-2][tempj+1] == -1);
            {
                if(posholder[tempi -2][tempj +1]== -1)
                {

                    counter++;
                    des[counter].seti(tempi - 2);
                    des[counter].setj(tempj + 1);
                    des[counter].setchecked(0);
                    posholder[tempi - 2][tempj + 1] = counter;
                }
            }
        }

        else if(des[counter].getchecked() == 4)
        {
            des[counter].setchecked(5);
            testing = movable(tempi-1, tempj+2);
            if(testing == 0)
            //if(tempj+2 >= 0 && tempj+2 < 8 && tempi-1 >= 0 && tempi-1 < 8 && posholder[tempi-1][tempj+2] == -1);
            {
                if(posholder[tempi-1][tempj+2]==-1)
                {
                counter++;
                des[counter].seti(tempi - 1);
                des[counter].setj(tempj + 2);
                des[counter].setchecked(0);
                posholder[tempi - 1][tempj + 2] = counter;
                }
            }
        }

         else if(des[counter].getchecked() == 5)
        {
            des[counter].setchecked(6);
            testing = movable(tempi+1, tempj+2);
            if(testing == -1)
            //if(tempj+2 >= 0 && tempj+2 < 8 && tempi+1 >= 0 && tempi+1 < 8 && posholder[tempi+1][tempj+2] == -1);
            {
                if(posholder[tempi+1][tempj +2]==-1)
                {

                    counter++;
                    des[counter].seti(tempi + 1);
                    des[counter].setj(tempj + 2);
                    des[counter].setchecked(0);
                    posholder[tempi + 1][tempj + 2] = counter;
                }
            }
        }

        else if(des[counter].getchecked() == 6)
        {
            testing = movable(tempi+1, tempj -2);
            des[counter].setchecked(7);
            if(testing == 0)
            //if(tempj-2 >= 0 && tempj-2 < 8 && tempi+1 >= 0 && tempi+1 < 8 && posholder[tempi+1][tempj-2] == -1);
            {
                if(posholder[tempi+1][tempj-2]==-1)
                {
                counter++;
                des[counter].seti(tempi + 1);
                des[counter].setj(tempj - 2);
                des[counter].setchecked(0);
                posholder[tempi + 1][tempj - 2] = counter;
                }
            }
        }
        else if(des[counter].getchecked() == 7)
        {
            des[counter].setchecked(8);
            testing = movable(tempi-1,tempj-2);
            //if(tempj-2 >= 0 && tempj-2 < 8 && tempi-1 >= 0 && tempi-1 < 8 && posholder[tempi-1][tempj-2] == -1);
            {
                if(posholder[tempi-1][tempj-2]==-1)
                {
                counter++;
                des[counter].seti(tempi - 1);
                des[counter].setj(tempj - 2);
                des[counter].setchecked(0);
                posholder[tempi - 1][tempj - 2] = counter;
                }
            }
        }
        //Finally if a position can't move the array call is pushed back so we're dealing
        //With the previous stack or "popping".
        else if(des[counter].getchecked()== 8)
        {
            posholder[tempi][tempj] = -1;
            counter = counter -1;
        }
        //This will test if the counter reaches 63 so the program knows it's done
        if(counter == 63)
        {
            keepgoing4 = false;
        }


  }

}
//Print function is called for every node and the outfile is open and closed in main.
void Print()
{
    //Outfile.open("output.txt");

    string stringprint;
    //Outputs the current node values
    Outfile << "(";
    Outfile << currentnode->geti();
    Outfile << ",";
    Outfile << currentnode->getj();
    Outfile << ")";
    Outfile << endl;
    //nested for loop to get through all values in 2d array
    for(int f = 0; f < 8; f++)
    {


        Outfile << endl;
        Outfile << "______________________________";
        Outfile << endl;


        for(int g = 0; g < 8; g++)
        {
        //I used string stream although I don't think it's required.
            Outfile << "|";
	    ss << posholder[f][g];
	    ss >> stringprint;

	   // cout <<"outfiel correct";
	   // cin >> tester;
	   // Outfile << "1";
	   // cout << "outfi

	   // cin >> tester;

            Outfile << stringprint;
	    ss.clear();
	    ss.str("");

            Outfile << "|";
        }
    }
    Outfile << endl;

    Outfile << "______________________________";
    Outfile << endl;
    Outfile << endl;
    Outfile << endl;


    //Outfile.close();
}




//This function clears the classes off the heap.
void Clear()
{
    currentnode = headnode;
    //Deletes all the instances of stack
    delete[]des;

    //Deletes every node.
    for(int i = 0; i<totalnodes; i++)
    {
	if(i == totalnodes -1)
	{
		delete currentnode;
	}
	else
	{

        	tempernode = currentnode;
        	currentnode = currentnode->getnextnode();
        	delete tempernode;
	}
    }

}
//This function tests all possible moves form a given position and return how many it can move to
//This is useful in the hurristic algorithm.
int totalmoves(int tmovesi, int tmovesj)
{
    int maxmoves = 0;
    int totaltest;
    //Checks if movable
    totaltest = movable(tmovesi+2, tmovesj+1);
    //if((tmovesi + 2 < 8) && (tmovesi + 2 >= 0) && (tmovesj + 1 < 8) && (tmovesj + 1 >=  0) && posholder[tmovesi + 2][tmovesj +1] == -1)
    if(totaltest == 0)
    {
        //Checks if moved to.
        if(posholder[tmovesi+2][tmovesj+1]==-1)
        {

            //Incraments total moves.
            maxmoves++;
        }
    }
    totaltest = movable(tmovesi+2, tmovesj-1);
    //if(tmovesi + 2 < 8 && tmovesi + 2 >= 0 && tmovesj - 1 < 8 && tmovesj - 1 >= 0 && posholder[tmovesi + 2][tmovesj -1] == -1)
    if(totaltest == 0)
    {
        if(posholder[tmovesi +2][tmovesj -1]== -1)
        {


        maxmoves++;
        }
    }
    totaltest = movable(tmovesi -2, tmovesj+1);
    //if(tmovesi - 2 < 8 && tmovesi - 2 >= 0 && tmovesj + 1 < 8 && tmovesj + 1 >= 0 && posholder[tmovesi - 2][tmovesj +1] == -1)
    if(totaltest == 0)
    {
        if(posholder[tmovesi -2][tmovesj+1]==-1)
        {


        maxmoves++;
        }
    }
    totaltest = movable(tmovesi -2, tmovesj - 1);
    if(totaltest == 0)
    //if(tmovesi - 2 < 8 && tmovesi - 2 >= 0 && tmovesj - 1 < 8 && tmovesj - 1 >= 0 && posholder[tmovesi - 2][tmovesj -1] == -1)
    {
        if(posholder[tmovesi-2][tmovesj-1]==-1)
        {

        maxmoves++;
        }
    }
    totaltest = movable(tmovesi +1, tmovesj + 2);
    if(totaltest == 0)
    //if(tmovesi + 1 < 8 && tmovesi + 1 >= 0 && tmovesj + 2 < 8 && tmovesj + 2 >= 0 && posholder[tmovesi + 1][tmovesj +2] == -1)
    {
        if(posholder[tmovesi + 1][tmovesj +2]==-1)
        {
        maxmoves++;
        }
    }
    totaltest = movable(tmovesi -1, tmovesj + 2);
    //if(tmovesi - 1 < 8 && tmovesi - 1 >= 0 && tmovesj + 2 < 8 && tmovesj + 2 >= 0 && posholder[tmovesi - 1][tmovesj +2] == -1)
    if(totaltest == 0)
    {
        if(posholder[tmovesi -1][tmovesj +2]==-1)
        {


        maxmoves++;
        }
    }
     totaltest = movable(tmovesi +1, tmovesj -2);
     if(totaltest == 0)
     //if(tmovesi + 1 < 8 && tmovesi + 1 >= 0 && tmovesj - 2 < 8 && tmovesj - 2 >=0 && posholder[tmovesi + 1][tmovesj -2] == -1)
    {
        if(posholder[tmovesi +1][tmovesi -2]==-1)
        {

        maxmoves++;
        }
    }
    totaltest = movable(tmovesi -1, tmovesj -2);
    if(totaltest == 0)
    //if(tmovesi - 1 < 8 && tmovesi - 1 >= 0 && tmovesj - 2 < 8 && tmovesj - 2 >= 0 && posholder[tmovesi - 1][tmovesj -2] == -1)
    {
        if(posholder[tmovesi-1][tmovesj-2]==-1)
        {
        maxmoves++;
        }
    }
    return maxmoves;
}
//This is the huristic algorithm.
void Hur(int huri, int hurj)
{
    int total;
    int movementi= 0;
    int movementj = 0;
    int minmoves = 8;
    int hurtest = 0;
    //Check if move is valid
    hurtest = movable(huri +2, hurj +1);
    if(hurtest == 0)
    //if(huri + 2 < 8 && huri + 2 >= 0 && hurj + 1 < 8 && hurj + 1 >= 0)
    {
        //Checks if it has been taken
        if(posholder[huri + 2][hurj +1] == -1)
        {
            //Finds the total moves it has from there.
        	total = totalmoves(huri + 2, hurj + 1);

        	//If it the new lowest set it to that
        	if(total <= minmoves)
        	{
            		minmoves = total;
            		movementi = huri + 2;
            		movementj = hurj + 1;
        	}
       }
    }
    hurtest = movable(huri +2, hurj-1);
    if(hurtest == 0)
    //if(huri + 2 < 8 && huri + 2 >= 0 && hurj - 1 < 8 && hurj - 1 >= 0 && posholder[huri + 2][hurj -1] == -1)
    {
        if(posholder[huri+2][hurj-1]==-1)
        {

        total = totalmoves(huri + 2, hurj - 1);
        if(total <= minmoves)
        {
            minmoves = total;
            movementi = huri + 2;
            movementj = hurj - 1;
        }
        }
    }
    hurtest = movable(huri-2, hurj +1);
    if(hurtest == 0)
    //if(huri - 2 < 8 && huri - 2 >= 0 && hurj + 1 < 8 && hurj + 1 >= 0&& posholder[huri - 2][hurj +1] == -1)
    {
        if(posholder[huri -2][hurj+1]==-1)
        {
        total = totalmoves(huri - 2, hurj + 1);
        if(total <= minmoves)
        {
            minmoves = total;
            movementi = huri - 2;
            movementj = hurj + 1;
        }
        }
    }
    hurtest = movable(huri-2,hurj-1);
    if(hurtest == 0)
    //if(huri - 2 < 8 && huri - 2 >= 0 && hurj - 1 < 8 && hurj - 1 >= 0 && posholder[huri - 2][hurj -1] == -1)
    {
        if(posholder[huri-2][hurj-1]==-1)
        {
        total = totalmoves(huri - 2, hurj - 1);
        if(total <= minmoves)
        {
            minmoves = total;
            movementi = huri - 2;
            movementj = hurj - 1;
        }
        }
    }
    hurtest = movable(huri+1,hurj+2);
    if(hurtest == 0)
    //if(huri + 1 < 8 && huri + 1 >= 0 && hurj + 2 < 8 && hurj + 2 >= 0&& posholder[huri + 1][hurj +2] == -1)
    {
        if(posholder[huri +1][hurj +2]==-1)
        {
        total = totalmoves(huri + 1, hurj + 2);
        if(total <= minmoves)
        {
            minmoves = total;
            movementi = huri + 1;
            movementj = hurj + 2;
        }
        }
    }
    hurtest = movable(huri-1, hurj + 2);
    if(hurtest == 0)
    //if(huri - 1 < 8 && huri - 1 >= 0 && hurj + 2 < 8 && hurj + 2 >= 0 && posholder[huri - 1][hurj +2] == -1)
    {
        if(posholder[huri-1][hurj +2] == -1)
        {
        total = totalmoves(huri - 1, hurj + 2);
        if(total <= minmoves)
        {
            minmoves = total;
            movementi = huri - 1;
            movementj = hurj + 2;
        }
        }
    }
    hurtest = movable(huri +1, hurj -2);
    if(hurtest == 0)
     //if(huri + 1 < 8 && huri + 1 >= 0 && hurj - 2 < 8 && hurj - 2 >= 0 && posholder[huri + 1][hurj -2] == -1)
    {
        if(posholder[huri +1][hurj -2]==-1)
        {
        total = totalmoves(huri + 1, hurj - 2);
        if(total <= minmoves)
        {
            minmoves = total;
            movementi = huri + 1;
            movementj = hurj - 2;
        }
        }
    }
    hurtest = movable(huri-1, hurj-2);
    if(hurtest == 0)
     //if(huri - 1 < 8 && huri - 1 >= 0 && hurj - 2 < 8 && hurj - 2 >= 0 && posholder[huri - 1][hurj -2] == -1)
    {
        if(posholder[huri-1][hurj-2]==-1)
        {
        total = totalmoves(huri - 1, hurj - 2);
        if(total <= minmoves)
        {
            minmoves = total;
            movementi = huri - 1;
            movementj = hurj - 2;
        }
        }
    }
    //Make the lowest move.
    counter = counter + 1;
    des[counter].seti(movementi);
    des[counter].setj(movementj);
    posholder[movementi][movementj] = counter;

}
int main()
{
    //This is to help see if we're done.
    int maincounter = 1;
    //opens file
    Outfile.open("output.text");
    Start();

    //Sets current to head
    currentnode = headnode;

    //This loop goes for as many nodes as there are.
    while(keepgoing == true)
    {

        counter = 0;
        //resets the values of 2d array to -1
        for(int w = 0; w < 8; w++)
        {
            for(int x = 0; x < 8; x++)
            {
                posholder[w][x]= -1;
            }
        }
        //Sets the initial value
        des[counter].seti(currentnode->geti());
        des[counter].setj(currentnode->getj());
        posholder[des[counter].geti()][des[counter].getj()] = counter;

        //Runs the huristic 31 times since initial value was just set
        while(counter < 33)
        {
            Hur(des[counter].geti(), des[counter].getj());
        }
        //Runs the backtracking algorithm.
        Stacktry();
        Print();
        //Ends the entire thing
        if(maincounter == totalnodes)
        {
            keepgoing = false;
        }
        else
        {
            maincounter++;
            currentnode = currentnode->getnextnode();
        }
    }
    //Deletes instances
    Clear();
    //Closes outifle
    Outfile.close();
}

