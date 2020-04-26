#!/bin/bash

# Logging supports several severities:
# - info
# - warning
# - error
# - done
# - fatal
#
# Note that `fatal` logs will terminate the running process with error code `1`.
#
# Example usage:
#
# ```
# log info Downloading foo...
# log warning Don't ctrl-c during the download please.
# log ok Done
# ```

declare -gA __LOG_PREFIXES
__LOG_PREFIXES[OK]='\e[32m[OK]\e[0m'
__LOG_PREFIXES[INFO]='\e[2m[INFO]\e[0m'
__LOG_PREFIXES[WARNING]='\e[33m[WARNING]\e[0m'
__LOG_PREFIXES[ERROR]='\e[31m[ERROR]\e[0m'
__LOG_PREFIXES[FATAL]='\e[41m\e[97m\e[1m[FATAL]\e[0m'

function log {
  local LEVEL="${1^^}"
  local MESSAGE="${*:2}"

  local PREFIX="${__LOG_PREFIXES[$LEVEL]}"
  if [ -z "$PREFIX" ]; then
    log warning "Unknown log level '$LEVEL'."
    PREFIX="[$LEVEL]"
  fi

  echo -e "$PREFIX": "$MESSAGE"

  if [[ "$LEVEL" == 'FATAL' ]]; then
    exit 1
  fi
}
