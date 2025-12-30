#!/bin/sh
set -e

BIN_NAME="${BIN_NAME:-runify}"
PREFIX="${PREFIX:-/usr/local}"
BIN_DIR="${PREFIX}/bin"
MAN_DIR="${PREFIX}/share/man/man1"

echo "Uninstalling ${BIN_NAME}..."

if [ -f "${BIN_DIR}/${BIN_NAME}" ]; then
    rm -f "${BIN_DIR}/${BIN_NAME}"
    echo "Removed ${BIN_DIR}/${BIN_NAME}"
else
    echo "Binary not found at ${BIN_DIR}/${BIN_NAME}"
fi

if [ -f "${MAN_DIR}/${BIN_NAME}.1.gz" ]; then
    rm -f "${MAN_DIR}/${BIN_NAME}.1.gz"
    echo "Removed ${MAN_DIR}/${BIN_NAME}.1.gz"
elif [ -f "${MAN_DIR}/${BIN_NAME}.1" ]; then
    rm -f "${MAN_DIR}/${BIN_NAME}.1"
    echo "Removed ${MAN_DIR}/${BIN_NAME}.1"
fi

echo "Done."
