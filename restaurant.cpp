#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include <utility>

using namespace std;

class TooManyCostumers: public exception{
public:
    TooManyCostumers() = default;

    const char *what() const noexcept override {
        return "Prea multi clienti!\n";
    }
};

class NotInMenu:public exception{
public:
    NotInMenu() = default;

    const char *what() const noexcept override {
        return "Aceasta mancare nu se afla in meniu, alegeti altceva.\n";
    }
};

class Restaurant{
private:
    int NrSeats{};

protected:
    vector<string>menu;
    map<string,string>orders;
    static int NrFree;

public:
    explicit Restaurant(int NrSeats);
    Restaurant(const Restaurant &ob){
        this->NrSeats = ob.NrSeats;
    }
    virtual ~Restaurant();
    static void take_seats(int nr_customers);
    void show_menu();
    const vector<string> &getMenu() const;
    friend istream& operator>> (istream&, Restaurant&);
//    friend ostream& operator<< (ostream&, Restaurant&);

};

Restaurant::Restaurant(int NrSeats){

    cout<<"Cate locuri are restaurantul?\n";
    NrSeats = 0;
    NrFree=NrSeats;

    menu.push_back("ciorba de vacuta");
    menu.push_back("supa crema de ciuperci");
    menu.push_back("snitzel cu cartofi prajiti");
    menu.push_back("pizza 4 formaggi");
    menu.push_back("pizza ");
    menu.push_back("paste carbonara");
    menu.push_back("paste bolog...");
    menu.push_back("clatite cu ciocolata");
    menu.push_back("papanasi");
}
Restaurant::~Restaurant(){
    NrSeats=0;
    NrFree=0;
    menu.clear();
    orders.clear();
}

void Restaurant::take_seats(int nr_customers){
    if(NrFree-nr_customers<0){
        throw TooManyCostumers();
    }
    else{
        NrFree=NrFree-nr_customers;
        cout<<"Clientii s-au asezat\n";
    }

}
void Restaurant::show_menu(){
    cout<<"Meniul este:";
    for(int i = 0; i < menu.size(); i++) {
        cout << i << " - " << menu[i] << "\n";
    }

}

const vector<string> &Restaurant::getMenu() const {
    return menu;
}
istream& operator>> (istream& in,Restaurant& r)
{
    in>>r.NrSeats;
    return in;
}


//restaurant stop

class Kitchen: public Restaurant{
private:
    map<string,string>commands;

public:
    explicit Kitchen(int NrSeats);
    virtual ~Kitchen();
    void receive_orders();
    static bool prepare_order(string raspuns);
    static void send_order();
//    string &operator[](int i){
//        if(i>commands.size()){
//            cout<<"index out of bounds\n";
//            return commands[0];
//        }
//        return commands[i];
//    }
//    Kitchen(const Kitchen &ob){
//        int i=0;
//        while(i<commands.size()){
//            this->commands[i]->first = ob.commands[i]->first;
//            this->commands[i]->second = ob.commands[i]->second;
//            i++;
//        }
//    }

};
Kitchen::Kitchen(int NrSeats):Restaurant(NrSeats){};
Kitchen::~Kitchen(){
    commands.clear();
}

void Kitchen::receive_orders(){
    map<string, string>::iterator itr;
    itr = orders.begin();
    commands.insert(pair<string, string>(itr->first,itr->second));
    orders.erase(itr->first);
    cout<<"A fost primita comanda\n";
}

bool Kitchen::prepare_order(string raspuns){
    cin>>raspuns;
    while(raspuns[0]=='n')
    {
        cout<<"Mancarea nu este gata.\n";
    }
    return true;
}

void Kitchen::send_order(){
    if(static_cast<bool>(Kitchen::prepare_order)){
        NrFree+=1;
    }
    cout<<"Mancarea a fost trimisa!\n";
}


class Customer:public Restaurant{
private:
    string name;

public:
    Customer(string name, int NrSeats);

    Customer(const Customer &ob) : Restaurant(ob) {
        this->name = ob.name;
    }
    ~Customer() override =default;
    void choice(int order);
    friend ostream& operator<< (ostream&, Customer&);
    friend istream& operator>> (istream&, Customer&);


};

Customer::Customer(string name,int NrSeats) : Restaurant(NrSeats),name(std::move(name)){}
void Customer::choice(int order){
    cout<<"Numarul felului dorite este:";
    cin>>order;
    while(order>getMenu().size())
    {
        throw NotInMenu();
    }
    orders.insert(pair<string, string>(name, menu[order]));
    cout<<"As dori"<<menu[order]<<"\n";

}
ostream& operator<< (ostream& out, Customer& c)
{
    out<<c.name<<"\n";
    return out;
}
istream& operator>> (istream& in,Customer& c)
{
    in>>c.name;
    return in;
}


int main() {

    int nr_customers,nr=0,i, order = 0,locuri=0;
    string nume,raspuns;
    Restaurant Vladimir = Restaurant(locuri);
    cin>>Vladimir;

    while(nr!=5){

        cout<<"Buna ziua!\nCate persoane sunteti?\n";
        cin>>nr_customers;

        Vladimir.take_seats(nr_customers);
        Vladimir.show_menu();

        i=1;
        while(i<=nr_customers)
        {
            string name;
            Customer C = Customer(name,locuri);
//            Restaurant *Vladimir = new Customer(nume);
//            Customer *c = dynamic_cast<Customer&>(Vladimir);
            cin>>C;
            cout<<"Ce ai dori sa mananci "<<C<<"?\n";
            C.choice(order);
        }
        Kitchen K = Kitchen(0);
        K.receive_orders();
        cout<<"Este gata comanda?\n";
        K.prepare_order(raspuns);
        K.send_order();

        nr++;

    }

    return 0;
}
