import React from 'react'
import './Cell.css'

function Cell(props) {
  const { type } = props
    
  return (
    <div className="Cell">
      {type}
    </div>
  )
  
}

export default Cell