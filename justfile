#!/usr/bin/env just --justfile

build:
    cmake -B build -S .
    cmake --build build
    uv sync

release:
    uv sync

test:
    source .venv/bin/activate
    pytest
