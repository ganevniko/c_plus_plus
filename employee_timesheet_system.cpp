#include <fstream>
#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;
const double MINIMUM_WAGE= 7.50;
class employee{
public:
    employee();
    explicit employee(string Name);
    employee(string Name, int id);
    employee(string Name, int id, double rate);
    void setId(int a);
    int getId() const;
    void setName(string newName);
    string getName();
    void setHourlyRate(double rate);
    double getHourlyRate();
private:
    string name;
    int Id;
    double hourlyRate;

};

employee::employee(){
    name = "John Doe";
    Id = 0;
    hourlyRate = MINIMUM_WAGE;

}
employee::employee(string Name){
    name = Name;
    Id = 0;
    hourlyRate = MINIMUM_WAGE;
}
employee::employee(string Name, int id){
    name = Name;
    Id = id;
    hourlyRate = MINIMUM_WAGE;
}
employee::employee(string Name, int id, double rate){
    name = Name;
    Id = id;
    hourlyRate = rate;
}



void employee::setId(int a){
    Id = a;
}
int employee::getId() const {
    return Id;
}

void employee::setName(string newName){
    name = newName;
}
string employee::getName() {
    return name;
}
void employee::setHourlyRate(double rate){
    hourlyRate = rate;
}
double employee::getHourlyRate() {
    return hourlyRate;
}

struct Node {
    employee *data;
    Node *next;
    Node *prev;

};
typedef Node* NodePtr;

class LinkedList{
private:
    NodePtr head;
public:
    LinkedList(){
        head = nullptr;
    }
    void addNode(string Name,int id, double rate);
    NodePtr getHead(){
        return head;
    }
};


void LinkedList::addNode(string Name,int id, double rate){
    employee *emp = new employee(Name,id,rate);
    NodePtr nod = new Node;
    nod->data = emp;
    nod->next = nullptr;
    nod->prev = nullptr;
    if (head == nullptr){
        head = nod;
        return;
    }
    else {
        NodePtr p = head;
        while(p->next != nullptr)
            p = p->next;
        p->next = nod;
        nod->prev = p;
    }
}





int main(){


    ifstream finEmployees, finTimeSheets;
    int id, count=0, employeesCount =0;
    int hours[100], ids[100];
    char employeeFile[100], timeSheetFile[100];
    string firstName, lastName, middleInitial;
    LinkedList list;
    double rate;
    cout<<"Enter the employee file name with extension for example employeeFile.txt"<<endl;
    cin>>employeeFile;
    cout<<"Enter the time sheet file name with extension for example timeSheetFile.txt"<<endl;
    cin>>timeSheetFile;


    finEmployees.open(employeeFile);
    if (finEmployees.fail()){
        cout << "Error opening file"<<endl;
        return 0;
    }

    while(finEmployees >> id >> rate >> firstName){
        string temp;
        finEmployees>>temp;
        if (temp[1]=='.') {
            middleInitial = temp;
            finEmployees >> lastName;
            string name = firstName + " "+ middleInitial+ " " + lastName;
            list.addNode(name, id,rate);
            employeesCount++;
        }
        else {
            lastName=temp;
            string name = firstName + " " + lastName;
            list.addNode(name, id,rate);
            employeesCount++;
        }

    }
    finEmployees.close();
    finTimeSheets.open(timeSheetFile);
    if (finTimeSheets.fail()){
        cout << "Error opening file"<<endl;
        return 0;
    }

    while(finTimeSheets >> ids[count] >> hours[count])
        count++;
    NodePtr nod = list.getHead();
    string fullNames[employeesCount];
    double totalEarnings[employeesCount];
    while(nod!= nullptr){
        double earnings = 0;
        for (int i = 0; i<count; i++){
            if (nod->data->getId() == ids[i]){
                earnings = earnings + nod->data->getHourlyRate() * hours[i];
            }
        }
        int i=0;
        while (totalEarnings[i]>=earnings)
            i++;
        if (i!=employeesCount-1) {
            for (int j = employeesCount - 2; j >= i; j--) {
                totalEarnings[j+1]=totalEarnings[j];
                fullNames[j+1]=fullNames[j];
            }
        }
        totalEarnings[i]=earnings;
        fullNames[i]=nod->data->getName();
        nod= nod->next;
    }
    finTimeSheets.close();
    
    cout << "************ Payroll Information ************"<<endl;
    for (int i=0;i<employeesCount;i++){
        cout<<fullNames[i]<<" $"<<totalEarnings[i]<<endl;
    }
    cout<< "**************** End Payroll ****************"<<endl;
    return 0;
}



