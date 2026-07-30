# =============================================================================
# Makefile — DSE Framework batch experiments
# =============================================================================
#
# Targets:
#   make all           Run MRLC + MLRC + MARC for all designs & constraints,
#                      then print and save the results tables.
#                      (synthesis skipped by default — DSE only, fast)
#
#   make mrlc          Run only MRLC experiments
#   make mlrc          Run only MLRC experiments
#   make marc          Run only MARC experiments
#
#   make tables        Regenerate tables from cached JSON (no re-runs)
#
#   make all-synth     Same as 'all' but with Yosys synthesis (slow)
#   make mrlc-synth    MRLC with synthesis
#   make mlrc-synth    MLRC with synthesis
#   make marc-synth    MARC with synthesis
#
#   make clean-results Remove all Results/ subdirectories
#   make help          Show this help
#
# Output:
#   Results/all_results.txt   — combined table of all runs
#
# =============================================================================

PYTHON     := python3
RUNNER     := run_all_experiments.py
OUTPUT     := Results/all_results.txt

.PHONY: all mrlc mlrc marc tables \
        all-synth mrlc-synth mlrc-synth marc-synth \
        clean-results help

# ── Default target ─────────────────────────────────────────────────────────────
all:
	@echo ""
	@echo "══════════════════════════════════════════════════════════════════"
	@echo "  DSE Framework — Running ALL experiments (MRLC + MLRC + MARC)"
	@echo "  Designs : Boyer-Peralta AES S-box"
	@echo "            Canright AES S-box"
	@echo "            SKINNY S-box"
	@echo "  Synthesis : SKIPPED (use 'make all-synth' for full area)"
	@echo "══════════════════════════════════════════════════════════════════"
	@echo ""
	$(PYTHON) $(RUNNER) --algo all --output $(OUTPUT)

# ── Algorithm-specific targets ─────────────────────────────────────────────────
mrlc:
	@echo ""
	@echo "══════════════ MRLC — All designs & orders ══════════════"
	$(PYTHON) $(RUNNER) --algo mrlc --output $(OUTPUT)

mlrc:
	@echo ""
	@echo "══════════════ MLRC — All designs & orders ══════════════"
	$(PYTHON) $(RUNNER) --algo mlrc --output $(OUTPUT)

marc:
	@echo ""
	@echo "══════════════ MARC — All designs & orders ══════════════"
	$(PYTHON) $(RUNNER) --algo marc --output $(OUTPUT)

# ── Tables only (read cached JSON, no re-runs) ─────────────────────────────────
tables:
	@echo ""
	@echo "══════════════ Regenerating tables from cached JSON ══════════════"
	$(PYTHON) $(RUNNER) --tables-only --output $(OUTPUT)

# ── With Yosys synthesis (slow) ────────────────────────────────────────────────
all-synth:
	@echo ""
	@echo "══════════════════════════════════════════════════════════════════"
	@echo "  DSE Framework — ALL experiments WITH Yosys synthesis"
	@echo "  Warning: this can take 30+ minutes"
	@echo "══════════════════════════════════════════════════════════════════"
	@echo ""
	$(PYTHON) $(RUNNER) --algo all --with-synth --output $(OUTPUT)

mrlc-synth:
	$(PYTHON) $(RUNNER) --algo mrlc --with-synth --output $(OUTPUT)

mlrc-synth:
	$(PYTHON) $(RUNNER) --algo mlrc --with-synth --output $(OUTPUT)

marc-synth:
	$(PYTHON) $(RUNNER) --algo marc --with-synth --output $(OUTPUT)

# ── Clean ──────────────────────────────────────────────────────────────────────
clean-results:
	@echo "Removing Results/ experiment subdirectories …"
	@find Results/ -mindepth 2 -name "results.json" -delete 2>/dev/null || true
	@find Results/ -mindepth 2 -type d -empty -delete 2>/dev/null || true
	@echo "Done."

# ── Help ───────────────────────────────────────────────────────────────────────
help:
	@echo ""
	@echo "Usage: make [target]"
	@echo ""
	@echo "Targets:"
	@echo "  all           Run MRLC+MLRC+MARC for all configs  (no synthesis)"
	@echo "  mrlc          Run MRLC only                       (no synthesis)"
	@echo "  mlrc          Run MLRC only                       (no synthesis)"
	@echo "  marc          Run MARC only                       (no synthesis)"
	@echo "  tables        Regenerate tables from cached JSON  (no re-runs)"
	@echo "  all-synth     Run everything WITH Yosys synthesis (slow)"
	@echo "  mrlc-synth    MRLC with synthesis"
	@echo "  mlrc-synth    MLRC with synthesis"
	@echo "  marc-synth    MARC with synthesis"
	@echo "  clean-results Remove all results.json files"
	@echo ""
	@echo "Output file: $(OUTPUT)"
	@echo ""
