## CppSheets

#### Introduction
CppSheets is a simple spreadsheet application. This program has its own XML-based file format (see "file.xml" for more information); it contains an example of all possible values. Basic formulas, cell formatting, and a few other features are supported.

Why did I make this? The answer is because I was looking for something challenging to do. I was getting bored with some of my other programs, so after playing around with the QTableWidget, I got to thinking that I could probably make some sort of spreadsheet application with it. After a few experimental programs, I began this project. I do not intend on making the next alternative to Microsoft Excel. My goal is simply to make a working spreadsheet application with as many features found in other programs as possible. The ultimate purpose is to have fun! I have thoroughly enjoyed working on this project, and I continue to enjoy working on it.

#### CppSheets files
CppSheets files are nothing special; they are simply XML files. However, the XML has to follow specific rules in order for it to be loaded. More information on the file format can be found below. These files are specific to this program. Because this program is mainly a hobby project, it may not be wise to use this for any production purposes- at least for now. If you want to, then go for it! While the file format is unlikely to change, you can expect constant GUI changes.

#### Excel files
CppSheets has experimental xlsx (Microsoft Excel) file compatibility. This is made possible through the xlnt (https://github.com/tfussell/xlnt) library. To make things easier, the code is included (unmodified) directly in this project. All credit to the original author.

Xlsx compatibility at this point is very, very limited. CppSheets is able to load text data from xlsx files and cell height/width attributes. All sheets contained in an Excel workbook are also able to be loaded. As far as saving goes, xlsx files can be saved to a limited extent. Only text data and new sheets are saved; formatting is not. Both mechanisms, especially the saving mechanism, are buggy.

CppSheets is currently not an alternative for Microsoft Excel, or any other office suite such as LibreOffice or WPS Office. Save workbooks using this program at your own risk; I am not responsible for mangled spreadsheets. Opening workbooks should not damage them.

#### Command Line
Guide on how to use command line:
=\				Kill the formula
-{				Create a tooltip
-{\				Clears tooltip

#### Formulas:
There are two ways to apply formulas: individual cells, and the bulk method. Please note that all formulas must start with an equals ("=") sign. Also note that formulas must be entered in the command line (make sure you are typing in the command line, not in the cell. If you are in the cell, it will be treated as text). 

Individual cells can be added, subtracted, multiplied, or divided by other cells and/or with constants. Any combination of numbers and signs can be used in a formula. Individual cell formulas now follow the Microsoft Excel syntax.

Bulk formulas allow you to apply a mathematical operating to all cells within a certain range. I am now starting to add better bulk formula support. Right now, the only bulk formula that is supported is the SUM formula. These follow the Microsoft Excel syntax, so they are supported from xlsx files.

Better formula support will be slowly added. It is unlikely that complete support will ever be attained. Remember, though, that this is a proof-of-concept program, not a drop-in replacement from MS Excel.

#### The file format:
Our custom file format is actually quite simple. It is fully XML based. 

The root element must always be title "sheet". Nothing more is needed.

Each page must be in an element titled "page". This element must contain an attribute entitled "title". The value of this attribute will be displayed as the page title in the program.

All page elements must contain two child elements, one entitled "data" and the other entitled "math". The "data" element just contains generic data that will be displayed in the table, along with information on how to display this data. The "math" element contains the formulas for each sheet.

The "data" element contains a variable number of child elements entitled "td". The value of the td element is the data to be displayed. Each td element should have the following attributes:
x 			(the table row to display it in)
y 			(the table column to display it in)
fgColor		(the cell's text color in hex)
bgColor		(the cell's background color in hex)
colwidth	(the column-width of the cell)
rowwidth	(the row-width of the cell)
spanx		(the number of rows the cell is to span)
spany		(the number of columns the cell is to span)
tooltip		(additional information presented as a tooltip)

The "math" element contains a variable number of child elements entitled "equ".
