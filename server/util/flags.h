#ifndef SRC_UTIL_BASE_FLAGS_H_
#define SRC_UTIL_BASE_FLAGS_H_

namespace util {

// Parses both absl and gflag flags.
//
// While our codebase uses absl flags (which are preferably to gflags) some of
// our dependencies still reply on gflags (eg: glog). Unfortunately, the two
// don't play nice together.
//
// Each library consumes all defined flags from argv and throws errors on
// unexpected flags. This means that:
//
// - A flag that's defined in both libraries (eg: --help) will only be correctly
//   parsed by a single library. That library will consume it (ie. remove it
//   from argv) making it seem unchanged to the second library.
// - A flag that's defined in a single library will cause errors in the other as
//   an undefined flag.
//
// Our approach creates a pass-through where duplicate flags are correctly
// parsed and will only throw undefined errors if neither library declares a
// flag.
void ParseCommandLineFlags(int argc, char** argv);

}  // namespace util

#endif  // SRC_UTIL_BASE_FLAGS_H_