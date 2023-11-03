local project = {
    group = "rythe/engine",
    name = "core",
    types = { "test", "module" },
    dependencies = {
        "third_party/OpenCL",
        "rythe/engine/rythe-standard-library"
    },
    defines = { "RYTHE_INTERNAL" }
}

return project