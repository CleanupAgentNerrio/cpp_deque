#pragma once

#include <deque>
#include <cstdlib>

template<class T, class Comp>
inline std::deque<T> Merge(const std::deque<T>& half1, const std::deque<T>& half2, const Comp& comparator) {
    size_t iter_1 = 0;
    size_t iter_2 = 0;
    std::deque<T> merge_deque;
    while (true) {
        if (iter_1 == half1.size()) {
            for (size_t i = iter_2; i < half2.size(); ++i) {
                merge_deque.push_back(half2[i]);
            }
            break;
        }
        if (iter_2 == half2.size()) {
            for (size_t i = iter_1; i < half1.size(); ++i) {
                merge_deque.push_back(half1[i]);
            }
            break;
        }
        if (comparator(half1[iter_1], half2[iter_2])) {
            merge_deque.push_back(half1[iter_1]);
            iter_1++;
        } else {
            merge_deque.push_back(half2[iter_2]);
            iter_2++;
        }
    }
    return merge_deque;
}

template<class T, class Comp>
inline std::deque<T> MergeSort(const std::deque<T>& src, const Comp& comparator) {
    if (src.size() <= 1) {
        return src;
    }
    const size_t mid = src.size() / 2;
    const std::deque<T> left_sorted = MergeSort(std::deque<T>{src.begin(), src.begin() + mid}, comparator);
    const std::deque<T> right_sorted = MergeSort(std::deque<T>{src.begin() + mid, src.end()}, comparator);
    return Merge(left_sorted, right_sorted, comparator);
}
