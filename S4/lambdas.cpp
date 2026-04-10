#include <bits/stdc++.h>

using namespace std;

int main() {

    int soma = 0;

    vector<int> v = {2, 4, 5, 6};

    auto somador =
    [&soma] (int x) { soma += x; };
    // [<variáveis a serem capturadas>] (<tipo> <parâmetro>, ...) { <corpo da função> }
    // Poderia ter um -> <tipo de retorno>, mas normalmente é omitido porque o compilador infere.

    for_each( v.begin(), v.end(), somador );

    // somador(5); // Poderia chamar assim também, caso não quisesse vetor.

    cout << soma << endl;

    return 0;

}

// Para compilar (na minha máquina):

// clang++ template.cpp                     
// ./a.out   

// Para compilar com nome:

//clang++ -o NOME_AQUI template.cpp
// ./NOME_AQUI.out
