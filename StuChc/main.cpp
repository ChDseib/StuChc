#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
//补充信息填在此处：

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
        Course course;
        cout<<"请输入课程编号：";
        cin>>course.courseCode;
        cout<<"请输入课程名称：";
        cin>>course.courseName;
        cout<<"请输入任课老师：";
        cin>>course.teacher;
        courses.push_back(course);
    }


    //删除课程信息
    void deleteCourse(vector<Course>& courses) {
        string courseCode;
        cout<<"请输入要删除的课程编号：";
        cin>>courseCode;
        for (size_t i=0; i<courses.size(); ++i) {
            if (courses[i].courseCode==courseCode) {
                courses.erase(courses.begin()+i);
                cout<<"删除成功。"<<endl;
                return;
            }
        }
        cout<<"未找到课程编号为"<<courseCode<<"的课程。"<<endl;
    }

    //显示所有课程信息
    void displayAllCourses(const vector<Course>& courses) const {
        cout<<"课程编号\t课程名称\t任课老师"<<endl;
        for (size_t i=0; i<courses.size(); ++i) {
            cout<<courses[i].courseCode<<"\t"<<courses[i].courseName<<"\t"<<courses[i].teacher<<endl;
        }
    }

    //将所增删的信息保存到本地
    void saveToFile(const vector<Course>& courses, const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (size_t i=0; i<courses.size(); ++i) {
                file<<courses[i].courseCode<<","<<courses[i].courseName<<","<<courses[i].teacher<<endl;
            }
            file.close();
            cout<<"保存成功。"<<endl;
        } else {
            cout<<"无法打开文件"<<filename<<"进行保存。"<<endl;
        }
    }

    //从本地加载课程信息
    void loadFromFile(vector<Course>& courses, const string& filename) {
        ifstream file(filename); //课程信息  课程编号/课程名/授课教师
        if (file.is_open()) {
            courses.clear();//
            string line;
            while (getline(file, line)) {
                Course course;
                size_t pos1=line.find(',');
                size_t pos2=line.find(',', pos1+1);
                if (pos1!=string::npos && pos2!=string::npos) {
                    course.courseCode=line.substr(0, pos1);
                    course.courseName=line.substr(pos1+1, pos2-pos1-1);
                    course.teacher=line.substr(pos2+1);
                    courses.push_back(course);
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
public:
    //登录 用户名/密码
    bool login(const vector<StudentInfo>& students, string& username, string& password) {
        cout<<"请输入用户名";
        cin>>username;
        cout<<"请输入密码：";
        cin>>password;
        for(int i=0;i<students.size();++i){
            if((students[i].username==username)&&(students[i].password==password)){

                return true;
            }
            else{
                return false;}
        }
    }

    //学生信息注册 用户名/密码/专业
    void registerStudent(vector<StudentInfo>& students) {
        StudentInfo student;
        cout<<"请输入用户名";
        cin>>student.username;
        cout<<"请输入密码：";
        cin>>student.password;
        cout<<"请输入专业：";
        cin>>student.major;
        students.push_back(student);
    }

    //保存学生信息
    void saveToFile(const vector<StudentInfo>& students, const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (size_t i=0; i<students.size(); ++i) {
                file<<students[i].username<<","<<students[i].password<<","<<students[i].major<<endl;
            }
            file.close();
            cout<<"保存成功。"<<endl;
        } else {
            cout<<"无法打开文件"<<filename<<"进行保存。"<<endl;
        }

    }
    //添加课程  先显示所有可选课程 选择后需判断冲突
    void addCourse(vector<Course>& allCourses, StudentInfo& student) {
        for(int i = 0; i < allCourses.size(); i++) {
            cout << i << ": " << allCourses[i].courseName << "      授课教师： " << allCourses[i].teacher << endl;
        }
        // 让学生选择课程
        int choice;
        cout << "请输入想要添加的课程编号: ";
        cin >> choice;
        // 将所选课程添加到学生的课程列表中
        if(choice >= 0 && choice < allCourses.size()) {
            student.selectedCourses.push_back(allCourses[choice]);
            cout << "课程添加成功!" << endl;
        } else {
            cout << "选择无效，请重试" << endl;
        }
    }

    void deleteCourse(vector<Course>& allCourses, StudentInfo& student) {
        for(int i = 0; i < student.selectedCourses.size(); i++) {
            cout << i << ": " << student.selectedCourses[i].courseName << "       授课教师： " << student.selectedCourses[i].teacher << endl;
        }
        int choice;
        cout << "请输入想要删除的课程编号: ";
        cin >> choice;
        // Check if the choice is within the range of selected courses
        if(choice >= 0 && choice < student.selectedCourses.size()) {
            student.selectedCourses.erase(student.selectedCourses.begin() + choice);
            cout << "选课删除成功!" << endl;
        } else {
            cout << "选择无效，请重试。" << endl;
        }
    }

    //显示学生的所选信息
    void displayMyCourses(const StudentInfo& student) const {
        std::cout << "学生 " << student.username << " 所选的课程有：\n";  //打印出学生的名字
        for (const auto &course: student.selectedCourses) {
            std::cout << "课程名称: " << course.courseName << ", 课程代码: " << course.courseCode
                      << '\n';   //遍历课程列表，打印出每一门课程的名称
        }
    }

    //保存选课信息 格式下面有讲
    void saveCourseSelection(const vector<StudentInfo>& students, const string& filename) const {
        ofstream file(filename);  // 创建一个输出文件流对象
        if (file.is_open()) {  // 检查文件是否成功打开
            for (size_t i = 0; i < students.size(); ++i) {  // 遍历每个学生
                for (size_t j = 0; j < students[i].selectedCourses.size(); ++j) {  // 遍历每个学生选择的课程
                    file << students[i].username << ","  // 将学生的用户名和他们所选课程的详细信息写入文件
                         << students[i].selectedCourses[j].courseCode << ","
                         << students[i].selectedCourses[j].courseName << ","
                         << students[i].selectedCourses[j].teacher << endl;
                }
            }
            file.close();   // 关闭文件
            cout << "保存成功。" << endl;
        } else {
            cout << "无法打开文件" << filename << "进行保存。" << endl;
        }
    }

    //加载选课信息，从selection文件中读取，根据students中的id
    void loadCourseSelection(vector<StudentInfo>& students, const vector<Course>& allCourses, const string& filename) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id, courseCode;
            getline(ss, id, ',');
            getline(ss, courseCode, ',');

            // Find the student and the course in the vectors
            for (auto &student: students) {
                if (student.username == id) {
                    for (const auto &course: allCourses) {
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
    const string coursesFilename ="courses.txt";  //课程信息  课程编号/课程名/授课教师
    const string studentsFilename ="students.txt"; //学生信息  用户名/密码/专业
    const string selectionFilename ="selection.txt"; //学生选课信息文件  学生编号/所选，所选，所选。。。。
    admin.loadFromFile(allCourses, coursesFilename); //从文件中加载课程信息
    ifstream studentFile(studentsFilename); //读取学生信息
    if (studentFile.is_open()) {
        students.clear(); //清空学生信息
        string line; //读取一行
        while (getline(studentFile, line)) { //读取一行
            StudentInfo studentInfo; //学生信息
            size_t pos1=line.find(','); //查找第一个逗号
            size_t pos2=line.find(',', pos1+1); //查找第二个逗号
            if (pos1!=string::npos && pos2!=string::npos) { //如果逗号都找到了
                studentInfo.username=line.substr(0, pos1); //用户名
                studentInfo.password=line.substr(pos1+1, pos2-pos1-1); //密码
                studentInfo.major=line.substr(pos2+1); //专业
                students.push_back(studentInfo); //添加到学生信息中
            }
        }
        studentFile.close(); //关闭文件
        cout<<"从文件"<<studentsFilename<<"中读取学生信息成功。"<<endl;//读取成功
    } else {
        cout<<"无法打开文件"<<studentsFilename<<"进行读取。"<<endl; //读取失败
    }

    // 从文件中加载学生选课信息
    student.loadCourseSelection(students, allCourses, selectionFilename);

    while (true) {
        cout<<"\n1. 登录为管理员\n2. 登录为学生\n3. 退出\n选择操作（1/2/3）:";
        int choice;
        cin>>choice;
        switch (choice) {
            case 1: {
                cout<<"\n管理员登录成功！"<<endl;
                while (true) {
                    cout<<"\n1. 添加课程\n2. 删除课程\n3. 显示所有课程\n4. 保存课程信息到文件\n5. 返回上一级\n选择操作（1/2/3/4/5）:";
                    cin>>choice;

                    switch (choice) {
                        case 1:
                            admin.addCourse(allCourses); //添加课程
                            admin.saveToFile(allCourses, coursesFilename);//保存课程信息到文件
                            break;
                        case 2:
                            admin.deleteCourse(allCourses);//删除课程
                            admin.saveToFile(allCourses, coursesFilename);//保存课程信息到文件
                            break;
                        case 3:
                            admin.displayAllCourses(allCourses);//显示所有课程
                            break;
                        case 4:
                            admin.saveToFile(allCourses, coursesFilename);//保存课程信息到文件
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
                switch (choice) {
                    case 1: {
                        string username, password;
                        if (student.login(students, username, password)) {
                            cout<<"\n学生登录成功！"<<endl;
                            while (true) {
                                cout<<"\n1. 添加课程\n2. 删除课程\n3. 显示我的课程\n4. 返回上一级\n选择操作（1/2/3/4）:";
                                cin>>choice;
                                switch (choice) {
                                    case 1:
                                        student.addCourse(allCourses, students[0]);
                                        break;
                                    case 2:
                                        student.deleteCourse(allCourses,students[0]);
                                        break;
                                    case 3:
                                        student.displayMyCourses(students[0]);
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
                        student.saveToFile(students, studentsFilename);//保存用户信息到文件
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
                // 保存学生信息到文件
                student.saveToFile(students, studentsFilename);
                // 保存学生选课信息到文件
                student.saveCourseSelection(students, selectionFilename);
                cout<<"\n退出系统。"<<endl;
                return 0;
            default:
                cout<<"无效的选项。"<<endl;
        }
    }

    return 0;
}