# FROM grpcweb/common

# WORKDIR /github/grpc-web/net/grpc/gateway/examples/echo/node-server

# RUN npm install

# EXPOSE 9090
# CMD ["node", "server.js"]

FROM frolvlad/alpine-gcc

RUN apk add --no-cache g++

# Install Bazel, https://bazel.build/versions/master/docs/install.html#ubuntu
FROM openjdk:8

RUN echo "deb [arch=amd64] http://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list \
  && curl https://bazel.build/bazel-release.pub.gpg | apt-key add -

RUN apt-get update \
  && apt-get install -y bazel \
  && rm -rf /var/lib/apt/lists/*

# Set up workspace
RUN mkdir -p /usr/src/app
ENV WORKSPACE /usr/src/app
WORKDIR /usr/src/app

WORKDIR /battleships/src/grpc-web-examples/grpc_js/server

EXPOSE 9090
CMD ["bazel", "run", ":echo_server"]
