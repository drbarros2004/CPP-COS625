#include <initializer_list>
#include <iostream>

using namespace std;

// `AbstractPair` acts as a contract. It shows what the derived classes must do, but without defining it.
class AbstractPair { 
    public:
        virtual ~AbstractPair() {} 
        virtual AbstractPair* clone() const = 0;    // = 0 shows explicitly that this is not the real function. It will be defined in the derived class
        virtual void imprime(ostream& o) const = 0; // same here

        // These virtual methods that are ( = 0 ) are pure virtual methods. 
};


// `PairImpl` is a template class. It defines how each specific pair should behave, but does it generically (for A and B).
template <typename A, typename B>
class PairImpl : public AbstractPair { 

    A first;
    B second;

    public:
        PairImpl (A a, B b) : first(a), second(b) {}
        
        AbstractPair* clone() const override { // Creates a deep copy of PairImpl. Needed because of double delete.
            return new PairImpl(*this);
        }

        void imprime(ostream& o) const override {
            o << first << " = " << second << endl;
        }
        // override explicitly tells the compiler that I want this function to substitute a method of same name declared on the parent Class.

};


// `Pair` "erases" the types. It has a template constructor for any combination of types.
// It has a pointer `Abstract Pair *p` that stores the adress of the real implementation (a `PairImpl` object).
// It is needed because, if we want to use `initializer_list` (or any collection), everything inside of it must have the same type.
class Pair {

    AbstractPair* p;

    public:
        // Template constructor allowing any combination of types.
        template <typename A, typename B> // This is how Pair "erases" the types. 
        Pair(A a, B b) {
            p = new PairImpl<A, B>(a, b);
        }

        // Copy constructor
        Pair(const Pair& other) { 
            p = other.p->clone();
        }

        // Operator overload to create a copy
        const Pair& operator = ( const Pair& other ){ 
            if( this != &other ) {
                delete p; 
                p = other.p->clone(); 
            }
            return *this; // Returning like this allows chaining the operator 
        }

        ~Pair() { // Rule of Three?: If a class needs a manual destructor, it almost (always) also needs operator(=) overload and copy constructor.
            delete p;
            p = nullptr;
        }

        // print receives an initializer_list of Pair. So, we this method to make sure it accesses the imprime method, that is written on PairImpl.
        void imprimir (ostream &o) const {
            p->imprime(o);
        }
};

void print(ostream& o, initializer_list<Pair> lista) {
    for (const auto& item : lista) {
        item.imprimir(o);
    }
}

int main() {

    Pair p{ "1", "2" };
    print( cout, { { "jan", 1 }, { string( "pi" ), 3.14 }, p } );
    
    return 0;
}

// Para compilar (na minha máquina):

// clang++ template.cpp                     
// ./a.out   

// Para compilar com nome:

//clang++ -o NOME_AQUI template.cpp
// ./NOME_AQUI.out
