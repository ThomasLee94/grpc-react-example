#!/bin/bash

import src/args.sh

declare_boolean help false optional

function __describe_flag {
  local NAME="$1"
  local REQUIRED="$2"

  local TYPE="${__FLAG_TYPES[$NAME]}"
  local DEFAULT_VALUE="${__FLAG_DEFAULT_VALUES[$NAME]}"
  local FLAG_VARIABLE="FLAGS_$NAME"
  local FLAG_VALUE="${!FLAG_VARIABLE}"

  echo "  --$NAME"
  printf "\e[2m"
  echo "    type: $TYPE"
  if [[ "$REQUIRED" == false ]]; then
    echo "    default: $DEFAULT_VALUE"
  fi
  echo "    value: $FLAG_VALUE"
  printf "\e[0m"
}

function __describe_flags {
  echo -e "\e[4mCommand line arguments\e[0m\n"
  if [[ ${#__REQUIRED_FLAGS[@]} -gt 0 ]]; then
    echo 'Required flags:'
    for NAME in "${__REQUIRED_FLAGS[@]}"; do
      __describe_flag "$NAME" true
    done
    echo
  fi
  echo 'Optional flags:'
  for NAME in "${__OPTIONAL_FLAGS[@]}"; do
    __describe_flag "$NAME" false
  done
}

function __describe_docstring {

  if ! [ -f "$__SCRIPT_PATH" ]; then
    echo -e "\e[33m<unable to locate $0>\e[0m\n"
    return 1
  fi

  # Search for the docstring

  local SKIP_NEXT_LINE=false
  if [[ "$(head -n 1 "$__SCRIPT_PATH")" == '#!'* ]]; then
    SKIP_NEXT_LINE=true
  fi

  local SEEKING_DOCSTRING=true
  local DOCSTRING=''
  while read -r LINE; do
    if [[ "$SKIP_NEXT_LINE" == true ]]; then
      SKIP_NEXT_LINE=false
      continue
    fi
    if [[ "$SEEKING_DOCSTRING" == true ]]; then
      if [ -n "$LINE" ]; then
        SEEKING_DOCSTRING=false
      fi
    fi
    if [[ "$SEEKING_DOCSTRING" == false ]]; then
      if [ -z "$LINE" ]; then
        break
      fi
      if ! [[ "$LINE" == '#'* ]]; then
        DOCSTRING=''
        break
      fi
      # shellcheck disable=SC2001
      DOCSTRING+="$(echo "$LINE" | sed 's/#\s\?//')\n"
    fi
  done < "$__SCRIPT_PATH"

  if [ -n "$DOCSTRING" ]; then
    printf '\e[2m'
    echo -e "$DOCSTRING"
    printf '\e[0m'
  fi
}

function __describe_program {
  echo "Help for $(basename "$0"):"
  echo
  __describe_docstring
  __describe_flags
}

function __process_default_flags {
  if [[ "${FLAGS_help:?}" == true ]]; then
    __describe_program
    exit 1
  fi
}
