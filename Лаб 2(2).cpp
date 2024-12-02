#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <string>
#include <iostream>
#include <limits>
#include <vector> 
#include <algorithm>
#include <stdexcept>
#include <list>

int fields1;
// Класс для помощи с вводом
class Help {
public:
    static int inputInteger() {
        int value;
        while (true) {
            std::cin >> value;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка! Введите целое число." << std::endl;
            }
            else {
                return value;
            }
        }
    }

    static int inputIntegerInRange(int min, int max) {
        int value;
        while (true) {
            value = inputInteger();
            if (value >= min && value <= max) {
                return value;
            }
            else {
                std::cout << "Ошибка! Введите число в пределах от " << min << " до " << max << "." << std::endl;
            }
        }
    }
};

// Абстрактный класс AbstractPlant
class AbstractPlant {
public:
    virtual void inputPlant() = 0; // Чистая виртуальная функция
    virtual void displayPlant(std::ostream& os) const = 0; // Чистая виртуальная функция для отображения деталей растения
    virtual std::string getPlantName() const = 0;
    virtual int getPlantYield() const = 0;
    virtual int getPlantPrice() const = 0;
    virtual ~AbstractPlant() = default; // Виртуальный деструктор для безопасного удаления через указатель базового класса
    virtual AbstractPlant* clone() const = 0;
};

// Базовый класс Plant
class Plant : public AbstractPlant {
protected:
    std::string name;
    int growthTime;
    int yield;
    int price;

public:
    Plant(std::string name = "Нет растения", int growthTime = 0, int yield = 0, int price = 0)
        : name(name), growthTime(growthTime), yield(yield), price(price) {}

    void inputPlant() override {
        while (true) {
            try {
                std::cout << "Введите название растения: ";
                std::cin >> name;
                if (name.empty()) throw std::invalid_argument("Название растения не может быть пустым!");

                std::cout << "Введите время роста (в днях): ";
                growthTime = Help::inputInteger();
                if (growthTime <= 0) throw std::invalid_argument("Время роста должно быть положительным!");

                std::cout << "Введите урожайность: ";
                yield = Help::inputInteger();
                if (yield < 0) throw std::invalid_argument("Урожайность не может быть отрицательной!");

                std::cout << "Введите цену: ";
                price = Help::inputInteger();
                if (price < 0) throw std::invalid_argument("Цена не может быть отрицательной!");

                break;
            }
            catch (const std::invalid_argument& e) {
                std::cout << "Ошибка: " << e.what() << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }

    void displayPlant(std::ostream& os) const override {
        os << "Растение: " << name
            << ", Время роста: " << growthTime << " дней, Урожайность: " << yield
            << ", Цена: " << price << " руб.\n";
    }

    AbstractPlant* clone() const override {
        return new Plant(*this);
    }

    std::string getPlantName() const override { return name; }
    int getPlantYield() const override { return yield; }
    int getPlantPrice() const override { return price; }
};

// Производный класс Fruits
class Fruits : public Plant {
private:
    std::string season;

public:
    Fruits(std::string name = "Нет фрукта", int growthTime = 0, int yield = 0, int price = 0, std::string season = "Неизвестно")
        : Plant(name, growthTime, yield, price), season(season) {}

    void inputPlant() override {
        Plant::inputPlant();
        std::cout << "Введите сезон для фрукта: ";
        std::cin >> season;
    }

    void displayPlant(std::ostream& os) const override {
        Plant::displayPlant(os);
        os << "Сезон: " << season << "\n";
    }

    AbstractPlant* clone() const override {
        return new Fruits(*this);
    }

    std::string getSeason() const { return season; }
};

// Класс Field (поле)
class Field {
private:
    int id;
    AbstractPlant* plant;
    bool isPlanted;

public:
    Field(int id = 0, AbstractPlant* plant = nullptr, bool isPlanted = false)
        : id(id), plant(plant), isPlanted(isPlanted) {}

    ~Field() {
        delete plant;
    }

    // Конструктор копирования
    Field(const Field& other)
        : id(other.id), isPlanted(other.isPlanted) {
        plant = other.plant ? other.plant->clone() : nullptr;
    }

    // Оператор копирующего присваивания
    Field& operator=(const Field& other) {
        if (this == &other) {
            return *this;
        }

        delete plant;
        id = other.id;
        isPlanted = other.isPlanted;
        plant = other.plant ? other.plant->clone() : nullptr;

        return *this;
    }

    // Конструктор перемещения
    Field(Field&& other) noexcept
        : id(other.id), plant(other.plant), isPlanted(other.isPlanted) {
        other.plant = nullptr;
    }

    // Оператор перемещающего присваивания
    Field& operator=(Field&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        delete plant;
        id = other.id;
        isPlanted = other.isPlanted;
        plant = other.plant;
        other.plant = nullptr;

        return *this;
    }

    void inputField() {
        delete plant;
        plant = nullptr;

        std::cout << "Введите номер поля: ";
        id = Help::inputInteger();
        std::cout << "Поле засажено? (1 - да, 0 - нет): ";
        isPlanted = Help::inputIntegerInRange(0, 1);

        if (isPlanted) {
            std::cout << "Выберите тип растения (1 - обычное, 2 - фрукт): ";
            int choice = Help::inputIntegerInRange(1, 2);

            if (choice == 1) {
                plant = new Plant();
            }
            else {
                plant = new Fruits();
            }
            plant->inputPlant();
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Field& field) {
        os << "\nПоле " << field.id << ": ";
        if (field.isPlanted && field.plant) {
            field.plant->displayPlant(os);
        }
        else {
            os << "Поле не засажено";
        }
        return os;
    }

    AbstractPlant* harvestField() {
        if (isPlanted) {
            isPlanted = false;
            AbstractPlant* harvestedPlant = plant;
            plant = nullptr;
            return harvestedPlant;
        }
        return nullptr;
    }

    bool isFieldPlanted() const { return isPlanted; }
    AbstractPlant* getPlant() const { return plant; }
};


// Шаблонный класс Storage (склад)
template <typename T>
class Storage {
private:
    T* plant;
    static int sellcount;
    static int allmoney;

public:
    Storage() : plant(nullptr) {}
    ~Storage() { delete plant; }

    void addPlant(T* newPlant) {
        delete plant;
        plant = newPlant;
    }

    void printStorage(int i) const {
        std::cout << "\nСклад " << i + 1 << ": ";
        if (plant) {
            plant->displayPlant(std::cout);
        }
        else {
            std::cout << "Склад пуст" << std::endl;
        }
    }

    void sellStorage(int& money) {
        if (!plant) throw std::runtime_error("Склад пуст!");

        money = plant->getPlantYield() * plant->getPlantPrice();
        allmoney += money;
        sellcount++;
        delete plant;
        plant = nullptr;
    }

    static int getSellcount() { return sellcount; }
    static int getAllmoney() { return allmoney; }
};

template <typename T>
int Storage<T>::sellcount = 0;

template <typename T>
int Storage<T>::allmoney = 0;

// Класс Farm (ферма)
class Farm {
private:
    std::vector<Field> fields;
    std::vector<Storage<AbstractPlant>> storage;
    int money;

public:
    Farm(int numFields) : fields(numFields), storage(numFields), money(0) {}

    void input() {
        for (int i = 0; i < fields1; i++) {
            std::cout << "\nВведите данные для поля " << i + 1 << ":\n";
            fields[i].inputField();
        }
    }

    void print() const {
        std::cout << "------------------\n";
        std::cout << "Информация о ферме\n";
        std::cout << "------------------\n";
        std::cout << "Поля:\n";
        printf("------------------------------------------------------------------------------------------------");
        for (int i = 0; i < fields1; i++) {
            std::cout << fields[i];
            storage[i].printStorage(i);
        }
        printf("------------------------------------------------------------------------------------------------");
    }

    void logic() {
        for (int i = 0; i < fields1; i++) {
            AbstractPlant* harvestedPlant = fields[i].harvestField();
            storage[i].addPlant(harvestedPlant);
        }
        std::cout << "\nПередача урожая на склады завершена.\n";
    }

    void sell() {
        std::cout << "\nУкажите номер склада для продажи урожая: ";
        int sellnumber = Help::inputIntegerInRange(1, fields1);
        try {
            storage[sellnumber - 1].sellStorage(money);
            std::cout << "\nВыручка: " << money << " руб." << std::endl;
            std::cout << "Общая выручка: " << Storage<AbstractPlant>::getAllmoney() << ", Продаж: " << Storage<AbstractPlant>::getSellcount() << std::endl;
        }
        catch (const std::runtime_error& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    }

    AbstractPlant* findBestPlantWithFind(const std::vector<Field>& fields) {
        // Шаг 1: Создаем контейнер с указателями на растения
        std::vector<AbstractPlant*> plants;

        for (const auto& field : fields) {
            if (field.isFieldPlanted()) { // Поле засажено
                plants.push_back(field.getPlant());
            }
        }

        // Если растений нет, возвращаем nullptr
        if (plants.empty()) {
            std::cout << "\nНет доступных растений.\n";
            return nullptr;
        }

        // Шаг 2: Найти максимальный доход
        auto maxPlantIt = std::max_element(plants.begin(), plants.end(), [](AbstractPlant* a, AbstractPlant* b) {
            return (a->getPlantYield() * a->getPlantPrice()) < (b->getPlantYield() * b->getPlantPrice());
            });

        // Шаг 3: Найти растение с максимальным доходом через std::find
        auto bestPlantIt = std::find(plants.begin(), plants.end(), *maxPlantIt);

        // Если найдено, возвращаем указатель на растение
        if (bestPlantIt != plants.end()) {
            AbstractPlant* bestPlant = *bestPlantIt;
            std::cout << "\nЛучшее растение:\n";
            bestPlant->displayPlant(std::cout);
            std::cout << "Ожидаемый доход: " << (bestPlant->getPlantYield() * bestPlant->getPlantPrice()) << " руб.\n";
            return bestPlant;
        }

        return nullptr;
    }

    void findBestPlantWithFind() {
        AbstractPlant* bestPlant = findBestPlantWithFind(fields);

        if (!bestPlant) {
            std::cout << "\nРастение с максимальным доходом не найдено.\n";
        }
    }

    static bool compare(const Field& a, const Field& b) {
        return a.getPlant()->getPlantYield() > b.getPlant()->getPlantYield();
    }
    void sortFieldsByYield() {
        std::sort(begin(fields), end(fields), compare);
        std::cout << "\nПоля отсортированы по урожайности.\n";
    }
};


int main() {
    setlocale(LC_ALL, "Russian");
    system("color F0");
    std::cout << "Ферма\n";

    try {
        std::cout << "Введите количество полей (2-5): ";
        fields1 = Help::inputIntegerInRange(2, 5);

        Farm myFarm(fields1);

        myFarm.input();
        myFarm.print();
        myFarm.findBestPlantWithFind();
        myFarm.sortFieldsByYield();
        myFarm.print();
        myFarm.logic();
        myFarm.print();
        myFarm.sell();
        myFarm.sell();
    }
    catch (...) {
        std::cout << "Ошибка при работе программы." << std::endl;
    }

    return 0;
}


// Пример работы с двумерным массивом, использоваться в основной программе не будет
/*
const int rows = 2;  // Количество рядов на ферме
const int cols = 2;  // Количество столбцов на ферме

// Создание двумерного массива объектов Field (2x2)
Field farm1[rows][cols];

// Ввод данных для каждого поля
std::cout << "Введите данные для полей фермы:" << std::endl;
for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
        std::cout << "\nВведите данные для поля [" << i + 1 << "][" << j + 1 << "]:" << std::endl;
        farm1[i][j].inputField();
    }
}

// Вывод данных о полях фермы
std::cout << "\nИнформация о полях фермы:" << std::endl;
for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
        std::cout << "\nИнформация о поле [" << i + 1 << "][" << j + 1 << "]:" << std::endl;
        farm1[i][j].printField();
    }
}

// Поиск лучшего растения
Plant bestPlant;
for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
        if (farm1[i][j].isFieldPlanted()) {
            Plant currentPlant = farm1[i][j].getPlant();
            if (currentPlant.getPlantYield() > bestPlant.getPlantYield()) {
                bestPlant = currentPlant;
            }
        }
    }
}

std::cout << "\nЛучшее растение на ферме: " << bestPlant.getPlantName()
    << " с урожайностью: " << bestPlant.getPlantYield() << std::endl;
*/

