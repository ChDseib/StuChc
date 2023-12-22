#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

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
public:
    void addCourse(vector<Course>& courses) {
        Course course;
        cout << "请输入课程编号：";
        cin >> course.courseCode;
        cout << "请输入课程名称：";
        cin >> course.courseName;
        cout << "请输入任课老师：";
        cin >> course.teacher;
        courses.push_back(course);
    }

    void deleteCourse(vector<Course>& courses) {
        string courseCode;
        cout << "请输入要删除的课程编号：";
        cin >> courseCode;
        for (size_t i = 0; i < courses.size(); ++i) {
            if (courses[i].courseCode == courseCode) {
                courses.erase(courses.begin() + i);
                cout << "删除成功。" << endl;
                return;
            }
        }
        cout << "未找到课程编号为" << courseCode << "的课程。" << endl;
    }

    void displayAllCourses(const vector<Course>& courses) const {
        cout << "课程编号\t课程名称\t任课老师" << endl;
        for (size_t i = 0; i < courses.size(); ++i) {
            cout << courses[i].courseCode << "\t" << courses[i].courseName << "\t" << courses[i].teacher << endl;
        }
    }

    void saveToFile(const vector<Course>& courses, const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (size_t i = 0; i < courses.size(); ++i) {
                file << courses[i].courseCode << "," << courses[i].courseName << "," << courses[i].teacher << endl;
            }
            file.close();
            cout << "保存成功。" << endl;
        } else {
            cout << "无法打开文件" << filename << "进行保存。" << endl;
        }
    }

    void loadFromFile(vector<Course>& courses, const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            courses.clear();
            string line;
            while (getline(file, line)) {
                Course course;
                size_t pos1 = line.find(',');
                size_t pos2 = line.find(',', pos1 + 1);
                if (pos1 != string::npos && pos2 != string::npos) {
                    course.courseCode = line.substr(0, pos1);
                    course.courseName = line.substr(pos1 + 1, pos2 - pos1 - 1);
                    course.teacher = line.substr(pos2 + 1);
                    courses.push_back(course);
                }
            }
            file.close();
            cout << "从文件" << filename << "中读取课程信息成功。" << endl;
        } else {
            cout << "无法打开文件" << filename << "进行读取。" << endl;
        }
    }
};

class Student {
public:
    bool login(const vector<StudentInfo>& students, string& username, string& password, int& stuid) {
        cout << "请输入用户名：";
        cin >> username;
        cout << "请输入密码：";
        cin >> password;
        for (int i = 0; i < students.size(); ++i) {
            if ((students[i].username == username) && (students[i].password == password)) {
                stuid = i;
                return true;
            }
        }
        return false;
    }

    void registerStudent(vector<StudentInfo>& students) {
        StudentInfo student;
        cout << "请输入用户名：";
        cin >> student.username;
        cout << "请输入密码：";
        cin >> student.password;
        cout << "请输入专业：";
        cin >> student.major;
        students.push_back(student);
    }

    void saveToFile(const vector<StudentInfo>& students, const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (size_t i = 0; i < students.size(); ++i) {
                file << students[i].username << "," << students[i].password << "," << students[i].major << endl;
            }
            file.close();
            cout << "保存成功。" << endl;
        } else {
            cout << "无法打开文件" << filename << "进行保存。" << endl;
        }
    }

    void addCourse(vector<Course>& allCourses, StudentInfo& student) {
        for (int i = 0; i < allCourses.size(); i++) {
            cout << i << ": " << allCourses[i].courseName << " by " << allCourses[i].teacher << endl;
        }
        int choice;
        cout << "请输入想要添加的课程编号: ";
        cin >> choice;

        std::ifstream file("selection.txt");
        std::string line;
        bool courseExists = false;
        if (file.is_open()) {
            while (getline(file, line)) {
                if (line.find(allCourses[choice].courseName) != std::string::npos) {
                    courseExists = true;
                    break;
                }
            }
            file.close();
        }
        if (courseExists) {
            cout << "已有课程，选课失败" << endl;
            return;
        }



        if (choice >= 0 && choice < allCourses.size()) {
            student.selectedCourses.push_back(allCourses[choice]);
            cout << "选课成功!" << endl;
        } else {
            cout << "无效选择，再次尝试" << endl;
        }
    }

    void deleteCourse(vector<Course>& allCourses, StudentInfo& student) {
        int i;
        for (i = 0; i < student.selectedCourses.size(); i++) {
            cout << i + 1 << ": " << student.selectedCourses[i].courseName << " by " << student.selectedCourses[i].teacher << endl;
        }
        int choice;
        cout << "输入你想删除课程的序号： ";
        cin >> choice;
        choice = choice - 1;

        if (choice >= 0 && choice < student.selectedCourses.size()) {
            student.selectedCourses.erase(student.selectedCourses.begin() + choice);
            cout << "选课删除成功!" << endl;
        } else {
            cout << "选择无效，请重试。" << endl;
        }
    }

    void displayMyCourses(const StudentInfo& student) const {
        std::cout << "学生 " << student.username << " 所选的课程有：\n";
        for (const auto& course : student.selectedCourses) {
            std::cout << "课程名称: " << course.courseName << ", 课程代码: " << course.courseCode << '\n';
        }
    }

    void saveCourseSelection(const vector<StudentInfo>& students, const string& filename) const {
        ofstream file("selection.txt");
        if (file.is_open()) {
            for (size_t i = 0; i < students.size(); ++i) {
                for (size_t j = 0; j < students[i].selectedCourses.size(); ++j) {
                    file << students[i].username << ","
                         << students[i].selectedCourses[j].courseCode << ","
                         << students[i].selectedCourses[j].courseName << ","
                         << students[i].selectedCourses[j].teacher << endl;
                }
            }
            file.close();
            cout << "保存成功。" << endl;
        } else {
            cout << "无法打开文件" << filename << "进行保存。" << endl;
        }
    }

    void loadCourseSelection(vector<StudentInfo>& students, const vector<Course>& allCourses, const string& filename) {
        ifstream file("selection.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id, courseCode;
            getline(ss, id, ',');
            getline(ss, courseCode, ',');

            for (auto& student : students) {
                if (student.username == id) {
                    for (const auto& course : allCourses) {
                        if (course.courseCode == courseCode) {
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
    vector<Course> allCourses;
    vector<StudentInfo> students;
    Admin admin;
    Student student;
    const string coursesFilename = "courses.txt";
    const string studentsFilename = "students.txt";
    const string selectionFilename = "selection.txt";
    admin.loadFromFile(allCourses, coursesFilename);
    ifstream studentFile(studentsFilename);
    if (studentFile.is_open()) {
        students.clear();
        string line;
        while (getline(studentFile, line)) {
            StudentInfo studentInfo;
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            if (pos1 != string::npos && pos2 != string::npos) {
                studentInfo.username = line.substr(0, pos1);
                studentInfo.password = line.substr(pos1 + 1, pos2 - pos1 - 1);
                studentInfo.major = line.substr(pos2 + 1);
                students.push_back(studentInfo);
            }
        }
        studentFile.close();
        cout << "从文件" << studentsFilename << "中读取学生信息成功。" << endl;
    } else {
        cout << "无法打开文件" << studentsFilename << "进行读取。" << endl;
    }

    student.loadCourseSelection(students, allCourses, selectionFilename);

    while (true) {
        cout << "\n1. 登录为管理员\n2. 登录为学生\n3. 退出\n选择操作（1/2/3）:";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: {
                cout << "\n管理员登录成功！" << endl;
                while (true) {
                    cout << "\n1. 添加课程\n2. 删除课程\n3. 显示所有课程\n4. 保存课程信息到文件\n5. 返回上一级\n选择操作（1/2/3/4/5）:";
                    cin >> choice;

                    switch (choice) {
                        case 1:
                            admin.addCourse(allCourses);
                            admin.saveToFile(allCourses, coursesFilename);
                            break;
                        case 2:
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
                cout << "\n1. 登录\n2. 注册\n3. 返回上一级\n选择操作（1/2/3）:";
                cin >> choice;
                switch (choice) {
                    case 1: {
                        string username, password;
                        int stuid;
                        if (student.login(students, username, password, stuid)) {
                            cout << "\n学生登录成功！" << endl;
                            while (true) {
                                cout << "\n1. 添加课程\n2. 删除课程\n3. 显示我的课程\n4. 返回上一级\n选择操作（1/2/3/4）:";
                                cin >> choice;
                                switch (choice) {
                                    case 1:
                                        student.addCourse(allCourses, students[stuid]);
                                        student.saveCourseSelection(students, selectionFilename);
                                        break;
                                    case 2:
                                        student.deleteCourse(allCourses, students[stuid]);
                                        student.saveCourseSelection(students, selectionFilename);
                                        break;
                                    case 3:
                                        student.displayMyCourses(students[stuid]);
                                        break;
                                    case 4:
                                        cout << "\n返回上一级。\n";
                                        break;
                                    default:
                                        cout << "无效的选项。" << endl;
                                }
                                if (choice == 4) {
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
                        student.saveToFile(students, studentsFilename);
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
                student.saveToFile(students, studentsFilename);
                student.saveCourseSelection(students, selectionFilename);
                cout << "\n退出系统。" << endl;
                return 0;
            default:
                cout << "无效的选项。" << endl;
        }
    }

    return 0;
}
