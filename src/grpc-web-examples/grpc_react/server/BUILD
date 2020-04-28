package(default_visibility = ["//visibility:public"])

cc_library(
    name = "echo_service_impl",
    srcs = [
        "echo_service_impl.cc",
        "echo_service_impl.h",
            ],
    deps = [
        "//src/grpc-web-examples/grpc_react/server/proto:echo_proto",
        "@com_github_grpc_grpc//:grpc++",
    ],
)


cc_binary(
    name = "server",
    srcs = ["server.cc"],
    deps = [
        ":echo_service_impl",
        "@com_github_grpc_grpc//:grpc++",
        "//src/grpc-web-examples/grpc_react/server/proto:echo_proto",
        "@com_github_grpc_grpc//:grpc++_reflection",
    ],
)