#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <iostream>
#include "bst.h"
using namespace std;
namespace cop3530 {

struct student_info {
    string name;
    double gpa;

    public:
        student_info();
        student_info(string name, double gpa);
        string get_name() const;
        double get_gpa() const;
        bool operator==(const student_info &other) const;
    
};

class student_db {
    // your bst
    bst<int, student_info> studentDataBase;

    public:
        student_db();
        ~student_db();
        void insert(const int student_id, const string &student_name, const double gpa);
        void erase(const int student_id);
        student_info& lookup(const int student_id);
        bool empty() const;
        size_t size() const;
        vector<pair<int, student_info>> get_all_students();
};
}