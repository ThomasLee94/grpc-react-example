workspace(name = "com_github_terrace_experimental")

# ------------------------------Setup python rules------------------------------

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

# Requires python3-distutils to be installed.
git_repository(
    name = "rules_python",
    commit = "94677401bc56ed5d756f50b441a6a5c7f735a6d4",
    remote = "https://github.com/bazelbuild/rules_python.git",
)

load("@rules_python//python:repositories.bzl", "py_repositories")

py_repositories()

load("@rules_python//python:pip.bzl", "pip_repositories")

pip_repositories()

# ----------------------Install transcoder dependencies-------------------------

load("@rules_python//python:pip.bzl", "pip_import")

pip_import(
    name = "transcoder_deps",
    python_interpreter = "python3",
    requirements = "//transcoding:requirements.txt",
)

load("@transcoder_deps//:requirements.bzl", "pip_install")

pip_install()
