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
    Nodo* raiz = new Nodo(1);
    raiz->left = new Nodo(2);
    raiz->right = new Nodo(3);
    raiz->left->left = new Nodo(4);
    raiz->left->right = new Nodo(5);
    raiz->right->left = new Nodo(6);

    cout << es_completo(raiz) << endl;
    cout << ancho_max(raiz) << endl;
    cout << profundidad_min(raiz) << endl;
}