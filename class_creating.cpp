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
