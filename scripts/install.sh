#!/bin/sh
set -e

BIN_NAME="${BIN_NAME:-runify}"
PREFIX="${PREFIX:-/usr/local}"
BIN_DIR="${PREFIX}/bin"
MAN_DIR="${PREFIX}/share/man/man1"

# Paths relative to project root (script is called from Makefile)
SRC_BIN="bin/${BIN_NAME}"
SRC_MAN="docs/${BIN_NAME}.1"

if [ ! -f "$SRC_BIN" ]; then
    echo "Error: Binary not found at $SRC_BIN. Run 'make build' first." >&2
    exit 1
fi

echo "Installing ${BIN_NAME} to ${BIN_DIR}..."
install -d "$BIN_DIR"
install -m 755 "$SRC_BIN" "$BIN_DIR/"

if [ -f "$SRC_MAN" ]; then
    echo "Installing man page to ${MAN_DIR}..."
    install -d "$MAN_DIR"
    install -m 644 "$SRC_MAN" "$MAN_DIR/"
    gzip -f "${MAN_DIR}/${BIN_NAME}.1"
fi

echo "Done. Run '${BIN_NAME}' to use."
