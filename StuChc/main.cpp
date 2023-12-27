#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>

using namespace std;

struct Course {
    string courseCode;
    string courseName;
    string teacher;
};

struct StudentInfo {
    string username;
    string password;
    string major;
    vector<Course> selectedCourses;
};

class Admin {
private:
    int nextCourseId;
    std::mt19937 gen;// 随机数生成器
public:
    Admin() : nextCourseId(1), gen(std::random_device{}()) {}// 构造函数初始化课程编号为1  初始化随机数生成器
   //检查课程代码的唯一性
    bool isCourseCodeUnique(const vector<Course>& courses, const string& courseCode) {
        return find_if(courses.begin(), courses.end(),
                       [courseCode](const Course& course) {
                           return course.courseCode == courseCode;
                       }) == courses.end();  // 如果课程编号在课程列表中不存在，则返回true
    }

    // 添加课程信息 编号/名称/任课老师
    void addCourse(vector<Course>& courses) {
        Course course;
        //生成范围在10000000-99999999之间的随机数/八位数
        std::uniform_int_distribution<int> dis(10000000, 99999999);
        // 生成唯一的课程编号
        do {
            course.courseCode = std::to_string(dis(gen)); // 将随机数转换为字符串
        } while (!isCourseCodeUnique(courses, course.courseCode)); // 检查课程编号是否唯一
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t  当前操作\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t   请输入课程名称\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        cin>>course.courseName;
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t   当前操作\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t   请输入任课老师\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        cin>>course.teacher;
        courses.push_back(course);
    }

    void deleteCourse(vector<Course>& courses) {
        string courseCode;
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t  当前操作\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t请输入要删除的课程编号\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        cin>>courseCode;
        auto it=remove_if(courses.begin(), courses.end(),
                            [courseCode]( Course& course) {
                                return course.courseCode==courseCode;
                            });// 删除课程编号为courseCode的课程
        if (it!=courses.end()) {
            courses.erase(it);
            printf("\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t删除成功!\t\t\t\t\t\t|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            printf("\n");
            //cout<<"删除成功。"<<endl;
        } else {
            cout<<"未找到课程编号为"<<courseCode<<"的课程。"<<endl;
        }
    }


    void displayAllCourses(  vector<Course>& courses)   {

        printf("\n\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t   全部课程\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\"课程编号\t\t课程名称\t\t任课老师\"\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        for (int i=0; i<courses.size(); ++i) {
            cout<<"\t\t\t\t\t\t\t\t\t\t\t|\t\t   "<<courses[i].courseCode<<"\t\t"<<courses[i].courseName<<"\t\t"<<  courses[i].teacher<<"\t\t\t\t|"<<endl;
        }
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
    }
    void saveToFile(  vector<Course>& courses,   string& filename)   {
        ofstream file(filename);
        if (file.is_open()) {
            for (int i=0; i<courses.size(); ++i) {
                file<<courses[i].courseCode<<","<<courses[i].courseName<<","<<courses[i].teacher<<endl;
            }// 保存课程信息到文件
            file.close();
        } else {
            cout<<"无法打开文件"<<filename<<"进行保存。"<<endl;
        }
    }

    void loadFromFile(vector<Course>& courses,  string& filename) {
        ifstream file(filename); //课程信息  课程编号/课程名/授课教师
        if (file.is_open()) {
            courses.clear();// 清空课程列表
            string line;// 逐行读取课程信息
            while (getline(file, line)) {
                Course course;
                int pos1=line.find(','); // 查找第一个逗号的位置
                int pos2=line.find(',', pos1+1);// 查找第二个逗号的位置
                if (pos1!=string::npos&&pos2!=string::npos) {
                    course.courseCode=line.substr(0, pos1);// 课程编号
                    course.courseName=line.substr(pos1+1, pos2 - pos1 - 1);// 课程名称
                    course.teacher=line.substr(pos2+1);
                    courses.push_back(course);

                    // 更新最大课程编号
                    int courseId=stoi(course.courseCode);
                    nextCourseId=max(nextCourseId, courseId+1);
                }
            }
            file.close();   // 从文件中读取课程信息
            cout<<"从文件"<<filename<<"中读取课程信息成功。"<<endl;
        } else {
            cout<<"无法打开文件"<<filename<<"进行读取。"<<endl;
        }
    }
};

class Student {
private:
    int nextSelectionId; // 记录学生选课的下一个编号
public:
    bool login(  vector<StudentInfo>& students, string& username, string& password, int& stuid) {
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t当前操作:登录\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t请输入用户名\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        cin>>username;
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t当前操作:登录\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t请输入密码\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        cin>>password;
        for (int i=0; i<students.size(); ++i) {
            if ((students[i].username==username)&&(students[i].password==password)) {
                stuid=i;
                return true;
            } // 检查用户名和密码是否匹配
        }
        return false;
    }

    void registerStudent(vector<StudentInfo>& students) {
        StudentInfo student;
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t当前操作:注册\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t请输入用户名\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        cin>>student.username;
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t当前操作:注册\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t请输入密码\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        cin>>student.password;
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t当前操作:注册\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t请输入专业\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        cin>>student.major;
        students.push_back(student); // 将学生信息添加到学生列表中
    }

    void saveToFile(  vector<StudentInfo>& students,   string& filename)   {
        ofstream file(filename);
        if (file.is_open()) {
            for (int i=0; i<students.size(); ++i) {
                file<<students[i].username<<","<<students[i].password<<","<<students[i].major<<endl;
            }// 保存学生信息到文件
            file.close();
            printf("\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t保存成功!\t\t\t\t\t\t|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            printf("\n");
        } else {
            cout<<"\t\t\t\t\t"<<"无法打开文件"<<filename<<"进行保存。"<<endl;
        }
    }

    Student() : nextSelectionId(1) {} // 构造函数初始化选课编号为1

    // 添加课程 先显示所有可选课程 选择后需判断冲突
    void addCourse(vector<Course>& allCourses, StudentInfo& student) {

        printf("\n\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t   全部课程\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\"课程编号\t\t课程名称\t\t任课老师\"\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        for (int i=0; i < allCourses.size(); ++i) {
            cout<<"\t\t\t\t\t\t\t\t\t\t\t|\t\t   "<<allCourses[i].courseCode<<"\t\t"<<allCourses[i].courseName<<"\t\t"<<  allCourses[i].teacher<<"\t\t\t\t|"<<endl;
        }
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");

        int choice;
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t当前操作:选课\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t请输入想要添加的课程序号\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        cin>>choice;
        choice--;
        // 在添加课程之前，先检查selection.txt文件中是否已存在所选课程
        std::ifstream file("selection.txt");
        std::string line;
//        bool courseExists=false;
//        if (file.is_open()) {
//            while (getline(file, line)) {
//                if (line.find(allCourses[choice].courseName)!=std::string::npos) {
//                    courseExists=true;
//                    break;
//                }
//            }
//            file.close();
//        }

        // 检查所选课程是否已经在学生的课程列表中
        for (int i=0; i<student.selectedCourses.size(); i++) {
            if (student.selectedCourses[i].courseName==allCourses[choice].courseName) {
                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t你已经选了这门课，请再次尝试\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                return;
            }
        }

        // 将所选课程添加到学生的课程列表中，使用课程代码作为编号
        if (choice>=0&&choice < allCourses.size()) {
            student.selectedCourses.push_back(allCourses[choice]);
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t选课成功!\t\t\t\t\t\t|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");

            // 使用课程代码作为选课编号
            student.selectedCourses.back().courseCode=allCourses[choice].courseCode;
        } else {
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t无效选择，请再次尝试!\t\t\t\t|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        }

    }

    // 删除课程
    void deleteCourse(vector<Course>& allCourses, StudentInfo& student) {
        int i;
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t当前已选课程\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        for(i=0; i<student.selectedCourses.size(); i++) {
            cout<<"\t\t\t\t\t\t\t\t\t\t\t|"<<"\t\t\t\t"<<i+1<<": "<<student.selectedCourses[i].courseName<<" by "<<student.selectedCourses[i].teacher<<"\t\t\t\t\t|\n";
        }

        int choice;
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t输入你想删除课程的序号\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        //cout<<"输入你想删除课程的序号： ";
        cin>>choice;
        choice=choice - 1;

        if(choice>=0&&choice<student.selectedCourses.size()) {
            student.selectedCourses.erase(student.selectedCourses.begin()+choice);
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t选课删除成功\t\t\t\t\t|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        } else {
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t  选择无效，请重试。\t\t\t\t|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        }
    }


    // 显示学生的课程列表
    void displayMyCourses(  StudentInfo& student)   {
        printf("\n\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        cout<<"\t\t\t\t\t\t\t\t\t\t\t|"<<"\t\t\t\t学生 "<<student.username<<" 所选的课程有：\t\t\t\t|\n";
        for (  auto& course : student.selectedCourses) {
            cout<<"\t"<<"\t\t\t\t\t\t\t\t\t\t|"<<"\t\t课程名称: "<<course.courseName<<"\t\t"<<" 课程代码: "<<course.courseCode<<"\t\t\t|\n";
        }
    }
    // 保存学生的选课信息到文件
    void saveCourseSelection(vector<StudentInfo>& students, string& filename) {
        ofstream file(filename);
        int m=0;
        if (file.is_open()) {
            for (int i=0; i < students.size(); ++i) {
                for (int j=0; j < students[i].selectedCourses.size(); ++j) {
                    file<<students[i].username<<","
                        <<students[i].selectedCourses[j].courseCode<<","
                        <<students[i].selectedCourses[j].courseName<<","
                        <<students[i].selectedCourses[j].teacher<<endl;
                }
            }
            file.close();
        } else {
            cout<<"无法打开文件"<<filename<<"进行保存。"<<endl;
        }
    }

    // 从文件中读取学生的选课信息
    void loadCourseSelection(vector<StudentInfo>& students,  vector<Course>& allCourses,   string& filename) {
        ifstream file("selection.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id, courseCode;
            getline(ss, id, ',');
            getline(ss, courseCode, ',');
            for (auto& student : students) {
                if (student.username==id) {
                    for (auto& course : allCourses) {
                        if (course.courseCode==courseCode) {
                            student.selectedCourses.push_back(course);
                            break;
                        }
                    }
                    break;
                }
            }
        }
        file.close();
    }
};

int main() {
    vector<Course> allCourses; // 所有课程信息
    vector<StudentInfo> students; // 所有学生信息
    Admin admin; // 管理员
    Student student; // 学生
    string coursesFilename="courses.txt";
    string studentsFilename="students.txt";
    string selectionFilename="selection.txt";
    admin.loadFromFile(allCourses, coursesFilename); // 从文件中读取课程信息
    ifstream studentFile(studentsFilename); // 从文件中读取学生信息
    if (studentFile.is_open()) {
        students.clear();
        string line;
        while (getline(studentFile, line)) {
            StudentInfo studentInfo;
            int pos1=line.find(',');
            int pos2=line.find(',', pos1+1);
            if (pos1!=string::npos&&pos2!=string::npos) {
                studentInfo.username=line.substr(0, pos1);
                studentInfo.password=line.substr(pos1+1, pos2 - pos1 - 1);
                studentInfo.major=line.substr(pos2+1);
                students.push_back(studentInfo);
            }
        }
        studentFile.close();
        cout<<"从文件"<<studentsFilename<<"中读取学生信息成功。"<<endl;
    } else {
        cout<<"无法打开文件"<<studentsFilename<<"进行读取。"<<endl;
    }

    student.loadCourseSelection(students, allCourses, selectionFilename);
    while (true) {
        printf("\n\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t   登录界面\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t请选择登录角色\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t1.登录为管理员\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t2.登录为学生\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t3.退出系统\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t选择操作（1/2/3）\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        int choice;
        cin>>choice;
        if (cin.fail()) {
            cout<<"输入错误，请输入数字。"<<endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;        }
        if (choice < 1 || choice > 3) {
            cout<<"输入错误，请输入范围内的选项。"<<endl;
            continue;
        }
        switch (choice) {
            case 1: {
                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t   当前操作\t\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t   请输入管理员密码\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                int password;
                cin>>password;
                if (password!=123456) {
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t  密码错误，登录失败。\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                    break;
                } else{
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t  密码正确，登录成功。\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                }
                while (true) {
                    printf("\n\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t 管理员界面\t\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t请选择如下功能\t\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t1. 添加课程\t\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t2. 删除课程\t\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t3. 显示所有课程\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t4. 保存课程信息到文件\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t5. 返回上一级\t\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t选择操作（1/2/3/4/5）:\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                    cin>>choice;
                    if (cin.fail()) {
                        cout<<"输入错误，请输入数字。"<<endl;
                        cin.clear(); // 清除错误标志
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略输入缓冲区中的所有字符
                        continue;        }
                    if (choice < 1 || choice > 5) {
                        cout<<"输入错误，请输入范围内的选项。"<<endl;
                        continue;
                    }
                    switch (choice) {
                        case 1:
                            admin.addCourse(allCourses);
                            admin.saveToFile(allCourses, coursesFilename);
                            break;
                        case 2:
                            admin.displayAllCourses(allCourses);
                            admin.deleteCourse(allCourses);
                            admin.saveToFile(allCourses, coursesFilename);
                            break;
                        case 3:
                            admin.displayAllCourses(allCourses);
                            break;
                        case 4:
                            admin.saveToFile(allCourses, coursesFilename);
                            break;
                        case 5:
                            cout<<"\n返回上一级。\n";
                            break;
                        default:
                            cout<<"无效的选项。"<<endl;
                    }

                    if (choice==5) {
                        break;
                    }
                }
                break;
            }

            case 2: {
                printf("\n\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t   学生界面\t\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t1. 登录\t\t\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t2. 注册\t\t\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t3. 返回上一级\t\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t选择操作（1/2/3）\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                cin>>choice;
                if (cin.fail()) {
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t  输入错误，请输入数字。\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;        }
                if (choice < 1 || choice > 3) {
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t  输入错误，请输入范围内的选项。\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                    continue;
                }
                switch (choice) {
                    case 1: {
                        string username, password;
                        int stuid;
                        if (student.login(students, username, password, stuid)) {
                            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                            printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t学生登录成功！\t\t\t\t\t|\n");
                            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                            while (true) {
                                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t   学生界面\t\t\t\t\t|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t 请选择功能\t\t\t\t\t|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t1. 添加课程\t\t\t\t\t|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t2. 删除课程\t\t\t\t\t|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t3. 显示我的课程\t\t\t\t|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t4. 返回上一级\t\t\t\t\t|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t选择操作（1/2/3/4）:\t\t\t\t|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                cin>>choice;
                                if (cin.fail()) {
                                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t输入错误，请输入数字！\t\t\t\t|\n");
                                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                    cin.clear();
                                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略输入缓冲区中的所有字符
                                    continue;        }
                                if (choice < 1 || choice > 4) {
                                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t  输入错误，请输入范围内的选项。\t\t\t|\n");
                                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                    continue;
                                }
                                switch (choice) {
                                    case 1:
                                        student.addCourse(allCourses, students[stuid]); // 添加课程
                                        student.saveCourseSelection(students, selectionFilename); // 保存选课信息到文件
                                        break;
                                    case 2:
                                        student.deleteCourse(allCourses, students[stuid]); // 删除课程
                                        student.saveCourseSelection(students, selectionFilename);// 保存选课信息到文件
                                        break;
                                    case 3:
                                        student.displayMyCourses(students[stuid]); // 显示学生的课程列表
                                        break;
                                    case 4:
                                        cout<<"\n返回上一级。\n";
                                        break;
                                    default:
                                        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t    无效的选项。\t\t\t\t\t|\n");
                                        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                }
                                if (choice==4) {
                                    break;
                                }
                            }
                        } else {
                            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                            printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t登录失败，用户名或密码错误。\t\t\t|\n");
                            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                        }
                        break;
                    }
                    case 2:
                        student.registerStudent(students);
                        student.saveToFile(students, studentsFilename);
                        break;
                    case 3:
                        cout<<"\n返回上一级。\n";
                        break;
                    default:
                        cout<<"无效的选项。"<<endl;
                }
                break;
            }

            case 3:
                // 保存课程信息到文件
                admin.saveToFile(allCourses, coursesFilename);
                student.saveToFile(students, studentsFilename);
                student.saveCourseSelection(students, selectionFilename);
                cout<<"\n退出系统。"<<endl;
                return 0;
            default:
                cout<<"无效的选项。"<<endl;
        }
    }
    return 0;
}
