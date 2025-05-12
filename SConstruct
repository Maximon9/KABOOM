#!/usr/bin/env python
import os
import sys


def RGlob(
    paths: list[str] = [],
    patterns: list[str] = [".cpp", ".c"],
    ondisk: bool = True,
    source: bool = False,
    strings: bool = False,
    exclude: list[str] = [],
):
    result_nodes = []
    while paths:
        path = paths.pop()
        all_nodes = Glob(
            f"{path}/*",
            ondisk=ondisk,
            source=source,
            strings=strings,
            exclude=exclude,
        )
        paths.extend(
            entry
            for entry in all_nodes
            if entry.isdir() or (entry.srcnode() and entry.srcnode().isdir())
        )  # `srcnode()` must be used because `isdir()` doesn't work for entries in variant dirs which haven't been copied yet.
        # print(list(map(lambda node: str(node), paths)))

        for pattern in patterns:
            result_nodes.extend(
                Glob(
                    f"{path}/*{pattern}",
                    ondisk=ondisk,
                    source=source,
                    strings=strings,
                    exclude=exclude,
                )
            )

    return result_nodes


libname = "KABOOM"
projectdir = "demo"

localEnv = Environment(tools=["default"], PLATFORM="")

# Build profiles can be used to decrease compile times.
# You can either specify "disabled_classes", OR
# explicitly specify "enabled_classes" which disables all other classes.
# Modify the example file as needed and uncomment the line below or
# manually specify the build_profile parameter when running SCons.

# localEnv["build_profile"] = "build_profile.json"

customs = ["custom.py"]
customs = [os.path.abspath(path) for path in customs]

opts = Variables(customs, ARGUMENTS)
opts.Update(localEnv)

Help(opts.GenerateHelpText(localEnv))

env = localEnv.Clone()

if not (os.path.isdir("godot-cpp") and os.listdir("godot-cpp")):
    print_error(
        """godot-cpp is not available within this folder, as Git submodules haven't been initialized.
Run the following command to download godot-cpp:

    git submodule update --init --recursive"""
    )
    sys.exit(1)

env = SConscript("godot-cpp/SConstruct", {"env": env, "customs": customs})

env.Append(CPPPATH=["src/"])

sources = RGlob(["src"], exclude=["src\\gen"])
print("\nAll Sources:")
print(list(map(lambda node: str(node), sources)))
print("\n")

if env["target"] in ["editor", "template_debug"]:
    try:
        doc_data = env.GodotCPPDocData(
            "src/gen/doc_data.gen.cpp", source=Glob("doc_classes/*.xml")
        )
        sources.append(doc_data)
    except AttributeError:
        print("Not including class reference as we're targeting a pre-4.3 baseline.")

# .dev doesn't inhibit compatibility, so we don't need to key it.
# .universal just means "compatible with all relevant arches" so we don't need to key it.
suffix = env["suffix"].replace(".dev", "").replace(".universal", "")

lib_filename = "{}{}{}{}".format(
    env.subst("$SHLIBPREFIX"), libname, suffix, env.subst("$SHLIBSUFFIX")
)

library = env.SharedLibrary(
    "bin/{}/{}".format(env["platform"], lib_filename),
    source=sources,
)

copy = env.Install("{}/bin/{}/".format(projectdir, env["platform"]), library)

default_args = [library, copy]
Default(*default_args)
