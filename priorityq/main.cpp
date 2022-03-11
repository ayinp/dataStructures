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
    int parentIndex(int childIn);
    int childIndex(bool isLeft, int parentIn);
};

template<typename T>
PriorityQueue<T>::PriorityQueue()
{
}

template<typename T>
PriorityQueue<T>::~PriorityQueue()
{
}

// left child is always parent indecy * 2 + 1
// right child is always parent indecy * 2 + 2
// parent from right child is always /2 - 1
// parent from left child is always /2 - 0.5

template<typename T>
void PriorityQueue<T>::insert(T value)
{
    if(things.empty()){
        things.push_back(value);
        return;
    }
    things.push_back(value);
    int childIn = things.size()-1;
    while(things[childIn] > things[parentIndex(childIn)]){
        swap(things[childIn], things[parentIndex(childIn)]);
        childIn = parentIndex(childIn);
    }
}

template<typename T>
T PriorityQueue<T>::remove()
{
    if(things.empty()){
        return T{};
        //put error guy here
    }
    if(things.size() == 1){
        T value = things[0];
        things.pop_back();
        return value;
    }
    T value = things[0];
    swap(things[size()-1], things[0]);
    things.pop_back();
    int parentIn = 0;
    while(parentIn < things.size()){
        if(childIndex(false, parentIn) < things.size()){
            if(things[childIndex(true, parentIn)] /*left*/ > things[childIndex(false, parentIn)]/*right*/){
                if(things[parentIn] > things[childIndex(true, parentIn)]){
                    swap(things[parentIn], things[childIndex(true, parentIn)]);
                    parentIn = childIndex(true, parentIn);
                }
                else{
                    break;
                }
            }
            //right > left or equal
            else{
                if(things[parentIn] > things[childIndex(false, parentIn)]){
                    swap(things[parentIn], things[childIndex(false, parentIn)]);
                    parentIn = childIndex(false, parentIn);
                    cout << "PARENTIN " << parentIn << endl;
                }
                else{
                    break;
                }
            }
        }
        else{
            if(things[parentIn] < things[childIndex(true, parentIn)]){
                swap(things[parentIn], things[childIndex(true, parentIn)]);
                parentIn = childIndex(true, parentIn);
            }
            else{
                break;
            }
        }

    }
    return value;

}

template<typename T>
int PriorityQueue<T>::size()
{
    return things.size();
}

template<typename T>
bool PriorityQueue<T>::isEmpty()
{
    return things.size() == 0;
}

template<typename T>
int PriorityQueue<T>::parentIndex(int childIn)
{

    return (childIn-1)/2;

}

template<typename T>
int PriorityQueue<T>::childIndex(bool isLeft, int parentIn)
{
    if(isLeft){
        return (parentIn*2)+1;
    }
    return (parentIn*2)+2;
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


