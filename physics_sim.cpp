#include "physics_sim.h"
#include <cmath>

// Модель падения с сопротивлением воздуха по методу Эйлера:  dv/dt = mg - kv -> dv = (g - (k/m)v)dt
std::vector<SimResult> simulateFallingBody(double mass, double k, double t_lim, double dt) {
    std::vector<SimResult> results;
    double v = 0, y = 0, g = 9.81;
    for (double t = 0; t <= t_lim; t += dt) {
        results.push_back({t, y, v});
        double acceleration = g - (k / mass) * v;
        v += acceleration * dt;
        y += v * dt;
    }
    return results;
}

// Модель пружины: гармонические колебания a = -(k/m)x
std::vector<SimResult> simulateSpring(double mass, double k, double x0, double t_lim, double dt) {
    std::vector<SimResult> results;
    double x = x0, v = 0;
    
    const double omega_sq = k / mass;  // ω² = k/m
    
    for (double t = 0; t <= t_lim; t += dt) {
        results.push_back({t, x, v});
        double acceleration = -omega_sq * x;
        v += acceleration * dt;
        x += v * dt;
    }
    
    return results;
}
//Движение с постоянным ускорением 
std::vector<SimResult> simulateConstantAccel(double x0, double v0, double a, double t_lim, double dt) {
    std::vector<SimResult> results;
    for (double t = 0; t <= t_lim; t += dt) {
        double x = x0 + v0 * t + 0.5 * a * t * t;
        double v = v0 + a * t;
        results.push_back({t, x, v});
    }
    return results;
}

//Заряд в электрическом поле
std::vector<SimResult> simulateChargeInField(double q, double m, double E, double t_lim, double dt) {
    double acceleration = (q * E) / m; // Второй закон Ньютона для заряда
    return simulateConstantAccel(0, 0, acceleration, t_lim, dt);

}
