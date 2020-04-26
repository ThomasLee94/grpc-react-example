#!/bin/bash

source "$(git rev-parse --show-toplevel)/tash/tash.sh" || exit 1
pushd  "$(dirname "$0")" > /dev/null

assert_linux

declare_string protoc_version '3.10.0'
declare_string grpc_web_plugin_version '1.0.6'
declare_string local_proto_dir ''

parse_args "$@"

assert_not_empty "${FLAGS_protoc_version:?}"
assert_not_empty "${FLAGS_grpc_web_plugin_version:?}"

readonly TMP_DIR="$(mktemp -d)"
readonly OUTPUT_DIR="$(realpath generated)"

# ------------------------ Clean Existing Generated Files ----------------------

log info 'Cleaning existing generated files.'

find generated -type f -name '*_pb.js' -delete
find generated -type d -empty -delete
mkdir -p generated

# ------------------------------ Download protoc -------------------------------

log info 'Downloading protoc.'

pushd "$(mktemp -d)" > /dev/null

PROTOC_URL="https://github.com/protocolbuffers/protobuf/releases/download/"
PROTOC_URL+="v${FLAGS_protoc_version:?}/protoc-${FLAGS_protoc_version:?}"
PROTOC_URL+="-linux-x86_64.zip"
wget "$PROTOC_URL" -O protoc.zip -q --show-progress
assert_last_command_ok

unzip -q protoc.zip
assert_last_command_ok

mv bin/protoc "$TMP_DIR/protoc"
assert_last_command_ok

popd > /dev/null

# ------------------------ Download protoc-gen-grpc-web ------------------------

log info 'Downloading protoc-gen-grpc-web.'

pushd "$TMP_DIR" > /dev/null

PROTOC_GRPC_WEB_URL="https://github.com/grpc/grpc-web/releases/download/"
PROTOC_GRPC_WEB_URL+="${FLAGS_grpc_web_plugin_version:?}/protoc-gen-grpc-web-"
PROTOC_GRPC_WEB_URL+="${FLAGS_grpc_web_plugin_version:?}-linux-x86_64"
wget "$PROTOC_GRPC_WEB_URL" -O protoc-gen-grpc-web -q --show-progress
assert_last_command_ok

chmod +x protoc-gen-grpc-web

popd > /dev/null

# ------------------------ Downloading Well Known Protos -----------------------

log info 'Downloading well-known protos (github.com/protocolbuffers/protobuf).'

pushd "$TMP_DIR" > /dev/null
mkdir external && cd external

wget https://github.com/protocolbuffers/protobuf/archive/master.zip \
    -q --show-progress
assert_last_command_ok

unzip -q master.zip
assert_last_command_ok

popd > /dev/null

# ------------------------- Locate & Compile All Protos ------------------------

# shellcheck disable=SC2154
if [ -z "$FLAGS_local_proto_dir" ]; then
  pushd proper > /dev/null
else
  pushd "$FLAGS_local_proto_dir" > /dev/null
  assert_last_command_ok
  log info "Using local proto directory '$FLAGS_local_proto_dir'"
  log warning "You've used --local_proto_dir: you should not check in the" \
      "generated result as it will not be reproducible for anyone pulling" \
      "this repository."
fi

log info 'Locating and compiling protos.'

declare -ag PROTOS
while read -r PROTO_FILE; do
  PROTOS+=("$PROTO_FILE")
done <<< "$(find src -type f -name '*.proto')"

"$TMP_DIR/protoc" \
  -I=. \
  "-I=$TMP_DIR/external/protobuf-master/src" \
  "--plugin=protoc-gen-grpc-web=$TMP_DIR/protoc-gen-grpc-web" \
  "--grpc-web_out=import_style=commonjs,mode=grpcwebtext:$OUTPUT_DIR" \
  "--js_out=import_style=commonjs:$OUTPUT_DIR" \
  "${PROTOS[@]}"
assert_last_command_ok 'Compilation failed.'

popd > /dev/null

# ----------------------------------- Cleanup ----------------------------------

log ok 'Done.'
