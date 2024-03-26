#!/bin/bash

# Check if there are at least two command line arguments
if [ $# -lt 2 ]
then
echo "Please enter the search term and at least one filename"
exit 1
fi

# Search term is in the first command line argument
search_term="$1"

# Loop over all filenames specified in the command line arguments
for filename in "${@:2}"
do
# Check if the file exists and is readable
if [ ! -r "$filename" ]
then
echo "Cannot read file: $filename"
continue
fi

echo "File: $filename"
echo "Content before filtering:"
cat "$filename"

# Remove lines containing the search term
filtered_content=$(sed "/$search_term/d" "$filename")

echo "Contents after filtering:"

# Put the text in a temporary file so we can print it
echo "$filtered_content" > temporary_file

# Print text
cat temporary_file

# Remove the temporary file
rm temporary_file
done
