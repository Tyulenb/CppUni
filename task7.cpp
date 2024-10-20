#include <iostream>

using namespace std;

struct Node {
	int data;
	Node* parent;
	Node* left;
	Node* right;
	int color;
};

class RBtree {
private:
	Node* root;
	Node* TNULL;

	void initialize(Node* node, Node* parent) {
		node->data = 0;
		node->parent = parent;
		node->left = nullptr;
		node->right = nullptr;
		node->color = 0;
	}

	void kerBypass(Node* node) {
		if (node != TNULL) {
			cout << node->data << " ";
			kerBypass(node->left);
			kerBypass(node->right);
		}
	}

	Node* kerSearch(Node* node, int key) {
		if (node == TNULL || key == node->data) {
			return node;
		}

		if (key < node->data) {
			return kerSearch(node->left, key);
		}
		return kerSearch(node->right, key);
	}

	void leftRotate(Node* x) {
		Node* y = x->right; //y = right child of x (y > x)
		x->right = y->left; //right child of x is now left child of y because left of y is bigger than x but less than y

		if (y->left != TNULL) { //if the left node of y is not null x becomes parent of y left child
			y->left->parent = x;
 		}
		y->parent = x->parent; // x parent becomes parent of y
		if (x->parent == nullptr) { // if x was the root
			this->root = y;
		}
		else if (x == x->parent->left) { // if x was left child of its parent, y becomes left child of x parent
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x; // x becomes left child of y
		x->parent = y; //y becomes parent of x
	}

	void rightRotate(Node* x) {
		Node* y = x->left; //y = left child of x (x > y)
		x->left = y->right; // left child of x is now right child of y 
		if (y->right != TNULL) {// if the right child of y is not null x becomes parent of y right child
			y->right->parent = x;
		}
		y->parent = x->parent; // y parent becomes parent of x
		if (x->parent == nullptr) { //if x was root
			this->root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->right = x; // x becomes left child of y
		x->parent = y; //y becomes parent of x
	}

	void changePos(Node* u, Node* v) {//change postions of 2 nodes
		if (u->parent == nullptr) {
			root = v;
		}
		else if(u==u->parent->left){
			u->parent->left = v;
		}
		else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	Node* minimum(Node* node) { //find mininmum in the subtree
		while (node->left != TNULL) {
			node = node->left;
		}
		return node;
	}

	Node* maximum(Node* node) { //find maximum in the subtree
		while (node->right != TNULL) {
			node = node->right;
		}
		return node;
	}

	void kerDeleteNode(Node* node, int key) {
		Node* z = TNULL;
		Node* x = nullptr;
		Node* y = nullptr;
		while (node != TNULL) { //finding the node
			if (node->data == key) {
				z = node;
			}

			if (node->data <= key) {
				node = node->right;
			}
			else {
				node = node->left;
			}
		}

		if (z == TNULL) {
			cout << "There is no such key in the tree.\n";
			return;
		}

		y = z;
		int origColor = y->color; // save the orig color of the node

		if (z->right == TNULL) { // if the right child of z is null
			x = z->left;
			changePos(z, z->left);
		}
		else if (z->left == TNULL) { // if the left child of z is null
			x = z->right;
			changePos(z, z->right);
		}
		else { // if z has 2 childs
			y = minimum(z->right); //find the min in right subtree (also we can find max if left subtree)
			//y = maximum(z->left); //Alternative

			origColor = y->color; // define new orig color, now it is the color of min
			x = y->right; //x is now right child of y
			//x=y->left; //Alternative

			if (y->parent == z) { 
				x->parent = y;
			}
			else {
				changePos(y, y->right); //change y and it's right child (y < y->right)
				y->right = z->right; //right child of z is now right child of y
				y->right->parent = y; //set parent y to new child of y(from prev step)

				/* //Alternative
				changePos(y,y->left);
				y->left = z->left;
				y->left->parent = y;
				*/
			}

			changePos(z, y); //change places of z and y
			y->left = z->left; //left child of z is now left child of y
			y->left->parent = y; //set parent y to new child of y(from prev step) 
			y->color = z->color; 

			/* //Alternative
			y->right = z->right; 
			y->right->parent = y; 
			y->color = z->color; 
			*/

		}
		delete z;
		if (origColor == 0) { // if node which we deleted was balck, we should rebalance our tree
			fixDel(x);
		}
	}

	void fixDel(Node* x) {
		Node* s;
		while (x != root && x->color == 0) {
			if (x == x->parent->left) { // x is left
				s = x->parent->right; //s is right to x now
				if (s->color == 1) { //if s is red
					s->color = 0; //set color to black
					x->parent->color = 1; // set parent color to red
					leftRotate(x->parent); 
					s = x->parent->right;
				}

				if (s->left->color == 0 && s->right->color == 0) {
					s->color = 1;
					x = x->parent;
				}
				else {
					if (s->right->color == 0) {
						s->left->color = 0;
						s->color = 1;
						rightRotate(s);
						s = x->parent->right;
					}

					s->color = s->parent->color;
					x->parent->color = 0;
					s->right->color = 0;
					leftRotate(x->parent);
					x = root;
				}
			}
			else {
				s = x->parent->left;
				if (s->color == 1) {
					s->color = 0;
					x->parent->color = 1;
					rightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->left->color == 0 && s->right->color == 0) {
					s->color = 1;
					x = x->parent;
				}
				else {
					if (s->left->color == 0) {
						s->right->color = 0;
						s->color = 0;
						leftRotate(s);
						s = x->parent->left;
					}

					s->color = x->parent->color;
					x->parent->color = 0;
					s->left->color = 0;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = 0;
	}

	void fixIns(Node* x) {
		Node* y;
		while (x->parent->color == 1) {
			if (x->parent == x->parent->parent->right) {
				y = x->parent->parent->left;
				if (y->color == 1) {
					y->color = 0;
					x->parent->color = 0;
					x->parent->parent->color = 1;
					x = x->parent->parent;
				}
				else {
					if (x == x->parent->left) {
						x = x->parent;
						rightRotate(x);
					}
					x->parent->color = 0;
					x->parent->parent->color = 1;
					leftRotate(x->parent->parent);
				}
			}
			else {
				y = x->parent->parent->right;

				if (y->color == 1) {
					y->color = 0;
					x->parent->color = 0;
					x->parent->parent->color = 1;
					x = x->parent->parent;
				}
				else {
					if (x == x->parent->right) {
						x = x->parent;
						leftRotate(x);
					}
					x->parent->color = 0;
					x->parent->parent->color = 1;
					rightRotate(x->parent->parent);
				}
			}
			if (x == root) {
				break;
			}
		}
		root->color = 0;
	}

	void kerPrint(Node* root, string ind, bool last) { //rewrite
		if (root != TNULL) {
			cout << ind;
			if (last) {
				cout << "R-----";
				ind += "    ";
			}
			else {
				cout << "L-----";
				ind += "|   ";
			}

			string color = root->color ? "RED" : "BLACK";
			cout << root->data<< "(" << color << ")" << endl;
			kerPrint(root->left, ind, false);
			kerPrint(root->right, ind, true);
		}
	}

public:
	RBtree() {
		TNULL = new Node;
		TNULL->color = 0;
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		root = TNULL;
	}

	void bypass() {
		kerBypass(this->root);
	}

	Node* search(int data) {
		return kerSearch(this->root, data);
	}

	void printTree() {
		if (root) {
			kerPrint(this->root, "", true);
		}
	}

	void insert(int data) {
		Node* node = new Node;
		node->parent = nullptr;
		node->data = data;
		node->right = TNULL;
		node->left = TNULL;
		node->color = 1;

		Node* y = nullptr;
		Node* x = this->root;

		while (x != TNULL) {
			y = x;
			if (node->data < x->data) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}

		node->parent = y;
		if (y == nullptr) {
			root = node;
		}
		else if (node->data < y->data) {
			y->left = node;
		}
		else {
			y->right = node;
		}

		if (node->parent == nullptr) {
			node->color = 0;
			return;
		}

		if (node->parent->parent == nullptr) {
			return;
		}

		fixIns(node);
	}

	void deleteNode(int data) {
		kerDeleteNode(this->root, data);
	}

};

int main()
{
	RBtree tree;
	tree.insert(10);
	tree.insert(15);
	tree.insert(20);
	tree.insert(1);
	tree.insert(25);
	tree.insert(30);
	tree.insert(5);

	tree.deleteNode(25);

	tree.printTree();
}