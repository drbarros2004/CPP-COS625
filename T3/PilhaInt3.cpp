#include <iostream>
#include <sstream>

using namespace std;

class PilhaInt {
public:

    // Constructor w/ default value and initializer.
    PilhaInt ( int capacidade = 10) : cap(capacidade) { 
        stack.reserve(capacidade);
    }

    // Copy constructor
    PilhaInt (const PilhaInt &other) : cap(other.cap), stack(other.stack) { }

    // Destructor
    ~PilhaInt() {
    } 

    // Add a new element to PilhaInt. Resizes it to 2 * original size if PilhaInt is full.
    void empilha(int valor) { 
        if ((int)stack.size() == cap) {
            redimensiona(cap * 2);
        }
        stack.push_back(valor);
    }

    // Remove and return the last element of PilhaInt. 
    int desempilha() {
        // pop_back returns void, so we need to store the last value before popping.
        int tmp = stack.back();
        stack.pop_back();
        return tmp;
    }

    // Returns the capacity of PilhaInt.
    int capacidade() { 
        return cap; 
    }

    // Resizes PilhaInt and updates attributes.
    void redimensiona( int new_cap ) { 

        if (new_cap < (int)stack.size()) {
            stack.resize(new_cap);
        }
        stack.reserve(new_cap);
        cap = new_cap;

    }

    // Operator overload to add one more element
    PilhaInt& operator << (int valor) { 
        empilha( valor );
        return *this; 
    }

    // Operator overload to create a copy
    const PilhaInt& operator = ( const PilhaInt& other ){ 
        if( this != &other ) {
            this->cap = other.cap; 
            this->stack = other.stack;
        }
        return *this; // Returning like this allows chaining the operator (same for "<<")
    }

    void print( std::ostream& o) {
        if ((int)stack.size() > 0) { // stack.size() returns a size_t type. It needs to be converted to int.
            o << "[ " << stack[0];
            for (auto it = stack.begin() + 1; it < stack.end(); it++) {
                o << ", " << *it; // don't need to use stack[*it] because *it points to the element itself
            }
            o << " ]"; 
        }
    }

private:
    int cap;
    std::vector<int> stack;
};


PilhaInt embaralha( PilhaInt q ) {
    int aux = q.desempilha();
    q << 32 << 9 << aux;
    
    return q;
}

int main() {

    PilhaInt p, q;
    q << 2;
    p << 19 << 18 << 17 << 30;
    q = p;
    p.desempilha();
    q << 7;
    stringstream ssp, ssq;
    p.print( ssp );
    q.print( ssq );

    cout << "q = " << ssq.str() << "\n" << "p = " << ssp.str() << endl;
  
    return 0;
}

// Para compilar (na minha máquina):

// clang++ template.cpp                     
// ./a.out   

// Para compilar com nome:

//clang++ -o NOME_AQUI template.cpp
// ./NOME_AQUI.out
