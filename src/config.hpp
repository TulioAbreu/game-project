#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <fstream>
#include "singleton.hpp"
#include "filepath.hpp"
#include "../third-party/json.hpp"

using Json = nlohmann::json;

class Config: public Singleton<Config> {
private:
    nlohmann::json mConfig;

public:
    Config() {
        std::ifstream configFile (Path("config.json"));
        configFile >> mConfig;
        configFile.close();
    }

    Json operator[](const char* key) {
        return mConfig[key];
    }

    Json operator[](const std::string key) {
        return mConfig[key];
    }
};

#endif
