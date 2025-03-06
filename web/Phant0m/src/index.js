const express = require("express");
const crypto = require("crypto");
const fs = require("fs");
const app = express();

const ACCESS_TOKEN = Symbol("accessToken");
const ADMIN_ID = Symbol.for("adminIdentifier").toString();

app.use(express.json());

app.use((err, req, res, next) => {
  if (err instanceof SyntaxError && err.status === 400 && "body" in err) {
    return res.status(400).send({ error: "Malformed JSON payload" });
  }
  next();
});

const FLAG = fs.readFileSync("/flag.txt", "utf8").trim();

class SecureStore {
  constructor() {
    this.store = new Map();

    const adminCredential = {
      username: "ghost_admin",
      [ACCESS_TOKEN]: crypto.randomBytes(16).toString("hex"),
      clearance: "LEVEL_5",
    };
    this.store.set(adminCredential.username, adminCredential);

    this.internalAuth = function (user, token, options = {}) {
      const storedUser = user && this.store.get(user);
      if (!storedUser) return false;

      if (
        options &&
        options[ADMIN_ID] !== undefined &&
        options[ADMIN_ID] == null
      ) {
        return true;
      }
      return storedUser[ACCESS_TOKEN] == token;
    };
  }

  authenticate(user, token, options) {
    return this.internalAuth.call(this, user, token, options);
  }
}

const secureUserStore = new SecureStore();

app.get("/", (req, res) => {
  res.send(`
    <h1>Phantom Gate Access System</h1>
    <p>Authorized personnel only.</p>
  `);
});

app.post("/auth", (req, res) => {
  const { username, credential, parameters } = req.body || {};

  // Simpler input validation
  if (!username || !credential || typeof username !== "string") {
    return res.status(400).json({ error: "Invalid credentials format" });
  }

  try {
    if (secureUserStore.authenticate(username, credential, parameters)) {
      return res.json({ success: true, flag: FLAG });
    }

    return res.status(401).json({
      error: "Authentication failed",
    });
  } catch (err) {
    console.error("Authentication error:", err.message);
    return res.status(500).json({ error: "Internal authentication error" });
  }
});

// Start server
const PORT = process.env.PORT || 1337;
app.listen(PORT, () => {
  console.log(`Phantom Gate listening on port ${PORT}`);
  console.log(`Visit http://localhost:${PORT}/`);
});
