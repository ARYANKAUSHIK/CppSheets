//This solves chain problems
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

#include "math.hh"

/*
To solve:
1) Determine how many layers we have
2) Break up the string into objects
3) Solve each layer, starting at the top
    -> When solved, put result into objects
4) Solve final equation
*/
double solve_chain(std::string problem) {
    double answer = 0;

    //Count the number of layers
    int layers = 1;
    bool closed = false;

    for (char c : problem) {
        if (c == '(') {
            if (closed) {
                closed = false;
            } else {
                ++layers;
            }
        } else if (c == ')') {
            closed = true;
        }
    }

    //Break up the string
    std::vector<std::string> objects;
    std::string current = "";

    for (char c : problem) {
        if (c == '+' || c == '-' || c == '*' || c == '/'
            || c == '(' || c == ')') {
            objects.push_back(current);
            
            current = "";
            current += c;
            objects.push_back(current);

            current = "";
        } else {
            current += c;
        }
    }

    objects.push_back(current);

    //Now, solve each layer
    int current_layer = layers;
    std::vector<std::string> n_objects;

    while (current_layer>0) {
        int cp = 1;
        std::vector<std::string> objects_tmp;

        std::vector<std::string> to_parse;
        if (current_layer == layers) {
            to_parse = objects;
        } else {
            to_parse = n_objects;
        }

        for (unsigned int i = 0; i<to_parse.size(); i++) {
            if (to_parse.at(i) == "(") {
                ++cp;

                if (cp == current_layer) {
                    std::string prob = "";

                    for (unsigned int j = i+1; j<to_parse.size(); j++) {
                        if (to_parse.at(j) == ")") {
                            double answer = solve_column(prob);
                            objects_tmp.push_back(std::to_string(answer));
                            i = j+1;
                            --cp;
                            break;
                        } else {
                            prob += to_parse.at(j);
                        }
                    }
                } else {
                    objects_tmp.push_back(to_parse.at(i));
                }
            } else if (to_parse.at(i) == ")") {
                if (cp > 1) {
                    --cp;
                }
                objects_tmp.push_back(to_parse.at(i));
            } else {
                objects_tmp.push_back(to_parse.at(i));
            }
        }

        n_objects = objects_tmp;
        --current_layer;
    }

    
    //Re-assemble into one string
    std::string prob = "";
    for (std::string str : n_objects) {
        prob += str;
    }

    //Solve
    answer = solve_column(prob);

    return answer;
}
