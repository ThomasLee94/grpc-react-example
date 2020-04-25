#!/bin/bash

sudo apt-get -y install build-essential autoconf libtool pkg-config
sudo apt-get -y install libgflags-dev
if ! [[ -f ~/bin/grpc_cli ]]; then
  pushd "$(mktemp -d)"
  git clone https://github.com/grpc/grpc.git ./
  git submodule update --init
  make grpc_cli
  mv ./bins/opt/grpc_cli ~/bin/grpc_cli
  popd
fi

# add the following to your path: export PATH="$PATH:$HOME/bin"
