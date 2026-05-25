/* 
 * File:   recursions and sorts.cpp
 * Author: Jason Ryan Reyes 
 * Created on May 17 2026, 7:19 PM
 * Purpose: Create a board game to show off the stl libary
 *         The game of life
 */

//System Libraries
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>
using namespace std;

//User Libraries

class player
{
private:
        string *name= new string;//holds the name of the player
        string *job = new string; //holds 20 possible jobs for the player to choose from
        int *money = new int;
        int *position = new int;
        int *lifepoints = new int;
        int *totalscore = new int;
        int *income = new int;   
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
    *name = '\0';
    *job = '\0';
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
        cin >> *name; // holds each player's name
        *money = 10000; //starting money set to $10,000
        *position = 0; //logical position on the board, not actual coordinates
        *lifepoints = 0; //lifepoints a score gained from landing on life tiles
        *totalscore = 0; //lifepoints + money
    }
    else
    {
        *name = '\0';
        *money = 0;
        *position = 0;
        *lifepoints = 0;
        *totalscore = 0;
}
}
void player::changename(string &newName)
{
    *name = newName; //changes the player's name to the new name
   
}
void player::changejob(string newJob)
{
    *job = newJob; //changes the player's job to the new job
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
    position += newPosition;
}

void player::viewplayerinfo()
{
    cout << "Player Name: " << name << endl;
    cout << "Job: " << job << endl;
    cout << "Money: $" << money << endl;
    cout << "Position: " << position << endl;
    cout << "Lifepoints: " << lifepoints << endl;
    cout << "Total Score: " << totalscore << endl;
}

int player::viewposition()
{
    return *position;
}
player::~player(){
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
    void tiles::tilesinfo(player &p , int roll);
    ~tiles();
};
tiles::tiles()
{
    total = 110;
    lifeTiles = new int[total / 10];
    //life tiles
    lifeTiles[0] = 10; //life tile 1
    lifeTiles[1] = 20; //life tile 2
    lifeTiles[2] = 30; //life tile 3
    lifeTiles[3] = 40; //life tile 4
    lifeTiles[4] = 50; //life tile 5
    lifeTiles[5] = 60; //life tile 6
    lifeTiles[6] = 70; //life tile 7
    lifeTiles[7] = 80; //life tile 8
    lifeTiles[8] = 90; //life tile 9
    lifeTiles[9] = 100; //life tile 10
    //pay tiles
    payTiles = new int[18];
    payTiles[0]  = 10; //pay tile 1
    payTiles[1]  = 15; //pay tile 2
    payTiles[2]  = 20; //pay tile 3
    payTiles[3]  = 25; //pay tile 4
    payTiles[4]  = 30; //pay tile 5
    payTiles[5]  = 35; //pay tile 6
    payTiles[6]  = 40; //pay tile 7
    payTiles[7]  = 45; //pay tile 8
    payTiles[8]  = 50; //pay tile 9
    payTiles[9]  = 55; //pay tile 10
    payTiles[10] = 60; //pay tile 11
    payTiles[11] = 65; //pay tile 12
    payTiles[12] = 70; //pay tile 13
    payTiles[13] = 75; //pay tile 14
    payTiles[14] = 80; //pay tile 15
    payTiles[15] = 85; //pay tile 16
    payTiles[16] = 90; //pay tile 17
    payTiles[17] = 95; //pay tile 18
    //stop tiles
    stopTiles = new int[3];
    stopTiles[0] = 10; //stop tile 1 for career choice
    stopTiles[1] = 15; //stop tile 2 for family choice
    stopTiles[2] = 20; //stop tile 3 for house choice
}
void tiles::tilesinfo(player &p , int roll)
{
    //check for stop tiles
    //first stop tile
    if (p.viewposition() < stopTiles[0])
    {
       if (p.viewposition() + roll >= stopTiles[0])
       {
        cout << "You landed on a career choice tile! Choose a new career." << endl;
        p.changeposition(stopTiles[0]);
       }
    }
    //second stop tile
     if (p.viewposition() < stopTiles[1])
    {
       if (p.viewposition() + roll >= stopTiles[1])
       {
        cout << "You landed on a family choice tile! Choose a family option." << endl;
        p.changeposition(stopTiles[1]);
       }
    }
    //third stop tile
     if (p.viewposition() < stopTiles[2])
    {
       if (p.viewposition() + roll >= stopTiles[2])
       {
        cout << "You landed on a house choice tile! Choose a house option." << endl;
        p.changeposition(stopTiles[2]);
       }
    }
    //check for pay tiles
    for (int i = 0; i < 18; i++)
    {
       if (p.viewposition() + roll >= payTiles[i])
       {
        cout << "You landed on a pay tile! You earn $" << payTiles[i] << "." << endl;
        p.changemoney(payTiles[i]);
       }
    }
    //check for life tiles
    for (int i = 0; i < 10; i++)
    {
       if (p.viewposition() + roll >= lifeTiles[i])
       {
        cout << "You landed on a life tile! You earn " << lifeTiles[i] << " lifepoints." << endl;
        p.changelifepoints(lifeTiles[i]);
       }
    }

}
tiles::~tiles()
{   delete[] lifeTiles;
    delete[] payTiles;
    delete[] stopTiles;
}

class board
{
private:
    int players;//number of players
    class player *p=new player[players]; 
    class tiles *t=new tiles;
    
public:
    board();
    ~board();
};
//job cards for career choices and promotions
class jobCards
{
private:
    char **job = new char*[20];//holds the name of the job
    int *salary = new int[5];//holds the salary of the job and 5 possible promotions
    
public:
    jobCards(/* args */);
    void jobCards::promotion(player &p,int level);
    ~jobCards();

};
jobCards::jobCards()
{   

    job[0] = {"Kitchen worker"};
    job[1] = {"Engineer"};
    job[2] = {"Doctor"};
    job[3] = {"Lawyer"};
    job[4] = {"artist"};
    
}
void jobCards::promotion(player &p,int level)
{
    if (level >= 0 && level < 5)
    {
        p.changeincome(salary[level]); //sets the player's income to the specified promotion salary
    }
}
jobCards::~jobCards()
{   delete[] salary;
    delete[] job;
}
board::board()
{  
    tiles t;
    cout << "Enter number of players: ";
    cin >> players;
    while (players>2&&players<6)
    {
        cout << "Invalid number of players. Please enter a number between 2 and 6: ";
        cin >> players;
    }
    player *p = new player[players];
}
board::~board()
{   
    for (int i = 0; i < players; i++)
    {
        p[i].~player();
    }
    delete[] p;
    delete t;
}   

int main(int argc, char const *argv[])
{
    
    return 0;
}
