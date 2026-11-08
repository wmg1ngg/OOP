//3240300160 陈婉妹
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<sstream>
#include<iomanip>
#include<algorithm>
#include<climits>

using namespace std;

struct Student{
    string name;
    map<string, int> grades;
};

struct Widths{ // column widths
    int no, name, col, avg;
};

void readInput(vector<Student>& stu, vector<string>& subs){ // read all students and collect all subjects
    string line;
    while(getline(cin, line)){ // skip empty lines
        if (line.empty()) continue;
        istringstream ss(line);
        Student s;
        ss >> s.name;
        string sub;
        int score;
        while (ss >> sub >> score) { // read (subject, score) pairs until the line is exhausted
            s.grades[sub] = score;
            if (find(subs.begin(), subs.end(), sub) == subs.end()) // if this subject is not already in the list, add it
                subs.push_back(sub);
        }
        stu.push_back(s);
    }
    sort(subs.begin(), subs.end()); // sort subjects alphabetically
}

Widths calcWidths(const vector<Student>& stu, const vector<string>& subs){ // calculate column widths based on the data
    const int pad = 2; // "pad" is the extra space added to the width for better readability
    Widths w;

    w.no = max((int)to_string(stu.size()).length(), 2) + pad;
    w.name = 4;
    for (auto& s : stu) // find the longest name among students
        w.name = max(w.name, (int)s.name.length());
    w.name += pad;
    w.col = 1;
    for (auto& sub : subs) // find the longest subject name among subjects
        w.col = max(w.col, (int)sub.length());
    w.col += pad;
    w.avg = 7 + pad;
    return w;
}

void printCell(int w, const string& s){ // print a cell with given width and content, right-aligned
    cout << setw(w) << right << s;
}

void printHeader(const vector<string>& subs, const Widths& w) {
    printCell(w.no,   "no");
    printCell(w.name, "name");
    for (auto& sub : subs){
        printCell(w.col, sub);
    }
    printCell(w.avg, "average");
    cout << "\n";
}

void printStudents(const vector<Student>& stu, const vector<string>& subs, const Widths& w){ // print each student's data and calculate their average score
    for (int i = 0; i < (int)stu.size(); i++){
        printCell(w.no,   to_string(i + 1));
        printCell(w.name, stu[i].name);

        double sum = 0;
        int cnt = 0;
        for(auto& sub : subs){ // for each subject, check if the student has a grade for it
            auto it = stu[i].grades.find(sub);
            if(it != stu[i].grades.end()){
                printCell(w.col, to_string(it->second)); // print the grade if it exists
                sum += it->second;
                cnt++;
            } else{
                printCell(w.col, "");
            }
        }

        if(cnt > 0){ // if the student has at least one grade, calculate and print the average
            ostringstream ss;
            ss << fixed << setprecision(5) << sum/cnt;
            printCell(w.avg, ss.str());
        }else{
            printCell(w.avg, "");
        }
        cout << "\n";
    }
}

void printSummary(const vector<Student>& stu, const vector<string>& subs, const Widths& w){ // print average, min, and max for each subject
    printCell(w.no, "");
    printCell(w.name, "average");
    for(auto& sub : subs){
        double sum = 0;
        int cnt = 0;
        for(auto& s : stu){
            auto it = s.grades.find(sub);
            if(it != s.grades.end()){
                sum += it->second; cnt++;
            }
        }
        if(cnt > 0){
            ostringstream ss;
            ss << fixed << setprecision(1) << sum / cnt;
            printCell(w.col, ss.str());
        }else{
            printCell(w.col, "");
        }
    }
    printCell(w.avg, "");
    cout << "\n";

    // min
    printCell(w.no, "");
    printCell(w.name, "min");
    for(auto& sub : subs){
        int val = INT_MAX;
        bool found = false;
        for(auto& s : stu){
            auto it = s.grades.find(sub);
            if(it != s.grades.end()){
                val = min(val, it->second);
                found = true;
            }
        }
        printCell(w.col, found ? to_string(val) : "");
    }
    printCell(w.avg, "");
    cout << "\n";

    // max
    printCell(w.no, "");
    printCell(w.name, "max");
    for(auto& sub : subs){
        int val = INT_MIN;
        bool found = false;
        for(auto& s : stu){
            auto it = s.grades.find(sub);
            if(it != s.grades.end()){
                val = max(val, it->second); found = true;
            }
        }
        printCell(w.col, found ? to_string(val) : "");
    }
    printCell(w.avg, "");
    cout << "\n";
}

int main(){
    vector<Student> stu;
    vector<string> subs;
    readInput(stu, subs);

    if(stu.empty()){
        cerr << "no input\n";
        return 1;
    }

    Widths w = calcWidths(stu, subs); // calculate column widths based on the data
    printHeader(subs, w); // print the header row with column names
    printStudents(stu, subs, w); // print each student's data and calculate their average score
    printSummary(stu, subs, w); // print average, min, and max for each subject


    return 0;
}