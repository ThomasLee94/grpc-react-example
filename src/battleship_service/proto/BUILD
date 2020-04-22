
package(default_visibility = ["//src/battleship_services/proto/pingpong:__subpackages__"])

load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

# ------------------------------- services.proto -------------------------------

proto_library(
    name = "services_proto",
    srcs = ["services.proto"],
)

cc_proto_library(
    name = "services_cc_proto",
    deps = [":services_proto"],
)

cc_grpc_library(
    name = "services_grpc_proto",
    srcs = [":services_proto"],
    grpc_only = True,
    deps = [":services_cc_proto"],
)