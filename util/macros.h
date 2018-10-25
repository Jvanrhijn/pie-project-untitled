//
// Created by jesse on 10/25/18.
//

#ifndef PIE_MACROS_H
#define PIE_MACROS_H

// useful macros

#define EXPECT_THROWS(x, exception, expr) do { EXPECT_ANY_THROW(try { \
                                                  expr; \
                                                  } catch (const exception &e) {\
                                                    EXPECT_EQ(e.what(), x);\
                                                    throw;\
                                                  });} while (0)

#endif //PIE_MACROS_H
