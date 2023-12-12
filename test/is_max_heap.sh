#!/bin/bash

filename=$1
d=$2

# Function to validate if input is a number
function is_number() {
    if [[ "$1" =~ ^[1-9]+$ ]]; then
        return 0
    else
        return 1
    fi
}

if [ -z "$filename" ] || [ -z "$d" ] || ! is_number "$d" ; then
    echo "Usage: $0 <csv_file> <d>"
    echo "<d> should be a positive integer"
    exit 1
fi

# Read the CSV file and store population values in an array
IFS=';'
while read -r _ population; do
    data+=("$population")
done < "$filename"

# Function to check if the array represents a d-ary max heap
function is_d_ary_max_heap() {
    local n=${#data[@]}
    local last_parent_index=$((n / d - 1))
    
    for ((i = last_parent_index; i >= 0; i--)); do
        current=$i
        
        while true; do
            max=$current
            
            # Calculate indices of children
            for ((j = 1; j <= d; j++)); do
                child=$((d * current + j))
                if [ "$child" -lt "$n" ] && [ "${data[$child]}" -gt "${data[$max]}" ]; then
                    max=$child
                fi
            done
            
            # Check if the current node is less than any of its children
            if [ "$max" != "$current" ]; then
                echo "Not a $d-ary max heap"
                exit 1
            fi
            
            # Move to the next parent
            current=$((current - 1))
            
            if [ "$current" -lt "$((i * d))" ]; then
                break
            fi
        done
    done
    
    echo "It's a $d-ary max heap"
    exit 0
}

# Call the function to check if it's a d-ary max heap
is_d_ary_max_heap
