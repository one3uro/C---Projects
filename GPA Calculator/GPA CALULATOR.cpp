#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <limits>



std::unordered_map<std::string, double> grade_scale = {
    {"A+", 4.0}, {"A", 4.0}, {"A-", 3.7},
    {"B+", 3.3}, {"B", 3.0}, {"B-", 2.7},
    {"C+", 2.3}, {"C", 2.0}, {"C-", 1.7},
    {"D+", 1.3}, {"D", 1.0}, {"F", 0.0}
};

double gpaCalculator() {
    float total_quality_points = 0.0;
    float total_credit = 0.0;
    int num_courses = 0;
    std::string input;
    std::string grade;
    float grade_points;
    float total_credits;

    

    std::cout << "Enter the number of courses: ";
    std::getline(std::cin, input);

    try {
        num_courses = std::stoi(input);
    } 
    catch (const std::invalid_argument& e) {
        std::cout << "Please enter a valid number.\n";
        return -1.0; // Fixed: returns a double for error
    }
    catch (const std::out_of_range& e) {
        std::cout << "That number is too large.\n";
        return -1.0; // Fixed: returns a double for error
    }

    std::cout << "You entered " << num_courses << " courses.\n";

    // Loop through entered course amount
    for (int i = 0; i < num_courses; i++) { // Fixed the counter increment typo here
        std::cout << "Looping through the provided course Number..." << (i + 1) << "\n";
        
        std::string grade = ""; 
        double credits = 0.0;
    // Enter Grade Using while loop

    while(grade_scale.find(grade) == grade_scale.end()){
        std::cout << "Enter Grade here: ";
        std::cin >> grade;
        if (grade_scale.find(grade) == grade_scale.end()) {
            std::cout << "Grade Entered is not in list of available grades.\n";
        }
    }

    //get credit hours
    std::cout << "Enter credits/hours for this course: ";
    while (!(std::cin >> credits) || credits <= 0) {
        std::cout << "Please enter a valid positive number for credits: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

     grade_points += (grade_scale[grade] * credits);
        total_credits += credits;
    } 

    // Caclulate final results

    if (total_credits == 0) return 0.0;

    // Fixed typo 'total_credit' -> 'total_credits'
    double calculated_gpa = grade_points / total_credits; 

    // Output results
    std::cout << "\nTotal Courses entered: " << num_courses << '\n';
    std::cout << "Your final GPA Grade is: " << calculated_gpa << '\n';

    return calculated_gpa;
} 





int main() {
    //call main function
    gpaCalculator();
    return 0;
}