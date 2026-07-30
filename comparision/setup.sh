#!/bin/bash
# One-time setup for the COMPRESS comparison sub-package
set -e
cd "$(dirname "$0")/compress_source"
ln -sf "../../../src/Design Synthesis/nangate45-pdk" synthesis/nangate45-pdk
echo "Setup complete."