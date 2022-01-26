#include <iostream>
#include <queue>
#include <functional>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

template <typename T>
class Stack{
public:
    T* values;
    int sizeFeild;
public:
    void push(T value);
    T pop();
    //pop off top
    T top();
    //returns top value without removing it
    int size();
    //size
    bool isEmpty();
    //checks if empty
};

template<typename T>
void Stack<T>::push(T value)
{

}

template<typename T>
T Stack<T>::pop()
{

}

template<typename T>
T Stack<T>::top()
{

}

template<typename T>
int Stack<T>::size()
{

}

template<typename T>
bool Stack<T>::isEmpty()
{

}


TEST(TestStack, Push1TestSizeAndValues) {
    Stack<int> s;
    s.push(1);
    ASSERT_EQ(s.size(), 1);
    ASSERT_EQ(s.pop(), 1);
}

TEST(TestStack, Push3TestSizeAndValues) {
    Stack<int> s;
    s.push(4);
    s.push(5);
    s.push(6);
    ASSERT_EQ(s.size(), 3);
    ASSERT_EQ(s.pop(), 6);
    ASSERT_EQ(s.pop(), 5);
    ASSERT_EQ(s.pop(), 4);
}

TEST(TestStack, Push50TestSizeAndValues) {
    Stack<int> s;
    for(int i = 0; i < 50; i++){
        s.push(i);
    }
    ASSERT_EQ(s.size(), 50);
    for(int i = 0; i < 50; i++){
        ASSERT_EQ(s.pop(), 49-i);
    }
}

TEST(TestStack, PopTest1) {
    Stack<int> s;
    s.push(6);
    s.push(7);
    s.push(8);
    ASSERT_EQ(s.size(), 3);
    ASSERT_EQ(s.top(), 8);
    s.pop();
    ASSERT_EQ(s.size(), 2);
    ASSERT_EQ(s.top(), 7);
}

TEST(TestStack, PopTest2) {
    Stack<int> s;
    s.push(6);
    s.push(7);
    s.push(8);
    ASSERT_EQ(s.size(), 3);
    ASSERT_EQ(s.pop(), 8);
    ASSERT_EQ(s.size(), 2);
}

TEST(TestStack, TopTest) {
    Stack<int> s;
    s.push(6);
    s.push(7);
    s.push(8);
    ASSERT_EQ(s.top(), 8);
    s.push(9);
    ASSERT_EQ(s.top(), 9);
}

TEST(TestStack, SizeTestEmpty) {
    Stack<int> s;
    ASSERT_EQ(s.size(), 0);
}

TEST(TestStack, SizeTest1) {
    Stack<int> s;
    s.push(6);
    ASSERT_EQ(s.size(), 1);
}

TEST(TestStack, SizeTest2) {
    Stack<int> s;
    s.push(6);
    s.push(7);
    s.push(8);
    ASSERT_EQ(s.size(), 3);
}

TEST(TestStack, EmptyTestTrue) {
    Stack<int> s;
    ASSERT_TRUE(s.isEmpty());
    s.push(6);
    ASSERT_FALSE(s.isEmpty());
    s.push(7);
    s.push(8);
    ASSERT_FALSE(s.isEmpty());
}

//template <typename T>
//class myVector {
//private:
//    vector<T> values;
//public:
//    myVector();
//    void push_back(T v);
//    T get(int index);
//    int size();
//};

//template <typename T>
//myVector<T>::myVector()
//{
//}

//template <typename T>
//void myVector<T>::push_back(T v)
//{
//    values.push_back(v);
//}

//template <typename T>
//T myVector<T>::get(int index)
//{
//    return values[index];
//}

//template <typename T>
//int myVector<T>::size()
//{
//    return values.size();
//}

//TEST(TestVector, NewVectorIsEmpty) {
//    myVector<double> v;
////    ASSERT_TRUE(v.size() == 0);
//    ASSERT_EQ(v.size(), 0);
//}

//TEST(TestVector, SizeIsOneAfterOnePushBack) {
//    myVector<double> v;
//    v.push_back(37);
//    ASSERT_EQ(v.size(), 1);
//}

//TEST(TestVector, PushTwoValuesAndCheckSize){
//    myVector<double> v;
//    v.push_back(1);
//    v.push_back(49);
//    ASSERT_EQ(v.get(0), 1);
//    ASSERT_EQ(v.get(1), 49);
//    ASSERT_EQ(v.size(), 2);
//}

//TEST(TestVector, CanRetrievePushedValue) {
//    myVector<double> v;
//    v.push_back(37);
//    ASSERT_EQ(v.get(0), 37);
//}

//TEST(TestVector, Push50Things){
//    myVector<double> v;
//    for(int i = 0; i < 50; i++){
//        v.push_back(i);
//        ASSERT_EQ(v.get(i), i);
//    }
//    ASSERT_EQ(v.size(), 50);
//}

//TEST(TestVector, Push50ThingsAgain){
//    myVector<double> v;
//    for(int i = 0; i < 50; i++){
//        v.push_back(i);
//    }
//    for(int i = 0; i < 50; i++){
//        ASSERT_EQ(v.get(i), i);
//    }
//    ASSERT_EQ(v.size(), 50);
//}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


