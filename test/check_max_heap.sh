#!/bin/bash

filename=$1

if [ -z "$filename" ]; then
    echo "Usage: $0 <csv_file>"
    exit 1
fi

# Read the CSV file and store population values in an array
IFS=';'
while read -r _ population; do
    data+=("$population")
done < "$filename"

# Function to check if the array represents a max heap
function is_max_heap() {
    local n=${#data[@]}
    
    for ((i = 0; i < n / 2; i++)); do
        left_child=$((2 * i + 1))
        right_child=$((2 * i + 2))
        
        # Check if left child exists and is greater than the parent
        if [ "$left_child" -lt "$n" ] && [ "${data[$left_child]}" -gt "${data[$i]}" ]; then
            echo "Not a max heap"
            exit 1
        fi

        # Check if right child exists and is greater than the parent
        if [ "$right_child" -lt "$n" ] && [ "${data[$right_child]}" -gt "${data[$i]}" ]; then
            echo "Not a max heap"
            exit 1
        fi
    done
    
    echo "It's a max heap"
    exit 0
}

# Call the function to check if it's a max heap
is_max_heap
