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
        cout << "ְ��" << endl;
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
};

void add_teacher(List *list) {
    int code;
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
/*    Node *node = new Node(
            new Teacher(code, name, gender, wage, birth_year, birth_month, birth_day, work_year, work_month, work_day));
    list->insert_head(node);*/
/*    node->next = list->head->next;
    list->head->next = node;
    node->pre = list->head;
    node->next->pre = node;
    list->count++;*/
}

void add_worker(List *list) {
    int code;
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
/*    Node *node = new Node(
            new Worker(code, name, gender, wage, birth_year, birth_month, birth_day, work_year, work_month, work_day));
    node->next = list->head->next;
    list->head->next = node;
    node->pre = list->head;
    node->next->pre = node;
    list->count++;*/
}

void show_all_data(List *list) {
    Node *ptr = list->head;
    Staff *data;
    int count = 1;
    cout << right << setw(10) << "���" << setw(10) << "ְ��" << setw(10) << "ְ����" << setw(10) << "����" << setw(10) << "�Ա�"
         << setw(10) << "����"
         << endl;
    while (ptr->next != nullptr && ptr->next->next != nullptr) {
        ptr = ptr->next;
        data = ptr->data;
        cout << right << setw(10) << count++ << setw(10) << (data->whoIAm() ? "����" : "��ʦ") << setw(10) << data->code
             << setw(10) << data->name << setw(10) << (data->gender ? "��" : "Ů") << setw(10) << data->wage << endl;
    }
}

void calc_ave_teacher_age(List *list) {

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

}

void List::insert_tail(Staff *data) {

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

                break;
            case 5://���㹤��ƽ������

                break;
            case 6://ɾ��һ����ʦ

                break;
            case 7://ɾ��һ������

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
