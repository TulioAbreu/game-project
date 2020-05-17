#include "sprite-manager.hpp"

#include "log.hpp"
#include <fstream>
#include "filepath.hpp"
#include "json.hpp"

SpriteManager::SpriteManager() {
    mLastSpriteId = 0;
    loadTextures();
    loadTemplateSprites();
}

sf::Texture SpriteManager::loadTexture(std::string filepath) {
    sf::Texture texture;
    texture.loadFromFile(filepath);
    return texture;
}

void SpriteManager::loadTextures() {
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

void SpriteManager::loadTemplateSprites() {
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

size_t SpriteManager::createSprite(size_t spriteTemplateId) {
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

bool SpriteManager::setSpritePosition(size_t spriteId, Vector2f position) {
    if (spriteId >= 0 && spriteId < mSprites.size()) {
        return false;
    }

    mSprites[spriteId].setPosition(position.x, position.y);
    return true;
}

sf::Sprite SpriteManager::getSpriteById(size_t spriteId) {
    return mSprites[spriteId];
}
