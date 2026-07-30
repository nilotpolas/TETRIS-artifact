#!/bin/bash
# Quick setup and run script for equivalence testbench

set -e  # Exit on error

echo "════════════════════════════════════════════════════════════════"
echo "MASKED S-BOX EQUIVALENCE TESTBENCH - QUICK SETUP"
echo "════════════════════════════════════════════════════════════════"
echo ""

# Get the directory where this script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR"

echo "[1/3] Checking prerequisites..."

# Check if Python 3 is available
if ! command -v python3 &> /dev/null; then
    echo "[✗] ERROR: python3 not found!"
    exit 1
fi
echo "[✓] Python 3 found"

# Check if gcc is available
if ! command -v gcc &> /dev/null; then
    echo "[✗] ERROR: gcc compiler not found!"
    exit 1
fi
echo "[✓] GCC compiler found"

# Check if input files exist
if [ ! -f "skinny_sbox_nor.c" ]; then
    echo "[✗] ERROR: skinny_sbox_nor.c not found!"
    exit 1
fi
echo "[✓] Unmasked S-box found"

if [ ! -f "/home/tapish08/Desktop/DSE-Framework/TestFiles/share_output/output.c" ]; then
    echo "[✗] ERROR: Masked S-box (output.c) not found!"
    exit 1
fi
echo "[✓] Masked S-box found"

echo ""
echo "[2/3] Generating and compiling testbench..."
python3 equivalence_testbench.py
if [ $? -ne 0 ]; then
    echo "[✗] Testbench generation/compilation failed!"
    exit 1
fi

echo ""
echo "[3/3] Results above ☝"
echo ""

# Check result
if [ -f "equivalence_test" ]; then
    echo "════════════════════════════════════════════════════════════════"
    echo "[✓] SETUP COMPLETE - Testbench ready!"
    echo "════════════════════════════════════════════════════════════════"
    exit 0
else
    echo "[✗] ERROR: Executable not created!"
    exit 1
fi
