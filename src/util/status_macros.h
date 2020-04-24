// This header file defines multiple macros that control common status logic.
//
// Example:
//
// ```cc
// grpc::Status foo() { ... }
//
// ::util::StatusOr<std::string> bar() { ... }
//
// grpc::Status baz() {
//   RETURN_IF_ERROR(foo()) << "Foo failed";
//
//   std::string value;
//   ASSIGN_OR_RETURN(value, bar(), "Bar failed");
//   LOG(INFO) << value;
//
//   return grpc::Status::OK;
// }
// ```
//
// Many macros can accept any "known status type". These are types that have
// overridden the following methods:
//
// - ::util::errors_internal::IsOk
// - ::util::errors_internal::XToStatus
// - ::util::errors_internal::XToValue
//
// Examples of how to override these methods can be found in the implementation
// details for grpc::Status and ::util::StatusOr<T> below.

#ifndef SRC_UTIL_BASE_STATUS_MACROS_H_
#define SRC_UTIL_BASE_STATUS_MACROS_H_

#include <string>

#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "grpc++/grpc++.h"

#include "src/util/status_or.h"

// Provided an expression that resolves to a known status type, return if error,
// otherwise do nothing.
#define RETURN_IF_ERROR(expr, ...)                                             \
  ({                                                                           \
    auto _expr_result = (expr);                                                \
    if (__builtin_expect(                                                      \
          !::util::errors_internal::IsOk(_expr_result), false)) {              \
      return ::util::errors_internal::XToStatus(_expr_result, ##__VA_ARGS__);  \
    }                                                                          \
    ::util::errors_internal::XToValue(&_expr_result);                          \
  })

// Provided an expression that resolves to a known status monad type, return if
// error, otherwise assign the success value to `lhs`.
#define ASSIGN_OR_RETURN(lhs, expr, ...)                                       \
  ({                                                                           \
    auto _expr_result = (expr);                                                \
    if (__builtin_expect(                                                      \
          !::util::errors_internal::IsOk(_expr_result), false)) {              \
      return ::util::errors_internal::XToStatus(_expr_result, ##__VA_ARGS__);  \
    }                                                                          \
    ::util::errors_internal::assign(                                           \
        &(lhs), ::util::errors_internal::XToValue(&_expr_result));             \
  })

// Asserts that a known status type is OK. Otherwise, exists fatally.
#define CHECK_OK(expr)                                                         \
  ::util::errors_internal::OkOrDie(::util::errors_internal::XToStatus(expr))

// Returns a object which uses the stream operator to build an error message. It
// implicitly converts to `grpc::Status` and `::util::StatusOr<T>`.
#define RETURN_IF_FALSE(expr)                                                  \
    if (__builtin_expect(!(expr), false))                                      \
      return ::util::errors_internal::StatusComposer()

// Returns a object which uses the stream operator to build an error message. It
// implicitly converts to `grpc::Status` and `::util::StatusOr<T>`.
#define RETURN_IF_TRUE(expr)                                                   \
    if (__builtin_expect(!!(expr), false))                                     \
      return ::util::errors_internal::StatusComposer()

// Boolean operator variants of RETURN_IF_FALSE and RETURN_IF_TRUE.
#define RETURN_IF_EQ(expr1, expr2) RETURN_IF_TRUE((expr1) == (expr2))
#define RETURN_IF_NE(expr1, expr2) RETURN_IF_TRUE((expr1) != (expr2))
#define RETURN_IF_LT(expr1, expr2) RETURN_IF_TRUE((expr1) < (expr2))
#define RETURN_IF_GT(expr1, expr2) RETURN_IF_TRUE((expr1) > (expr2))
#define RETURN_IF_LTE(expr1, expr2) RETURN_IF_TRUE((expr1) <= (expr2))
#define RETURN_IF_GTE(expr1, expr2) RETURN_IF_TRUE((expr1) >= (expr2))

// Container variants of RETURN_IF_FALSE and RETURN_IF_TRUE.
#define RETURN_IF_EMPTY(expr) RETURN_IF_EQ(expr.size(), 0)

namespace util {
namespace errors_internal {

// ---------------- Support grpc::Status as a known status type ----------------

inline bool IsOk(const grpc::Status& status) {
  return status.ok();
}

inline const grpc::Status XToStatus(const grpc::Status& status) {
  return status;
}

template <typename... Args>
inline const grpc::Status XToStatus(
    const grpc::Status& status, const Args&... rest) {
  return grpc::Status(
      status.error_code(), absl::StrCat(rest..., ": ", status.error_message()));
}

inline void XToValue(const grpc::Status* status) {}

// ------------- Support ::util::StatusOr<T> as a known status type ------------

template <typename T>
inline bool IsOk(const ::util::StatusOr<T>& status) {
  return status.ok();
}

template <typename T>
inline const grpc::Status XToStatus(const util::StatusOr<T>& statusor) {
  return statusor.status();
}

template <typename T, typename... Args>
inline const grpc::Status XToStatus(
    const util::StatusOr<T>& statusor, const Args&... rest) {
  return grpc::Status(
      statusor.status().error_code(),
      absl::StrCat(rest..., ": ", statusor.status().error_message()));
}

template <typename T>
inline T XToValue(const util::StatusOr<T>* statusor) {
  return statusor->ValueOrDie();
}

// -------------------------- Implementation Details --------------------------

template <typename T>
inline void assign(T* lhs, const T& value) { *lhs = value; }

void OkOrDie(const grpc::Status& status);

class StatusComposer {
 public:
  StatusComposer& operator<<(const std::string& value);
  StatusComposer& operator<<(const char* value);
  StatusComposer& operator<<(char value);
  StatusComposer& operator<<(int16_t value);
  StatusComposer& operator<<(uint16_t value);
  StatusComposer& operator<<(int32_t value);
  StatusComposer& operator<<(uint32_t value);
  StatusComposer& operator<<(int64_t value);
  StatusComposer& operator<<(uint64_t value);
  StatusComposer& operator<<(double value);
  StatusComposer& operator<<(const absl::string_view& value);
  StatusComposer& operator<<(const grpc::Status& status);

  operator grpc::Status() const {
    return grpc::Status(grpc::StatusCode::UNKNOWN, message_);
  }

  template <typename T>
  operator util::StatusOr<T>() const {
    return grpc::Status(grpc::StatusCode::UNKNOWN, message_);
  }

 private:
  std::string message_;
};

}  // namespace errors_internal
}  // namespace util

#endif  // SRC_UTIL_BASE_STATUS_MACROS_H_