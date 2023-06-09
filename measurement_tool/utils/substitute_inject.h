#ifndef MEASUREMENT_TOOL_SUBSTITUTE_INJECT_H
#define MEASUREMENT_TOOL_SUBSTITUTE_INJECT_H

#include "string"
#include "unordered_set"
#include "vector"

void substituteInjectUtil(const std::string &s,
                          const std::unordered_set<char> &alphabet,
                          char substitute_char,
                          std::vector<std::string> &result) {
    bool found = false;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == substitute_char) {
            for (const auto c: alphabet) {
                std::string new_s = s;
                new_s[i] = c;
                found = true;
                substituteInjectUtil(new_s, alphabet, substitute_char, result);
            }
        }
    }

    if (!found) {
        result.push_back(s);
    }
}

// Function to generate all possible strings by replacing '?' with alphabet
std::vector<std::string> substituteInject(const std::string &s,
                                          std::unordered_set<char> alphabet) {
    if (alphabet.contains('?')) {
        alphabet.erase('?');
    }

    std::vector<std::string> result;
    substituteInjectUtil(s, alphabet, '?', result);
    return result;
}

#endif
