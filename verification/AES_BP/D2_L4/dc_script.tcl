remove_design -all

set nang45 /home/c_karfa/nilotpola/NangateOpenCellLibrary/NangateOpenCellLibrary.db

set target_library $nang45
set link_library "* $nang45"

define_design_lib WORK -path .

analyze -library WORK -autoread {sbox.v}

elaborate sbox
current_design sbox
link


create_clock -name clk -period 10 clk


# VERICA compatible cells only

set_dont_use [get_lib_cells NangateOpenCellLibrary/FA*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/HA*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/AOI*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/OAI*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/MUX*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/CLKBUF*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/OR3*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/OR4*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/OR5*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/NOR3*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/NOR4*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/NOR5*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/XNOR3*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/XNOR4*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/XNOR5*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/XOR3*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/XOR4*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/XOR5*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/AND3*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/AND4*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/AND5*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/NAND3*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/NAND4*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/NAND5*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/BUF*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/DFFR*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/DFFS*]
set_dont_use [get_lib_cells NangateOpenCellLibrary/SDFF*]


compile -map_effort medium -area_effort medium

compile_ultra -no_autoungroup


ungroup -all -flatten


change_names -rules verilog -hierarchy


set verilogout_single_bit true
set verilogout_show_unconnected_pins false


write -format verilog -output aes_bp_d2_l4_verica.v