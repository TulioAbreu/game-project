#ifndef SPRITE_MANAGER_HPP
#define SPRITE_MANAGER_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <map>
#include "utils/rectangle/rectangle.hpp"
#include "utils/vector2/vector2.hpp"
#include "json.hpp"
#include "singleton.hpp"

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
    SpriteTemplate createSpriteTemplate(json jsonObject);
public:
    SpriteManager();
    sf::Texture loadTexture(std::string filepath);
    void loadTextures();
    bool loadTemplateSprites();
    virtual ~SpriteManager() {}
    size_t createSprite(size_t spriteTemplateId);
    bool setSpritePosition(size_t spriteId, Vector2f position);
    sf::Sprite getSpriteById(size_t spriteId);
};

#endif
