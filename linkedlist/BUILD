package(default_visibility = ["//visibility:public"])


cc_library(
    name = "node",
    hdrs = ["node.h"],
    deps = [
        "//node:node"
    ],
)

cc_library(
    name = "linkedlist",
    srcs = ["linkedlist.cc"],
    hdrs = ["linkedlist.h"],
    deps = [
        "//node:node"
    ],
)

cc_library(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":linkedlist"
    ],
)




