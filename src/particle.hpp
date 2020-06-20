#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <vector>
#include "color.hpp"
#include "vector2.hpp"
#include <cmath>

// TODO: Future optimization: imagine player moving around and we getting camera offset with 500 particles (thats bad) - maybe some batch operations?

struct Particle {
    Color color;
    Vector2f position;
    int size;
    
    Particle(Color color, Vector2f position, int size) {
        this->color = color;
        this->position = position;
        this->size = size;
    }
};

enum class ParticlePattern {
    NONE = 0,
    TEST
};

class Particles {
public:
    std::vector<Particle> particles;
    Vector2f epicenterPosition;
    ParticlePattern pattern;

    Particles();

    void update();

private:
    void testPatternUpdate();
};

#endif
