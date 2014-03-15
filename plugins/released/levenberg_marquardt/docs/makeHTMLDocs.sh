#! /usr/bin/bash

echo "Creating documentation for the plugin"
mainDoc=mainDoc
pluginName=levenberg_marquardt

htlatex $mainDoc.tex

mkdir html
cp -v $mainDoc.html ./html/index.html
rm -v $mainDoc.html
cp *.html ./html
cp -r Figures ./html
cp *.css ./html

./clean.sh
echo "Done.."
