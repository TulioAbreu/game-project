#include "sprite-manager.hpp"

#include <fstream>
#include <exception>

#include "log.hpp"
#include "filepath.hpp"

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

SpriteTemplate SpriteManager::createSpriteTemplate(json jsonObject) {
    const size_t textureId = jsonObject["textureId"];
    const Rectangle area = {
        jsonObject["area"]["width"],
        jsonObject["area"]["height"],
        jsonObject["area"]["positionX"],
        jsonObject["area"]["positionY"]
    };

    return {textureId, area};
}

bool SpriteManager::loadTemplateSprites() {
    LOG("Loading template sprites...");

    const std::string spritesJsonFilepath (Path("data/textures/sprites.json"));
    std::fstream spriteTemplatesFile (spritesJsonFilepath);
    if (!spriteTemplatesFile.is_open()) {
        LOG_ERROR("SpriteManager/loadTemplateSprites: Could not open " << spritesJsonFilepath);
        return false;
    }

    json spritesIndexJson;
    spriteTemplatesFile >> spritesIndexJson;

    try {
        for (auto spriteTemplateJson : spritesIndexJson) {
            const size_t spriteTemplateId = spriteTemplateJson["id"];
            mSpriteTemplates[spriteTemplateId] = createSpriteTemplate(spriteTemplateJson);
        }
    } catch (...) {
        // TODO: This error is too serious. Consider giving a "Could not load scene" error
        LOG_ERROR("SpriteManager/loadTemplateSprites: Could not load texture due to invalid json data. Check textures/sprites.json.");
        return false;
    }
    return true;
}

size_t SpriteManager::createSprite(size_t spriteTemplateId) {
    SpriteTemplate* spriteTemplatePtr = nullptr;
    try {
        spriteTemplatePtr = &mSpriteTemplates.at(spriteTemplateId);
    }
    catch (...) {
        LOG_WARNING("SpriteManager/createSprite: Could not find Sprite Template with specified id. [spriteId = " << spriteTemplateId << "]");
        return -1;
    }

    sf::Sprite sprite;
    try {
        sprite.setTexture(mTexturesMap.at(spriteTemplatePtr->textureId));
    } catch (...) {
        LOG_WARNING("SpriteManager/createSprite: Could not find texture with specified id. [spriteId = " << spriteTemplatePtr->textureId << "]");
        return -1;
    }
    sprite.setTextureRect(sf::IntRect(spriteTemplatePtr->area.positionX,
                                      spriteTemplatePtr->area.positionY,
                                      spriteTemplatePtr->area.width,
                                      spriteTemplatePtr->area.height));

    size_t spriteId = mLastSpriteId++;
    mSprites[spriteId] = sprite;
    return spriteId;
}

bool SpriteManager::setSpritePosition(size_t spriteId, Vector2f position) {
    try {
        mSprites.at(spriteId).setPosition(position.x, position.y);
    } catch (...) {
        LOG_WARNING("SpriteManager/setSpritePosition: Could not set sprite's position. [spriteId = " << spriteId << "]");
        return false;
    }
    return true;
}

sf::Sprite SpriteManager::getSpriteById(size_t spriteId) {
    try {
        const sf::Sprite spriteAtId = mSprites.at(spriteId);
        return spriteAtId;
    } catch (...) {
        LOG_WARNING("SpriteManager/getSpriteById: Could not get sprite with specified id. [spriteId = " << spriteId << "]");
    }
    return mSprites[spriteId];
}