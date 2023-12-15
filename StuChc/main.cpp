#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//������Ϣ���ڴ˴���

using namespace std;

struct Course {
    string courseCode;//�γ̱��
    string courseName;//�γ�����
    string teacher;//�ڿν�ʦ
};

struct StudentInfo {
    string username;//�û���
    string password;//����
    string major;//רҵ
    vector<Course> selectedCourses;
};

class Admin {
public:
    //��ӿγ���Ϣ  ���/����/�ο���ʦ
    void addCourse(vector<Course>& courses) {
        Course course;
        cout<<"������γ̱�ţ�";
        cin>>course.courseCode;
        cout<<"������γ����ƣ�";
        cin>>course.courseName;
        cout<<"�������ο���ʦ��";
        cin>>course.teacher;
        courses.push_back(course);
    }


    //ɾ���γ���Ϣ
    void deleteCourse(vector<Course>& courses) {
        string courseCode;
        cout<<"������Ҫɾ���Ŀγ̱�ţ�";
        cin>>courseCode;
        for (size_t i=0; i<courses.size(); ++i) {
            if (courses[i].courseCode==courseCode) {
                courses.erase(courses.begin()+i);
                cout<<"ɾ���ɹ���"<<endl;
                return;
            }
        }
        cout<<"δ�ҵ��γ̱��Ϊ"<<courseCode<<"�Ŀγ̡�"<<endl;
    }

    //��ʾ���пγ���Ϣ
    void displayAllCourses(const vector<Course>& courses) const {
        cout<<"�γ̱��\t�γ�����\t�ο���ʦ"<<endl;
        for (size_t i=0; i<courses.size(); ++i) {
            cout<<courses[i].courseCode<<"\t"<<courses[i].courseName<<"\t"<<courses[i].teacher<<endl;
        }
    }

    //������ɾ����Ϣ���浽����
    void saveToFile(const vector<Course>& courses, const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (size_t i=0; i<courses.size(); ++i) {
                file<<courses[i].courseCode<<","<<courses[i].courseName<<","<<courses[i].teacher<<endl;
            }
            file.close();
            cout<<"����ɹ���"<<endl;
        } else {
            cout<<"�޷����ļ�"<<filename<<"���б��档"<<endl;
        }
    }

    //�ӱ��ؼ��ؿγ���Ϣ
    void loadFromFile(vector<Course>& courses, const string& filename) {
        ifstream file(filename); //�γ���Ϣ  �γ̱��/�γ���/�ڿν�ʦ
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
            cout<<"���ļ�"<<filename<<"�ж�ȡ�γ���Ϣ�ɹ���"<<endl;
        } else {
            cout<<"�޷����ļ�"<<filename<<"���ж�ȡ��"<<endl;
        }
    }
};

class Student {
public:
    //��¼ �û���/����
    bool login(const vector<StudentInfo>& students, string& username, string& password) {

    }

    //ѧ����Ϣע�� �û���/����/רҵ
    void registerStudent(vector<StudentInfo>& students) {

    }

    //����ѧ����Ϣ
    void saveToFile(const vector<StudentInfo>& students, const string& filename) const {

    }
    //��ӿγ�  ����ʾ���п�ѡ�γ� ѡ������жϳ�ͻ
    void addCourse(vector<Course>& allCourses, StudentInfo& student) {

    }

    //��ʾѧ������ѡ��Ϣ
    void displayMyCourses(const StudentInfo& student) const {
        std::cout << "ѧ�� " << student.username << " ��ѡ�Ŀγ��У�\n";  //��ӡ��ѧ��������
        for (const auto& course : student.courses) {
            std::cout << "�γ�����: " << course.courseName << ", �γ̴���: " << course.courseCode << '\n';          //�����γ��б���ӡ��ÿһ�ſγ̵�����
    }

    //����ѡ����Ϣ ��ʽ�����н�
    void saveCourseSelection(const vector<StudentInfo>& students, const string& filename) const {

    }

    //����ѡ����Ϣ����selection�ļ��ж�ȡ������students�е�id
    void loadCourseSelection(vector<StudentInfo>& students, const vector<Course>& allCourses, const string& filename) {

    }
};

int main() {
    vector<Course> allCourses;
    vector<StudentInfo> students;
    Admin admin;
    Student student;
    const string coursesFilename ="courses.txt";  //�γ���Ϣ  �γ̱��/�γ���/�ڿν�ʦ
    const string studentsFilename ="students.txt"; //ѧ����Ϣ  �û���/����/רҵ
    const string selectionFilename ="selection.txt"; //ѧ��ѡ����Ϣ�ļ�  ѧ�����/��ѡ����ѡ����ѡ��������
    admin.loadFromFile(allCourses, coursesFilename); //���ļ��м��ؿγ���Ϣ
    ifstream studentFile(studentsFilename); //��ȡѧ����Ϣ
    if (studentFile.is_open()) {
        students.clear(); //���ѧ����Ϣ
        string line; //��ȡһ��
        while (getline(studentFile, line)) { //��ȡһ��
            StudentInfo studentInfo; //ѧ����Ϣ
            size_t pos1=line.find(','); //���ҵ�һ������
            size_t pos2=line.find(',', pos1+1); //���ҵڶ�������
            size_t pos3=line.find(',', pos2+1); //���ҵ���������
            if (pos1!=string::npos && pos2!=string::npos && pos3!=string::npos) { //����������Ŷ��ҵ���
                studentInfo.username=line.substr(0, pos1); //�û���
                studentInfo.password=line.substr(pos1+1, pos2-pos1-1); //����
                studentInfo.major=line.substr(pos2+1, pos3-pos2-1); //רҵ
                students.push_back(studentInfo); //��ӵ�ѧ����Ϣ��
            }
        }
        studentFile.close(); //�ر��ļ�
        cout<<"���ļ�"<<studentsFilename<<"�ж�ȡѧ����Ϣ�ɹ���"<<endl;//��ȡ�ɹ�
    } else {
        cout<<"�޷����ļ�"<<studentsFilename<<"���ж�ȡ��"<<endl; //��ȡʧ��
    }

    // ���ļ��м���ѧ��ѡ����Ϣ
    student.loadCourseSelection(students, allCourses, selectionFilename);

    while (true) {
        cout<<"\n1. ��¼Ϊ����Ա\n2. ��¼Ϊѧ��\n3. �˳�\nѡ�������1/2/3��:";
        int choice;
        cin>>choice;
        switch (choice) {
            case 1: {
                cout<<"\n����Ա��¼�ɹ���"<<endl;
                while (true) {
                    cout<<"\n1. ��ӿγ�\n2. ɾ���γ�\n3. ��ʾ���пγ�\n4. ����γ���Ϣ���ļ�\n5. ������һ��\nѡ�������1/2/3/4/5��:";
                    cin>>choice;

                    switch (choice) {
                        case 1:
                            admin.addCourse(allCourses); //��ӿγ�
                            break;
                        case 2:
                            admin.deleteCourse(allCourses);//ɾ���γ�
                            break;
                        case 3:
                            admin.displayAllCourses(allCourses);//��ʾ���пγ�
                            break;
                        case 4:
                            admin.saveToFile(allCourses, coursesFilename);//����γ���Ϣ���ļ�
                            break;
                        case 5:
                            cout<<"\n������һ����\n";
                            break;
                        default:
                            cout<<"��Ч��ѡ�"<<endl;
                    }

                    if (choice==5) {
                        break;
                    }
                }
                break;
            }

            case 2: {
                cout<<"\n1. ��¼\n2. ע��\n3. ������һ��\nѡ�������1/2/3��:";
                cin>>choice;
                switch (choice) {
                    case 1: {
                        string username, password;
                        if (student.login(students, username, password)) {
                            cout<<"\nѧ����¼�ɹ���"<<endl;
                            while (true) {
                                cout<<"\n1. ��ӿγ�\n2. ��ʾ�ҵĿγ�\n3. ������һ��\nѡ�������1/2/3��:";
                                cin>>choice;
                                switch (choice) {
                                    case 1:
                                        student.addCourse(allCourses, students[0]);
                                        break;
                                    case 2:
                                        student.displayMyCourses(students[0]);
                                        break;
                                    case 3:
                                        cout<<"\n������һ����\n";
                                        break;
                                    default:
                                        cout<<"��Ч��ѡ�"<<endl;
                                }
                                if (choice==3) {
                                    break;
                                }
                            }
                        } else {
                            cout<<"��¼ʧ�ܣ��û������������"<<endl;
                        }
                        break;
                    }
                    case 2:
                        student.registerStudent(students);
                        break;
                    case 3:
                        cout<<"\n������һ����\n";
                        break;
                    default:
                        cout<<"��Ч��ѡ�"<<endl;
                }
                break;
            }

            case 3:
                admin.saveToFile(allCourses, coursesFilename);
                // ����ѧ����Ϣ���ļ�
                student.saveToFile(students, studentsFilename);
                // ����ѧ��ѡ����Ϣ���ļ�
                student.saveCourseSelection(students, selectionFilename);
                cout<<"\n�˳�ϵͳ��"<<endl;
                return 0;
            default:
                cout<<"��Ч��ѡ�"<<endl;
        }
    }

    return 0;
}
