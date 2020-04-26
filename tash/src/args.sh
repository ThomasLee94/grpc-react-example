#!/bin/bash

# Command line arguments adhere to the following syntax expectations:
#
# - Positional argument: `foo.sh foo`
# - Escaped positional argument: `foo.sh -- --foo`
# - Keyword argument: `foo.sh --foo bar`
#
# For example, `foo.sh --foo bar baz -- --qux` is parsed as:
# - Keyword argument: `--foo bar`
# - Positional argument: `baz`
# - Positional argument: `--qux`
#
# To declare arguments:
#
# `declare_<type> <name> <default_value> <required>?`
#
# Where:
# - type: ^(string|integer|float|boolean)$
# - name: ^[a-zA-Z][a-zA-Z0-9_]*$
# - default_value: .*
# - required: ^(required|optional)$ defaults to 'optional'
#
# To parse arguments in Tash, run the following command *after* declaring your
# flags.
#
# `parse_args "$@"`
#
# Note that boolean arguments have special semantics such that:
#
# Truthy:
# - `--foo`
# - `--foo yes`
# - `--foo true`
#
# Falsey:
# - `--foo no`
# - `--foo false`
#
# All truthy and falsey values will be normalized to "true" and "false"
# respectively.
#
# To access flag values, the variable `FLAGS_<name>` will be exported. To
# access positional arguments, the variable `FLAGS_POSITIONAL` is exported.
# Note that it maintains order.
#
# Example usage:
#
# ```
# declare_boolean help false optional
#
# if [[ "$FLAGS_help" == true ]]; then
#   ...
# fi
#
# for $VALUE in $FLAGS_POSITIONAL; do
#   echo "$VALUE"
# done
# ```

import src/assert.sh
import src/logging.sh

assert_linux

declare -Ag __VALIDATORS
__VALIDATORS[STRING]='^.*$'
__VALIDATORS[INTEGER]='^[-+]?([1-9][0-9]*|0)$'
__VALIDATORS[FLOAT]='^[-+]?([1-9][0-9]*|0)\.?[0-9]*$'
__VALIDATORS[BOOLEAN]='^true|false|yes|no$'

declare -Agx __FLAG_VALIDATORS
declare -Agx __FLAG_TYPES
declare -Agx __FLAG_DEFAULT_VALUES
declare -agx __REQUIRED_FLAGS
declare -agx __OPTIONAL_FLAGS

function __set_flag {
  local NAME="$1"
  local VALUE="$2"

  if [ -z "${__FLAG_TYPES[$NAME]}" ]; then
    log fatal "Unexpected flag --$NAME."
  fi

  # Normalize boolean values to true/false
  if [[ "${__FLAG_TYPES[$NAME]}" == "BOOLEAN" ]]; then
    case "$VALUE" in
      true|yes)
        VALUE=true
        ;;
      false|no)
        VALUE=false
        ;;
      *)
        log fatal "Unsure how to normalize boolean value '$VALUE'."
        ;;
    esac
  fi

  export "FLAGS_$NAME=$VALUE"
}

function __declare_flag {
  local NAME="$1"
  local DEFAULT_VALUE="$2"
  local TYPE="$3"
  local REQUIRED="$4"

  assert_not_empty "$NAME"
  assert_matches_regex "$NAME" '^[a-zA-Z][a-zA-Z0-9_]*$'
  if ! [ -z "${__FLAG_TYPES[$NAME]}" ]; then
    log fatal "Redefinition of flag '$NAME' not allowed."
  fi

  assert_not_empty "$TYPE"
  __FLAG_TYPES[$NAME]=$TYPE

  local VALIDATOR="${__VALIDATORS[$TYPE]}"
  assert_not_empty "$VALIDATOR"
  __FLAG_VALIDATORS[$NAME]="$VALIDATOR"

  if ! [ -z "$DEFAULT_VALUE" ]; then
    assert_matches_regex "$DEFAULT_VALUE" "$VALIDATOR"
  fi

  if [ -z "$REQUIRED" ]; then
    REQUIRED='optional'
  fi
  assert_matches_regex "$REQUIRED" '^required|optional$'
  if [[ "$REQUIRED" == "required" ]]; then
    __REQUIRED_FLAGS+=($NAME)
  else
    __OPTIONAL_FLAGS+=($NAME)
  fi

  __FLAG_DEFAULT_VALUES[$NAME]="$DEFAULT_VALUE"
  export "FLAGS_$NAME=$DEFAULT_VALUE"
}

function declare_string { __declare_flag "$1" "$2" 'STRING' "$3"; }
function declare_integer { __declare_flag "$1" "$2" 'INTEGER' "$3"; }
function declare_float { __declare_flag "$1" "$2" 'FLOAT' "$3"; }
function declare_boolean { __declare_flag "$1" "$2" 'BOOLEAN' "$3"; }

function parse_args {
  local -A PARSED_FLAGS
  local -A UNDEFINED_FLAGS
  for NAME in "${__REQUIRED_FLAGS[@]}"; do
    UNDEFINED_FLAGS[$NAME]=true
  done

  declare -g POSITIONALS=""
  while (( "$#" )); do
    case "$1" in
      --)  # end of argument parsing
        shift
        break
        ;;
      --*=*)
        local COMPOSITE=${1:2}
        local NAME="${COMPOSITE%%=*}"
        local VALUE="${COMPOSITE#*=}"

        if [[ "${PARSED_FLAGS[$NAME]}" == true ]]; then
          log fatal "Flag --$NAME defined multiple times."
        fi
        PARSED_FLAGS[$NAME]=true
        UNDEFINED_FLAGS[$NAME]=false

        if [[ "${__FLAG_TYPES[$NAME]}" == 'BOOLEAN' ]]; then
          if [ -z "$VALUE" ]; then
            VALUE=true
          fi
        fi

        assert_matches_regex "$VALUE" "${__FLAG_VALIDATORS[$NAME]}"
        __set_flag "$NAME" "$VALUE"
        shift
        ;;
      --*)
        local NAME=${1:2}
        local VALUE="$2"
        shift

        if [[ "${PARSED_FLAGS[$NAME]}" == true ]]; then
          log fatal "Flag --$NAME defined multiple times."
        fi
        PARSED_FLAGS[$NAME]=true
        UNDEFINED_FLAGS[$NAME]=false

        if [ $# -eq 0 ]; then
          if [[ "${__FLAG_TYPES[$NAME]}" == 'BOOLEAN' ]]; then
            VALUE=true
          fi
        else
          if [[ "${__FLAG_TYPES[$NAME]}" == 'BOOLEAN' ]]; then
            if [[ "$VALUE" == --* ]]; then
              VALUE=true
            else
              shift 1
            fi
          else
            shift 1
          fi
        fi

        assert_matches_regex "$VALUE" "${__FLAG_VALIDATORS[$NAME]}"
        __set_flag "$NAME" "$VALUE"
        ;;
      *)  # preserve positional arguments
        POSITIONALS+=" \"$1\""
        shift
        ;;
    esac
  done
  while (( "$#" )); do
    POSITIONALS+=" \"$1\""
    shift
  done

  __process_default_flags

  for NAME in "${!UNDEFINED_FLAGS[@]}"; do
    if [[ "${UNDEFINED_FLAGS[$NAME]}" == true ]]; then
      log fatal "Keyword argument --$NAME is required."
    fi
  done

  export FLAGS_POSITIONAL=($POSITIONALS)
}
