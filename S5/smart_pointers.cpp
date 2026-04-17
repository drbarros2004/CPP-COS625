#include <memory>
#include <iostream>
using namespace std;

int main() {
  unique_ptr<int> p{ new int };
  unique_ptr<int> outro{ new int };

  *p = 6;
  cout << *p << endl;      // 6

  // Reatribuição: libera o int atual, assume o novo
  p = unique_ptr<int>( new int );
  cout << *p << endl;      // lixo — int recém alocado

  // p = outro;            // ERRO de compilação — cópia é deletada
  p = std::move(outro);   // ok — MOVE transfere a posse
  // outro agora é nullptr — não tem mais o recurso

  return 0;
} // ~unique_ptr deleta o int ✔