#include <iostream>
#include <queue>
#include <functional>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

template<typename T>
void mergeSort(vector<T>& values){
    if((values.size() <= 1)){
        return;
    }
    if(values.size() == 2){
        if(values[0] > values[1]){
            swap(values[0], values[1]);
        }
        return;
    }

    vector<T> left = {};
    vector<T> right = {};
    for(int i = 0; i < values.size(); i++){
        if(i < values.size()/2){
            left.push_back(values[i]);
        }
        else{
            right.push_back(values[i]);
        }
    }
    mergeSort(left);
    mergeSort(right);
    vector<T> newSort = {};
    int inL = 0;
    int inR = 0;
    while(inR < right.size() && inL < left.size()){
        if(left[inR] > right[inL]){
            newSort.push_back(right[inR]);
            inR++;
        }
        else{
            newSort.push_back(left[inL]);
            inL++;
        }
    }
}

TEST(TestSort, noEl){
    vector<int> v = {};
    mergeSort(v);
    ASSERT_EQ(v.size(), 0);
}

TEST(testSort, oneEl){
    vector<int> v = {3};
    mergeSort(v);
    ASSERT_EQ(v.size(), 1);
    ASSERT_EQ(v[0], 3);
}

TEST(testSort, twoElSort){
    vector<int> v = {2, 5};
    mergeSort(v);
    ASSERT_EQ()
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

