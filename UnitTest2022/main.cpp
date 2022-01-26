#include <iostream>
#include <queue>
#include <functional>
#include <vector>

#include "gtest/gtest.h"

using namespace std;


class myVector {
private:
    vector<double> values;
public:
    myVector();
    void push_back(double v);
    double get(int index);
    int size();
};

myVector::myVector()
{
}

void myVector::push_back(double v)
{
    values.push_back(v);
}

double myVector::get(int index)
{
    return values[index];
}

int myVector::size()
{
    return values.size();
}

TEST(TestVector, NewVectorIsEmpty) {
    myVector v;
//    ASSERT_TRUE(v.size() == 0);
    ASSERT_EQ(v.size(), 0);
}

TEST(TestVector, SizeIsOneAfterOnePushBack) {
    myVector v;
    v.push_back(37);
    ASSERT_EQ(v.size(), 1);
}

TEST(TestVector, PushTwoValuesAndCheckSize){
    myVector v;
    v.push_back(1);
    v.push_back(49);
    ASSERT_EQ(v.get(0), 1);
    ASSERT_EQ(v.get(1), 49);
    ASSERT_EQ(v.size(), 2);
}

TEST(TestVector, CanRetrievePushedValue) {
    myVector v;
    v.push_back(37);
    ASSERT_EQ(v.get(0), 37);
}

TEST(TestVector, Push50Things){
    myVector v;
    for(int i = 0; i < 50; i++){
        v.push_back(i);
        ASSERT_EQ(v.get(i), i);
    }
    ASSERT_EQ(v.size(), 50);
}

TEST(TestVector, Push50ThingsAgain){
    myVector v;
    for(int i = 0; i < 50; i++){
        v.push_back(i);
    }
    for(int i = 0; i < 50; i++){
        ASSERT_EQ(v.get(i), i);
    }
    ASSERT_EQ(v.size(), 50);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


