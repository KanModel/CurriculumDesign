/*
设计要求：
设计要求实现如下功能：
（1）建立职工信息数据，包括职工编号、姓名、性别、工资、出生时间、参加工作时间和年龄（必须计算得到）。
（2）根据职工信息表，建立只含有姓名和年龄的职工信息简表。（可选功能）
（3）使用继承的方法构造3个类，（即雇员类——虚基类，教师类和工人类——派生类）使用相应的对象放置10个职工信息。
（4）编写同名display()成员函数，用来输出数组的内容。
（5）按不同类别输出职工信息，比如按系输出教师信息。（可选功能）
（6）要求对“＜＜”和“＞＞”运算符进行重载。考虑到输人职工编号时，也会因不小心引人空格，而且名字中也需要有空格，所以重载“＞＞’’运算符时，需要满足这个要求。
（7）抽取并计算职工的平均年龄。
（8）检索（查找）指定信息。（如按姓名检索、按年龄检索）
（9）显示年龄分布的柱状图，示例如下：
（10）参考界面如下：
设计功能：
增加一位教师记录
增加一位工人记录
显示全部职工记录
计算教师平均年龄
计算工人平均年龄
删除一个教师
删除一个工人
按系输出教师信息（可选）
按姓名检索所有信息
结束程序运行
*/

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int FEMALE = 0;
const int MALE = 1;

const int TEACHER = 0;
const int WORKER = 1;

const int ByName = 0;
const int ByCode = 1;

int getSystemTimeOfYear() {
    time_t timer;
    time(&timer);
    tm *t_tm = localtime(&timer);
    return (t_tm->tm_year + 1900);
}

class Staff {
public:
    string code;
    string name;
    int gender;
    int wage;
    int birth_year;
    int work_year;

    virtual int whoIAm() {
        cout << "职工" << endl;
        return 0;
    }

    Staff() {}

    Staff(const string &code, const string &name, int gender, int wage, int birth_year, int work_year) :
            code(code), name(name), gender(gender), wage(wage), birth_year(birth_year), work_year(work_year) {}

};

class Teacher : public Staff {
public:
    int whoIAm() override {
        return TEACHER;
    }

    Teacher() {}

    Teacher(const string &code, const string &name, int gender, int wage, int birth_year, int work_year) :
            Staff(code, name, gender, wage, birth_year, work_year) {}
};

class Worker : public Staff {
public:
    int whoIAm() override {
        return WORKER;
    }

    Worker() {}

    Worker(const string &code, const string &name, int gender, int wage, int birth_year, int work_year) :
            Staff(code, name, gender, wage, birth_year, work_year) {}
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

    void insert_tail(Node *node);//从尾插入
    void insert_tail(Staff *data);//从尾插入

    void insert_head(Node *copy);//从头插入
    void insert_head(Staff *data);//从头插入

    bool isEmpty(){
        return count == 0;
    }

    friend void add_teacher(List *list);

    friend void add_worker(List *list);

    friend void show_all_data(List *list);

    friend void calc_ave_teacher_age(List *list);

    friend void calc_ave_worker_age(List *list);

    friend void delete_teacher(List *list);

    friend void delete_teacher_by_name(List *list);

    friend void delete_teacher_by_code(List *list);

    friend void delete_worker(List *list);

    friend void delete_worker_by_name(List *list);

    friend void delete_worker_by_code(List *list);

    friend void find_by_name(List *list);
};

void add_teacher(List *list) {
    string code;
    string name;
    int gender;
    int wage;
    int birth_year;
    int work_year;

    cout << "请输入职工号：";
    cin >> code;
    cout << "请输入姓名：";
    cin >> name;
    cout << "请输入性别[0女/1男]";
    cin >> gender;
    cout << "请输入工资：";
    cin >> wage;
    cout << "请分别输入生日年份：";
    cin >> birth_year;
    cout << "请分别输入入职年份：";
    cin >> work_year;
    list->insert_head(
            new Teacher(code, name, gender, wage, birth_year, work_year));
}

void add_worker(List *list) {
    string code;
    string name;
    int gender;
    int wage;
    int birth_year;
    int work_year;

    cout << "请输入职工号：";
    cin >> code;
    cout << "请输入姓名：";
    cin >> name;
    cout << "请输入性别[0女/1男]";
    cin >> gender;
    cout << "请输入工资：";
    cin >> wage;
    cout << "请分别输入生日年份：";
    cin >> birth_year;
    cout << "请分别输入入职年份：";
    cin >> work_year;
    list->insert_head(
            new Worker(code, name, gender, wage, birth_year, work_year));
}

void show_all_data(List *list) {
    if (list->isEmpty()) {
        cout << "数据为空！" << endl;
        return;
    }
    Node *ptr = list->head;
    Staff *data;
    int count = 1;
    cout << right << setw(10) << "序号" << setw(10) << "职别" << setw(10) << "职工号" << setw(10) << "姓名" << setw(10) << "性别"
         << setw(10) << "工资" << setw(10) << "年龄" << endl;
    while (ptr->next != nullptr && ptr->next->next != nullptr) {
        ptr = ptr->next;
        data = ptr->data;
        cout << right << setw(10) << count++ << setw(10) << (data->whoIAm() ? "工人" : "教师") << setw(10) << data->code
             << setw(10) << data->name << setw(10) << (data->gender ? "男" : "女") << setw(10) << data->wage << setw(10)
             << getSystemTimeOfYear() - data->birth_year << endl;
    }
}

void calc_ave_teacher_age(List *list) {
    int count = 0;
    double ave_age, sum = 0;
    Node *ptr = list->head;
    Staff *data;
    while (ptr->next != nullptr && ptr->next->next != nullptr) {
        ptr = ptr->next;
        data = ptr->data;
        if (data->whoIAm() == TEACHER) {
            count++;
            sum += (getSystemTimeOfYear() - data->birth_year);
        }
    }
    ave_age = sum / count;
    cout << "教师平均年龄：" << ave_age << endl;
}

void calc_ave_worker_age(List *list) {
    int count = 0;
    double ave_age, sum = 0;
    Node *ptr = list->head;
    Staff *data;
    while (ptr->next != nullptr && ptr->next->next != nullptr) {
        ptr = ptr->next;
        data = ptr->data;
        if (data->whoIAm() == WORKER) {
            count++;
            sum += (getSystemTimeOfYear() - data->birth_year);
        }
    }
    ave_age = sum / count;
    cout << "工人平均年龄：" << ave_age << endl;
}

void List::insert_head(Node *node) {
    Node *copy = new Node(*node);

    copy->next = head->next;
    copy->pre = head;
    head->next = copy;
    copy->next->pre = copy;
    count++;
}

void List::insert_head(Staff *data) {
    this->insert_head(new Node(data));
}

void List::insert_tail(Node *node) {
    Node *copy = new Node(*node);

    copy->next = tail;
    copy->pre = tail->pre;
    tail->pre->next = copy;
    tail->pre = copy;
    count++;
}

void List::insert_tail(Staff *data) {
    this->insert_head(new Node(data));
}

void delete_teacher_by_name(List *list) {
    string name;
    cout << "请输入需要删除教师的 姓名：";
    cin >> name;
    Node *ptr = list->head;
    Staff *data;
    while (ptr->next != nullptr && ptr->next->next != nullptr) {
        ptr = ptr->next;
        data = ptr->data;
        if (data->whoIAm() == TEACHER) {
            if (data->name == name) {
                ptr->pre->next = ptr->next;
                delete ptr;
                cout << "成功删除姓名为 " << name << " 的教师" << endl;
                return;
            }
        }
    }
    cout << "表中无名为 " << name << " 的教师" << endl;
}

void delete_teacher_by_code(List *list) {
    string code;
    cout << "请输入需要删除教师的 职工号：";
    cin >> code;
    Node *ptr = list->head;
    Staff *data;
    while (ptr->next != nullptr && ptr->next->next != nullptr) {
        ptr = ptr->next;
        data = ptr->data;
        if (data->whoIAm() == TEACHER) {
            if (data->code == code) {
                ptr->pre->next = ptr->next;
                delete ptr;
                cout << "成功删除 职工号 为 " << code << " 的教师" << endl;
                return;
            }
        }
    }
    cout << "表中无 职工号 为 " << code << " 的教师" << endl;
}

void delete_worker_by_name(List *list) {
    string name;
    cout << "请输入需要删除工人的 姓名：";
    cin >> name;
    Node *ptr = list->head;
    Staff *data;
    while (ptr->next != nullptr && ptr->next->next != nullptr) {
        ptr = ptr->next;
        data = ptr->data;
        if (data->whoIAm() == WORKER) {
            if (data->name == name) {
                ptr->pre->next = ptr->next;
                delete ptr;
                cout << "成功删除姓名为 " << name << " 的工人" << endl;
                return;
            }
        }
    }
    cout << "表中无名为 " << name << " 的工人" << endl;
}

void delete_worker_by_code(List *list) {
    string code;
    cout << "请输入需要删除工人的 职工号：";
    cin >> code;
    Node *ptr = list->head;
    Staff *data;
    while (ptr->next != nullptr && ptr->next->next != nullptr) {
        ptr = ptr->next;
        data = ptr->data;
        if (data->whoIAm() == WORKER) {
            if (data->code == code) {
                ptr->pre->next = ptr->next;
                delete ptr;
                cout << "成功删除 职工号 为 " << code << " 的工人" << endl;
                return;
            }
        }
    }
    cout << "表中无 职工号 为 " << code << " 的工人" << endl;
}

void delete_teacher(List *list) {
    int flag;
    cout << "请选择删除方式[0通过名字/1通过职工号]：";
    cin >> flag;
    switch (flag) {
        case ByName:
            delete_teacher_by_name(list);
            break;
        case ByCode:
            delete_teacher_by_code(list);
            break;
        default:
            cout << "请输入正确选项！" << endl;
    }
}

void delete_worker(List *list) {
    int flag;
    cout << "请选择删除方式[0通过名字/1通过职工号]：";
    cin >> flag;
    switch (flag) {
        case ByName:
            delete_worker_by_name(list);
            break;
        case ByCode:
            delete_worker_by_code(list);
            break;
        default:
            cout << "请输入正确选项！" << endl;
    }
}

void find_by_name(List *list) {
    string name;
    cout << "请输入姓名:";
    cin >> name;
    Node *ptr = list->head;
    Staff *data;
    while (ptr->next != nullptr && ptr->next->next != nullptr) {
        ptr = ptr->next;
        data = ptr->data;
        if (data->name == name) {
            cout << right << setw(10) << (data->whoIAm() ? "工人" : "教师") << setw(10) << data->code
                 << setw(10) << data->name << setw(10) << (data->gender ? "男" : "女") << setw(10) << data->wage << setw(10)
                 << getSystemTimeOfYear() - data->birth_year << endl;
            return;
        }
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
                calc_ave_teacher_age(list);
                break;
            case 5://计算工人平均年龄
                calc_ave_worker_age(list);
                break;
            case 6://删除一个教师
                delete_teacher(list);
                break;
            case 7://删除一个工人
                delete_worker(list);
                break;
            case 8://按姓名检索所有信息
                find_by_name(list);
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
