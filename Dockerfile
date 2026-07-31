FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# --- System dependencies -------------------------------------------------
# build-essential..zlib1g-dev  : Yosys build requirements
# iverilog, gcc                : RTL simulation + C-level verification
# graphviz                     : pydot/graphviz Python bindings need the `dot` binary
RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential clang bison flex \
        libreadline-dev gawk tcl-dev libffi-dev git \
        pkg-config python3 python3-pip python3-venv \
        libboost-system-dev libboost-python-dev libboost-filesystem-dev \
        zlib1g-dev graphviz iverilog ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# --- Yosys 0.33 (exact version used for the paper's area numbers) --------
RUN git clone --depth 1 --branch yosys-0.33 \
        https://github.com/YosysHQ/yosys.git /tmp/yosys \
    && cd /tmp/yosys \
    && make config-gcc \
    && make -j"$(nproc)" \
    && make install \
    && cd / && rm -rf /tmp/yosys


RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential clang bison flex \
        libreadline-dev gawk tcl-dev libffi-dev git \
        pkg-config python3 python3-pip python3-venv python-is-python3 \
        libboost-system-dev libboost-python-dev libboost-filesystem-dev \
        zlib1g-dev graphviz iverilog ca-certificates \
    && rm -rf /var/lib/apt/lists/*
# --- Python dependencies (cached separately from the source tree) --------
WORKDIR /artifact
COPY src/requirement.txt /artifact/src/requirement.txt
RUN pip3 install --no-cache-dir -r /artifact/src/requirement.txt

# --- Artifact source -----------------------------------------------------
COPY . /artifact

# Scripts resolve ./MaskedHLS_LP/... relative to CWD, so src/ is the workdir
WORKDIR /artifact/src

CMD ["/bin/bash"]