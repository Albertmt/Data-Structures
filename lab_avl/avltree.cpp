/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K & key) const
{
	return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node * subtree, const K & key) const
{
	if (subtree == NULL)
		return V();
	else if (key == subtree->key)
		return subtree->value;
	else
	{
		if (key < subtree->key)
			return find(subtree->left, key);
		else
			return find(subtree->right, key);
	}
}

template<class K, class V>
int AVLTree<K, V>::max(int a, int b){
	return (a<b)?b:a;
}

template <class K, class V>
int AVLTree<K, V>::balanceFactor(Node * source){
	if(source == NULL)
		return 0;
	return heightOrNeg1(source ->left) - heightOrNeg1(source -> right);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
	Node * b = t ->right;
	t -> right = b -> left;
	b->left = t;
	t = b;
	b = t->left;

	//adjusting heights
	b->height = 1 + max(heightOrNeg1(b->left), heightOrNeg1(b->right));
	t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
	// Implemented for you:
	rotateLeft(t->left);
	rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
	Node * b = t ->left;
	t -> left = b -> right;
	b-> right = t;
	t = b;
	b = t->right;
	
	b->height = 1 + max(heightOrNeg1(b->left), heightOrNeg1(b->right));
	t->height = 1 + max(heightOrNeg1(t->left),heightOrNeg1(t->right));  
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
	rotateRight(t->right);
	rotateLeft(t);

    // your code here
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
	insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node* & subtree, const K & key, const V & value){
	
	//if (key == subtree -> key) return;

	if(subtree == NULL)
		subtree = new Node(key, value);
	else (key > subtree->key) ? insert(subtree->right, key, value)
				  : insert(subtree->left, key, value);
	subtree -> height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
	int balance = balanceFactor(subtree);
	if (balance == 2 && balanceFactor(subtree->left) == 1)
		rotateRight(subtree);
	else if (balance == 2 && balanceFactor(subtree->left) == -1)
		rotateLeftRight(subtree);
	else if (balance == -2 && balanceFactor(subtree ->right) == -1)
		rotateLeft(subtree);
	else if (balance == -2 && balanceFactor(subtree->right) == 1)
		rotateRightLeft(subtree);
    // your code here
}
