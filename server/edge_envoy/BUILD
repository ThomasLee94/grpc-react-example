load("@io_bazel_rules_docker//container:container.bzl", "container_image")

container_image(
    name = "image_envoy",
    base = "@envoy_latest//image",
    cmd = [
        "/usr/local/bin/envoy",
        "-c",
        "/envoy.yaml",
    ],
    files = ["envoy.yaml"],
)