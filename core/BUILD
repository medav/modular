cc_binary(
    name = "modular",
    deps = [":public"],
    srcs = [
        "source/main.cpp", 
        "source/module-manager.cpp", 
        "source/module-win.cpp",
    ],
    includes = ["include", "."]
)

cc_inc_library(
    name = "public",
    hdrs = glob(["public/*"]),
    prefix = "public",
    visibility = ["//visibility:public"]
)