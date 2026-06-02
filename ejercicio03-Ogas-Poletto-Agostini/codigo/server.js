/**
 * Collaborative Canvas – VPS Backend
 * Endpoint: POST /drawing  → save strokes
 *           GET  /drawing  → retrieve strokes
 *
 * Install: npm install express cors
 * Run:     node server.js
 */

const express = require("express");
const cors    = require("cors");
const fs      = require("fs");
const path    = require("path");

const app  = express();
const PORT = process.env.PORT || 5005;
const DATA_FILE = path.join(__dirname, "drawing_state.json");

// Permite recibir JSON grande porque el dibujo completo viaja como trazos.
app.use(cors());
app.use(express.json({ limit: "50mb" }));

// ── Helpers ───────────────────────────────────────────────────────────────────

function loadState() {
  // Si no hay archivo todavia, el lienzo empieza vacio.
  try {
    if (fs.existsSync(DATA_FILE)) {
      const raw = fs.readFileSync(DATA_FILE, "utf8");
      return JSON.parse(raw);
    }
  } catch (e) {
    console.error("Failed to load state:", e.message);
  }
  return { strokes: [] };
}

function saveState(state) {
  // Persiste todo el estado para que sobreviva a reinicios del servidor.
  fs.writeFileSync(DATA_FILE, JSON.stringify(state), "utf8");
}

// ── GET /drawing ──────────────────────────────────────────────────────────────
// Returns current drawing state (all strokes)

app.get("/drawing", (req, res) => {
  // Devuelve el estado completo para que cada cliente pueda mezclarse.
  const state = loadState();
  res.json(state);
});

// ── POST /drawing ─────────────────────────────────────────────────────────────
// Merges incoming strokes with stored strokes (incremental merge by ID)

app.post("/drawing", (req, res) => {
  const incoming = req.body;

  // Se espera el mismo formato que produce DrawingModel::toJson().
  if (!incoming || !Array.isArray(incoming.strokes)) {
    return res.status(400).json({ error: "Invalid payload: expected { strokes: [] }" });
  }

  const current = loadState();

  // Indice de IDs existentes para no duplicar trazos al guardar varias veces.
  const knownIds = new Set(current.strokes.map(s => s.id));

  let added = 0;
  for (const stroke of incoming.strokes) {
    if (!knownIds.has(stroke.id)) {
      current.strokes.push(stroke);
      knownIds.add(stroke.id);
      added++;
    }
  }

  // Ordena por tiempo para conservar la superposicion visual del dibujo.
  current.strokes.sort((a, b) => (a.timestamp || 0) - (b.timestamp || 0));

  saveState(current);

  console.log(`[${new Date().toISOString()}] Merged ${added} new strokes. Total: ${current.strokes.length}`);

  res.json({ ok: true, total: current.strokes.length, added });
});

// ── DELETE /drawing ───────────────────────────────────────────────────────────
// Clear all strokes (admin use)

app.delete("/drawing", (req, res) => {
  // Endpoint administrativo para reiniciar el lienzo compartido.
  saveState({ strokes: [] });
  res.json({ ok: true, message: "Canvas cleared." });
});

// ── Health ────────────────────────────────────────────────────────────────────

app.get("/health", (req, res) => {
  // Verificacion simple para comprobar que el servidor responde.
  const state = loadState();
  res.json({ status: "ok", strokeCount: state.strokes.length });
});

// ── Start ─────────────────────────────────────────────────────────────────────

app.listen(PORT, () => {
  console.log(`Collaborative Canvas server running on port ${PORT}`);
  console.log(`Endpoints:`);
  console.log(`  GET    /drawing  → fetch all strokes`);
  console.log(`  POST   /drawing  → merge & save strokes`);
  console.log(`  DELETE /drawing  → clear canvas`);
  console.log(`  GET    /health   → server status`);
});
