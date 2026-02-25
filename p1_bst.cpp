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


int main() {
    BST<int> bst;
    for (int i = 1; i <= 20; i++)
        bst.insert(i);

    bst.eliminar(5);
    bst.eliminar(15);

    bst.inOrder();
    std::cout << bst.height() << std::endl;

    return 0;
}