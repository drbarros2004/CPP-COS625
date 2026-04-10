#include <iostream>
#include <sstream>

using namespace std;

class PilhaInt {
public:

    PilhaInt( int tamanho = 10 ) {
        for (int i = 0; i < MAX_PILHA; i++)
            tab[i] = 0;
        topo = 0;
    }

    void empilha(int valor) {
        tab[topo++] = valor;
    }

    int desempilha() {
        return tab[--topo];
    }

    PilhaInt& operator << (int valor) { // sobrecarga de operadores para empilhar elementos
        empilha( valor );
        return *this;
    }

    const PilhaInt& operator= ( const PilhaInt& p ){ // sobrecarga de operadores para criar uma cópia
        if( this != &p ) {
            topo = p.topo;
            for( int i = 0; i < p.topo; i++ ) {
                tab[i] = p.tab[i];
            }
        }
        return *this; // retornar assim para permitir encadeamento
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
    static const int MAX_PILHA = 20;
    int tab[MAX_PILHA];
    int topo;
};

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
