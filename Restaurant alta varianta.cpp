#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <exception>
#include <memory>


class TooManyCostumers: public std::exception{
public:
    TooManyCostumers() = default;

    const char *what() const noexcept override {
        return "There aren't enough available seats\n";
    }
};

class NoFreeWaiters: public std::exception{
public:
    NoFreeWaiters() = default;

    const char *what() const noexcept override {
        return "There aren't available waiters at the moment. Please wait!\n";
    }
};

class Restaurant{
protected:
    int NrSeats;
    static int NrFree;
    std::vector<std::string>menu;
    std::vector<std::string>vegmenu;

public:
    explicit Restaurant(int NrSeats_){
        this->NrSeats = NrSeats_;
        Restaurant::NrFree = NrSeats_;

        menu.emplace_back("ciorba de vacuta");
        menu.emplace_back("supa crema de ciuperci");
        menu.emplace_back("schnitzel cu cartofi prajiti");
        menu.emplace_back("pizza 4 formaggi");
        menu.emplace_back("pizza capriciosa");
        menu.emplace_back("paste carbonara");
        menu.emplace_back("paste bologneze");
        menu.emplace_back("clatite cu ciocolata");
        menu.emplace_back("papanasi");

        vegmenu.emplace_back("Ratatouille");
        vegmenu.emplace_back("Conopida la cuptor");
        vegmenu.emplace_back("Chili Vegan");
        vegmenu.emplace_back("Paste cu ciuperci");
        vegmenu.emplace_back("Chiftele vegetariene cu cartofi la cuptor");
        vegmenu.emplace_back("Ciorba de fasole");
        vegmenu.emplace_back("Dovlecei la gratar");
        vegmenu.emplace_back("pizza 4 formaggi");

    }
    Restaurant(const Restaurant &R){
        this->NrSeats = R.NrSeats;
        Restaurant::NrFree = Restaurant::NrFree;
        this->menu = R.menu;
        this->vegmenu = R.vegmenu;

    }
    virtual ~Restaurant()=default;
    void set_NrSeats(int NrSeats_){
        NrSeats = NrSeats_;
    };

    static void set_NrFree(int NrFree_){
        NrFree = NrFree_;
    };

    const std::vector<std::string> &getMenu() const {
        return menu;
    }

    const std::vector<std::string> &getVegmenu() const {
        return vegmenu;
    }

    static void TakeSeats(int nr_customers){
        try{
            if(NrFree-nr_customers<0){
                throw TooManyCostumers();
            }
            std::cout<<"The Customers are seated\n";
        }
        catch(const TooManyCostumers &e){
            std::cout<<e.what()<<'\n';
        }

    }
    friend std::ostream &operator<<(std::ostream &os, const Restaurant &R){
        os<<"The restaurant has "<<R.NrSeats<<" seats in total.\n"<<"At the moment the restaurant has "<<Restaurant::NrFree<<" available seats.\n";
        return os;
    }
    void show_menu()const {
        std::cout<<"Meniul normal este:";
        for(int i = 0; i < menu.size(); i++) {
            std::cout << i << " - " << menu[i] << "\n";
        }
        std::cout<<"Meniul vegetarian este:";
        for(int i = 0; i < vegmenu.size(); i++) {
            std::cout << i << " - " << vegmenu[i] << "\n";
        }
    }
};



enum class CustomerType {
    EatsMeat,
    Vegetarian
};

class Customer{
private:
    static std::string name;

public:
    explicit Customer(std::string name_){
        Customer::name = name_;
    }
    Customer(const Customer &C){
        Customer::name = Customer::name;
    }
    virtual ~Customer() =default;

    static const std::string &getName()  {
        return name;
    }

    void setName(const std::string &name_) {
        Customer::name = name_;
    }
    virtual CustomerType getType() const=0;

    virtual void print(std::ostream &os) const {

        os << name << " ordered " << "\n";//?
    }
    friend std::ostream &operator<<(std::ostream &os, Customer *C){
        C->print(os);
        return os;
    }

};


class MeatCustomer:public Customer{
private:
    static std::string order;


public:
    MeatCustomer(std:: string order_,std::string name_):Customer(name_){
        MeatCustomer::order = order_;
    }

    MeatCustomer(const MeatCustomer &M) :Customer(M){
        MeatCustomer::order = MeatCustomer::order;
    }
    virtual ~MeatCustomer()=default;

    static const std::string &getOrder() {
        return order;
    }

    static void setOrder(const std::string &order_) {
        MeatCustomer::order = order_;
    }
    void print(std::ostream &os) const override {
        Customer::print(os);
        std::cout << order << ".\n";
    }
    friend std::ostream &operator<<(std::ostream &os, const MeatCustomer &meat) {
        meat.print(os);
        return os;
    }

    CustomerType getType() const override {
        return CustomerType::EatsMeat;
    }

};

class VegCustomer:public Customer{
private:
    static std::string vegorder;


public:
    VegCustomer(std:: string vegorder_,std::string name_):Customer(name_){
        VegCustomer::vegorder = vegorder_;
    }

    VegCustomer(const VegCustomer &V) :Customer(V){
        VegCustomer::vegorder = VegCustomer::vegorder;
    }
    virtual ~VegCustomer()=default;

    static const std::string &getVegOrder() {
        return vegorder;
    }

    static void setVegOrder(const std::string &vegorder_) {
        VegCustomer::vegorder = vegorder_;
    }
    void print(std::ostream &os) const override {
        Customer::print(os);
        std::cout << "The customer ordered " << vegorder << ".\n";
    }
    friend std::ostream &operator<<(std::ostream &os, const VegCustomer &veg) {
        veg.print(os);
        return os;
    }
    CustomerType getType() const override {
        return CustomerType::Vegetarian;
    }
};
class Order{
protected:
    static std::vector<std::shared_ptr<Customer>> orders;

    Order() = default;

public:

    static const std::vector<std::shared_ptr<Customer>>& getCustomers() {
        return orders;
    }

    static void addCustomer(const std::shared_ptr<Customer> &customer) {
        orders.push_back(customer);
    }

    static void printAllOrders() {
        for (auto &customer : orders)
            std::cout << customer << '\n';
    }
};

//std::vector<std::shared_ptr<Customer>> Order::orders;

class Kitchen: public Order, public Restaurant{
private:
    int NrWaiters;
    int NrFreeWaiters;
public:
    Kitchen(int NrWaiters_,int NrSeats_)
            :Restaurant(NrSeats_){
        this->NrWaiters = NrWaiters_;
        this->NrFreeWaiters = NrWaiters;
    }
    Kitchen(const Kitchen &K) : Order(K), Restaurant(K) {
        this->NrWaiters = K.NrWaiters;
        this->NrFreeWaiters = K.NrFreeWaiters;
    }
    virtual ~Kitchen()=default;

    static bool prepare_order(const std::string& answear){
        if(answear == "no"){
            std::cout<<"The food is not ready yet!\n";
            return false;
        }
        else{
            std::cout<<"The food is ready!\n";
            return true;
        }

    }
    void send_order(){
        std::string answear;
        if(prepare_order(answear)){
            orders.pop_back();
            NrFree += 1;
            NrFreeWaiters +=1;
            std::cout<<"The food was sent to the table!\n";
        }
    }

    bool waiters() const{
        try{
            if(NrFreeWaiters==0){
                throw NoFreeWaiters();
            }
            else{
                std::cout<<"This table has a waiter now\n";
                NrFree-=1;
                return true;
            }

        }
        catch(const NoFreeWaiters &e){
            std::cout<<e.what()<<'\n';
            return false;
        }
    }
    friend std::istream &operator>>(std::istream &in, Kitchen &K){
        in>>K.NrWaiters>>K.NrFreeWaiters;
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, Kitchen &K){
        out<<"The restaurant has "<<K.NrWaiters<<" waiters in total.\n"<<"At the moment the restaurant has "<<K.NrFreeWaiters<<" available waiters.\n";
        return out;
    }

};

int main() {

    int n,nr_customers;
    std::cin>>n;
    Restaurant R(20);
    while(n!=0)
    {
        std::cout<<"Buna ziua!Doriti o masa pentru cate persoane?\n";
        std::cin>>nr_customers;
        Restaurant::TakeSeats(nr_customers);
        while(nr_customers!=0){
            std::string tip,nume,comanda;
            R.show_menu();
            std::cin>>tip;
            if(tip == "Vegetarian"){
                std::cin>>nume>>comanda;
                auto customer = std::make_shared<VegCustomer>(nume,comanda);
                Order::addCustomer(customer);
            }
            else{
                std::cin>>nume>>comanda;
                auto customer = std::make_shared<MeatCustomer>(nume,comanda);
                Order::addCustomer(customer);
            }
        }
        Kitchen K(7,20);
        if(!K.waiters()){
            std::string raspuns;
            do{
                std::cin>>raspuns;
                Kitchen::prepare_order(raspuns);
            }
            while(!Kitchen::prepare_order(raspuns));
            K.send_order();
        }
        else{
            K.waiters();
            std::string raspuns;
            do{
                std::cin>>raspuns;
                Kitchen::prepare_order(raspuns);
            }
            while(!Kitchen::prepare_order(raspuns));
            K.send_order();
        }
    }
    std::cout<<"B";

    return 0;
}
