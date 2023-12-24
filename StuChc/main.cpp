#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

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
public:
    Admin() : nextCourseId(1) {} // 构造函数初始化课程编号为1

    // 添加课程信息 编号/名称/任课老师
    void addCourse(vector<Course>& courses) {
        Course course;
        course.courseCode=to_string(nextCourseId++); // 使用当前编号，然后递增
        cout<<"请输入课程名称：";
        cin>>course.courseName;
        cout<<"请输入任课老师：";
        cin>>course.teacher;
        courses.push_back(course);
    }

    void deleteCourse(vector<Course>& courses) {
        string courseCode;
        cout<<"请输入要删除的课程编号：";
        cin>>courseCode;

        auto it=remove_if(courses.begin(), courses.end(),
                            [courseCode]( Course& course) {
                                return course.courseCode==courseCode;
                            });

        if (it!=courses.end()) {
            courses.erase(it);
            cout<<"删除成功。"<<endl;
        } else {
            cout<<"未找到课程编号为"<<courseCode<<"的课程。"<<endl;
        }
    }


    void displayAllCourses(  vector<Course>& courses)   {
        cout<<"课程编号\t课程名称\t任课老师"<<endl;
        for (int i=0; i<courses.size(); ++i) {
            cout<<courses[i].courseCode<<"\t"<<courses[i].courseName<<"\t"<<courses[i].teacher<<endl;
        }
    }

    void saveToFile(  vector<Course>& courses,   string& filename)   {
        ofstream file(filename);
        if (file.is_open()) {
            for (int i=0; i<courses.size(); ++i) {
                file<<courses[i].courseCode<<","<<courses[i].courseName<<","<<courses[i].teacher<<endl;
            }
            file.close();
            cout<<"保存成功。"<<endl;
        } else {
            cout<<"无法打开文件"<<filename<<"进行保存。"<<endl;
        }
    }

    void loadFromFile(vector<Course>& courses,  string& filename) {
        ifstream file(filename); //课程信息  课程编号/课程名/授课教师
        if (file.is_open()) {
            courses.clear();//
            string line;
            while (getline(file, line)) {
                Course course;
                int pos1=line.find(',');
                int pos2=line.find(',', pos1+1);
                if (pos1!=string::npos&&pos2!=string::npos) {
                    course.courseCode=line.substr(0, pos1);
                    course.courseName=line.substr(pos1+1, pos2 - pos1 - 1);
                    course.teacher=line.substr(pos2+1);
                    courses.push_back(course);

                    // 更新最大课程编号
                    int courseId=stoi(course.courseCode);
                    nextCourseId=max(nextCourseId, courseId+1);
                }
            }
            file.close();
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
        cout<<"请输入用户名：";
        cin>>username;
        cout<<"请输入密码：";
        cin>>password;
        for (int i=0; i<students.size(); ++i) {
            if ((students[i].username==username)&&(students[i].password==password)) {
                stuid=i;
                return true;
            }
        }
        return false;
    }

    void registerStudent(vector<StudentInfo>& students) {
        StudentInfo student;
        cout<<"请输入用户名：";
        cin>>student.username;
        cout<<"请输入密码：";
        cin>>student.password;
        cout<<"请输入专业：";
        cin>>student.major;
        students.push_back(student);
    }

    void saveToFile(  vector<StudentInfo>& students,   string& filename)   {
        ofstream file(filename);
        if (file.is_open()) {
            for (int i=0; i<students.size(); ++i) {
                file<<students[i].username<<","<<students[i].password<<","<<students[i].major<<endl;
            }
            file.close();
            cout<<"保存成功。"<<endl;
        } else {
            cout<<"无法打开文件"<<filename<<"进行保存。"<<endl;
        }
    }

    Student() : nextSelectionId(1) {} // 构造函数初始化选课编号为1

    // 添加课程 先显示所有可选课程 选择后需判断冲突
    void addCourse(vector<Course>& allCourses, StudentInfo& student) {
        // ...
        cout<<"可选课程如下："<<endl;
        cout<<"序号\t课程编号\t课程名称\t任课老师"<<endl;
        for (int i=0; i < allCourses.size(); ++i) {
            cout<<i+1<<"\t"<<allCourses[i].courseCode<<"\t"<<allCourses[i].courseName<<"\t"<<allCourses[i].teacher<<endl;
        }

        int choice;
        cout<<"请输入想要添加的课程序号: ";
        cin>>choice;
        choice--;
        // 在添加课程之前，先检查selection.txt文件中是否已存在所选课程
        std::ifstream file("selection.txt");
        std::string line;
        bool courseExists=false;
        if (file.is_open()) {
            while (getline(file, line)) {
                if (line.find(allCourses[choice].courseName)!=std::string::npos) {
                    courseExists=true;
                    break;
                }
            }
            file.close();
        }

        // 检查所选课程是否已经在学生的课程列表中
        for (int i=1; i<student.selectedCourses.size(); i++) {
            if (student.selectedCourses[i].courseName==allCourses[choice].courseName) {
                cout<<"你已经选了这门课，请再次尝试"<<endl;
                return;
            }
        }

        // 将所选课程添加到学生的课程列表中，使用课程代码作为编号
        if (choice>=0&&choice < allCourses.size()) {
            student.selectedCourses.push_back(allCourses[choice]);
            cout<<"选课成功!"<<endl;

            // 使用课程代码作为选课编号
            student.selectedCourses.back().courseCode=allCourses[choice].courseCode;
        } else {
            cout<<"无效选择，请再次尝试"<<endl;
        }
        
    }

    // 删除课程
    void deleteCourse(vector<Course>& allCourses, StudentInfo& student) {
        int i;
        for(i=0; i<student.selectedCourses.size(); i++) {
            cout<<i+1<<": "<<student.selectedCourses[i].courseName<<" by "<<student.selectedCourses[i].teacher<<endl;
        }

        int choice;
        cout<<"输入你想删除课程的序号： ";
        cin>>choice;
        choice=choice - 1;

        if(choice>=0&&choice<student.selectedCourses.size()) {
            student.selectedCourses.erase(student.selectedCourses.begin()+choice);
            cout<<"选课删除成功!"<<endl;
        } else {
            cout<<"选择无效，请重试。"<<endl;
        }
    }


    void displayMyCourses(  StudentInfo& student)   {
        std::cout<<"学生 "<<student.username<<" 所选的课程有：\n";
        for (  auto& course : student.selectedCourses) {
            std::cout<<"课程名称: "<<course.courseName<<", 课程代码: "<<course.courseCode<<'\n';
        }
    }

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
            cout<<"保存成功。"<<endl;
        } else {
            cout<<"无法打开文件"<<filename<<"进行保存。"<<endl;
        }
    }


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
    vector<Course> allCourses;
    vector<StudentInfo> students;
    Admin admin;
    Student student;
    string coursesFilename="courses.txt";
    string studentsFilename="students.txt";
    string selectionFilename="selection.txt";
    admin.loadFromFile(allCourses, coursesFilename);
    ifstream studentFile(studentsFilename);
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
        cout<<"\n1. 登录为管理员\n2. 登录为学生\n3. 退出\n选择操作（1/2/3）:";
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
                cout<<"请输入管理员密码";
                int password;
                cin>>password;
                if (password!=123456) {
                    cout<<"密码错误，登录失败。"<<endl;
                    break;
                } else{
                    cout<<"密码正确，登录成功。"<<endl;
                }
                while (true) {
                    cout<<"\n1. 添加课程\n2. 删除课程\n3. 显示所有课程\n4. 保存课程信息到文件\n5. 返回上一级\n选择操作（1/2/3/4/5）:";
                    cin>>choice;
                    if (cin.fail()) {
                        cout<<"输入错误，请输入数字。"<<endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
                cout<<"\n1. 登录\n2. 注册\n3. 返回上一级\n选择操作（1/2/3）:";
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
                        string username, password;
                        int stuid;
                        if (student.login(students, username, password, stuid)) {
                            cout<<"\n学生登录成功！"<<endl;
                            while (true) {
                                cout<<"\n1. 添加课程\n2. 删除课程\n3. 显示我的课程\n4. 返回上一级\n选择操作（1/2/3/4）:";
                                cin>>choice;
                                if (cin.fail()) {
                                    cout<<"输入错误，请输入数字。"<<endl;
                                    cin.clear();
                                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    continue;        }
                                if (choice < 1 || choice > 4) {
                                    cout<<"输入错误，请输入范围内的选项。"<<endl;
                                    continue;
                                }
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
                                        cout<<"\n返回上一级。\n";
                                        break;
                                    default:
                                        cout<<"无效的选项。"<<endl;
                                }
                                if (choice==4) {
                                    break;
                                }
                            }
                        } else {
                            cout<<"登录失败，用户名或密码错误。"<<endl;
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
