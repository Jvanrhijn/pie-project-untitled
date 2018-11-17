//
// Created by jesse on 11/10/18.
//

#include "string.h"

namespace pie {

String::String(std::string text, const pie::charmap &char_map, float scale)
  : text_(std::move(text)), location_(0.0f, 0.0f), scale_(scale)
{
  float dx = 0.0f;
  for (const auto& c: text_) {
    // retrieve the corresponding character object from the charmap, copy it
    Character character(char_map.at(c));
    character.Scale(scale);
    // move the character to the correct position in the string
    //character.MoveTo(x, location_.second);
    character.MoveAlong(dx, 0.0f);
    // advance the cursor for the next character
    dx += (character.advance() >> 6)*scale; // advance is given in 1/64 pixels
    // place the character into the char vector
    characters_.push_back(std::move(character));
  }
}

void String::Center() {
  const auto first_char = characters_.front();
  const auto last_char = characters_.back();
  const auto loc = last_char.location();
  // only need first and last char for x shift
  const double xshift = (-0.5*(loc.first + last_char.Width()) - first_char.bearing().first)*scale_;
  // all numbers are equally tall; grab last char arbitrarily
  const double yshift = -0.5*last_char.Height()*scale_;
  std::for_each(characters_.begin(), characters_.end(), [&xshift, &yshift](Character& c){c.MoveAlong(xshift, yshift);});
}

void String::Draw(GLFWwindow *window) const {
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  for (const auto& c: characters_) {
    // get character position in pixels
    float x, y;
    std::tie(x, y) = c.location();
    // scale the pixel position to screen-space position
    x /= width;
    y /= height;
    // create character in correct position
    Character char_moved(c);
    char_moved.MoveTo(location_.first + x, location_.second + y);
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
  throw std::runtime_error("String rotating not implemented");
}

}
