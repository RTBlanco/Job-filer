#!/bin/sh
set -eu

REPO_RAW_URL="${REPO_RAW_URL:-https://raw.githubusercontent.com/RTBlanco/Job-filer/main}"
INSTALL_DIR="${INSTALL_DIR:-$HOME/.local/bin}"
BINARY_NAME="${BINARY_NAME:-filer}"

need_command() {
  if ! command -v "$1" >/dev/null 2>&1; then
    echo "Error: '$1' is required but was not found." >&2
    exit 1
  fi
}

script_dir=""
case "$0" in
  */*)
    script_dir=$(CDPATH= cd "$(dirname "$0")" && pwd)
    ;;
esac

tmp_dir=$(mktemp -d)
cleanup() {
  rm -rf "$tmp_dir"
}
trap cleanup EXIT INT HUP TERM

need_command cc

source_file=""
if [ -n "$script_dir" ] && [ -f "$script_dir/src/main.c" ]; then
  source_file="$script_dir/src/main.c"
elif [ -f "./src/main.c" ]; then
  source_file="./src/main.c"
else
  need_command curl
  source_file="$tmp_dir/main.c"
  echo "Downloading source..."
  curl -fsSL "$REPO_RAW_URL/src/main.c" -o "$source_file"
fi

mkdir -p "$INSTALL_DIR"

echo "Building $BINARY_NAME..."
cc -O2 -o "$tmp_dir/$BINARY_NAME" "$source_file"

if command -v install >/dev/null 2>&1; then
  install -m 0755 "$tmp_dir/$BINARY_NAME" "$INSTALL_DIR/$BINARY_NAME"
else
  cp "$tmp_dir/$BINARY_NAME" "$INSTALL_DIR/$BINARY_NAME"
  chmod 0755 "$INSTALL_DIR/$BINARY_NAME"
fi

echo "Installed $BINARY_NAME to $INSTALL_DIR/$BINARY_NAME"

case ":$PATH:" in
  *":$INSTALL_DIR:"*)
    echo "Run it with: $BINARY_NAME"
    ;;
  *)
    echo "Add this to your shell profile, then restart your terminal:"
    echo "  export PATH=\"$INSTALL_DIR:\$PATH\""
    echo "Then run it with: $BINARY_NAME"
    ;;
esac
