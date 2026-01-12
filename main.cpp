#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <vector>
#include "physics_sim.h"

// Функция ввода с обработкой ошибок
double getValidDouble(const std::string& prompt, double minVal, bool strictlyGreater = false) {
    double val;
    while (true) {
        std::cout << prompt;
        if (!(std::cin >> val)) {
            std::cout << "Ошибка: введите числовое значение!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else if (strictlyGreater && val <= minVal) {
            std::cout << "Ошибка: значение должно быть строго больше " << minVal << "!\n";
        } else if (!strictlyGreater && val < minVal) {
            std::cout << "Ошибка: значение не может быть меньше " << minVal << "!\n";
        } else {
            return val;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;

    while (true) {
        std::cout << "\n--- МЕНЮ СИМУЛЯТОРА (Все величины в СИ) ---\n"
                  << "1. Падение с сопротивлением воздуха\n"
                  << "2. Пружинный маятник\n"
                  << "3. Движение с постоянным ускорением\n"
                  << "4. Заряд в электрическом поле\n"
                  << "0. Выход\n"
                  << "Выберите пункт: ";

        if (!(std::cin >> choice) || choice < 0 || choice > 4) {
            std::cout << "Ошибка: выберите пункт от 0 до 4.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choice == 0) break;

        double t_lim = getValidDouble("Введите время симуляции (секунды): ", 0.0, true);
        double dt;
        while (true) {
            dt = getValidDouble("Введите шаг dt (секунды): ", 0.0, true);
            if (dt >= t_lim) {
                std::cout << "Ошибка: шаг должен быть меньше времени симуляции (" << t_lim << " с)!\n";
            } else break;
        }

        std::vector<SimResult> data;
        if (choice == 1) {
            double m = getValidDouble("Масса (кг): ", 0.0, true);
            double k = getValidDouble("Коэффицент сопротивления (кг/с): ", 0.0, false);
            data = simulateFallingBody(m, k, t_lim, dt);
        } else if (choice == 2) {
            double m = getValidDouble("Масса груза (кг): ", 0.0, true);
            double k = getValidDouble("Жесткость (Н/м): ", 0.0, true);
            double x0 = getValidDouble("Начальное смещение (метры): ", -1e9);
            data = simulateSpring(m, k, x0, t_lim, dt);
        } else if (choice == 3) {
            double x0 = getValidDouble("Начальная позиция (метры): ", -1e9);
            double v0 = getValidDouble("Начальная скорость (м/с): ", -1e9);
            double a = getValidDouble("Ускорение (м/с^2): ", -1e9);
            data = simulateConstantAccel(x0, v0, a, t_lim, dt);
        } else if (choice == 4) {
            double q = getValidDouble("Заряд (Кл): ", -1e9);
            double m = getValidDouble("Масса (кг): ", 0.0, true);
            double E = getValidDouble("Поле E (В/м): ", -1e9);
            data = simulateChargeInField(q, m, E, t_lim, dt);
        }

        // Форматированный вывод результатов
        std::cout << "\n" << std::fixed << std::setprecision(4);
        std::cout << "    Время (с)     Позиция (м)    Скорость (м/с)\n";
        std::cout << std::string(48, '-') << std::endl;
        for (size_t i = 0; i < data.size(); i++) {
            std::cout << std::right 
                    << std::setw(12) << data[i].time << "    "
                    << std::setw(12) << data[i].position << "    "
                    << std::setw(12) << data[i].velocity << std::endl;
        }
    }
    return 0;
}