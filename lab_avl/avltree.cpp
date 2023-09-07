/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * temp = t->right;
    t->right = temp->left;

    temp->left = t;

    int left2 = heightOrNeg1(t->left);
    int right2 = heightOrNeg1(t->right);
    t->height = std::max(left2, right2) + 1;

    t = temp;

    left2 = heightOrNeg1(t->left);
    right2 = heightOrNeg1(t->right);
    t->height = std::max(left2, right2) + 1;
    }

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * temp = t->left;
    t->left = temp->right;

    temp->right = t;

    int left2 = heightOrNeg1(t->left);
    int right2 = heightOrNeg1(t->right);
    t->height = std::max(left2, right2) + 1;

    t = temp;

    left2 = heightOrNeg1(t->left);
    right2 = heightOrNeg1(t->right);
    t->height = std::max(left2, right2) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    //opposite of rotateLeftRight
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == NULL) {
        return;
    }
    int right2 = heightOrNeg1(subtree->right);
    int left2 = heightOrNeg1(subtree->left);
    int isBalance = right2 - left2;

    if (isBalance == -2) {
      if (heightOrNeg1(subtree->left->left)>=heightOrNeg1(subtree->left->right)){
            rotateRight(subtree);
        }
        else {
            rotateLeftRight(subtree);
        }
    }

    else if (isBalance == 2) {
      if (heightOrNeg1(subtree->right->right) >= heightOrNeg1(subtree->right->left)){
            rotateLeft(subtree);
        }
        else {
            rotateRightLeft(subtree);
        }
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
     if (subtree == NULL) {
		subtree = new Node(key,value);
		return;
	}
	else if (key < subtree->key) {
        insert(subtree->left, key, value);
  }
    else if (key > subtree->key) {
        insert(subtree->right, key, value);
  }
  int left2 = heightOrNeg1(subtree->left);
  int right2 = heightOrNeg1(subtree->right);
	subtree->height = 1 + std::max(left2, right2);
	rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL){
        return;
}
    if (key < subtree->key) {
        // your code here
        remove(subtree -> left, key);
    }
    else if (key > subtree->key) {
        // your code here
        remove(subtree -> right, key);
    }
    else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        }
        else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node * rTemp = subtree->left;
            while(rTemp->right != NULL) {
            rTemp = rTemp->right;
          }
          swap (rTemp, subtree);
          remove (subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
            Node* childNode = subtree->left != NULL ? subtree->left : subtree->right;
            delete subtree;
            subtree = childNode;
      }
        // your code here
    }
    //moved rebalance out due to tests remove big and remove small failing
    rebalance(subtree);

}
