#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using std::cout;
using std::endl;
using std::vector;

using vectIter = vector<int>::iterator;
void sort(vector<int> & nuts, vector<int> & bolts)
{
    cout << nuts.size() << endl;

    auto half = nuts.size() / 2;


    auto swapIndexNuts = 0;
    auto swapIndexBolts = 0;
    for (auto i = 0u; i < bolts.size(); ++i)
    {
        if (bolts[i] > nuts[i])
        {
            while (nuts[swapIndexNuts] == bolts[swapIndexBolts])
            {
                ++swapIndexBolts;
            }
            std::swap(bolts[swapIndexBolts], bolts[i]);
            ++swapIndexBolts;
        }
        else if (bolts[i] < nuts[i])
        {
            while (nuts[swapIndexNuts] == bolts[swapIndexBolts])
            {
                ++swapIndexNuts;
            }
            std::swap(nuts[i], nuts[swapIndexNuts]);
            ++swapIndexNuts;
        }
    }
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    auto vectorSize = 10000u;

    vector<int> nuts(vectorSize);
    vector<int> bolts(vectorSize);

    std::iota(nuts.begin(), nuts.end(), 0);
    std::iota(bolts.begin(), bolts.end(), 0);

    std::shuffle(nuts.begin(), nuts.end(), gen);
    std::shuffle(bolts.begin(), bolts.end(), gen);

    auto start = std::chrono::high_resolution_clock::now();

    sort(nuts, bolts);

//    while(!bolts.empty())
//    {
//        for (auto i = 0u; i < nuts.size(); ++i)
//        {
//            cout << nuts.size() << endl;
//            for (auto j = 0u; j < bolts.size(); ++j)
//            {
//                if (bolts[j] == nuts[i])
//                {
//                    bolts.erase(bolts.begin()+j);
//                    nuts.erase(nuts.begin()+i);
//                }
//            }
//        }
//    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start;
    std::cout << diff.count() << std::endl;

    return 0;
}