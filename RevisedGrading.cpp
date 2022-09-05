#include "RevisedGrading.h"

#include "Exam.h"
#include "Student.h"

std::string GetRevisedGrade(double marks)
{
    if (marks >= 86 && marks <= 100)
    {
        return "A";
    }
    else if (marks >= 81 && marks < 86)
    {
        return "A-";
    }
    else if (marks >= 76 && marks < 81)
    {
        return "B+";
    }
    else if (marks >= 71 && marks < 76)
    {
        return "B";
    }
    else if (marks >= 66 && marks < 71)
    {
        return "B-";
    }
    else if (marks >= 61 && marks < 66)
    {
        return "C+";
    }
    else if (marks >= 56 && marks < 61)
    {
        return "C";
    }
    else if (marks >= 46 && marks < 56)
    {
        return "D";
    }
    else if (marks >= 41 && marks < 46)
    {
        return "D-";
    }
    else if (marks >= 36 && marks < 41)
    {
        return "E";
    }
    else if (marks >= 0 && marks < 36)
    {
        return "F";
    }
    return "";
}

double GetRevisedGradePoint(double marks)
{
    if (marks >= 86 && marks <= 100)
    {
        return 4.0;
    }
    else if (marks >= 81 && marks < 86)
    {
        return 3.7;
    }
    else if (marks >= 76 && marks < 81)
    {
        return 3.3;
    }
    else if (marks >= 71 && marks < 76)
    {
        return 3.0;
    }
    else if (marks >= 66 && marks < 71)
    {
        return 2.7;
    }
    else if (marks >= 61 && marks < 66)
    {
        return 2.3;
    }
    else if (marks >= 56 && marks < 61)
    {
        return 2.0;
    }
    else if (marks >= 46 && marks < 56)
    {
        return 1.67;
    }
    else if (marks >= 41 && marks < 46)
    {
        return 1.33;
    }
    else if (marks >= 36 && marks < 41)
    {
        return 1.0;
    }
    else if (marks >= 0 && marks < 36)
    {
        return 0.0;
    }
    return -1.0;
}

void PrintRevisedSubject(std::ostream& out, Subject& subject)
{
    out << "\n";
    out << subject.subject_code << "\t"
        << std::setw(70) << std::left
        << subject.subject_name
        << std::setw(7) << std::right
        << subject.credit_hours << "\t"
        << std::setw(10) << std::left
        << " " << GetRevisedGrade(subject.marks) << "\t  "
        << std::setprecision(5) << std::fixed << std::showpoint
        << GetRevisedGradePoint(subject.marks);
}

double CalculateRevisedGPA(Exam& exam)
{
    double sum = 0;
    int total_credit_hours = 0;

    if (exam.numOfSubjects <= 0)
        return -1.0;

    else
    {
        for (int i = 0; i < exam.numOfSubjects; i++)
        {
            sum = sum + GetRevisedGradePoint(exam.sub[i].marks) * exam.sub[i].credit_hours;
            total_credit_hours = total_credit_hours + exam.sub[i].credit_hours;
        }

        double gpa = sum / (double)total_credit_hours;

        return gpa;
    }
}

void PrintRevisedExam(std::ostream& out, Exam& exam)
{
    out << "\n\n"
        << exam.printTrimester() << " " << exam.year << " Exam Results: " << std::endl;

    out << "\n"
        << exam.numOfSubjects << " subjects taken.";
    out << "\n___________________________________________________________________________________________________________________________";
    out << "\nSubject Code\t" << std::setw(70) << std::left << "Subject Name"
        << "Credit Hours"
        << "\tGrade "
        << "\tGrade Point";
    out << "\n___________________________________________________________________________________________________________________________";
    for (int i = 0; i < exam.numOfSubjects; i++)
        PrintRevisedSubject(out, exam.sub[i]);

    out << "\nGPA: " << CalculateRevisedGPA(exam);

    out << "\n\n";
}

double CalculateRevisedCurrentCGPA(Student& student)
{
    double sum = 0;
    Exam temp;
    int total_credits = 0;

    if (student.exam_cnt == 0)
    {
        cout << "\n\nNo exam result yet.\n";
        return -1.0;
    }

    else
    {
        int totalCreditsEarned = 0;
        for (int i = 0; i < student.exam_cnt; i++)
        {

            total_credits = 0;
            for (int j = 0; j < student.exam[i].numOfSubjects; j++)
            {
                total_credits = total_credits + student.exam[i].sub[j].credit_hours;
            }

            // calculate total points
            sum = sum + (CalculateRevisedGPA(student.exam[i]) * total_credits);
            totalCreditsEarned = totalCreditsEarned + total_credits;
        }

        double current_cgpa = sum / student.totalCreditsEarned;

        return current_cgpa;
    }
}
