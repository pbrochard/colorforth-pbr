#! /bin/bash

FILE="$1"
OUTPUT="output.c"
DIR=$(mktemp -d --suffix="-colorforth")


function finish() {
  rm -rf "$DIR"
}
trap finish EXIT

awk 'BEGIN{p=1} p {print $0} /#ifdef __SECTION_HASH_DEF/ {p=0}' "$FILE" > "$DIR/pre.c"
awk 'BEGIN{p=0} /#endif.*__SECTION_HASH_DEF/ {p=1} p {print $0}' "$FILE" > "$DIR/post.c"

HASHES=$(awk 'match($0, /define_primitive.*ENTRY_NAME\("([^"]+)"\), ([^)]+)\);/, a) {print a[1]" "a[2]}' "$FILE")

while read -r name opcode; do
  hash=$(colorforth --hash "$name")
  printf "#define %-30s(opcode_t) %-20s // %s\n" "$opcode" "$hash" "$name"
done <<< "$HASHES" > "$DIR/def.c"

cat "$DIR/pre.c" > "$DIR/$OUTPUT"
echo >> "$DIR/$OUTPUT"
cat "$DIR/def.c" >> "$DIR/$OUTPUT"
echo >> "$DIR/$OUTPUT"
cat "$DIR/post.c" >> "$DIR/$OUTPUT"

cat "$DIR/def.c"
cp "$DIR/$OUTPUT" "$FILE"
