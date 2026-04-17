#include <bits/stdc++.h>

using namespace std;

void print( vector<int> v, std::ostream& o) {
    if ((int)v.size() > 0) { // v.size() returns a size_t type. It needs to be converted to int.
        o << "[ " << v[0];
        for (auto it = v.begin() + 1; it < v.end(); it++) {
            o << ", " << *it; // *it points to the element itself
        } 
        o << " ]" << endl; 
    }
}

int main() {

    vector<int> v = { 3, 7, 11, 13 };

    // count_if — conta elementos que satisfazem um predicado
    int impares = count_if( v.begin(), v.end(),
    []( int x ){ return x % 2 != 0; } );   
    cout << impares << endl;


    // find_if — encontra o primeiro que satisfaz
    auto it = find_if( v.begin(), v.end(),
    []( int x ){ return x > 8; } );        
    cout << *it << endl;


    // sort com critério customizado
    sort( v.begin(), v.end(),
    []( int a, int b ){ return a > b; } );  // decrescente
    print (v, cout);


    // transform — mapeia cada elemento para um novo valor
    vector<int> quadrados(v.size());
    transform( v.begin(), v.end(), quadrados.begin(),
    []( int x ){ return x * x; } );        
    print (quadrados, cout);

}

// Para compilar (na minha máquina):


// clang++ template.cpp                     
// ./a.out   

// Para compilar com nome:

//clang++ -o NOME_AQUI template.cpp
// ./NOME_AQUI.out