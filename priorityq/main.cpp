#include <iostream>
#include <queue>
#include <functional>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

template <typename T>
class PriorityQueue{
public:
    vector<T> things = {};
public:
    PriorityQueue();
    ~PriorityQueue();
    void insert(T value);
    T remove();
    int size();
    bool isEmpty();
};

template<typename T>
PriorityQueue<T>::PriorityQueue()
{
}

template<typename T>
PriorityQueue<T>::~PriorityQueue()
{
}

template<typename T>
void PriorityQueue<T>::insert(T value)
{
}

template<typename T>
T PriorityQueue<T>::remove()
{
}

template<typename T>
int PriorityQueue<T>::size()
{
}

template<typename T>
bool PriorityQueue<T>::isEmpty()
{
}

TEST(TestPQ, SizeTestEmpty) {
    PriorityQueue<int> s;
    ASSERT_EQ(s.size(), 0);
}

TEST(TestPQ, SizeTest1) {
    PriorityQueue<int> s;
    s.insert(6);
    ASSERT_EQ(s.size(), 1);
}

TEST(TestPQ, SizeTest2) {
    PriorityQueue<int> s;
    s.insert(6);
    s.insert(7);
    s.insert(8);
    ASSERT_EQ(s.size(), 3);
}

TEST(TestPQ, EmptyTest) {
    PriorityQueue<int> s;
    ASSERT_TRUE(s.isEmpty());
    s.insert(6);
    ASSERT_FALSE(s.isEmpty());
    s.insert(7);
    s.insert(8);
    ASSERT_FALSE(s.isEmpty());
    s.remove();
    s.remove();
    s.remove();
    ASSERT_TRUE(s.isEmpty());
}

TEST(TestPQ, TestHeapProperty) {
    PriorityQueue<int> s;
    for(int i = 0; i < 50; i++){
        s.insert(i);
    }
    ASSERT_EQ(s.size(), 50);
    int last = s.remove();
    for(int i = 0; i < 49; i++){
        ASSERT_LE(s.remove(), last);
    }
}

TEST(TestPQ, PopTest1) {
    PriorityQueue<int> s;
    s.insert(6);
    s.insert(7);
    s.insert(8);
    ASSERT_EQ(s.size(), 3);
    ASSERT_EQ(s.remove(), 8);
    ASSERT_EQ(s.size(), 2);
}



TEST(TestPQ, TopTest) {
    PriorityQueue<int> s;
    s.insert(6);
    s.insert(7);
    s.insert(8);
    ASSERT_EQ(s.remove(), 8); // 8 is gone
    s.insert(9); // 9 is here
    ASSERT_EQ(s.remove(), 9); // 9 is gone
    s.insert(5); // 5 is here
    ASSERT_EQ(s.remove(), 7); // 7 is gone
    ASSERT_EQ(s.remove(), 6); // 6 is gone
    ASSERT_EQ(s.remove(), 5); // 5 is gone
    ASSERT_EQ(s.size(), 0); // should be empty
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


