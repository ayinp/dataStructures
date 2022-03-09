#include <iostream>
#include <queue>
#include <functional>
#include <vector>

#include "gtest/gtest.h"

template<typename T>
class BSTree;


//NODE
using namespace std;
template<typename T>
class Node{
private:
    T value;
    Node* right = nullptr;
    Node* left = nullptr;
    int height = 0;
public:
    Node();
    ~Node();
    bool includes(T val);
    bool insert(T val, Node<T> *&myPointer);
    bool remove(T val, Node<T> *&myPointer);
    friend BSTree<T>;
    void inOrder(vector<T>& vec);
    void preOrder(vector<T>& vec);
    void postOrder(vector<T>& vec);
    void updateHeight();
    int heightChild(bool isLeft);
    int balanceFactor();
    void rebalance(Node<T> *&myPointer);
    void rotateLeft(Node<T>*& myPointer);
    void rotateRight(Node<T>*& myPointer);
};

template<typename T>
Node<T>::Node()
{

}

template<typename T>
Node<T>::~Node()
{
    delete left;
    delete right;

}

template<typename T>
bool Node<T>::includes(T val)
{
    if(val == value){
        return true;
    }
    if(val > value && right != nullptr){
        return right->includes(val);
    }
    if(val < value & left != nullptr){
        return left->includes(val);
    }
    return false;
}

template<typename T>
bool Node<T>::insert(T val, Node<T>*& myPointer)
{
    bool in = false;
    if(val > value && right != nullptr){
        in = right->insert(val, right);
    }
    else if(val < value && left != nullptr){
        in = left->insert(val, left);
    }
    else if(val > value && right == nullptr){
        right = new Node<T>;
        right->value = val;
        in = true;
    }
    else if(val < value && left == nullptr){
        left = new Node<T>;
        left->value = val;
        in = true;
    }
    updateHeight();
    if(balanceFactor() > 1 || balanceFactor() < -1){
        rebalance(myPointer);
    }
    return in;
}

template<typename T>
bool Node<T>::remove(T val, Node<T>*& myPointer)
{
    if(val == value){
        if(right == nullptr && left == nullptr){
            myPointer = nullptr;
            delete this;
            return true;
        }
        if(right == nullptr){
            myPointer = left;
            left = nullptr;
            delete this;
            return true;
        }
        if(left == nullptr){
            myPointer = right;
            right = nullptr;
            delete this;
            return true;
        }
        Node<T>* rightMost = left;
        Node<T>* RMParent = this;
        if(rightMost->right != nullptr){
            while(rightMost->right){
                RMParent = rightMost;
                rightMost = rightMost->right;
            }
            value = rightMost->value;
            rightMost->remove(value, RMParent->right);
            updateHeight();
            if(balanceFactor() > 1 || balanceFactor() < -1){
                rebalance(myPointer);
            }
            return true;
        }
        else{
            value = rightMost->value;
            rightMost->remove(value, RMParent->left);
            updateHeight();
            if(balanceFactor() > 1 || balanceFactor() < -1){
                rebalance(myPointer);
            }
            return true;
        }
    }
    bool in = false;
    if(val > value && right != nullptr){
        in = right->remove(val, right);
    }
    else if(val < value && left != nullptr){
        in = left->remove(val, left);
    }
    updateHeight();

    return in;
}

template<typename T>
void Node<T>::inOrder(vector<T> &vec)
{
    if(left){
        left->inOrder(vec);
    }
    vec.push_back(value);
    if(right){
        right->inOrder(vec);
    }

}

template<typename T>
void Node<T>::preOrder(vector<T> &vec)
{
    vec.push_back(value);
    if(left){
        left->preOrder(vec);
    }
    if(right){
        right->preOrder(vec);
    }
}

template<typename T>
void Node<T>::postOrder(vector<T> &vec)
{
    if(left){
        left->postOrder(vec);
    }
    if(right){
        right->postOrder(vec);
    }
    vec.push_back(value);
}

template<typename T>
void Node<T>::updateHeight()
{
    if(heightChild(true) > heightChild(false)){
        height = heightChild(true) + 1;
    }
    else{
        height = heightChild(false) + 1;
    }
}

template<typename T>
int Node<T>::heightChild(bool isLeft)
{
    if(isLeft){
        if(left == nullptr){
            return -1;
        }
        //not null
        return left->height;
    }
    //not left
    if(right == nullptr){
        return -1;
    }
    //not null
    return right->height;
}

template<typename T>
int Node<T>::balanceFactor()
{
    return heightChild(true)-heightChild(false);
}

template<typename T>
void Node<T>::rebalance(Node<T>*& myPointer)
{
    if(balanceFactor() > 0 && left->balanceFactor() > 0){
        rotateRight(myPointer);
    }
    else if(balanceFactor() > 0 && left->balanceFactor() < 0){
        left->rotateLeft(left);
        rotateRight(myPointer);
    }
    else if(balanceFactor() < 0 && right->balanceFactor() > 0){
        right->rotateRight(right);
        rotateLeft(myPointer);
    }
    else if(balanceFactor() < 0 && right->balanceFactor() < 0){
        rotateLeft(myPointer);
    }
}

template<typename T>
void Node<T>::rotateLeft(Node<T>*& myPointer)
{
    Node<T>* P = this;
    Node<T>* Q = right;
    Node<T>* A = left;
    Node<T>* B = right->left;
    Node<T>* C = right->right;

    P->right = B;
    Q->left = P;
    myPointer = Q;
}

template<typename T>
void Node<T>::rotateRight(Node<T>*& myPointer)
{
    Node<T>* Q = this;
    Node<T>* P = left;
    Node<T>* A = left->left;
    Node<T>* B = left->right;
    Node<T>* C = right;

    Q->left = B;
    P->right = Q;
    myPointer = P;
}





//TREE
template<typename T>
class BSTree{
private:
    Node<T>* root = nullptr;
    int sz = 0;
public:
    BSTree();
    ~BSTree();
    bool includes(T value); //done
    void insert(T value);   //done
    void remove(T value);
    vector<T> inOrder();
    vector<T> preOrder();
    vector<T> postOrder();
    int size() { return sz; };             //done
    bool isEmpty() { return size() == 0; } // done

};

template<typename T>
BSTree<T>::BSTree()
{

}

template<typename T>
BSTree<T>::~BSTree()
{
    delete root;
}

template<typename T>
bool BSTree<T>::includes(T value)
{
    if(root == nullptr){
        return false; // :(
    }
    if(value == root->value){
        return true;
    }
    if(value > root->value && root->right != nullptr){
        return root->right->includes(value);
    }
    if(value < root->value && root->left != nullptr){
        return root->left->includes(value);
    }
    return false;
}

template<typename T>
void BSTree<T>::insert(T value)
{
    if(root == nullptr){
        sz++;
        root = new Node<T>;
        root->value = value;
    }
    else{

        if(value > root->value && root->right != nullptr){
            if(root->right->insert(value, root->right)){
                sz++;
            }
        }
        else if(value < root->value && root->left != nullptr){
            if(root->left->insert(value, root->left)){
                sz++;
            }
        }
        else if (value > root->value && root->right == nullptr){
            root->right = new Node<T>;
            root->right->value = value;
            sz++;
        }
        else if(value < root->value && root->left == nullptr){
            root->left = new Node<T>;
            root->left->value = value;
            sz++;
        }

    }
    if(root->balanceFactor() > 1 || root->balanceFactor() < -1){
        root->rebalance(root);
    }

}

template<typename T>
void BSTree<T>::remove(T value)
{
    if(root != nullptr){
        if(root->remove(value, root)){
            sz--;
        }
        if(root){
            if(root->balanceFactor() > 1 || root->balanceFactor() < -1){
                root->rebalance(root);
            }
        }
        return;
    }

}

template<typename T>
vector<T> BSTree<T>::inOrder()
{
    vector<T> list;
    if(root != nullptr){
        root->inOrder(list);
    }
    return list;
}

template<typename T>
vector<T> BSTree<T>::preOrder()
{
    vector<T> list;
    if(root != nullptr){
        root->preOrder(list);
    }
    return list;
}

template<typename T>
vector<T> BSTree<T>::postOrder()
{
    vector<T> list;
    if(root != nullptr){
        root->postOrder(list);
    }
    return list;
}



TEST(TestTree, emptySizeTest){
    BSTree<int> t;
    ASSERT_TRUE(t.isEmpty());
    ASSERT_EQ(t.size(), 0);
}

TEST(TestTree, emptyAndSizeTestMore){
    BSTree<int> t;
    t.insert(2);
    t.insert(3);
    t.insert(1);
    t.insert(5);
    t.insert(9);
    ASSERT_FALSE(t.isEmpty());
    ASSERT_EQ(t.size(), 5);
    t.insert(6);
    t.insert(4);
    t.insert(8);
    t.insert(7);
    ASSERT_FALSE(t.isEmpty());
    ASSERT_EQ(t.size(), 9);
    t.remove(2);
    t.remove(5);
    t.remove(1);
    t.remove(3);
    t.remove(9);
    t.remove(100);
    ASSERT_FALSE(t.isEmpty());
    ASSERT_EQ(t.size(), 4);
    t.remove(6);
    t.remove(4);
    t.remove(8);
    t.remove(7);
    ASSERT_TRUE(t.isEmpty());
    ASSERT_EQ(t.size(), 0);
}

TEST(TestTree, includesTestEmpty){
    BSTree<int> t;
    ASSERT_FALSE(t.includes(100));
    ASSERT_FALSE(t.includes(4));
}

TEST(TestTree, includesTestOne){
    BSTree<int> t;
    t.insert(4);
    ASSERT_FALSE(t.includes(100));
    ASSERT_TRUE(t.includes(4));
}

TEST(TestTree, includesTestMore){
    BSTree<int> t;
    t.insert(2);
    t.insert(3);
    t.insert(1);
    t.insert(5);
    t.insert(9);
    ASSERT_FALSE(t.includes(4));
    ASSERT_TRUE(t.includes(3));
    t.insert(6);
    t.insert(4);
    t.insert(8);
    t.insert(7);
    ASSERT_FALSE(t.includes(100));
    ASSERT_TRUE(t.includes(4));
    ASSERT_TRUE(t.includes(3));
    t.remove(2);
    t.remove(3);
    t.remove(1);
    t.remove(5);
    t.remove(9);
    ASSERT_FALSE(t.includes(3));
    ASSERT_FALSE(t.includes(2));
    ASSERT_FALSE(t.includes(1));
    ASSERT_FALSE(t.includes(5));
    ASSERT_FALSE(t.includes(9));
    ASSERT_TRUE(t.includes(4));
    ASSERT_TRUE(t.includes(6));
    ASSERT_TRUE(t.includes(8));
    ASSERT_TRUE(t.includes(7));
    t.remove(6);
    t.remove(4);
    t.remove(8);
    t.remove(7);
    ASSERT_FALSE(t.includes(100));
    ASSERT_FALSE(t.includes(4));
}

TEST(TestTree, inOrderTest){
    BSTree<int> t;
    t.insert(2);
    t.insert(3);
    t.insert(1);
    t.insert(5);
    t.insert(9);
    t.insert(6);
    t.insert(4);
    t.insert(8);
    t.insert(7);
    vector<int> vec = t.inOrder();
    for(int i = 1; i < t.size(); i++ ){
        if(vec[i] > vec[i-1]){
            ASSERT_TRUE(true);
        }
    }
}

TEST(TestTree, preOrderTest){
    BSTree<int> t;
    t.insert(2);
    t.insert(3);
    t.insert(1);
    t.insert(5);
    t.insert(9);
    t.insert(6);
    t.insert(4);
    t.insert(8);
    t.insert(7);
    vector<int> vec = t.preOrder();
    ASSERT_TRUE(vec.size()==t.size());
    for(int i = 1; i <= 9; i++){
        bool found = false;
        for(int j = 0; j < vec.size(); j++){
            if(vec[j] == i){
                found = true;
            }
        }
        ASSERT_TRUE(found);
    }
}

TEST(TestTree, postOrderTest){
    BSTree<int> t;
    t.insert(2);
    t.insert(3);
    t.insert(1);
    t.insert(5);
    t.insert(9);
    t.insert(6);
    t.insert(4);
    t.insert(8);
    t.insert(7);
    vector<int> vec = t.postOrder();
    ASSERT_TRUE(vec.size()==t.size());
    for(int i = 1; i <= 9; i++){
        bool found = false;
        for(int j = 0; j < vec.size(); j++){
            if(vec[j] == i){
                found = true;
            }
        }
        ASSERT_TRUE(found);
    }
}

TEST(TestTree, specialTest){
    BSTree<int> t;
    t.insert(30);
    t.insert(5);
    t.insert(35);
    t.insert(32);
    t.insert(40);
    t.insert(45);
}

//TEST(TestDeque, emptyTest){
//    Deque<int> d;
//    ASSERT_TRUE(d.isEmpty());
//}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

