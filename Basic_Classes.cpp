#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void capitalizeWords(char* text) {
    bool capitalizeNext = true;
    unsigned char* ptr = reinterpret_cast<unsigned char*>(text);
    while (*ptr) {
        if (*ptr >= 0xD0 && *ptr <= 0xD1) {
            if (capitalizeNext) {
                if (*ptr == 0xD0 && *(ptr + 1) >= 0xB0 && *(ptr + 1) <= 0xBF) {
                    *(ptr + 1) -= 0x20;
                } else if (*ptr == 0xD1 && *(ptr + 1) >= 0x80 && *(ptr + 1) <= 0x8F) {
                    *(ptr + 1) -= 0x20;
                }
                capitalizeNext = false;
            }
            ptr += 2;
        } else if (isspace(*ptr)) {
            capitalizeNext = true;
            ptr++;
        } else {
            capitalizeNext = false;
            ptr++;
        }
    }
}

class post {
   private:
    char* street;
    char* city;
    unsigned int index;
    unsigned short int num;

   public:
    bool correct(const string& mas) {
        for (char ch : mas) {
            if (strchr("~@#$%^*<>_=+`\\/|!()", ch)) {
                return false;
            }
        }
        return true;
    }

    bool hasDigit(const string& s) {
        for (char ch : s) {
            if (isdigit(ch)) {  // Если символ цифра
                return true;
            }
        }
        return false;  // Если цифр нет
    }

    post(const char* s, const char* c, unsigned int i, unsigned short int nm) {
        city = new char[strlen(c) + 1];
        street = new char[strlen(s) + 1];
        strcpy(city, c);
        strcpy(street, s);
        num = nm;
        index = i;
    }
    // Конструктор для ввода данных с консоли
    post() {
        cin.ignore(10000, '\n');
        cout << "Введите город : ";
        char temp[41];  // временное хранилище для ввода
        while (true) {
            cin.getline(temp, 41);
            if (cin.fail() || !correct(temp) || hasDigit(temp) || strlen(temp) > 40) {
                cout << "Некорректный ввод!" << endl;
                cin.clear();
            } else {
                city = new char[strlen(temp) + 1];
                strcpy(city, temp);
                capitalizeWords(city);
                break;
            }
        }

        cout << "Введите улицу : ";
        while (true) {
            cin.getline(temp, 41);
            if (cin.fail() || !correct(temp) || hasDigit(temp) || strlen(temp) > 40) {
                cout << "Некорректный ввод!" << endl;
                cin.clear();
            } else {
                street = new char[strlen(temp) + 1];
                strcpy(street, temp);
                capitalizeWords(street);
                break;
            }
        }

        cout << "Введите номер дома : ";
        while (true) {
            cin >> num;
            if (cin.fail() || num <= 0 || num > 100 || cin.peek() != '\n') {
                cout << "Некорректный ввод!" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            } else
                break;
        }

        cout << "Введите индекс : ";
        while (true) {
            cin.clear();
            cin >> index;
            if (cin.fail() || index < 100000 || index >= 1000000 || cin.peek() != '\n') {
                cout << "Некорректный ввод!" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            } else
                break;
        }
    }

    ~post() {
        delete[] street;  // Освобождаем память
        delete[] city;    // Освобождаем память
    }

    bool set_street(const char* s) {
        if (correct(s) && strlen(s) < 40 && !hasDigit(s)) {
            street = new char[strlen(s) + 1];
            strcpy(street, s);
            return true;
        }
        return false;
    }

    bool set_index(unsigned int i) {
        if (i < 1000000 && i > 99999 && cin.peek() == '\n') {
            index = i;
            return true;
        }
        return false;
    }
    bool set_city(const char* c) {
        if (correct(c) && strlen(c) < 40 && !hasDigit(c)) {
            city = new char[strlen(c) + 1];
            strcpy(city, c);
            return true;
        }
        return false;
    }

    bool set_num(unsigned short int nm) {
        if (nm == 0) return false;
        num = nm;
        return true;
    }

    const char* get_city() const { return (city == nullptr || city[0] == '\0') ? "Пусто!" : city; }

    const char* get_street() const { return (street == nullptr || street[0] == '\0') ? "Пусто!" : street; }

    unsigned int get_index() const { return index; }
    unsigned short int get_num() const { return num; }
};

class company : public post {
   private:
    char* name;
    unsigned int kolvo;
    int capital;

   public:
    // Конструктор для ввода данных с консоли
    company() : post() {  // Вызов конструктора post для ввода адресных данных
        cin.ignore(10000, '\n');
        cout << "Введите название компании: ";
        char temp[41];  // временное хранилище для ввода
        while (true) {
            cin.getline(temp, 41);
            if (cin.fail() || !correct(temp) || strlen(temp) > 40) {
                cout << "Некорректный ввод!" << endl;
                cin.clear();
            } else {
                name = new char[strlen(temp) + 1];
                strcpy(name, temp);
                capitalizeWords(name);
                break;
            }
        }

        cout << "Введите количество работников: ";
        while (true) {
            cin >> kolvo;
            if (cin.fail() || kolvo <= 0 || kolvo > 5000 || cin.peek() != '\n') {
                cout << "Некорректный ввод!" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            } else
                break;
        }

        cout << "Введите капитал: ";
        while (true) {
            cin >> capital;
            if (cin.fail() || capital <= 0 || capital > 50000000 || cin.peek() != '\n') {
                cout << "Некорректный ввод!" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            } else
                break;
        }
    }

    ~company() {
        delete[] name;  // Освобождаем память
    }

    // Конструктор с параметрами
    company(const char* n, const char* s, const char* c, unsigned int i, unsigned short int nm,
            unsigned int k, int cap)
        : post(s, c, i, nm), kolvo(k), capital(cap) {}

    bool set_name(const char* n) {
        if (correct(n) && strlen(n) <= 40) {
            name = new char[strlen(n) + 1];
            strcpy(name, n);
            return true;
        }
        return false;
    }

    bool set_kolvo(unsigned int k) {
        if (k <= 0) return false;
        kolvo = k;
        return true;
    }

    // Методы для установки и получения данных
    void set_capital(int cap) { capital = cap; }

    const char* get_name() const { return (name && strlen(name) > 0) ? name : "Пусто!"; }

    int get_kolvo() const { return kolvo; }
    int get_capital() const { return capital; }
};

int main() {
    setlocale(LC_ALL, "");
    int n, intm;
    char ch;
    char str[41];
    int num;
    while (true) {
        cout << "Введите количество компаний :";
        cin >> n;
        if (n > 10 || n < 1 || cin.peek() != '\n') {
            cout << "Некорректный ввод!" << endl;
            cin.clear();
            while (cin.get() != '\n')
                ;
        } else {
            break;
        }
    }
    company* companies = new company[n];

    do {
        cout << " V - Просмотреть компании;\n"
                " С - Изменить данные компаний;\n"
                " E - Выйти;\n"
                " Введите команду:";
        cin >> ch;
        ch = toupper(ch);
        switch (ch) {
            case 'V':
                for (int i = 0; i < n; i++) {
                    cout << "\n№" << i + 1 << " Компания: " << companies[i].get_name()
                         << " Индекс: " << companies[i].get_index() << " Город: " << companies[i].get_city()
                         << " Улица: " << companies[i].get_street()
                         << " Номер дома: " << companies[i].get_num()
                         << " К-во работников: " << companies[i].get_kolvo()
                         << " Капитал: " << companies[i].get_capital() << endl;
                }
                break;

            case 'C':
                while (true) {
                    printf("Введите номер компании:");
                    cin >> intm;
                    intm--;
                    if (cin.fail() || intm < 0 || intm >= n || cin.peek() != '\n') {
                        cout << "Некорректный ввод!" << endl;
                        cin.clear();
                        while (cin.get() != '\n')
                            ;
                    } else {
                        break;
                    }
                }
                do {
                    cout << " N - Изменить название\n"
                            " S - Изменить улицу\n"
                            " C - Изменить город\n"
                            " I - Изменить индекс\n"
                            " H - Изменить номер дома\n"
                            " K - Изменить к-во работников\n"
                            " M - Изменить капитал\n"
                            " Y - Выйти\n"
                            " Введите команду:";
                    cin >> ch;
                    ch = toupper(ch);
                    switch (ch) {
                        case 'K':
                            cout << "Введите новое количество работников\n";
                            cin >> num;
                            if (cin.fail() || num <= 0 || num > 5000 || cin.peek() != '\n') {
                                cout << "Некорректный ввод!\n" << endl;
                                cin.clear();
                                while (cin.get() != '\n')
                                    ;
                                break;
                            }
                            if (companies[intm].set_kolvo(num)) {  // index
                                cout << "Данные изменены успешно\n";
                            } else {
                                cout << "Некорректный ввод!\n";
                            }
                            break;
                            break;
                        case 'N':
                            cout << "Введите новое название:\n";
                            cin.ignore();
                            cin.getline(str, 40);
                            capitalizeWords(str);
                            if (companies[intm].set_name(str)) {
                                cout << "Данные изменены успешно\n";
                            } else {
                                cout << "Некорректный ввод!\n";
                            }
                            break;
                        case 'S':
                            cout << "Введите новую улицу\n";
                            cin.ignore();
                            cin.getline(str, 40);
                            capitalizeWords(str);
                            if (companies[intm].set_street(str)) {
                                cout << "Данные изменены успешно\n";
                            } else {
                                cout << "Некорректный ввод!\n";
                            }
                            break;
                        case 'C':
                            cout << "Введите новый город\n";
                            cin.ignore();
                            cin.getline(str, 40);
                            capitalizeWords(str);
                            if (companies[intm].set_city(str)) {
                                cout << "Данные изменены успешно\n";
                            } else {
                                cout << "Некорректный ввод!\n";
                            }
                            break;
                        case 'I':
                            cout << "Введите новый индекс\n";
                            cin >> num;
                            if (cin.fail()) {
                                cout << "Некорректный ввод!\n" << endl;
                                cin.clear();
                                while (cin.get() != '\n')
                                    ;
                                break;
                            }
                            if (companies[intm].set_index(num)) {
                                cout << "Данные изменены успешно\n";
                            } else {
                                cout << "Некорректный ввод!\n";
                            }
                            break;
                        case 'H':
                            cout << "Введите новый номер дома\n";
                            cin >> num;
                            if (cin.fail() || num <= 0 || num > 100 || cin.peek() != '\n') {
                                cout << "Некорректный ввод!" << endl;
                                cin.clear();
                                while (cin.get() != '\n')
                                    ;
                                break;
                            }
                            if (companies[intm].set_num(num)) {
                                cout << "Данные изменены успешно\n";
                            } else {
                                cout << "Некорректный ввод!\n";
                            }
                            break;
                        case 'M':
                            cout << "Введите новый капитал\n";
                            cin >> num;
                            if (cin.fail() || num <= 0 || num > 50000000 || cin.peek() != '\n') {
                                cout << "Некорректный ввод!\n" << endl;
                                cin.clear();
                                while (cin.get() != '\n')
                                    ;
                                break;
                            }
                            companies[intm].set_capital(num);
                            cout << "Данные изменены успешно\n";
                            break;
                        case 'Y':

                            break;
                        default:
                            cout << "Нет такой команды!\n";
                            break;
                    }
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } while (ch != 'Y');
                break;
            case 'E':
                break;

            default:
                cout << "Нет такой команды!\n";
                break;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (ch != 'E');
    delete[] companies;
    return 0;
}
