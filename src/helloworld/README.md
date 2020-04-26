# gRPC-Web Hello World Guide

This guide is intended to help you get started with gRPC-Web with a simple
Hello World example. For more information about the gRPC-Web project as a
whole, please visit the [main repo](https://github.com/grpc/grpc-web).

## Install `proto` & `protoc-gen-grpc-web`

To generate the protobuf messages and client service stub class from your
`.proto` definitions, we need the `protoc` binary and the
`protoc-gen-grpc-web` plugin.

To install the above, run `sh install_grpc_js_deps.sh`

If you are left with executables, make sure they are both discoverable from your PATH.

For example, in MacOS, you can do:

```
$ sudo mv ~/Downloads/protoc-gen-grpc-web-1.0.7-darwin-x86_64 \
  /usr/local/bin/protoc-gen-grpc-web
$ chmod +x /usr/local/bin/protoc-gen-grpc-web
```

After they are installed, run the following command to generate `_pb` files:

```sh
protoc -I=. helloworld.proto \
  --js_out=import_style=commonjs:.
```

After the command runs successfully, you should now see two new files generated
in the current directory:

 - `helloworld_pb.js`
 - `helloworld_grpc_web_pb.js`
 
These are also the 2 files that our `client.js` file imported earlier in the
example.

## Compile the Client JavaScript Code

Next, we need to compile the client side JavaScript code into something that
can be consumed by the browser.

```sh
$ npm install
$ npx webpack client.js
```

Here we use `webpack` and give it an entry point `client.js`. You can also use
`browserify` or other similar tools. This will resolve all the `require()`
statements and produce a `./dist/main.js` file that can be embedded in our
`index.html` file.

## Run the Example!

We are ready to run the Hello World example. The following set of commands will
run the 3 processes all in the background.

 1. Run the NodeJS gRPC Service. This listens at port `:9090`.

 ```sh
 $ node server.js &
 ```

 2. Run the Envoy proxy. The `envoy.yaml` file configures Envoy to listen to
 browser requests at port `:8080`, and forward them to port `:9090` (see
 above).

 ```sh
 $ docker build -t helloworld/envoy -f ./envoy.Dockerfile .
 $ docker run -d -p 8080:8080 -p 9901:9901 --network=host helloworld/envoy
 ```

NOTE: As per [this issue](https://github.com/grpc/grpc-web/issues/436):
if you are running Docker on Mac/Windows, remove the `--network=host` option:

 ```sh
 ...
 $ docker run -d -p 8080:8080 -p 9901:9901 helloworld/envoy
 ```

 3. Run the simple Web Server. This hosts the static file `index.html` and
 `dist/main.js` we generated earlier.

 ```sh
 $ python2 -m SimpleHTTPServer 8081 &
 ```

 or for Python 3.x

 ```sh
 $ python3 -m http.server 8081 &
 ```

When these are all ready, you can open a browser tab and navigate to

```
localhost:8081
```

Open up the developer console and you should see the following printed out:

```
Hello! World
```

You can also browse to the envoy admin via
```
localhost:9901
```
