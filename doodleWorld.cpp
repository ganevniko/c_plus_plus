#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;
const int worldSize =5;
const int initialNumberOfAnts = 2;
const int initialNumberOfDoodleBugs = 1;
const char antsAppearance = 'O';
const char doodleBugsAppearance = 'X';
const char emptySpaceAppearance = '-';

char doodleWorld[worldSize][worldSize];


class organism {
public:
    organism(int row, int column);
    int getRow();
    int getColumn();
    bool lifeCheck();
    void kill();
    char getLeft();
    char getRight();
    char getUp();
    char getDown();
    void setLeft(char l);
    void setRight(char r);
    void setUp(char u);
    void setDown(char d);
    //virtual void move() const;
private:
    int positionRow;
    int positionColumn;
    bool isAlive;
    char left;
    char right;
    char up;
    char down;
};


organism :: organism(int row, int column){
    positionRow = row;
    positionColumn = column;
    isAlive = true;
    if (positionRow == 0)
        up = '9';
    else
        up = doodleWorld[positionRow-1][column];
    if (positionRow == worldSize-1 )
        down = '9';
    else
        down = doodleWorld[positionRow+1][column];
    if (positionColumn == 0 )
        left = '9';
    else
        left = doodleWorld[positionRow][column-1];
    if (positionColumn == worldSize-1 ) {
        right = '9';
    }

    else {
        right = doodleWorld[positionRow][column + 1];
    }

}

int organism :: getRow() {
    return positionRow;
}
int organism :: getColumn() {
    return positionColumn;
}

bool organism :: lifeCheck() {
    return isAlive;
}

void organism:: kill() {
    isAlive = false;
}

char organism:: getLeft(){
    return left;
}

char organism:: getRight(){
    return right;
}
char organism:: getUp(){
    return up;
}
char organism:: getDown(){
    return down;
}

void organism:: setLeft(char l){
     left =l;
}

void organism:: setRight(char r){
    right = r;
}
void organism:: setUp(char u){
    up = u;
}
void organism:: setDown(char d){
    down =d;
}

class ant : public organism {
public:
    ant(int row, int column);
private:
    int stepsAlive;
    char appearance;
};
ant::ant(int row, int column):organism(row,column){
    appearance = antsAppearance ;
    stepsAlive =0;
}


class doodleBug : public organism{
public:
    doodleBug(int row, int column);
private:
    int stepsAlive;
    char appearance;
};

doodleBug::doodleBug(int row, int column):organism(row,column){
    appearance = doodleBugsAppearance;
    stepsAlive =0;
}

void displayWorld(char arr[worldSize][worldSize]);
int main(){
    srand(time(0));
    char next='y';
    int tempRow=0, tempColumn=0;
    vector<ant> antsArray;
    vector<doodleBug> doodleBugsArray;

    //Initializing world
    for (int i = 0; i < worldSize; ++i ) {
        for (int j = 0; j < worldSize; ++j)
            doodleWorld[i][j] = emptySpaceAppearance;
    }
    //Initializing ants
    for (int i=0; i<initialNumberOfAnts; i++){
        while (doodleWorld[tempRow][tempColumn]!=emptySpaceAppearance) {
            tempRow = int(rand() % worldSize);
            tempColumn = int(rand() % worldSize);
        }
        antsArray.push_back(ant(tempRow, tempColumn));
        doodleWorld[tempRow][tempColumn]= antsAppearance;

    }
    //Initializing Doodles
    for (int i=0; i<initialNumberOfDoodleBugs; i++){
        while (doodleWorld[tempRow][tempColumn]!=emptySpaceAppearance) {
            tempRow = int(rand() % worldSize);
            tempColumn = int(rand() % worldSize);
        }
        doodleBugsArray.push_back(doodleBug(tempRow, tempColumn));
        doodleWorld[tempRow][tempColumn]= doodleBugsAppearance;

    }



    cout<<"The Current state of Doddle World is:"<<endl;
    displayWorld(doodleWorld);
    while (next == 'y') {
        cout << "To move one step further press \"Enter\" to end game enter n:" << endl;
        next = cin.get();
        if (next!='n') {
            next = 'y';
            displayWorld(doodleWorld);
        }
    }

    cout<<"right --> "<<antsArray[1].getRight()<<endl;
    cout<<"left --> "<<antsArray[1].getLeft()<<endl;
    cout<<"up --> "<<antsArray[1].getUp()<<endl;
    cout<<"down --> "<<antsArray[1].getDown()<<endl;

    return 0;
}



void displayWorld(char arr[worldSize][worldSize]){
    for (int i=0; i<worldSize; i++) {
        for (int j = 0; j < worldSize; j++) {
            cout << arr[i][j]<<"\t";
        }
        cout << endl;
    }

}

void lookAround(organism org){
    char l, r, u, d;

    if (org.getRow() == 0)
        org.setUp('9');
    else
        org.setUp(doodleWorld[org.getRow()-1][org.getColumn()]);
    if (org.getRow() == worldSize-1 )
        org.setDown('9');
    else
        org.setDown(doodleWorld[org.getRow()+1][org.getColumn()]);
    if (org.getColumn() == 0 )
        org.setLeft('9');
    else
        org.setLeft(doodleWorld[org.getRow()][org.getColumn()-1]);
    if (org.getColumn() == worldSize-1 ) {
        org.setRight('9');
    }

    else {
        org.setRight(doodleWorld[org.getRow()][org.getColumn() + 1]);
    }

}
