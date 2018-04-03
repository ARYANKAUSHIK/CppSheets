## CppSheets

#### xlsx branch
You are on the xlsx branch. In this branch, I am working to add some Excel file compatibility with this program. I am using the xlnt (https://github.com/tfussell/xlnt) library, and to make development easy, the code is being included directly in mine. All credit to the original author.

#### Introduction
CppSheets is a simple, proof-of-concept spreadsheet application. I made this program as a hobby project primarily for the sake of making something different and challenging. This program has its own XML-based file format (see "file.xml" for more information); it contains an example of all possible values. Basic formulas, cell formatting, and a few other features are supported. 

Please note that this program is very experimental. In fact, virtually its only purpose is to provide an example of what a simple spreadsheet application could look like. I would not recommend using it for any kind of production purposes. Also, the file format is specific to this program.

Guide on how to use command line:
=\				Kill the formula
-{				Create a tooltip
-{\				Clears tooltip

#### Formulas:
There are two ways to apply formulas: individual cells, and the bulk method. Please note that all formulas must start with an equals ("=") sign. Also note that formulas must be entered in the command line (make sure you are typing in the command line, not in the cell. If you are in the cell, it will be treated as text). 

Individual cells can simply be added, subtracted, multiplied, or divided by using one of the following operators: "+", "-", "x", "/". To specify your cells, put the coordinates in parentheses with the row followed by the column (separated with a comma). Below is an example:
=(4,2)+(4,3)+(4,4)+(4,5)+(4,6)

Sometimes, you may want to use a hardcoded number in your formula (eg, converting a decimal to a percent). To do so, enclose the number in brackets. Below is an example:
=(4,7)/(5,7)x[100]

Bulk formulas allow you to apply a mathematical operating to all cells within a certain range. To use these, first begin with one of the operational keywords: 'add' (addition), 'sub' (subtraction), 'mp' (multiplication), and 'div' (division). After the keyword, insert the following symbol: '>'. This does nothing but to let the parser know that we have specified the keyword (its basically a stop command for the parser). After that, specify the starting coordinates, followed by a colon (':'), and ending with the stop coordinates. Below is an example for addition:
=add>(1,2):(1,6)

A long-time MS Excel user would probably find these formulas inferior and cumbersome. This is understandable. But again, this program is meant to be experimental and proof-of-concept, not the next alternative to Excel. 

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
