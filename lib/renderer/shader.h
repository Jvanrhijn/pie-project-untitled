//
// Created by jesse on 11/1/18.
//

#ifndef PIE_SHADER_H_H
#define PIE_SHADER_H_H

class Program {
 public:
  Program() = default;
  ~Program() = default;
};

class Shader {
 public:
  explicit Shader(const std::string &path);
  ~Shader() = default;

  void BindShader(Program &program) const;

 private:



};

#endif //PIE_SHADER_H_H
