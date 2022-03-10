#include <iostream>
#include <string>
using namespace std;

class Nod{
private:
    char info;
    Nod *next;
public:
    Nod();
    explicit Nod(char);//dc explicit?
    void setInfo(char date);
    void setNext(Nod *urm);
    char getInfo() const;
    Nod *getNext() const;

};
Nod::Nod(){
    this->info = 0;
    this->next = nullptr;//dc nu e NULL??
}
Nod::Nod(char info){
    this->info = info;
    this->next = nullptr;
}//????

void Nod::setInfo(char date) {
    Nod::info = date;
}

void Nod::setNext(Nod *urm) {
    Nod::next = urm;
}

char Nod::getInfo() const {
    return info;
}

Nod *Nod::getNext() const {
    return next;
}


class Stiva_de_caractere{
private:
    Nod* vf;
public:
    Stiva_de_caractere();
    ~Stiva_de_caractere();
    Nod *getVarf() const;
    void pop();
    void push(char);
    int isempty();
    void top();
    friend istream& operator>> (istream&, Stiva_de_caractere&);
    friend ostream& operator<< (ostream&, Stiva_de_caractere&);
    string inversare(string&);
    Stiva_de_caractere operator-(Stiva_de_caractere&);


};

Stiva_de_caractere::Stiva_de_caractere(){
    vf = nullptr;
}

Nod *Stiva_de_caractere::getVarf() const {
    return vf;
}
Stiva_de_caractere::~Stiva_de_caractere(){

    while (vf != nullptr){
        Nod *curent = vf;
        vf = vf -> getNext();//delete?

    }
}

void Stiva_de_caractere::push(char c){

    Nod *nou = new Nod();
    nou -> setInfo(c);
    nou -> setNext(vf);
    vf = nou;

//    delete nou;//trebuie? nu merge bine
}

void Stiva_de_caractere::pop(){//corect?
    if(vf == nullptr){cout<<"Stiva goala\n";}
    else{
        Nod *iese = vf;
        vf = vf -> getNext();
        cout<<iese->getInfo()<<"\n";
    }
}

int Stiva_de_caractere::isempty(){

    if(vf == nullptr){
        return 0;
    }
    else return 1;
}

void Stiva_de_caractere::top(){
    cout<<"varful este "<<vf ->getInfo()<<"\n";
}

istream& operator>> (istream& in, Stiva_de_caractere& s)
{
    char c;
    int nr;
    in>>nr;
    while(nr>0){
        in>>c;
        s.push(c);
        nr--;
    }
    return in;
}

ostream& operator<< (ostream& out, Stiva_de_caractere &s)//nu afiseaza
{
    while(!s.isempty())
    {
        out<<s.getVarf()->getInfo();
        s.pop();
    }
    return out;
}
string Stiva_de_caractere::inversare(string &inv){//nu returneaza ce trb

    int i,n;
    n = inv.size();
    for(i=0;i<n;i++){
        push(inv[i]);//abc=>[a,b,c]-vf
    }
    inv.clear();//gol
    for(i=0;i<n;i++){
        inv.push_back(getVarf()->getInfo());//cba?
        pop();
    }
    return inv;

}

Stiva_de_caractere Stiva_de_caractere::operator-(Stiva_de_caractere &stiva){
    Stiva_de_caractere S;
    while(!isempty() || !stiva.isempty()){

        if(getVarf()->getInfo()> stiva.getVarf()->getInfo()){
            S.push(getVarf()->getInfo());
            pop();
            stiva.pop();
        }
        else {
            S.push(stiva.getVarf()->getInfo());
            pop();
            stiva.pop();
        }
    }
    return S;
}


int main(){
    char chr;
    string s,sir;

    Stiva_de_caractere S1,S2,S3,S4,S5;
    if(S1.isempty() == 1){cout<<"S1 nu e goala\n";}
    else cout<<"S1 e goala\n";
    cin>>chr;
    S1.push(chr);
    if(S1.isempty() == 1){cout<<"S1 nu e goala\n";}
    else cout<<"S1 e goala\n";
    S1.top();
    S1.pop();
    if(S1.isempty() == 1){cout<<"S1 nu e goala\n";}
    else cout<<"S1 e goala\n";
    cin>>chr;
    cin>>chr;
    cout<<"Supraincarcarea operatorului <<"<<S1<<"\n";
    cin>>s;
    sir = S2.inversare(s);
    cout<<"Inversul sirului s este "<<sir<<"\n";

    cin>>S3;
    cout<<S3;
    cin>>S4;
    S5 = S3-S4;
    cout<<"Supraincarcarea operatorului - este:"<<S5<<"\n";

//    S3.push('E');
//    S3.push('X');
//    S3.push('A');
//    S3.push('M');
//    S3.push('E');
//    S3.push('N');
//
//    S4.push('P');
//    S4.push('O');
//    S4.push('O');
//    S4.push('L');
//    S4.push('A');
//    S4.push('B');
//    S4.push('O');
//    S4.push('R');
//    S4.push('A');
//    S4.push('T');
//    S4.push('O');
//    S4.push('R');
}