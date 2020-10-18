#include "./reader.hpp"

bool ScriptSummary::readFromFile(FilePath filePath, std::vector<ScriptEntry>& scriptSummaryEntries) {
    json scriptSummaryJson;
    bool success = JSON::load(filePath.value, &scriptSummaryJson);
    if (!success) {
        return false;
    }

    for (auto scriptEntry : scriptSummaryJson) {
        const auto name = std::string(scriptEntry["name"]);
        const auto path = std::string(scriptEntry["path"]);

        if (name.size() <= 0 || path.size() <= 0) {
            LOG_WARNING("Invalid entry at 'behaviours.json'. [name = " << name << ", path = " << path << "]");
            continue;
        }
        scriptSummaryEntries.push_back(ScriptEntry(name, path));
    }

    return true;
}