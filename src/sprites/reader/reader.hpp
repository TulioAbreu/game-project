#ifndef SPRITES_READER_HPP
#define SPRITES_READER_HPP

#include <vector>
#include <cassert>
#include "../../json.hpp"
#include "../../utils/log/log.hpp"
#include "../../utils/filepath/filepath.hpp"
#include "../../utils/rectangle/rectangle.hpp"

namespace Sprites {
    struct TextureSummaryEntry {
        int textureId;
        FilePath filePath;

        TextureSummaryEntry(const size_t textureId, const FilePath filePath) {
            this->textureId = textureId;
            this->filePath = filePath;
        }
    };

    struct SpriteSummaryEntry {
        int spriteId;
        int textureId;
        Rectangle spriteSheetArea;

        SpriteSummaryEntry(const size_t spriteId, const size_t textureId, const Rectangle area) {
            this->spriteId = spriteId;
            this->textureId = textureId;
            this->spriteSheetArea = area;
        }
    };

    bool readTextureSummary(FilePath filePath, std::vector<TextureSummaryEntry>& textureSummary);
    bool readSpriteSummary(FilePath filePath, std::vector<SpriteSummaryEntry>& spriteSummary);
};

#endif
