#!/usr/bin/env bash

CUB_ROOT='.'
LOGDIR='log'

GOOD_MAP='assets/maps/good'
BAD_MAP='assets/maps/bad'

COLOR_RESET='\033[0m'
COLOR_GREEN='\033[1;32m'
COLOR_RED='\033[1;31m'
COLOR_YELLOW='\033[1;33m'
COLOR_CYAN='\033[1;36m'
COLOR_GREY='\033[1;30m'

print_info() {
    printf "%b[Info]%b %s\n" "$COLOR_GREY" "$COLOR_RESET" "$1"
}

print_success() {
    printf "%b[Success]%b %s\n" "$COLOR_GREEN" "$COLOR_RESET" "$1"
}

print_error() {
    printf "%b[Error]%b %s\n" "$COLOR_RED" "$COLOR_RESET" "$1" >&2
}

run_tests() {
    local fold="$1"
    local mode="$2"
    local file
    local result
    local error_count=0
    local total=0

	echo $(pwd)
	echo $fold
    for file in "$fold/"*; do
        [[ ! -f "$file" ]] && continue

        local filename; filename=$(basename "$file")
        print_info "Testing map: '$filename'"

        ./cub3d "$file" > "$LOGDIR/${filename%.*}.out"
        result=$?

        if [[ "$mode" == "good" ]]; then
            if [[ "$result" -eq 0 ]]; then
                print_success "Expected success"
            else
                print_error "Unexpected failure (exit $result)"
                ((error_count++))
            fi
        else
            if [[ "$result" -ne 0 ]]; then
                print_success "Expected failure"
            else
                print_error "Unexpected success (exit 0)"
                ((error_count++))
            fi
        fi

        ((total++))
    done

    printf "\n%b[SUMMARY]%b Total: %d | Errors: %d | Passed: %d\n" \
        "$COLOR_YELLOW" "$COLOR_RESET" "$total" "$error_count" "$((total - error_count))"

    return "$error_count"
}

main() {
    local mode="$1"
    local fold

    if [[ "$mode" == 'good' || "$mode" == 'g' ]]; then
        fold="$GOOD_MAP"
        mode='good'
    elif [[ "$mode" == 'bad' || "$mode" == 'b' ]]; then
        fold="$BAD_MAP"
        mode='bad'
    else
        print_error "Usage: $0 [good|g|bad|b]"
        return 1
    fi

    run_tests "$fold" "$mode"
    return $?
}

cd "$CUB_ROOT" || {
    printf "%b[ERROR]%b Failed to change directory to %s\n" "$COLOR_RED" "$COLOR_RESET" "$CUB_ROOT" >&2
    exit 1
}

mkdir -p "$LOGDIR"

main "$@"

