package(default_visibility = ["//visibility:public"])

cc_library(
    name = "ship",
    srcs = ["ship.cc"],
    hdrs = ["ship.h"],
)

cc_library(
    name = "board",
    srcs = ["board.cc"],
    hdrs = ["board.h"],
    deps = [
        ":ship",
    ],
)

cc_library(
    name = "player",
    srcs = ["player.cc"],
    hdrs = ["player.h"],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":ship",
        ":player",
        ":board",
    ],
)
