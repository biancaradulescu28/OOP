#include <iostream>
#include <string>
using namespace std;

class Nod{
private:
    char info;
    Nod *next;
public:
    Nod();
    Nod(char);
    void setInfo(char date);
    void setNext(Nod *urm);
    char getInfo() const;
    Nod *getNext() const;
    ~Nod();

};
Nod::Nod(){
    this->info = 0;
    this->next = nullptr;
}
Nod::Nod(char c){
    info = c;
    next = nullptr;
}

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
Nod::~Nod(){
    delete next;
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
        vf = vf -> getNext();
        delete curent;
    }
    delete vf;
}

void Stiva_de_caractere::push(char c){

    if(vf == nullptr)
    {
        Nod *nou = new Nod();
        nou -> setInfo(c);
        vf = nou;

    }
    else {
        Nod *nou = new Nod();
        nou->setNext(vf);
        nou->setInfo(c);
        vf = nou;
    }
}

void Stiva_de_caractere::pop(){
    if(vf == nullptr){cout<<"Stiva goala\n";}
    else{
        vf = vf -> getNext();
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
    while(nr){
        in>>c;
        s.push(c);
        nr--;
    }
    return in;
}

ostream& operator<< (ostream& out, Stiva_de_caractere &s)
{
    while(s.isempty()!=0)
    {
        out<<s.getVarf()->getInfo();
        s.pop();
    }
    return out;
}
string Stiva_de_caractere::inversare(string &inv){

    int i,n;
    n = inv.size();
    for(i=0;i<n;i++){
        push(inv[i]);//abc=>[a,b,c]-vf
    }
    inv.clear();//gol
    for(i=0;i<n;i++){
        inv.push_back(getVarf()->getInfo());
        pop();
    }
    return inv;

}

Stiva_de_caractere Stiva_de_caractere::operator-(Stiva_de_caractere &S1){
    Stiva_de_caractere S2;
    while(isempty() != 0 && S1.isempty() != 0) {
            if (getVarf()->getInfo() > S1.getVarf()->getInfo()) {
                S2.push(getVarf()->getInfo());
                top();
                pop();
                S1.pop();
                S2.top();
            }
            else {
            S2.push(S1.getVarf()->getInfo());
            S1.top();
            pop();
            S1.pop();
            S2.top();
            }
    }
    return S2;
}


int main(){
    char chr;
    string s,sir;

    Stiva_de_caractere S1,S2,S3,S4,S5;
    if(S1.isempty() == 1){cout<<"S1 nu e goala\n";}
    else cout<<"S1 e goala\n";
    cout<<"insereaza caracter";
    cin>>chr;
    S1.push(chr);
    if(S1.isempty() == 1){cout<<"S1 nu e goala\n";}
    else cout<<"S1 e goala\n";
    S1.top();
    cout<<"Pop";
    S1.pop();
    if(S1.isempty() == 1){cout<<"S1 nu e goala\n";}
    else cout<<"S1 e goala\n";
    cout<<"insereaza sir pentru testarea functiei de inversare";
    cin>>s;
    sir = S2.inversare(s);
    cout<<"Inversul sirului s este "<<sir<<"\n";
    cout<<"insereaza caracter";
    cin>>chr;
    S1.push(chr);
    cout<<"insereaza caracter";
    cin>>chr;
    S1.push(chr);
    if(S1.isempty() == 1){cout<<"S1 nu e goala\n";}
    else cout<<"S1 e goala\n";
    S1.top();
    cout<<"Supraincarcarea operatorului << "<<S1<<"\n";
    cout<<"insereaza prima sitiva pentru scadere";
    cin>>S3;
    cout<<"insereaza a doua stiva pentru scadere";
    cin>>S4;
    S3-S4 = S5;
    if(S5.isempty() == 1){cout<<"S5 nu e goala\n";}
    else cout<<"S5 e goala\n";
    cout<<"Supraincarcarea operatorului - este:"<<S5<<"\n";//nu afiseaza

    return 0;

}

/*
6
e x a m e n
12
p o o l a b o r a t o r
 */
