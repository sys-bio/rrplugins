#!  bash

echo "Hello"

releaseFolder='Release'
pRelease='PythonRelease'

#Clean PythonRelease folder
echo "Cleaning folder: $pRelease"

rm -rf $pRelease

mkdir $pRelease

#Copy everything in Release to PythonRelease
cp -r $releaseFolder/* $pRelease

#Remove obsolete files installed by third parties

rm -rfv $pRelease/OLD_NEWS.txt
rm -rfv $pRelease/NOTICE.txt
rm -rfv $pRelease/COPYING.txt
rm -rfv $pRelease/bin/libsbml.dll
rm -rfv $pRelease/bin/README.txt

#Remove stuff not nededd in the python release
#rm -rfv $pRelease/install_roadrunner_win.py
rm -rfv $pRelease/lib
rm -rfv $pRelease/include
rm -rfv $pRelease/examples
rm -rfv $pRelease/compilers
rm -rfv $pRelease/rr_support
rm -rfv $pRelease/bin/*.exe
rm -rfv $pRelease/bin/*.bat
rm -rfv $pRelease/plugins/*.lib

#Get time
timeStr=`date +%m%d%Y-%H.%M`
echo "Time is now: $timeStr"
zipFileName="TellluriumPlugins-"$timeStr".zip"
echo "zipFileName: "$zipFileName
cd $pRelease
zip -r $zipFileName .
cd ..
mv $pRelease/$zipFileName .

#Copy to DropBox
cp -v $zipFileName "/d/DropBox/tel_distro"
echo "done.."
