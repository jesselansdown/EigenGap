#!/bin/sh
gap=../..
while getopts g: flag
do
    case "${flag}" in
        g) gap=${OPTARG};;
    esac
done

./autogen.sh
./configure --with-gaproot=${gap}
make

echo
echo "Installation attempted with GAP root directory: "
echo $gap
echo
echo "If this is incorrect, please try again with the following flag: "
echo "-g <path-to-GAP-root>
echo "(Refer to the documentation for more details)"
echo
