#include <iostream>
#include <queue>
#include <functional>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

bool inLessThanEnd(int in, int size){
    return (size-in) > 0;
}


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
    int Lin = 0;
    int Rin = 0;

    while(inLessThanEnd(Rin, right.size()) || inLessThanEnd(Lin, left.size())){

        if((inLessThanEnd(Rin, right.size()) && inLessThanEnd(Lin, left.size())) && left[Lin] > right[Rin]){
            newSort.push_back(right[Rin]);
            Rin++;
        }
        else if((inLessThanEnd(Rin, right.size()) && inLessThanEnd(Lin, left.size())) && (left[Lin] < right[Rin] || left[Lin] == right[Rin])){
            newSort.push_back(left[Lin]);
            Lin++;
        }
        else if(!inLessThanEnd(Rin, right.size()) && inLessThanEnd(Lin, left.size())){
            newSort.push_back(left[Lin]);
            Lin++;
        }
        else if(inLessThanEnd(Rin, right.size()) && !inLessThanEnd(Lin, left.size())){
            newSort.push_back(right[Rin]);
            Rin++;
        }
    }
    values = newSort;
}




TEST(TestSort, noEl){
    vector<int> v = {};
    mergeSort(v);
    ASSERT_EQ(v.size(), 0);
}

TEST(TestSort, oneEl){
    vector<int> v = {3};
    mergeSort(v);
    ASSERT_EQ(v.size(), 1);
    ASSERT_EQ(v[0], 3);
}

TEST(TestSort, twoElSort){
    vector<int> v = {2, 5};
    mergeSort(v);
    ASSERT_EQ(v[0], 2);
    ASSERT_EQ(v[1], 5);
}

TEST(TestSort, twoElNonSort){
    vector<int> v = {5, 2};
    mergeSort(v);
    ASSERT_EQ(v[0], 2);
    ASSERT_EQ(v[1], 5);
}

TEST(TestSort, tenElSort){
    vector<int> v = {1, 3, 4, 5, 6, 13, 17, 22, 89, 90};
    mergeSort(v);
    ASSERT_EQ(v, (vector<int>{1, 3, 4, 5, 6, 13, 17, 22, 89, 90}));
}

TEST(TestSort, tenElNonSort){
    vector<int> v = {4, 90, 3, 22, 1, 13, 17, 6, 89, 5};
    mergeSort(v);
    ASSERT_EQ(v, (vector<int>{1, 3, 4, 5, 6, 13, 17, 22, 89, 90}));
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

