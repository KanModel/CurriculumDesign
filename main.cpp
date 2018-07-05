/*
���Ҫ��
���Ҫ��ʵ�����¹��ܣ�
��1������ְ����Ϣ���ݣ�����ְ����š��������Ա𡢹��ʡ�����ʱ�䡢�μӹ���ʱ������䣨�������õ�����
��2������ְ����Ϣ������ֻ���������������ְ����Ϣ�������ѡ���ܣ�
��3��ʹ�ü̳еķ�������3���࣬������Ա�ࡪ������࣬��ʦ��͹����ࡪ�������ࣩʹ����Ӧ�Ķ������10��ְ����Ϣ��
��4����дͬ��display()��Ա���������������������ݡ�
��5������ͬ������ְ����Ϣ�����簴ϵ�����ʦ��Ϣ������ѡ���ܣ�
��6��Ҫ��ԡ��������͡�������������������ء����ǵ�����ְ�����ʱ��Ҳ����С�����˿ո񣬶���������Ҳ��Ҫ�пո��������ء��������������ʱ����Ҫ�������Ҫ��
��7����ȡ������ְ����ƽ�����䡣
��8�����������ң�ָ����Ϣ�����簴���������������������
��9����ʾ����ֲ�����״ͼ��ʾ�����£�
��10���ο��������£�
��ƹ��ܣ�
����һλ��ʦ��¼
����һλ���˼�¼
��ʾȫ��ְ����¼
�����ʦƽ������
���㹤��ƽ������
ɾ��һ����ʦ
ɾ��һ������
��ϵ�����ʦ��Ϣ����ѡ��
����������������Ϣ
������������
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
        cout << "ְ��" << endl;
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
    Node *next, *pre;//��һ������һ���ڵ�
    Staff *data;

    Node(Node *next, Node *pre) : next(next), pre(pre) {}

    Node(Node *next, Node *pre, Staff *data) : next(next), pre(pre), data(data) {}

    Node(Staff *data) : data(data), next(nullptr), pre(nullptr) {}

    Node() : next(nullptr), pre(nullptr) {}
};

class List {
private:
    int count;
    Node *head, *tail;

public:
    List() : head(new Node()), tail(new Node), count(0) {
        head->next = tail;
        tail->pre = head;
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

    void insert_tail(Node *node);//��β����
    void insert_tail(Staff *data);//��β����

    void insert_head(Node *copy);//��ͷ����
    void insert_head(Staff *data);//��ͷ����

    bool isEmpty() {
        return count == 0;
    }

    void add_teacher();

    void add_worker();

    void show_all_data();

    void calc_ave_teacher_age();

    void calc_ave_worker_age();

    void delete_teacher();

    void delete_teacher_by_name();

    void delete_teacher_by_code();

    void delete_worker();

    void delete_worker_by_name();

    void delete_worker_by_code();

    void find_by_name();

};

void List::add_teacher() {
    string code;
    string name;
    int gender;
    int wage;
    int birth_year;
    int work_year;

    cout << "������ְ���ţ�";
    cin >> code;
    cout << "������������";
    cin >> name;
    cout << "�������Ա�[0Ů/1��]";
    cin >> gender;
    cout << "�����빤�ʣ�";
    cin >> wage;
    cout << "��ֱ�����������ݣ�";
    cin >> birth_year;
    cout << "��ֱ�������ְ��ݣ�";
    cin >> work_year;
    insert_head(new Teacher(code, name, gender, wage, birth_year, work_year));
}

void List::add_worker() {
    string code;
    string name;
    int gender;
    int wage;
    int birth_year;
    int work_year;

    cout << "������ְ���ţ�";
    cin >> code;
    cout << "������������";
    cin >> name;
    cout << "�������Ա�[0Ů/1��]";
    cin >> gender;
    cout << "�����빤�ʣ�";
    cin >> wage;
    cout << "��ֱ�����������ݣ�";
    cin >> birth_year;
    cout << "��ֱ�������ְ��ݣ�";
    cin >> work_year;
    insert_head(new Worker(code, name, gender, wage, birth_year, work_year));
}

void List::show_all_data() {
    if (isEmpty()) {
        cout << "����Ϊ�գ�" << endl;
        return;
    }
    Node *ptr = head;
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

void List::calc_ave_teacher_age() {
    int count = 0;
    double ave_age, sum = 0;
    Node *ptr = head;
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

void List::calc_ave_worker_age() {
    int count = 0;
    double ave_age, sum = 0;
    Node *ptr = head;
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

void List::delete_teacher_by_name() {
    string name;
    cout << "��������Ҫɾ����ʦ�� ������";
    cin >> name;
    Node *ptr = head;
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

void List::delete_teacher_by_code() {
    string code;
    cout << "��������Ҫɾ����ʦ�� ְ���ţ�";
    cin >> code;
    Node *ptr = head;
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

void List::delete_worker_by_name() {
    string name;
    cout << "��������Ҫɾ�����˵� ������";
    cin >> name;
    Node *ptr = head;
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

void List::delete_worker_by_code() {
    string code;
    cout << "��������Ҫɾ�����˵� ְ���ţ�";
    cin >> code;
    Node *ptr = head;
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

void List::delete_teacher() {
    int flag;
    cout << "��ѡ��ɾ����ʽ[0ͨ������/1ͨ��ְ����]��";
    cin >> flag;
    switch (flag) {
        case ByName:
            delete_teacher_by_name();
            break;
        case ByCode:
            delete_teacher_by_code();
            break;
        default:
            cout << "��������ȷѡ�" << endl;
    }
}

void List::delete_worker() {
    int flag;
    cout << "��ѡ��ɾ����ʽ[0ͨ������/1ͨ��ְ����]��";
    cin >> flag;
    switch (flag) {
        case ByName:
            delete_worker_by_name();
            break;
        case ByCode:
            delete_worker_by_code();
            break;
        default:
            cout << "��������ȷѡ�" << endl;
    }
}

void List::find_by_name() {
    string name;
    cout << "����������:";
    cin >> name;
    Node *ptr = head;
    Staff *data;
    while (ptr->next != nullptr && ptr->next->next != nullptr) {
        ptr = ptr->next;
        data = ptr->data;
        if (data->name == name) {
            cout << right << setw(10) << (data->whoIAm() ? "����" : "��ʦ") << setw(10) << data->code
                 << setw(10) << data->name << setw(10) << (data->gender ? "��" : "Ů") << setw(10) << data->wage
                 << setw(10)
                 << getSystemTimeOfYear() - data->birth_year << endl;
            return;
        }
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
                list->add_teacher();
                break;
            case 2://����һλ���˼�¼
                list->add_worker();
                break;
            case 3://��ʾȫ��ְ����¼
                list->show_all_data();
                break;
            case 4://�����ʦƽ������
                list->calc_ave_teacher_age();
                break;
            case 5://���㹤��ƽ������
                list->calc_ave_worker_age();
                break;
            case 6://ɾ��һ����ʦ
                list->delete_teacher();
                break;
            case 7://ɾ��һ������
                list->delete_worker();
                break;
            case 8://����������������Ϣ
                list->find_by_name();
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
