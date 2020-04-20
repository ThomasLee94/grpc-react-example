package(default_visibility = ["//visibility:public"])

cc_library(
    name = "random",
    srcs = ["random.cc"],
    hdrs = ["random.h"],
)

cc_library(
    name = "board",
    srcs = ["board.cc"],
    hdrs = ["board.h"],
)

cc_library(
    name = "player",
    srcs = ["player.cc"],
    hdrs = ["player.h"],
    deps = [
        ":random",
        ":board",
    ],
)

cc_library(
    name = "game",
    srcs = ["game.cc"],
    hdrs = ["game.h"],
    deps = [
        ":board",
        ":player",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":random",
        ":board",
        ":player",
        ":game",
    ],
)
