#!/bin/bash
cd build
mkdir linux_bin
cp src/CppSheets linux_bin
cp xlnt/source/libxlnt.{so,so.1.2} linux_bin
cp ../linux_install.sh linux_bin
cp ../linux_uninstall.sh linux_bin
cp ../linux_deploy_readme linux_bin/README
cp ../CppSheets.desktop linux_bin
cp ../src/icons/kspread.png linux_bin/CppSheets.png
cp ../COPYING* linux_bin

tar -czvf CppSheets_bin_linux.tar.gz linux_bin/*
