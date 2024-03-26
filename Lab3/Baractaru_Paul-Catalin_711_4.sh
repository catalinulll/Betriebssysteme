#!/bin/bash

# Iterate over each file provided as an argument
for file in "$@"; do

# Process the file
awk '
{
# Iterate over each word in the current line
for (i = 2; i <= NF; i++) {

# If the current word is the same as the previous word
if ($i == $(i-1)) {

# If this is a new line, print the previous repeated word 
if (NR != prev_line) {

# If there was a previous repeated word, print it
if (prev_word != "" && !(prev_word in repeated_words)) {
print prev_line, prev_word
repeated_words[prev_word] = 1
}

# Clear the previous word variable for new repeated word
prev_word = ""
found_repeated_word = 0
}

if (!found_repeated_word) {
# Store the current line number as the previous line number
prev_line = NR

# Append the current word to the previous word variable
prev_word = $i
found_repeated_word = 1
}
}
}
}
END {

# If there was a previous repeated word at the end of the file, print it
if (prev_word != "" && !(prev_word in repeated_words)) {
print prev_line, prev_word
}
}' "$file"
done

