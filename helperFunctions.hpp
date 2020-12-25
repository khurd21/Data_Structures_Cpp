//
//  helperFunctions.hpp
//
//  Created by Kyle Hurd on 12/12/20.
//

#ifndef helperFunctions_hpp
#define helperFunctions_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <sstream>


/* *
 *  Created by:  Kyle Hurd
 *  Modified:    11/28/2020
 *  Description: Converts an integer to a string. For example,
 *               if int 42 is passed in, '42' as a string will
 *               be returned.
 */
template <class T>
std::string numToString(T num) {
    std::ostringstream ss;
    ss << num;
    return ss.str();
}

/* *
 *  Created by:  Kyle Hurd
 *  Modified:    11/28/2020
 *  Description: print() behaves much like the function
 *               from Python, and was created to try and clean
 *               up the look of the code. You can add multiple
 *               elements by appending them via a '+'.
 *               Ex. print("Hello " + name + "!");
 *               Default output is cout, but can be outputted to
 *               a file or other source by adding the location
 *               as a second parameter.
 *               Ex.
 *               std::fstream outfile;
 *               openOutFile(outfile, "path/to/file.txt");
 *               print("Output to fstream", outfile);
 */
void print(std::string n = "", std::ostream &output = std::cout) {
    output << n << std::endl;
}

/* *
 *  Created by:  Kyle Hurd
 *  Modified:    11/28/2020
 *  Description: Opens an fstream type variable in input
 *               mode from the name of the file provided
 *               by the string s.
 *
 *               Ex.
 *               std::fstream infile;
 *               openInFile(infile, "./path/to/file.txt");
 */
void openInFile(std::fstream &file, std::string s) {
    
    file.open(s, std::ios::in);
    
    if (file.is_open()) print(s + " opened successfully.");
    else                print(s + " could not be opened. Cannot read data.");
}

/* *
 *  Created by:  Kyle Hurd
 *  Modified:    11/28/2020
 *  Description: Opens an fstream type variable in output
 *               mode from the file name provided by the string
 *               s.
 *
 *               Ex.
 *               std::fstream outfile;
 *               openOutFile(outfile, "./path/to/file.txt");
 */
void openOutFile(std::fstream &file, std::string s) {
    
    file.open(s, std::ios::out);
    
    if (file.is_open()) print(s + " opened successfully.");
    else                print(s + " could not be opened. Cannot write data.");
}

#endif /* helperFunctions_hpp */
