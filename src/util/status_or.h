#ifndef SRC_UTIL_BASE_STATUS_OR_H_
#define SRC_UTIL_BASE_STATUS_OR_H_

#include <new>
#include <string>
#include <utility>

#include "glog/logging.h"
#include "grpc++/grpc++.h"

namespace util {

template<typename T>
class StatusOr {
  template<typename U> friend class StatusOr;

 public:
  // Construct a new StatusOr with Status::UNKNOWN status
  StatusOr();

  // Construct a new StatusOr with the given non-ok status. After calling
  // this constructor, calls to ValueOrDie() will CHECK-fail.
  //
  // NOTE: Not explicit - we want to use StatusOr<T> as a return
  // value, so it is convenient and sensible to be able to do 'return
  // Status()' when the return type is StatusOr<T>.
  StatusOr(const grpc::Status& status);  // NOLINT

  // Construct a new StatusOr with the given value. If T is a plain pointer,
  // value must not be nullptr. After calling this constructor, calls to
  // ValueOrDie() will succeed, and calls to status() will return OK.
  //
  // NOTE: Not explicit - we want to use StatusOr<T> as a return type
  // so it is convenient and sensible to be able to do 'return T()'
  // when when the return type is StatusOr<T>.
  //
  // REQUIRES: if T is a plain pointer, value != nullptr. This requirement is
  // DCHECKed. In optimized builds, passing a null pointer here will have
  // the effect of passing PosixErrorSpace::EINVAL as a fallback.
  StatusOr(const T& value);  // NOLINT

  // Copy constructor.
  StatusOr(const StatusOr& other);

  // Conversion copy constructor, T must be copy constructible from U
  template<typename U>
  StatusOr(const StatusOr<U>& other);

  // Assignment operator.
  StatusOr& operator=(const StatusOr& other);

  // Conversion assignment operator, T must be assignable from U
  template<typename U>
  StatusOr& operator=(const StatusOr<U>& other);

  // Returns a reference to our status. If this contains a T, then
  // returns Status::OK.
  const grpc::Status& status() const;

  // Returns this->status().ok()
  bool ok() const;

  // Returns a reference to our current value, or CHECK-fails if !this->ok().
  // If you need to initialize a T object from the stored value,
  // ConsumeValueOrDie() may be more efficient.
  const T& ValueOrDie() const;

 private:
  grpc::Status status_;
  T value_;
};

// ---------------------- Template Implementation Details ----------------------

namespace internal {

class StatusOrHelper {
 public:
  // Customized behavior for StatusOr<T> vs. StatusOr<T*>
  template<typename T>
  struct Specialize;
};

template<typename T>
struct StatusOrHelper::Specialize {
  // For non-pointer T, a reference can never be nullptr.
  static inline bool IsValueNull(const T& t) {
    return false;
  }
};

template<typename T>
struct StatusOrHelper::Specialize<T*> {
  static inline bool IsValueNull(const T* t) {
    return t == nullptr;
  }
};

}  // namespace internal

template<typename T>
inline StatusOr<T>::StatusOr() : status_(grpc::StatusCode::UNKNOWN, "") {}

template<typename T>
inline StatusOr<T>::StatusOr(const grpc::Status& status) {
  if (status.ok()) {
    status_ =
      grpc::Status(
          grpc::StatusCode::INTERNAL, "Status::OK is not a valid argument.");
  } else {
    status_ = status;
  }
}

template<typename T>
inline StatusOr<T>::StatusOr(const T& value) {
  if (internal::StatusOrHelper::Specialize<T>::IsValueNull(value)) {
    status_ =
        grpc::Status(
            grpc::StatusCode::INTERNAL, "nullptr is not a valid argument.");
  } else {
    status_ = grpc::Status::OK;
    value_ = value;
  }
}

template<typename T>
inline StatusOr<T>::StatusOr(const StatusOr<T>& other)
    : status_(other.status_), value_(other.value_) {}

template<typename T>
inline StatusOr<T>& StatusOr<T>::operator=(const StatusOr<T>& other) {
  status_ = other.status_;
  value_ = other.value_;
  return *this;
}

template<typename T>
template<typename U>
inline StatusOr<T>::StatusOr(const StatusOr<U>& other)
    : status_(other.status_), value_(other.status_.ok() ? other.value_ : T()) {}

template<typename T>
template<typename U>
inline StatusOr<T>& StatusOr<T>::operator=(const StatusOr<U>& other) {
  status_ = other.status_;
  if (status_.ok()) value_ = other.value_;
  return *this;
}

template<typename T>
inline const grpc::Status& StatusOr<T>::status() const {
  return status_;
}

template<typename T>
inline bool StatusOr<T>::ok() const {
  return status().ok();
}

template<typename T>
inline const T& StatusOr<T>::ValueOrDie() const {
  if (!status_.ok()) {
    LOG(FATAL) <<  "Attempting to fetch value instead of handling error "
        << status_.error_message();
  }
  return value_;
}

}  // namespace util

#endif  // SRC_UTIL_BASE_STATUS_OR_H_