import { Login } from "./components/Login";
import { Home } from "./components/Home";
import React, { useState } from "react"


export const App = () => {
  const [username, setUsername] = useState("")
  
  return username ? 
    (<Home username={username} /> )
    : 
    ((<Login onSubmit={setUsername} />))
}
