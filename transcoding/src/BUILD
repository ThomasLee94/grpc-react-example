package(default_visibility = ["//visibility:public"])

load("@transcoder_deps//:requirements.bzl", "requirement")

# Compile the src directory into a python library to be imported by the entry
# point of the transcoder.

py_library(
    name = "transcode_lib",
    srcs = [
        "__init__.py",
        "__main__.py",
        "video.py",
    ],
    deps = [requirement("absl-py")],
)
