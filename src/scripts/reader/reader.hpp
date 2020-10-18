#ifndef SCRIPTS_READER_HPP
#define SCRIPTS_READER_HPP

#include <string>
#include <vector>
#include "../../json.hpp"
#include "../../utils/filepath/filepath.hpp"
#include "../../utils/log/log.hpp"

struct ScriptEntry {
    std::string name;
    std::string path;

    ScriptEntry(std::string name, std::string path) {
        this->name = name;
        this->path = path;
    }
};

class ScriptSummary {
    static bool readFromFile(FilePath filePath, std::vector<ScriptEntry>& scriptSummaryEntries);
};

#endif
