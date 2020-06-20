#include "particle.hpp"

Particles::Particles() {
    epicenterPosition = {0, 0};
    pattern = ParticlePattern::NONE;
}

void Particles::update() {
    switch (pattern) {
        case ParticlePattern::NONE: {
            // Do nothing
        } break;
        case ParticlePattern::TEST: {
            testPatternUpdate();
        } break;
    }
}

void Particles::testPatternUpdate() {
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
