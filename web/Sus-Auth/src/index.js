const express = require('express');
const fs = require('fs');
const path = require('path');
const app = express();
const port = 1337;

const flag = fs.readFileSync('/flag.txt', 'utf8');

app.use(express.json());

//For invalid json errors
app.use((err, req, res, next) => {
    if (err instanceof SyntaxError && err.status === 400 && 'body' in err) {
      console.error('Bad JSON received:', err);
      return res.status(400).send({ error: 'Malformed JSON payload' });
    }
    next();
  });

const generatePass = size => {
    let hex = '';
    for (let i = 0; i < size; i++) {
        hex += Math.floor(Math.random() * 16).toString(16);
    }
    return hex;
};

const users = {
    'PsychoTherapist': generatePass(16),
};

function verifyCredentials(req, res, next) {
    const { username, password } = req.body;

    if (!username || !password) {
        return res.status(400).send('Missing username or password.');
    }
    if (typeof username !== 'string' || typeof password !== 'string') {
        return res.status(400).send('Invalid credential format.');
    }

    if (users[username] && users[username] == password) {
        return next();
    } else {
        return res.status(401).send('Unauthorized');
    }
}

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'index.html'));
  });

app.post('/admin', verifyCredentials, (req, res) => {
    res.send(flag);
});

app.listen(port, '0.0.0.0', () => {
    console.log(`Server is running on http://localhost:${port}`);
});
