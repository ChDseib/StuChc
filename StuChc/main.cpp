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
        cout << "������γ̱�ţ�";
        cin >> course.courseCode;
        cout << "������γ����ƣ�";
        cin >> course.courseName;
        cout << "�������ο���ʦ��";
        cin >> course.teacher;
        courses.push_back(course);
    }

    void deleteCourse(vector<Course>& courses) {
        string courseCode;
        cout << "������Ҫɾ���Ŀγ̱�ţ�";
        cin >> courseCode;
        for (size_t i = 0; i < courses.size(); ++i) {
            if (courses[i].courseCode == courseCode) {
                courses.erase(courses.begin() + i);
                cout << "ɾ���ɹ���" << endl;
                return;
            }
        }
        cout << "δ�ҵ��γ̱��Ϊ" << courseCode << "�Ŀγ̡�" << endl;
    }

    void displayAllCourses(const vector<Course>& courses) const {
        cout << "�γ̱��\t�γ�����\t�ο���ʦ" << endl;
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
            cout << "����ɹ���" << endl;
        } else {
            cout << "�޷����ļ�" << filename << "���б��档" << endl;
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
            cout << "���ļ�" << filename << "�ж�ȡ�γ���Ϣ�ɹ���" << endl;
        } else {
            cout << "�޷����ļ�" << filename << "���ж�ȡ��" << endl;
        }
    }
};

class Student {
public:
    bool login(const vector<StudentInfo>& students, string& username, string& password, int& stuid) {
        cout << "�������û�����";
        cin >> username;
        cout << "���������룺";
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
        cout << "�������û�����";
        cin >> student.username;
        cout << "���������룺";
        cin >> student.password;
        cout << "������רҵ��";
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
            cout << "����ɹ���" << endl;
        } else {
            cout << "�޷����ļ�" << filename << "���б��档" << endl;
        }
    }

    void addCourse(vector<Course>& allCourses, StudentInfo& student) {
        for (int i = 0; i < allCourses.size(); i++) {
            cout << i << ": " << allCourses[i].courseName << " by " << allCourses[i].teacher << endl;
        }
        int choice;
        cout << "��������Ҫ��ӵĿγ̱��: ";
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
            cout << "���пγ̣�ѡ��ʧ��" << endl;
            return;
        }



        if (choice >= 0 && choice < allCourses.size()) {
            student.selectedCourses.push_back(allCourses[choice]);
            cout << "ѡ�γɹ�!" << endl;
        } else {
            cout << "��Чѡ���ٴγ���" << endl;
        }
    }

    void deleteCourse(vector<Course>& allCourses, StudentInfo& student) {
        int i;
        for (i = 0; i < student.selectedCourses.size(); i++) {
            cout << i + 1 << ": " << student.selectedCourses[i].courseName << " by " << student.selectedCourses[i].teacher << endl;
        }
        int choice;
        cout << "��������ɾ���γ̵���ţ� ";
        cin >> choice;
        choice = choice - 1;

        if (choice >= 0 && choice < student.selectedCourses.size()) {
            student.selectedCourses.erase(student.selectedCourses.begin() + choice);
            cout << "ѡ��ɾ���ɹ�!" << endl;
        } else {
            cout << "ѡ����Ч�������ԡ�" << endl;
        }
    }

    void displayMyCourses(const StudentInfo& student) const {
        std::cout << "ѧ�� " << student.username << " ��ѡ�Ŀγ��У�\n";
        for (const auto& course : student.selectedCourses) {
            std::cout << "�γ�����: " << course.courseName << ", �γ̴���: " << course.courseCode << '\n';
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
            cout << "����ɹ���" << endl;
        } else {
            cout << "�޷����ļ�" << filename << "���б��档" << endl;
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
        cout << "���ļ�" << studentsFilename << "�ж�ȡѧ����Ϣ�ɹ���" << endl;
    } else {
        cout << "�޷����ļ�" << studentsFilename << "���ж�ȡ��" << endl;
    }

    student.loadCourseSelection(students, allCourses, selectionFilename);

    while (true) {
        cout << "\n1. ��¼Ϊ����Ա\n2. ��¼Ϊѧ��\n3. �˳�\nѡ�������1/2/3��:";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: {
                cout << "\n����Ա��¼�ɹ���" << endl;
                while (true) {
                    cout << "\n1. ��ӿγ�\n2. ɾ���γ�\n3. ��ʾ���пγ�\n4. ����γ���Ϣ���ļ�\n5. ������һ��\nѡ�������1/2/3/4/5��:";
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
                            cout << "\n������һ����\n";
                            break;
                        default:
                            cout << "��Ч��ѡ�" << endl;
                    }

                    if (choice == 5) {
                        break;
                    }
                }
                break;
            }

            case 2: {
                cout << "\n1. ��¼\n2. ע��\n3. ������һ��\nѡ�������1/2/3��:";
                cin >> choice;
                switch (choice) {
                    case 1: {
                        string username, password;
                        int stuid;
                        if (student.login(students, username, password, stuid)) {
                            cout << "\nѧ����¼�ɹ���" << endl;
                            while (true) {
                                cout << "\n1. ��ӿγ�\n2. ɾ���γ�\n3. ��ʾ�ҵĿγ�\n4. ������һ��\nѡ�������1/2/3/4��:";
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
                                        cout << "\n������һ����\n";
                                        break;
                                    default:
                                        cout << "��Ч��ѡ�" << endl;
                                }
                                if (choice == 4) {
                                    break;
                                }
                            }
                        } else {
                            cout << "��¼ʧ�ܣ��û������������" << endl;
                        }
                        break;
                    }
                    case 2:
                        student.registerStudent(students);
                        student.saveToFile(students, studentsFilename);
                        break;
                    case 3:
                        cout << "\n������һ����\n";
                        break;
                    default:
                        cout << "��Ч��ѡ�" << endl;
                }
                break;
            }

            case 3:
                admin.saveToFile(allCourses, coursesFilename);
                student.saveToFile(students, studentsFilename);
                student.saveCourseSelection(students, selectionFilename);
                cout << "\n�˳�ϵͳ��" << endl;
                return 0;
            default:
                cout << "��Ч��ѡ�" << endl;
        }
    }

    return 0;
}
