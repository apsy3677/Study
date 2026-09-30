# E1: EDA, FPGA & Vivado Primer (vocabulary a Vivado interviewer expects)

> You already know formal verification (VC Formal/DPV) deeply. This file fills the **implementation-side** vocabulary: synthesis → place → route → timing, and FPGA architecture, so you can talk to a Vivado team fluently.
> Don't over-claim. Say *"I haven't built a placer, but here's how I understand it and how my C++/perf/formal experience transfers."*

---

## 1. The flow in one picture
```
 ASIC:  RTL (Verilog/VHDL/SV) ─► Synthesis ─► Gate netlist ─► Floorplan ─► Placement ─► CTS ─► Routing ─► STA/Signoff ─► GDSII
 FPGA:  RTL / HLS C++ ─► Synthesis ─► LUT/FF/DSP/BRAM netlist ─► opt ─► Place ─► phys_opt ─► Route ─► STA ─► Bitstream
                           ▲                                                                          │
      Formal/equivalence checking (RTL ≡ netlist) · simulation · lint/CDC ◄────────────────────────── timing closure loop
```

## 2. FPGA architecture (AMD/Xilinx UltraScale+ terms)
| Resource | What it is | Why software cares |
|---|---|---|
| **LUT6** | a 6-input lookup table = any 6-input boolean function (can act as two LUT5s sharing inputs) | technology mapping targets K=6 cuts |
| **FF** | flip-flops (registers) | retiming, packing with LUTs, control sets (clock/enable/reset) must match to pack together |
| **CLB / slice** | UltraScale+ CLB = 1 slice = **8 LUTs + 16 FFs + CARRY8** + wide muxes (F7/F8/F9) | packing/clustering legality rules |
| **SLICEM** vs SLICEL | SLICEM LUTs can also be distributed RAM / shift registers (SRL) | inference choices in synthesis |
| **DSP** (DSP48E2) | hard multiply-accumulate block (27×18 multiplier, pre-adder, 48-bit accumulator) | inference; pipelining registers inside the DSP |
| **BRAM / URAM** | 36 Kb block RAM (splittable into 2×18 Kb) / 288 Kb UltraRAM | memory inference, column placement |
| **Routing fabric** | wires of various lengths + **switch matrices** (programmable interconnect points, PIPs) | the routing-resource graph; FPGA routing = choosing PIPs |
| **Clocking** | global clock buffers (BUFG), clock regions, MMCM/PLL | clock placement/routing is special and constrained |
| **I/O, GTs** | I/O banks with voltage standards; high-speed serial transceivers | pin planning |
| **SLR** (SSI technology) | big devices stack several dies (**Super Logic Regions**) on an interposer; crossing uses **SLLs** (super long lines) | partitioning to minimize SLR crossings is a placement problem |
| **Versal** | adds AI Engines, a hardened NoC, Arm processing system + programmable logic | more heterogeneous compilation flows |

**ASIC vs FPGA implementation:** ASIC places standard cells anywhere (continuous-ish rows) and routes on metal layers. FPGA places onto **fixed, discrete sites** and routes through **fixed** programmable wires. The FPGA problem is more "assignment/graph search on a fixed resource graph". Routability and timing are tightly coupled because of the fixed wire lengths.

## 3. Vivado flow & commands (Tcl, non-project mode)
```tcl
read_verilog top.v ; read_xdc top.xdc
synth_design -top top -part xcvu9p-flga2104-2-i
opt_design                      ;# logic optimization: const prop, sweep, remap, BRAM power opt
place_design                    ;# global → detailed placement
phys_opt_design                 ;# physical opt: replication, retiming, rewiring based on timing
route_design
report_timing_summary          ;# WNS / TNS / WHS / THS
report_utilization ; report_qor_suggestions ; report_design_analysis -congestion
write_checkpoint post_route.dcp ;# design checkpoint = save/restore of the full in-memory design
write_bitstream top.bit
```
- **DCP (design checkpoint)** ≈ your save/restore work: a serialized in-memory design at a stage. Incremental implementation reuses a reference DCP's placement and routing.
- **XDC** = SDC-based constraints: `create_clock`, `set_input_delay`/`set_output_delay`, `set_false_path`, `set_multicycle_path`, `set_max_delay`, plus physical constraints (`LOC`, `Pblock` floorplanning).
- **Vitis HLS**: C/C++ → RTL. (Bridge: your DPV experience verifies C++ models against RTL, which is exactly the trust problem HLS flows have. Mention it as a *why-me* point.)
- **QoR** (quality of results) = Fmax/WNS, utilization, power, routability, **plus runtime & memory** of the tool itself.

## 4. Synthesis in 8 bullets
1. **Parse & elaborate** HDL → a generic RTL netlist (operators, muxes, registers), with parameters resolved and hierarchy built.
2. **RTL optimizations**: constant propagation, dead-logic sweep, resource sharing, FSM extraction and re-encoding (one-hot/binary/gray).
3. **Inference**: recognize RAMs, ROMs, shift registers, DSP patterns (`a*b+c`).
4. **Logic optimization** on a technology-independent representation (e.g. an **AIG**): structural hashing, rewriting, balancing (depth reduction).
5. **Technology mapping**: cover the logic with **K-input LUTs** via **cut enumeration** (depth-optimal: FlowMap; then area recovery).
6. **Retiming**: move registers across combinational logic to balance path delays.
7. **Hierarchy**: flatten for optimization vs keep for debug/incremental (`-flatten_hierarchy rebuilt`).
8. **Output**: a netlist of device primitives (LUT, FDRE, CARRY8, DSP48E2, RAMB36…).

## 5. Static Timing Analysis (STA) essentials ★★
- **Timing path**: startpoint (input port or clock pin of a FF) → combinational logic → endpoint (FF D-pin or output port).
- **Setup check (max delay):** data must arrive **before** the capturing edge minus setup time.
  `slack_setup = (T_clk + capture_clock_arrival − t_setup − uncertainty) − data_arrival`
- **Hold check (min delay):** data must not change **too soon** after the capturing edge.
  `slack_hold = data_arrival − (capture_clock_arrival + t_hold)`
- **Slack < 0 → violation.** **WNS** = worst negative slack; **TNS** = sum of the negative slacks over the endpoints; WHS/THS for hold.
- **Fmax ≈ 1 / (T − WNS)** (for a single-clock design).
- **Clock skew** = the difference in clock arrival between launch and capture; positive skew helps setup and hurts hold.
- **Exceptions**: false paths (never exercised), multicycle paths (allowed N cycles), clock domain crossings (need synchronizers; timing is often cut with `set_clock_groups -asynchronous`).
- **Delay models**: cell delay from lookup tables (**NLDM**: delay/slew = f(input slew, output load); you did NLDM work!), wire delay (Elmore / RC). FPGA: characterized delays for the routing resources.
- The **timing graph** is a DAG (registers break the cycles) → arrival times propagate by **topological order** (see P08 Card E and E2).

## 6. Formal verification (your home turf: use it as a bridge)
- **Equivalence checking** (RTL vs synthesized netlist): match state points, prove the combinational cones equal with **SAT/BDD**. Guards synthesis optimizations.
- **Model/property checking** (SVA assertions): bounded model checking (BMC, unrolled + SAT), k-induction, IC3/PDR.
- **Datapath validation (DPV)**: C/C++ reference vs RTL, transaction-level equivalence. Hard parts: multipliers (SAT-hard) → case splits, partitioning (your partitioning/multiprocessing work).
- **Why it matters to Vivado:** every optimization (opt_design, phys_opt retiming/replication) must preserve function, and formal/equivalence checking is how you prove it at scale.

## 7. Why EDA software is hard (a great "what interests you" answer)
1. **Scale**: 10⁷–10⁸ instances, 10⁹ routing-graph edges on large FPGAs → memory layout *is* performance.
2. **NP-hard cores** (partitioning, placement, routing, mapping) → heuristics with QoR/runtime trade-offs.
3. **Determinism** across runs, thread counts and platforms (customers bisect with it).
4. **Incrementality**: small ECO → don't redo hours of work.
5. **Long-running and memory-hungry**: a 1% runtime regression across a benchmark suite matters. QoR regressions need statistical gating.
6. **Backward compatibility**: Tcl APIs, checkpoints, constraints stay stable across releases.

## 8. Glossary (1 line each)
**Netlist**: cells (instances of library masters) connected by nets via pins/ports · **Hypergraph**: a net connects many pins → a hyperedge · **Fanout**: the number of sinks of a net · **HPWL**: half-perimeter wirelength of a net's bounding box · **Congestion**: routing demand > capacity in a region · **Utilization**: used/available sites · **Packing**: clustering LUTs/FFs into slices/CLBs · **Legalization**: snapping placement to legal sites without overlap · **ECO**: engineering change order, a small post-implementation change · **Pblock**: a floorplan region constraint · **Control set**: {clock, clock enable, set/reset} of a FF · **CDC**: clock domain crossing · **LEF/DEF**: ASIC physical library/design exchange formats · **Liberty (.lib)**: cell timing/power models · **SDC/XDC**: timing constraints · **QoR**: quality of results · **Signoff**: final verification before tape-out/bitstream.

---

## Self-test
1. Walk the Vivado flow command by command and say what each stage optimizes.
2. What is in an UltraScale+ CLB? Why do control sets matter for packing?
3. Setup vs hold: write both slack equations. Which one does clock skew hurt?
4. WNS vs TNS: which one tells you "how many paths are broken"?
5. What is an SLR, and why is SLR crossing a placement concern?
6. How does equivalence checking protect synthesis and phys_opt optimizations?
7. Name 4 reasons EDA software is hard to build.
