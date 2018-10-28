//This is a simple program that solves math via the PEMDAS
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include "math.hh"

/*
To solve:
1) Break down the program into objects; an object is either a number or an operator.
2) Go through the array, and solve multiplication and division first;
	if the operator is addition or subtraction, re-add it to the new array;
	otherwise, re-add the new product/quotient to the array
3) Go through the array again, this time solving addition and subtraction
4) Return the result
*/
double solve_column(std::string problem) {
	double answer = 0;
	
	//First, break down the array
	std::vector<std::string> objects1;
	std::string current = "";
	
	for (char c : problem) {
		if (c == '+' || c == '-' || c == '*' || c == '/') {
			objects1.push_back(current);
			
			current = "";
			current += c;
			objects1.push_back(current);
			
			current = "";
		} else {
			current += c;
		}
	}
	
	objects1.push_back(current);
	
	//Now, go through the array again and solve for mp/div
	std::vector<std::string> objects2;
	double tanswer = 0;
	bool was_last = false;
	
	for (int i = 1; i<objects1.size(); i+=2) {
		if (objects1.at(i) == "+" || objects1.at(i) == "-") {
			if (was_last) {
				objects2.push_back(std::to_string(tanswer));
				was_last = false;
			} else {
				objects2.push_back(objects1.at(i-1));
			}
			
			objects2.push_back(objects1.at(i));
			//objects2.push_back(objects1.at(i+1));
		} else if (objects1.at(i) == "*" || objects1.at(i) == "/") {
			double no2 = std::atof(objects1.at(i+1).c_str());
			
			if (!was_last) {
				tanswer = std::atof(objects1.at(i-1).c_str());
				was_last = true;
			}
			
			
			if (objects1.at(i) == "*") {
				tanswer *= no2;
			} else if (objects1.at(i) == "/") {
				tanswer /= no2;
			}
		} else {
			std::cout << "Error: Unknown operator." << std::endl;
		}
	}
	
	if (was_last) {
		objects2.push_back(std::to_string(tanswer));
	} else {
		objects2.push_back(objects1.at(objects1.size()-1));
	}
	
	//Now solve for addition and subtraction
	//Since we are on the last step, we can append it directly to the answer variable
	answer = std::atof(objects2.at(0).c_str());
	
	for (int i = 1; i<objects2.size(); i+=2) {
		double no2 = std::atof(objects2.at(i+1).c_str());
		
		if (objects2.at(i) == "+") {
			answer += no2;
		} else if (objects2.at(i) == "-") {
			answer -= no2;
		}
	}
	
	return answer;
}
