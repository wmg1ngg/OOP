// 陈婉妹 3240300160
#include <iostream>
#include <string>

struct Student{ // student structure to hold names, scores, and averages
    std::string name[10];
    int score1[10], score2[10], score3[10];
    double average[10];
};

void OutputForm();
int Min(const int a[]);
int Max(const int a[]);

void OutputForm(){ // print the header of the table
    std::cout.setf(std::ios::left); // left-align the output
    
    const char* headers[] = {"no", "name", "score1", "score2", "score3", "average"};
    
    for(int i = 0; i < 6; i++){
        std::cout.width(8); // set the width for each column
        std::cout << headers[i];
    }
    std::cout << std::endl; // end the line after printing the header
}

int Min(const int a[]){ // find the minimum score in an array of scores
    int min_score = a[0];
    for(int i = 1; i < 10; i++){
        if(a[i] < min_score){
            min_score = a[i];
        }
    }
    return min_score;
}

int Max(const int a[]){ // find the maximum score in an array of scores
    int max_score = a[0];
    for(int i = 1; i < 10; i++){
        if(a[i] > max_score){
            max_score = a[i];
        }
    }
    return max_score;
}

int main(){
    double score1avg = 0, score2avg = 0, score3avg = 0;
    Student s;
    
    for(int i = 0; i < 10; i++){
        // input the information of each student
        std::cin >> s.name[i]; 
        std::cin >> s.score1[i];
        std::cin >> s.score2[i];
        std::cin >> s.score3[i];
        
        s.average[i] = (s.score1[i] + s.score2[i] + s.score3[i]) / 3.0; // calculate the average score for each student
        
        // calculate the total score for each subject
        score1avg += s.score1[i];
        score2avg += s.score2[i];
        score3avg += s.score3[i];
    }

    OutputForm();

    // print the information of each student in a formatted way
    for(int i = 0; i < 10; i++){
        std::cout.width(8);
        std::cout << i + 1;
        std::cout.width(8);
        std::cout << s.name[i];
        std::cout.width(8);
        std::cout << s.score1[i];
        std::cout.width(8);
        std::cout << s.score2[i];
        std::cout.width(8);
        std::cout << s.score3[i];
        std::cout.width(8);
        std::cout << s.average[i];
        std::cout << std::endl;
    }
    
    // print the average for each subject
    std::cout.width(8);
    std::cout << " ";
    std::cout.width(8);
    std::cout << "average";
    std::cout.width(8);
    std::cout << score1avg / 10;
    std::cout.width(8);
    std::cout << score2avg / 10;
    std::cout.width(8);
    std::cout << score3avg / 10;
    std::cout << std::endl;

    // print the minimum for each subject
    std::cout.width(8);
    std::cout << " ";
    std::cout.width(8);
    std::cout << "min";
    std::cout.width(8);
    std::cout << Min(s.score1);
    std::cout.width(8);
    std::cout << Min(s.score2);
    std::cout.width(8);
    std::cout << Min(s.score3);
    std::cout << std::endl;

    // print the maximum for each subject
    std::cout.width(8);
    std::cout << " ";
    std::cout.width(8);
    std::cout << "max";
    std::cout.width(8);
    std::cout << Max(s.score1);
    std::cout.width(8);
    std::cout << Max(s.score2);
    std::cout.width(8);
    std::cout << Max(s.score3);
    std::cout << std::endl;

    return 0;
}