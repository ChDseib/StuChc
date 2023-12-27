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
    std::mt19937 gen;// �����������
public:
    Admin() : nextCourseId(1), gen(std::random_device{}()) {}// ���캯����ʼ���γ̱��Ϊ1  ��ʼ�������������
   //���γ̴����Ψһ��
    bool isCourseCodeUnique(const vector<Course>& courses, const string& courseCode) {
        return find_if(courses.begin(), courses.end(),
                       [courseCode](const Course& course) {
                           return course.courseCode == courseCode;
                       }) == courses.end();  // ����γ̱���ڿγ��б��в����ڣ��򷵻�true
    }

    // ��ӿγ���Ϣ ���/����/�ο���ʦ
    void addCourse(vector<Course>& courses) {
        Course course;
        //���ɷ�Χ��10000000-99999999֮��������/��λ��
        std::uniform_int_distribution<int> dis(10000000, 99999999);
        // ����Ψһ�Ŀγ̱��
        do {
            course.courseCode = std::to_string(dis(gen)); // �������ת��Ϊ�ַ���
        } while (!isCourseCodeUnique(courses, course.courseCode)); // ���γ̱���Ƿ�Ψһ
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t  ��ǰ����\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t   ������γ�����\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        cin>>course.courseName;
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t   ��ǰ����\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t   �������ο���ʦ\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        cin>>course.teacher;
        courses.push_back(course);
    }

    void deleteCourse(vector<Course>& courses) {
        string courseCode;
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t  ��ǰ����\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t������Ҫɾ���Ŀγ̱��\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        cin>>courseCode;
        auto it=remove_if(courses.begin(), courses.end(),
                            [courseCode]( Course& course) {
                                return course.courseCode==courseCode;
                            });// ɾ���γ̱��ΪcourseCode�Ŀγ�
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
            }// ����γ���Ϣ���ļ�
            file.close();
        } else {
            cout<<"�޷����ļ�"<<filename<<"���б��档"<<endl;
        }
    }

    void loadFromFile(vector<Course>& courses,  string& filename) {
        ifstream file(filename); //�γ���Ϣ  �γ̱��/�γ���/�ڿν�ʦ
        if (file.is_open()) {
            courses.clear();// ��տγ��б�
            string line;// ���ж�ȡ�γ���Ϣ
            while (getline(file, line)) {
                Course course;
                int pos1=line.find(','); // ���ҵ�һ�����ŵ�λ��
                int pos2=line.find(',', pos1+1);// ���ҵڶ������ŵ�λ��
                if (pos1!=string::npos&&pos2!=string::npos) {
                    course.courseCode=line.substr(0, pos1);// �γ̱��
                    course.courseName=line.substr(pos1+1, pos2 - pos1 - 1);// �γ�����
                    course.teacher=line.substr(pos2+1);
                    courses.push_back(course);

                    // �������γ̱��
                    int courseId=stoi(course.courseCode);
                    nextCourseId=max(nextCourseId, courseId+1);
                }
            }
            file.close();   // ���ļ��ж�ȡ�γ���Ϣ
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
        cin>>username;
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t��ǰ����:��¼\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t����������\t\t\t\t\t|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        cin>>password;
        for (int i=0; i<students.size(); ++i) {
            if ((students[i].username==username)&&(students[i].password==password)) {
                stuid=i;
                return true;
            } // ����û����������Ƿ�ƥ��
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
        cin>>student.username;
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
        cin>>student.major;
        students.push_back(student); // ��ѧ����Ϣ��ӵ�ѧ���б���
    }

    void saveToFile(  vector<StudentInfo>& students,   string& filename)   {
        ofstream file(filename);
        if (file.is_open()) {
            for (int i=0; i<students.size(); ++i) {
                file<<students[i].username<<","<<students[i].password<<","<<students[i].major<<endl;
            }// ����ѧ����Ϣ���ļ�
            file.close();
            printf("\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\t����ɹ�!\t\t\t\t\t\t|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            printf("\n");
        } else {
            cout<<"\t\t\t\t\t"<<"�޷����ļ�"<<filename<<"���б��档"<<endl;
        }
    }

    Student() : nextSelectionId(1) {} // ���캯����ʼ��ѡ�α��Ϊ1

    // ��ӿγ� ����ʾ���п�ѡ�γ� ѡ������жϳ�ͻ
    void addCourse(vector<Course>& allCourses, StudentInfo& student) {

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
        cin>>choice;
        choice--;
        // ����ӿγ�֮ǰ���ȼ��selection.txt�ļ����Ƿ��Ѵ�����ѡ�γ�
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

        // �����ѡ�γ��Ƿ��Ѿ���ѧ���Ŀγ��б���
        for (int i=0; i<student.selectedCourses.size(); i++) {
            if (student.selectedCourses[i].courseName==allCourses[choice].courseName) {
                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t���Ѿ�ѡ�����ſΣ����ٴγ���\t\t\t\t|\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                return;
            }
        }

        // ����ѡ�γ���ӵ�ѧ���Ŀγ��б��У�ʹ�ÿγ̴�����Ϊ���
        if (choice>=0&&choice < allCourses.size()) {
            student.selectedCourses.push_back(allCourses[choice]);
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t\tѡ�γɹ�!\t\t\t\t\t\t|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");

            // ʹ�ÿγ̴�����Ϊѡ�α��
            student.selectedCourses.back().courseCode=allCourses[choice].courseCode;
        } else {
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t��Чѡ�����ٴγ���!\t\t\t\t|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
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
        } else {
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t  ѡ����Ч�������ԡ�\t\t\t\t|\n");
            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        }
    }


    // ��ʾѧ���Ŀγ��б�
    void displayMyCourses(  StudentInfo& student)   {
        printf("\n\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
        cout<<"\t\t\t\t\t\t\t\t\t\t\t|"<<"\t\t\t\tѧ�� "<<student.username<<" ��ѡ�Ŀγ��У�\t\t\t\t|\n";
        for (  auto& course : student.selectedCourses) {
            cout<<"\t"<<"\t\t\t\t\t\t\t\t\t\t|"<<"\t\t�γ�����: "<<course.courseName<<"\t\t"<<" �γ̴���: "<<course.courseCode<<"\t\t\t|\n";
        }
    }
    // ����ѧ����ѡ����Ϣ���ļ�
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
            cout<<"�޷����ļ�"<<filename<<"���б��档"<<endl;
        }
    }

    // ���ļ��ж�ȡѧ����ѡ����Ϣ
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
    vector<Course> allCourses; // ���пγ���Ϣ
    vector<StudentInfo> students; // ����ѧ����Ϣ
    Admin admin; // ����Ա
    Student student; // ѧ��
    string coursesFilename="courses.txt";
    string studentsFilename="students.txt";
    string selectionFilename="selection.txt";
    admin.loadFromFile(allCourses, coursesFilename); // ���ļ��ж�ȡ�γ���Ϣ
    ifstream studentFile(studentsFilename); // ���ļ��ж�ȡѧ����Ϣ
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
                    break;
                } else{
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t  ������ȷ����¼�ɹ���\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
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
                    cin>>choice;
                    if (cin.fail()) {
                        cout<<"����������������֡�"<<endl;
                        cin.clear(); // ��������־
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �������뻺�����е������ַ�
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
                cin>>choice;
                if (cin.fail()) {
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t  ����������������֡�\t\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;        }
                if (choice < 1 || choice > 3) {
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t  ������������뷶Χ�ڵ�ѡ�\t\t\t|\n");
                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
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
                                cin>>choice;
                                if (cin.fail()) {
                                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t����������������֣�\t\t\t\t|\n");
                                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                    cin.clear();
                                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �������뻺�����е������ַ�
                                    continue;        }
                                if (choice < 1 || choice > 4) {
                                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                    printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t  ������������뷶Χ�ڵ�ѡ�\t\t\t|\n");
                                    printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                    continue;
                                }
                                switch (choice) {
                                    case 1:
                                        student.addCourse(allCourses, students[stuid]); // ��ӿγ�
                                        student.saveCourseSelection(students, selectionFilename); // ����ѡ����Ϣ���ļ�
                                        break;
                                    case 2:
                                        student.deleteCourse(allCourses, students[stuid]); // ɾ���γ�
                                        student.saveCourseSelection(students, selectionFilename);// ����ѡ����Ϣ���ļ�
                                        break;
                                    case 3:
                                        student.displayMyCourses(students[stuid]); // ��ʾѧ���Ŀγ��б�
                                        break;
                                    case 4:
                                        cout<<"\n������һ����\n";
                                        break;
                                    default:
                                        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                        printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t    ��Ч��ѡ�\t\t\t\t\t|\n");
                                        printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                                }
                                if (choice==4) {
                                    break;
                                }
                            }
                        } else {
                            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
                            printf("\t\t\t\t\t\t\t\t\t\t\t|\t\t\t\t��¼ʧ�ܣ��û������������\t\t\t|\n");
                            printf("\t\t\t\t\t\t\t\t\t\t\t|-----------------------------------------------|\n");
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
                // ����γ���Ϣ���ļ�
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
