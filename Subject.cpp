#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Subject.h"




Subject::Subject()
{
	strcpy(subject_code, " ");
	strcpy(subject_name, " ");
	credit_hours = 0;
	marks = 0;
}


const char *Subject::getGrade()
{
	if(marks >= 0 && marks < 50)
		return "F";
	else if(marks >= 50 && marks < 55)
		return "C";
	else if(marks >= 55 && marks < 60)
		return "C+";
	else if(marks >= 60 && marks < 65)
		return "B-";
	else if(marks >= 65 && marks < 70)
		return "B";
	else if(marks >= 70 && marks < 75)
		return "B+";
	else if(marks >= 75 && marks < 80)
		return "A-";
	else if(marks >= 80 && marks < 90)
		return "A";
	else if(marks >= 90 && marks <= 100)
		return "A+";
	else
		return "N/A";
}


double Subject::getGradePoint()
{
	if(marks >= 0 && marks < 50)
		return 0.00;
	else if(marks >= 50 && marks < 55)
		return 2.00;
	else if(marks >= 55 && marks < 60)
		return 2.33;
	else if(marks >= 60 && marks < 65)
		return 2.67;
	else if(marks >= 65 && marks < 70)
		return 3.00;
	else if(marks >= 70 && marks < 75)
		return 3.33;
	else if(marks >= 75 && marks < 80)
		return 3.67;
	else if(marks >= 80 && marks <= 100) //cover A and A+
		return 4.00;
	else 
		return -1.0;
}



void Subject::print(ostream &out)
{
	out << "\n";
	out << subject_code << "\t" << setw(70) << left << subject_name << setw(7) << right << credit_hours << 
		"\t" << setw(10) << left << " " << getGrade() << "\t  " << setprecision(5) << fixed << showpoint <<
		getGradePoint();
}
