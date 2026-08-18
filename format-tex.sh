#!/usr/bin/env bash
# Formats (or checks) .tex files with latexindent, using .latexindent.yaml.
#
# Usage:
#   ./format-tex.sh          # format all tracked .tex files in place
#   ./format-tex.sh --check  # exit 1 if any file is not correctly formatted (no writes)
#   ./format-tex.sh file.tex # format a specific file

set -euo pipefail
cd "$(dirname "${BASH_SOURCE[0]}")"

if ! command -v latexindent >/dev/null 2>&1; then
  echo "error: latexindent not found (install with: sudo dnf install texlive-latexindent)" >&2
  exit 1
fi

CRUFT_DIR=".latexindent-cruft"
mkdir -p "$CRUFT_DIR"

CHECK_MODE=0
FILES=()
for arg in "$@"; do
  if [[ "$arg" == "--check" ]]; then
    CHECK_MODE=1
  else
    FILES+=("$arg")
  fi
done

if [[ ${#FILES[@]} -eq 0 ]]; then
  mapfile -t FILES < <(git ls-files '*.tex')
fi

if [[ ${#FILES[@]} -eq 0 ]]; then
  echo "no .tex files found"
  exit 0
fi

status=0
for f in "${FILES[@]}"; do
  if [[ $CHECK_MODE -eq 1 ]]; then
    # -k: exit 0 if unchanged, 1 if formatting would change the file
    if ! latexindent -k -s -l -c="$CRUFT_DIR" "$f" >/dev/null 2>"$CRUFT_DIR/stderr.log"; then
      echo "not formatted: $f"
      status=1
    fi
  else
    latexindent -w -s -l -c="$CRUFT_DIR" "$f" >/dev/null 2>"$CRUFT_DIR/stderr.log"
    echo "formatted: $f"
  fi
done

exit $status
