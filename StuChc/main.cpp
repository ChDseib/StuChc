#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Course {
    string courseCode;//课程编号
    string courseName;//课程名称
    string teacher;//授课教师
};

struct StudentInfo {
    string username;//用户名
    string password;//密码
    string major;//专业
    vector<Course> selectedCourses;
};

class Admin {
public:
    //添加课程信息  编号/名称/任课老师
    void addCourse(vector<Course>& courses) {

    }

    //删除课程信息
    void deleteCourse(vector<Course>& courses) {

    }

    //显示所有课程信息
    void displayAllCourses(const vector<Course>& courses) const {

    }

    //将所增删的信息保存到本地
    void saveToFile(const vector<Course>& courses, const string& filename) const {

    }

    //从本地加载课程信息
    void loadFromFile(vector<Course>& courses, const string& filename) {

    }
};

class Student {
public:
    //登录 用户名/密码
    bool login(const vector<StudentInfo>& students, string& username, string& password) {

    }

    //学生信息注册 用户名/密码/专业
    void registerStudent(vector<StudentInfo>& students) {

    }

    //保存学生信息
    void saveToFile(const vector<StudentInfo>& students, const string& filename) const {

    }
    //添加课程  先显示所有可选课程 选择后需判断冲突
    void addCourse(vector<Course>& allCourses, StudentInfo& student) {

    }

    //显示学生的所选信息
    void displayMyCourses(const StudentInfo& student) const {

    }

    //保存选课信息 格式下面有讲
    void saveCourseSelection(const vector<StudentInfo>& students, const string& filename) const {

    }

    //加载选课信息，从selection文件中读取，根据students中的id
    void loadCourseSelection(vector<StudentInfo>& students, const vector<Course>& allCourses, const string& filename) {

    }
};

int main() {
    vector<Course> allCourses;
    vector<StudentInfo> students;
    Admin admin;
    Student student;

    const string coursesFilename = "courses";  //课程信息  课程编号/课程名/授课教师
    const string studentsFilename = "students"; //学生信息  用户名/密码/专业
    const string selectionFilename = "selection"; //学生选课信息文件  学生编号/所选，所选，所选。。。。

    admin.loadFromFile(allCourses, coursesFilename);

    ifstream studentFile(studentsFilename);

    if (studentFile.is_open()) {
        students.clear();

        string line;
        while (getline(studentFile, line)) {
            StudentInfo studentInfo;
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);
            if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
                studentInfo.username = line.substr(0, pos1);
                studentInfo.password = line.substr(pos1 + 1, pos2 - pos1 - 1);
                studentInfo.major = line.substr(pos2 + 1, pos3 - pos2 - 1);
                students.push_back(studentInfo);
            }
        }

        studentFile.close();
        cout << "从文件 " << studentsFilename << " 中读取学生信息成功。" << endl;
    } else {
        cout << "无法打开文件 " << studentsFilename << " 进行读取。" << endl;
    }

    // 新增: 从文件中加载学生选课信息
    student.loadCourseSelection(students, allCourses, selectionFilename);

    while (true) {
        cout << "\n1. 登录为管理员\n2. 登录为学生\n3. 退出\n选择操作（1/2/3）: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\n管理员登录成功！" << endl;
                while (true) {
                    cout << "\n1. 添加课程\n2. 删除课程\n3. 显示所有课程\n4. 保存课程信息到文件\n5. 返回上一级\n选择操作（1/2/3/4/5）: ";
                    cin >> choice;

                    switch (choice) {
                        case 1:
                            admin.addCourse(allCourses);
                            break;
                        case 2:
                            admin.deleteCourse(allCourses);
                            break;
                        case 3:
                            admin.displayAllCourses(allCourses);
                            break;
                        case 4:
                            admin.saveToFile(allCourses, coursesFilename);
                            break;
                        case 5:
                            cout << "\n返回上一级。\n";
                            break;
                        default:
                            cout << "无效的选项。" << endl;
                    }

                    if (choice == 5) {
                        break;
                    }
                }
                break;
            }

            case 2: {
                cout << "\n1. 登录\n2. 注册\n3. 返回上一级\n选择操作（1/2/3）: ";
                cin >> choice;

                switch (choice) {
                    case 1: {
                        string username, password;
                        if (student.login(students, username, password)) {
                            cout << "\n学生登录成功！" << endl;
                            while (true) {
                                cout << "\n1. 添加课程\n2. 显示我的课程\n3. 返回上一级\n选择操作（1/2/3）: ";
                                cin >> choice;

                                switch (choice) {
                                    case 1:
                                        student.addCourse(allCourses, students[0]);
                                        break;
                                    case 2:
                                        student.displayMyCourses(students[0]);
                                        break;
                                    case 3:
                                        cout << "\n返回上一级。\n";
                                        break;
                                    default:
                                        cout << "无效的选项。" << endl;
                                }

                                if (choice == 3) {
                                    break;
                                }
                            }
                        } else {
                            cout << "登录失败，用户名或密码错误。" << endl;
                        }
                        break;
                    }

                    case 2:
                        student.registerStudent(students);
                        break;

                    case 3:
                        cout << "\n返回上一级。\n";
                        break;

                    default:
                        cout << "无效的选项。" << endl;
                }

                break;
            }

            case 3:
                admin.saveToFile(allCourses, coursesFilename);
                // 保存学生信息到文件
                student.saveToFile(students, studentsFilename);
                // 保存学生选课信息到文件
                student.saveCourseSelection(students, selectionFilename);
                cout << "\n退出系统。" << endl;
                return 0;

            default:
                cout << "无效的选项。" << endl;
        }
    }

    return 0;
}
