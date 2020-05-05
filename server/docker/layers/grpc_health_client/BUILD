package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "grpc_health_client",
    srcs = ["grpc_health_client.cc"],
    deps = [
        #FIXME: https://github.com/grpc/grpc/issues/20828
        "@com_github_grpc_grpc//src/proto/grpc/health/v1:health_proto",
        "//server/util:flags",
        "@com_github_abseil_absl//absl/flags:flag",
        "@com_github_abseil_absl//absl/time",
        "@com_github_google_glog//:glog",
        "@com_github_grpc_grpc//:grpc++",
    ],
)

load("@io_bazel_rules_docker//container:layer.bzl", "container_layer")

container_layer(
    name = "layer",
    directory = "/bin/",
    files = [":grpc_health_client"],
)