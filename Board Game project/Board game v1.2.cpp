/* 
 * File:   recursions and sorts.cpp
 * Author: Jason Ryan Reyes 
 * Created on May 17 2026, 7:19 PM
 * Purpose: Create a board game to show off the stl libary
 *         The game of life
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>

using namespace std;
class output{
    void display();
    void displayinfo(int player);
    void displayboard();

};
class player
{
private:
    string *name = new string; // holds the name of the player
    string *job = new string;  // simplified to hold a single job string dynamically
    int *money = new int;
    int *position = new int;
    int *lifepoints = new int;
    int *totalscore = new int;
    int *income = new int;
    int *paytear = new int;
public:
    player();
    player(bool active);
    void changename(string &newName);
    void changejob(string newJob);
    void changemoney(int newMoney);
    void changelifepoints(int newLifepoints);
    void changeposition(int newPosition);
    void viewplayerinfo();
    int viewposition();
    void changeincome(int &newIncome);
    ~player();
};

player::player()
{
    *name = ""; 
    *job = "";
    *money = 0;
    *position = 0;
    *lifepoints = 0;
    *totalscore = 0;
    *income = 0;
}

void player::changeincome(int &newIncome)
{
    *income = newIncome;
}

player::player(bool active)
{
    if (active)
    {
        cout << "Enter player name: ";
        cin >> *name; 
        *money = 10000; 
        *position = 0; 
        *lifepoints = 0; 
        *totalscore = 0; 
        *income = 0;
    }
    else
    {
        *name = "";
        *money = 0;
        *position = 0;
        *lifepoints = 0;
        *totalscore = 0;
        *income = 0;
    }
}

void player::changename(string &newName)
{
    *name = newName; 
}

void player::changejob(string newJob)
{
    *job = newJob; 
}

void player::changemoney(int newMoney)
{
    *money += newMoney;
}

void player::changelifepoints(int newLifepoints)
{
    *lifepoints += newLifepoints;
}

void player::changeposition(int newPosition)
{
    *position += newPosition; // Fixed Bug: Changes the dereferenced target value, not pointer address
}

void player::viewplayerinfo()
{
    // Fixed: Must dereference pointers to print values, otherwise prints raw hex addresses
    cout << "Player Name: " << *name << endl;
    cout << "Job: " << *job << endl;
    cout << "Money: $" << *money << endl;
    cout << "Position: " << *position << endl;
    cout << "Lifepoints: " << *lifepoints << endl;
    cout << "Total Score: " << *totalscore << endl;
}

int player::viewposition()
{
    return *position;
}

player::~player() {
    delete name;
    delete job;
    delete money;
    delete position;
    delete lifepoints;
    delete totalscore;
    delete income;
}


class tiles
{
private:
    int total;
    int *lifeTiles;
    int *payTiles;
    int *stopTiles;
public:
    tiles();
    void tilesinfo(player &p , int roll);
    ~tiles();
};

tiles::tiles()
{
    total = 110;
    lifeTiles = new int[total / 10];
    for (int i = 0; i < 10; i++) {
        lifeTiles[i] = (i + 1) * 10;
    }

    payTiles = new int[18];
    for (int i = 0; i < 18; i++) {
        payTiles[i] = 10 + (i * 5);
    }

    stopTiles = new int[3];
    stopTiles[0] = 10; 
    stopTiles[1] = 15; 
    stopTiles[2] = 20; 
}

void tiles::tilesinfo(player &p , int roll)
{
    // check for stop tiles
    if (p.viewposition() < stopTiles[0])
    {
       if (p.viewposition() + roll >= stopTiles[0])
       {
        cout << "You landed on a career choice tile! Choose a new career." << endl;
        p.changeposition(stopTiles[0] - p.viewposition());
        return;
       }
    }
    if (p.viewposition() < stopTiles[1])
    {
       if (p.viewposition() + roll >= stopTiles[1])
       {
        cout << "You landed on a family choice tile! Choose a family option." << endl;
        p.changeposition(stopTiles[1] - p.viewposition());
        return;
       }
    }
    if (p.viewposition() < stopTiles[2])
    {
       if (p.viewposition() + roll >= stopTiles[2])
       {
        cout << "You landed on a house choice tile! Choose a house option." << endl;
        p.changeposition(stopTiles[2] - p.viewposition());
        return;
       }
    }

    // check for pay tiles
    for (int i = 0; i < 18; i++)
    {
       if (p.viewposition() + roll >= payTiles[i] && p.viewposition() < payTiles[i])
       {
        cout << "You passed/landed on a pay tile! You earn $" << payTiles[i] << "." << endl;
        p.changemoney(payTiles[i]);
       }
    }

    // check for life tiles
    for (int i = 0; i < 10; i++)
    {
       if (p.viewposition() + roll >= lifeTiles[i] && p.viewposition() < lifeTiles[i])
       {
        cout << "You passed/landed on a life tile! You earn " << lifeTiles[i] << " lifepoints." << endl;
        p.changelifepoints(lifeTiles[i]);
       }
    }

    p.changeposition(roll);
}

tiles::~tiles()
{ 
    delete[] lifeTiles;
    delete[] payTiles;
    delete[] stopTiles;
}


class board
{
private:
    int players;
    player *p; 
    tiles *t;
    
public:
    board();
    ~board();
};

board::board()
{  
    cout << "Enter number of players (2-5): ";
    cin >> players;
    while (players < 2 || players > 5) 
    {
        cout << "Invalid number of players. Please enter a number between 2 and 5: ";
        cin >> players;
    }
    
    
    p = new player[players];
    t = new tiles();
}

board::~board()
{   
    
    delete[] p; 
    delete t;
}   


class Cards
{
private:
    const char **job; 
    int **salary;
    
public:
    Cards();
    void pickjob(player &p);
    ~Cards();
};

Cards::Cards()
{   
    // Initialize job array
    job = new const char*[9];
    job[0] = "Doctor";
    job[1] = "Accountant";
    job[2]= "salesperson";
    job[3] = "Police Officer";
    job[4] = "Teacher";
    job[5] = "athlete";
    job[6] = "Entertainer";
    job[7] = "computer consultant";
    job[8] = "Artist";
    // Initialize salary array
    //salary arry = [roll goes here][{0=pay 1=tax 2=tear}]
    salary = new int*[9];
    for (int i = 0; i < 9; i++)
    {
        salary[i] = new int[2];
    }
    salary[0][0] = 20000;// pay
    salary[0][1] = 5000;// tax
    salary[0][2] = 1;// tear
    salary[1][0] = 50000;// pay
    salary[1][1] = 20000;// tax
    salary[1][2] = 1;// tear
    //end of tear 1 pay
    //start of tear 2 pay
    salary[2][0] = 30000;//pay
    salary[2][1] = 10000;// tax
    salary[2][2] = 2;// tear
    salary[3][0] = 40000;// pay
    salary[3][1] = 15000;// tax
    salary[3][2] = 2;// tear
    salary[4][0] = 80000;// pay
    salary[4][1] = 35000;// tax
    salary[4][2] = 2;// tear
    //end of tear 2 pay
    //start of tear 3 pay
    salary[5][0] = 60000;// pay
    salary[5][1] = 25000;// tax
    salary[5][2] = 3;// tear
    salary[6][0] = 70000;// pay
    salary[6][1] = 30000;// tax
    salary[6][2] = 3;// tear
    salary[7][0] = 90000;// pay
    salary[7][1] = 40000;// tax
    salary[7][2] = 3;// tear
    //end of tear 3 pay
    //start of tear 4 pay
    salary[8][0] = 100000;// pay
    salary[8][1] = 45000;// tax
    salary[8][2] = 4;// tear
    //end of tear 4 pay


    //debug section to check code
    cout<< job[7] << endl;
    cout<< salary[7][0] << endl;
    cout<< salary[7][1] << endl;
    //
}
void Cards::pickjob(player &p){
    //temp dice
    int *temp = new int[3];
    // you can't roll the same number twice so you don't pull the same card more then once
    while (temp[0] == temp[1] || temp[0] == temp[2] || temp[1] == temp[2])
    {
        temp[0] = rand() % 9 + 1;
        temp[1] = rand() % 9 + 1;
        temp[2] = rand() % 9 + 1;
    }
    cout<< "draw 3 job cards " << endl;
    cout<< job[temp[0]]<<job[temp[1]]<<job[temp[2]] << endl;
    

    cout<< "pick a job from the cards drawn." << endl;
}


Cards::~Cards()
{   
    delete[] salary;
    delete[] job; 
}

int main(int argc, char const *argv[])
{
    board gameOfLife;
    Cards cards;
    cards.~Cards();
    return 0;

}