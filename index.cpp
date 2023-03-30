#include <iostream>
#include <string>
#include <map>
#include <limits>
#include <fstream>

/*
Project: Student Management System
For CS0007L - Computer Programming 2

Group Name: Kulto ni Ian

Group Members:
- Alpha Romer N. Coma
- Ian Sioson
- Job Isaac Ong
- Johnmark Mayo

Course Instructor:
Sir. Andales
*/

class Student
{
private:
    static int _idCounter;
    int _id = 0;
    std::string _name = "";
    std::string _birthday = "";
    std::string _address = "";
    bool _isMale = false;
    std::string _degreeProgram = "";
    int _yearLevel = 0;
    Student *_next = NULL;
    Student *_prev = NULL;

public:
    Student(std::string name, std::string birthday, std::string address, bool isMale, std::string degreeProgram, int yearLevel)
    {
        _id = ++_idCounter;
        _name = name;
        _birthday = birthday;
        _address = address;
        _isMale = isMale;
        _degreeProgram = degreeProgram;
        _yearLevel = yearLevel;
    }

    int getId() { return _id; }
    std::string getName() { return _name; }
    std::string getBirthday() { return _birthday; }
    std::string getAddress() { return _address; }
    bool getIsMale() { return _isMale; }
    std::string getDegreeProgram() { return _degreeProgram; }
    int getYearLevel() { return _yearLevel; }
    Student *getNext() { return _next; }
    Student *getPrev() { return _prev; }

    void setName(std::string name) { _name = name; }
    void setBirthday(std::string birthday) { _birthday = birthday; }
    void setAddress(std::string address) { _address = address; }
    void setIsMale(bool isMale) { _isMale = isMale; }
    void setDegreeProgram(std::string degreeProgram) { _degreeProgram = degreeProgram; }
    void setYearLevel(int yearLevel) { _yearLevel = yearLevel; }
    void setNext(Student *next) { _next = next; }
    void setPrev(Student *prev) { _prev = prev; }
};

class BaseSystem
{
protected:
    std::string _members[4] = {"Alpha Romer N. Coma", "Ian Sioson", "Job Isaac Ong", "Johnmark Mayo"};
    void promptMenu(int &selection, int max = 0, std::string message = "")
    {
        std::cout << message;
        std::cin >> selection;
        if (std::cin.fail() || selection < 1 || selection > max)
        {
            std::cout << ">> Invalid input. Please try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            promptMenu(selection, max, message);
        }
    }
    template <typename T>
    void input(T &var, std::string message = "")
    {
        std::cout << message;
        if constexpr (std::is_same_v<T, std::string>)
        {
            std::getline(std::cin, var);
        }
        else
        {
            std::cin >> var;
            if (std::cin.fail())
            {
                std::cout << ">> Invalid input. Please try again.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                input(var, message);
            }
        }
    }
    void printBreak(int len = 40, char c = '-')
    {
        std::cout << std::string(len, c) << "\n";
    }
    int getStudentId()
    {
        int id = 0;
        input(id, "Enter Student ID: ");
        return id;
    }
};

class StudentSystem : public BaseSystem
{

private:
    Student *curr = NULL;
    Student *head = NULL;
    Student *tail = NULL;
    std::string _filename = "students.txt";
    std::map<int, std::string> _choices = {
        {1, "Add New Record"},
        {2, "Search Record"},
        {3, "Display All Records"},
        {4, "Display Specific Record"},
        {5, "Delete Record"},
        {6, "Save to File"},
        {7, "Load from File"},
        {8, "Exit"}};

    void displayIntro()
    {
        std::cout << "__    __           __    __                      __    __  __        ______                     "
                  << "\n";
        std::cout << "|  \\  /  \\         |  \\  |  \\                    |  \\  |  \\|  \\      |      \\                   "
                  << "\n";
        std::cout << "| $$ /  $$__    __ | $$ _| $$_     ______        | $$\\ | $$ \\$$       \\$$$$$$ ______   _______  "
                  << "\n";
        std::cout << "| $$/  $$|  \\  |  \\| $$|   $$ \\   /      \\       | $$$\\| $$|  \\        | $$  |      \\ |       \\ "
                  << "\n";
        std::cout << "| $$  $$ | $$  | $$| $$ \\$$$$$$  |  $$$$$$\\      | $$$$\\ $$| $$        | $$   \\$$$$$$\\| $$$$$$$\\ "
                  << "\n";
        std::cout << "| $$$$$\\ | $$  | $$| $$  | $$ __ | $$  | $$      | $$\\$$ $$| $$        | $$  /      $$| $$  | $$"
                  << "\n";
        std::cout << "| $$ \\$$\\| $$__/ $$| $$  | $$|  \\| $$__/ $$      | $$ \\$$$$| $$       _| $$_|  $$$$$$$| $$  | $$"
                  << "\n";
        std::cout << "| $$  \\$$\\$$     $$| $$   \\$$  $$ \\$$    $$      | $$  \\$$$| $$      |   $$ \\$$    $$| $$  | $$"
                  << "\n";
        std::cout << " \\$$   \\$$ \\$$$$$$  \\$$    \\$$$$   \\$$$$$$        \\$$   \\$$ \\$$       \\$$$$$$ \\$$$$$$$ \\$$   \\$$"
                  << "\n";
    }

    void displayOutro()
    {
        std::cout << " /$$$$$$$$ /$$                           /$$             /$$     /$$\n";
        std::cout << "|__  $$__/| $$                          | $$            |  $$   /$$/\n";
        std::cout << "   | $$   | $$$$$$$   /$$$$$$  /$$$$$$$ | $$   /$$       \\  $$ /$$//$$$$$$  /$$   /$$\n";
        std::cout << "   | $$   | $$__  $$ |____  $$| $$__  $$| $$  /$$/        \\  $$$$//$$__  $$| $$  | $$\n";
        std::cout << "   | $$   | $$  \\ $$  /$$$$$$$| $$  \\ $$| $$$$$$/          \\  $$/| $$  \\ $$| $$  | $$\n";
        std::cout << "   | $$   | $$  | $$ /$$__  $$| $$  | $$| $$_  $$           | $$ | $$  | $$| $$  | $$\n";
        std::cout << "   | $$   | $$  | $$|  $$$$$$$| $$  | $$| $$ \\  $$          | $$ |  $$$$$$/|  $$$$$$/\n";
        std::cout << "   |__/   |__/  |__/ \\_______/|__/  |__/|__/  \\__/          |__/  \\______/  \\______/\n\n\n";

        int i = 1;
        std::cout << "Kulto Ni Ian Members: \n";
        for (auto &member : _members)
            std::cout << i++ << ". " << member << "\n";
        printBreak();
    }

    void displayChoices()
    {
        for (auto &choice : _choices)
            std::cout << choice.first << ". " << choice.second << "\n";
    }
    void promptSelection()
    {
        int selection = 0;
        do
        {
            displayChoices();
            promptMenu(selection, _choices.size(), "\nPlease type your selection: ");
            switch (selection)
            {
            case 1:
                addNewRecord();
                break;
            case 2:
                searchRecord();
                break;
            case 3:
                displayAllRecords();
                break;
            case 4:
                displaySpecificRecord();
                break;
            case 5:
                deleteRecord();
                break;
            case 6:
                saveToFile();
                break;
            case 7:
                loadFromFile();
                break;
            case 8:
                printBreak();
                displayOutro();
                std::cout << "Thank you for using the Student Information System\n";
                printBreak();
                return;
            }
        } while (selection != 8);
    }
    void addNewRecord()
    {
        std::string name = "", birthday = "", address = "", degreeProgram = "";
        int yearLevel = 0;
        bool isMale = false;
        int gender = 0, id = 0;
        std::cin.ignore();
        input(name, "Enter your name: ");
        input(birthday, "Enter your birthday: ");
        input(address, "Enter your address: ");
        input(degreeProgram, "Enter your degree program: ");
        input(yearLevel, "Enter your year level: ");
        input(gender, "Gender (1 for Male, 2 for Female): ");
        isMale = gender == 1 ? true : false;
        Student *student = new Student(name, birthday, address, isMale, degreeProgram, yearLevel);
        if (head == NULL)
        {
            head = student;
            tail = student;
            head->setNext(NULL);
            head->setPrev(NULL);
        }
        else
        {
            student->setNext(NULL);
            student->setPrev(tail);
            tail->setNext(student);
            tail = student;
        }
        std::cout << "\n>> Student added!\n\n";
    }
    Student *searchRecord()
    {
        int id = 0;
        input(id, "Enter the ID of the student: ");
        Student *p = head;
        while (p != NULL)
        {
            if (p->getId() == id)
            {
                std::cout << "\n>> Student found!\n\n";
                return p;
            }
            p = p->getNext();
        }
        std::cout << "\n>> Student not found!\n\n";
        return NULL;
    }
    void displayAllRecords()
    {
        Student *student = head;
        printBreak();
        std::cout << ">> Displaying all records...\n";
        printBreak();
        while (student != NULL)
        {
            std::cout << "ID: " << student->getId() << "\n";
            std::cout << "Name: " << student->getName() << "\n";
            std::cout << "Birthday: " << student->getBirthday() << "\n";
            std::cout << "Address: " << student->getAddress() << "\n";
            std::cout << "Gender: " << (student->getIsMale() ? "Male" : "Female") << "\n";
            std::cout << "Degree Program: " << student->getDegreeProgram() << "\n";
            std::cout << "Year Level: " << student->getYearLevel() << "\n\n";
            student = student->getNext();
        }
        printBreak();
    }
    void displaySpecificRecord()
    {
        Student *student = searchRecord();
        printBreak();
        std::cout << ">> Displaying specific record...\n";
        printBreak();
        if (student != NULL)
        {
            std::cout << "ID: " << student->getId() << "\n";
            std::cout << "Name: " << student->getName() << "\n";
            std::cout << "Birthday: " << student->getBirthday() << "\n";
            std::cout << "Address: " << student->getAddress() << "\n";
            std::cout << "Gender: " << (student->getIsMale() ? "Male" : "Female") << "\n";
            std::cout << "Degree Program: " << student->getDegreeProgram() << "\n";
            std::cout << "Year Level: " << student->getYearLevel() << "\n\n";
        }
        else
        {
            std::cout << ">> Record not found.\n\n";
        }
    }
    bool deleteRecord()
    {
        Student *student = searchRecord();
        printBreak();
        std::cout << ">> Deleting record...\n";
        printBreak();
        if (student != NULL)
        {
            Student *p = head;
            while (p != NULL)
            {

                if (head == student)
                {
                    head = student->getNext();
                    delete student;
                    std::cout << ">> Student deleted!\n\n";
                    return true;
                }
                if (p->getNext() == student)
                {
                    p->setNext(student->getNext());
                    delete student;
                    std::cout << ">> Student deleted!\n\n";
                    return true;
                }
                p = p->getNext();
            }
        }
        else
        {
            std::cout << ">> Record not found.\n";
        }
        return false;
    }
    bool saveToFile()
    {
        std::ofstream file(_filename, std::ios::binary);
        if (!file.is_open())
            return false;
        Student *student = head;
        while (student != NULL)
        {
            file << student->getId() << "\n";
            file << student->getName() << "\n";
            file << student->getBirthday() << "\n";
            file << student->getAddress() << "\n";
            file << (student->getIsMale() ? "1" : "0") << "\n";
            file << student->getDegreeProgram() << "\n";
            file << student->getYearLevel() << "\n";
            student = student->getNext();
        }
        file.close();
        return true;
    }
    bool loadFromFile()
    {
        std::ifstream file(_filename, std::ios::binary);
        if (!file.is_open())
            return false;
        std::string line;
        Student *curr = head;
        while (std::getline(file, line))
        {
            int id = std::stoi(line);
            std::getline(file, line);
            std::string name = line;
            std::getline(file, line);
            std::string birthday = line;
            std::getline(file, line);
            std::string address = line;
            std::getline(file, line);
            bool isMale = line == "1" ? true : false;
            std::getline(file, line);
            std::string degreeProgram = line;
            std::getline(file, line);
            int yearLevel = std::stoi(line);
            Student *student = new Student(name, birthday, address, isMale, degreeProgram, yearLevel);
            if (head == NULL)
            {
                head = student;
                tail = student;
                head->setNext(NULL);
                head->setPrev(NULL);
            }
            else
            {
                student->setNext(NULL);
                student->setPrev(tail);
                tail->setNext(student);
                tail = student;
            }
        }
        file.close();
        return true;
    }

public:
    void init()
    {
        displayIntro();
        std::cout << "\nWelcome to the Student Information System" << std::endl
                  << std::string(50, '-') << "\n";
        promptSelection();
    }
};
int Student::_idCounter = 0;

int main(void)
{
    StudentSystem system;
    system.init();
    return EXIT_SUCCESS;
}
