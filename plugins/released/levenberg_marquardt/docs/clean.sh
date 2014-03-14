#! /usr/bin/bash

echo "Cleaning docs folder"

extensions="4ct 4tc aux css dvi idv lg log tmp xref html"

for ext in $extensions
do
    echo "Cleaning *.$ext"
    rm -v *.$ext
done

echo "Done.."


