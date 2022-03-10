#include <iostream>
#include <math.h>
using namespace std;


class nr_complex{
private:
    double r,im;
public:

    nr_complex();
    nr_complex(double,double);
    nr_complex(nr_complex&);
    ~nr_complex();

    void set_r(double);
    void set_im(double);
    double get_r(){return r;};
    double get_im(){return im;};

    void citire(istream &in);
    void afis();

    friend istream& operator>> (istream&, nr_complex&);
    friend ostream& operator<< (ostream &out, nr_complex& nc);

    double modul();

    friend nr_complex operator+(nr_complex&, nr_complex&);
    friend nr_complex operator*(nr_complex&, nr_complex&);
    friend nr_complex operator/(nr_complex&, nr_complex&);

};

nr_complex::nr_complex(){
    this->r=0;
    this->im=0;
}

nr_complex::nr_complex(double r, double im){
    this->r=r;
    this->im=im;
}
nr_complex::nr_complex(nr_complex &nc){
    this->r=nc.r;
    this->im=nc.im;
}
nr_complex::~nr_complex(){
    this->r=0;
    this->im=0;
}

void nr_complex::set_r(double a) {
    r=a;
}

void nr_complex::set_im(double b) {
    im=b;
}

void nr_complex::citire(istream &in){
    cout<<"Cititi partea reala: ";
    in>>r;
    cout<<"Cititi partea imaginara: ";
    in>>im;
}

void nr_complex::afis(){
    if (im==0) {
        cout<<r;
    }
    else{
        if (r==0){
            if(im>0) cout<<"i*"<<im;
            else cout<<"-i*"<<im;
        }
        else{
            if(im>0) cout<<r<<"+i*"<<im;
            else cout<<r<<"-i*"<<-im;
        }
    }
}

istream& operator>> (istream& in, nr_complex& nc)
{
    in>>nc.r>>nc.im;
    return in;
}

ostream& operator<< (ostream& out, nr_complex& nc)
{
    out<<nc.r<<"  "<<nc.im<<"\n";
    return out;
}

double nr_complex::modul(){
    return sqrt(r*r + im*im);
}

inline nr_complex operator+(nr_complex& x, nr_complex& y){
    nr_complex rez;
    rez.r=x.r+y.r;
    rez.im=x.im + y.im;
    return rez;
}

inline nr_complex operator*(nr_complex& x, nr_complex& y){
    nr_complex rez;
    rez.r=(x.r * y.r)-(x.im * y.im);
    rez.im=(x.r * y.im)+(x.im * y.r);
    return rez;
}

inline nr_complex operator/(nr_complex& x, nr_complex& y){
    nr_complex rez;
    rez.r=(x.r*y.r + x.im*y.im)/(y.r*y.r + y.im*y.im);
    rez.im=(x.im*y.r - x.r*y.im)/(y.r*y.r + y.im*y.im);
    return rez;
}

int main()
{
    nr_complex x,y;
    cin>>x;
    cin>>y;
    x.afis();
    cout<<"\n";
    y.afis();
    cout<<"\n";
    cout<<x.modul()<<"\n";
    (x+y).afis();
    cout<<"\n";
    (x*y).afis();
    cout<<"\n";
    (x/y).afis();

    return 0;
}