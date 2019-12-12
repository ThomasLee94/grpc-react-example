package(default_visibility = ["//transcoding:__subpackages__"])

load("@rules_python//python:defs.bzl", "py_binary")

py_binary(
    name = "transcoder",
    srcs = ["//transcoding:transcoder.py"],
    deps = ["//transcoding/src:transcode_lib"],
)
