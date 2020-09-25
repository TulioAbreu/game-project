#include "reader.hpp"

bool Sprites::readTextureSummary(FilePath filePath, std::vector<Sprites::TextureSummaryEntry>& textureSummary) {
    LOG("Loading texture summary...");
    json textureSummaryFile;
    bool success = JSON::load(filePath.value, &textureSummaryFile);
    if (!success) {
        LOG_ERROR("Sprites/readTexturesSummary: Could not read textures.json");
        return false;
    }

    try {
        for (auto texture : textureSummaryFile) {
            const size_t id = texture["id"];
            // TODO: Remove assert
            // TODO: Add custom exception
            assert (id >= 0);
            const std::string path = texture["path"];
            assert (path.size() > 0);
            textureSummary.push_back(Sprites::TextureSummaryEntry(
                id,
                FilePath(std::string("data/textures/") + path)
            ));
        }
    } catch (...) {
        LOG_ERROR("Sprites/readTexturesSummary: Invalid textureId value, check out textures.json file.");
        return false;
    }
    return true;
}

bool Sprites::readSpriteSummary(FilePath filePath, std::vector<Sprites::SpriteSummaryEntry>& spriteSummary) {
    LOG("Loading sprite summary...");
    json spriteSummaryFile;
    bool success = JSON::load(filePath.value, &spriteSummaryFile);
    if (!success) {
        LOG_ERROR("Sprites/readSpriteSummary: Could not read sprites.json file.");
        return false;
    }

    try {
        for (auto sprite : spriteSummaryFile) {
            const size_t id = sprite["id"];
            assert (id >= 0);
            const size_t textureId = sprite["textureId"];
            assert (textureId >= 0);
            const Rectangle area = {
                sprite["area"]["width"],
                sprite["area"]["height"],
                sprite["area"]["positionX"],
                sprite["area"]["positionY"],
            };
            assert (area.height >= 0);
            assert (area.width >= 0);
            spriteSummary.push_back(Sprites::SpriteSummaryEntry(
                id,
                textureId,
                area
            ));
        }
    } catch (...) {
        LOG_ERROR("Sprites/readSpriteSummary: Invalid sprite values, check out sprites.json file.");
        return false;
    }
    return true;
}
