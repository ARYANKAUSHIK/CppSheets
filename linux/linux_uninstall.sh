#!/bin/bash
echo "Uninstalling CppSheets..."
rm /usr/bin/CppSheets
rm /usr/lib/libxlnt.{so,so.1.2}
rm /usr/share/applications/CppSheets.desktop
rm /usr/share/icons/hicolor/48x48/CppSheets.svg
ldconfig
update-desktop-database
echo "Done"
