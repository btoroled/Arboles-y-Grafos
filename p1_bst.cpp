#include <iostream>
#include <stack>
#include <queue>
#include  <algorithm>

template<typename T>
struct Nodo {
    T x;
    Nodo<T>* left;
    Nodo<T>* right;
    Nodo<T>* padre;
    Nodo(T dato) {
        x = dato;
        left = nullptr;
        right = nullptr;
        padre = nullptr;
    }
};

template<typename T>
class BST {
    Nodo<T>* root;
    Nodo<T>* minimoNodo(Nodo<T>* nodo) {
        while (nodo != nullptr && nodo->left != nullptr) {
            nodo = nodo->left;
        }
        return nodo;
    }

    void transplant(Nodo<T>* u, Nodo<T>* v) {
        if (u->padre == nullptr)
            root = v;
        else if (u==u->padre->left)
            u->padre->left = v;
        else
            u->padre->right = v;
        if (v != nullptr)
            v->padre = u->padre;
    }

    public:
    BST(): root(nullptr) {};

    void insert(T dato) {
        Nodo<T>* z = new Nodo<T>(dato);
        Nodo<T>* y = nullptr;
        Nodo<T>* x = root;

        while (x != nullptr) {
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
        if (y==nullptr)
            root =z;
        else if (dato < y->x)
            y->left = z;
        else
            y->right = z;
    }

    void eliminar(T dato) {
        Nodo<T>* z = root;
        while (z != nullptr && z->x != dato) {
            if (dato < z->x)
                z = z->left;
            else
                z= z->right;
        }
        if (z == nullptr) return;

        if (z->left == nullptr) {
            transplant(z, z->right);
            delete z;
            return;
        }
        if (z->right == nullptr) {
            transplant(z, z->left);
            delete z;
            return;
        }
        Nodo<T>* y = minimoNodo(z->right);
        if (y->padre != z) {
            transplant(y, y->right);
            y->right = z->right;
            if (y->right != nullptr) y->right->padre = y;
        }
        transplant(z, y);
        y->left = z->left;
        if (y->left != nullptr) y->left->padre = y;
        delete z;
    }

    void inOrder() {
        std::stack<Nodo<T>*> st;
        Nodo<T>* actual = root;
        while (actual != nullptr || !st.empty()) {
            while (actual != nullptr) {
                st.push(actual);
                actual = actual->left;
            }
            actual = st.top();
            st.pop();
            std::cout << actual->x << " " << actual->padre << std::endl;
            actual = actual->right;
        }
        std::cout << std::endl;
    }

    int height() {
        if (root == nullptr) return -1;
        std::queue<Nodo<T>*> q;
        q.push(root);
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

void imprimir(std::string titulo, BST<int>& bst) {
    std::cout << titulo << std::endl;
    bst.inOrder();
    std::cout << bst.height() << std::endl;
    std::cout << "----" << std::endl;
}


int main() {

    BST<int> bst;
    for (int i = 1; i <= 20; i++) bst.insert(i);
    bst.eliminar(5);
    bst.eliminar(15);
    imprimir("Caso 1: Ascendente 1..20, delete 5 y 15", bst);

    BST<int> bst1;
    for (int i = 20; i >= 1; i--) bst.insert(i);
    bst1.eliminar(20);
    bst1.eliminar(1);
    imprimir("Caso 2: Descendente 20..1, delete 20 y 1", bst1);

    BST<int> bst2;
    std::vector<int> v = {10,5,15,3,7,12,17,1,4,6,8,11,13,16,18};
    for (int x : v) bst2.insert(x);
    bst2.eliminar(1);
    bst2.eliminar(3);
    bst2.eliminar(5);
    imprimir("Caso 3: Balanceado, delete hoja/1hijo/2hijos", bst2);

    BST<int> bst3;
    std::vector<int> v3 = {8,8,8,5,5,10,10,9,11};
    for (int x : v3) bst3.insert(x);
    bst3.eliminar(100);
    bst3.eliminar(8);
    imprimir("Caso 4: Duplicados ignorados + delete inexistente + delete existente", bst3);
    return 0;
}