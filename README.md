# Module 4: Templates, STL and Ranges (C++20)

Практическая работа по обобщенному программированию на C++.

## Что сделано
1. **Шаблоны и Concepts:** Создана шаблонная функция `square<T>` с ограничением `Numeric` (integral или floating_point), а также концепт `Squarable` на основе `requires`.
2. **Compile-time проверки:** Использован `static_assert` для проверки размеров типов и тривиального копирования.
3. **Обработка данных (STL):** Классический подход с `remove_if`, `sort` и `accumulate` для фильтрации `Prediction` по порогу уверенности.
4. **Обработка данных (Ranges):** Современный подход с `std::views::filter`, `std::ranges::sort` и `std::views::transform`.

## Сборка и запуск
```bash
g++ -std=c++20 -Wall -Wextra -pedantic -O2 main.cpp -o demo
./demo
