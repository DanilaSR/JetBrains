#include <iostream>

using namespace :: std;

struct polynom_static{
    double* koef;
    int n;
};


class Polynom{
public:
    double* koef;
    int n;
public:

    Polynom() {
        koef = new double[1];
        n = 1;
    }
    explicit Polynom(int n){
        koef = new double[n];
        this->n = n;
        this->koef = new double[n];
        for (int i = 0; i < n; i++){
            this->koef[i] = 0;
        }
    }

    Polynom (Polynom const &other) {
        n = other.get_size();
        this->koef = new double[n];
        for (int i = 0; i < n; i++) {
            this->koef[i] = other.koef[i];
        }
    }

    ~Polynom(){
        alloc(0);
    }

    double get_element(unsigned int i) const{
        return koef[i];
    }
    int get_size() const{
        return n;
    }
    Polynom operator* (Polynom& v) const{
        Polynom N (n + v.get_size() - 1);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < v.get_size(); j++)
                N.koef[i+j] += koef[i]*v.koef[j];
        }
        return N;

    }
    Polynom operator* (double a) const{
        Polynom b(n);
        b = *this;
        for (int i = 0; i < n; i++){
            b.koef[i] = b.koef[i] * a;
        }
        return b;
    }


    Polynom & operator= (const Polynom& a){
//        if (&a == this) {
//            return *this;
//        }
//        if (koef != nullptr){
//            delete[] koef;
//        }
//        n = a.n;
//        this->koef = new double[n];
//        for (int i = 0; i < n; i++){
//            (*this).koef[i] = a.koef[i];
//        }
//        return *this;
        if ( &a==this )
        {
            cerr << "Warning:  attempt to copy Polynomial onto self" << endl;
        }
        else {
            if( a.get_size()<=0 ) {
                alloc(0);
            } else {
                alloc(a.get_size());
                for (int i=0; i< n ; i++) {
                    koef[i] = a.koef[i];
                }
            }
        }
        return *this;
    };
    Polynom & operator= (double a){
        alloc(1);
        koef[0] = a;
        return *this;
    }
    Polynom & operator = (Polynom &&other)  noexcept {
        if (this != &other) {
            this->n = other.get_size();
            this->koef = other.koef;
            other.koef = nullptr;
        }
        return *this;
    }
    Polynom operator + (Polynom const &other) const {
        if (this->n == other.n){
            Polynom a(this->n);
            for (int i = 0; i < this->n; i++ )
                a.koef[i] = this->koef[i] + other.koef[i];
            return a;
        }
        if ( this->n > other.n) {
            Polynom a;
            a = *this;
            unsigned int delta;
            delta = this->n - other.n;
            for (int i = this->n - 1; i >= delta; i--)
                a.koef[i] = a.koef[i] + other.koef[i - delta];
            return a;
        }

        else {
            Polynom a;
            a = other;
            unsigned int delta = other.n - this->n;
            for (int i = other.n - 1; i >= delta; i--)
                a.koef[i] = a.koef[i] + this->koef[i - delta];
            return a;
        }

    }
    Polynom& operator+= (const Polynom& a){
        *this = *this + a;
        return *this;
    }

    Polynom operator - (Polynom const &other) const {
        return  other * (-1) + *this;
    }

    Polynom operator / (Polynom& p2) const{
        Polynom G;
        G = *this;
        if (p2.get_size() > G.n) {
            cout << "It's impossible";
            return G;
        }
        int delta;
        delta = G.n - p2.n;
        Polynom a(delta + 1);
        for (int i = 0; i < delta + 1; i++){
            Polynom temp (delta + 1);
            a.koef[i] = G.koef[i]/p2.koef[0];
            temp.koef[i] = a.koef[i];
            G = G -  p2 * temp;
        }
        return a;

    }

    int degree() const{
        return this->n - 1;
    }

    static double pow (double a, int b){      //функция возведения в степень
        for (int i = 1; i < b; i++)
            a *= a;
        return a;
    }
    double value (double x) const{
        double v = this->koef[n - 1];
        for (int i = 0; i < this->n - 1; i++){
            v += this->koef[i]*pow(x, this->degree() - i);
        }
        return v;

    };

    Polynom derivative() const //производная от А
    {
        Polynom Z(n - 1);
        for (int i = 0; i < n - 1; i++)
        {
            Z.koef[i] =(n - i - 1)*koef[i];
        }
        return Z;
    }

//    int setSize(int dgr){
//        if( dgr <0 ) {
//            cerr << "Error:  attempted to set a negative degree" << endl;
//            exit(1);
//        } else {
//            if( dgr !=0 ) {
//                koef = new double [dgr];
//                if( koef== nullptr ) {
//                    n = 1;
//                    cerr << "Warning:  unable to allocate enough space for list" << endl;
//                    exit(2); // this surely is reasonable.
//                } else {
//                    n = dgr;
//                }
//            }
//        }
//        return dgr;
//    }

    void alloc (int n0){
        if (n0 < 0)
            cout << "Error";
        else{
            if (n0 == 0) {
                delete[] this->koef;
                this->n = 0;
            }
            else {
                delete[] this->koef;
                this->koef = new double[n0];
                this->n = n0;
            }
        }
    }



    friend istream& operator>> (istream& is, const  Polynom &p);
    friend ostream& operator << (ostream &os, const Polynom &v);


};


Polynom operator* (double a, const Polynom& v) {
    for (int i = 0; i < v.get_size(); i++)
        v.koef[i] = v.koef[i] * a;
    return v;
}

Polynom operator* (const Polynom& v, const Polynom& p){
    Polynom N (p.get_size() + v.get_size() - 1);
    for (int i = 0; i < v.get_size(); i++){
        for (int j = 0; j < p.get_size(); j++)
            N.koef[i+j] += v.koef[i]*p.koef[j];
    }
    return N;
}



ostream& operator<< (ostream& os, const Polynom& v ){
    for (int i = 0; i < v.get_size(); i++){
        os << v.get_element(i) << 'x' << "^" << v.get_size() - i - 1 << " ";
        if (i < v.get_size() - 1){
            os << "+ ";
        }
    }
    return os;
}


istream& operator >> (istream &is, const Polynom &p) {
    for (int i = 0; i < p.get_size(); i++)
        cin >> p.koef[i];
    return is;
}


