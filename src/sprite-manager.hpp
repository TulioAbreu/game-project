#ifndef SPRITE_MANAGER_HPP
#define SPRITE_MANAGER_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <vector>
#include "singleton.hpp"
#include "rectangle.hpp"
#include "vector2.hpp"

class SpriteManager: public Singleton<SpriteManager> {
private:
    std::vector<sf::Texture> mTextures;
    std::vector<sf::Sprite> mSprites;
    int mLastTextureId;
    int mLastSpriteId;

public:
    SpriteManager() {
        mLastTextureId = 0;
        mLastSpriteId = 0;
    }

    virtual ~SpriteManager() {
    }

    size_t createTextureFromFile(std::string filepath) {
        sf::Texture texture;
        texture.loadFromFile(filepath);

        mTextures.push_back(texture);
        return mLastTextureId++;
    }

    size_t createSpriteFromTexture(size_t textureId, Rectangle spriteRectangle) {
        sf::Sprite sprite;
        sprite.setTexture(mTextures[textureId]);
        sprite.setTextureRect(sf::IntRect(spriteRectangle.positionX,
                                          spriteRectangle.positionY,
                                          spriteRectangle.width,
                                          spriteRectangle.height));
        mSprites.push_back(sprite);
        return mLastSpriteId;
    }

    bool setSpritePosition(size_t spriteId, Vector2f position) {
        if (spriteId >= 0 && spriteId < mSprites.size()) {
            return false;
        }

        mSprites[spriteId].setPosition(position.x, position.y);
        return true;
    }

    sf::Sprite getSpriteById(size_t spriteId) {
        return mSprites[spriteId];
    }
};

#endif
