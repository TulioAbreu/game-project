#ifndef SPRITE_MANAGER_HPP
#define SPRITE_MANAGER_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <fstream>
#include <map>
#include "filepath.hpp"
#include "json.hpp"
#include "rectangle.hpp"
#include "singleton.hpp"
#include "vector2.hpp"

struct SpriteTemplate {
    size_t textureId;
    Rectangle area;
};

class SpriteManager: public Singleton<SpriteManager> {
private:
    std::map<size_t, sf::Texture> mTexturesMap;
    std::map<size_t, SpriteTemplate> mSpriteTemplates;
    std::map<size_t, sf::Sprite> mSprites;
    int mLastSpriteId;

public:
    SpriteManager() {
        mLastSpriteId = 0;
        loadTextures();
        loadTemplateSprites();
    }

    sf::Texture loadTexture(std::string filepath) {
        sf::Texture texture;
        texture.loadFromFile(filepath);
        return texture;
    }

    void loadTextures() {
        LOG("Loading textures...");
        // TODO: This piece of code is repeating itself on the entire codebase. Maybe create a function for this?
        std::fstream texturesIndexFile (Path("data/textures/textures.json"));
        if (!texturesIndexFile.is_open()) {
            LOG_ERROR("SpriteManager/loadTextures: Could not open textures.json");
            return;
        }

        json texturesIndexJson;
        texturesIndexFile >> texturesIndexJson;

        for (auto textureIndex : texturesIndexJson) {
            const size_t textureId = textureIndex["id"];
            const std::string texturePath = textureIndex["path"];
            mTexturesMap[textureId] = loadTexture(Path("data/textures/") + texturePath);
        }
    }

    void loadTemplateSprites() {
        LOG("Loading template sprites...");

        const std::string spritesJsonFilepath (Path("data/textures/sprites.json"));
        std::fstream spriteTemplatesFile (spritesJsonFilepath);
        if (!spriteTemplatesFile.is_open()) {
            LOG_ERROR("SpriteManager/loadTemplateSprites: Could not open " << spritesJsonFilepath);
            return;
        }

        json spritesIndexJson;
        spriteTemplatesFile >> spritesIndexJson;

        for (auto spriteTemplate : spritesIndexJson) {
            const size_t spriteTemplateId = spriteTemplate["id"];
            const size_t textureId = spriteTemplate["textureId"];
            const Rectangle area = {
                spriteTemplate["area"]["width"],
                spriteTemplate["area"]["height"],
                spriteTemplate["area"]["positionX"],
                spriteTemplate["area"]["positionY"]
            };
            mSpriteTemplates[spriteTemplateId] = {textureId, area};
        }
    }

    virtual ~SpriteManager() {}

    size_t createSprite(size_t spriteTemplateId) {
        SpriteTemplate& spriteTemplate = mSpriteTemplates[spriteTemplateId];

        sf::Sprite sprite;
        sprite.setTexture(mTexturesMap[spriteTemplate.textureId]);
        sprite.setTextureRect(sf::IntRect(spriteTemplate.area.positionX,
                                          spriteTemplate.area.positionY,
                                          spriteTemplate.area.width,
                                          spriteTemplate.area.height));
        size_t spriteId = mLastSpriteId;
        mLastSpriteId++;

        mSprites[spriteId] = sprite;
        return spriteId;
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
