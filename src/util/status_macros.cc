#include "src/util/status_macros.h"

#include <string>

#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "glog/logging.h"
#include "grpc++/grpc++.h"

namespace util {
namespace errors_internal {

void OkOrDie(const grpc::Status& status) {
  if (!status.ok()) {
    LOG(FATAL)
        << "Expected status OK instead was "
        << "(code " << status.error_code() << ") "
        << ": " << status.error_message();
  }
}

StatusComposer& StatusComposer::operator<<(const std::string& value) {
  message_ = absl::StrCat(message_, value);
  return *this;
}

StatusComposer& StatusComposer::operator<<(const char* value) {
  message_ = absl::StrCat(message_, value);
  return *this;
}

StatusComposer& StatusComposer::operator<<(char value) {
  message_ = absl::StrCat(message_, std::to_string(value));
  return *this;
}

StatusComposer& StatusComposer::operator<<(int16_t value) {
  message_ = absl::StrCat(message_, value);
  return *this;
}

StatusComposer& StatusComposer::operator<<(uint16_t value) {
  message_ = absl::StrCat(message_, value);
  return *this;
}

StatusComposer& StatusComposer::operator<<(int32_t value) {
  message_ = absl::StrCat(message_, value);
  return *this;
}

StatusComposer& StatusComposer::operator<<(uint32_t value) {
  message_ = absl::StrCat(message_, value);
  return *this;
}

StatusComposer& StatusComposer::operator<<(int64_t value) {
  message_ = absl::StrCat(message_, value);
  return *this;
}

StatusComposer& StatusComposer::operator<<(uint64_t value) {
  message_ = absl::StrCat(message_, value);
  return *this;
}

StatusComposer& StatusComposer::operator<<(double value) {
  message_ = absl::StrCat(message_, value);
  return *this;
}

StatusComposer& StatusComposer::operator<<(const absl::string_view& value) {
  message_ = absl::StrCat(message_, value);
  return *this;
}

StatusComposer& StatusComposer::operator<<(const grpc::Status& status) {
  message_ =
    absl::StrCat(
        message_,
        absl::StrFormat(
            "Status(%d, \"%s\")", status.error_code(), status.error_message()));
  return *this;
}

}  // namespace errors_internal
}  // namespace util