#ifndef REVISED_GRADING_H
#define REVISED_GRADING_H

#include "Exam.h"
#include "Student.h"

#include <iomanip>
#include <iostream>
#include <string>

std::string GetRevisedGrade(double);

double GetRevisedGradePoint(double);

void PrintRevisedSubject(std::ostream&, Subject&);

void PrintRevisedExam(std::ostream&, Exam&);

double CalculateRevisedGPA(Exam&);

double CalculateRevisedCurrentCGPA(Student&);

#endif // REVISED_GRADING_H