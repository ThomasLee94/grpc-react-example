#!/bin/bash

import src/assert.sh

declare -rgx TASH_MAJOR_VERSION='1'
declare -rgx TASH_MINOR_VERSION='0'
declare -rgx TASH_PATCH_VERSION='0'
declare -rgx TASH_VERSION="$TASH_MAJOR_VERSION.$TASH_MINOR_VERSION.$TASH_PATCH_VERSION"

function __fail_tash_compatibility {
  local VERSION="$1"
  log fatal "Tash version $TASH_VERSION does not meet minimum compatibility $VERSION"
}

function assert_tash_compatibility {
  local VERSION="$1"

  assert_matches_regex "$VERSION" '^[0-9]+\.[0-9]+\.[0-9]+$'

  local MAJOR
  local MINOR
  local PATCH

  MAJOR="$(echo "$VERSION" | cut -d '.' -f 1)"
  MINOR="$(echo "$VERSION" | cut -d '.' -f 2)"
  PATCH="$(echo "$VERSION" | cut -d '.' -f 3)"

  if [[ "$MAJOR" -gt "$TASH_MAJOR_VERSION" ]]; then
    __fail_tash_compatibility "$VERSION"
  fi
  if [[ "$MAJOR" -lt "$TASH_MAJOR_VERSION" ]]; then
    return
  fi

  if [[ "$MINOR" -gt "$TASH_MINOR_VERSION" ]]; then
    __fail_tash_compatibility "$VERSION"
  fi
  if [[ "$MINOR" -lt "$TASH_MINOR_VERSION" ]]; then
    return
  fi

  if [[ "$PATCH" -gt "$TASH_PATCH_VERSION" ]]; then
    __fail_tash_compatibility "$VERSION"
  fi
}
