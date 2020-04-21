import React, { Component } from 'react';
import Grid from './Grid';
import './App.css';

class Square {
  constructor(type) {
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
        <Grid cells={this.state.cells} />
      </div>
    );
  }
}

export default App;
