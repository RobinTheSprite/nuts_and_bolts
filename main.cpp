#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using std::cout;
using std::endl;
using std::vector;

using vectIter = vector<int>::iterator;

std::pair<vectIter, vectIter>
partition(vectIter &nutsFirst, vectIter &nutsLast, vectIter &boltsFirst, vectIter &boltsLast)
{
    auto nutsPivot = *(nutsLast - 1);
    auto boltsPivot = *(boltsLast - 1);
    auto swapNuts = nutsFirst;
    auto swapBolts = boltsFirst;
    for (auto j = nutsFirst; j < nutsLast; ++j)
    {
        if (*nutsFirst < boltsPivot)
        {
            std::swap(*swapNuts, *nutsFirst);
            ++swapNuts;
        }

        if (*boltsFirst < nutsPivot)
        {
            std::swap(*swapBolts, *boltsFirst);
            ++swapBolts;
        }

        ++nutsFirst;
        ++boltsFirst;
    }

    std::swap(*swapNuts, *(nutsLast - 1));
    std::swap(*swapBolts, *(boltsLast - 1));

    return {swapNuts, swapBolts};
}

void sort(vectIter nutsFirst, vectIter nutsLast, vectIter boltsFirst, vectIter boltsLast)
{
    if (nutsFirst < nutsLast)
    {
       auto [pNuts, pBolts] = partition(nutsFirst, nutsLast, boltsFirst, boltsLast);
        sort(nutsFirst, pNuts, boltsFirst, pBolts);
        sort(pNuts, nutsLast, pBolts, boltsLast);
    }
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    auto vectorSize = 10u;

    vector<int> nuts(vectorSize);
    vector<int> bolts(vectorSize);

    std::iota(nuts.begin(), nuts.end(), 0);
    std::iota(bolts.begin(), bolts.end(), 0);

    std::shuffle(nuts.begin(), nuts.end(), gen);
    std::shuffle(bolts.begin(), bolts.end(), gen);

    auto start = std::chrono::high_resolution_clock::now();

    while (!nuts.empty())
    {
        sort(nuts.begin(), nuts.end(), bolts.begin(), bolts.end());
        for (auto i = 0u; i < nuts.size(); ++i)
        {
            if (nuts[i] == bolts[i])
            {
                nuts.erase(nuts.begin() + i);
                bolts.erase(bolts.begin() + i);
            }
        }
    }

//    while(!nuts.empty())
//    {
//        for(auto i = 0u; i < nuts.size(); ++i)
//        {
//            if (nuts[i] == bolts[i])
//            {
//                nuts.erase(nuts.begin() + i);
//                bolts.erase(bolts.begin() + i);
//            }
//        }
//        if (!nuts.empty())
//        {
//            std::rotate(bolts.begin(), bolts.begin() + 1, bolts.end());
//        }
//    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start;
    std::cout << diff.count() << std::endl;

    return 0;
}