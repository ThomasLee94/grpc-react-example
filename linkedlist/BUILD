package(default_visibility = ["//visibility:public"])


cc_library(
    name = "node",
    hdrs = ["node.h"],
)

cc_library(
    name = "linkedlist",
    srcs = ["linkedlist.cc"],
    hdrs = ["linkedlist.h"],
    deps = [
        ":node"
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":linkedlist"
    ],
)




