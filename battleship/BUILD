package(default_visibility = ["//visibility:public"])

cc_library(
    name = "board",
    srcs = ["board.cc"],
    hdrs = ["board.h"],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":board",
    ],
)
