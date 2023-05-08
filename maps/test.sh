#!/bin/bash

# Function to print colored output
print_colored() {
    local color="$1"
    local message="$2"

    case "$color" in
        green) echo -e "\033[32m$message\033[0m" ;;
        red) echo -e "\033[31m$message\033[0m" ;;
        *) echo "$message" ;;
    esac
}


# Function to run the test executable
run_test() {
    local executable="$1"
    local input_file="$2"
    local output_file="$3"

    # Kill the program after 5 seconds
    ( sleep 5; killall "$executable" ) &
    local timer_pid=$!

    # Run the program with valgrind and pipe output to a file
    valgrind --leak-check=full --error-exitcode=1 --log-file="$output_file" ./"$executable" "$input_file"
    local exit_code=$?

    # Kill the timer subprocess
    kill "$timer_pid" 2>/dev/null

    return $exit_code
}

# Function to check test results
check_results() {
    local output_file="$1"

    # Check for the "Error" string
    grep -iq "Error" "$output_file"
    local error_found=$?

    # Check for valgrind issues
    grep -q "ERROR SUMMARY: 0 errors" "$output_file"
    local valgrind_success=$?

    if [ $error_found -eq 0 ]; then
        print_colored green "Success: Error string found"
    else
        print_colored red "Failure: Error string not found"
    fi

    if [ $valgrind_success -eq 0 ]; then
        print_colored green "Success: No valgrind issues"
    else
        print_colored red "Failure: Valgrind issues detected"
    fi
}
# Function to clean up generated files
cleanup() {
    local output_file="$1"
    rm -f "$output_file"
}

# Function to run tests with a list of input files
run_tests_with_files() {
    local executable="$1"
    shift

    for input_file in "$@"; do
        echo "Running test with input file: $input_file"
        local output_file="output_$(basename "$input_file")"
        run_test "$executable" "$input_file" "$output_file"
        check_results "$output_file"
        cleanup "$output_file"
        echo
    done
}

# Check for proper arguments
if [ $# -lt 1 ]; then
    echo "Usage: $0 <executable>"
    exit 1
fi


# Main function
main() {
    local executable="$1"

	# Add input files to the list below
	local input_files=(
	"0_outside_map.cub"
"2_players_map.cub"
"alexis_2.cub"
"alexis_3.cub"
"alexis_4.cub"
"alexis.cub"
"bad_color.cub"
"corrupted_texture_path_east.cub"
"corrupted_texture_path_north.cub"
"corrupted_texture_path_south.cub"
"corrupted_texture_path_west.cub"
"cross.cub"
"double_comma.cub"
"double_comma_empty.cub"
"empty_map.cub"
"illegal_instruction_after_map.cub"
"invalid_characters.cub"
"list_files.sh"
"long_short_lines.cub"
"map_1.cub"
"map_different_f.cub"
"map_double_NO.cub"
"map_floor_overflow.cub"
"map_floor_overflow_int.cub"
"map_gen.py"
"map_not_last.cub"
"minimalist.wrongextensio"
"missing_color.cub"
"missing_map.cub"
"missing_player_map.cub"
"missing_south_texture.cub"
"missing_texture.cub"
"multiplayer.cub"
"neg_color.cub"
"no_info.cub"
"no_map.cub"
"normal_map.cub"
"normal_map_fullHD.cub"
"normal_map_with_minecraft_text.cub"
"only_newlines.cub"
"open_corner.cub"
"open_down_map.cub"
"open_left_map.cub"
"open_right_map.cub"
"open_up_map.cub"
"open_wall.cub"
"player_in_wall.cub"
"space_color.cub"
"stuck_texture_name.cub"
"texture_in_map.cub"
"too_many_informations.cub"
"undefined_s_elememt.cub"
"unreadable (1).cub"
"unreadable.cub"
"weird_ceil_name.cub"
"weird_texture_name.cub"
"wrong_player_pos_down.cub"
"wrong_player_pos_left.cub"
"wrong_player_pos_up.cub"
)

    run_tests_with_files "$executable" "${input_files[@]}"
}

main "$@"
