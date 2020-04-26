#!/bin/bash

# Capture the original calling script's full path so that we can continue to
# access it after directory changes.
if ! [[ -f "$0" ]]; then
  printf '\e[31mERROR:\e[0m Tash must be sourced before directory changes.\n'
  exit 1
fi
readonly __SCRIPT_PATH="$(realpath "$0")"

# ----------------------- BEGIN SOURCE + SHEBANG SUPPORT -----------------------

# The return statement may only be used if this file was executed directly or
# sourced, meaning that if it fails, we can assert that this file was the
# "shebang" for a tash file.
if ( return 0 2>/dev/null ); then
  if ! [ -z "${__TASH_SENTINEL_VALUE+x}" ]; then
    # Tash has already been "sourced" and we can prevent executing this file a
    # second time by exiting early.
    return 0
  fi
else
  # Tash is being used as a "shebang", however, `$0` points to tash source
  # instead of the file we wish to execute. We fix this by re-running tash
  # directly with a manual `$0` override.
  #
  # Unfortunately we need a sentinel value so that after re-running tash we can
  # detect that we need to source the rewritten `$0` and for this we use
  # "TASH_EXEC".
  exec bash -c ". '$0'" "$1" TASH_EXEC "${@:2}"
  exit $?
fi
declare -g __TASH_SENTINEL_VALUE=true

# ----------------------- END SOURCE + SHEBANG SUPPORT -----------------------

declare -A __IMPORTS

function __register_import {
  local FILE="$1"
  if ! [ -z "$FILE" ]; then
    __IMPORTS[$(realpath "$FILE")]=true
  fi
}

function __is_imported {
  local FILE="$1"
  if ! [ -z "$FILE" ]; then
    if ! [ -z "${__IMPORTS[$(realpath "$FILE")]}" ]; then
      echo true
      return
    fi
  fi
  echo false
}

function import {
  local FILE="$1"
  if ! [ -z "$FILE" ]; then
    if [[ "$(__is_imported "$FILE")" == false ]]; then
      __register_import "$FILE"
      source "$FILE"
    fi
  fi
}

function __import_all_tash_files {
  local TASH_PATH
  TASH_PATH="$(realpath "${BASH_SOURCE[0]}")"

  command pushd "$(dirname "$TASH_PATH")" > /dev/null
  local FILE
  for FILE in $(find src -type f | grep '.sh$'); do
    if [[ "$FILE" =~ .*_test\.sh$ ]]; then continue; fi
    import "$FILE"
  done
  command popd > /dev/null
}

__import_all_tash_files

# ----------------------- BEGIN SOURCE + SHEBANG SUPPORT -----------------------

# If the tash "shebang" sentinel value is set, then remove it and source the
# destination file.
if [[ "$1" == "TASH_EXEC" ]]; then
  shift
  source "$0"
fi

# ----------------------- END SOURCE + SHEBANG SUPPORT -----------------------
