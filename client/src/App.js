import React, { Component } from 'react';
import Grid from './ui/components/Grid';
import './App.css';

import { echoServiceEndpointRPC } from './service/EchoService.js';

let output = echoServiceEndpointRPC().then(()=>{}).catch(()=>{})

class Square {
  squares = 0;
  constructor(type) {
    Square.squares += 1;
    this.key = Square.squares
    this.type = type
  }
}

class App extends Component {
  constructor() {
    super()
    const cells = []

    for (let i = 0; i < 100; i += 1) {
      const type = Math.random() < 0.8 ? 0 : 1
      const square = new Square(type)
      cells.push(square)
    }

    this.state = {
      cells
    }
  }

  render() {
    return (
      <div className="App">
        {/* add exported function? */}
        
        
      </div>
    );
  }
}

export default App;