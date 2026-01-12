#include <vector>

// Структура для хранения результатов (время, координата, скорость)
struct SimResult {
    double time;
    double position;
    double velocity;
};

std::vector<SimResult> simulateFallingBody(double mass, double k, double t_lim, double dt);
std::vector<SimResult> simulateSpring(double mass, double k, double x0, double t_lim, double dt);
std::vector<SimResult> simulateConstantAccel(double x0, double v0, double a, double t_lim, double dt);
std::vector<SimResult> simulateChargeInField(double q, double m, double E, double t_lim, double dt);
