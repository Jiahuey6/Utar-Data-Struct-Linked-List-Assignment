#define _CRT_SECURE_NO_WARNINGS
#include "List.h"
#include "RevisedGrading.h"
#include "Student.h"
#include "Subfunctions.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

bool CreateStuList(const char*, List*);
bool DeleteStudent(List*, char*);
bool DisplayStudent(List, int);
bool AddExamResult(const char*, List*);
bool recalculateResult(List, char*);
bool FilterStudent(List, List*, char*, int, int);
bool checkEligibleFYP(List, char*);
int menu();

int main()
{
    List list;
    int choice = 0;
    do
    {
        choice = menu(); // Guaranteed to be valid (1-8)

        char id[64];           // Used for case 2, case 7
        int source = 0;        // Used for case 3
        List list2;            // Used for case 6
        char course[64] = { 0 }; // Used for case 6
        int year = 0;          // Used for case 6
        int totalCredit = 0;   // Used for case 6

        bool result = false;
        switch (choice)
        {
        case 1:
            result = CreateStuList("student.txt", &list);
            if (result)
            {

                system("cls");
                std::cout << "1:" << std::endl;
                std::cout << std::endl;
                std::cout << "Successfully read student details!" << std::endl;
            }
            else
            {
                system("cls");
                std::cout << "1:" << std::endl;
                std::cout << std::endl;
                std::cout << "ERROR: Failed to read student details." << std::endl;
            }
            break;
        case 2:
            system("cls");
            std::cout << std::endl;
            std::cout << "2: ";
            std::cout << "Enter the ID of the Student to delete:" << std::endl;
            std::cout << "> ";
            std::cin >> id;
            result = DeleteStudent(&list, id);
            std::cout << "Student successfully deleted." << std::endl;
            if (!result)
            {
                std::cout << "ERROR: Student with id " << id << " not found." << std::endl;
            }
            break;
        case 3:
            do
            {
                system("cls");
                std::cout << std::endl;
                std::cout << "3: ";
                std::cout << "Choose a source:" << std::endl;
                std::cout << "1. Screen" << std::endl;
                std::cout << "2. File" << std::endl;
                std::cout << "> ";
                std::cin >> source;
            } while (source < 1 || source > 2);
            result = DisplayStudent(list, source);
            if (!result)
            {
                system("cls");
                std::cout << std::endl;
                std::cout << "3: ";
                std::cout << "ERROR: List is empty." << std::endl;
            }
            break;
        case 4:
            result = AddExamResult("exam.txt", &list);
            if (result)
            {
                //system("cls");
                //std::cout << std::endl;
                std::cout << "4: ";
                std::cout << "Successfully read exam details!" << std::endl;
            }
            else
            {
                //system("cls");
                //std::cout << std::endl;
                std::cout << "4: ";
                std::cout << "ERROR: Failed to read exam details." << std::endl;
            }
            break;
        case 5:
            system("cls");
            std::cout << std::endl;
            std::cout << "5: ";
            std::cout << "Enter the ID of the Student to check:" << std::endl;
            std::cout << "> ";
            std::cin >> id;
            result = recalculateResult(list, id);
            if (!result)
            {
                system("cls");
                std::cout << std::endl;

                std::cout << "ERROR: Student with id " << id << " not found." << std::endl;
            }
            break;
        case 6:
            system("cls");
            std::cout << std::endl;
            std::cout << "6: ";
            std::cout << std::endl;
            std::cout << "Enter the course to filter:" << std::endl;
            std::cout << "> ";
            std::cin >> course;
            std::cout << "Enter the year to filter:" << std::endl;
            std::cout << "> ";
            std::cin >> year;
            std::cout << "Enter the total credit to filter:" << std::endl;
            std::cout << "> ";
            std::cin >> totalCredit;
            result = FilterStudent(list, &list2, course, year, totalCredit);
            if (result)
            {
                DisplayStudent(list2, 1);
            }
            else
            {
                std::cout << "ERROR: List is in invalid state." << std::endl;
            }
            break;
        case 7:
            system("cls");
            std::cout << std::endl;
            std::cout << "7: ";
            std::cout << std::endl;
            std::cout << "Enter the ID of the Student to check:" << std::endl;
            std::cout << "> ";
            std::cin >> id;
            result = checkEligibleFYP(list, id);
            if (!result)
            {
                std::cout << "ERROR: Student with id " << id << " not found." << std::endl;
            }
            break;
        case 8:
        default:
            system("cls");
            std::cout << "See you next time." << std::endl;
            std::cout << std::endl;
            break;
        }

    } while (choice != 8);

    return 0;
}

/**
 * @brief Reads file `filename` and populates list with students.
 *
 * @param filename file to read from
 * @param list list to be populated with students with
 * @return true Successful operation
 * @return false File not found
 */
bool CreateStuList(const char* filename, List* list)
{
    ifstream in;
    string line;

    in.open(filename);
    if (in.is_open())
    {
        int count = 0;
        map<string, Student> studentMap;
        string currentId;

        while (getline(in, line))
        {
            vector<string> rawSplitLine = Split('=', line);
            string data;

            ++count;

            if (!rawSplitLine.empty())
            {
                data = rawSplitLine[1].substr(1);
            }

            switch (count)
            {
            case 1: // Student Id
                currentId = data;
                strcpy(studentMap[currentId].id, data.c_str());
                break;
            case 2: // Name
                strcpy(studentMap[currentId].name, data.c_str());
                break;
            case 3: // Course
                strcpy(studentMap[currentId].course, data.c_str());
                break;
            case 4: // Phone Number
                strcpy(studentMap[currentId].phone_no, data.c_str());
                break;
            default: // Reset
                count = 0;
                break;
            }
        }

        // Insert into list
        for (auto& kv : studentMap)
        {
            // But first initialize every number
            kv.second.exam_cnt = 0;
            for (int i = 0; i < 10; ++i)
            {
                kv.second.exam[i].gpa = 0.0;
                kv.second.exam[i].numOfSubjects = 0;
                kv.second.exam[i].trimester = 0;
                kv.second.exam[i].year = 0;
                for (int j = 0; j < 6; ++j)
                {
                    kv.second.exam[i].sub[j].credit_hours = 0;
                    kv.second.exam[i].sub[j].marks = 0.0;
                }
            }

            // Then, insert
            list->insert(kv.second);
        }

        return true;
    }

    return false;
}

/**
 * @brief Deletes a student from list given id
 *
 * @param list list to delete from
 * @param id id of Student
 * @return true Successful deletion
 * @return false Deletion failed, student is not found
 */
bool DeleteStudent(List* list, char* id)
{
    int count = 0;
    Node* node = list->head;
    while (node)
    {
        ++count;
        if (strcmp(node->item.id, id) == 0)
        {
            list->remove(count);
            return true;
        }
        node = node->next;
    }

    return false;
}

/**
 * @brief Writes the student list to the source supplied.
 *
 * @param list Student list
 * @param source ostream to display the information on
 * @return true Successful display
 * @return false List is empty, failure
 */
bool DisplayStudent(List list, int source)
{
    if (list.empty())
    {
        return false;
    }

    ostream* o = &cout;
    ofstream out;
    if (source == 2)
    {
        out.open("student_result.txt");
        if (!out)
        {
            cout << "\nError opening file.\n";
            return false;
        }
        o = &out;
    }

    for (Node* node = list.head; node; node = node->next)
    {
        Student s = node->item;
        s.print(*o);
        for (int i = 0; i < s.exam_cnt; ++i)
        {
            s.exam[i].print(*o);
        }
    }

    return true;
}

/**
 * @brief Reads file `filename` and populates students with exam results.
 *
 * @return true Successful operation
 * @return false File not found
 */
bool AddExamResult(const char* filename, List* list)
{
    // Convert list to map
    map<string, Student*> studentMap;
    Node* node = list->head;
    while (node)
    {
        studentMap[node->item.id] = &(node->item);
        node = node->next;
    }

    // Read from file
    ifstream file;
    string line;

    file.open(filename);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            vector<string> splitLine = SplitExamFile(" \t", line);
            if (!splitLine.empty())
            {
                for (int i = 0; i < 10; ++i)
                {
                    if (!studentMap[splitLine[0]]->exam[i].trimester) // Unused exam slot
                    {
                        ++(studentMap[splitLine[0]]->exam_cnt);
                        studentMap[splitLine[0]]->exam[i].trimester = stoi(splitLine[1]);
                        studentMap[splitLine[0]]->exam[i].year = stoi(splitLine[2]);
                        studentMap[splitLine[0]]->exam[i].numOfSubjects = stoi(splitLine[3]);

                        int count = 4;
                        for (int j = 0; j < studentMap[splitLine[0]]->exam[i].numOfSubjects; ++j)
                        {
                            strcpy(studentMap[splitLine[0]]->exam[i].sub[j].subject_code, splitLine[count++].c_str());
                            strcpy(studentMap[splitLine[0]]->exam[i].sub[j].subject_name, splitLine[count++].c_str());
                            studentMap[splitLine[0]]->exam[i].sub[j].credit_hours = stoi(splitLine[count++]);
                            studentMap[splitLine[0]]->exam[i].sub[j].marks = stod(splitLine[count++]);
                        }

                        studentMap[splitLine[0]]->exam[i].calculateGPA();
                        studentMap[splitLine[0]]->calculateCurrentCGPA();

                        break;
                    }
                }
            }
        }

        return true;
    }

    return false;
}

/**
 * @brief Displays the original details of the student with `id` and the details of the student with `id` as if they were using the new grading system.
 *
 * @param list list to read students from
 * @param id id of student to print details for
 * @return true Successful operation
 * @return false Student is not found
 */
bool recalculateResult(List list, char* id)
{
    Node* node = list.head;
    while (node)
    {
        if (strcmp(node->item.id, id) == 0)
        {
            Student student = node->item;
            std::cout << "RESULT OUTPUT BASED ON ORIGINAL GRADING:\n"
                << "_________________________________________";
            student.print(cout);
            std::cout << std::endl;
            std::cout << "-----------------------------------------------ORIGINAL GRADING EXAM RESULT:-------------------------------------------------";

            for (int i = 0; i < student.exam_cnt; ++i)
            {
                student.exam[i].print(cout);
            }

            std::cout << std::endl;
            std::cout << "-----------------------------------------------ORIGINAL GRADING EXAM RESULT:-------------------------------------------------" << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "RESULT OUTPUT BASED ON REVISED GRADING:\n"
                << "_______________________________________"
                << std::endl;
            std::cout << "\n\nName: " << student.name;
            std::cout << "\nId: " << student.id;
            std::cout << "\nCourse: " << student.course;
            std::cout << "\nPhone No: " << student.phone_no;
            std::cout << "\nCurrent CGPA: " << CalculateRevisedCurrentCGPA(student);
            std::cout << "\nTotal Credits Earned: " << student.totalCreditsEarned << std::endl;
            std::cout << std::endl;
            std::cout << "-----------------------------------------------REVISED GRADING EXAM RESULT:-------------------------------------------------";

            for (int i = 0; i < student.exam_cnt; ++i)
            {
                PrintRevisedExam(cout, student.exam[i]);
            }

            std::cout << std::endl;
            std::cout << "-----------------------------------------------ORIGINAL GRADING EXAM RESULT:-------------------------------------------------" << std::endl;

            return true;
        }
        node = node->next;
    }

    return false;
}

bool FilterStudent(List list1, List* list2, char* course, int year, int totalcredit)
{
    if (list1.empty())
    {
        return false;
    }
    if (!list2->empty())
    {
        return false;
    }

    Node* node1 = list1.head;
    while (node1)
    {
        if (strcmp(node1->item.course, course) == 0 &&
            std::string(node1->item.id).substr(0, 2) == std::to_string(year).substr(2, 2) &&
            node1->item.totalCreditsEarned >= totalcredit)
        {
            list2->insert(node1->item);
        }
        node1 = node1->next;
    }
    return true;
}

/**
 * @brief checks if a student, denoted by `id`, in `list` satisfies the condition to take their FYP.
 *
 * This function prints to the console.
 *
 * @param list list to access the student
 * @param id id of the student to check eligibility
 * @return true Eligible
 * @return false Not Eligible
 */
bool checkEligibleFYP(List list, char* id)
{
    if (list.count < 1)
    {
        return false;
    }

    // Get student
    Student* student = nullptr;
    Node* tmp = list.head;
    while (tmp)
    {
        if (strcmp(id, tmp->item.id) == 0)
        {
            student = &(tmp->item);
            break;
        }
        tmp = tmp->next;
    }

    // Check if student exists
    if (!student)
    {
        cout << "There is no student with id " << id << " in the list." << endl;
        return true;
    }

    // Check 30 credits hours & grade
    bool isCreditHoursEligible = false;
    bool isPassedUCCD2502 = false;
    bool isPassedUCCD2513 = false;
    int total_credit_hours = 0;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            char failing_grade[] = "F";
            Subject current_subject = student->exam[i].sub[j];
            // Credit hours
            total_credit_hours += current_subject.credit_hours;

            // Grade
            if (strcmp(current_subject.subject_code, "UCCD2502") == 0)
            {
                if (strcmp(current_subject.getGrade(), failing_grade) != 0)
                {
                    isPassedUCCD2502 = true;
                }
            }

            if (strcmp(current_subject.subject_code, "UCCD2513") == 0)
            {
                if (strcmp(current_subject.getGrade(), failing_grade) != 0)
                {
                    isPassedUCCD2513 = true;
                }
            }
        }
    }

    if (total_credit_hours >= 30)
    {
        isCreditHoursEligible = true;
    }

    // Printing
    if (isCreditHoursEligible && isPassedUCCD2502 && isPassedUCCD2513)
    {
        student->print(cout);
    }
    else
    {
        cout << "This student " << student->name << " is not eligible to take FYP yet" << endl;
    }

    return true;
}

/**
 * @brief Prompts the user for a choice. Returns the choice of the user.
 *
 * 1. Create student list
 * 2. Delete Student
 * 3. Print student list
 * 4. Add exam result
 * 5. Recalculate Result
 * 6. Filter Student
 * 7. Check Eligible FYP Student
 * 8. Exit.
 *
 * @return int Choice of the user
 */
int menu()
{
    bool isInvalidInputGiven = false;
    int input = 0;
    do
    {
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "- = Welcome to the Student Management System = -" << std::endl;
        std::cout << std::endl;
        std::cout << "Choose a task:" << std::endl;
        std::cout << "1. Create student list" << std::endl;
        std::cout << "2. Delete Student" << std::endl;
        std::cout << "3. Print student list" << std::endl;
        std::cout << "4. Add exam result" << std::endl;
        std::cout << "5. Recalculate Result" << std::endl;
        std::cout << "6. Filter Student" << std::endl;
        std::cout << "7. Check Eligible FYP Student" << std::endl;
        std::cout << "8. Exit." << std::endl;

        if (isInvalidInputGiven)
        {

            std::cout << std::endl;
            std::cout << "INVALID INPUT" << std::endl;
            std::cout << "Enter Input between 1 - 8" << std::endl;
            std::cout << std::endl;
        }
        else
        {
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
        }
        std::cout << "> ";
        std::cin >> input;
        isInvalidInputGiven = true;
    } while (input < 1 || input > 8);

    return input;
}
