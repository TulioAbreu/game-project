#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <fstream>
#include "singleton.hpp"
#include "json.hpp"
#include "filepath.hpp"

class Config: public Singleton<Config> {
private:
    json mConfig;

public:
    Config() {
        std::ifstream configFile (Path("config.json"));
        configFile >> mConfig;
        configFile.close();
    }

    json operator[](const char* key) {
        return mConfig[key];
    }

    json operator[](const std::string key) {
        return mConfig[key];
    }
};

#endif
