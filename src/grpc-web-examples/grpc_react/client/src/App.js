import React from 'react';
import logo from './logo.svg';
import './App.css';

const {EchoServiceClient} = require('./generated/echo_grpc_web_pb.js');
const {EchoRequest} = require('./generated/echo_pb.js');
 
const client = new EchoServiceClient('localhost:8080');
 
const request = new EchoRequest();
request.setMessage('Hello World!');
 
const metadata = {'custom-header-1': 'value1'};
 
client.echo(request, metadata, (err, response) => {
  console.log("Testing")
});

// function App() {
//   return (
//     <div className="App">
//       <header className="App-header">
//         <img src={logo} className="App-logo" alt="logo" />
//         <p>
//           Edit <code>src/App.js</code> and save to reload.
//         </p>
//         <a
//           className="App-link"
//           href="https://reactjs.org"
//           target="_blank"
//           rel="noopener noreferrer"
//         >
//           Learn React
//         </a>
//       </header>
//     </div>
//   );
// }

// const echoapp = new App();
// const response = await echoapp.Echo("Yo")
// response.getMessage()

export default App;
