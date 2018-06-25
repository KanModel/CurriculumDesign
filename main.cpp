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
//    cout << "today is " << t_tm->tm_year + 1900 << " " << t_tm->tm_mon + 1 << " " << t_tm->tm_mday << endl;
    return (t_tm->tm_year + 1900);
}

class Staff {
public:
    string code;
    string name;
    int gender;
    int wage;
    int birth_year, birth_month, birth_day;
    int work_year, work_month, work_day;

    virtual int whoIAm() {
        cout << "ְ��" << endl;
        return 0;
    }

    Staff() {}

    Staff(string code, string name, int gender, int wage, int birth_year, int birth_month, int birth_day,
          int work_year, int work_month, int work_day) : code(code), name(name), gender(gender), wage(wage),
                                                         birth_year(birth_year), birth_month(birth_month),
                                                         birth_day(birth_day), work_year(work_year),
                                                         work_month(work_month), work_day(work_day) {}

};

class Teacher : public Staff {
public:
    int whoIAm() override {
        return TEACHER;
    }

    Teacher() {}

    Teacher(string code, string name, int gender, int wage, int birth_year, int birth_month, int birth_day,
            int work_year, int work_month, int work_day) : Staff(code, name, gender, wage, birth_year, birth_month,
                                                                 birth_day, work_year, work_month, work_day) {}
};

class Worker : public Staff {
public:
    int whoIAm() override {
        return WORKER;
    }

    Worker() {}

    Worker(string code, string name, int gender, int wage, int birth_year, int birth_month, int birth_day,
           int work_year, int work_month, int work_day) : Staff(code, name, gender, wage, birth_year, birth_month,
                                                                birth_day, work_year, work_month, work_day) {}
};

class Node {
public:
    Node *next, *pre;//��һ������һ���ڵ�
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

    void insert_tail(Node *node);//��β����
    void insert_tail(Staff *data);//��β����

    void insert_head(Node *node);//��ͷ����
    void insert_head(Staff *data);//��ͷ����

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
};

void add_teacher(List *list) {
    string code;
    string name;
    int gender;
    int wage;
    int birth_year, birth_month, birth_day;
    int work_year, work_month, work_day;

    cout << "������ְ���ţ�";
    cin >> code;
    cout << "������������";
    cin >> name;
    cout << "�������Ա�[0Ů/1��]";
    cin >> gender;
    cout << "�����빤�ʣ�";
    cin >> wage;
    cout << "��ֱ����������ꡢ�¡��գ�";
    cin >> birth_year >> birth_month >> birth_day;
    cout << "��ֱ�������ְ�ꡢ�¡��գ�";
    cin >> work_year >> work_month >> work_day;
    list->insert_head(
            new Teacher(code, name, gender, wage, birth_year, birth_month, birth_day, work_year, work_month, work_day));
}

void add_worker(List *list) {
    string code;
    string name;
    int gender;
    int wage;
    int birth_year, birth_month, birth_day;
    int work_year, work_month, work_day;

    cout << "������ְ���ţ�";
    cin >> code;
    cout << "������������";
    cin >> name;
    cout << "�������Ա�[0Ů/1��]";
    cin >> gender;
    cout << "�����빤�ʣ�";
    cin >> wage;
    cout << "��ֱ����������ꡢ�¡��գ�";
    cin >> birth_year >> birth_month >> birth_day;
    cout << "��ֱ�������ְ�ꡢ�¡��գ�";
    cin >> work_year >> work_month >> work_day;
    list->insert_head(
            new Worker(code, name, gender, wage, birth_year, birth_month, birth_day, work_year, work_month, work_day));
}

void show_all_data(List *list) {
    Node *ptr = list->head;
    Staff *data;
    int count = 1;
    cout << right << setw(10) << "���" << setw(10) << "ְ��" << setw(10) << "ְ����" << setw(10) << "����" << setw(10) << "�Ա�"
         << setw(10) << "����" << setw(10) << "����" << endl;
    while (ptr->next != nullptr && ptr->next->next != nullptr) {
        ptr = ptr->next;
        data = ptr->data;
        cout << right << setw(10) << count++ << setw(10) << (data->whoIAm() ? "����" : "��ʦ") << setw(10) << data->code
             << setw(10) << data->name << setw(10) << (data->gender ? "��" : "Ů") << setw(10) << data->wage << setw(10)
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
    cout << "��ʦƽ�����䣺" << ave_age << endl;
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
    cout << "����ƽ�����䣺" << ave_age << endl;
}

void List::insert_head(Node *node) {
    node->next = head->next;
    head->next = node;
    node->pre = head;
    node->next->pre = node;
    count++;
}

void List::insert_head(Staff *data) {
    this->insert_head(new Node(data));
}

void List::insert_tail(Node *node) {
    //todo
}

void List::insert_tail(Staff *data) {
    //todo
}

void delete_teacher_by_name(List *list) {
    string name;
    cout << "��������Ҫɾ����ʦ�� ������" ;
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
                cout << "�ɹ�ɾ������Ϊ " << name << " �Ľ�ʦ" << endl;
                return;
            }
        }
    }
    cout << "��������Ϊ " << name << " �Ľ�ʦ" << endl;
}

void delete_teacher_by_code(List *list) {
    string code;
    cout << "��������Ҫɾ����ʦ�� ְ���ţ�" ;
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
                cout << "�ɹ�ɾ�� ְ���� Ϊ " << code << " �Ľ�ʦ" << endl;
                return;
            }
        }
    }
    cout << "������ ְ���� Ϊ " << code << " �Ľ�ʦ" << endl;
}

void delete_worker_by_name(List *list) {
    string name;
    cout << "��������Ҫɾ�����˵� ������" ;
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
                cout << "�ɹ�ɾ������Ϊ " << name << " �Ĺ���" << endl;
                return;
            }
        }
    }
    cout << "��������Ϊ " << name << " �Ĺ���" << endl;
}

void delete_worker_by_code(List *list) {
    string code;
    cout << "��������Ҫɾ�����˵� ְ���ţ�" ;
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
                cout << "�ɹ�ɾ�� ְ���� Ϊ " << code << " �Ĺ���" << endl;
                return;
            }
        }
    }
    cout << "������ ְ���� Ϊ " << code << " �Ĺ���" << endl;
}

void delete_teacher(List *list) {
    int flag;
    cout << "��ѡ��ɾ����ʽ[0ͨ������/1ͨ��ְ����]��" ;
    cin >> flag;
    switch (flag) {
        case ByName:
            delete_teacher_by_name(list);
            break;
        case ByCode:
            delete_teacher_by_code(list);
            break;
        default:
            cout << "��������ȷѡ�" << endl;
    }
}

void delete_worker(List *list) {
    int flag;
    cout << "��ѡ��ɾ����ʽ[0ͨ������/1ͨ��ְ����]��" ;
    cin >> flag;
    switch (flag) {
        case ByName:
            delete_worker_by_name(list);
            break;
        case ByCode:
            delete_worker_by_code(list);
            break;
        default:
            cout << "��������ȷѡ�" << endl;
    }
}


int show_function() {
    int selection;
    cout << "ְ����Ϣ��¼" << endl;
    cout << "1.����һλ��ʦ��¼" << endl;
    cout << "2.����һλ���˼�¼" << endl;
    cout << "3.��ʾȫ��ְ����¼" << endl;
    cout << "4.�����ʦƽ������" << endl;
    cout << "5.���㹤��ƽ������" << endl;
    cout << "6.ɾ��һ����ʦ" << endl;
    cout << "7.ɾ��һ������" << endl;
    cout << "8.����������������Ϣ" << endl;
    cout << "0.������������" << endl;

    cin >> selection;
    return selection;
}

int main() {
    List *list = new List;
    int selection = show_function();
    while (selection != 0) {
        switch (selection) {
            case 1://����һλ��ʦ��¼
                add_teacher(list);
                break;
            case 2://����һλ���˼�¼
                add_worker(list);
                break;
            case 3://��ʾȫ��ְ����¼
                show_all_data(list);
                break;
            case 4://�����ʦƽ������
                calc_ave_teacher_age(list);
                break;
            case 5://���㹤��ƽ������
                calc_ave_worker_age(list);
                break;
            case 6://ɾ��һ����ʦ
                delete_teacher(list);
                break;
            case 7://ɾ��һ������
                delete_worker(list);
                break;
            case 8://����������������Ϣ

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
