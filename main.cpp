/*
���Ҫ��
���Ҫ��ʵ�����¹��ܣ�
��1������ְ����Ϣ���ݣ�����ְ����š��������Ա𡢹��ʡ�����ʱ�䡢�μӹ���ʱ������䣨�������õ����� ��
��2������ְ����Ϣ������ֻ���������������ְ����Ϣ�������ѡ���ܣ� ��
��3��ʹ�ü̳еķ�������3���࣬������Ա�ࡪ������࣬��ʦ��͹����ࡪ�������ࣩʹ����Ӧ�Ķ������10��ְ����Ϣ�� ��
��4����дͬ��display()��Ա���������������������ݡ� ��
��5������ͬ������ְ����Ϣ�����簴ϵ�����ʦ��Ϣ������ѡ���ܣ� todo
��6��Ҫ��ԡ��������͡�������������������ء����ǵ�����ְ�����ʱ��Ҳ����С�����˿ո񣬶���������Ҳ��Ҫ�пո��������ء��������������ʱ����Ҫ�������Ҫ�� ��
��7����ȡ������ְ����ƽ�����䡣 ��
��8�����������ң�ָ����Ϣ�����簴��������������������� ��
��9����ʾ����ֲ�����״ͼ��ʾ�����£� ��
��10���ο��������£�
��ƹ��ܣ�
����һλ��ʦ��¼ ��
����һλ���˼�¼ ��
��ʾȫ��ְ����¼ ��
�����ʦƽ������ ��
���㹤��ƽ������ ��
ɾ��һ����ʦ ��
ɾ��һ������ ��
��ϵ�����ʦ��Ϣ����ѡ��
����������������Ϣ ��
������������ ��
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
        cout << "ְ��" << endl;
        return 0;
    }

    Staff() {}

    Staff(const string &code, const string &name, int gender, int wage, int birth_year, int work_year) :
            code(code), name(name), gender(gender), wage(wage), birth_year(birth_year), work_year(work_year) {}

    friend ostream &operator<<(ostream &out, Staff &data);
};

ostream &operator<<(ostream &out, Staff &data) {
    cout << right << setw(10) << (data.whoIAm() ? "����" : "��ʦ") << setw(10) << data.code
         << setw(10) << data.name << setw(10) << (data.gender ? "��" : "Ů") << setw(10) << data.wage << setw(10)
         << getSystemTimeOfYear() - data.birth_year << setw(8) << getSystemTimeOfYear() - data.work_year << "��";
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
    cout << "������ְ���ţ�";
    getline(cin, teacher.code);
    cout << "������������";
    getline(cin, teacher.name);
    cout << "�������Ա�[0Ů/1��]";
    cin >> teacher.gender;
    cout << "�����빤�ʣ�";
    cin >> teacher.wage;
    cout << "��ֱ�����������ݣ�";
    cin >> teacher.birth_year;
    cout << "��ֱ�������ְ��ݣ�";
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
    cout << "������ְ���ţ�";
    getline(cin, worker.code);
    cout << "������������";
    getline(cin, worker.name);
    cout << "�������Ա�[0Ů/1��]";
    cin >> worker.gender;
    cout << "�����빤�ʣ�";
    cin >> worker.wage;
    cout << "��ֱ�����������ݣ�";
    cin >> worker.birth_year;
    cout << "��ֱ�������ְ��ݣ�";
    cin >> worker.work_year;
    return in;
}

class Node {
private:
    Node *next, *pre;//��һ������һ���ڵ�
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

    void insert_tail(Node *node);//��β����
    void insert_tail(Staff *data);//��β����

    void insert_head(Node *copy);//��ͷ����
    void insert_head(Staff *data);//��ͷ����

    void add_teacher();//��ӽ�ʦ

    void add_worker();//��ӹ���

    void show_all_data();//���������Ϣ

    void show_simple_data();//�����Ϣ���

    void calc_ave_teacher_age();//�����ʦƽ������

    void calc_ave_worker_age();//���㹤����������

    void delete_teacher();//ɾ����ʦ

    void delete_teacher_by_name();//ͨ������ɾ����ʦ

    void delete_teacher_by_code();//ͨ��ְ����ɾ����ʦ

    void delete_worker();//ɾ������

    void delete_worker_by_name();//ͨ������ɾ������

    void delete_worker_by_code();//ͨ��ְ����ɾ������

    void find_by_name();//ͨ������������Ϣ

    void find_by_age();//ͨ�����������Ϣ

    void modify();//�޸�����

    void read_data();//��ȡ�ı��ļ��д洢������

    void save_data();//�������ݵ��ı��ļ�

    int show_graph();//��ʾ����ֲ���״ͼ
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
        cout << "����Ϊ�գ�" << endl;
        return;
    }
    Node *ptr = head;
    Staff *data;
    int count = 1;
    cout << right << setw(4) << "���" << setw(10) << "ְ��" << setw(10) << "ְ����" << setw(10) << "����" << setw(10) << "�Ա�"
         << setw(10) << "����" << setw(10) << "����" << setw(10) << "����ʱ��" << endl;
    while (ptr->getNext() != nullptr && ptr->getNext()->getNext() != nullptr) {
        ptr = ptr->getNext();
        data = ptr->getData();
        cout << right << setw(4) << count++ << *data << endl;
    }
}

void List::show_simple_data() {
    if (isEmpty()) {
        cout << "����Ϊ�գ�" << endl;
        return;
    }
    Node *ptr = head;
    Staff *data;
    int count = 1;
    cout << right << setw(4) << "���" << setw(10) << "ְ��" << setw(10) << "����" << setw(10) << "����" << endl;
    while (ptr->getNext() != nullptr && ptr->getNext()->getNext() != nullptr) {
        ptr = ptr->getNext();
        data = ptr->getData();
        cout << right << setw(4) << count++ << setw(10) << (data->whoIAm() ? "����" : "��ʦ") << setw(10) << data->name
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
    cout << "��ʦƽ�����䣺" << ave_age << endl;
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
    cout << "����ƽ�����䣺" << ave_age << endl;
}

void List::insert_head(Node *node) {
    Node *copy = new Node(*node);
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
    cout << "��������Ҫɾ����ʦ�� ������";
    cin.get();
    getline(cin, name);
    Node *ptr = head;
    Staff *data;
    while (ptr->getNext() != nullptr && ptr->getNext()->getNext() != nullptr) {
        ptr = ptr->getNext();
        data = ptr->getData();
        if (data->whoIAm() == TEACHER) {
            if (data->name == name) {
                ptr->getPre()->setNext(ptr->getNext());
                ptr->getNext()->setPre(ptr->getPre());
                delete ptr;
                cout << "�ɹ�ɾ������Ϊ " << name << " �Ľ�ʦ" << endl;
                count--;
                return;
            }
        }
    }
    cout << "��������Ϊ " << name << " �Ľ�ʦ" << endl;
}

void List::delete_teacher_by_code() {
    string code;
    cout << "��������Ҫɾ����ʦ�� ְ���ţ�";
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
                cout << "�ɹ�ɾ�� ְ���� Ϊ " << code << " �Ľ�ʦ" << endl;
                count--;
                return;
            }
        }
    }
    cout << "������ ְ���� Ϊ " << code << " �Ľ�ʦ" << endl;
}

void List::delete_worker_by_name() {
    string name;
    cout << "��������Ҫɾ�����˵� ������";
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
                cout << "�ɹ�ɾ������Ϊ " << name << " �Ĺ���" << endl;
                count--;
                return;
            }
        }
    }
    cout << "��������Ϊ " << name << " �Ĺ���" << endl;
}

void List::delete_worker_by_code() {
    string code;
    cout << "��������Ҫɾ�����˵� ְ���ţ�";
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
                cout << "�ɹ�ɾ�� ְ���� Ϊ " << code << " �Ĺ���" << endl;
                count--;
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
    cin.get();
    getline(cin, name);
    Node *ptr = head;
    Staff *data;
    cout << right << setw(10) << "ְ��" << setw(10) << "ְ����" << setw(10) << "����" << setw(10) << "�Ա�"
         << setw(10) << "����" << setw(10) << "����" << setw(10) << "����ʱ��" << endl;
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
    cout << "����������:";
    cin >> age;
    Node *ptr = head;
    Staff *data;
    cout << right << setw(10) << "ְ��" << setw(10) << "ְ����" << setw(10) << "����" << setw(10) << "�Ա�"
         << setw(10) << "����" << setw(10) << "����" << setw(10) << "����ʱ��" << endl;
    while (ptr->getNext() != nullptr && ptr->getNext()->getNext() != nullptr) {
        ptr = ptr->getNext();
        data = ptr->getData();
        if (getSystemTimeOfYear() - data->birth_year == age) {
            cout << right << *data << endl;
        }
    }
}

void List::modify() {
    bool isFind = false;
    string name;
    cout << "����������:";
    cin.get();
    getline(cin, name);
    Node *ptr = head;
    Staff *data;
    while (ptr->getNext() != nullptr && ptr->getNext()->getNext() != nullptr) {
        ptr = ptr->getNext();
        data = ptr->getData();
        if (data->name == name) {
            cout << "Ѱ�ҵ���Ӧ��Ϣ��" << endl;
            cout << right << setw(10) << "ְ��" << setw(10) << "ְ����" << setw(10) << "����" << setw(10) << "�Ա�"
                 << setw(10) << "����" << setw(10) << "����" << setw(10) << "����ʱ��" << endl;
            cout << right << *data << endl;
            isFind = true;
            break;
        }
    }

    if (isFind) {
        int selection;
        cout << "��ѡ����Ҫ���ĵ�����[����0�˳�]��" << endl;
        cout << "1��ְ����" << endl;
        cout << "2������" << endl;
        cout << "3���Ա�" << endl;
        cout << "4������" << endl;
        cout << "5���������" << endl;
        cout << "6����ְ���" << endl;
        cin >> selection;
        while (selection != 0) {
            switch (selection) {
                case 1:
                    cout << "�������µ�ְ���ţ�";
                    cin.get();
                    getline(cin, data->code);
                    break;
                case 2:
                    cout << "�������µ�������";
                    cin.get();
                    getline(cin, data->name);
                    break;
                case 3:
                    cout << "�������µ��Ա�[0Ů/1��]��";
                    cin >> data->gender;
                    break;
                case 4:
                    cout << "�������µĹ��ʣ�";
                    cin >> data->wage;
                    break;
                case 5:
                    cout << "�������µĳ�����ݣ�";
                    cin >> data->birth_year;
                    break;
                case 6:
                    cout << "�������µ���ְ��ݣ�";
                    cin >> data->work_year;
                    break;
            }
            cout << "��ѡ����Ҫ���ĵ�����[����0�˳�]��" << endl;
            cout << "1��ְ����" << endl;
            cout << "2������" << endl;
            cout << "3���Ա�" << endl;
            cout << "4������" << endl;
            cout << "5���������" << endl;
            cout << "6����ְ���" << endl;
            cin >> selection;
        }
        cout << "�޸ĺ���Ϣ��" << endl;
        cout << right << setw(10) << "ְ��" << setw(10) << "ְ����" << setw(10) << "����" << setw(10) << "�Ա�"
             << setw(10) << "����" << setw(10) << "����" << setw(10) << "����ʱ��" << endl;
        cout << right << *data << endl;
    } else {
        cout << "δѰ�ҵ���Ӧ��Ϣ��" << endl;
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

int List::show_graph() {
    Node *current = getHead()->getNext();
    int length = getCount();
    double number[5] = {0.0};
    if (isEmpty()) {
        cout << "û�����ݣ�" << endl;
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
    cout << "����ֲ��ٷֱ�ͳ��ͼ" << endl;
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
    cout << "ְ����Ϣ��¼" << endl;
    cout << "1.����һλ��ʦ��¼" << endl;
    cout << "2.����һλ���˼�¼" << endl;
    cout << "3.��ʾȫ��ְ����¼" << endl;
    cout << "4.��ʾְ����Ϣ���" << endl;
    cout << "5.�����ʦƽ������" << endl;
    cout << "6.���㹤��ƽ������" << endl;
    cout << "7.ɾ��һ����ʦ" << endl;
    cout << "8.ɾ��һ������" << endl;
    cout << "9.����������������Ϣ" << endl;
    cout << "10.���������������Ϣ" << endl;
    cout << "11.����ȫ����Ա������ͳ������ͼ" << endl;
    cout << "12.�޸���Ϣ" << endl;
    cout << "0.������������" << endl;

    cin >> selection;
    return selection;
}

int main() {
    List *list = new List;
    list->read_data();
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
            case 4://��ʾȫ��ְ�����
                list->show_simple_data();
                break;
            case 5://�����ʦƽ������
                list->calc_ave_teacher_age();
                break;
            case 6://���㹤��ƽ������
                list->calc_ave_worker_age();
                break;
            case 7://ɾ��һ����ʦ
                list->delete_teacher();
                break;
            case 8://ɾ��һ������
                list->delete_worker();
                break;
            case 9://����������������Ϣ
                list->find_by_name();
                break;
            case 10://����������������Ϣ
                list->find_by_age();
                break;
            case 11://����ͳ��ͼ
                list->show_graph();
                break;
            case 12://�޸�����
                list->modify();
                break;
            default:
                cout << "��������ȷ�������֣�" << endl;
                break;
        }
        selection = show_function();
    }
    list->save_data();
    return 0;
}
