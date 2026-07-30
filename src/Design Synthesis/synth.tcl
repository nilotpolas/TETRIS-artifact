# Yosys synthesis script for COMPRESS.

# Environment variables
# - SYNTH_SRCS: space-separated list of source files
# - VDEFINES: list of verilog define
# - VINCLUDE: includes directory
# - SYNTH_TOP: name of top module
# - SYNTH_LIB: .lib file
# - RESDIR: directory to store results

# set srcs [list {*}$::env(SYNTH_SRCS)]
# set defines [list {*}$::env(VDEFINES)]
# set include $::env(VINCLUDE)
# set top $::env(SYNTH_TOP)
# set lib $::env(SYNTH_LIB)
set lib ./nangate45-pdk/stdcells.lib
# set resdir $::env(RESDIR)

# foreach file $srcs {
#     yosys read_verilog -I$include {*}$defines $file
# }
yosys read_verilog sbox.v
# yosys hierarchy -check -top $top
yosys hierarchy -check -top sbox
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

# yosys write_verilog $resdir/design.v
# yosys tee -o $resdir/area.json stat -liberty $lib -json
# yosys write_json $resdir/design.json
yosys write_verilog sbox_yosys.v
yosys tee -o area.json stat -liberty $lib -json
yosys write_json sbox_yosys.json