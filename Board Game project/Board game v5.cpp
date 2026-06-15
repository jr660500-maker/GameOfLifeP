/* 
 *
 * File:   recursions and sorts.cpp
 * Author: Jason Ryan Reyes 
 * Created on May 17 2026, 7:19 PM
 * Purpose: Create a board game to show off the stl libary
 *         The game of life
 * 
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <queue>
using namespace std;

//helpers
void merge(int arr[], int left, int mid, int right) {
    // Calculate sizes of the two temporary subarrays
    int n1 = mid - left + 1;
    int n2 = right - mid;
    //temp arrys
    int*leftarr =new int[n1];
    int*rightarr=new int[n2];
    // Copy data to temporary vectors
    for (int i = 0; i < n1; i++) {
        leftarr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightarr[j] = arr[mid + 1 + j];
    }
    // Merge the temporary vectors back into the original array
    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = left; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (leftarr[i] <= rightarr[j]) {
            arr[k] = leftarr[i];
            i++;
        } else {
            arr[k] = rightarr[j];
            j++;
        }
        k++;
    }
    // Copy any remaining elements of L[]
    while (i < n1) {
        arr[k] = leftarr[i];
        i++;
        k++;
    }
    // Copy any remaining elements of R[]
    while (j < n2) {
        arr[k] = rightarr[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[], int left, int right) {
    // Base case: Stop when the section has 1 or 0 elements
    if (left >= right) {
        return;
    }
    
    // Calculate midpoint securely to prevent integer overflow
    int mid = left + (right - left) / 2;
    // Recursively sort the left half
    mergeSort(arr, left, mid);
    // Recursively sort the right half
    mergeSort(arr, mid + 1, right);
    // Merge the two sorted halves
    merge(arr, left, mid, right);
}

//used for two claerner 2d pointers
struct Node {
    int dest;
    Node* next;
};

class Graph {
private:
    int vertices;
    Node** adjList; // Pointer to an array of pointers

public:
    //defalt constructors
    Graph(){}
    // Constructor: Dynamically allocate the array
    Graph(int vectices) {
        this->vertices = vectices;
        adjList = new Node*[vectices];
        // Initialize all head pointers to NULL
        for (int i = 0; i < vectices; ++i) {
            adjList[i] = nullptr;
        }
    }
    // Destructor: Clean up all dynamically allocated memory
    ~Graph() {
        for (int i = 0; i < vertices; ++i) {
            Node* current = adjList[i];
            while (current != nullptr) {
                Node* nextNode = current->next;
                delete current; // Free node memory
                current = nextNode;
            }
        }
        delete[] adjList; // Free array memory
    }
    // Add an edge to an undirected graph
    void addEdge(int src, int dest) {
        // Insert new node at the beginning of src list
        Node* newNode = new Node{dest, adjList[src]};
        adjList[src] = newNode;

        // Insert new node at the beginning of dest list (undirected)
        newNode = new Node{src, adjList[dest]};
        adjList[dest] = newNode;
    }
    // Print the graph connections
    void printGraph() {
        for (int i = 0; i < vertices; ++i) {
            std::cout << "Vertex " << i << ":";
            Node* temp = adjList[i];
            while (temp != nullptr) {
                std::cout << " -> " << temp->dest;
                temp = temp->next;
            }
            std::cout << "\n";
        }
    }
};
class player
{
private:
    string name ; // holds the name of the player
    string *job = new string;  // simplified to hold a single job string dynamically
    string *homeName = new string;
    int *money = new int;
    int *position = new int;
    int *lifepoints = new int;
    int *totalscore = new int;
    int *income = new int;
    int *tax = new int;
    bool *college = new bool;
    bool *family = new bool;
    int *homeValue = new int;
public:
    player();
    void loadPs(bool active);
    int totalScore();
    void changename(string &newName);
    void changejob(string newJob);
    void changejob(int newJob);
    void changemoney(int newMoney);
    void changelifepoints(int newLifepoints);
    void changeposition(int newPosition);
    void viewplayerinfo();
    void pickfamly();
    void changehome(int newHomeValue);
    bool viewcollege();
    string viewhome();
    string viewname();
    int viewmoney();
    int viewlifepoints();
    int viewposition();
    int homevalue();
    void changetax(int newTax);
    int viewjob();
    player copy(player &Duplicate);
    void sortbyname(player p[], int numPlayers);
    void changeincome(int newIncome);
    void SortplayerScore(player p[], int numPlayers);
    void mergeSortPlayers(player p[], int left, int right);
    void mergePlayers(player p[], int left, int mid, int right);
    ~player();
};

player::player()
{
    name = ""; 
    *job = "";
    *money = 0;
    *position = 0;
    *lifepoints = 0;
    *totalscore = 0;
    *income = 0;
    *tax = 0;
    *college = false;
    *family =false;
}
int player::viewmoney(){
    return *money;
}
int player::viewlifepoints(){
    return *lifepoints;
}

int player::totalScore()
{
    *money +=homevalue();
    *totalscore = *lifepoints + (*money / 1000); 
    return *totalscore;
}
void player::pickfamly(){
    bool *family=new bool;
    cout<<"Would you like to start a family? (1 for yes, 0 for no): ";
    cin >> *family;
    if (*family==true)
    {
        *lifepoints += 10;
    }
    else
    {
        *lifepoints += 5;
    }
}
string player::viewhome(){
    return *homeName;
}
string player::viewname(){
    return name;
}
int player::homevalue(){
    return *homeValue;
}
void player::changehome(int newHomeValue){
    string *homeNameL=new string[9];
    homeNameL[0] = {"log cabin"};
    homeNameL[1] = {"Farm House"};
    homeNameL[2] = {"Beach house"};
    homeNameL[3] = {"Dutch Colonial"};
    homeNameL[4] = {"Cozy Condo"};
    homeNameL[5] = {"Split-level"};
    homeNameL[6] = {"Mobile Home"};
    homeNameL[7] = {"Tudor"};
    homeNameL[8] = {"Victorian"};
    //vaule of homes
    stack<int> homeValueL;
    homeValueL.push(80000);
    homeValueL.push(160000);
    homeValueL.push(140000);
    homeValueL.push(120000);
    homeValueL.push(100000);
    homeValueL.push(40000);
    homeValueL.push(60000);
    homeValueL.push(180000);
    homeValueL.push(200000);
    *homeValue=homeValueL.top(); // Set home value based on the new home
    *homeName=homeNameL[newHomeValue];
    
    delete[] homeNameL;

    
}
void player::changetax(int newTax){
    *tax = newTax;
}
void player::changeincome(int newIncome)
{
    *income = newIncome;
}
bool player::viewcollege()
{
    return *college;
}
void player::loadPs(bool active)
{
    if (active)
    {
        cout << "Enter player name: first name only: ";
        cin >> name; 
        *money = 10000; 
        *position = 0; 
        *lifepoints = 0; 
        *totalscore = 0; 
        *income = 0;
        cout<<"Would you like to attend college? (1 for yes, 0 for no): ";

        cin >> *college;
    }
    else
    {
        name = "";
        *money = 0;
        *position = 0;
        *lifepoints = 0;
        *totalscore = 0;
        *income = 0;
        *job = "";
        *tax = 0;
        *college = false;
        *homeValue = 0;
    }
}

void player::changename(string &newName)
{
    name = newName; 
}
void player::changejob(int newJob){
    const string jobs[9] =
    {
        "Doctor",
        "Accountant",
        "Salesperson",
        "Police Officer",
        "Teacher",
        "Athlete",
        "Entertainer",
        "Computer consultant",
        "Artist"
    };

    *job = jobs[newJob];
}
void player::changejob(string newJob)
{
    *job = newJob; 
}

void player::changemoney(int newMoney)
{
    *money += newMoney;
}
int player::viewjob(){
    if (*job == "Doctor") return 0;
    if (*job == "Accountant") return 1;
    if (*job == "Salesperson") return 2;
    if (*job == "Police Officer") return 3;
    if (*job == "Teacher") return 4;
    if (*job == "Athlete") return 5;
    if (*job == "Entertainer") return 6;
    if (*job == "Computer consultant") return 7;
    if (*job == "Artist") return 8;
    //if job has erro return -1
    return -1; 
}
void player::changelifepoints(int newLifepoints)
{
    *lifepoints += newLifepoints;
}

void player::changeposition(int newPosition)
{
    *position += newPosition; 
}

void player::viewplayerinfo()
{
   
    cout << "Player Name: " << name << endl;
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
player player::copy(player &Duplicate)
{
    name = Duplicate.viewname();
    changejob(Duplicate.viewjob());
    *money = Duplicate.viewmoney();
    *position = Duplicate.viewposition();
    *lifepoints = Duplicate.viewlifepoints();
    *totalscore = Duplicate.totalScore();
    *income = Duplicate.viewjob(); // Assuming income is related to job, adjust as needed
    *tax = 0; // Reset tax or set based on job if necessary
    *college = Duplicate.viewcollege();
    *homeValue = Duplicate.homevalue();
    *homeName = Duplicate.viewhome();
    return *this; // Return the current object after copying
}
void player::sortbyname(player p[], int numPlayers)
{
    for (int i = 0; i < numPlayers - 1; i++)
    {
        for (int j = 0; j < numPlayers - i - 1; j++)
        {
            if (p[j].viewname() > p[j + 1].viewname())
            {
                player temp;
                temp.copy(p[j]);
                p[j].copy(p[j + 1]);
                p[j + 1].copy(temp);
            }
        }
    }
}
void player::SortplayerScore(player p[], int numPlayers)
{
    mergeSortPlayers(p, 0, numPlayers - 1);
}
void player::mergeSortPlayers(player p[], int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSortPlayers(p, left, mid);
    mergeSortPlayers(p, mid + 1, right);

    mergePlayers(p, left, mid, right);
}
void player::mergePlayers(player p[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    player *leftArr = new player[n1];
    player *rightArr = new player[n2];

    for (int i = 0; i < n1; i++)
    {
        leftArr[i].copy(p[left + i]);
    }

    for (int i = 0; i < n2; i++)
    {
        rightArr[i].copy(p[mid + 1 + i]);
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (leftArr[i].totalScore() >= rightArr[j].totalScore())
        {
            p[k].copy(leftArr[i]);
            i++;
        }
        else
        {
            p[k].copy(rightArr[j]);
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        p[k].copy(leftArr[i]);
        i++;
        k++;
    }

    while (j < n2)
    {
        p[k].copy(rightArr[j]);
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

void mergeSortPlayers(player p[], int left, int right){

}
void mergePlayers(player p[], int left, int mid, int right);
void SortplayerScore(player p[], int numplayers);

player::~player() {
    delete job;
    delete money;
    delete position;
    delete lifepoints;
    delete totalscore;
    delete income;
    delete tax;
    delete college;
    delete homeValue;
    delete homeName;
}
class Cards
{
private:
    const char **job; 
    string *homeName=new string[9];
    int *homeValue=new int[9];
    int **salary;
    int *tier=0;
public:
    Cards();
    void pickjob(player &p);
    void PSalary(player &p);
    void House(player &p);
    ~Cards();
};

Cards::Cards()
{   

    //House cards
    homeName[0] = {"log cabin"};
    homeName[1] = {"Farm House"};
    homeName[2] = {"Beach house"};
    homeName[3] = {"Dutch Colonial"};
    homeName[4] = {"Cozy Condo"};
    homeName[5] = {"Split-level"};
    homeName[6] = {"Mobile Home"};
    homeName[7] = {"Tudor"};
    homeName[8] = {"Victorian"};
    // Initialize home value array
    homeValue[0] =  80000;
    homeValue[1] = 160000;
    homeValue[2] = 140000;
    homeValue[3] = 120000;
    homeValue[4] = 100000;
    homeValue[5] =  40000;
    homeValue[6] =  60000;
    homeValue[7] = 180000;
    homeValue[8] = 200000;
    map<int, string> jobMap = {
        {0, "Doctor"},
        {1, "Accountant"},
        {2, "Salesperson"},
        {3, "Police Officer"},
        {4, "Teacher"},
        {5, "Athlete"},
        {6, "Entertainer"},
        {7, "Computer consultant"},
        {8, "Artist"}
    };
    // Initialize job array
    list<string> jobList = {
        "Doctor",
        "Accountant",
        "Salesperson",
        "Police Officer",
        "Teacher",
        "Athlete",
        "Entertainer",
        "Computer consultant",
        "Artist"
    };
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
    //salary arry = [roll goes here][{0=pay 1=tax 2=tier}]
    salary = new int*[9];
    for (int i = 0; i < 9; i++)
    {
        salary[i] = new int[3];
    }
    salary[0][0] = 20000;// pay
    salary[0][1] = 5000;// tax
    salary[0][2] = 1;// tier
    salary[1][0] = 50000;// pay
    salary[1][1] = 20000;// tax
    salary[1][2] = 1;// tier
    //end of tier 1 pay
    //start of tier 2 pay
    salary[2][0] = 30000;//pay
    salary[2][1] = 10000;// tax
    salary[2][2] = 2;// tier
    salary[3][0] = 40000;// pay
    salary[3][1] = 15000;// tax
    salary[3][2] = 2;// tier
    salary[4][0] = 80000;// pay
    salary[4][1] = 35000;// tax
    salary[4][2] = 2;// tier
    //end of tier 2 pay
    //start of tier 3 pay
    salary[5][0] = 60000;// pay
    salary[5][1] = 25000;// tax
    salary[5][2] = 3;// tier
    salary[6][0] = 70000;// pay
    salary[6][1] = 30000;// tax
    salary[6][2] = 3;// tier
    salary[7][0] = 90000;// pay
    salary[7][1] = 40000;// tax
    salary[7][2] = 3;// tier
    //end of tier 3 pay
    //start of tier 4 pay
    salary[8][0] = 100000;// pay
    salary[8][1] = 45000;// tax
    salary[8][2] = 4;// tier
    //end of tier 4 pay
    //debug section to check code
    cout<< job[7] << endl;
    cout<< salary[7][0] << endl;
    cout<< salary[7][1] << endl;
    //
}
void Cards::House(player &p){
    int *temp = new int[3];
    int *Choice=new int;
   do
    {
    temp[0] = rand() % 9;
    temp[1] = rand() % 9;
    temp[2] = rand() % 9;
    }
    while (temp[0] == temp[1] ||temp[0] == temp[2] ||temp[1] == temp[2]);
    cout<< "You will choise from the following homes: " << endl;
    cout<< homeName[temp[0]] << " : " << homeName[temp[1]] << " : " << homeName[temp[2]] << endl;
    cin >> *Choice;
    while (*Choice != 1 && *Choice != 2 && *Choice != 3){
        cout<< "Invalid choice. Please press 1, 2, or 3 to choose." << endl;
        cin >> *Choice;
    }
    p.changehome(temp[*Choice - 1]);
    delete[] temp;
    delete Choice;
}
void Cards::PSalary(player &p){
    int roll;
    int jobIndex = p.viewjob();

    // Doctors and Accountants (Indices 0 and 1)  Tier 3 or 4
    if (jobIndex <= 1) {
        roll = (rand() % 4) + 5; // Generates indices 5, 6, 7, 8
        p.changeincome(salary[roll][0]);
        p.changetax(salary[roll][1]);
    }
    // Salesperson, Police Officer, Teacher, Athlete (Indices 2 to 5)  Tier 2 or 3
    else if (jobIndex >= 2 && jobIndex <= 5) {
        roll = (rand() % 6) + 2; // Generates indices 2, 3, 4, 5, 6, 7
        p.changeincome(salary[roll][0]);
        p.changetax(salary[roll][1]);
    }
    // Entertainer, Computer Consultant, Artist (Indices 6 to 8)  Tier 1 or 2
    else if (jobIndex >= 6 && jobIndex <= 8) {
        roll = rand() % 5; // Generates indices 0, 1, 2, 3, 4
        p.changeincome(salary[roll][0]);
        p.changetax(salary[roll][1]);
    }
}
void Cards::pickjob(player &p){
    int temp[3]; // Stack allocation avoids leaks completely
    int choice;

    do {
        temp[0] = rand() % 9;
        temp[1] = rand() % 9;
        temp[2] = rand() % 9;
    } while (temp[0] == temp[1] || temp[0] == temp[2] || temp[1] == temp[2]);

    bool validChoice = false;

    // Use a while loop to cleanly handle user validation without goto statements
    while (!validChoice) {
        cout << "Draw 3 job cards: " << endl;
        cout << "1. " << job[temp[0]] << "\n2. " << job[temp[1]] << "\n3. " << job[temp[2]] << endl;
        cout << "Pick a job from the cards drawn. Press 1, 2, or 3 to choose." << endl;
        cin >> choice;

        while (choice != 1 && choice != 2 && choice != 3) {
            cout << "Invalid choice. Please press 1, 2, or 3 to choose." << endl;
            cin >> choice;
        }

        int selectedJobIdx = temp[choice - 1];

        // Validate choice based on college rule (Doctor is index 0)
        if (selectedJobIdx == 0 && !p.viewcollege()) {
            cout << "\nYou can't pick the job " << job[selectedJobIdx] 
                 << " because you haven't attended college. Please pick a different card.\n" << endl;
        } else {
            validChoice = true; // Selection is valid; break loop execution
        }
    }

    p.changejob(temp[choice - 1]);
}

Cards::~Cards()
{   
        for (int i = 0; i < 9; i++)
    {
        delete[] salary[i];
    }
    delete[] homeName;
    delete[] homeValue;
    delete[] salary;
    delete[] job; 
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
    void tilesinfo(player &p, Cards &c, int roll);
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

void tiles::tilesinfo(player &p, Cards &c, int roll)
{
    // check for stop tiles
    if (p.viewposition() < stopTiles[0])
    {
       if (p.viewposition() + roll >= stopTiles[0])
       {
        cout << "You landed on a career choice tile! Choose a new career." << endl;
        p.changeposition(stopTiles[0] - p.viewposition());
        c.pickjob(p);
       }
    }
    if (p.viewposition() < stopTiles[1])
    {
       if (p.viewposition() + roll >= stopTiles[1])
       {
        cout << "You landed on a family choice tile! Choose a family option." << endl;
        p.changeposition(stopTiles[1] - p.viewposition());
        
       }
    }
    if (p.viewposition() < stopTiles[2])
    {
       if (p.viewposition() + roll >= stopTiles[2])
       {
        cout << "You landed on a house choice tile! Choose a house option." << endl;
        p.changeposition(stopTiles[2] - p.viewposition());
        c.House(p);
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
class output{
    public:
    void display();
    void displayboard();
    void endgameDisplay(player p[], int numPlayers);
};
void output::display(){
    cout<< "Welcome to the game of life!"<<endl;
    cout<< "The goal of the game is to be the player with the most lifepoints to reach the end of the board."<<endl;
    cout<< "You will also have the opportunity to choose a career, start a family, and buy a house."<<endl;
    cout<< "You earn lifepoints by landing on life tiles and earn money by passing pay tiles."<<endl;
    cout<< "At the end of the game your left over money will be turned into lifepoints."<<endl;
    cout<< "Good luck and have fun!"<<endl;
}
void output::displayboard(){
    cout<< "The board is 110 spaces long."<<endl;
    cout<< "There are 10 life tiles, 18 pay tiles, and 3 stop tiles."<<endl;
    cout<< "The stop tiles are at space 10, 15, and 20."<<endl;
    cout<< "The life tiles are at space 10, 20, 30, 40, 50, 60, 70, 80, 90, and 100."<<endl;
    cout<< "The pay tiles are at space 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, and 95."<<endl;
}
void output::endgameDisplay(player p[], int numPlayers){
    cout<< "Game over! Here are the final scores: " << endl;
    for (int i = 0; i < numPlayers; i++)
    {
        cout << "Player " << i + 1 <<" " << p[i].totalScore() << " lifepoints." << endl;
    }
}

class board
{
private:
    int players;
    player *p; 
    tiles *t;
    Cards *c;
    output *o;
    Graph *g;
public:
    board();
    void moveP();
    void intro();
    int getPlayers();
    void history();
    bool wincheck();
    void sortPlayersByName();
    void sortPlayesByscore();
    void endgame();
    void que();
    void graph();
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
    c = new Cards();
    o = new output();
    g = new Graph(players);
    for (int i = 0; i < players; i++)
    {
        p[i].loadPs(true);
    }
}
void board::intro(){
    //display rules usting output class 
    o->display();
     o->displayboard();
}
int board::getPlayers(){
    return players;
}

bool board::wincheck(){
for (int i = 0; i < players; i++)
{
    if (p[i].viewposition()<=110)
    {
        return false;
    }
}
return true;
}
void board::sortPlayesByscore(){
    player temp;
    temp.SortplayerScore(p, players);
        cout<<"here are the final scores sorted "<<endl;
        for (int i = 0; i < players; i++)
        {
            cout<<"player" <<i+1<< " "<<p[i].totalScore()<< " lifepoints."<<endl;
        }
        
}
void board::sortPlayersByName() {
    player temp;
    temp.sortbyname(p, players);
        cout<< "Here are the final scores sorted by name: " << endl;
    for (int i = 0; i < players; i++)
    {
        cout << "Player " << i + 1 <<" " << p[i].totalScore() << " lifepoints." << endl;
    }
}

void board::history(){
    fstream historyFile("GameOfLifeHistory.txt", ios::app);

    for (int i = 0; i < players; i++) {
        historyFile << "Player Name: " << p[i].viewname() << endl;
        historyFile << "Job: " << p[i].viewjob() << endl;
        historyFile << "Money: $" << p[i].viewmoney() << endl;
        historyFile << "Position: " << p[i].viewposition() << endl;
        historyFile << "Lifepoints: " << p[i].viewlifepoints() << endl;
        historyFile << "Total Score: " << p[i].totalScore() << endl;
        historyFile << "Home: " << p[i].viewhome() << endl;
        historyFile << "-----------------------------" << endl;
    }

    historyFile.close();
}


void board::moveP(){
    int *roll = new int;

    for (int i = 0; i < players; i++)
    {
        *roll = rand() % 10 + 1;
        cout<< "Player " << i + 1 << " rolled a " << *roll << endl;
        t->tilesinfo(p[i],*c,*roll);
    }
    delete roll;
    
}
void board::que(){
    queue<player> playerQueue;
    for (int i = 0; i < players; i++) {
        playerQueue.push(p[i]);
    }
    while (!playerQueue.empty()) {
        player currentPlayer = playerQueue.front();
        playerQueue.pop();
        // Process currentPlayer's turn here
    }
}
void board::endgame(){
    o->endgameDisplay(p, players);
}
void board::graph(){
    player temp;
    temp.SortplayerScore(p, players);
        
}
board::~board()
{   
    delete g;
    delete[] p; 
    delete t;
    delete c;
    delete o;
}   

int main(int argc, char const *argv[])
{
    board gameOfLife;
    gameOfLife.intro();

    do
    {
        gameOfLife.moveP();
    } while (gameOfLife.wincheck()==false);
    gameOfLife.history();
    gameOfLife.sortPlayersByName();
    gameOfLife.endgame();
    
    return 0;
}