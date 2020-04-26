#!/bin/bash
set -o history

import src/logging.sh

function assert_linux {
  if [[ "$OSTYPE" != 'linux-gnu' ]]; then
    log fatal "Incompatible OS: $OSTYPE; Expected 'linux-gnu'"
  fi
}

function assert_not_empty {
  local VALUE="$1"
  if [ -z "$VALUE" ]; then
    log fatal 'Provided value may not be empty.'
  fi
}

function assert_matches_regex {
  local VALUE="$1"
  local REGEX="$2"
  if ! [[ "$VALUE" =~ $REGEX ]]; then
    log fatal "'$VALUE' must match regex '$REGEX'"
  fi
}

function assert_last_command_ok {
  # shellcheck disable=SC2181
  if [ $? -ne 0 ]; then
    local ERROR_MESSAGE="$1"
    local LAST_COMMAND
    LAST_COMMAND="$(history | tail -n2 | head -n1 | sed 's/^ *[0-9]* *//')"
    if [ -z "$ERROR_MESSAGE" ]; then
      log fatal "Command failed: $LAST_COMMAND"
    else
      log fatal "$ERROR_MESSAGE"
    fi
  fi
}
