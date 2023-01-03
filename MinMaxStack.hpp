//
// Created by diogotvf7 on 03-01-2023.
//

#ifndef AED2223_G29_MINMAXSTACK_HPP
#define AED2223_G29_MINMAXSTACK_HPP

#include <stack>
#include <utility>
#include <functional>

template<class T,
        typename Compare = std::less<T>>
class MinMaxStack {
    std::stack<std::pair<T, std::pair<T, T>>> s;
    Compare comp;

public:
    void push(T t) {
        T min = s.empty() ? t : std::min(t, s.top().second.first, comp);
        T max = s.empty() ? t : std::max(t, s.top().second.second, comp);
        s.push({t, {min, max}});
    }

    void  pop() {
        T poppedItem = s.top().first;
        s.pop();
        return poppedItem;
    }

    T getMin() {
        return s.top().second.first;
    }

    T getMax() {
        return s.top().second.second;
    }
};


#endif //AED2223_G29_MINMAXSTACK_HPP
