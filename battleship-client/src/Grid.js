import React from 'react'
import Cell from './Cell'
import './Grid.css'

const numbers = [11,33,55,66]
const prices = numbers.map((n) => `$${n.toFixed(2)}`)
// ['$11.00', '$33.00', ...]

function Grid(props) {
  const { cells } = props

  const array = cells.map((cell) => <Cell type={cell.type} />)

  return (
    <div className="Grid">
      {array}
    </div>
  )
}

export default Grid