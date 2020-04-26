#!/bin/bash

# Contains installations to ensure that your build environment is configured
# correctly for this repository.

source "$(dirname "$0")/tash.sh"
pushd  "$(dirname "$0")" > /dev/null

assert_linux
assert_tash_compatibility 1.0.0

parse_args "$@"

# ------------------------------- Install Tooling ------------------------------

# Install pre-commit into your git hooks (https://pre-commit.com).
pre-commit install
assert_last_command_ok

# ----------------------------------- Cleanup ----------------------------------

log ok 'Done'
