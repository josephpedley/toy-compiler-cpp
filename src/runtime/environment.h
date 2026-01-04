#pragma once
#include <unordered_map>
#include <string>
#include <stdexcept>

struct Environment {
    std::unordered_map<std::string, int> values;

    int get(const std::string& name) const {
        auto it = values.find(name);
        if (it == values.end()) {
            throw std::runtime_error("Undefined variable: " + name);
        }
        return it->second;
    }

    void set(const std::string& name, int value) {
        values[name] = value;
    }
};
