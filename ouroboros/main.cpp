#include <iostream>
#include <queue>
#include <functional>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

template<typename T>
class Deque{
public:
    vector<T> deque;
    T frontIndex;
    T backIndex;
    int sz;
public:
    void pushBack(T){};
    //  Add an item to the back of the queue
    void pushFront(T){};
    //  Add an item to the front of the queue
    T popBack(){return T{};};
    //  Remove/return an item from the back of the queue
    T popFront(){return T{};};
    //  Remove/return an item from the front of the queue
    T back(){return T{};};
    //  return the item from the back of the queue without removing it
    T front(){return T{};};
    //  return the item from the front of the queue without removing it
    bool isEmpty(){return false;};
    //  return TRUE if the queue contains no items
    int size(){return -1;};
    //  return the number of elements in the queue
};

TEST(TestDeque, emptyTest){
    Deque<int> d;
    ASSERT_TRUE(d.isEmpty());
}
TEST(TestDeque, emptyTestAfterPushBack){
    Deque<int> d;
    ASSERT_TRUE(d.isEmpty());
    d.pushBack(2);
    ASSERT_FALSE(d.isEmpty());
    d.pushBack(5);
    d.pushBack(6);
    ASSERT_FALSE(d.isEmpty());
    d.popBack();
    ASSERT_FALSE(d.isEmpty());
    d.popBack();
    d.popBack();
    ASSERT_TRUE(d.isEmpty());
}
TEST(TestDeque, emptyTestAfterPushFront){
    Deque<int> d;
    ASSERT_TRUE(d.isEmpty());
    d.pushFront(2);
    ASSERT_FALSE(d.isEmpty());
    d.pushFront(5);
    d.pushFront(6);
    ASSERT_FALSE(d.isEmpty());
    d.popFront();
    ASSERT_FALSE(d.isEmpty());
    d.popFront();
    d.popFront();
    ASSERT_TRUE(d.isEmpty());
}
TEST(TestDeque, emptyInchwormPushFront){
    Deque<int> d;
    ASSERT_TRUE(d.isEmpty());
    d.pushFront(2);
    ASSERT_FALSE(d.isEmpty());
    d.pushFront(5);
    d.pushFront(6);
    ASSERT_FALSE(d.isEmpty());
    d.popBack();
    ASSERT_FALSE(d.isEmpty());
    d.popBack();
    d.popBack();
    ASSERT_TRUE(d.isEmpty());
}
TEST(TestDeque, emptyInchwormPushBack){
    Deque<int> d;
    ASSERT_TRUE(d.isEmpty());
    d.pushBack(2);
    ASSERT_FALSE(d.isEmpty());
    d.pushBack(5);
    d.pushBack(6);
    ASSERT_FALSE(d.isEmpty());
    d.popFront();
    ASSERT_FALSE(d.isEmpty());
    d.popFront();
    d.popFront();
    ASSERT_TRUE(d.isEmpty());
}
TEST(TestDeque, emptySize){
    Deque<int> d;
    ASSERT_EQ(d.size(), 0);
}
TEST(TestDeque, sizeOneFrontBack){
    Deque<int> d;
    ASSERT_EQ(d.size(), 0);
    d.pushFront(2);
    ASSERT_EQ(d.size(), 1);
    d.popBack();
    ASSERT_EQ(d.size(), 0);
}
TEST(TestDeque, sizeOneFrontFront){
    Deque<int> d;
    ASSERT_EQ(d.size(), 0);
    d.pushFront(2);
    ASSERT_EQ(d.size(), 1);
    d.popFront();
    ASSERT_EQ(d.size(), 0);
}
TEST(TestDeque, sizeOneBackBack){
    Deque<int> d;
    ASSERT_EQ(d.size(), 0);
    d.pushBack(2);
    ASSERT_EQ(d.size(), 1);
    d.popBack();
    ASSERT_EQ(d.size(), 0);
}
TEST(TestDeque, sizeOneBackFront){
    Deque<int> d;
    ASSERT_EQ(d.size(), 0);
    d.pushBack(2);
    ASSERT_EQ(d.size(), 1);
    d.popFront();
    ASSERT_EQ(d.size(), 0);
}
TEST(TestDeque, sizeFiveFrontBack){
    Deque<int> d;
    ASSERT_EQ(d.size(), 0);
    d.pushFront(2);
    d.pushFront(3);
    d.pushFront(7);
    d.pushFront(2);
    d.pushFront(9);
    ASSERT_EQ(d.size(), 5);
    d.popFront();
    d.popFront();
    d.popFront();
    d.popFront();
    d.popFront();
    ASSERT_EQ(d.size(), 0);
}
TEST(TestDeque, sizeFiveFrontFront){
    Deque<int> d;
    ASSERT_EQ(d.size(), 0);
    d.pushFront(2);
    d.pushFront(3);
    d.pushFront(7);
    d.pushFront(2);
    d.pushFront(9);
    ASSERT_EQ(d.size(), 5);
    d.popBack();
    d.popBack();
    d.popBack();
    d.popBack();
    d.popBack();
    ASSERT_EQ(d.size(), 0);
}
TEST(TestDeque, sizeFiveBackBack){
    Deque<int> d;
    ASSERT_EQ(d.size(), 0);
    d.pushBack(2);
    d.pushBack(3);
    d.pushBack(7);
    d.pushBack(2);
    d.pushBack(9);
    ASSERT_EQ(d.size(), 5);
    d.popBack();
    d.popBack();
    d.popBack();
    d.popBack();
    d.popBack();
    ASSERT_EQ(d.size(), 0);
}
TEST(TestDeque, sizeFiveBackFront){
    Deque<int> d;
    ASSERT_EQ(d.size(), 0);
    d.pushBack(2);
    d.pushBack(3);
    d.pushBack(7);
    d.pushBack(2);
    d.pushBack(9);
    ASSERT_EQ(d.size(), 5);
    d.popFront();
    d.popFront();
    d.popFront();
    d.popFront();
    d.popFront();
    ASSERT_EQ(d.size(), 0);
}
TEST(TestDeque, size50FrontBack){
    Deque<int> d;
    for(int i = 0; i < 50; i++){
        d.pushFront(i);
        ASSERT_EQ(d.size(), i+1);
    }
    ASSERT_EQ(d.size(), 50);
    for(int i = 0; i < 50; i++){
        d.popBack();
        ASSERT_EQ(d.size(), 50-i);
    }
    ASSERT_EQ(d.size(), 0);
}
TEST(TestDeque, size50FrontFront){
    Deque<int> d;
    for(int i = 0; i < 50; i++){
        d.pushFront(i);
        ASSERT_EQ(d.size(), i+1);
    }
    ASSERT_EQ(d.size(), 50);
    for(int i = 0; i < 50; i++){
        d.popFront();
        ASSERT_EQ(d.size(), 50-i);
    }
    ASSERT_EQ(d.size(), 0);
}
TEST(TestDeque, size50BackBack){
    Deque<int> d;
    for(int i = 0; i < 50; i++){
        d.pushBack(i);
        ASSERT_EQ(d.size(), i+1);
    }
    ASSERT_EQ(d.size(), 50);
    for(int i = 0; i < 50; i++){
        d.popBack();
        ASSERT_EQ(d.size(), 50-i);
    }
    ASSERT_EQ(d.size(), 0);
}
TEST(TestDeque, size50BackFront){
    Deque<int> d;
    for(int i = 0; i < 50; i++){
        d.pushBack(i);
        ASSERT_EQ(d.size(), i+1);
    }
    ASSERT_EQ(d.size(), 50);
    for(int i = 0; i < 50; i++){
        d.popFront();
        ASSERT_EQ(d.size(), 50-i);
    }
    ASSERT_EQ(d.size(), 0);
}

TEST(TestDeque, frontTestFrontBack){
    Deque<int> d;
    d.pushFront(7);
    ASSERT_EQ(d.front(), 7);
    d.pushFront(6);
    ASSERT_EQ(d.front(), 6);
    d.pushFront(9);
    ASSERT_EQ(d.front(), 9);
    d.popBack();
    ASSERT_EQ(d.front(), 9);
    d.popBack();
    ASSERT_EQ(d.front(), 9);
}
TEST(TestDeque, frontTestFrontFront){
    Deque<int> d;
    d.pushFront(7);
    ASSERT_EQ(d.front(), 7);
    d.pushFront(6);
    ASSERT_EQ(d.front(), 6);
    d.pushFront(9);
    ASSERT_EQ(d.front(), 9);
    d.popFront();
    ASSERT_EQ(d.front(), 6);
    d.popFront();
    ASSERT_EQ(d.front(), 7);
}
TEST(TestDeque, frontTestBackBack){
    Deque<int> d;
    d.pushBack(7);
    ASSERT_EQ(d.front(), 7);
    d.pushBack(6);
    ASSERT_EQ(d.front(), 7);
    d.pushBack(9);
    ASSERT_EQ(d.front(), 7);
    d.popBack();
    ASSERT_EQ(d.front(), 7);
    d.popBack();
    ASSERT_EQ(d.front(), 7);
}
TEST(TestDeque, frontTestBackFront){
    Deque<int> d;
    d.pushBack(7);
    ASSERT_EQ(d.front(), 7);
    d.pushBack(6);
    ASSERT_EQ(d.front(), 7);
    d.pushBack(9);
    ASSERT_EQ(d.front(), 7);
    d.popFront();
    ASSERT_EQ(d.front(), 6);
    d.popFront();
    ASSERT_EQ(d.front(), 9);
}

TEST(TestDeque, backTestFrontBack){
    Deque<int> d;
    d.pushFront(7);
    ASSERT_EQ(d.back(), 7);
    d.pushFront(6);
    ASSERT_EQ(d.back(), 7);
    d.pushFront(9);
    ASSERT_EQ(d.back(), 7);
    d.popBack();
    ASSERT_EQ(d.back(), 6);
    d.popBack();
    ASSERT_EQ(d.back(), 9);
}
TEST(TestDeque, backTestFrontFront){
    Deque<int> d;
    d.pushFront(7);
    ASSERT_EQ(d.back(), 7);
    d.pushFront(6);
    ASSERT_EQ(d.back(), 7);
    d.pushFront(9);
    ASSERT_EQ(d.back(), 7);
    d.popFront();
    ASSERT_EQ(d.back(), 7);
    d.popFront();
    ASSERT_EQ(d.back(), 7);
}
TEST(TestDeque, backTestBackBack){
    Deque<int> d;
    d.pushBack(7);
    ASSERT_EQ(d.back(), 7);
    d.pushBack(6);
    ASSERT_EQ(d.back(), 6);
    d.pushBack(9);
    ASSERT_EQ(d.back(), 9);
    d.popBack();
    ASSERT_EQ(d.back(), 6);
    d.popBack();
    ASSERT_EQ(d.back(), 7);
}
TEST(TestDeque, backTestBackFront){
    Deque<int> d;
    d.pushBack(7);
    ASSERT_EQ(d.back(), 7);
    d.pushBack(6);
    ASSERT_EQ(d.back(), 6);
    d.pushBack(9);
    ASSERT_EQ(d.back(), 9);
    d.popFront();
    ASSERT_EQ(d.back(), 9);
    d.popFront();
    ASSERT_EQ(d.back(), 9);
}
TEST(TestDeque, popFrontPushFront){
    Deque<int> d;
    d.pushFront(5);
    d.pushFront(1);
    d.pushFront(7);
    ASSERT_EQ(d.popFront(), 7);
    ASSERT_EQ(d.popFront(), 1);
    ASSERT_EQ(d.popFront(), 5);
}
TEST(TestDeque, popFrontPushBack){
    Deque<int> d;
    d.pushBack(5);
    d.pushBack(1);
    d.pushBack(7);
    ASSERT_EQ(d.popFront(), 5);
    ASSERT_EQ(d.popFront(), 1);
    ASSERT_EQ(d.popFront(), 7);
}
TEST(TestDeque, popBackPushFront){
    Deque<int> d;
    d.pushFront(5);
    d.pushFront(1);
    d.pushFront(7);
    ASSERT_EQ(d.popBack(), 5);
    ASSERT_EQ(d.popBack(), 1);
    ASSERT_EQ(d.popBack(), 7);
}
TEST(TestDeque, popBackPushBack){
    Deque<int> d;
    d.pushBack(5);
    d.pushBack(1);
    d.pushBack(7);
    ASSERT_EQ(d.popBack(), 7);
    ASSERT_EQ(d.popBack(), 1);
    ASSERT_EQ(d.popBack(), 5);
}
TEST(TestDeque, PushFrontSize){
    Deque<int> d;
    d.pushFront(4);
    ASSERT_EQ(d.size(), 1);
    d.pushFront(1);
    ASSERT_EQ(d.size(), 2);
    d.pushFront(7);
    ASSERT_EQ(d.size(), 3);
    d.pushFront(9);
    ASSERT_EQ(d.size(), 4);
    d.pushFront(12);
    ASSERT_EQ(d.size(), 5);
}
TEST(TestDeque, PushFrontTop){
    Deque<int> d;
    d.pushFront(4);
    ASSERT_EQ(d.front(), 4);
    d.pushFront(1);
    ASSERT_EQ(d.front(), 1);
    d.pushFront(7);
    ASSERT_EQ(d.front(), 7);
    d.pushFront(9);
    ASSERT_EQ(d.front(), 9);
    d.pushFront(12);
    ASSERT_EQ(d.front(), 12);
}
TEST(TestDeque, PushBackSize){
    Deque<int> d;
    d.pushBack(4);
    ASSERT_EQ(d.size(), 1);
    d.pushBack(1);
    ASSERT_EQ(d.size(), 2);
    d.pushBack(7);
    ASSERT_EQ(d.size(), 3);
    d.pushBack(9);
    ASSERT_EQ(d.size(), 4);
    d.pushBack(12);
    ASSERT_EQ(d.size(), 5);
}
TEST(TestDeque, PushBackTop){
    Deque<int> d;
    d.pushBack(4);
    ASSERT_EQ(d.back(), 4);
    d.pushBack(1);
    ASSERT_EQ(d.back(), 1);
    d.pushBack(7);
    ASSERT_EQ(d.back(), 7);
    d.pushBack(9);
    ASSERT_EQ(d.back(), 9);
    d.pushBack(12);
    ASSERT_EQ(d.back(), 12);
}
TEST(TestDeque, popAndTopAndPush50FrontBack){
    Deque<int> d;
    for(int i = 0; i < 50; i++){
        d.pushFront(i);
        ASSERT_EQ(d.front(), i+1);
        ASSERT_EQ(d.back(), 50-i);
    }
    for(int i = 0; i < 50; i++){
        ASSERT_EQ(d.popBack(), 50-i);
    }
}
TEST(TestDeque, popAndTopAndPush50FrontFront){
    Deque<int> d;
    for(int i = 0; i < 50; i++){
        d.pushFront(i);
        ASSERT_EQ(d.front(), i+1);
        ASSERT_EQ(d.back(), 50-i);
    }
    for(int i = 0; i < 50; i++){
        ASSERT_EQ(d.popFront(), i);
    }
}
TEST(TestDeque, popAndTopAndPush50BackBack){
    Deque<int> d;
    for(int i = 0; i < 50; i++){
        d.pushBack(i);
        ASSERT_EQ(d.front(), i+1);
        ASSERT_EQ(d.back(), 50-i);
    }
    for(int i = 0; i < 50; i++){
        ASSERT_EQ(d.popBack(), 50-i);
    }
}
TEST(TestDeque, popAndTopAndPush50BackFront){
    Deque<int> d;
    for(int i = 0; i < 50; i++){
        d.pushBack(i);
        ASSERT_EQ(d.front(), i+1);
        ASSERT_EQ(d.back(), 50-i);
    }
    for(int i = 0; i < 50; i++){
        ASSERT_EQ(d.popFront(), i);
    }
}
TEST(TestDeque, wrapAroundForward){
    Deque<int> d;
    d.pushFront(12);
    d.pushFront(2);
    d.pushFront(19);
    d.popBack();
    d.pushFront(1);
    d.popBack();
    d.pushFront(4);
    d.popBack();
    d.pushFront(8);
    d.popBack();
    d.pushFront(5);
    d.popBack();
    d.pushFront(3);
    ASSERT_EQ(d.size(), 3);
    ASSERT_EQ(d.front(), 3);
    ASSERT_EQ(d.back(), 8);
}
TEST(TestDeque, wrapAroundBackward){
    Deque<int> d;
    d.pushBack(12);
    d.pushBack(2);
    d.pushBack(19);
    d.popFront();
    d.pushBack(1);
    d.popFront();
    d.pushBack(4);
    d.popFront();
    d.pushBack(8);
    d.popFront();
    d.pushBack(5);
    d.popFront();
    d.pushBack(3);
    ASSERT_EQ(d.size(), 3);
    ASSERT_EQ(d.front(), 8);
    ASSERT_EQ(d.back(), 3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


