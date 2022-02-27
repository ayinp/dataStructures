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
public:
    Node();
    bool includes(T val);
    void insert(T val);
    friend BSTree<T>;
};

template<typename T>
Node<T>::Node()
{

}

template<typename T>
bool Node<T>::includes(T val)
{
    if(val == value){
        return true;
    }
    if(val > value && right != nullptr){
        return right->includes(value);
    }
    if(val < value & left != nullptr){
        return left->includes(value);
    }
    return false;
}

template<typename T>
void Node<T>::insert(T val)
{
    if(val > value && right != nullptr){
        right->insert(val);
    }
    else if(val < value && left != nullptr){
        left->insert(val);
    }
    else if(val > value && right == nullptr){
        right = new Node<T>;
        right->value = val;
    }
    else{
        left = new Node<T>;
        left->value = val;
    }
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
    void insert(T value);
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
    else if(!includes(value)){
        sz++;
        if(value > root->value && root->right != nullptr){
            root->right->insert(value);
        }
        else if(value < root->value && root->left != nullptr){
            root->left->insert(value);
        }
        else if (value > root->value && root->right == nullptr){
            root->right = new Node<T>;
            root->right->value = value;
        }
        else{
            root->left = new Node<T>;
            root->left->value = value;
        }

    }

}

template<typename T>
void BSTree<T>::remove(T value)
{

}

template<typename T>
vector<T> BSTree<T>::inOrder()
{

}

template<typename T>
vector<T> BSTree<T>::preOrder()
{

}

template<typename T>
vector<T> BSTree<T>::postOrder()
{

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
    //    t.remove(2);
    //    t.remove(3);
    //    t.remove(1);
    //    t.remove(5);
    //    t.remove(9);
    //    ASSERT_FALSE(t.isEmpty());
    //    ASSERT_EQ(t.size(), 4);
    //    t.remove(6);
    //    t.remove(4);
    //    t.remove(8);
    //    t.remove(7);
    //    ASSERT_TRUE(t.isEmpty());
    //    ASSERT_EQ(t.size(), 0);
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
    //    t.remove(2);
    //    t.remove(3);
    //    t.remove(1);
    //    t.remove(5);
    //    t.remove(9);
    //    ASSERT_FALSE(t.includes(3));
    //    ASSERT_FALSE(t.includes(2));
    //    ASSERT_FALSE(t.includes(1));
    //    ASSERT_FALSE(t.includes(5));
    //    ASSERT_FALSE(t.includes(9));
    //    ASSERT_TRUE(t.includes(4));
    //    ASSERT_TRUE(t.includes(6));
    //    ASSERT_TRUE(t.includes(8));
    //    ASSERT_TRUE(t.includes(7));
    //    t.remove(6);
    //    t.remove(4);
    //    t.remove(8);
    //    t.remove(7);
    //    ASSERT_FALSE(t.includes(100));
    //    ASSERT_FALSE(t.includes(4));
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

//TEST(TestDeque, emptyTest){
//    Deque<int> d;
//    ASSERT_TRUE(d.isEmpty());
//}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



