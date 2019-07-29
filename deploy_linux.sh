#!/bin/bash
cd build
mkdir linux_bin
cp src/CppSheets linux_bin
cp xlnt/source/libxlnt.{so,so.1.2} linux_bin
cp libgraph/libgraph.so linux_bin
cp libmath/libmath.so linux_bin
cp ../linux/linux_install.sh linux_bin
cp ../linux/linux_uninstall.sh linux_bin
cp ../share/linux_deploy_readme linux_bin/README
cp ../share/CppSheets.desktop linux_bin
cp ../src/icons/sheets.svg linux_bin/CppSheets.svg
cp ../COPYING* linux_bin

tar -czvf CppSheets_bin_linux.tar.gz linux_bin/*
