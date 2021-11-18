#ifndef VE281P1_SORT_HPP
#define VE281P1_SORT_HPP

#include <vector>
#include <cstdlib>
#include <functional>

using namespace std;

template<class T>
void mySwap(T &a, T &b) {
    T temp;
    temp = a;
    a = b;
    b = temp;
}


template<typename T, typename Compare>
void bubble_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    int size = static_cast<int> (vector.size());
    bool flag = true;
    if (size < 2) return;
    else {
        for (int i = 0; i < size - 1 && flag; i++) {
            flag = false;
            for (int j = 0; j < size - i - 1; j++) {
                if (comp(vector[j + 1], vector[j])) {
                    mySwap(vector[j], vector[j + 1]);
                    flag = true;
                }
            }
        }
    }
}

template<typename T, typename Compare>
void insertion_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    size_t size = vector.size();
    for (int i = 0; i < (int) size; i++) {
        T temp = vector[i];
        int index = i - 1;
        while (index >= 0 && comp(temp, vector[index])) {
            vector[index + 1] = vector[index];
            index--;
        }
        vector[index + 1] = temp;
    }
}

template<typename T, typename Compare>
void selection_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    int left = 0;
    int right = (int) vector.size() - 1;
    while (left < right) {
        int min = left;
        int max = right;
        for (int i = left; i < right + 1; i++) {
            if (comp(vector[i], vector[min])) {
                min = i;
            }
            if (!comp(vector[i], vector[max])) {
                max = i;
            }
        }
        mySwap(vector[max], vector[right]);
        if (min == right) min = max;
        mySwap(vector[min], vector[left]);
        left++;
        right--;
    }
}

template<typename T, typename Compare>
void merge(std::vector<T> &vector, T newVec[], int front, int mid, int end, Compare comp = std::less<T>()) {
    int i = front;
    int j = mid + 1;
    for (int k = front; k <= end; k++) {
        newVec[k] = vector[k];
    }
    for (int k = front; k <= end; k++) {
        if (i > mid) {
            vector[k] = newVec[j++];
        } else if (j > end) {
            vector[k] = newVec[i++];
        } else if (comp(newVec[j], newVec[i])) {
            vector[k] = newVec[j++];
        } else vector[k] = newVec[i++];
    }
}

template<typename T, typename Compare>
void merge_sort(std::vector<T> &vector, T newVec[], int front, int end, Compare comp = std::less<T>()) {
    if (front >= end)
        return;
    int mid = (front + end) / 2;
    merge_sort(vector, newVec, front, mid, comp);
    merge_sort(vector, newVec, mid + 1, end, comp);
    merge(vector, newVec, front, mid, end, comp);
}

template<typename T, typename Compare>
void merge_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    T *newVec = new T[(int) vector.size()];
    merge_sort(vector, newVec, 0, (int) vector.size() - 1, comp);
    delete[] newVec;
}


template<typename T, typename Compare>
int partitionE(std::vector<T> &vector, int left, int right, Compare comp = std::less<T>()) {
    std::vector<T> newVector(right - left + 1);
    int l = left;
    int r = right;
    int index = (left + right) / 2;
    mySwap(vector[left], vector[index]);
    int position = left + 1;
    while (position <= right) {
        if (comp(vector[position], vector[left])) {
            newVector[l - left] = vector[position];
            l++;
        } else {
            newVector[r - left] = vector[position];
            r--;
        }
        position++;
    }
    newVector[l - left] = vector[left];
    for (int i = left; i <= right; i++) {
        vector[i] = newVector[i - left];
    }
    return l;
}

template<typename T, typename Compare>
void quick_sort_extra_helper(std::vector<T> &vector, int left, int right, Compare comp = std::less<T>()) {
    if (left >= right) return;
    int pivot = partitionE(vector, left, right, comp);
    quick_sort_extra_helper(vector, left, pivot - 1, comp);
    quick_sort_extra_helper(vector, pivot + 1, right, comp);
}


template<typename T, typename Compare>
void quick_sort_extra(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    quick_sort_extra_helper(vector, 0, (int) vector.size() - 1, comp);

}

template<typename T, typename Compare>
void quick_sort_inplace_helper(std::vector<T> &vector, int left, int right, Compare comp = std::less<T>()) {
    if (left >= right) return;
    T p = vector[left];
    int i = left, j = right;
    while (i != j) {
        while (j > i && !comp(vector[j], p)) {
            j--;
        }
        mySwap(vector[i], vector[j]);
        while (i < j && comp(vector[i], p)) {
            i++;
        }
        mySwap(vector[i], vector[j]);
    }
    quick_sort_inplace_helper(vector, left, i - 1, comp);
    quick_sort_inplace_helper(vector, i + 1, right, comp);
}


template<typename T, typename Compare>
void quick_sort_inplace(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    quick_sort_inplace_helper(vector, 0, (int) vector.size() - 1, comp);
}

#endif //VE281P1_SORT_HPP