# NanGate45 PDK

The Nangate 45nm PDK is not included here to avoid duplication — TETRIS
ships the same library. If you need it here, either:

1. Symlink from TETRIS's copy:
   `ln -s ../../../<path-to-tetris-nangate45> nangate45-pdk`

2. Or download from the upstream COMPRESS repo:
   `git clone https://github.com/cassiersg/compress && cp -r compress/synthesis/nangate45-pdk .`
