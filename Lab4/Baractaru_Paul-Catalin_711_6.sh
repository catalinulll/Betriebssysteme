#!/bin/bash

# Check if there is at least one command line argument
if [ $# -eq 0 ]; then
echo "Usage: $0 <directory_name>"
exit 1
fi

# Set the directory name to the first command line argument
dir_name="$1"

# Check if the directory exists
if [ ! -d "$dir_name" ]; then
echo "$dir_name not found"
exit 1
fi

# Find all files and directories in the directory and its subdirectories
# Search for files or directories
# Increment the count for the file/directory name
find "$dir_name"/* -type f -o -type d | awk -F/ '{count[$NF]++} END {for (name in count) {print name, count[name]}}' | sort

