//
// Created by jesse on 11/10/18.
//

#ifndef PIE_CHARMAP_H
#define PIE_CHARMAP_H

#include <map>
#include <string>
#include <memory>

#include "character.h"

namespace pie {

using charmap = std::map<char, Character>;

charmap getCharMap(const std::string& fontpath, size_t size, const Color& color);

} // namespace pie


#endif //PIE_CHARMAP_H
