#include <iostream>

using namespace std;

struct Node {
    int data;
    int height;
    Node* left;
    Node* right;
    Node* parent;
};

class Tree {
private:
    Node* tree_root;
    int getHeight(Node* n) {
        return n ? n->height : 0;
    }

    int bfactor(Node* n) {
        return getHeight(n->left) - getHeight(n->right);
    }

    void fixheight(Node* n) {
        n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
    }

    Node* leftRotate(Node* prev) {
        Node* fut = prev->right;
        prev->right = fut->left;
        fut->left = prev;

        if (prev->right != nullptr) {
            prev->right->parent = prev;
        }
        Node* tmp = prev->parent;
        prev->parent = fut;
        fut->parent = tmp;

        fixheight(prev);
        fixheight(fut);
        return fut;
    }

    Node* rightRotate(Node* prev) {
        Node* fut = prev->left;
        prev->left = fut->right;
        fut->right = prev;

        if (prev->left != nullptr) {
            prev->left->parent = prev;
        }
        Node* tmp = prev->parent;
        prev->parent = fut;
        fut->parent = tmp;

        fixheight(prev);
        fixheight(fut);
        return fut;
    }

    Node* getMin(Node* n) {
        return n->left ? getMin(n->left) : n;
    }

    Node* removeMin(Node* n) {
        if (n->left == nullptr) {
            return n->right;
        }
        n->left = removeMin(n->left);
        return balance(n);
    }

    Node* balance(Node* n) {
        fixheight(n);
        if (bfactor(n) == -2) {
            if ((n->right != nullptr) && (bfactor(n->right) > 0)) {
                n->right = rightRotate(n->right);
            }
            return leftRotate(n);
        }
        else if (bfactor(n) == 2) {
            if ((n->left != nullptr) && (bfactor(n->left) < 0)) {
                n->left = leftRotate(n->left);
            }
            return rightRotate(n);
        }
        else {
            return n;
        }
    }

    Node* insertNode(Node* root, int data) {
        if (root == nullptr) {
            return new Node{ data, 1, nullptr, nullptr, nullptr};
        }
        if (data < root->data) {
            root->left = insertNode(root->left, data);
            root->left->parent = root;
        }
        else {
            root->right = insertNode(root->right, data);
            root->right->parent = root;
        }
        return balance(root);
    }

    Node* findNode(Node* root, int data) {
        if (root == nullptr) {
            return nullptr;
        }

        if (data < root->data) {
            findNode(root->left, data);
        }
        else if (data > root->data) {
            findNode(root->right, data);
        }
        else {
            return root;
        }
    }

    Node* removeNode(Node* root, int data) {
        if (root == nullptr) {
            return nullptr;
        }

        if (data < root->data) {
            root->left = removeNode(root->left, data);
        }
        else if (data > root->data) {
            root->right = removeNode(root->right, data);
        }
        else {
            Node* l = root->left;
            Node* r = root->right;
            Node* par = root->parent;
            delete root;
            if (r == nullptr) {
                return l;
            }
            Node* min = getMin(r);
            min->right = removeMin(r);
            min->left = l;
            min->parent = par;
            min->left->parent = min;
            min->right->parent = min;
            return balance(min);
        }

        return balance(root);
    }
    void KerPrint(Node* root, string ind, bool last) {
        if (root != nullptr) {
            cout << ind;
            if (last) {
                cout << "R----";
                ind += "    ";
            }
            else {
                cout << "L----";
                ind += "|   ";
            }
            int parent = root->parent != nullptr ? root->parent->data : -1;
            cout << "(" << root->data << " parent: " << parent << ")" << "\n";
            KerPrint(root->left, ind, false);
            KerPrint(root->right, ind, true);
        }
    }

public:
    Tree() {
        this->tree_root = nullptr;
    }
    void insert(int data) {
        this->tree_root = insertNode(tree_root, data);
    }
    void print() {
        KerPrint(tree_root, "", false);
    }
    void remove(int data) {
        this->tree_root = removeNode(tree_root, data);
    }

    Node* find(int data) {
        return findNode(tree_root, data);
    }

};

int main()
{
    Tree tr;
    while (true) {
        cout << "\nEnter 1 to insert number to the tree\nEnter 2 to delete number from the tree\nEnter 3 to print tree\nEnter 4 to find number in the tree\nEnter 5 to exit\n";
        int choice; cin >> choice;
        int number;
        switch (choice)
        {
        case 1:
            cout << "\nEnter a number to insert: ";
            cin >> number;
            tr.insert(number);
            cout << "Inserted!\n";
            break;
        case 2:
            cout << "\nEnter a number to delete: ";
            cin >> number;
            if (tr.find(number)) {
                tr.remove(number);
                cout << "Removed!\n";
            }
            else {
                cout << "There is no such number in the tree\n";
            }
            break;
        case 3:
            tr.print();
            break;
        case 4:
            cout << "\nEnter a number to find: ";
            cin >> number;
            if (tr.find(number)) {
                cout << "The number is presented in the tree\n";
            }
            else {
                cout << "There is no such number in the tree\n";
            }
        default:
            return 0;
        }
    }
}