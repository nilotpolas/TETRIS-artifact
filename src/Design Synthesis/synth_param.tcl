# Parameterized Yosys synthesis script.
# All paths are passed via environment variables so this file never needs editing.
#
# Required env vars:
#   SYNTH_SRC     – absolute path to the input .v file
#   SYNTH_TOP     – top module name (e.g. sbox)
#   SYNTH_RESDIR  – absolute path to the output directory (must already exist)
#   SYNTH_LIB     – absolute path to the .lib file

set src    $::env(SYNTH_SRC)
set top    $::env(SYNTH_TOP)
set resdir $::env(SYNTH_RESDIR)
set lib    $::env(SYNTH_LIB)

yosys read_verilog $src
yosys hierarchy -check -top $top
yosys proc
yosys opt
yosys fsm
yosys opt
yosys memory
yosys opt
yosys techmap
yosys opt

yosys dfflibmap -liberty $lib
yosys abc -liberty $lib
yosys clean

yosys write_verilog  $resdir/design_synth.v
yosys tee -o         $resdir/area.json  stat -liberty $lib -json
yosys write_json     $resdir/design_synth.json
