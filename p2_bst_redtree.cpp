#include <iostream>
#include <stack>
#include <queue>
using namespace std;

template<typename T>
struct NodoRB {
    T x;
    int color;
    NodoRB<T>* left;
    NodoRB<T>* right;
    NodoRB<T>* padre;
    NodoRB(T dato, int c) {
        x = dato;
        color = c;
        left = nullptr;
        right = nullptr;
        padre = nullptr;
    }
};

template<typename T>
class RBTree {
    NodoRB<T>* raiz;
    NodoRB<T>* NIL;

    void leftRotate(NodoRB<T>* x) {
        NodoRB<T>* y = x->right;
        x->right = y->left;
        if (y->left != NIL)
            y->left->padre = x;

        y->padre = x->padre;
        if (x->padre == NIL)
            raiz = y;
        else if (x == x->padre->left)
            x->padre->left = y;
        else
            x->padre->right = y;

        y->left = x;
        x->padre = y;
    }

    void rightRotate(NodoRB<T>* y) {
        NodoRB<T>* x = y->left;
        y->left = x->right;
        if (x->right != NIL)
            x->right->padre = y;

        x->padre = y->padre;
        if (y->padre == NIL)
            raiz = x;
        else if (y == y->padre->right)
            y->padre->right = x;
        else
            y->padre->left = x;

        x->right = y;
        y->padre = x;
    }

    void insertarFix(NodoRB<T>* z) {
        while (z->padre->color == 1) {
            if (z->padre == z->padre->padre->left) {
                NodoRB<T>* y = z->padre->padre->right;
                if (y->color == 1) {
                    z->padre->color = 0;
                    y->color = 0;
                    z->padre->padre->color = 1;
                    z = z->padre->padre;
                } else {
                    if (z == z->padre->right) {
                        z = z->padre;
                        leftRotate(z);
                    }
                    z->padre->color = 0;
                    z->padre->padre->color = 1;
                    rightRotate(z->padre->padre);
                }
            } else {
                NodoRB<T>* y = z->padre->padre->left;
                if (y->color == 1) {
                    z->padre->color = 0;
                    y->color = 0;
                    z->padre->padre->color = 1;
                    z = z->padre->padre;
                } else {
                    if (z == z->padre->left) {
                        z = z->padre;
                        rightRotate(z);
                    }
                    z->padre->color = 0;
                    z->padre->padre->color = 1;
                    leftRotate(z->padre->padre);
                }
            }
        }
        raiz->color = 0;
    }

    void borrarSubarbol(NodoRB<T>* n) {
        if (n == NIL) return;
        stack<NodoRB<T>*> st;
        st.push(n);
        while (!st.empty()) {
            NodoRB<T>* cur = st.top();
            st.pop();
            if (cur->left != NIL) st.push(cur->left);
            if (cur->right != NIL) st.push(cur->right);
            delete cur;
        }
    }

public:
    RBTree() {
        NIL = new NodoRB<T>(T(), 0);
        NIL->left = NIL->right = NIL->padre = NIL;
        raiz = NIL;
    }

    ~RBTree() {
        borrarSubarbol(raiz);
        delete NIL;
    }

    void insertar(T dato) {
        NodoRB<T>* z = new NodoRB<T>(dato, 1);
        z->left = z->right = NIL;

        NodoRB<T>* y = NIL;
        NodoRB<T>* x = raiz;
        while (x != NIL) {
            y = x;
            if (dato < x->x)
                x = x->left;
            else if (dato > x->x)
                x = x->right;
            else {
                delete z;
                return;
            }
        }

        z->padre = y;
        if (y == NIL)
            raiz = z;
        else if (dato < y->x)
            y->left = z;
        else
            y->right = z;

        insertarFix(z);
    }

    int altura() {
        if (raiz == NIL) return -1;
        queue<NodoRB<T>*> q;
        q.push(raiz);
        int h = -1;
        while (!q.empty()) {
            int sz = (int)q.size();
            while (sz--) {
                NodoRB<T>* n = q.front();
                q.pop();
                if (n->left != NIL) q.push(n->left);
                if (n->right != NIL) q.push(n->right);
            }
            h++;
        }
        return h;
    }

    void preOrden() {
        if (raiz == NIL) {
            cout << endl;
            return;
        }
        stack<NodoRB<T>*> st;
        st.push(raiz);
        while (!st.empty()) {
            NodoRB<T>* n = st.top();
            st.pop();
            cout << n->x << ' ';
            if (n->right != NIL) st.push(n->right);
            if (n->left != NIL) st.push(n->left);
        }
        cout << endl;
    }
};

template<typename T>
struct Nodo {
    T x;
    Nodo<T>* left;
    Nodo<T>* right;
    Nodo(T dato) {
        x = dato;
        left = nullptr;
        right = nullptr;
    }
};

template<typename T>
class BSTSimple {
    Nodo<T>* raiz;
public:
    BSTSimple(): raiz(nullptr) {}
    void insertar(T dato) {
        Nodo<T>* z = new Nodo<T>(dato);
        if (raiz == nullptr) {
            raiz = z;
            return;
        }
        Nodo<T>* cur = raiz;
        Nodo<T>* p = nullptr;
        while (cur != nullptr) {
            p = cur;
            if (dato < cur->x)
                cur = cur->left;
            else if (dato > cur->x)
                cur = cur->right;
            else {
                delete z;
                return;
            }
        }
        if (dato < p->x) p->left = z;
        else p->right = z;
    }

    int altura() {
        if (raiz == nullptr) return -1;
        queue<Nodo<T>*> q;
        q.push(raiz);
        int h = -1;
        while (!q.empty()) {
            int sz = (int)q.size();
            while (sz--) {
                Nodo<T>* n = q.front();
                q.pop();
                if (n->left != nullptr) q.push(n->left);
                if (n->right != nullptr) q.push(n->right);
            }
            h++;
        }
        return h;
    }
};

void probar(string titulo, const vector<int>& v) {
    BSTSimple<int> bst;
    RBTree<int> rbt;

    for (int x : v) {
        bst.insertar(x);
        rbt.insertar(x);
    }

    cout << titulo << endl;
    cout << bst.altura() << endl;
    cout << rbt.altura() << endl;
    rbt.preOrden();
    cout << "----" << endl;
}


int main() {
    // Caso 1
    vector<int> v1;
    for (int i = 1; i <= 20; i++) v1.push_back(i);
    probar("Caso 1: Ascendente 1..20", v1);

    // Caso 2
    vector<int> v2;
    for (int i = 20; i >= 1; i--) v2.push_back(i);
    probar("Caso 2: Descendente 20..1", v2);

    // Caso 3
    vector<int> v3 = {10,5,15,3,7,12,17,1,4,6,8,11,13,16,18,2,9,14,19,20};
    probar("Caso 3: Mezclado", v3);

    // Caso 4
    vector<int> v4 = {8,8,8,5,5,10,10,9,11,11,1,1,2,2};
    probar("Caso 4: Con duplicados (ignorados)", v4);

    // Caso 5
    vector<int> v5;
    for (int i = 1; i <= 100; i++) v5.push_back(i);
    probar("Caso 5: Ascendente 1..100", v5);
}