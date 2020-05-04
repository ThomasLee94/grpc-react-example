# Installs & builds

run `npm run generate`
run `npm run setup`

This step downloads the necessary pre-requisites, and serves as the base docker image for the subsequent docker images.
```
$ docker build -t grpcweb/common \
  -f docker/common/Dockerfile .
```

------------

## Run gRPC backend

`bazel run :<server>`
```
$ docker build -t grpcweb/cpp_grpc_server \
  -f docker/cpp_grpc_server/Dockerfile .
$ docker run -d -p 9090:9090 --name cpp_grpc_server grpcweb/cpp_grpc_server
```
-------------

## Run Envoy Proxy

This step runs the Envoy proxy, and listens on port 8080. Any gRPC-Web browser requests will be forwarded to port 9090.
```
$ docker build -t grpcweb/envoy \
  -f docker/envoy/Dockerfile .
$ docker run -d -p 8080:8080 --link cpp_grpc_server:cpp_grpc_server grpcweb/envoy
```
--------------

## Serve static JS/HTML contents

This steps compiles the front-end gRPC-Web client into a static .JS file, and we use a simple server to serve up the JS/HTML static contents.

```
$ docker build -t grpcweb/commonjs_client  \
  -f docker/commonjs_client/Dockerfile .
$ docker run -d -p 8081:8081 grpcweb/commonjs-client
```

--------------
## Run the example from your browser

Finally, open a browser tab, and inspect

http://localhost:8081/echohtml.html

<!-- 
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
 $ bazel run :<server_name>
 ```

 2. Run the Envoy proxy. The `envoy.yaml` file configures Envoy to listen to
 browser requests at port `:8080`, and forward them to port `:9090` (see
 above).

 ```sh
 $ docker build -t helloworld/envoy -f ./docker/envoy/envoy.Dockerfile .
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
``` -->

To kill docker container
```
docker kill $(docker ps -q)
```
