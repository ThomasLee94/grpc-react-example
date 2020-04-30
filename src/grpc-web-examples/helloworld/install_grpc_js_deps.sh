# FLAGS_protoc_version="3.10."
# FLAGS_grpc_web_plugin_version="1.0.6"
readonly TMP_DIR="$(mktemp -d)"

# ------------------------------ Download protoc -------------------------------

echo 'Downloading protoc.'

PROTOC_URL="https://github.com/protocolbuffers/protobuf/releases/download/v3.11.4/protobuf-cpp-3.11.4.zip"
echo "$PROTOC_URL"
wget "$PROTOC_URL" -O protoc.zip -q --show-progress

unzip -q protoc.zip

sudo mv protobuf-3.11.4/bin/protoc /usr/bin
sudo mv protobuf-3.11.4/include/* /usr/include

echo 'protoc installed!'

# ------------------------ Download protoc-gen-grpc-web ------------------------

echo 'Downloading protoc-gen-grpc-web.'

PROTOC_GRPC_WEB_URL="https://github.com/grpc/grpc-web/releases/download/${FLAGS_grpc_web_plugin_version:?}/protoc-gen-grpc-web-${FLAGS_grpc_web_plugin_version:?}-linux-x86_64"
wget "$PROTOC_GRPC_WEB_URL" -O protoc-gen-grpc-web -q --show-progress

chmod +x protoc-gen-grpc-web
echo 'protoc-gen-grpc-web installed!'

# ----------------------------------- Cleanup ----------------------------------

echo 'Done.'
