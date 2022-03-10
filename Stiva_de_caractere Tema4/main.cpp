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
    ~Nod();

};
Nod::Nod(){
    this->info = 0;
    this->next = nullptr;//dc nu e NULL??
}
Nod::Nod(char c){
    info = c;
    next = nullptr;
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
    Stiva_de_caractere operator-(Stiva_de_caractere& stiva){
        Stiva_de_caractere S;
        while(isempty() != 0 || stiva.isempty() != 0){

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

void Stiva_de_caractere::pop(){//corect?
    if(vf == nullptr){cout<<"Stiva goala\n";}
    else{
        Nod *iese = vf;
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

ostream& operator<< (ostream& out, Stiva_de_caractere &s)//nu afiseaza
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
        inv.push_back(getVarf()->getInfo());//cba?
        pop();
    }
    return inv;

}

//Stiva_de_caractere Stiva_de_caractere::operator-(Stiva_de_caractere &stiva){
//    Stiva_de_caractere S;
//    while(isempty() != 0 || stiva.isempty() != 0){
//
//        if(getVarf()->getInfo()> stiva.getVarf()->getInfo()){
//            S.push(getVarf()->getInfo());
//            pop();
//            stiva.pop();
//        }
//        else {
//            S.push(stiva.getVarf()->getInfo());
//            pop();
//            stiva.pop();
//        }
//    }
//    return S;
//}


int main(){
    char chr;
    string s,sir;

    Stiva_de_caractere S1,S2,S3,S4,S5,S6;
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
    cin>>s;
    sir = S2.inversare(s);
    cout<<"Inversul sirului s este "<<sir<<"\n";
    cin>>chr;
    S1.push(chr);
    cin>>chr;
    S1.push(chr);
    if(S1.isempty() == 1){cout<<"S1 nu e goala\n";}
    else cout<<"S1 e goala\n";
    cout<<"Supraincarcarea operatorului << "<<S1<<"\n";
    cin>>S3;
    cout<<S3<<"\n";
    S4.push('E');
    S4.push('X');
    S4.push('A');
    S4.push('M');
    S4.push('E');
    S4.push('N');
    cout<<S4<<"\n";
    if(S4.isempty() == 1){cout<<"S4 nu e goala\n";}
    else cout<<"S4 e goala\n";

    S5.push('P');
    S5.push('O');
    S5.push('O');
    S5.push('L');
    S5.push('A');
    S5.push('B');
    S5.push('O');
    S5.push('R');
    S5.push('A');
    S5.push('T');
    S5.push('O');
    S5.push('R');

    S6 = S4-S5;
    cout<<"Supraincarcarea operatorului - este:"<<S6<<"\n";



}