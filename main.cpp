/*
 *  UCF COP3330 Fall 2021 Assignment 5 Solution
 *  Copyright 2021 Yohan Hmaiti
 */

// include the header file that has all the libraries needed and imports needed
#include "std_lib_facilities.h"

// use the standard namespace
using namespace std;

// declare three variables that will represent the coefficients in a quadratic formula of the 
// form ax^2 + bx + c, we will also declare a global boolean value that will be updated whenever the 
// user expresses their desire to have their roots evaluated, in that case we set the bool variable to true
// otherwise false
double a, b, c;
bool isValid;

// create a global variable that will be called whenever we want to administer a check and evaluation of the solutions
// specifically the roots, the choice of this approximate number is explained in the related function
double checkMark = 1.0e-7;

// when the bool variable is set to true we check the validity of the passed variable to the function
// by using the value of 1.0e-7 as is explained through the concept of the instability of the quadratic formula
// through the fundamentals of numerical computation, I chose to have 1.0e-7 instead of 1.0e-6 to limit the decimal side
double evaluate(double current) {

    // before evaluating we need to set the variable passed (root) back to its equation
    // and we will store the resulting sum in a variable that will be later used for the evaluation
    double result = (a * current * current) + (b * current) + c;

    // conditional that handles the case where the user doesn't want an evaluation of the results
    // in this case we just return the number back....
    if (!isValid)

        return current;

    // else statement that handles whenever the user wants the roots/solution evaluated
    else {
        
        // handle the case where after the subtitution the result is 0
        if (result == 0)

            return current;

        // handle the case where we get a result that is positive and at the same tim beyong and bigger
        // then the set checkMark for this current assignment
        if (result > 0 && result > checkMark)

            cout << "The current root: " << result << " is positive and off, as it is bigger than the set checkMark\n";

        // handle the case where the result is negative and at the same time smaller than that -checkMark value
        else if (result < - checkMark)

            cout << "The current root: " << result << " is negative and off, as it is smaller than the set checkMark\n";

        // return the current root at the end
        return current;

    }

}

// main driver function
int main(void) {
    
    // prompt the user for their choice to either have their roots checked later in the process or no
    cout << "Welcome to the quadratic equation solver :D, ok! first would you like your roots to be later evaluated ('y' for yes or any other letter for no)?\n";
    // gather the choice input from the user
    char temp = 0;
    cin >> temp;

    // evaluate if the user chose yes or something else
    if (temp == 'y')
        isValid = true;
    else 
        isValid = false;

    // prompt the user for the coefficients needed to administer the calculations
    cout << "The format of a quadratic equation is a * (x^2) + b * (x) + c = 0, please enter a, b and c successively in order with a space: ";
    cin >> a >> b >> c;
    
    // first check if the user enters the first coefficient a as 0 leaving us with an equation in the format of 
    // bx+c, in this case we will check if the second coefficient b is 0, if so we cannot determine the roots
    // if b is not 0 then the root is set to -c/b, then we will evaluate this root if the user wants to.
    if (a == 0) {

        if (b == 0)

            cout << "You entered a as 0 and b as 0, so the root calculation is not possible in this case.....\n";

        else {
            
            double root = -c / b;
            cout << "The single root possible is -> " << evaluate(root);

        }

    }

    // handle the case where the user enters a first coefficient that is not 0, but enters the second as 0
    // so we are left with an equation of the form ax^2+c 
    else if (b == 0) {

        double currRoot = -(c / a);

        if (currRoot < 0)

            cout << "Based on the given coefficients, there aren't any possible real roots......\n";

        else if (currRoot == 0)

            cout << "The possible root is -> 0\n";

        else

            cout << "Based on the given coefficients, we can possibly get two roots, first -> " << evaluate(-sqrt(currRoot)) << " then second ->" << evaluate(sqrt(currRoot));

    }

    // handle the case where all coefficients were entered successfully and they are all different than 0
    else {

        // determine delta b^2 - 4ac, if it is equal to 0 there is one root only, if it is positive then we have 
        // two roots possible, if it is negative then we have imaginary number that in our case will just be pointed to
        // by a print statement....
        double delta = b * b - 4 * a * c;

        // each case has the appropriate root calculation and the appropriate message to be printed
        if (delta == 0) {

            double rt = (-b / (2 * a));
            cout << "The delta resulted in 0, therefore there is only one possible root -> " << evaluate(rt);
        
        }

        else if (delta < 0)

            cout << "The delta calculation resulted in a negative number, so there aren't any real roots possible...\n";

        else {

            double rt1 = (-b - sqrt(delta)) / (2 * a);
            double rt2 = (-b + sqrt(delta)) / (2 * a);
            cout << "The delta calculation resulted in a positive number, so we can determine two roots -> " << evaluate(rt1) << " and " << evaluate(rt2);
        
        }

    }

    // end of the main function
    return 0;
}
