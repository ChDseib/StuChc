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
    std::mt19937 gen;
public:
    Admin() : nextCourseId(1), gen(std::random_device{}()) {} // ���캯����ʼ���γ̱��Ϊ1�������������
// �� Admin ����������·������ڼ��γ̴����Ψһ��
    bool isCourseCodeUnique(const vector<Course>& courses, const string& courseCode) {
        return find_if(courses.begin(), courses.end(),
                       [courseCode](const Course& course) {
                           return course.courseCode == courseCode;
                       }) == courses.end();
    }

    // ��ӿγ���Ϣ ���/����/�ο���ʦ
    void addCourse(vector<Course>& courses) {
        Course course;
        std::uniform_int_distribution<int> dis(10000000, 99999999);

        do {
            course.courseCode = std::to_string(dis(gen));
        } while (!isCourseCodeUnique(courses, course.courseCode));
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t  ��ǰ����\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t   ������γ�����\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
       // cout<<"������γ����ƣ�";
        cin>>course.courseName;
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t   ��ǰ����\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t   �������ο���ʦ\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
       // cout<<"�������ο���ʦ��";

        cin>>course.teacher;
        courses.push_back(course);
    }

    void deleteCourse(vector<Course>& courses) {
        string courseCode;
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t  ��ǰ����\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t������Ҫɾ���Ŀγ̱��\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        //cout<<"������Ҫɾ���Ŀγ̱�ţ�";
        cin>>courseCode;

        auto it=remove_if(courses.begin(), courses.end(),
                            [courseCode]( Course& course) {
                                return course.courseCode==courseCode;
                            });

        if (it!=courses.end()) {
            courses.erase(it);
            printf("\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\tɾ���ɹ�!\t\t\t\t\t\t|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            printf("\n");
            //cout<<"ɾ���ɹ���"<<endl;
        } else {
            cout<<"δ�ҵ��γ̱��Ϊ"<<courseCode<<"�Ŀγ̡�"<<endl;
        }
    }


    void displayAllCourses(  vector<Course>& courses)   {

        printf("\n\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t   ȫ���γ�\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\"�γ̱��\t\t�γ�����\t\t�ο���ʦ\"\t\t\t|\n");
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
            }
            file.close();
           // cout<<"1��"<<endl;
        } else {
            cout<<"�޷����ļ�"<<filename<<"���б��档"<<endl;
        }
    }

    void loadFromFile(vector<Course>& courses,  string& filename) {
        ifstream file(filename); //�γ���Ϣ  �γ̱��/�γ���/�ڿν�ʦ
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

                    // �������γ̱��
                    int courseId=stoi(course.courseCode);
                    nextCourseId=max(nextCourseId, courseId+1);
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
private:
    int nextSelectionId; // ��¼ѧ��ѡ�ε���һ�����
public:
    bool login(  vector<StudentInfo>& students, string& username, string& password, int& stuid) {
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t��ǰ����:��¼\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t�������û���\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        //cout<<"�������û�����";
        cin>>username;
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t��ǰ����:��¼\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t����������\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
       // cout<<"���������룺";
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
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t��ǰ����:ע��\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t�������û���\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        //cout<<"�������û�����";
        cin>>student.username;
       // cout<<"���������룺";
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t��ǰ����:ע��\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t����������\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        cin>>student.password;
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t��ǰ����:ע��\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t������רҵ\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        //cout<<"������רҵ��";
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
            printf("\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t����ɹ�!\t\t\t\t\t\t|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            printf("\n");
           // cout<<"����ɹ���"<<endl;
        } else {
            cout<<"\t\t\t\t\t"<<"�޷����ļ�"<<filename<<"���б��档"<<endl;
        }
    }

    Student() : nextSelectionId(1) {} // ���캯����ʼ��ѡ�α��Ϊ1

    // ��ӿγ� ����ʾ���п�ѡ�γ� ѡ������жϳ�ͻ
    void addCourse(vector<Course>& allCourses, StudentInfo& student) {
        // ...
       // cout<<"��ѡ�γ����£�"<<endl;
        //cout<<"���\t�γ̱��\t�γ�����\t�ο���ʦ"<<endl;
        printf("\n\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t   ȫ���γ�\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\"�γ̱��\t\t�γ�����\t\t�ο���ʦ\"\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        for (int i=0; i < allCourses.size(); ++i) {
            cout<<"\t\t\t\t\t\t\t\t\t\t\t|\t\t   "<<allCourses[i].courseCode<<"\t\t"<<allCourses[i].courseName<<"\t\t"<<  allCourses[i].teacher<<"\t\t\t\t|"<<endl;
        }
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");

        int choice;
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t��ǰ����:ѡ��\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t��������Ҫ��ӵĿγ����\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        //cout<<"��������Ҫ��ӵĿγ����: ";
        cin>>choice;
        choice--;
        // ����ӿγ�֮ǰ���ȼ��selection.txt�ļ����Ƿ��Ѵ�����ѡ�γ�
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

        // �����ѡ�γ��Ƿ��Ѿ���ѧ���Ŀγ��б���
        for (int i=0; i<student.selectedCourses.size(); i++) {
            if (student.selectedCourses[i].courseName==allCourses[choice].courseName) {
                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t���Ѿ�ѡ�����ſΣ����ٴγ���\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
               // cout<<"���Ѿ�ѡ�����ſΣ����ٴγ���"<<endl;
                return;
            }
        }

        // ����ѡ�γ���ӵ�ѧ���Ŀγ��б��У�ʹ�ÿγ̴�����Ϊ���
        if (choice>=0&&choice < allCourses.size()) {
            student.selectedCourses.push_back(allCourses[choice]);
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\tѡ�γɹ�!\t\t\t\t\t\t|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
           // cout<<"ѡ�γɹ�!"<<endl;

            // ʹ�ÿγ̴�����Ϊѡ�α��
            student.selectedCourses.back().courseCode=allCourses[choice].courseCode;
        } else {
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t��Чѡ�����ٴγ���!\t\t\t\t|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            //cout<<"��Чѡ�����ٴγ���"<<endl;
        }
        
    }

    // ɾ���γ�
    void deleteCourse(vector<Course>& allCourses, StudentInfo& student) {
        int i;
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t��ǰ��ѡ�γ�\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        for(i=0; i<student.selectedCourses.size(); i++) {
            cout<<"\t\t\t\t\t\t\t\t\t\t\t|"<<"\t\t\t\t"<<i+1<<": "<<student.selectedCourses[i].courseName<<" by "<<student.selectedCourses[i].teacher<<"\t\t\t\t\t|\n";
        }

        int choice;
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t��������ɾ���γ̵����\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        //cout<<"��������ɾ���γ̵���ţ� ";
        cin>>choice;
        choice=choice - 1;

        if(choice>=0&&choice<student.selectedCourses.size()) {
            student.selectedCourses.erase(student.selectedCourses.begin()+choice);
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\tѡ��ɾ���ɹ�\t\t\t\t\t|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
           // cout<<"ѡ��ɾ���ɹ�!"<<endl;
        } else {
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t  ѡ����Ч�������ԡ�\t\t\t\t|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            //cout<<"ѡ����Ч�������ԡ�"<<endl;
        }
    }


    void displayMyCourses(  StudentInfo& student)   {
        printf("\n\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        cout<<"\t\t\t\t\t\t\t\t\t\t\t|"<<"\t\t\t\tѧ�� "<<student.username<<" ��ѡ�Ŀγ��У�\t\t\t\t|\n";
        for (  auto& course : student.selectedCourses) {
            cout<<"\t"<<"\t\t\t\t\t\t\t\t\t\t|"<<"\t\t�γ�����: "<<course.courseName<<"\t\t"<<" �γ̴���: "<<course.courseCode<<"\t\t\t|\n";
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
           // printf("\n");
          //  printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
           // printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t����ɹ�\t\t\t\t\t\t|\n");
           // printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
           // printf("\n");
            //cout<<"����ɹ���"<<endl;
        } else {
            cout<<"�޷����ļ�"<<filename<<"���б��档"<<endl;
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
        cout<<"���ļ�"<<studentsFilename<<"�ж�ȡѧ����Ϣ�ɹ���"<<endl;
    } else {
        cout<<"�޷����ļ�"<<studentsFilename<<"���ж�ȡ��"<<endl;
    }

    student.loadCourseSelection(students, allCourses, selectionFilename);

    while (true) {
        printf("\n\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t   ��¼����\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t��ѡ���¼��ɫ\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t1.��¼Ϊ����Ա\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t2.��¼Ϊѧ��\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t3.�˳�ϵͳ\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\tѡ�������1/2/3��\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
      //  cout<<"\n1. ��¼Ϊ����Ա\n2. ��¼Ϊѧ��\n3. �˳�\nѡ�������1/2/3��:";
        int choice;
        cin>>choice;

        if (cin.fail()) {
            cout<<"����������������֡�"<<endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;        }
        if (choice < 1 || choice > 3) {
            cout<<"������������뷶Χ�ڵ�ѡ�"<<endl;
            continue;
        }

        switch (choice) {
            case 1: {
                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t   ��ǰ����\t\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t   ���������Ա����\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                int password;
                cin>>password;
                if (password!=123456) {
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t  ������󣬵�¼ʧ�ܡ�\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                    //cout<<"������󣬵�¼ʧ�ܡ�"<<endl;
                    break;
                } else{
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t  ������ȷ����¼�ɹ���\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                  //  cout<<"������ȷ����¼�ɹ���"<<endl;
                }
                while (true) {
                    printf("\n\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t ����Ա����\t\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t��ѡ�����¹���\t\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t1. ��ӿγ�\t\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t2. ɾ���γ�\t\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t3. ��ʾ���пγ�\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t4. ����γ���Ϣ���ļ�\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t5. ������һ��\t\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\tѡ�������1/2/3/4/5��:\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                    //cout<<"\n\n2. ɾ���γ�\n3. ��ʾ���пγ�\n4. ����γ���Ϣ���ļ�\n5. ������һ��\nѡ�������1/2/3/4/5��:";
                    cin>>choice;
                    if (cin.fail()) {
                        cout<<"����������������֡�"<<endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        continue;        }
                    if (choice < 1 || choice > 5) {
                        cout<<"������������뷶Χ�ڵ�ѡ�"<<endl;
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
                printf("\n\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t   ѧ������\t\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t1. ��¼\t\t\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t2. ע��\t\t\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t3. ������һ��\t\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\tѡ�������1/2/3��\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
             //   cout<<"\n1. ��¼\n2. ע��\n3. ������һ��\nѡ�������1/2/3��:";
                cin>>choice;
                if (cin.fail()) {
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t  ����������������֡�\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                  //  cout<<"����������������֡�"<<endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;        }
                if (choice < 1 || choice > 3) {
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t  ������������뷶Χ�ڵ�ѡ�\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                   // cout<<"������������뷶Χ�ڵ�ѡ�"<<endl;
                    continue;
                }
                switch (choice) {
                    case 1: {
                        string username, password;
                        int stuid;
                        if (student.login(students, username, password, stuid)) {
                            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                            printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\tѧ����¼�ɹ���\t\t\t\t\t|\n");
                            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                            //cout<<"\nѧ����¼�ɹ���"<<endl;
                            while (true) {
                                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t   ѧ������\t\t\t\t\t|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t ��ѡ����\t\t\t\t\t|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t1. ��ӿγ�\t\t\t\t\t|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t2. ɾ���γ�\t\t\t\t\t|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t3. ��ʾ�ҵĿγ�\t\t\t\t|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t4. ������һ��\t\t\t\t\t|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\tѡ�������1/2/3/4��:\t\t\t\t|\n");
                                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                             //   cout<<"\n1. ��ӿγ�\n2. ɾ���γ�\n3. ��ʾ�ҵĿγ�\n4. ������һ��\nѡ�������1/2/3/4��:";
                                cin>>choice;
                                if (cin.fail()) {
                                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t����������������֣�\t\t\t\t|\n");
                                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                    //cout<<"����������������֡�"<<endl;
                                    cin.clear();
                                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    continue;        }
                                if (choice < 1 || choice > 4) {
                                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t  ������������뷶Χ�ڵ�ѡ�\t\t\t|\n");
                                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                    //cout<<"������������뷶Χ�ڵ�ѡ�"<<endl;
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
                                        cout<<"\n������һ����\n";
                                        break;
                                    default:
                                        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t    ��Ч��ѡ�\t\t\t\t\t|\n");
                                        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                        //cout<<"��Ч��ѡ�"<<endl;
                                }
                                if (choice==4) {
                                    break;
                                }
                            }
                        } else {
                            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                            printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t��¼ʧ�ܣ��û������������\t\t\t|\n");
                            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                           // cout<<"��¼ʧ�ܣ��û������������"<<endl;
                        }
                        break;
                    }
                    case 2:
                        student.registerStudent(students);
                        student.saveToFile(students, studentsFilename);
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
                student.saveToFile(students, studentsFilename);
                student.saveCourseSelection(students, selectionFilename);
                cout<<"\n�˳�ϵͳ��"<<endl;
                return 0;
            default:
                cout<<"��Ч��ѡ�"<<endl;
        }
    }

    return 0;
}
