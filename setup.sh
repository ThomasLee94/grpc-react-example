#!/bin/bash

# Contains installations to ensure that your build environment is configured
# correctly for this repository.

# Pull git submodules.
#
# Note that this step is required before sourcing tash since tash is a git
# submodule.
git submodule init || exit 1
git submodule update || exit 1

source "$(git rev-parse --show-toplevel)/tash/tash.sh" || exit 1
pushd  "$(dirname "$0")" > /dev/null

assert_linux

# ------------------------------- Install Tooling ------------------------------

# Install Git LFS (large file storage).
git lfs install
assert_last_command_ok

# Enable Git LFS file locking verification
git config lfs.https://github/terrace-co/proper.git/info/lfs.locksverify true

# Pull files stored in Git LFS (necessary if lfs was installed after clone).
git lfs pull
assert_last_command_ok

# Install pre-commit into your git hooks (https://pre-commit.com).
pre-commit install
assert_last_command_ok

# ----------------------------------- Cleanup ----------------------------------

log ok 'Done'
