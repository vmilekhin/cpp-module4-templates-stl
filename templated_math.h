#pragma once
#include <concepts>
#include <type_traits>

// Концепт из лекции (слайд 15)
template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

// Шаблонная функция (слайд 7, 15)
template<Numeric T>
T square(T value) {
    return value * value;
}

// Концепт на основе требований (слайд 16)
template<typename T>
concept Squarable = requires(T x) {
    { x * x } -> std::convertible_to<T>;
};

template<Squarable T>
T checked_square(T x) {
    return x * x;
}
