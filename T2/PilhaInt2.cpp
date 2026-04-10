#include <iostream>
#include <sstream>

using namespace std;

class PilhaInt {
public:

    // Constructor w/ default value
    PilhaInt( int capacidade = 10 ) {
        cap = capacidade;
        topo = 0;
        tab = (int*) malloc(cap * sizeof(int));

        for (int i = 0; i < cap; i++) {
            tab[i] = 0;
        }
    }

    // Copy constructor
    PilhaInt (const PilhaInt& other) {
        // Copy the attributes one by one
        this->cap = other.cap; // (*this.cap) = other.cap;
        this->topo = other.topo;

        // Allocate memory based on the capacity of the original PilhaInt object
        this->tab = (int*) malloc(other.cap * sizeof(int)); 

        // Copy elements from the original one by one
        for (int i = 0; i < other.topo; i++) {
            this->tab[i] = other.tab[i];
        }

        // We use this-><attribute> because this is a ptr. So, the syntax is (->). We could also use (*this).<attribute>
    }

    // Destructor
    ~PilhaInt() {
        // As I free the pointer tab, I also free ALL the space allocated by it on memory
        free(tab);
        tab = NULL;
    } 

    void empilha(int valor) { 

        // If PilhaInt is full, resize it to 2 times its current capacity value.
        if (topo == cap) {
            redimensiona( 2*cap );
        }
        // Post-increment/decrement: topo++ returns topo and then increments and updates topo to topo += 1.
        tab[topo++] = valor;
    }

    int desempilha() {
        // Pre-increment/decrement: --topo decrements topo and then returns it (updated).
        return tab[--topo];
    }

    int capacidade() { return cap; }

    void redimensiona( int new_cap ) { 

        int* tmp = (int*) realloc( tab, new_cap * sizeof(int) );

        // Always check if realloc worked by checking tmp != NULL
        if ( tmp != NULL ) {
            tab = tmp;
            cap = new_cap;

            if (cap < topo) {
                topo = cap; 
            }
        }

    }

    // Operator overload to add one more element
    PilhaInt& operator << (int valor) { 
        empilha( valor );
        return *this; 
    }

    // Operator overload to create a copy
    const PilhaInt& operator = ( const PilhaInt& other ){ 
        if( this != &other ) {
            if ( this->cap != other.cap) {
                free(this->tab);
                this->tab = NULL; // Good practice to point to NULL after freeing
                this->cap = other.cap; 
                this->tab = (int*) malloc(other.cap * sizeof(int)); 
            }

            if (this->tab != NULL) {
                this->topo = other.topo;
                for (int i = 0; i < other.topo; i++) {
                    this->tab[i] = other.tab[i];
                }
            }
                
        }
        return *this; // Returning like this allows chaining the operator (same for "<<")
    }

    void print( std::ostream& o) {
        if (topo > 0) {
            o << "[ " << tab[0];
            for (int i = 1; i < topo; i++) {
                o << ", " << tab[i];
            }
            o << " ]"; 
        }
    }

private:
    int *tab;
    int cap;
    int topo;
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
