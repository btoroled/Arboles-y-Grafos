#include <iostream>
#include <queue>
#include <algorithm>
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

bool es_completo(Nodo* raiz) {
    if (raiz == nullptr) return true;

    queue<Nodo*> q;
    q.push(raiz);
    bool visto_null = false;

    while (!q.empty()) {
        Nodo* cur = q.front();
        q.pop();

        if (cur == nullptr) {
            visto_null = true;
        } else {
            if (visto_null) return false;
            q.push(cur->left);
            q.push(cur->right);
        }
    }
    return true;
}

int ancho_max(Nodo* raiz) {
    if (raiz == nullptr) return 0;

    queue<Nodo*> q;
    q.push(raiz);
    int best = 0;

    while (!q.empty()) {
        int sz = (int)q.size();
        best = max(best, sz);
        while (sz--) {
            Nodo* cur = q.front();
            q.pop();
            if (cur->left != nullptr) q.push(cur->left);
            if (cur->right != nullptr) q.push(cur->right);
        }
    }
    return best;
}

int profundidad_min(Nodo* raiz) {
    if (raiz == nullptr) return 0;

    queue<Nodo*> q;
    q.push(raiz);
    int d = 0;

    while (!q.empty()) {
        int sz = (int)q.size();
        d++;
        while (sz--) {
            Nodo* cur = q.front();
            q.pop();
            if (cur->left == nullptr && cur->right == nullptr)
                return d;
            if (cur->left != nullptr) q.push(cur->left);
            if (cur->right != nullptr) q.push(cur->right);
        }
    }
    return d;
}

int main() {
    // Caso 1
    Nodo* raiz1 = nullptr;
    probar("Caso 1: Arbol vacio", raiz1);

    // Caso 2
    Nodo* raiz2 = new Nodo(1);
    probar("Caso 2: Un nodo", raiz2);

    // Caso 3
    Nodo* raiz3 = new Nodo(1);
    raiz3->left = new Nodo(2);
    raiz3->right = new Nodo(3);
    raiz3->left->left = new Nodo(4);
    raiz3->left->right = new Nodo(5);
    raiz3->right->left = new Nodo(6);
    probar("Caso 3: Completo", raiz3);

    // Caso 4
    Nodo* raiz4 = new Nodo(1);
    raiz4->left = new Nodo(2);
    raiz4->right = new Nodo(3);
    raiz4->right->left = new Nodo(6);
    probar("Caso 4: No completo (falta left->*, aparece right->left)", raiz4);

    // Caso 5
    Nodo* raiz5 = new Nodo(1);
    raiz5->left = new Nodo(2);
    raiz5->right = new Nodo(3);
    raiz5->left->left = new Nodo(4);
    raiz5->right->right = new Nodo(7);
    probar("Caso 5: No completo (hueco en left->right y aparece right->right)", raiz5);

    // Caso 6
    Nodo* raiz6 = new Nodo(1);
    raiz6->left = new Nodo(2);
    raiz6->left->left = new Nodo(3);
    raiz6->left->left->left = new Nodo(4);
    probar("Caso 6: Cadena izquierda", raiz6);

    // Caso 7
    Nodo* raiz7 = new Nodo(1);
    raiz7->right = new Nodo(2);
    raiz7->right->right = new Nodo(3);
    probar("Caso 7: Cadena derecha (no completo)", raiz7);

    // Caso 8
    Nodo* raiz8 = new Nodo(1);
    raiz8->left = new Nodo(2);
    raiz8->right = new Nodo(3);
    raiz8->left->left = new Nodo(4);
    raiz8->left->right = new Nodo(5);
    raiz8->right->left = new Nodo(6);
    raiz8->right->right = new Nodo(7);
    raiz8->left->left->left = new Nodo(8);
    raiz8->left->left->right = new Nodo(9);
    probar("Caso 8: Perfecto hasta nivel 3 parcial (ancho mayor)", raiz8);
}