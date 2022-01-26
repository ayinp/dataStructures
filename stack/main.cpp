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
    int size;
public:
    void push(T value);
    T pop();
    T top();
    int findSize();
    bool isEmpty();
};

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


