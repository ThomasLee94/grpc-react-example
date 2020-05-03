package(default_visibility = ["//visibility:public"])

load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")
# load("@rules_proto//proto:defs.bzl", "proto_library")
# load("//bazel:closure_grpc_web_library.bzl", "closure_grpc_web_library")

# ------------------------------- echo.proto -------------------------------

proto_library(
    name = "echo_proto",
    srcs = [
        "echo.proto",
    ],
)

cc_proto_library(
    name = "echo_cc_proto",
    deps = [":echo_proto"],
)

cc_grpc_library(
    name = "echo_grpc_proto",
    srcs = [":echo_proto"],
    grpc_only = True,
    deps = [":echo_cc_proto"],
)

# closure_grpc_web_library(
#     name = "echo",
#     deps = [
#         ":echo_proto",
#     ],
# )