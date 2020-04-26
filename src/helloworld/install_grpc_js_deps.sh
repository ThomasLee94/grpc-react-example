FLAGS_protoc_version="3.10.0"
FLAGS_grpc_web_plugin_version="1.0.6"

# ------------------------------ Download protoc -------------------------------
echo 'Downloading protoc.'

PROTOC_URL="https://github.com/protocolbuffers/protobuf/releases/download/v${FLAGS_protoc_version:?}/protoc-${FLAGS_protoc_version:?}-linux-x86_64.zip"
wget "$PROTOC_URL" -O protoc.zip -q --show-progress

unzip -q protoc.zip

echo 'protoc installed!'

# ------------------------ Download protoc-gen-grpc-web ------------------------
echo 'Downloading protoc-gen-grpc-web.'

PROTOC_GRPC_WEB_URL="https://github.com/grpc/grpc-web/releases/download/${FLAGS_grpc_web_plugin_version:?}/protoc-gen-grpc-web-${FLAGS_grpc_web_plugin_version:?}-linux-x86_64"
wget "$PROTOC_GRPC_WEB_URL" -O protoc-gen-grpc-web -q --show-progress

chmod +x protoc-gen-grpc-web
echo 'protoc-gen-grpc-web installed!'

# ----------------------------------- Cleanup ----------------------------------

echo 'Done.'
