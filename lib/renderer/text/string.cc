//
// Created by jesse on 11/10/18.
//

#include "string.h"

namespace pie {

String::String(std::string text, const pie::charmap &char_map)
  : text_(std::move(text)), location_(0.0f, 0.0f)
{
  float x = 0.0f;
  for (const auto& c: text_) {
    // retrieve the corresponding character object from the charmap, copy it
    Character character(char_map.at(c));
    // move the character to the correct position in the string
    character.MoveTo(x, location_.second);
    // advance the cursor for the next character
    x += (character.advance() >> 6);
    // place the character into the char vector
    characters_.push_back(std::move(character));
  }
}

void String::Draw(GLFWwindow *window) const {
  for (auto& c: characters_) {
    // get character position in pixels
    float x, y;
    std::tie(x, y) = c.location();
    // scale the pixel position to screen-space position
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    x /= width;
    y /= height;
    // create character in correct position
    Character char_moved(c);
    char_moved.MoveTo(x, y);
    // draw each character into the OpenGL window
    char_moved.Draw(window);
  }
}

void String::MoveTo(double x, double y) {
  location_.first = x;
  location_.second = y;
}

void String::MoveAlong(double dx, double dy) {
  location_.first += dx;
  location_.second += dy;
}

void String::Rotate(double angle) {

}

}
