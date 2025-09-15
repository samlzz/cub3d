#!/usr/bin/env bash

CUB_ROOT='.'
LOGDIR='log'

# ? Maps folders
GOOD_MAP='assets/maps/good'
BAD_MAP='assets/maps/bad'

main() {
	local mode="$1"
	local fold

	if [[ "$mode" == 'good' || "$mode" == 'g' ]]; then
		fold="$GOOD_MAP"
	else
		fold="$BAD_MAP"
	fi
	local i; i=0
	local out
	for f in "$fold/"*; do
		echo "Test map: '$(basename $f)'"
		./cub3d "$f" > "$LOGDIR/"$(basename "${f%.*}.out")
		out="$?"
		if [ "$out" -eq 0 ]; then
			echo "success exit"
		else
			echo "cub3d returned: $out"
		fi
	done
}

cd "$CUB_ROOT"
mkdir -p "$LOGDIR"

main "$@"