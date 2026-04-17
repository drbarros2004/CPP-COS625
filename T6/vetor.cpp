#include <iostream>
#include <sstream>
#include <array>            
#include <initializer_list> 

using namespace std;

template <size_t n, typename T> 
class Vetor {
private:

    array<T, n> data;

public: 

    // Default constructor (initializes with 0).
    Vetor() {
        for (auto& element : data) {
            element = 0;
        }
    }

    // Constructor from `initializer_list`.
    Vetor ( const initializer_list<T>& list ) {
        if (list.size() != n ) {
            cerr << "Error: size of initiliazer list is different from Vetor declared size." << endl;
            exit(1);
        }
        auto it = list.begin();
        for (size_t i = 0; i < list.size(); i++) {
            data[i] = *it;
            it++;
        }
    }

    // Operator overload for assignment.
    const Vetor& operator= ( const initializer_list<T>& list ) { 
        if (list.size() != n ) {
            cerr << "Error: size of initiliazer list is different from Vetor declared size." << endl;
            exit(1);
        }
        auto it = list.begin();
        for (size_t i = 0; i < list.size(); i++) {
            this->data[i] = *it;
            it++;
        }
        return *this;
    }

    // Operator overload (`+`).
    Vetor operator + ( const Vetor& other ) const {
        Vetor<n, T> result;
        for (size_t i = 0; i < n; ++i) {
            result.data[i] = this->data[i] + other.data[i];
        }
        return result;
    }

    // Operator overload (`-`).
    Vetor operator - ( const Vetor& other ) const {
        Vetor<n, T> result;
        for (size_t i = 0; i < n; ++i) {
            result.data[i] = this->data[i] - other.data[i];
        }
        return result;
    }

    // Operator overload (`*`) - dot product.
    T operator * ( const Vetor& other ) const {
        T result = 0; 
        for (size_t i = 0; i < n; ++i) {
            result += this->data[i] * other.data[i];
        }
        return result;
    }

    // Operator overload (`*`) - scalar multiplication
    Vetor operator * ( T scalar ) const {
        Vetor<n, T> result;
        for (size_t i = 0; i < n; ++i) {
            result.data[i] = this->data[i] * scalar;
        }
        return result;
    }

    // Allow inverse order (Scalar * Vetor)
    friend Vetor operator*(T scalar, const Vetor& v) {
        return v * scalar; 
    }

    // Operator overload (`/`) - scalar division
    Vetor operator / ( T scalar ) const {
        Vetor<n, T> result;
        for (size_t i = 0; i < n; ++i) {
            result.data[i] = this->data[i] / scalar;
        }
        return result;
    }

    // Operator overload (`<<`)
    friend std::ostream& operator << (std::ostream& o, const Vetor& v) {
        if (n > 0) {
            o << "[ " << v.data[0];
            for (size_t i = 1; i < n; i++) {
                o << ", " << v.data[i]; 
            } 
            o << " ]"; 
        }
        return o;
    }

    // Proxy used for implementing Cross Product with `**` operator, to allow expressions like `a ** b`.
    class CrossProductProxy {
    public:
        const Vetor<n, T>& right_v; // Reference to b.
        CrossProductProxy(const Vetor<n, T>& v) : right_v(v) {}
    };

    // Operator overload for `*` to return a `CrossProductProxy` instead of dereferencing Vetor.
    CrossProductProxy operator*() const {
        return CrossProductProxy(*this); // Calls CrossProductProxy constructor passing (*this), i.e, the Vetor object b.
    }

    // Operator overload that receives a `Vetor` and a `CrossProductProxy`, returning a `Vetor`.
    Vetor operator*(const CrossProductProxy& proxy) const {
        if (n != 3) {
            cerr << "Error: Cross product is only defined for n = 3. " << endl;
            exit (1);
        }
        Vetor<n, T> result; 
        result.data[0] = this->data[1] * proxy.right_v.data[2] - this->data[2] * proxy.right_v.data[1];
        result.data[1] = this->data[2] * proxy.right_v.data[0] - this->data[0] * proxy.right_v.data[2];
        result.data[2] = this->data[0] * proxy.right_v.data[1] - this->data[1] * proxy.right_v.data[0];
        return result;
    }
};

int main() {
    Vetor<3, double> a;
    Vetor<3, double> b = {-2.0, -5.2, 1 };
    a = {1.0, 2.0, 4.0};

    cout << a + b << endl;
    cout << a * b << endl;
    cout << a * 2 << endl;
    cout << a / 2 << endl;
    cout << a**b << endl;
}


// Para compilar (na minha máquina):

// clang++ template.cpp                     
// ./a.out   

// Para compilar com nome:

//clang++ -o NOME_AQUI template.cpp
// ./NOME_AQUI.out
