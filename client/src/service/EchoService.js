/*eslint-disabled */
//@ts-nocheck
import { promisify } from 'util';
import {EchoServiceClient} from '../generated/src/echo_grpc_web_pb';
import {EchoRequest, EchoResponse} from '../generated/src/echo_pb'

const client = new EchoServiceClient('http://edge.gloofoo.xyz', null, null);

export async function echoServiceEndpointRPC() {
    const request = new EchoRequest();
    request.setMessage("Testing the echo rpc!");
    console.log('here')

    const call = client.echo(request, {'custom-header-1': 'value1'},
  (err, response) => {
      console.log(err)
    console.log(response.getMessage());
  });
call.on('status', (status) => {
  // ...
});
    
    
    console.log('yeet')
    return 
}

// const client = new EchoServiceClient('localhost:8080');
// const request = new EchoRequest();


// request.setMessage('Hello World!');
    
// const metadata = {'custom-header-1': 'value1'};
    
// client.Echo(request, metadata, (err, response) => {
//     console.log("Testing")
// });
 
// const echoapp = new App();
// const response = await echoapp.Echo("Yo")
// response.getMessage()

// module.exports = {
//     echoServiceEndpointRPC
// }