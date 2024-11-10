#include <iostream>

using namespace std;

struct Node {
    string data;
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

    void setHeight(Node* n) {
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

        setHeight(prev);
        setHeight(fut);
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

        setHeight(prev);
        setHeight(fut);
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
        setHeight(n);
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

    Node* insertNode(Node* root, string data) {
        if (root == nullptr) {
            return new Node{ data, 1, nullptr, nullptr, nullptr };
        }
        if (data.compare(root->data) < 0) {
            root->left = insertNode(root->left, data);
            root->left->parent = root;
        }
        else {
            root->right = insertNode(root->right, data);
            root->right->parent = root;
        }
        return balance(root);
    }

    Node* findNode(Node* root, string data) {
        if (root == nullptr) {
            return nullptr;
        }

        if (data.compare(root->data.substr(0, data.size()))<0) {
            findNode(root->left, data);
        }
        else if (data.compare(root->data.substr(0, data.size())) >0) {
            findNode(root->right, data);
        }
        else {
            cout << root->data << "\n";
            findNode(root->left, data);
            findNode(root->right, data);
        }
    }

    Node* removeNode(Node* root, string data) {
        if (root == nullptr) {
            return nullptr;
        }

        if (data.compare(root->data) < 0) {
            root->left = removeNode(root->left, data);
        }
        else if (data.compare(root->data) > 0) {
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
            if (min->left != nullptr) {
                min->left->parent = min;
            }
            if (min->right != nullptr) {
                min->right->parent = min;
            }
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
            string parent = root->parent != nullptr ? root->parent->data : "root";
            cout << "(" << root->data << " parent: " << parent << ")" << "\n";
            KerPrint(root->left, ind, false);
            KerPrint(root->right, ind, true);
        }
    }

public:
    Tree() {
        this->tree_root = nullptr;
    }
    void insert(string data) {
        this->tree_root = insertNode(tree_root, data);
    }
    void print() {
        KerPrint(tree_root, "", false);
    }
    void remove(string data) {
        this->tree_root = removeNode(tree_root, data);
    }

    Node* find(string data) {
        return findNode(tree_root, data);
    }

};

int main()
{
    Tree tr;
    while (false) {
        cout << "\nEnter 1 to insert word to the dictionary\nEnter 2 to delete word from the dictionary\nEnter 3 to print tree\nEnter 4 to words by prefix\nEnter 5 to exit\n";
        int choice; cin >> choice;
        string word;
        switch (choice)
        {
        case 1:
            cout << "\nEnter a word to insert: ";
            cin >> word;
            tr.insert(word);
            cout << "Inserted!\n";
            break;
        case 2:
            cout << "\nEnter a word to delete: ";
            cin >> word;
            tr.remove(word);
            break;
        case 3:
            tr.print();
            break;
        case 4:
            cout << "\nEnter a prefix to find words: ";
            cin >> word;
            tr.find(word); 
            break;
        default:
            return 0;
        }
    }

    tr.insert("apple");
    tr.insert("apricot");
    tr.insert("paint");
    tr.insert("finger");
    tr.insert("keyboard");
    tr.insert("approach");
    tr.insert("map");
    tr.insert("mouse");
    tr.insert("minecraft");
    tr.insert("apology");
    tr.insert("key");
    tr.print();
    cout << "prefix: ke\n";
    tr.find("ke");
    cout << "prefix: app\n";
    tr.find("app");
    cout << "prefix: ap\n";
    tr.find("ap");
}