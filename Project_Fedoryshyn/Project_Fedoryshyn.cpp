#include <iostream>
#include <fstream>
using namespace std;

struct Student
{
    char Surname[50];
    char Name[50];
    int day;
    int month;
    int year;
};

void RW();
void RD();

void RW(Student student);
void RD(Student student);

int main()
{
    bool exit = false;

    do
    {
        cout << "Select option:\n1.Write and read DAT\n2.Write and read TXT\n0.Exit: ";

        int choice = 0;

        cin >> choice;

        if (choice == 1)
        {
            Student student{};

            RW(student);
            RD(student);
        }

        if (choice == 2)
        {
            RW();
            RD();
        }

        if (choice == 0)
        {
            exit = true;
        }

        cout << "Press any key to continue";

        cin.ignore();

        cin.get();
    } while (!exit);
}   

bool IsOlder(Student first_Student, Student second_Student)
{
    if (first_Student.year != second_Student.year)
        return first_Student.year < second_Student.year;

    if (first_Student.month != second_Student.month)
        return first_Student.month < second_Student.month;

        return first_Student.day < second_Student.day;
}

void RW(Student student)
{
    int numberOfStudents = 0;

    cout << "Enter number of students: ";

    cin >> numberOfStudents;

    ofstream file("INFO.DAT", ios::binary);

    for (int i = 0; i < numberOfStudents; i++)
    {
        cout << "Enter student surname, name, day, month and year of birth: ";

        cin >> student.Surname 
            >> student.Name 
            >> student.day 
            >> student.month 
            >> student.year;

        file.write((char*)&student, sizeof(Student));
    }

    file.close();
}

void RD(Student temporary)
{
    ifstream file("INFO.DAT", ios::binary);

    Student students[100];

    int numberOfStudents = 0;

    while (numberOfStudents < 100 && file.read((char*)&students[numberOfStudents], sizeof(Student)))
    {
        numberOfStudents++;
    }

    for (int i = 0; i < numberOfStudents - 1; i++)
    {
        for (int j = 0; j < numberOfStudents - i - 1; j++)
        {
            if (!IsOlder(students[j], students[j + 1]))
            {
                temporary = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temporary;
            }
        }
    }

    cout << "Students sorted by age: \n";

    for (int i = 0; i < numberOfStudents; i++)
    {
        cout << students[i].Surname << " "
            << students[i].Name << " "
            << students[i].day << "."
            << students[i].month << "."
            << students[i].year << endl;
    }
    file.close();
}

void RW()
{
    int numberOfTrains = 0;

    cout << "Enter number of trains: ";

    cin >> numberOfTrains;

    ofstream file("INFO.TXT");

    for (int i = 0; i < numberOfTrains; i++)
    {
        int trainNumber;
        char destination[50];
        int departureHour, departureMinute;
        int arrivalHour, arrivalMinute;

        cout << "Enter train number, station(destination), time of departure hour and minute and time of arrive hour and minute: ";

        cin >> trainNumber
            >> destination
            >> departureHour
            >> departureMinute
            >> arrivalHour
            >> arrivalMinute;

        file << trainNumber << " "
             << destination << " "
             << departureHour << " "
             << departureMinute << " "
             << arrivalHour << " "
             << arrivalMinute << endl;
    }

    file.close();
}

void RD()
{
    ifstream file("INFO.TXT");

    int trainNumber;
    char destination[50];
    int departureHour, departureMinute;
    int arrivalHour, arrivalMinute;

    cout << "Train with travel time less than 10 hours:\n";

    while (file >> trainNumber
        >> destination
        >> departureHour
        >> departureMinute
        >> arrivalHour
        >> arrivalMinute)
    {
        int departureTime = departureHour * 60 + departureMinute;
        int arrivalTime = arrivalHour * 60 + arrivalMinute;

        int travelTime = arrivalTime - departureTime;

        if (travelTime < 0)
        {
            travelTime += 24 * 60;
        }

        if (travelTime <= 10 * 60)
        {
            cout << "Train: " << trainNumber
                << ", destination: " << destination
                << ", departure: " << departureHour << ":"
                << departureMinute
                << ", arrival: " << arrivalHour << ":"
                << arrivalMinute << endl;
        }
    }

    file.close();
}