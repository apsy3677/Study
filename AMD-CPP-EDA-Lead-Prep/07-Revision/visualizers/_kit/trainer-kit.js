// Trainer kit: the engine every pattern trainer shares. build.sh inlines this file into each
// trainer, so every generated .html stands alone. Each page keeps its own algorithm, events
// and drawing; the kit only does stepping, playback, prediction plumbing, code, log and self-test.
const TK = (() => {
  const $ = (id) => document.getElementById(id);
  const esc = (s) => String(s).replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;");
  const fmtSet = (a) => (a.length ? "{" + a.slice().sort((p, q) => p - q).join(", ") + "}" : "none");
  const r1 = (x) => Math.round(x * 10) / 10;

  // Step / Back / Play / Reset over a list of recorded events, plus the arrow keys.
  // opts: count() → number of events, render(), pending() → a prediction is waiting,
  //       check() → grade it, rebuild() → re-run the algorithm, delay in ms.
  function player(opts) {
    const P = { k: 0, timer: null };
    const stop = () => { if (P.timer) { clearInterval(P.timer); P.timer = null; } };
    P.step = () => {
      if (opts.pending()) { opts.check(); return; }
      if (P.k < opts.count() - 1) P.k++; else stop();
      opts.render();
    };
    P.back = () => { if (P.k > 0) { P.k--; opts.render(); } };
    P.togglePlay = () => {
      if (P.timer) { stop(); opts.render(); return; }
      if (P.k >= opts.count() - 1) P.k = 0;
      P.timer = setInterval(() => {
        if (P.k >= opts.count() - 1 || opts.pending()) { stop(); opts.render(); }   // pause for a prediction
        else P.step();
      }, opts.delay || 900);
      opts.render();
    };
    P.reset = () => { stop(); opts.rebuild(); P.k = 0; opts.render(); };
    P.stop = stop;
    // Keep the shared buttons in sync. label = text for the Step button while a prediction waits.
    P.sync = (pending, label, stepDisabled) => {
      $("counter").textContent = `step ${P.k + 1} of ${opts.count()}`;
      $("back").disabled = P.k === 0;
      $("step").textContent = pending ? label || "Check" : "Step";
      $("step").disabled = stepDisabled !== undefined ? stepDisabled : !pending && P.k >= opts.count() - 1;
      $("play").textContent = P.timer ? "Pause" : "Play";
    };
    $("step").addEventListener("click", P.step);
    $("back").addEventListener("click", P.back);
    $("play").addEventListener("click", P.togglePlay);
    $("reset").addEventListener("click", P.reset);
    document.addEventListener("keydown", (ev) => {
      const tag = (ev.target.tagName || "").toLowerCase();
      if (tag === "input" || tag === "select" || tag === "textarea") return;
      if (tag === "button" && ev.key === " ") return;   // the button's own click handles Space
      if (ev.key === "ArrowRight" || ev.key === " ") { ev.preventDefault(); P.step(); }
      else if (ev.key === "ArrowLeft") { ev.preventDefault(); P.back(); }
    });
    return P;
  }

  // Live code: highlight the given line indexes; lines that mention BUG are tinted.
  function renderCode(el, lines, hl) {
    const on = new Set(hl || []);
    el.innerHTML = lines.map((ln, i) => {
      const cls = [];
      if (on.has(i)) cls.push("hl");
      if (/BUG/.test(ln)) cls.push("bug");
      return `<span class="${cls.join(" ")}">${esc(ln)}</span>`;
    }).join("");
  }

  // Event log, newest first.
  function renderLog(el, lines, max) {
    el.innerHTML = lines.slice().reverse().slice(0, max || 16).map((l) => `<li>${esc(l)}</li>`).join("");
    el.start = lines.length;
  }

  function scoreText(score, predicting, tip) {
    return predicting || score.total ? `Predictions: ${score.ok} of ${score.total} right` : tip;
  }

  // SVG arrowheads: pairs of [id, css color]. Use as marker-end="url(#id)".
  function markers(list) {
    return "<defs>" + list.map(([id, color]) =>
      `<marker id="${id}" viewBox="0 0 10 10" refX="8.5" refY="5" markerUnits="userSpaceOnUse" markerWidth="11" markerHeight="11" orient="auto-start-reverse"><path d="M0,0 L10,5 L0,10 z" style="fill: ${color}"></path></marker>`).join("") + "</defs>";
  }

  // Open the page with #selftest to run the page's own checks; results appear at the top.
  // fn() returns [[label, passed, detail?], ...].
  function selftest(fn) {
    if (location.hash !== "#selftest") return;
    const errors = [];
    window.addEventListener("error", (e) => errors.push(e.message));
    setTimeout(() => {
      let results = [];
      try { results = fn() || []; } catch (e) { results.push(["self-test threw: " + e.message, false, (e.stack || "").split("\n")[1]]); }
      for (const m of errors) results.push(["window error: " + m, false]);
      const ok = results.filter((r) => r[1]).length;
      const box = document.createElement("section");
      box.className = "panel selftest";
      box.innerHTML = `<h2>Self-test: ${ok} / ${results.length} passed</h2><ol>${results
        .map(([label, pass, detail]) => `<li class="${pass ? "ok" : "bad"}">${pass ? "✓" : "✗"} ${esc(label)}${detail !== undefined && detail !== "" ? " · " + esc(detail) : ""}</li>`)
        .join("")}</ol>`;
      document.querySelector(".wrap").prepend(box);
    }, 300);
  }

  return { $, esc, fmtSet, r1, player, renderCode, renderLog, scoreText, markers, selftest };
})();
