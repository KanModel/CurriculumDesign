#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int FEMALE = 0;
const int MALE = 1;

class Staff {
public:
    int code;
    string name;
    int gender;
    int wage;
    int birth_year, birth_month, birth_day;
    int work_year, work_month, work_day;

    virtual int whoIAm() {
        cout << "职工" << endl;
        return 0;
    }

    Staff() {}

    Staff(int code, const string &name, int gender, int wage, int birth_year, int birth_month, int birth_day,
          int work_year, int work_month, int work_day) : code(code), name(name), gender(gender), wage(wage),
                                                         birth_year(birth_year), birth_month(birth_month),
                                                         birth_day(birth_day), work_year(work_year),
                                                         work_month(work_month), work_day(work_day) {}

};

class Teacher : public Staff {
public:
    int whoIAm() override {
        return 0;
    }

    Teacher() {}

    Teacher(int code, const string &name, int gender, int wage, int birth_year, int birth_month, int birth_day,
            int work_year, int work_month, int work_day) : Staff(code, name, gender, wage, birth_year, birth_month,
                                                                 birth_day, work_year, work_month, work_day) {}
};

class Worker : public Staff {
public:
    int whoIAm() override {
        return 1;
    }

    Worker() {}

    Worker(int code, const string &name, int gender, int wage, int birth_year, int birth_month, int birth_day,
           int work_year, int work_month, int work_day) : Staff(code, name, gender, wage, birth_year, birth_month,
                                                                birth_day, work_year, work_month, work_day) {}
};

class Node {
public:
    Node *next, *pre;//上一个和下一个节点
    Staff *data;

    Node(Node *next, Node *pre) : next(next), pre(pre) {}

    Node(Node *next, Node *pre, Staff *data) : next(next), pre(pre), data(data) {}

    Node(Staff *data) : data(data), next(nullptr), pre(nullptr) {}

    Node() : next(nullptr), pre(nullptr) {}
};

class List {
    int count;
    Node *head, *tail;

public:
    List() : head(new Node()), tail(new Node), count(0) {
        head->next = tail;
        tail->pre = head;
    }

    void insert_tail(Node node);//从尾插入
    void insert_tail(Staff data);//从尾插入

    void insert_head(Node node);//从头插入
    void insert_head(Staff data);//从头插入

    friend void add_teacher(List *list);

    friend void add_worker(List *list);

    friend void show_all_data(List *list);
};

void add_teacher(List *list) {
    int code;
    string name;
    int gender;
    int wage;
    int birth_year, birth_month, birth_day;
    int work_year, work_month, work_day;

    cout << "请输入职工号：";
    cin >> code;
    cout << "请输入姓名：";
    cin >> name;
    cout << "请输入性别[0女/1男]";
    cin >> gender;
    cout << "请输入工资：";
    cin >> wage;
    cout << "请分别输入生日年、月、日：";
    cin >> birth_year >> birth_month >> birth_day;
    cout << "请分别输入入职年、月、日：";
    cin >> work_year >> work_month >> work_day;
    Node *node = new Node(
            new Teacher(code, name, gender, wage, birth_year, birth_month, birth_day, work_year, work_month, work_day));
    node->next = list->head->next;
    list->head->next = node;
    node->pre = list->head;
    node->next->pre = node;
    list->count++;
}

void add_worker(List *list) {
    int code;
    string name;
    int gender;
    int wage;
    int birth_year, birth_month, birth_day;
    int work_year, work_month, work_day;

    cout << "请输入职工号：";
    cin >> code;
    cout << "请输入姓名：";
    cin >> name;
    cout << "请输入性别[0女/1男]";
    cin >> gender;
    cout << "请输入工资：";
    cin >> wage;
    cout << "请分别输入生日年、月、日：";
    cin >> birth_year >> birth_month >> birth_day;
    cout << "请分别输入入职年、月、日：";
    cin >> work_year >> work_month >> work_day;
    Node *node = new Node(
            new Worker(code, name, gender, wage, birth_year, birth_month, birth_day, work_year, work_month, work_day));
    node->next = list->head->next;
    list->head->next = node;
    node->pre = list->head;
    node->next->pre = node;
    list->count++;
}

void show_all_data(List *list) {
    Node *ptr = list->head;
    Staff *data;
    int count = 1;
    cout << right << setw(10) << "序号" << setw(10) << "职别" << setw(10) << "职工号" << setw(10) << "姓名" << setw(10) << "性别"
         << setw(10) << "工资"
         << endl;
    while (ptr->next != nullptr && ptr->next->next != nullptr) {
        ptr = ptr->next;
        data = ptr->data;
        cout << right << setw(10) << count++ << setw(10) << (data->whoIAm() ? "工人" : "教师") << setw(10) << data->code
             << setw(10) << data->name << setw(10) << (data->gender ? "男" : "女") << setw(10) << data->wage << endl;
    }
}

int show_function() {
    int selection;
    cout << "职工信息记录" << endl;
    cout << "1.增加一位教师记录" << endl;
    cout << "2.增加一位工人记录" << endl;
    cout << "3.显示全部职工记录" << endl;
    cout << "4.计算教师平均年龄" << endl;
    cout << "5.计算工人平均年龄" << endl;
    cout << "6.删除一个教师" << endl;
    cout << "7.删除一个工人" << endl;
    cout << "8.按姓名检索所有信息" << endl;
    cout << "0.结束程序运行" << endl;

    cin >> selection;
    return selection;
}

int main() {
    List *list = new List;
    int selection = show_function();
    while (selection != 0) {
        switch (selection) {
            case 1://增加一位教师记录
                add_teacher(list);
                break;
            case 2://增加一位工人记录
                add_worker(list);
                break;
            case 3://显示全部职工记录
                show_all_data(list);
                break;
            case 4://计算教师平均年龄

                break;
            case 5://计算工人平均年龄

                break;
            case 6://删除一个教师

                break;
            case 7://删除一个工人

                break;
            case 8://按姓名检索所有信息

                break;
            case 9:

                break;
            default:
                selection = show_function();
                break;
        }
        selection = show_function();
    }
    return 0;
}
