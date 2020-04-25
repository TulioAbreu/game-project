#ifndef SCENE_SERIALIZATION_HPP
#define SCENE_SERIALIZATION_HPP

#include "vector2.hpp"

typedef Vector2i SizeMeta;
typedef Vector2i PositionMeta;

struct EntityMeta {
    int id;
    SizeMeta size;
    PositionMeta position;
};

struct CameraMeta {
    int id;
    PositionMeta position;
};

#endif