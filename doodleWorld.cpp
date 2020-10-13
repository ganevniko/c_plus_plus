#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;
    const int worldSize =5;
const int initialNumberOfAnts = 2;
const int initialNumberOfDoodleBugs = 1;
const char antsAppearance = 'o';
const char doodleBugsAppearance = 'X';
const char emptySpaceAppearance = '-';
const int doodleBugStepsToStarvation = 3;
const int antStepsToBreed =3;
char doodleWorld[worldSize][worldSize];


class organism {
public:
    organism(int row, int column);
    int getRow() const;
    int getColumn() const;
    void setRow(int a);
    void setColumn(int a);
    bool lifeCheck() const;
    void kill();
    char getLeft() const;
    char getRight() const;
    char getUp() const;
    char getDown() const;
    void updateLeft();
    void updateRight();
    void updateUp();
    void updateDown();
    void lookAround();
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

int organism :: getRow() const {
    return this->positionRow;
}
int organism :: getColumn() const{
    return positionColumn;
}

void organism::setRow(int a){
    this->positionRow=a;
}

void organism::setColumn(int a){
    this->positionColumn=a;
}


bool organism :: lifeCheck() const {
    return isAlive;
}

void organism:: kill() {
    isAlive = false;
}

char organism:: getLeft() const{
    return left;
}

char organism:: getRight() const{
    return right;
}
char organism:: getUp() const{
    return up;
}
char organism:: getDown() const{
    return down;
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

/*//////////////////////////////////////////////////////////////////////////////////////////////////*/

class ant : public organism {
public:
    ant(int row, int column);
    ant breed();
    void move();
    int getStepsAlive();

private:
    int stepsAlive;
    char appearance;
};
ant::ant(int row, int column):organism(row,column){
    appearance = antsAppearance ;
    stepsAlive =0;
}
int ant::getStepsAlive() {
    return this->stepsAlive;
}

void ant:: move(){
    srand(time(0));
    vector<char> whatsAvailable;
    char decision='n';
    int randomizing;
    this->lookAround();
    if (doodleWorld[getRow()][getColumn()]==doodleBugsAppearance ) {
        this->kill();
        cout<<"killed ant on row "<<getRow()<<" and column "<<getColumn()<<endl;
    }
    else{
        this->stepsAlive = this->stepsAlive +1;
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
ant ant::breed(){
    this->lookAround();
    vector<char> whereToBreed;
    ant newAnt(this->getRow(),this->getColumn());
    char decision='n';
    int randomizing;
    if (getRight() == emptySpaceAppearance)
        whereToBreed.push_back('r');
    if (getLeft() == emptySpaceAppearance)
        whereToBreed.push_back('l');
    if (getUp() == emptySpaceAppearance)
        whereToBreed.push_back('u');
    if (getDown() == emptySpaceAppearance)
        whereToBreed.push_back('d');

    if (!(whereToBreed.empty())) {
        randomizing = int(rand() % whereToBreed.size());
        decision = whereToBreed[randomizing];

    }

    if (decision == 'l'){
        newAnt.setColumn(this->getColumn()-1);
    }
    if (decision == 'r'){
        newAnt.setColumn(this->getColumn()+1);
    }

    if (decision == 'u'){
        newAnt.setRow(this->getRow()-1);
    }

    if (decision == 'd'){
        newAnt.setColumn(this->getRow()+1);
    }

    doodleWorld[newAnt.getRow()][newAnt.getColumn()] = antsAppearance;
    return newAnt;
}
// ////////////////////////////////////////////////////////////////////////////


class doodleBug : public organism{
public:
    doodleBug(int row, int column);
    void breed();
    void move();
    int getStarving() const;
    void setStarving(int a);
private:
    int stepsStarving;
    char appearance;
};

doodleBug::doodleBug(int row, int column):organism(row,column){
    appearance = doodleBugsAppearance;
    stepsStarving =0;
}
void doodleBug:: breed(){

}

int doodleBug::getStarving() const{
    return this->stepsStarving;
}
void doodleBug::setStarving(int a){
    this->stepsStarving = this->stepsStarving+1;
}
void doodleBug::move(){
    srand(time(0));
    bool starving = true;
    vector<char> whatsAvailable;
    char decision='n';
    int randomizing;
    this->lookAround();
    if (getRight()==antsAppearance) {
        decision = 'r';
        starving = false;
    }
    else if (getLeft()==antsAppearance) {
        decision = 'l';
        starving = false;
    }
    else if (getUp()==antsAppearance) {
        decision = 'u';
        starving = false;
    }
    else if (getDown()==antsAppearance) {
        decision = 'd';
        starving = false;
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
    if (starving)
        this->setStarving(getStarving()+1);
    if (this-> getStarving() >= doodleBugStepsToStarvation) {
        kill();
        doodleWorld[this->getRow()][this->getColumn()] = emptySpaceAppearance;
        cout<<"Killed"<<endl;
    }

}

void displayWorld(char arr[worldSize][worldSize]);

int main(){
    srand(time(0));
    char next='y';
    int tempRow=0, tempColumn=0, sizeCheck;
    vector<ant> antsArray, tempAntsArray;
    vector<doodleBug> doodleBugsArray, tempDoodleBugArray;


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
        // Doodlebugs taking a step
        for (int i=0; i<doodleBugsArray.size();i++) {
            doodleBugsArray[i].move();
            doodleBugsArray[i].lookAround();
        }
        //Ants taking a step
        for (int i=0; i<antsArray.size();i++) {
            antsArray[i].move();
            antsArray[i].lookAround();
        }
        /*/ants breed
        for (int i=0; i<antsArray.size();i++) {
            if (antsArray[i].getStepsAlive()% antStepsToBreed == 0)
                antsArray.push_back(antsArray[i].breed());
        }*/
        // updating vector of surviving and new ants
        for (int i=0; i<antsArray.size();i++){
            if (antsArray[i].lifeCheck())
                tempAntsArray.push_back(antsArray[i]);
        }
        sizeCheck = antsArray.size() - tempAntsArray.size();
        antsArray=tempAntsArray;
        tempAntsArray.clear();
        cout<<" erased "<<sizeCheck<<" ants."<<endl;

        // updating vector of surviving and new bugs
        for (int i=0; i<doodleBugsArray.size();i++){
            if (doodleBugsArray[i].lifeCheck())
                tempDoodleBugArray.push_back(doodleBugsArray[i]);
        }
        doodleBugsArray=tempDoodleBugArray;
        tempDoodleBugArray.clear();



        displayWorld(doodleWorld);
        cout << "To move one step further press y" << endl;
        cin>>next;

    }


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




