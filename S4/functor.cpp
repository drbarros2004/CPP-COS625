#include <bits/stdc++.h>

using namespace std;

class Acumulador {
    double total = 0.0; // estado persistente entre chamadas
public:
    double operator()(double x)
    {
        total += x;
        return total;
    }
    double soma() const { return total; }
};

int main() {
    Acumulador ac;
    cout << ac(3.0) << endl; // 3
    cout << ac(7.0) << endl; // 10
    cout << ac(2.5) << endl; // 12.5

    // Isso é impossível com uma função comum — funções 
    // não têm onde guardar estado entre chamadas (exceto com variáveis estáticas, que são globais e não reentráveis).

    cout << ac.soma() << endl;
}

// Para compilar (na minha máquina):

// clang++ template.cpp                     
// ./a.out   

// Para compilar com nome:

//clang++ -o NOME_AQUI template.cpp
// ./NOME_AQUI.out
