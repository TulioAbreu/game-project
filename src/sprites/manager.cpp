#include "manager.hpp"

Sprites::Manager::Manager() {
    mLastSpriteId = 0;
    loadTextures();
    loadTemplateSprites();
}

sf::Texture Sprites::Manager::loadTexture(std::string filepath) {
    sf::Texture texture;
    texture.loadFromFile(filepath);
    return texture;
}

void Sprites::Manager::loadTextures() {
    const std::string TEXTURE_SUMMARY_PATH = "data/textures/textures.json";

    std::vector<Sprites::TextureSummaryEntry> textureSummary;
    const bool result = Sprites::readTextureSummary(
        Path(TEXTURE_SUMMARY_PATH),
        textureSummary
    );
    if (!result) return;

    for (auto texture : textureSummary) {
        mTexturesMap[texture.textureId] = loadTexture(texture.filePath.value);
    }
}

bool Sprites::Manager::loadTemplateSprites() {
    LOG("Loading template sprites...");
    const std::string SPRITE_SUMMARY_PATH = "data/textures/sprites.json";

    std::vector<Sprites::SpriteSummaryEntry> spriteSummary;
    const bool success = Sprites::readSpriteSummary(Path(SPRITE_SUMMARY_PATH), spriteSummary);
    if (!success) return false;

    for (auto sprite : spriteSummary) {
        const size_t id = sprite.spriteId;
        mSpriteTemplates[id] = {
            sprite.textureId,
            sprite.spriteSheetArea
        };
    }

    return true;
}

size_t Sprites::Manager::createSprite(size_t spriteTemplateId) {
    Sprites::Template* spriteTemplatePtr = nullptr;
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

bool Sprites::Manager::setSpritePosition(size_t spriteId, Vector2f position) {
    try {
        mSprites.at(spriteId).setPosition(position.x, position.y);
    } catch (...) {
        LOG_WARNING("SpriteManager/setSpritePosition: Could not set sprite's position. [spriteId = " << spriteId << "]");
        return false;
    }
    return true;
}

sf::Sprite Sprites::Manager::getSpriteById(size_t spriteId) {
    try {
        const sf::Sprite spriteAtId = mSprites.at(spriteId);
        return spriteAtId;
    } catch (...) {
        LOG_WARNING("SpriteManager/getSpriteById: Could not get sprite with specified id. [spriteId = " << spriteId << "]");
    }
    return mSprites[spriteId];
}
