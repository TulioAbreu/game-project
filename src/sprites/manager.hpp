#ifndef SPRITES_MANAGER_HPP
#define SPRITES_MANAGER_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <map>
#include <fstream>
#include <exception>
#include "../utils/rectangle/rectangle.hpp"
#include "../utils/vector2/vector2.hpp"
#include "../json.hpp"
#include "../singleton.hpp"
#include "../sprites/reader/reader.hpp"
#include "../utils/log/log.hpp"
#include "../utils/filepath/filepath.hpp"

namespace Sprites {
struct Template {
    size_t textureId;
    Rectangle area;
};

class Manager: public Singleton<Manager> {
private:
    std::map<size_t, sf::Texture> mTexturesMap;
    std::map<size_t, Template> mSpriteTemplates;
    std::map<size_t, sf::Sprite> mSprites;
    int mLastSpriteId;
public:
    Manager();
    virtual ~Manager() {}
    sf::Texture loadTexture(std::string filepath);
    void loadTextures();
    bool loadTemplateSprites();
    size_t createSprite(size_t spriteTemplateId);
    bool setSpritePosition(size_t spriteId, Vector2f position);
    sf::Sprite getSpriteById(size_t spriteId);
};
};

#endif
