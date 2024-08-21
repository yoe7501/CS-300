#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Define a Course structure
struct Course {
    std::string courseNumber;
    std::string title;
    std::vector<std::string> prerequisites;
    Course* next;

    Course(std::string courseNum, std::string courseTitle)
        : courseNumber(courseNum), title(courseTitle), next(nullptr) {}
};

// Function to insert a course into the linked list in sorted order
void insertCourse(Course*& head, Course* newCourse) {
    if (head == nullptr || head->courseNumber > newCourse->courseNumber) {
        newCourse->next = head;
        head = newCourse;
    } else {
        Course* current = head;
        while (current->next != nullptr && current->next->courseNumber < newCourse->courseNumber) {
            current = current->next;
        }
        newCourse->next = current->next;
        current->next = newCourse;
    }
}

// Function to load courses from file into the linked list
void loadCourses(Course*& head, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Unable to open file." << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string courseNum, title;
        getline(ss, courseNum, ',');
        getline(ss, title, ',');

        Course* newCourse = new Course(courseNum, title);

        std::string prereq;
        while (getline(ss, prereq, ',')) {
            newCourse->prerequisites.push_back(prereq);
        }

        insertCourse(head, newCourse);
    }
    file.close();
    std::cout << "Courses loaded successfully." << std::endl;
}

// Function to print the course list in alphanumeric order
void printCourseList(Course* head) {
    Course* current = head;
    while (current != nullptr) {
        std::cout << current->courseNumber << ": " << current->title << std::endl;
        current = current->next;
    }
}

// Function to print course information and its prerequisites
void printCourseInfo(Course* head, const std::string& courseNumber) {
    Course* current = head;
    while (current != nullptr) {
        if (current->courseNumber == courseNumber) {
            std::cout << "Course Number: " << current->courseNumber << std::endl;
            std::cout << "Title: " << current->title << std::endl;
            std::cout << "Prerequisites: ";
            if (current->prerequisites.empty()) {
                std::cout << "None" << std::endl;
            } else {
                for (const std::string& prereq : current->prerequisites) {
                    std::cout << prereq << " ";
                }
                std::cout << std::endl;
            }
            return;
        }
        current = current->next;
    }
    std::cout << "Course not found." << std::endl;
}

// Function to display the menu and handle user input
void displayMenu(Course*& head) {
    int choice = 0;
    std::string filename;
    std::string courseNumber;

    while (choice != 9) {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Load Courses" << std::endl;
        std::cout << "2. Print Course List" << std::endl;
        std::cout << "3. Print Course Information" << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter the file name: ";
                std::cin >> filename;
                loadCourses(head, filename);
                break;
            case 2:
                printCourseList(head);
                break;
            case 3:
                std::cout << "Enter the course number: ";
                std::cin >> courseNumber;
                printCourseInfo(head, courseNumber);
                break;
            case 9:
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
        }
    }
}

int main() {
    Course* head = nullptr;
    displayMenu(head);

    // Cleanup
    while (head != nullptr) {
        Course* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
