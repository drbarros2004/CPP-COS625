#include <bits/stdc++.h>

using namespace std;

int main() {

    map<string, int> m;
    m["Janeiro"] = 31;

    // find retorna iterador para o par {chave, valor}
    auto it = m.find("Janeiro");

    if ( it != m.end() ) {
    cout << it->first  << endl;  // "Janeiro"  — a chave
    cout << it->second << endl;  // 31         — o valor
    }

    // Busca de chave inexistente — NÃO insere nada
    if ( m.find("Fevereiro") != m.end() ) {
        cout << "existe" << endl;
    }
    else {
        cout << "Não existe" << endl; // ← cai aqui
    }

    cout << m.size() << endl;  // ainda 1 — Fevereiro não foi criado ✔

    // find também funciona em map const
    const map<string,int>& f = m;
    auto it2 = f.find("Janeiro");  // ok em const ✔


    return 0;

}

// Para compilar (na minha máquina):


// clang++ template.cpp                     
// ./a.out   

// Para compilar com nome:

//clang++ -o NOME_AQUI template.cpp
// ./NOME_AQUI.out
