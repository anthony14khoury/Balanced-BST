#include <string>
#include <vector>
#include "student_db.h"
using namespace std;


namespace cop3530 {

student_info::student_info() 
{
    name = "No Name";
    gpa = 0.0;
}


student_info::student_info(string name, double gpa): name(name), gpa(gpa) 
{
    this->name = name;
    this->gpa = gpa;
}

string student_info::get_name() const 
{
    return name;
}

double student_info::get_gpa() const 
{
    return gpa;
}

bool student_info::operator==(const student_info &other) const {
    return name == other.name && abs(gpa-other.gpa) < 0.000000001;
}



student_db::student_db() 
{
    //Constructs a student_db object, initializing necessary member variables, etc.
}

student_db::~student_db() 
{
    //Destructs the student_db object. Should free any dynamically allocated memory.
    
    
}

void student_db::insert(const int student_id, const string &student_name, const double gpa) 
{
    //Inserts a new student with identification number student_id, name student_name, and grade point average gpa.
    student_info studentInfo;
    studentInfo.name = student_name;
    studentInfo.gpa = gpa;

    studentDataBase.insert(student_id, studentInfo);        
}

void student_db::erase(const int student_id) 
{
    //Removes the student with identification number student_id.
    //Throws an out_of_range error if a node with Key key is not found in the bst

    studentDataBase.erase(student_id);

}

student_info& student_db::lookup(const int student_id) 
{
    //Returns a student_info struct for the student with identification number student_id.
    //Throws an out_of_range error if the student is not found.

    return studentDataBase.at(student_id);    
}

bool student_db::empty() const 
{
    //Returns true if there are no students in the database and false otherwise.

    if(studentDataBase.empty() == true)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

size_t student_db::size() const 
{
    //Returns the number of students in the database

    return studentDataBase.size();

}

vector<pair<int, student_info>> student_db::get_all_students() 
{
    //Returns a vector of all students in the database in order of increasing identification number. Each element of the vector should be a pair where the first element is the identification number of the student and the second element is a student_info struct for the student. See the test cases for details on the format expected.

    return studentDataBase.inorder_contents();
}

}