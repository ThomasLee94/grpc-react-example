package(default_visibility = ["//visibility:public"])

load("@io_bazel_rules_docker//cc:image.bzl", "cc_image", )

cc_library(
    name = "echo_service_impl",
    srcs = [
        "echo_service_impl.cc",
        "echo_service_impl.h",
            ],
    deps = [
        "//server/proto:echo_grpc_proto",
        "@com_github_grpc_grpc//:grpc++",
    ],
)


cc_binary(
    name = "echo_server",
    srcs = ["echo_server.cc"],
    deps = [
        ":echo_service_impl",
        "//server/proto:echo_grpc_proto",
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_grpc_grpc//:grpc++_reflection",
    ],
)

load("@io_bazel_rules_docker//cc:image.bzl", "cc_image")

cc_image(
    name = "image",
    args = ["--logtostderr"],
    base = "//server/docker/images:cc_image",
    binary = ":echo_server",
)