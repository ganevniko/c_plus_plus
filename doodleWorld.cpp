#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;
const int worldSize =5;
const int initialNumberOfAnts = 3;
const int initialNumberOfDoodleBugs = 2;
const char antsAppearance = 'o';
const char doodleBugsAppearance = 'X';
const char emptySpaceAppearance = '-';
const char directions[4]={'l','r','u','d'};
char doodleWorld[worldSize][worldSize];


class organism {
public:
    organism(int row, int column);
    int getRow();
    int getColumn();
    void setRow(int a);
    void setColumn(int a);
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
    void updateLeft();
    void updateRight();
    void updateUp();
    void updateDown();
    void lookAround();
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
    return this->positionRow;
}
int organism :: getColumn() {
    return positionColumn;
}

void organism::setRow(int a){
    this->positionRow=a;
}

void organism::setColumn(int a){
    this->positionColumn=a;
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
    this->left =l;
}

void organism:: setRight(char r){
    this->right = r;
}
void organism:: setUp(char u){
    this->up = u;
}
void organism:: setDown(char d){
    this->down =d;
}

void organism::updateUp(){
    if (positionRow == 0)
        up = '9';
    else
        up = doodleWorld[positionRow-1][positionColumn];


}
void organism::updateDown(){
    if (positionRow == worldSize-1 )
        down = '9';
    else
        down = doodleWorld[positionRow+1][positionColumn];


}
void organism::updateLeft(){
    if (positionColumn == 0 )
        left = '9';
    else
        left = doodleWorld[positionRow][positionColumn-1];

}
void organism::updateRight(){
    if (positionColumn == worldSize-1 ) {
        right = '9';
    }

    else {
        right = doodleWorld[positionRow][positionColumn + 1];
    }


}

void organism::lookAround(){
    updateDown();
    updateLeft();
    updateRight();
    updateUp();
}

// //////////////////////////////////////////////////////////////////////////////////////////////////

class ant : public organism {
public:
    ant(int row, int column);
    void breed();
    void move();

private:
    int stepsAlive;
    char appearance;
};
ant::ant(int row, int column):organism(row,column){
    appearance = antsAppearance ;
    stepsAlive =0;
}
void ant:: move(){
    srand(time(0));
    vector<char> whatsAvailable;
    char decision='n';
    int randomizing;
    this->lookAround();
    if (doodleWorld[getRow()][getColumn()]==doodleBugsAppearance ) {
        kill();
        cout<<"killed ant on row "<<getRow()<<" and column "<<getColumn()<<endl;
    }
    else{
        if (getRight() == emptySpaceAppearance)
            whatsAvailable.push_back('r');
        if (getLeft() == emptySpaceAppearance)
            whatsAvailable.push_back('l');
        if (getUp() == emptySpaceAppearance)
            whatsAvailable.push_back('u');
        if (getDown() == emptySpaceAppearance)
            whatsAvailable.push_back('d');

        if (!(whatsAvailable.empty())) {
            randomizing = int(rand() % whatsAvailable.size());
            decision = whatsAvailable[randomizing];
        }
    }
        if (decision== 'r' || decision== 'd' || decision== 'u' || decision== 'l' ){
            doodleWorld[getRow()][getColumn()] = emptySpaceAppearance;
            if (decision == 'u' && doodleWorld[getRow()-1][getColumn()]!=antsAppearance) {
                this->setRow(getRow() - 1);
                doodleWorld[getRow()][getColumn()] = antsAppearance;
            }
            if (decision == 'd' && doodleWorld[getRow()+1][getColumn()]!=antsAppearance) {
                this->setRow(getRow() + 1);
                doodleWorld[getRow()][getColumn()] = antsAppearance;
            }
            if (decision == 'l' && doodleWorld[getRow()][getColumn()-1]!=antsAppearance) {
                this->setColumn(getColumn() - 1);
                doodleWorld[getRow()][getColumn()] = antsAppearance;
            }
            if (decision == 'r' && doodleWorld[getRow()][getColumn()+1]!=antsAppearance) {
                this->setColumn(getColumn() + 1);
                doodleWorld[getRow()][getColumn()] = antsAppearance;
            }
        }



}
void ant::breed(){


}
// ////////////////////////////////////////////////////////////////////////////


class doodleBug : public organism{
public:
    doodleBug(int row, int column);
    void breed();
    void move();
private:
    int stepsAlive;
    char appearance;
};

doodleBug::doodleBug(int row, int column):organism(row,column){
    appearance = doodleBugsAppearance;
    stepsAlive =0;
}
void doodleBug:: breed(){

}
void doodleBug::move(){
    srand(time(0));
    vector<char> whatsAvailable;
    char decision='n';
    int randomizing;
    this->lookAround();
    if (getRight()==antsAppearance) {
        decision = 'r';
    }
    else if (getLeft()==antsAppearance) {
        decision = 'l';
    }
    else if (getUp()==antsAppearance) {
        decision = 'u';
    }
    else if (getDown()==antsAppearance) {
        decision = 'd';
    }

    if (decision!= 'r' && decision!= 'd' && decision!= 'u' && decision!= 'l' ) {
        if (getRight() == emptySpaceAppearance)
            whatsAvailable.push_back('r');
        if (getLeft() == emptySpaceAppearance)
            whatsAvailable.push_back('l');
        if (getUp() == emptySpaceAppearance)
            whatsAvailable.push_back('u');
        if (getDown() == emptySpaceAppearance)
            whatsAvailable.push_back('d');

        if (!(whatsAvailable.empty())) {
            randomizing = int(rand() % whatsAvailable.size());
            decision = whatsAvailable[randomizing];
        }
    }

    if (decision== 'r' || decision== 'd' || decision== 'u' || decision== 'l' ){
        doodleWorld[getRow()][getColumn()] = emptySpaceAppearance;
        if (decision == 'u' && doodleWorld[getRow()-1][getColumn()]!=doodleBugsAppearance) {
            this->setRow(getRow() - 1);
            doodleWorld[getRow()][getColumn()] = doodleBugsAppearance;
        }
        if (decision == 'd' && doodleWorld[getRow()+1][getColumn()]!=doodleBugsAppearance) {
            this->setRow(getRow() + 1);
            doodleWorld[getRow()][getColumn()] = doodleBugsAppearance;
        }
        if (decision == 'l' && doodleWorld[getRow()][getColumn()-1]!=doodleBugsAppearance) {
            this->setColumn(getColumn() - 1);
            doodleWorld[getRow()][getColumn()] = doodleBugsAppearance;
        }
        if (decision == 'r' && doodleWorld[getRow()][getColumn()+1]!=doodleBugsAppearance) {
            this->setColumn(getColumn() + 1);
            doodleWorld[getRow()][getColumn()] = doodleBugsAppearance;
        }
    }

}

void displayWorld(char arr[worldSize][worldSize]);

int main(){
    srand(time(0));
    char next='y';
    int tempRow=0, tempColumn=0, selected_direction;
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
            tempRow = int(rand() % worldSize)+1;
            tempColumn = int(rand() % worldSize)+1;
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
    for (int i=0; i<antsArray.size();i++)
        antsArray[i].lookAround();

    cout<<"The Current state of Doodle World is:"<<endl;
    displayWorld(doodleWorld);
    cout<<" Are you ready to take the first step? if yes enter 'y'."<<endl;
    cin>>next;
    while (next == 'y') {
        for (int i=0; i<doodleBugsArray.size();i++) {
            doodleBugsArray[i].move();
            doodleBugsArray[i].lookAround();
        }
        for (int i=0; i<antsArray.size();i++) {
            antsArray[i].move();
            antsArray[i].lookAround();
            if (antsArray[i].lifeCheck() == false)
                antsArray.erase(antsArray.begin()+i-1);
        }
        cout<<"The surviving ants are "<<endl;
        for (int i=0; i<antsArray.size();i++)
            cout<<i<<" - in row "<<antsArray[i].getRow()<<" and column "<<antsArray[i].getColumn()<<endl;

        displayWorld(doodleWorld);
        cout << "To move one step further press y" << endl;
        cin>>next;

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




