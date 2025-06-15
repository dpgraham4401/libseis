#!/usr/bin/env just --justfile

init:
    #!/usr/bin/env bash
    uv venv --allow-existing
    uv sync

build: init
    #!/usr/bin/env bash
    source .venv/bin/activate
    cmake -B build -S .
    cmake --build build

test: init
    #!/usr/bin/env bash
    source .venv/bin/activate
    pytest
    cd build
    ctest --output-on-failure
