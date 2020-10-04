#include<iostream>
#include<vector>

using namespace std;
int digit_to_int(char c);


class Money{
public:
    friend Money operator +(const Money& amount1, const Money& amount2);
    friend Money operator -(const Money& amount1, const Money& amount2);
    friend Money operator -(const Money& amount);
    friend bool operator ==(const Money& amount1, const Money& amount2);
    friend bool operator <(const Money& amount1, const Money& amount2);

    Money (long dollars, int cents);
    Money (long dollars);
    Money();
    double get_value() const;
    friend istream& operator>>(istream& ins, Money& amount);
    friend ostream& operator<<(ostream& outs, Money& amount);
private:
    long all_cents;

};
//Add two amounts
Money operator +(const Money& amount1, const Money& amount2){
    Money temp;
    temp.all_cents = amount1.all_cents+amount2.all_cents;
    return temp;

}
//Subtract two amounts
Money operator -(const Money& amount1, const Money& amount2){
    Money temp;
    temp.all_cents=amount1.all_cents-amount2.all_cents;
    return temp;

}
//Determine if two amounts are equal
bool operator ==(const Money& amount1, const Money& amount2){
    return amount1.all_cents==amount2.all_cents;
}
//Compare two amounts
bool operator <(const Money& amount1, const Money& amount2){
    return amount1.all_cents<amount2.all_cents;
}
//Return the negative value of the amount
Money operator -(const Money& amount){
    Money temp;
    temp.all_cents=-amount.all_cents;
    return temp;
}
//Initialize with dollars and cents
Money:: Money (long dollars, int cents){
    if (dollars* cents <0) {
        cout << "Illegal values for dollars and cents.\n";
        exit(1);
    }
    all_cents = dollars*100+cents;
}
//Initialize with dollars only
Money:: Money (long dollars): all_cents(dollars*100){
    //blank
    }
//Initialize by default
Money:: Money (): all_cents(0){
    //Blank
    }
// get_value
double Money::get_value() const{
    return all_cents*0.01;
}

//Istream
istream& operator>>(istream& ins, Money& amount){
    char one_char, decimal_point, digit1, digit2; //digits for the amount of cents
    long dollars;
    int cents;
    bool negative; //set to true if input is negative
    ins>> one_char;
    if (one_char=='-'){
        negative = true;
        ins >> one_char; //read '$'
    }
    else
        negative=false;
    //if input is legal then one_char == '$'
    ins>>dollars>>decimal_point>>digit1>>digit2;
    if (one_char != '$' || decimal_point != '.'|| !isdigit(digit1)|| !isdigit(digit2)){
        cout<<" Error illegal form of money input\n";
        exit(1);
    }
    cents = digit_to_int(digit1) *10 + digit_to_int(digit2);
    amount.all_cents = dollars*100 + cents;
    if (negative)
        amount.all_cents= -amount.all_cents;
    return ins;

}
// from book
int digit_to_int(char c){
    return (static_cast<int>(c) - static_cast<int>('0'));
}
// Ostream
ostream& operator<<(ostream& outs, Money& amount){
    long positive_cents, dollars, cents;
    positive_cents = labs(amount.all_cents);
    dollars = positive_cents/100;
    cents = positive_cents%100;

    if (amount.all_cents<0)
        outs <<"- $"<<dollars<<'.';
    else
        outs<<"$"<<dollars<<'.';

    if (cents <10)
        outs<<'0';
    outs<<cents;
    return outs;
}

class check{
public:
    check();
    check(int checkNumber, Money checkAmount, bool isCashed);
    friend istream& operator>>(istream& ins, check theCheck);
    void setAmount(Money theAmount);
    void setCashed(bool isCashed);
    void setNumber(int checkNumber);
    void printAmount();
    Money getAmount();
    bool getCashed();
    int getCheckNumber();
private:
    int number;
    Money amount;
    bool cashed;

};

void check::setAmount(Money theAmount){
    amount=theAmount;

}
void check::setNumber(int checkNumber){
    number=checkNumber;

}
void check::setCashed(bool isCashed){
    cashed=isCashed;

}

void check::printAmount() {
    cout<<amount;
}
int check::getCheckNumber() {
    return number;
}

bool check::getCashed() {
    return cashed;
}

Money check::getAmount() {
    return amount;
}

istream& operator>>(istream& ins, check theCheck){
    int checkNumber;
    Money checkAmount;
    bool isCashed;
    ins>>checkNumber>>checkAmount>>isCashed;
    theCheck.number=checkNumber;
    theCheck.amount=checkAmount;
    theCheck.cashed=isCashed;

    return ins;
}
check::check():number(1),amount(),cashed(false){}
check::check(int checkNumber, Money checkAmount, bool isCashed){
    number = checkNumber;
    amount=checkAmount;
    cashed=  isCashed;
}

Money sumDepositMoney(vector<Money> arr);
Money sumChecksMoney(vector<check> arr);
int main(){
    Money currentBalance, oldBalance, realBalance, totalCashedChecks, totalDeposits, tempAmount;
    Money difference;
    string comparingBalances;
    char answer1, answer2;
    int tempNumber;
    float tempAmt;
    bool tempCashed;
    vector<check> cashedChecksArr, uncashedChecksArray;
    vector<Money> deposits;

    //obtaining old balance
    cout<<"Enter the balance as of last time you balanced your checkbook including '$' sign and cents, for example $100.45 or $1.00:"<<endl;
    cin>>oldBalance;
    //obtaining current balance
    cout<<"Enter the current account balance including '$' sign and cents, for example $100.45 or $1.00:"<<endl;
    cin>>currentBalance;
    //obtaining deposit information
    cout<<"Have you made any deposits since last time you balanced your checkbook? Enter 'Y' or 'y for YES and any other character for NO?"<<endl;
    cin>>answer1;
    while (answer1 =='Y' || answer1== 'y'){
        cout<<"What was the deposit amount including '$' sign and cents, for example $100.45 or $1.00?"<<endl;
        cin>>tempAmount;
        deposits.push_back(tempAmount);
        cout<<"have you made any other deposits? Enter 'Y' or 'y for YES and any other character for NO?"<<endl;
        cin>>answer1;
    }
    //obtaining check writing information
    cout<<"Did you write any checks since last time you balanced your checkbook? Enter 'Y' or 'y for YES and any other character for NO?"<<endl;
    cin>>answer2;
    while (answer2 == 'Y' || answer2 =='y'){
        cout<<"Please enter the check information in the following format: number(ex: 1001) amount(ex: 128.32 or 30) cashed(ex: 1 for true or 0 for false):"<<endl;
        cin>>tempNumber>>tempAmt>>tempCashed;
        tempAmount=Money((tempAmt*100)/100,int(tempAmt*100)%100);
        check tempCheck(tempNumber, tempAmount, tempCashed);
        if (tempCheck.getCashed() == 1)
            cashedChecksArr.push_back(tempCheck);
        else
            uncashedChecksArray.push_back(tempCheck);
        cout<<"Do you have any additional checks to disclose? Enter 'Y' or 'y for YES and any other character for NO?"<<endl;
        cin>>answer2;
    }


    totalCashedChecks = sumChecksMoney(cashedChecksArr);
    totalDeposits = sumDepositMoney(deposits);
    realBalance = oldBalance + totalDeposits - totalCashedChecks;
    if (realBalance<currentBalance){
        comparingBalances = "higher";
        difference = currentBalance - realBalance;
    }
    else{
        comparingBalances = "lower";
        difference =  realBalance - currentBalance;
    }



    cout<<"The total of checks cashed is:"<<totalCashedChecks<<endl;
    cout<<"Total deposits are:"<<totalDeposits<<endl;
    cout<<"New balance should be:"<<realBalance<<endl;
    cout<<"The balance displayed by the bank is "<<difference<<" "<<comparingBalances<<" than what it should be."<<endl;
    cout<<endl<<endl<<"The checks cashed since the last time you balanced your checkbook are:"<<endl;
    cout<<"Check Number\tAmount"<<endl;
    for (int i=0;i<cashedChecksArr.size();i++){
        cout<<cashedChecksArr[i].getCheckNumber()<<"\t\t";
        cashedChecksArr[i].printAmount();
        cout<<endl;
    }

    cout<<endl<<endl<<"The checks still not cashed since the last time you balanced your checkbook are:"<<endl;
    cout<<"Check Number\tAmount"<<endl;
    for (int i=0;i<uncashedChecksArray.size();i++){
        cout<<uncashedChecksArray[i].getCheckNumber()<<"\t\t";
        uncashedChecksArray[i].printAmount();
        cout<<endl;
    }

    return 0;
}


Money sumDepositMoney(vector<Money> arr){
    Money temp;
    for (int i=0;i<arr.size();i++)
        temp=temp+arr[i];
    return temp;
}

Money sumChecksMoney(vector<check> arr){
    Money temp;
    for (int i=0;i<arr.size();i++)
        temp = temp + arr[i].getAmount();
    return temp;
}
