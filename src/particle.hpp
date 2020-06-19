#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <vector>
#include "color.hpp"
#include "vector2.hpp"
#include <cmath>

// TODO: Future optimization: imagine player moving around and we getting camera offset with 500 particles (thats bad)

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

class Particles {
public:
    std::vector<Particle> particles;
    Vector2f epicenterPosition;

    Particles() {
        epicenterPosition = {0, 0};
    }

    void update() {
        if (particles.size() < 70) {
            if (rand() % 100 < 30) {
                particles.push_back(Particle(
                    Color(255, 255, 0),
                    Vector2f(epicenterPosition.x - (rand()%5), 0 - epicenterPosition.y - (rand()%5)),
                    5
                ));
            }
        }

        for (auto& particle : particles) {
            Vector2f movement = {rand()%5, rand()%5};
            particle.position = particle.position + movement;
        }

        if (particles.size() > 0) {
            if (rand() % 100 < 5) {
                particles.erase(particles.begin());
            }
        }
    }
};

#endif
