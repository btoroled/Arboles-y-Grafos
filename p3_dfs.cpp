#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct Nodo {
    int x;
    Nodo* left;
    Nodo* right;
    Nodo(int v) {
        x = v;
        left = nullptr;
        right = nullptr;
    }
};

struct Estado {
    Nodo* nodo;
    int suma;
    int etapa;
    Estado(Nodo* n, int s, int e) : nodo(n), suma(s), etapa(e) {}
};

bool camino_suma(Nodo* raiz, int K, vector<int>& camino) {
    camino.clear();
    if (raiz == nullptr) return false;

    stack<Estado> st;
    st.push(Estado(raiz, raiz->x, 0));

    while (!st.empty()) {
        Estado& e = st.top();
        if (e.etapa == 0) {
            camino.push_back(e.nodo->x);
            if (e.nodo->left == nullptr && e.nodo->right == nullptr && e.suma == K)
                return true;

            e.etapa = 1;

            if (e.nodo->right != nullptr)
                st.push(Estado(e.nodo->right, e.suma + e.nodo->right->x, 0));
            if (e.nodo->left != nullptr)
                st.push(Estado(e.nodo->left, e.suma + e.nodo->left->x, 0));
        } else {
            st.pop();
            camino.pop_back();
        }
    }
    return false;
}


void imprimir(string titulo, Nodo* raiz, int K) {
    vector<int> camino;
    cout << titulo << endl;
    cout << K << endl;
    if (camino_suma(raiz, K, camino)) {
        for (int v : camino) cout << v << ' ';
        cout << endl;
    } else {
        cout << "NO" << endl;
    }
    cout << "----" << endl;
}



int main() {
    Nodo* raiz1 = new Nodo(5);
    raiz1->left = new Nodo(4);
    raiz1->right = new Nodo(8);
    raiz1->left->left = new Nodo(11);
    raiz1->left->left->left = new Nodo(7);
    raiz1->left->left->right = new Nodo(2);
    raiz1->right->left = new Nodo(13);
    raiz1->right->right = new Nodo(4);
    raiz1->right->right->right = new Nodo(1);

    imprimir("Caso 1: Existe", raiz1, 22);
    imprimir("Caso 2: No existe", raiz1, 26);
    imprimir("Caso 3: Leaf solo derecha", raiz1, 18);

    // Caso 2 (árbol pequeño)
    Nodo* raiz2 = new Nodo(1);
    raiz2->left = new Nodo(2);
    raiz2->right = new Nodo(3);

    imprimir("Caso 4: Pequeño existe", raiz2, 3);
    imprimir("Caso 5: Pequeño no existe", raiz2, 5);

    // Caso 3 (con negativos)
    Nodo* raiz3 = new Nodo(-10);
    raiz3->left = new Nodo(9);
    raiz3->right = new Nodo(-20);
    raiz3->right->left = new Nodo(15);
    raiz3->right->right = new Nodo(-7);

    imprimir("Caso 6: Con negativos existe", raiz3, -37);
    imprimir("Caso 7: Con negativos no existe", raiz3, -100);

    // Caso 4 (árbol vacío)
    Nodo* raiz4 = nullptr;
    imprimir("Caso 8: Arbol vacio", raiz4, 0);

    // Caso 5 (un nodo)
    Nodo* raiz5 = new Nodo(7);
    imprimir("Caso 9: Un nodo existe", raiz5, 7);
    imprimir("Caso 10: Un nodo no existe", raiz5, 8);
}