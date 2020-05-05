package(default_visibility = ["//visibility:public"])

load("@io_bazel_rules_docker//container:image.bzl", "container_image")
load("@io_bazel_rules_docker//cc:image.bzl", DISTROLESS_CC_BASE = "DEFAULT_BASE")

container_image(
    name = "cc_image",
    base = DISTROLESS_CC_BASE,
    layers = [
        "//server/docker/layers/grpc_health_client:layer",
    ],
)