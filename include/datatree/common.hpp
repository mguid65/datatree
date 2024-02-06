/**
 * @brief Common utilities
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#ifndef DATATREE_COMMON_HPP
#define DATATREE_COMMON_HPP

namespace mguid {

// Uses compiler specific extensions if possible.
#ifdef __GNUC__ // GCC, Clang, ICC

inline void unreachable() { __builtin_unreachable(); }

#elif defined(_MSC_VER) // MSVC

inline void unreachable() { __assume(false); }

#else
// Even if no extension is used, undefined behavior is still raised by
// the empty function body and the noreturn attribute.

[[noreturn]] inline void unreachable() {}

#endif

}

#endif  // DATATREE_COMMON_HPP
