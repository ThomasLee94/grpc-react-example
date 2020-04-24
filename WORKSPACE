workspace(name = "com_github_tom_battleship")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Install GRPC Deps + Build Rules (includes protoc)

http_archive(
    name = "com_github_grpc_grpc",
    sha256 = "c84b3fa140fcd6cce79b3f9de6357c5733a0071e04ca4e65ba5f8d306f10f033",
    strip_prefix = "grpc-1.24.3",
    url = "https://github.com/grpc/grpc/archive/v1.24.3.tar.gz",
)

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps", "grpc_test_only_deps")

grpc_deps()

grpc_test_only_deps()

load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
load("@upb//bazel:workspace_deps.bzl", "upb_deps")
load("@io_bazel_rules_go//go:deps.bzl", "go_register_toolchains", "go_rules_dependencies")
load("@build_bazel_rules_apple//apple:repositories.bzl", "apple_rules_dependencies")

protobuf_deps()

upb_deps()

go_rules_dependencies()

go_register_toolchains()

apple_rules_dependencies()

# Install GRPC Proto

http_archive(
    name = "com_github_grpc_proto",
    sha256 = "73c362cb2223d746ce6d22d203babfe8e51be4080549402a72256c2c77b9f58d",
    strip_prefix = "grpc-proto-5ce8e3e598b805a1e0372062913f24b0715fdefc",
    url = "https://github.com/grpc/grpc-proto/archive/5ce8e3e598b805a1e0372062913f24b0715fdefc.zip",
)

# GLog

http_archive(
    name = "com_github_google_glog",
    sha256 = "f28359aeba12f30d73d9e4711ef356dc842886968112162bc73002645139c39c",
    strip_prefix = "glog-0.4.0",
    url = "https://github.com/google/glog/archive/v0.4.0.tar.gz",
)

# Abseil

http_archive(
    name = "com_github_abseil_absl",
    sha256 = "df253040d3308ca6472d39d1b531395035afa9ee5472d343674524dab216e6c6",
    strip_prefix = "abseil-cpp-ab3552a18964e7063c8324f45b3896a6a20b08a8",
    url = "https://github.com/abseil/abseil-cpp/archive/ab3552a18964e7063c8324f45b3896a6a20b08a8.zip",
)
