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

    if (mSpriteTemplates.contains(spriteTemplateId)) {
        spriteTemplatePtr = &(mSpriteTemplates[spriteTemplateId]);
    } else {
        LOG_WARNING("SpriteManager/createSprite: Could not find sprite template [spriteId = " << spriteTemplateId << "]");
        return -1;
    }

    sf::Sprite sprite;
    const auto spriteTextureId = spriteTemplatePtr->textureId;
    if (mTexturesMap.contains(spriteTextureId)) {
        sprite.setTexture(mTexturesMap[spriteTextureId]);
    } else {
        LOG_WARNING("SpriteManager/createSprite: Could not find texture [textureId = " << spriteTextureId << "]");
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
    if (mSprites.contains(spriteId)) {
        mSprites[spriteId].setPosition(position.x, position.y);
    } else {
        LOG_WARNING("SpriteManager/setSpritePosition: Could not find sprite. [spriteId = " << spriteId << "]");
        return false;
    }
    return true;
}

sf::Sprite Sprites::Manager::getSpriteById(size_t spriteId) {
    if (mSprites.contains(spriteId)) {
        return mSprites[spriteId];
    } else {
        LOG_WARNING("SpriteManager/getSpriteById: Could not get sprite. [spriteId = " << spriteId << "]");
    }
    return mSprites[spriteId];
}
