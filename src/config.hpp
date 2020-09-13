#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <fstream>
#include "singleton.hpp"
#include "json.hpp"
#include "utils/filepath/filepath.hpp"
#include "utils/vector2/vector2.hpp"

const std::string CONFIG_PATH = "config.json";
const std::string DEFAULT_WINDOW_TITLE = "Game Project";
const Vector2f DEFAULT_WINDOW_SIZE = {1200, 768};

class Config: public Singleton<Config> {
private:
    std::string mWindowTitle;
    Vector2f mWindowSize;

    std::string readWindowTitle(json& config) {
        std::string windowTitle;

        try {
            windowTitle = config["window"]["title"];
        } catch (...) {
            windowTitle = DEFAULT_WINDOW_TITLE;
        }

        return windowTitle;
    }

    Vector2f readWindowSize(json& config) {
        Vector2f windowSize;

        try {
            windowSize = {
                config["window"]["width"],
                config["window"]["height"]
            };
        } catch (...) {
            windowSize = DEFAULT_WINDOW_SIZE;
        }

        return windowSize;
    }

    json readConfigFile(FilePath filepath) {
        std::ifstream configFile (filepath.value);
        json config;
        configFile >> config;
        configFile.close();
        return config;
    }

public:
    Config() {
        json config = readConfigFile(Path(CONFIG_PATH));

        mWindowTitle = readWindowTitle(config);
        mWindowSize = readWindowSize(config);
    }

    const std::string getWindowTitle() const {
        return mWindowTitle;
    }

    const Vector2f getWindowSize() const {
        return mWindowSize;
    }
};

#endif
