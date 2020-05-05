#include "server/util/flags.h"

#include <string>
#include <vector>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "gflags/gflags.h"

ABSL_DECLARE_FLAG(std::vector<std::string>, undefok);

namespace GFLAGS_NAMESPACE {
  extern void (*gflags_exitfunc)(int);
}  // namespace GFLAGS_NAMESPACE

namespace util {

namespace {

void IgnoreAllGflags() {
  std::vector<gflags::CommandLineFlagInfo> gflag_flags;
  gflags::GetAllFlags(&gflag_flags);

  std::vector<std::string> undefok;
  for (const auto& gflag_flag : gflag_flags) {
    undefok.push_back(gflag_flag.name);
  }

  absl::SetFlag(&FLAGS_undefok, undefok);
}

void ignore_gflags_error(int /* error_code */) {}

void QuietlyHandleCommandLineHelpFlags() {
  void (*old_gflags_error_handler)(int) = GFLAGS_NAMESPACE::gflags_exitfunc;
  GFLAGS_NAMESPACE::gflags_exitfunc = &ignore_gflags_error;
  gflags::HandleCommandLineHelpFlags();
  GFLAGS_NAMESPACE::gflags_exitfunc = old_gflags_error_handler;
}

char** ReserveAndCopyArgv(int argc, char** argv) {
  char** new_argv = new char*[argc];
  for (int i = 0; i < argc; ++i) {
    const int flag_len = strlen(argv[i]) + 1;
    new_argv[i] = new char[flag_len];
    snprintf(new_argv[i], flag_len, "%s", argv[i]);
  }
  return new_argv;
}

}  // namespace

void ParseCommandLineFlags(int argc, char** argv) {
  // We need to copy argv because gflags reorders argv in ways that are
  // incompatible with absl.
  //
  // eg: gflags expects the syntax "--key=value" always whereas absl will also
  // accept "--key value". Because of this, the following argv:
  //
  // > --foo value --bar
  //
  // will be reordered as
  //
  // > --foo --bar value
  //
  // due to gflags interpreting "value" as a positional argument.
  char** argv_copy = ReserveAndCopyArgv(argc, argv);

  // Prevents gflags from exiting fatally when presented with an unknown flag.
  gflags::AllowCommandLineReparsing();

  // Parses all non-help gflags.
  //
  // We need to manually handle help flags such that they don't exit after
  // displaying help information. Otherwise absl will never log its help
  // information.
  google::ParseCommandLineNonHelpFlags(&argc, &argv, false);

  // Parse gflag help flags while preventing system exit.
  QuietlyHandleCommandLineHelpFlags();

  // Populate the absl flag `--undefok` with all gflags.
  //
  // This ensures that if a flag is declared in gflags, but not in absl, absl
  // will not exit fatally. As a result, the only undefined flag errors raised
  // will occur when a flag is neither declared in gflags or absl.
  IgnoreAllGflags();

  // Parse absl flags.
  absl::ParseCommandLine(argc, argv_copy);
}

}  // namespace util