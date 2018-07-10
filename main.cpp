/*
设计要求：
设计要求实现如下功能：
（1）建立职工信息数据，包括职工编号、姓名、性别、工资、出生时间、参加工作时间和年龄（必须计算得到）。 √
（2）根据职工信息表，建立只含有姓名和年龄的职工信息简表。（可选功能） √
（3）使用继承的方法构造3个类，（即雇员类——虚基类，教师类和工人类——派生类）使用相应的对象放置10个职工信息。 todo 10个信息
（4）编写同名display()成员函数，用来输出数组的内容。 todo
（5）按不同类别输出职工信息，比如按系输出教师信息。（可选功能） todo
（6）要求对“＜＜”和“＞＞”运算符进行重载。考虑到输人职工编号时，也会因不小心引人空格，而且名字中也需要有空格，所以重载“＞＞’’运算符时，需要满足这个要求。 √
（7）抽取并计算职工的平均年龄。 √
（8）检索（查找）指定信息。（如按姓名检索、按年龄检索） √
（9）显示年龄分布的柱状图，示例如下： √
（10）参考界面如下：
设计功能：
增加一位教师记录 √
增加一位工人记录 √
显示全部职工记录 √
计算教师平均年龄 √
计算工人平均年龄 √
删除一个教师 √
删除一个工人 √
按系输出教师信息（可选）
按姓名检索所有信息 √
结束程序运行 √
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

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

    friend ostream &operator<<(ostream &out, Staff &data);
};

ostream &operator<<(ostream &out, Staff &data) {
    cout << right << setw(10) << (data.whoIAm() ? "工人" : "教师") << setw(10) << data.code
         << setw(10) << data.name << setw(10) << (data.gender ? "男" : "女") << setw(10) << data.wage << setw(10)
         << getSystemTimeOfYear() - data.birth_year << setw(8) << getSystemTimeOfYear() - data.work_year << "年";
}

class Teacher : public Staff {
public:
    int whoIAm() override {
        return TEACHER;
    }

    Teacher() {}

    Teacher(const string &code, const string &name, int gender, int wage, int birth_year, int work_year) :
            Staff(code, name, gender, wage, birth_year, work_year) {}

    friend istream &operator>>(istream &in, Teacher &teacher);
};

istream &operator>>(istream &in, Teacher &teacher) {
    cin.get();
    cout << "请输入职工号：";
    getline(cin, teacher.code);
    cout << "请输入姓名：";
    getline(cin, teacher.name);
    cout << "请输入性别[0女/1男]";
    cin >> teacher.gender;
    cout << "请输入工资：";
    cin >> teacher.wage;
    cout << "请分别输入生日年份：";
    cin >> teacher.birth_year;
    cout << "请分别输入入职年份：";
    cin >> teacher.work_year;
    return in;
}

class Worker : public Staff {
public:
    int whoIAm() override {
        return WORKER;
    }

    Worker() {}

    Worker(const string &code, const string &name, int gender, int wage, int birth_year, int work_year) :
            Staff(code, name, gender, wage, birth_year, work_year) {}

    friend istream &operator>>(istream &in, Worker &worker);
};

istream &operator>>(istream &in, Worker &worker) {
    cin.get();
    cout << "请输入职工号：";
    getline(cin, worker.code);
    cout << "请输入姓名：";
    getline(cin, worker.name);
    cout << "请输入性别[0女/1男]";
    cin >> worker.gender;
    cout << "请输入工资：";
    cin >> worker.wage;
    cout << "请分别输入生日年份：";
    cin >> worker.birth_year;
    cout << "请分别输入入职年份：";
    cin >> worker.work_year;
    return in;
}

class Node {
private:
    Node *next, *pre;//上一个和下一个节点
    Staff *data;
public:

    Node(Node *next, Node *pre) : next(next), pre(pre) {}

    Node(Node *next, Node *pre, Staff *data) : next(next), pre(pre), data(data) {}

    Node(Staff *data) : data(data), next(nullptr), pre(nullptr) {}

    Node() : next(nullptr), pre(nullptr) {}

    Node *getNext() {
        return next;
    }

    void setNext(Node *next) {
        this->next = next;
    }

    Node *getPre() {
        return pre;
    }

    void setPre(Node *pre) {
        this->pre = pre;
    }

    Staff *getData() {
        return data;
    }

    void setData(Staff *data) {
        this->data = data;
    }
};

class List {
private:
    int count;
    Node *head, *tail;

public:
    List() : head(new Node()), tail(new Node), count(0) {
        head->setNext(tail);
        tail->setPre(head);
    }

    int getCount() {
        return count;
    }

    void setCount(int count) {
        this->count = count;
    }

    Node *getHead() {
        return head;
    }

    void setHead(Node *head) {
        this->head = head;
    }

    Node *getTail() {
        return tail;
    }

    void setTail(Node *tail) {
        this->tail = tail;
    }

    bool isEmpty() {
        return count == 0;
    }

    void insert_tail(Node *node);//从尾插入
    void insert_tail(Staff *data);//从尾插入

    void insert_head(Node *copy);//从头插入
    void insert_head(Staff *data);//从头插入

    void add_teacher();

    void add_worker();

    void show_all_data();

    void show_simple_data();

    void calc_ave_teacher_age();

    void calc_ave_worker_age();

    void delete_teacher();

    void delete_teacher_by_name();

    void delete_teacher_by_code();

    void delete_worker();

    void delete_worker_by_name();

    void delete_worker_by_code();

    void find_by_name();

    void find_by_age();

    void read_data();

    void save_data();

    int showGraph();
};

void List::add_teacher() {
    Teacher *teacher = new Teacher;
    cin >> *teacher;
    insert_tail(teacher);
}

void List::add_worker() {
    Worker *worker = new Worker;
    cin >> *worker;
    insert_tail(worker);
}

void List::show_all_data() {
    if (isEmpty()) {
        cout << "数据为空！" << endl;
        return;
    }
    Node *ptr = head;
    Staff *data;
    int count = 1;
    cout << right << setw(4) << "序号" << setw(10) << "职别" << setw(10) << "职工号" << setw(10) << "姓名" << setw(10) << "性别"
         << setw(10) << "工资" << setw(10) << "年龄" << setw(10) << "工作时间" << endl;
    while (ptr->getNext() != nullptr && ptr->getNext()->getNext() != nullptr) {
        ptr = ptr->getNext();
        data = ptr->getData();
        cout << right << setw(4) << count++ << *data << endl;
    }
}

void List::show_simple_data() {
    if (isEmpty()) {
        cout << "数据为空！" << endl;
        return;
    }
    Node *ptr = head;
    Staff *data;
    int count = 1;
    cout << right << setw(4) << "序号" << setw(10) << "职别" << setw(10) << "姓名" << setw(10) << "年龄" << endl;
    while (ptr->getNext() != nullptr && ptr->getNext()->getNext() != nullptr) {
        ptr = ptr->getNext();
        data = ptr->getData();
        cout << right << setw(4) << count++ << setw(10) << (data->whoIAm() ? "工人" : "教师") << setw(10) << data->name
             << setw(10) << getSystemTimeOfYear() - data->birth_year << endl;
    }
}

void List::calc_ave_teacher_age() {
    int count = 0;
    int ave_age, sum = 0;
    Node *ptr = head;
    Staff *data;
    while (ptr->getNext() != nullptr && ptr->getNext()->getNext() != nullptr) {
        ptr = ptr->getNext();
        data = ptr->getData();
        if (data->whoIAm() == TEACHER) {
            count++;
            sum += (getSystemTimeOfYear() - data->birth_year);
        }
    }
    ave_age = sum / count;
    cout << "教师平均年龄：" << ave_age << endl;
}

void List::calc_ave_worker_age() {
    int count = 0;
    int ave_age, sum = 0;
    Node *ptr = head;
    Staff *data;
    while (ptr->getNext() != nullptr && ptr->getNext()->getNext() != nullptr) {
        ptr = ptr->getNext();
        data = ptr->getData();
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

//    copy->next = head->next;
//    copy->pre = head;
//    head->next = copy;
//    copy->next->pre = copy;

    copy->setNext(head->getNext());
    copy->setPre(head);
    head->setNext(copy);
    copy->getNext()->setPre(copy);
    count++;
}

void List::insert_head(Staff *data) {
    this->insert_head(new Node(data));
}

void List::insert_tail(Node *node) {
    Node *copy = new Node(*node);

//    copy->next = tail;
//    copy->pre = tail->pre;
//    tail->pre->next = copy;
//    tail->pre = copy;

    copy->setNext(tail);
    copy->setPre(tail->getPre());
    tail->getPre()->setNext(copy);
    tail->setPre(copy);
    count++;
}

void List::insert_tail(Staff *data) {
    this->insert_tail(new Node(data));
}

void List::delete_teacher_by_name() {
    string name;
    cout << "请输入需要删除教师的 姓名：";
    cin.get();
    getline(cin, name);
    Node *ptr = head;
    Staff *data;
    while (ptr->getNext() != nullptr && ptr->getNext()->getNext() != nullptr) {
        ptr = ptr->getNext();
        data = ptr->getData();
        if (data->whoIAm() == TEACHER) {
            if (data->name == name) {
//                ptr->pre->next = ptr->next;
//                ptr->next->pre = ptr->pre;
                ptr->getPre()->setNext(ptr->getNext());
                ptr->getNext()->setPre(ptr->getPre());
                delete ptr;
                cout << "成功删除姓名为 " << name << " 的教师" << endl;
                count--;
                return;
            }
        }
    }
    cout << "表中无名为 " << name << " 的教师" << endl;
}

void List::delete_teacher_by_code() {
    string code;
    cout << "请输入需要删除教师的 职工号：";
    cin.get();
    getline(cin, code);
    Node *ptr = head;
    Staff *data;
    while (ptr->getNext() != nullptr && ptr->getNext()->getNext() != nullptr) {
        ptr = ptr->getNext();
        data = ptr->getData();
        if (data->whoIAm() == TEACHER) {
            if (data->code == code) {
                ptr->getPre()->setNext(ptr->getNext());
                ptr->getNext()->setPre(ptr->getPre());
                delete ptr;
                cout << "成功删除 职工号 为 " << code << " 的教师" << endl;
                count--;
                return;
            }
        }
    }
    cout << "表中无 职工号 为 " << code << " 的教师" << endl;
}

void List::delete_worker_by_name() {
    string name;
    cout << "请输入需要删除工人的 姓名：";
    cin.get();
    getline(cin, name);
    Node *ptr = head;
    Staff *data;
    while (ptr->getNext() != nullptr && ptr->getNext()->getNext() != nullptr) {
        ptr = ptr->getNext();
        data = ptr->getData();
        if (data->whoIAm() == WORKER) {
            if (data->name == name) {
                ptr->getPre()->setNext(ptr->getNext());
                ptr->getNext()->setPre(ptr->getPre());
                delete ptr;
                cout << "成功删除姓名为 " << name << " 的工人" << endl;
                count--;
                return;
            }
        }
    }
    cout << "表中无名为 " << name << " 的工人" << endl;
}

void List::delete_worker_by_code() {
    string code;
    cout << "请输入需要删除工人的 职工号：";
    cin.get();
    getline(cin, code);
    Node *ptr = head;
    Staff *data;
    while (ptr->getNext() != nullptr && ptr->getNext()->getNext() != nullptr) {
        ptr = ptr->getNext();
        data = ptr->getData();
        if (data->whoIAm() == WORKER) {
            if (data->code == code) {
                ptr->getPre()->setNext(ptr->getNext());
                ptr->getNext()->setPre(ptr->getPre());
                delete ptr;
                cout << "成功删除 职工号 为 " << code << " 的工人" << endl;
                count--;
                return;
            }
        }
    }
    cout << "表中无 职工号 为 " << code << " 的工人" << endl;
}

void List::delete_teacher() {
    int flag;
    cout << "请选择删除方式[0通过名字/1通过职工号]：";
    cin >> flag;
    switch (flag) {
        case ByName:
            delete_teacher_by_name();
            break;
        case ByCode:
            delete_teacher_by_code();
            break;
        default:
            cout << "请输入正确选项！" << endl;
    }
}

void List::delete_worker() {
    int flag;
    cout << "请选择删除方式[0通过名字/1通过职工号]：";
    cin >> flag;
    switch (flag) {
        case ByName:
            delete_worker_by_name();
            break;
        case ByCode:
            delete_worker_by_code();
            break;
        default:
            cout << "请输入正确选项！" << endl;
    }
}

void List::find_by_name() {
    string name;
    cout << "请输入姓名:";
    cin.get();
    getline(cin, name);
    Node *ptr = head;
    Staff *data;
    cout << right << setw(10) << "职别" << setw(10) << "职工号" << setw(10) << "姓名" << setw(10) << "性别"
         << setw(10) << "工资" << setw(10) << "年龄" << setw(10) << "工作时间" << endl;
    while (ptr->getNext() != nullptr && ptr->getNext()->getNext() != nullptr) {
        ptr = ptr->getNext();
        data = ptr->getData();
        if (data->name == name) {
            cout << right << *data << endl;
            return;
        }
    }
}

void List::find_by_age() {
    int age;
    cout << "请输入年龄:";
    cin >> age;
    Node *ptr = head;
    Staff *data;
    cout << right << setw(10) << "职别" << setw(10) << "职工号" << setw(10) << "姓名" << setw(10) << "性别"
         << setw(10) << "工资" << setw(10) << "年龄" << setw(10) << "工作时间" << endl;
    while (ptr->getNext() != nullptr && ptr->getNext()->getNext() != nullptr) {
        ptr = ptr->getNext();
        data = ptr->getData();
        if (getSystemTimeOfYear() - data->birth_year == age) {
            cout << right << *data << endl;
        }
    }
}

void List::read_data() {
    ofstream ofile;
    ofile.open("data.txt", ios::app);
    if (!ofile) return;
    else {
        ofile.close();
        ifstream infile;
        infile.open("data.txt", ios::in);
        while (!infile.eof()) {
            string str;
            getline(infile, str);
            if (str.length() == 0) {
                break;
            }
            int be = atoi(str.c_str());
            if (be == TEACHER) {
                Teacher *data = new Teacher;
                getline(infile, data->code);
                getline(infile, data->name);
                string gender, wage, b, w;
                getline(infile, gender);
                getline(infile, wage);
                getline(infile, b);
                getline(infile, w);
                data->gender = atoi(gender.c_str());
                data->wage = atoi(wage.c_str());
                data->birth_year = atoi(b.c_str());
                data->work_year = atoi(w.c_str());
                insert_tail(data);
            } else if (be == WORKER) {
                Worker *data = new Worker;
                getline(infile, data->code);
                getline(infile, data->name);
                string gender, wage, b, w;
                getline(infile, gender);
                getline(infile, wage);
                getline(infile, b);
                getline(infile, w);
                data->gender = atoi(gender.c_str());
                data->wage = atoi(wage.c_str());
                data->birth_year = atoi(b.c_str());
                data->work_year = atoi(w.c_str());
                insert_tail(data);
            }
        }
    }
}

void List::save_data() {
    ofstream outfile;
    outfile.open("data.txt", ios::out);
    Node *ptr = getHead()->getNext();
    while (ptr->getNext() != nullptr) {
        Staff *data = ptr->getData();
        outfile << data->whoIAm() << '\n';
        outfile << data->code << '\n';
        outfile << data->name << '\n';
        outfile << data->gender << '\n';
        outfile << data->wage << '\n';
        outfile << data->birth_year << '\n';
        outfile << data->work_year << '\n';
        ptr = ptr->getNext();
    }
    outfile.close();
}

int List::showGraph() {
    Node *current = getHead()->getNext();
    int length = getCount();
    double number[5] = {0.0};
    if (isEmpty()) {
        cout << "没有数据！" << endl;
        return 0;
    }
    for (int i = 0; i < length; i++) {
        int age = getSystemTimeOfYear() - current->getData()->birth_year;
        if (age < 21) {
            number[0]++;
        } else if (age >= 21 && age <= 28) {
            number[1]++;
        } else if (age > 28 && age <= 35) {
            number[2]++;
        } else if (age > 35 && age <= 42) {
            number[3]++;
        } else {
            number[4]++;
        }
        current = current->getNext();
    }
    for (int i = 0; i < 5; i++) {
        number[i] = (double) number[i] / getCount() * 100;
    }
    cout << "年龄分布百分比统计图" << endl;
    string arr[10][5];
    for (int i = 0; i < 5; i++) {
        int count = number[i] / 10;
        for (int j = 9; j >= 0; j--) {
            if (number[i] == 0) {
                break;
            } else {
                if (count > 0) {
                    arr[j][i] = "  *    ";
                } else if (count <= 0) {
                    arr[j][i] = "       ";
                }
                count--;
            }
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 5; j++) {
            cout << arr[i][j];
        }
        cout << endl;
    }
    for (int i = 0; i < 5; i++) {
        if (number[i] != 0) {
            printf("%.1f", number[i]);
            cout << "%  ";
        }
    }
    cout << endl;
    for (int i = 0; i < 5; i++) {
        if (number[i] != 0) {
            switch (i) {
                case 0:
                    cout << "<21    ";
                    break;
                case 1:
                    cout << "21-28  ";
                    break;
                case 2:
                    cout << "28-35  ";
                    break;
                case 3:
                    cout << "35-42  ";
                    break;
                case 4:
                    cout << "  >42";
                    break;
            }
        }
    }
    cout << endl;
    return 1;
}

int show_function() {
    int selection;
    cout << "职工信息记录" << endl;
    cout << "1.增加一位教师记录" << endl;
    cout << "2.增加一位工人记录" << endl;
    cout << "3.显示全部职工记录" << endl;
    cout << "4.显示职工信息简表" << endl;
    cout << "5.计算教师平均年龄" << endl;
    cout << "6.计算工人平均年龄" << endl;
    cout << "7.删除一个教师" << endl;
    cout << "8.删除一个工人" << endl;
    cout << "9.按姓名检索所有信息" << endl;
    cout << "10.按年龄检索所有信息" << endl;
    cout << "11.生成全部人员的年龄统计柱形图" << endl;
    cout << "0.结束程序运行" << endl;

    cin >> selection;
    return selection;
}

int main() {
    List *list = new List;
    list->read_data();
    int selection = show_function();
    while (selection != 0) {
        switch (selection) {
            case 1://增加一位教师记录
                list->add_teacher();
                break;
            case 2://增加一位工人记录
                list->add_worker();
                break;
            case 3://显示全部职工记录
                list->show_all_data();
                break;
            case 4://显示全部职工简表
                list->show_simple_data();
                break;
            case 5://计算教师平均年龄
                list->calc_ave_teacher_age();
                break;
            case 6://计算工人平均年龄
                list->calc_ave_worker_age();
                break;
            case 7://删除一个教师
                list->delete_teacher();
                break;
            case 8://删除一个工人
                list->delete_worker();
                break;
            case 9://按姓名检索所有信息
                list->find_by_name();
                break;
            case 10://按姓名检索所有信息
                list->find_by_age();
                break;
            case 11://柱形统计图
                list->showGraph();
                break;
            default:
                cout << "请输入正确操作数字！" << endl;
                break;
        }
        selection = show_function();
    }
    list->save_data();
    return 0;
}
