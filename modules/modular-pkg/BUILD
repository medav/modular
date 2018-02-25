cc_binary (
    name = "hello.dll",
    deps = ["//core:public"],
    srcs = glob(["hello/source/*"]),
    includes = [
        "hello/include", 
        "_protocols",
        "_interfaces",
        ".",
    ],
    linkshared = True,
    visibility = ["//visibility:public"],
)

cc_binary (
    name = "telemetry.dll",
    deps = ["//core:public"],
    srcs = glob(["telemetry/source/*"]),
    includes = [
        "telemetry/include", 
        "_protocols",
        "_interfaces",
        ".",
    ],
    linkshared = True,
    visibility = ["//visibility:public"],
)