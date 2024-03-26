#!/bin/bash

# Check if the script was called with exactly one argument. It exits if the number of arguments is not equal to 1
if [ $# -ne 1 ]; then
echo "Usage: $0 directory" >&2
exit 1
fi

# Check that the argument is a valid directory
if [ ! -d "$1" ]; then
echo "Error: $1 is not a directory" >&2
exit 1
fi

# Variable to count the number of lines
total=0


for file in $(find "$1" -type f -name "*.txt"); do # Search all text files in the directory and its subdirectories
lines=$(wc -l < "$file") # Counts the number of lines in the file
total=$((total + lines)) # Add the number of lines to the total
done

# Print the total number of lines
echo "$total"

