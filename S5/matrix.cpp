#include <bits/stdc++.h>

using namespace std;

class Matriz {
public:
    // Proxy que representa uma única linha da matriz
    class Linha {
        double *dados;
        friend class Matriz;
        Linha(double *d) : dados(d) {}

    public:
        // Segundo []: seleciona a coluna dentro da linha
        double &operator[](int j) { return dados[j]; }
        const double &operator[](int j) const { return dados[j]; }
    };

    class Coluna {
    private:
        int coluna;
        Matriz &m;
        friend class Matriz;

    public:
        Coluna( int coluna, Matriz& m) : coluna(coluna), m(m) {}

        double operator[](int j) {
            return m[j][coluna];
        }
    };

    // Primeiro []: retorna o proxy Linha para a linha i
    Linha operator[](int i)             { return Linha(tab[i]); }
    // const Linha operator[](int i) const { return Linha(tab[i]); }

    Coluna col (int n) {
        return Coluna(n, *this);
    }


private:
    double tab[10][10]{};
};

int main() {
    Matriz m;
    m[2][3] = 9.5; // Atribuição via linha

    // Uso do proxy de coluna para ler o dado
    // col(3) seleciona a quarta coluna, [2] seleciona a terceira linha dessa coluna
    double valor = m.col(3)[2]; 

    cout << "Valor acessado via coluna: " << valor << endl; // Saída: 9.5
}