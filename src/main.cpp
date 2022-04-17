#include "tower_sim.hpp"

void test_generic_points() {
    Point<float, 3> p1;
    Point<float, 3> p2;

    Point2D point2D {1, 2};
    auto p3 = p1 + p2;
    p1 += p2;
    p1 *= 3.f; // ou 3.f, ou 3.0 en fonction du type de Point

    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;
}

int main(int argc, char** argv)
{
    test_generic_points();
    TowerSimulation simulation { argc, argv };
    simulation.launch();

    return 0;
}