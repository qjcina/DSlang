//
// Created by qj on 05.06.18.
//

#ifndef PROJECT_REGEX_H
#define PROJECT_REGEX_H

#include <regex>

const std::regex labelRegex = std::regex("([a-z]*): ([0-9]*)"); // NOLINT
const std::regex labelName = std::regex("([a-z]*):"); // NOLINT
#endif //PROJECT_REGEX_H
