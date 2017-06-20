/**
 * Thomas Herr
 *
 */
using namespace std;

#include <iostream>
#include <string>
#include <cstdio>

struct RomanNumeral {
    string expression;
    bool isValid() {
        bool valid = true;
        //Check if the expression is valid
        for(unsigned int i=0; i<expression.length(); i++) {
            char current = expression.at(i);
            if(current=='I'||current=='V'||current=='X'||current=='L'||current=='C'||current=='D'||current=='M') {
                //Do nothing. Characters are valid
            } else {
                valid = false;
            }
        }
        return valid;
    }
};

int get_selection();
RomanNumeral getRomanInput();
int getBase10Input();
RomanNumeral Base10ToRoman();
void RomanAddition();
void RemoveSubstractives();
void AddSubstractives();

/**
 * Loop to get user input
 * @return
 */
int get_selection() {
    int selection;
    for(;;) {
        cout << "Your Options:" << endl;
        cout << "1. Roman to Base 10" << endl;
        cout << "2. Base 10 to Roman" << endl;
        cout << "3. Add 2 Roman numbers" << endl;
        cout << "4. Exit" << endl;

        cin >> selection;

        if(!cin.fail()) {
            if(selection>=1||selection<=4) {
                return selection;
            } else {
                cout << "Invalid Input Provided. Please select again";
            }
        } else {
            cout << "Invalid Input Provided. Please select again";
        }
    }
}
/**
 * Get input from user for Roman Numeral to operate on
 * @return RomanNumeral struct containing data
 */
RomanNumeral getRomanInput() {
    cout << "Input the Roman number: ";

    RomanNumeral input;

    for(;;) {
        cin >> input.expression;

        if(!cin.fail()) {
            if(input.isValid()) {
                break;
            } else {
                cout << "Invalid input, please try again" << endl;
            }
        } else {
            cout << "Invalid input, please try again" << endl;
        }
    }


    return input;
}

/**
 * Get user input in the form of a base 10 number
 * @return int Base 10 integer user has input
 */
int getBase10Input() {
    int input;
    for(;;) {
        cout << "Input the base 10 number (< 9999 and > 0): ";

        cin >> input;

        if(!cin.fail()) {
            if(input>0&&input<9999) {
                break;
            } else {
                cout << "Invalid Input, please try again" << endl;
            }
        } else {
            cout << "Invalid Input, please try again" << endl;
        }
    }

    return input;
}

int RomanToBase10(char input) {
    int total = 0;
    switch(input) {
        case 'I':
            total+=1;
            break;
        case 'V':
            total+=5;
            break;
        case 'X':
            total+=10;
            break;
        case 'L':
            total+=50;
            break;
        case 'C':
            total+=100;
            break;
        case 'D':
            total+=500;
            break;
        case 'M':
            total+=1000;
            break;
        default:
            cout << "Invalid Character Detected" << endl;
            break;
    }

    return total;
}

/**
 * Convert roman numeral into Base 10 integer
 * I	V	X	L	C	D	M
 * 1	5	10	50	100	500	1000
 *
 * M CM XC IV = 1000 + 100 + 1000 + 10 + 100 + 1 + 5 = 2216
 *
 * Simply add up the values of the Roman symbols. Of course, if a subtractive appears with a I, X, or C to the left
 * of a "larger" symbol, we need to substitute the pair for the correct numeric value.
 *
 * @param input RomanNumeral
 */
int RomanToBase10(RomanNumeral input) {

    int total = 0;
    for(unsigned int i=0; i<input.expression.length(); i++) {
        char current = input.expression.at(i);
        char next = input.expression.at(i+1);

        switch(current) {
            case 'I':
                //Check if the next character is V or X (Warning about indexes)
                if(next=='V') {
                    //This is actually 4, so add that and skip a character position
                    total+=4;
                    i++;
                } else if(next=='X') {
                    //This is actually 9, so add that and skip a character position
                    total+=9;
                    i++;
                } else {
                    total+=1;
                }
                break;
            case 'V':
                cout << "Adding 5" << endl;
                total+=5;
                break;
            case 'X':
                //Check if the next character is an L or C

                if(next=='L') {
                    //This is actually 40, so add that and skip a character position
                    total+=40;
                    i++;
                } else if(next=='C') {
                    //This is actually 90, so add that and skip a character position
                    total+=90;
                    i++;
                } else {
                    total+=10;
                }

                break;
            case 'L':
                cout << "Adding 50" << endl;
                total+=50;
                break;
            case 'C':
                //Check if the next character is an D or M

                if(next=='D') {
                    //This is actually 400, so add that and skip a character position
                    total+=400;
                    i++;
                } else if(next=='M') {
                    //This is actually 90, so add that and skip a character position
                    total+=900;
                    i++;
                } else {
                    total+=100;
                }

                break;
            case 'D':
                cout << "Adding 500" << endl;
                total+=500;
                break;
            case 'M':
                cout << "Adding 1000" << endl;
                total+=1000;
                break;
            default:
                cout << "Invalid Character Detected at position " << i << endl;
                break;
        }
    }

    cout << "In Base 10 this is: " << total << endl;
    return total;
}

/**
 * Look for repeat of symbols (Groups of 4)
 * To do this we proceed right-to-left and look for four of the same symbol.
 *
 * @param input
 */
void RemoveSubstractives(RomanNumeral &input) {
    //MMCCCXXXXVIIII
    //If we have any of the follwing patterns:

    //IV = IIII
    //IX = VIIII
    //XL = XXXX
    //XC = LXXXX
    //CD = CCCC
    //CM = DCCCC

    size_t ixmatch = input.expression.find("VIIII");

    if(ixmatch!=string::npos) {
        std::cout << "Found VIIII at position: " << ixmatch << endl;
        input.expression.replace(ixmatch, ixmatch+5, "IX");
    }

    size_t ivmatch = input.expression.find("IIII");

    if(ivmatch!=string::npos) {
        std::cout << "Found IIII at position: " << ivmatch << endl;
        input.expression.replace(ivmatch, ivmatch+4, "IV");
    }

    size_t xcmatch = input.expression.find("LXXXX");

    if(xcmatch!=string::npos) {
        std::cout << "Found LXXXX at position: " << xcmatch << endl;
        input.expression.replace(xcmatch, xcmatch+5, "XC");
    }

    size_t xlmatch = input.expression.find("XXXX");

    if(xlmatch!=string::npos) {
        std::cout << "Found XXXX at position: " << xlmatch << endl;
        input.expression.replace(xlmatch, xlmatch+4, "XL");
    }

    size_t cmmatch = input.expression.find("DCCCC");

    if(cmmatch!=string::npos) {
        std::cout << "Found DCCCC at position: " << cmmatch << endl;
        input.expression.replace(cmmatch, cmmatch+5, "CM");
    }

    size_t cdmatch = input.expression.find("CCCC");

    if(cdmatch!=string::npos) {
        std::cout << "Found CCCC at position: " << cdmatch << endl;
        input.expression.replace(cdmatch, cdmatch+4, "CD");
    }

    cout << "Fully Reduced Form: " << input.expression << endl;
}

/**
 * Find any shortforms and unexpand them
 *
 * @param input
 */
void AddSubstractives(RomanNumeral &input) {

    //If we have any of the follwing patterns:

    //IV = IIII
    //IX = VIIII
    //XL = XXXX
    //XC = LXXXX
    //CD = CCCC
    //CM = DCCCC

    size_t ixmatch = input.expression.find("IX");

    if(ixmatch!=string::npos) {
        std::cout << "Found IX at position: " << ixmatch << endl;
        input.expression.replace(ixmatch, ixmatch+1, "VIIII");
    }


    size_t ivmatch = input.expression.find("IV");

    if(ivmatch!=string::npos) {
        std::cout << "Found IV at position: " << ivmatch << endl;
        input.expression.replace(ivmatch, ivmatch+1, "IIII");
    }

    size_t xcmatch = input.expression.find("XC");

    if(xcmatch!=string::npos) {
        std::cout << "Found XC at position: " << xcmatch << endl;
        input.expression.replace(xcmatch, xcmatch+1, "LXXXX");
    }

    size_t xlmatch = input.expression.find("XL");

    if(xlmatch!=string::npos) {
        std::cout << "Found XL at position: " << xlmatch << endl;
        input.expression.replace(xlmatch, xlmatch+1, "XXXX");
    }

    size_t cmmatch = input.expression.find("CM");

    if(cmmatch!=string::npos) {
        std::cout << "Found CM at position: " << cmmatch << endl;
        input.expression.replace(cmmatch, cmmatch+1, "DCCCC");
    }

    size_t cdmatch = input.expression.find("CD");

    if(cdmatch!=string::npos) {
        std::cout << "Found CD at position: " << cdmatch << endl;
        input.expression.replace(cdmatch, cdmatch+1, "CCCC");
    }



    cout << "Fully Expanded Form: " << input.expression << endl;
}

/**
 * Sort Roman Numerals in ASC order
 *
 * @param input
 */
void SortRomanNumerals(RomanNumeral &input) {

    for(int x=0;x<input.expression.length();x++) {
        for(unsigned int i=0; i<input.expression.length(); i++) {
            //Go through and check each character in relation to its position to left character, if right is larger swap them
            if(i+1<input.expression.length()) {
                char current_character = input.expression.at(i);
                char next_character = input.expression.at(i+1);

                //Convert both to base 10
                int current_character_integer =  RomanToBase10(current_character);
                int next_character_integer = RomanToBase10(next_character);

                if(next_character_integer>current_character_integer) {
                    swap(input.expression[i],input.expression[i+1]);
                }
            }

        }
    }

    cout << "Sorted Expression: " << input.expression << endl;
}

/**
 * Given a base 10 number return a RomanNumeral equivilent
 *
 * @param input int Base 10 user number
 * //2349
 */
RomanNumeral Base10ToRoman(int input) {

    RomanNumeral result;
    int value_left = input;

    //Want to keep going until value left is zero

    do  {
        if(value_left-1000>0) {
            result.expression+='M';
            value_left = value_left - 1000;
        } else if(value_left-500>0) {
            result.expression+='D';
            value_left = value_left - 500;
        } else if(value_left-100>0) {
            result.expression+='C';
            value_left = value_left - 100;
        } else if(value_left-50>0) {
            result.expression+='L';
            value_left = value_left - 50;
        } else if(value_left-10>0) {
            result.expression+='X';
            value_left = value_left - 10;
        } else if(value_left-5>0) {
            result.expression+='V';
            value_left = value_left - 5;
        } else if(value_left-1>0) {
            result.expression+='I';
            value_left = value_left - 1;
        } else {
            result.expression+='I';
            value_left=0;
        }
    } while(value_left>0);


    cout << "Result before substituting subtractives: " << result.expression << endl;
    RemoveSubstractives(result);

    return result;
}


/**
 * 1.	Substitute for any subtractives in both values; that is; "uncompact" the Roman values.
 * 2.	Put the two values together—catenate them.
 * 3.	Sort the symbols in order from left-to-right with the "largest" symbols on the left.
 * 4.	Starting with the right end, combine groups of the same symbols that can make a "larger" one and substitute the single larger one.
 * 5.	Compact the result by substituting subtractives where possible.
 *
 * @param first
 * @param second
 */
void RomanAddition(RomanNumeral first, RomanNumeral second) {
    //Example: CCCLXIX + DCCCXLV
    cout << "Adding: " << first.expression << " to " << second.expression << endl;

    int tempFirst = RomanToBase10(first);
    int tempSecond = RomanToBase10(second);

    int result = tempFirst+tempSecond;

    RomanNumeral tempResult = Base10ToRoman(result);

    //Sort Values
    SortRomanNumerals(tempResult);

    //Compact
    RemoveSubstractives(tempResult);
}



int main() {

    //Hardcode your first name, last name, and student number into 3 strings.
    const string FIRSTNAME = "Thomas";
    const string LASTNAME = "Herr";
    const int STUDENTNUMBER = 200325519;

    //Concatenate your first + last + (ID) to display on the output as seen in the sample
    //Gratissimum: Jason Gubbels (230333333)
    printf("Gratissimum: %s %s (%d)", FIRSTNAME.c_str(), LASTNAME.c_str(), STUDENTNUMBER);


    //Loop continuously to allow the user to make a selection (#4 exits)
    int selection = get_selection();

    //Use a switch statement to determine the user input
    switch(selection) {
        case 1:;
            RomanToBase10(getRomanInput());
            break;
        case 2:
            Base10ToRoman(getBase10Input());
            break;
        case 3:
            RomanAddition(getRomanInput(), getRomanInput());
            break;
        case 4:
            cout << "Gratias tibi!!" << endl;
            #if defined(__linux__)
                        __pause();
            #elif defined(__APPLE__)
                        system( "read -n 1 -s -p \"Press any key to continue...\"" );
            #elif defined(_WIN32)
                    system("pause");
            #elif defined(_WIN64)
                system("pause");
            #endif

        default:
            cout << "Gratias tibi!!" << endl;
            break;
    }

    //Once the user has made the selection call the respective function above to perform the below type of examples.
    //Background is provided along with working samples.

    return 0;
}