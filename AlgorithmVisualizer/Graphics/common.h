#pragma once
#include <unordered_map>
#include <cstdlib>
#include <algorithm>

struct EnumClassHash{
    /**
     * @brief 
     * 
     * This allows us to use enums as part of hash table std::unordered_map<enum, T, operator>
     * 
     * @tparam T 
     * @param t 
     * @return std::size_t 
     */
    template<typename T>
    std::size_t operator()(T t) const {
        return static_cast<std::size_t>(t);
    }
};
