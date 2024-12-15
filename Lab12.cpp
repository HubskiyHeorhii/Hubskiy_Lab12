#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Computer { //клас комп'ютер
protected: //захищений
    string processor; //сам ПС
    int ram; //пам'ять ПС Random Access Memory
    int availableRam; //вільна пам'ять

public: //пуюлічний клас
    Computer(string proc, int ramSize)  //конструктор КОМП'ЮТЕР який ініціалізує елементи структури/класу
        : processor(proc), ram(ramSize), availableRam(ramSize) {}

    virtual void runProgram(const string& programName, int memoryUsage) { //функція яка запускає програму на ПС
        if (memoryUsage > availableRam) { //якщо пам'ять для використання більша за пам'ять пристрою то
            cout << "Not enough RAM to run the program: " << programName << endl; //виводить, якщо немає достатньо пам'яті для запуску програми
        } else {
            availableRam -= memoryUsage; //якщо менше чи дорвівнює то
            cout << "Running program: " << programName //вказує інформацію про програму(назва) 
                 << " on processor " << processor //на якому пристрої вона була запущена
                 << " with " << availableRam << " GB RAM remaining." << endl; //та скільки пам'яті використала
        }
    }

    virtual void displayInfo() { //віртуальний клас войд який показує всю інформацію про притсрої, що були створені
        cout << "Processor: " << processor //назва пристрою
             << ", RAM: " << ram << " GB" //початкова кількість пам'яті
             << ", Available RAM: " << availableRam << " GB" << endl; //скільки вільної зараз
    }

    virtual ~Computer() {} //віртуальний дестрктор классу комп'ютер, який очищає дані комп'ютера, щоб далі не зашкодти другому класу який буде привязаний
};

class Laptop : public Computer { //відносно умові привязуємо клас ноутбуку до ПК
private: //стоврюєио приватний клас
    double batteryLevel; //заносимо туди рівень батареї

public: //знову створюєио публічний клас
    Laptop(string proc, int ramSize, double battery = 100.0) //створюємо конструктор ноутбук, для ініціалізації його елементів взятих з комп'ютера
        : Computer(proc, ramSize), batteryLevel(battery) {}

    void runProgram(const string& programName, int memoryUsage) override { //перевизначає те, що було створено для комп'ютера, жд Ноутбуку
        if (batteryLevel <= 0) {
            cout << "Cannot run the program. Battery is empty." << endl;
        } else if (memoryUsage > availableRam) {
            cout << "Not enough RAM to run the program: " << programName << endl;
        } else { //якщо все нормально, то віднімається пам'ять(яку вказав користувач для відкриття програми) та -5% до батареї пристрою який обрали
            availableRam -= memoryUsage;
            batteryLevel -= 5.0;
            if (batteryLevel < 0) batteryLevel = 0;

            cout << "Running program: " << programName
                 << " on laptop with processor " << processor 
                 << ", " << availableRam << " GB RAM remaining, "
                 << "Battery: " << batteryLevel << "%" << endl;
        }
    }

    void displayInfo() override { //перевизначена функція з комп'ютера, яка показує всі пристрої
        Computer::displayInfo();
        cout << "Battery Level: " << batteryLevel << "%" << endl;
    }
};

void showMenu() { //менюшка
    cout << "\nMenu:\n";
    cout << "1. Create Computer" << endl; //створити ПК
    cout << "2. Create Laptop" << endl; //створити Ноут
    cout << "3. Run a program on a specific device" << endl; //запустити программу
    cout << "4. Display Info for all devices" << endl; //показати всі пристрої
    cout << "5. Exit" << endl; //вихід
    cout << "Choose an option: "; //обери опцію
}

int main() { //головна змінна
    vector<Computer*> devices; //зберігає все, що було створено з ПК та Ноти(бо вони пов'язані з ПК)
    int choice; //змінна вибору
    string processor;
    string programName;
    int ramSize; //розмір пам'яті
    int deviceIndex; //номер техніки для запуску 
    int memoryUsage; //використована пам'ять

    do {
        showMenu(); //постінйи вивід меню
        cin >> choice;
        cin.ignore(); //очищення даних меню минулих, перед виводу меню нового

        switch (choice) {
            case 1: 
                cout << "Enter processor: "; //вводимо інфу про ПК
                getline(cin, processor);
                cout << "Enter RAM size (GB): ";
                cin >> ramSize;
                cin.ignore(); 
                devices.push_back(new Computer(processor, ramSize));
                cout << "Computer created successfully!" << endl;
                break;

            case 2: 
                cout << "Enter processor: "; //вводимо інфу про Ноут
                getline(cin, processor); 
                cout << "Enter RAM size (GB): ";
                cin >> ramSize;
                cin.ignore();
                devices.push_back(new Laptop(processor, ramSize));
                cout << "Laptop created successfully!" << endl;
                break;

            case 3: //функція запуски прорам на пристрої
                if (devices.empty()) { 
                    cout << "No devices available!" << endl;
                    break;
                }
                cout << "Available devices: " << endl;
                for (size_t i = 0; i < devices.size(); ++i) {
                    cout << i + 1 << ". ";
                    devices[i]->displayInfo();
                }
                cout << "Select a device to run the program (1-" << devices.size() << "): "; //вибір пристрою за списком
                cin >> deviceIndex;
                cin.ignore();

                if (deviceIndex < 1 || deviceIndex > static_cast<int>(devices.size())) {
                    cout << "Invalid device selected!" << endl;
                } else {
                    cout << "Enter program name: "; //назва програми
                    getline(cin, programName);
                    cout << "Enter memory required by the program (GB): "; //скільки пам'яті їсть
                    cin >> memoryUsage;
                    cin.ignore();

                    devices[deviceIndex - 1]->runProgram(programName, memoryUsage);
                }
                break;

            case 4: //показує всі існуючі пристрої
                if (devices.empty()) {
                    cout << "No devices created yet!" << endl;
                } else {
                    cout << "All devices:" << endl;
                    for (size_t i = 0; i < devices.size(); ++i) {
                        cout << i + 1 << ". ";
                        devices[i]->displayInfo();
                    }
                }
                break;

            case 5: //кінець
                cout << "Exiting program..." << endl;
                break;

            default: //якщо під час вибору, була вказaна помилка
                cout << "Invalid option. Please try again." << endl;
        }

    } while (choice != 5); //обов'язково

    for (Computer* device : devices) { //звільнюємо пам'ять і тим самим все
        delete device; //кікаємо пристрої
    }

    return 0;
}

// -> - оператор застосовується до вказівників на об'єкти, щоб звертатися до їхніх методів або змінних.
// * - вказівник
// поліморфізм - дозволяє використовувати однакові інтерфейси для об'єктів різних класів, що дає змогу викликати різні реалізації методів у залежності від типу об'єкта, до якого належить цей метод.
// У цьому випадку ми маємо поліморфізм через віртуальні функції та перевизначення методів у похідному класі.
