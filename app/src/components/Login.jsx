import { useState } from 'react';

export function Login({ onSubmit }) {
    const [username, setUsername] = useState('');
    return (
        <>
            <h1>Welcome</h1>
            <p>What is your name</p>
            <form
                onSubmit={(e) => {
                    e.preventDefault();
                    onSubmit(username);
                }}
            >
                <input
                    type="text"
                    value={username}
                    placeholder="username"
                    onChange={(e) => setUsername(e.target.value)}
                />
                <button type="submit">Submit</button>
            </form>
        </>
    )
}