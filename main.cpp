#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ranges>
#include <cmath>
#include "templated_math.h"

struct Prediction {
    int class_id;
    double confidence;
};

int main() {
    // 1. Демонстрация шаблонов и concepts
    std::cout << "--- Templates & Concepts ---\n";
    std::cout << "square(3)   = " << square(3) << '\n';
    std::cout << "square(2.5) = " << square(2.5) << '\n';
    
    // 2. Данные для обработки
    std::vector<Prediction> items{{1, 0.6}, {2, 0.95}, {3, 0.8}, {4, 0.5}};
    double threshold = 0.8;

    // --- Подход A: Классический STL (remove_if + sort + accumulate) ---
    std::cout << "\n--- Approach A: STL (Classic) ---\n";
    auto items_stl = items; // копия для теста
    
    // Удаляем всё, что ниже порога
    items_stl.erase(
        std::remove_if(items_stl.begin(), items_stl.end(),
            [threshold](const Prediction& p) { return p.confidence < threshold; }),
        items_stl.end()
    );
    
    // Сортируем по убыванию
    std::sort(items_stl.begin(), items_stl.end(),
        [](const Prediction& a, const Prediction& b) { return a.confidence > b.confidence; });
    
    // Суммируем
    double sum_stl = std::accumulate(items_stl.begin(), items_stl.end(), 0.0,
        [](double acc, const Prediction& p) { return acc + p.confidence; });
    
    for (const auto& p : items_stl) std::cout << p.class_id << ":" << p.confidence << " ";
    std::cout << "\nAvg (STL): " << (sum_stl / items_stl.size()) << '\n';

    // --- Подход B: Ranges (views::filter | transform) ---
    std::cout << "\n--- Approach B: Ranges (Modern) ---\n";
    auto accepted = items | std::views::filter([threshold](const auto& p) {
        return p.confidence >= threshold;
    });

    // Внимание: ranges::sort изменяет контейнер, поэтому нужна копия
    std::vector<Prediction> items_ranges(accepted.begin(), accepted.end());
    
    std::ranges::sort(items_ranges, std::greater{}, &Prediction::confidence);

    for (const auto& p : items_ranges) std::cout << p.class_id << ":" << p.confidence << " ";
    
    // Считаем сумму через ranges
    auto confidences = items_ranges | std::views::transform(&Prediction::confidence);
    double sum_ranges = std::accumulate(confidences.begin(), confidences.end(), 0.0);
    
    std::cout << "\nAvg (Ranges): " << (sum_ranges / items_ranges.size()) << '\n';

    // 3. Проверка compile-time (Slide 17)
    static_assert(sizeof(double) >= 8);
    static_assert(std::is_trivially_copyable_v<Prediction>);

    return 0;
}
