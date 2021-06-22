// LinkedList_Students.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iomanip>
#include<sstream>
#include<fstream>
#include<vector>
using namespace std;

//Quản lý danh sách sinh viên bằng danh sách liên kết
//1. Tạo 1 file text, trong đó chứa dữ liệu là danh sách sinh viên gồm các thông tin : Ho ten, ngay sinh, lớp
//Mỗi 1 dòng trong file thể hiện thông tin của 1 sinh viên, các thông tin của mỗi sinh viên cách nhau dấu ','
//File này tạo manual bằng tay
//2. Đọc file dữ liệu bên trên, sử dụng danh sách liên kết để quản lý dữ liệu
//3. Đưa ra màn hình các lựa chọn :
//-Xuất thông tin
//- Sắp xếp dữ liệu, in ra thông tin danh sách
//- Thêm / sửa / xóa dữ liệu(có cập nhật vào file)

struct Student
{
    
    string name;
    int dateOfBirth;
    string _class;

    Student() {}
    Student(string ipName, int ipDate, string ipClass) : name(ipName), dateOfBirth(ipDate), _class(ipClass) {}
    Student(const Student& obj)
    {
        name = obj.name;
        dateOfBirth = obj.dateOfBirth;
        _class = obj._class;
    }

    Student& operator=(const Student& ipPerson)
    {
        if (this == &ipPerson)
        {
            return *this;
        }
        name = ipPerson.name;
        dateOfBirth = ipPerson.dateOfBirth;
        _class = ipPerson._class;
        return *this;
    }

    bool operator>(const Student& obj)
    {
        //convert string to int
        stringstream buff1(_class);
        int lValue = 0;
        buff1 >> lValue;

        stringstream buff2(obj._class);
        int rValue = 0;
        buff2 >> rValue;

        //compare
        if (lValue > rValue)
        {
            return true;
        }
        return false;
    }

    bool operator<(const Student& obj)
    {
        //convert string to int
        stringstream buff1(_class);
        int lValue = 0;
        buff1 >> lValue;

        stringstream buff2(obj._class);
        int rValue = 0;
        buff2 >> rValue;

        //compare
        if (lValue < rValue)
        {
            return true;
        }
        return false;
    }

    void ReadFromFile(const string& fileName)
    {
       

        //fstream file;
        //file.open(fileName, ios::in);//open file | mode: read only

        //if (file.fail())
        //{
        //    cout << "Failed to open!";
        //}

        //string data;
        ////getline(file, data);//file>>data
        ////vector<string>save;// list save data packages

        //vector<string> element{};
        //while (getline(file, data))// (file>>data) read data from file => string data | read line by line 
        //{

        //    string info;

        //    stringstream buff(data);

        //    while (buff >> info)
        //    {
        //        element.push_back(info);
        //    }

        //    //new data
        //    name = element.at(0);
        //    dateOfBirth = stoi(element.at(1));//from string => int
        //    _class = element.at(2);
        //}

        //file.close();


    }

    Student* FromFile(const string& ipData)
    {
        vector<string>elements{};
        stringstream buff(ipData);
        string temp;
        while (buff >> temp)
        {
            elements.push_back(temp);
        }

        name = elements.at(0);
        dateOfBirth = stoi(elements.at(1));//string => int
        _class = elements.at(2);

        return (this);
    }
    string ToFile()
    {
        string s = name + "\t" + to_string(dateOfBirth) + "\t" + _class;
        return s;
    }

    void DisplayOne(const Student& ipPerson,int& index)
    {
        index++;
        cout << index << setw(20) << ipPerson.name << setw(20) << ipPerson.dateOfBirth
            << setw(20) << ipPerson._class << endl;
        
    }


    vector<Student*> ReadDataFromFile(const string& fileName)
    {
        vector<Student*> studentList;

        fstream file;
        file.open(fileName, ios::in);
        if (file.fail())
        {
            cout << "Failed to open!";
        }

        string data;
        vector<string>saveLine;// list save data packages

        while (getline(file, data))// (file>>data) read data from file => string data | read line by line 
        {
            saveLine.push_back(data);//push data to list
        }

        //print List
        cout << "Tale of Students:\n";
        cout << "STT " << setw(20) << "Name" << setw(20) << "Date of birth " << setw(20) << "Class" << endl;
        int index = 0;
        for (int i = 0; i < saveLine.size(); i++)
        {
            cout << saveLine.at(i);
            string ipData = saveLine.at(i);
            studentList.push_back(FromFile(ipData));//in ra tu Node?

            cout << ipData<<endl;
            //DisplayOne(*studentList.at(i),index);

        }

        cout << "Tale of Students:\n";
        cout << "STT " << setw(20) << "Name" << setw(20) << "Date of birth " << setw(20) << "Class" << endl;
        

        file.close();
        return studentList;

    }

    
};

//check input Student data
bool CheckName(const string& ipName)
{
    for (unsigned int i = 0; i < ipName.length(); ++i)
    {
        if (!((ipName[i] >= 65 && ipName[i] <= 90) || (ipName[i] >= 97 && ipName[i] <= 122) || ipName[i] == 32))
        {
            return false;
        }
    }
    return true;
}

bool CheckDateOfBirth(const int& ipDate)
{
    if (!(ipDate > 0 && ipDate <= 31))
    {
        return false;
    }
    return true;
}

bool CheckClass(const string ipClass)
{
    for (unsigned int i = 0; i < ipClass.length(); ++i)
    {
        if (!((ipClass[i] >= 65 && ipClass[i] <= 90) || (ipClass[i] >= 97 && ipClass[i] <= 122) || ipClass[i] == 32))
        {
            return false;
        }
    }
    return true;
}

struct Node
{
    Student data;
    Node* next;

    Node()
    {
        next = nullptr;
    }
    ~Node()
    {
        if (next != nullptr)
        {
            delete next;
            next = nullptr;
        }
    }
};
Node* head; // head of LL

struct Node* CreateNewNode(const Student& ipPerson)
{
    //Node* newNode = (Node*)malloc(sizeof(Node));
    Node* newNode = new Node;
    newNode->data = ipPerson;// operator = 
    newNode->next = nullptr;

    return newNode;
}

void InsertAtHead(Node*& head,const Student& ipPerson)
{
    Node* newNode = CreateNewNode(ipPerson);
    if (head == NULL)//empty list => head point to first student (newNode) 
    {
        head = newNode;
        return;
    }
    //make newNode => head  [] []
    newNode->next = head;
    head = newNode;
}

void InsertAtTail(Node*& head, const Student& ipPerson)
{
    Node* newNode = CreateNewNode(ipPerson);
    Node* temp = head;

    if (head == NULL)//empty list => head point to first student (newNode) 
    {
        head = newNode;
        return;
    }
    
    while (temp->next != nullptr)//go to the last ele
    {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = nullptr;
}

void RemoveAtHead(Node*& head) 
{
    if (head == NULL) 
    {
        return;
    }
    Node* temp = head;
    head = head->next;
    temp->next = nullptr;
    delete temp;
    temp = nullptr;
    //return;
}

void RemoveAtTail(Node*& head)// [] []
{
    

    if (head->next == nullptr)//empty list => head point to first student (newNode) 
    {
        head = nullptr;
        return;
    }

    Node* temp = head;
    while (temp->next->next != nullptr)//go to the second last ele
    {
        temp = temp->next;
    }

    Node* lastNode = temp->next;// last ele
    temp->next = nullptr;

    delete lastNode;
    lastNode = nullptr;
}

void Print()
{
    Node* temp = head;
    if (temp == nullptr)
    {
        return; //empty list => exit
    }

    cout << "Tale of Students:\n";
    cout << "STT " << setw(20) << "Name" << setw(20) << "Date of birth " << setw(20) << "Class" << endl;
    int index = 0;

    while (temp != nullptr)
    {
        index++;
        cout << index << setw(20) << temp->data.name << setw(20) << temp->data.dateOfBirth
            << setw(20) << temp->data._class << endl;
        temp = temp->next;
    }
    cout << endl;
}

void BubbleSort(Node* head)
{
    int swapped, i;
    Node* ptr1;
    Node* lptr = nullptr;

    /* Checking for empty list */
    if (head == nullptr)
    {
        return;
    }
    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (ptr1->data > ptr1->next->data)//accesding
            {
                swap(ptr1->data, ptr1->next->data);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}


int main()
{
    //Student person1("Lam Le", 25, "11CDT2");
    //InsertAtHead(head, person1);
    //Student person2("Phu Le", 4, "20DT1");
    //InsertAtTail(head, person2);
    //Student person3("Trieu Phan", 11, "13AT3");
    //InsertAtTail(head, person3);

    //Print();

    ////RemoveAtHead(head);
    ////RemoveAtTail(head);
    ////cout << "After removing: " << endl;
    //BubbleSort(head);
    //cout << "After sorting" << endl;
    
    Print();

    Student list;
    string fileName = "input.txt";
    list.ReadDataFromFile(fileName);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
