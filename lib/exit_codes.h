//
// Created by jesse on 10/30/18.
//

#ifndef PIE_EXIT_CODES_H
#define PIE_EXIT_CODES_H

namespace pie {

enum ExitCode {
  FAIL_OPENGL_INIT = 1,
  FAIL_WINDOW_CREATE = 2,
  FAIL_LOAD_GL = 3,
  FAIL_LOAD_TEXTURE = 4,
};

}

#endif //PIE_EXIT_CODES_H
