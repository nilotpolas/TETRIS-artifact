# VERICA Test Files

## File Structure

The test suite contains three cipher implementations organized by masking order (D) and logic levels (L).

## File Descriptions

Each test case directory contains:

- `*.v`: Verilog gate-level netlist of the circuit synthesized to logic gates
- `*.json`: VERICA configuration file specifying verification parameters
- `annotations.json`: Input/output tagging file that labels wires as clocks, refresh signals, and share information
- `dc_input.v`: Pre-synthesis Verilog behavioral/RTL description
- `dc_output.v`: Post-synthesis netlist from Design Compiler
- `dc_script.tcl`: Synopsys Design Compiler synthesis script
- `verica.log`: Output log from previous VERICA verification runs

## How to Run VERICA

### Basic Usage

Navigate to the VERICA root directory and run:

```bash
bin/release/verica -c AES_BP/D2_L4/aes_bp_d2_l4.json
```

Replace the path with any of the available test cases:

```bash
bin/release/verica -c AES_Canrights/D2_L4/aes_canrights_d2_l4.json
bin/release/verica -c SKINNY_NOR/D3_L4/skinny_nor_d3_l4.json
```

### Running with Output Logging

To save verification results to a log file:

```bash
bin/release/verica -c AES_BP/D2_L4/aes_bp_d2_l4.json > AES_BP/D2_L4/verica.log 2>&1
```


## Masking Orders

- D2: 2-share masking, verifies order 1 security
- D3: 3-share masking, verifies order 2 security
- D4: 4-share masking, verifies order 3 security
- D5: 5-share masking, verifies order 4 security

Higher masking orders require more computational resources.

## Troubleshooting

### Segmentation Fault Error

If VERICA crashes with a segmentation fault:

1. Disable glitches in the JSON configuration:
```json
   "model": {"glitches": false}
```
### File Not Found Error

Ensure you are running VERICA from the VERICA root directory, not from a subdirectory:

```bash
pwd
# Should show: /path/to/VERICA
```

Verify file paths in the JSON configuration are correct relative to the VERICA root.

## Verification Strategy

Start with simpler test cases before progressing to complex ones:

1. Run AES_BP/D2_L4 first
2. Progress to AES_BP/D3_L6
3. Then AES_BP/D4_L6
4. Compare with AES_Canrights implementations
5. Compare with SKINNY_NOR implementations

## Support

For issues with the VERICA framework, contact: the VERICA developers https://github.com/Chair-for-Security-Engineering/VERICA

