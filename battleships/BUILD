package(default_visibility = ["//visibility:public"])

cc_library(
    name = "battleship",
    srcs = ["battleship.cc"],
    hdrs = ["battleship.h"],
    deps = [
      ":block"
    ],
)

cc_library(
    name = "block",
    hdrs = ["block.h"],
)

cc_library(
    name = "player",
    srcs = ["player.cc"],
    hdrs = ["player.h"],
    deps = [
        ":battleship",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":player",
    ],
)
