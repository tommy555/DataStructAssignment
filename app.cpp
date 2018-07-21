#include	<iostream>
#include 	<fstream>
#include	<string>
#include	<cstdlib>
#include	<iomanip>
#include	"List.h"
#include	"Student.h"
#include	"Node.h"

//menu function
bool ReadFile(char *, List *);
bool DeleteRecord(List *, char *);
bool Display(List, int);
bool InsertResult(char *, List *);
bool printStatistic(List);
bool findEligibleFYPStudent(List, List *);
bool identifyGoodPoorStudent(List, List *, List *);
int menu();

//utilities
void printStudentList();
void test_insert_student();
void clearCin();
void printStudDetail(List, ostream &, int, char *);
string studStrFilter(string);

//run menu function
void runDel();
void runDisplay();

List studentList;

//public var
ifstream in;
ofstream out;

using namespace std;


void main() {
	test_insert_student();
	menu();
	cout << "\n\n";
	system("pause");
}

bool ReadFile(char *filename, List *studList)
{
	ifstream myfile(filename);
	string str;
	string strStud;
	int count = 1;
	if (!myfile.is_open()) cout << "Unable to open file";

	while (getline(myfile, str))
	{
		switch (count) {
		case 1:
			//strStud = studStrFilter(str);
			cout << "Student ID: " << strStud << endl;
			break;
		case 2:
			//strStud = studStrFilter(str);
			cout << "Name: " << strStud << endl;
			break;
		case 3:
			//strStud = studStrFilter(str);
			cout << "Course: " << strStud << endl;
			break;
		case 4:
			//strStud = studStrFilter(str);
			cout << "Phone Number: " << strStud << endl;
			break;
		}
		count++;
		if (count >= 5)
			count = 1;
	}
	return true;
}
bool DeleteRecord(List *studentList, char *id)
{
	int pos;
	if (studentList->findPosById(id, pos))
	{
		
		if (studentList->remove(pos)) cout << "Student with ID: " << id << " have been removed.\n\n";
		else
		{
			cout << "Unable to remove the student with ID: " << id << ".\n\n";
			return false;
		}
	}

	printStudentList();
	return true;
}
bool Display(List sl, int src)
{
	char fn[20] = "student_result.txt";
	if (sl.empty()) return false;
	switch (src)
	{
	case 1:
		printStudDetail(sl, cout, 1, fn);
		break;
	case 2:
		printStudDetail(sl, out, 2, fn);
		break;
	default:
		cout << "Invalid input, please try again";
		return false;
	}

	return true;
}
bool InsertResult(char *fn, List *sl)
{
	string line;
	int lineCount = 1, totalSubTaken, studentPos, exmCount;
	in.open(fn);
	Student *curStud = new Student();
	if (!in)
	{
		cout << "Unable to open file. Please try again. \n\n";
		return false;
	}

	while (in >> line)
	{
		switch (lineCount)
		{
		case 1:
			if (!sl->findPosById(&line[0], studentPos)) return false;
			curStud = &sl->find(studentPos)->item;
			exmCount = curStud->exam_cnt;
			break;
		case 2:
			curStud->exam[exmCount].trimester = stoi(line);
			break;
		case 3:
			curStud->exam[exmCount].year = stoi(line);
			break;
		case 4:
			curStud->exam[exmCount].numOfSubjects = stoi(line);
			for (int i = 0; i < curStud->exam[exmCount].numOfSubjects; i++)
			{
				in >> line;
				strcpy_s(curStud->exam[exmCount].sub[i].subject_code, &line[exmCount]);
				in >> line;
				strcpy_s(curStud->exam[exmCount].sub[i].subject_name, &line[exmCount]);
				in >> line;
				curStud->exam[exmCount].sub[i].credit_hours = stoi(line);
				in >> line;
				curStud->exam[exmCount].sub[i].marks = stoi(line);
			}
			curStud->exam_cnt++;
			break;
		default:
			break;
		}
		lineCount++;
		if (lineCount >= 5) lineCount = 1;
	}

	return true;
}
bool printStatistic(List list)
{
	int totalCsStud = 0;
	int totalIaStud = 0;
	int totalIbStud = 0;
	int totalCnStud = 0;
	int totalCtStud = 0;
	int sub = 0;
	double totalCgpa = 0.0;
	double totalSub = 0.0;
	double ceps = 0.0;
	Student stud;

	for(int i = 1; i <=list.size(); i++)
	{
		list.get(i, stud);
		if (strcmp(stud.course, "CS") == 0) totalCsStud++;
		else if (strcmp(stud.course, "IA") == 0)totalIaStud++;
		else if (strcmp(stud.course, "IB") == 0)totalIbStud++;
		else if (strcmp(stud.course, "CN") == 0)totalCnStud++;
		else if (strcmp(stud.course, "CT") == 0)totalCtStud++;
	
		totalCgpa += stud.current_cgpa;
		for (int a = 0; a < stud.exam_cnt; a++)
		{
			cout << "Student " << stud.id << " have a exam at year " << stud.exam[a].year << " semester " << stud.exam[a].trimester << endl;
			for (int b = 0; b < stud.exam[a].numOfSubjects; b++)
			{
			}
		}
	}

	cout << "Total Students: " << list.size() << endl;
	cout << "CS Students - " << totalCsStud << endl;
	cout << "IA Students - " << totalIaStud << endl;
	cout << "IB Students - " << totalIbStud << endl;
	cout << "CN Students - " << totalCnStud << endl;
	cout << "CT Students - " << totalCtStud << endl;

	cout << "Average CGPA: " << (totalCgpa/list.size()) << endl;
	cout << "Average Subjects Taken Per Semester: " << totalSub << endl;
	cout << "Average Credits Earned Per Semester: " << ceps << endl;

	return true;
}

bool findEligibleFYPStudent(List list1, List *FYPlist)
{
	
	return true;
}
bool identifyGoodPoorStudent(List, List *, List *);

int menu()
{
	int selection;
	cout
		<< "1. Read file.\n2. Delete record.\n3. Insert past exam result.\n4. Display Output"
		<< "\n5. Print Statistic\n6. Find Eligible FYP Student\n7. Identify Good and Poor Result Student\n8. Exit.\n\nPlease select: ";
	cin >> selection;
	switch (selection)
	{
		case 1:
			ReadFile("student.txt", &studentList);
			break;
		break;

		case 2:
			runDel();
			break;

		case 3:
			if (InsertResult("exam.txt", &studentList)) cout << "Reading exam.txt...." << endl;
			break;

		case 4:
			runDisplay();
			break;

		case 5:
			printStatistic(studentList);
			break;

		case 6:
			Student stud;
			bool isUCCD2502Taken = false, isUCCD2513Taken = false;
			for (int i = 1; i <= studentList.size(); i++)
			{
				studentList.get(i, stud);

				if (stud.totalCreditsEarned >= 30)	// check students earned 30 credit hours
				{
					for (int j = 0; j < stud.exam_cnt; j++)	//check students result history
					{
						for (int k = 0; k < stud.exam[j].numOfSubjects; k++)	//check students subject taken 
						{
							if (strcmp("UCCCD2502", stud.exam[j].sub[k].subject_code) == 0)
							{
								isUCCD2502Taken = true;
							}

							if (strcmp("UCCD2513", stud.exam[j].sub[k].subject_code) == 0)
							{
								isUCCD2513Taken = true;
							}

							if (isUCCD2502Taken == true && isUCCD2513Taken == true)
							{
								cout << "Student Eligible to Take FYP: " << endl;
								cout << "==============================" << endl;
								cout << stud.name << endl;
							}
						}
					}
				}
				else
					cout << "There is no student that is eligible to take FYP." << endl;
			}
			findEligibleFYPStudent(studentList, );
			break;

		case 7:
			cout << "Run 7" << endl;
			break;

		case 8:
			exit(0);
			break;

		default:
			clearCin();
			cout << "Invalid input. Please try again.\n\n" << endl;
			menu();
		break;
	}

	menu();
	return 0;
}

void printStudentList()
{
	//char *nName, char *nId, char *nCourse, char *nPhone, double nGPA, int nCredit
	Student curStudent;
	cout 
		<< setw(12) << left << "Name"
		<< setw(12) << left << "ID"
		<< setw(12) << left << "Course"
		<< setw(12) << left << "Phone "
		<< setw(12) << left << "GPA"
		<< setw(12) << "Credit hour"
		<< endl;

	for (int i = 1; i <= studentList.count; i++)
	{
		studentList.get(i, curStudent);
		cout
			<< setw(12) << left << curStudent.name
			<< setw(12) << left << curStudent.id
			<< setw(12) << left << curStudent.course
			<< setw(12) << left << curStudent.phone_no
			<< setw(12) << left << curStudent.current_cgpa
			<< setw(12) << curStudent.totalCreditsEarned << endl;
	}
}

void test_insert_student()
{
	Student stud1("stud1", "1200233", "DI", "0123456781", 3.0, 30);
	Student stud2("stud2", "1201237", "DB", "0177777771", 2.0, 40);
	Student stud3("stud3", "1300899", "IT", "0133333331", 2.5, 50);
	Student stud4("stud4", "1200234", "BC", "0144444441", 4.0, 60);
	Student stud5("stud5", "1200234", "CN", "0144444441", 4.0, 60);
	Student stud6("stud6", "1200234", "CN", "0144444441", 4.0, 60);
	Student stud7("stud7", "1200234", "CS", "0144444441", 4.0, 60);
	Student stud8("stud8", "1200234", "IA", "0144444441", 4.0, 60);

	studentList.insert(1, stud1);
	studentList.insert(2, stud2);
	studentList.insert(3, stud3);
	studentList.insert(4, stud4);
	studentList.insert(5, stud5);
	studentList.insert(6, stud6);
	studentList.insert(7, stud7);
	studentList.insert(8, stud8);

}

void clearCin()
{
	cin.clear();
	cin.ignore(10000, '\n');
}

void runDel()
{
	int pos;
	char input[50];

	cout << "|-----------------------|" << endl;
	cout << "|                       |" << endl;
	cout << "|     DELETE RECORD     |" << endl;
	cout << "|                       |" << endl;
	cout << "|-----------------------|" << endl;

	printStudentList();
	cout << "Please enter the student ID to delete a student: ";
	cin >> input;
	if (studentList.findPosById(input, pos)) DeleteRecord(&studentList, input);
	else
	{
		cout << "Student not found, please try again.\n\n" << endl;
		runDel();
	}
}

void runDisplay()
{
	int src;
	cout << "Choose where to display:\n\t1. On Screen\n\t2. On File\n\nPlease choose: ";
	cin >> src;
	if (src>=1 && src <=2) if (!Display(studentList, src)) cout << "The list is empty" << endl;
}

void printStudDetail(List sl, ostream &output, int src, char *fn)
{
	char star_text[32] = "*******************************", dash_text[29] = "----------------------------";

	if (src == 2) out.open(fn);

	for (int i = 1; i <= sl.size(); i++)
	{
		Node *cs = sl.find(i);
		output << star_text << "STUDENT " << i << star_text << "\n\n";
		cs->item.print(output);
		if (cs->item.exam_cnt <= 0) output << "\n\n\nTHIS STUDENT HAVEN'T TAKE ANY EXAM YET\n\n\n";
		else
		{
			output << dash_text << "PAST EXAM RESULT" << dash_text << "\n\n";
			for (int i = 0; i < cs->item.exam_cnt; i++)
			{
				cs->item.exam[i].print(output);
			}
		}
	}
	char cmd[50] = "start ";
	strcat_s(cmd, fn);
	out.close();
	if (src == 2)
	{
		system(cmd);
	}
}

string studStrFilter(string str)
{
	int pos = str.find('=');
	cout << "str: " << str << endl;
	cout << "pos: " << pos << endl;
	if (pos>=1)
	{
		str = str.substr(pos + 2);
	}

	return str;
}



