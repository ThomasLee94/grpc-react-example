package(default_visibility = ["//visibility:public"])

cc_library(
    name = "battleship_service_impl",
    srcs = [
        "battleship_service_impl.cc",
        "battleship_service_impl.h",
            ],
    deps = [
        "//src/battleship_service/proto:services_grpc_proto",
        "@com_github_grpc_grpc//:grpc++",
        "//src/util:status_macros"
    ],
)


cc_binary(
    name = "server",
    srcs = ["server.cc"],
    deps = [
        ":battleship_service_impl",
        "//src/battleship_game:game",
        "@com_github_grpc_grpc//:grpc++",
        "//src/battleship_service/proto:services_grpc_proto",
    ],
)
