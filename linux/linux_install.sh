#!/bin/bash
echo "Installing..."
cp CppSheets /usr/bin
cp libxlnt.{so,so.1.2} /usr/lib
cp libgraph.so /usr/local/lib
cp libmath.so /usr/local/lib
cp CppSheets.desktop /usr/share/applications
cp CppSheets.svg /usr/share/icons/hicolor/48x48
ldconfig
update-desktop-database
echo "Done"
