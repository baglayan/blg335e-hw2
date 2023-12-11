#!/bin/bash

# Check if a file name is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

# File to be checked
filename=$1

# Variable to hold the previous number
previous_number=-1

# Counter for out-of-order elements
out_of_order_count=0

# Array to hold positions of out-of-order elements
declare -a out_of_order_positions

# Line number tracker
line_number=0

# Read the file line by line
while IFS=';' read -r city population
do
    # Increment line number
    ((line_number++))

    # Check if the current number is smaller than the previous one
    if (( population < previous_number )); then
        ((out_of_order_count++))
        out_of_order_positions+=($line_number)
    fi
    previous_number=$population
done < "$filename"

# Report the result
if [ "$out_of_order_count" -eq 0 ]; then
    echo "The file is sorted."
else
    echo "The file is not sorted. $out_of_order_count element(s) out of order."
    if [ "$out_of_order_count" -lt 10 ]; then
        echo "Out-of-order elements found at positions: ${out_of_order_positions[*]}"
    fi
    exit 1
fi
