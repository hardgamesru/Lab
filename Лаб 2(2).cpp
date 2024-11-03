#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <string>
#include <iostream>

int fields1;

class Plant {
private:
    std::string name;
    int growthTime; // Время роста в днях
    int yield; // Урожайность
    int price; // Цена

public:
    Plant(std::string name = "Нет растения", int growthTime = 0, int yield = 0, int price = 0)
        : name(name), growthTime(growthTime), yield(yield), price(price) {}

    void inputPlant() {
        std::cout << "Введите название растения: ";
        std::cin >> this->name; // this для повышения читаемости
        std::cout << "Введите время роста (в днях): ";
        std::cin >> this->growthTime;
        std::cout << "Введите урожайность: ";
        std::cin >> this->yield;
        std::cout << "Введите цену: ";
        std::cin >> this->price;
    }

    void printPlant() const {
        std::cout << "Растение: " << name << ", Время роста: " << growthTime << " дней, Урожайность: " << yield << " , Цена: " << price << " руб." << std::endl;
    }

    std::string getPlantName() const {
        return name;
    }

    int getPlantYield() const {
        return yield;
    }

    int getPlantPrice() const {
        return price;
    }
    // Разумное использование оператора this, оператора +
    Plant operator+(const Plant& other) const {
        return Plant(this->name + " + " + other.name,
            this->growthTime,
            this->yield + other.yield,
            (this->price + other.price) / 2); // Средняя цена
    }

    Plant& operator++() {
        ++yield; // Увеличиваем урожайность на 1
        return *this; // Возвращаем текущий объект
    }

    Plant operator++(int) {
        Plant temp = *this; // Сохраняем текущее состояние
        ++yield; // Увеличиваем урожайность на 1
        return temp; // Возвращаем старое состояние
    }

};

class Field {
private:
    int id;
    Plant plant;
    bool isPlanted; // true если поле засажено, false если нет

public:
    Field(int id = 0, Plant plant = Plant(), bool isPlanted = false)
        : id(id), plant(plant), isPlanted(isPlanted) {}

    void inputField() {
        std::cout << "Введите номер поля: ";
        std::cin >> id;
        std::cout << "Поле засажено? (1 - да, 0 - нет): ";
        std::cin >> isPlanted;
        if (isPlanted) {
            plant.inputPlant();
        }
        else {
            plant = Plant();
        }
    }

    void printField() const {
        std::cout << "\nПоле " << id << ": ";
        if (isPlanted) {
            plant.printPlant();
        }
        else {
            std::cout << "Поле не засажено" << std::endl;
        }
    }

    int harvestField() {
        if (isPlanted) {
            isPlanted = false;
        }
        return 0;
    }

    Plant getPlant() const {
        return plant;
    }

    bool isFieldPlanted() const {
        return isPlanted;
    }

    friend bool compareYield(const Plant& p1, const Plant& p2); // Дружественная функция

};

bool compareYield(const Plant& p1, const Plant& p2) {
    return p1.getPlantYield() > p2.getPlantYield();
}

class Storage {
private:
    Plant plant;
    std::string plantName;
    int plantYield;
    int plantPrice;
    int money; // выручка
    static int sellcount; // статическая переменная для количества продаж
    static int allmoney; // выручка от всех продаж

public:
    Storage(Plant plant = Plant(), std::string plantName = "Нет растения", int plantYield = 0, int plantPrice = 0, int money = 0)
        : plantYield(plantYield), plantPrice(plantPrice) {}

    void printStorage(int i) const {
        std::cout << "\nСклад " << i + 1 << ": Название растения : " << plant.getPlantName() << ", Урожаемость растения : " << plant.getPlantYield() << ", Цена за единицу : " << plant.getPlantPrice() << " руб." << std::endl;
    }

    void addPlant(Plant plant1) {
        plant = plant1;
    }

    void sellStorage(int* money) {
        *money = plant.getPlantYield() * plant.getPlantPrice();
        allmoney += *money;
        sellcount++;
        plant = Plant();
    }

    void sellStorageRef(int& money) {
        money = plant.getPlantYield() * plant.getPlantPrice();
        allmoney += money;
        sellcount++;
        plant = Plant();
    }

    static int getSellcount() {
        return sellcount;
    }

    static int getAllmoney() {
        return allmoney;
    }
};

int Storage::sellcount = 0;
int Storage::allmoney = 0;

class Farm {
private:
    Field fields[5];
    Storage storage[5];
    int money;
public:
    Farm() {
        for (int i = 0; i < fields1; i++) {
            fields[i] = Field(i);
        }
    }

    void input() {
        for (int i = 0; i < fields1; ++i) {
            std::cout << "\nВведите данные для поля\n";
            fields[i].inputField();
        }
    }

    void print() const {
        std::cout << "------------------\n";
        std::cout << "Информация о ферме\n";
        std::cout << "------------------\n";
        std::cout << "Поля:\n";
        printf("------------------------------------------------------------------------------------------------");
        for (int i = 0; i < fields1; ++i) {
            fields[i].printField();
            storage[i].printStorage(i);
        }
        printf("------------------------------------------------------------------------------------------------");

    }

    void logic() {
        for (int i = 0; i < fields1; ++i) {
            storage[i].addPlant(fields[i].getPlant());
            fields[i].harvestField();
        }
        printf("\nПередача на склады\n");
    }

    void sell() { // через указатель
        int sellnumber;
        printf("\nУрожай какого склада вы бы хотели продать?: ");
        std::cin >> sellnumber;
        printf("\nПродажа урожая со склада %d (через указатель)", sellnumber);
        storage[sellnumber - 1].sellStorage(&money);
        printf("\n\nКоличество денег с продажи склада- %d\n", money);
        printf("\nОбщее количество денег с продаж %d, количество продаж - %d\n", Storage::getAllmoney(), Storage::getSellcount());
    }

    void sellref() { // через ссылку
        int sellnumber;
        printf("\nУрожай какого склада вы бы хотели продать?: ");
        std::cin >> sellnumber;
        printf("\nПродажа урожая со склада %d (через ссылку)", sellnumber);
        storage[sellnumber - 1].sellStorageRef(money);
        printf("\n\nКоличество денег с продажи склада- %d\n", money);
        printf("\nОбщее количество денег с продаж %d, количество продаж - %d\n", Storage::getAllmoney(), Storage::getSellcount());
    }

    Plant findBestPlant() const {
        Plant bestPlant = Plant(); // Начальное значение "Нет растения"
        for (int i = 0; i < fields1; ++i) {
            if (fields[i].isFieldPlanted()) {
                const Plant& currentPlant = fields[i].getPlant();
                if (compareYield(currentPlant, bestPlant)) {
                    bestPlant = currentPlant;
                }
            }
        }
        return bestPlant;
    }

};


int main() {
    setlocale(LC_ALL, "Russian");
    system("color F0");

    printf("Ферма\n");

    printf("Введите количество полей:\n");
    scanf("%d", &fields1);
    Farm myFarm;
    // Ввод данных о ферме
    myFarm.input();

    // Вывод информации о ферме
    myFarm.print();

    Plant bestPlant = myFarm.findBestPlant();
    if (bestPlant.getPlantName() != "Нет растения") {
        std::cout << "\nЛучшее растение: " << bestPlant.getPlantName()
            << " с урожайностью: " << bestPlant.getPlantYield() << std::endl;
    }
    else {
        std::cout << "\nНет засаженных растений." << std::endl;
    }
    // Выполняем основную логику 
    myFarm.logic();

    // Выводим обновленную информацию о ферме
    myFarm.print();

    myFarm.sell();

    myFarm.print();

    myFarm.sellref();

    myFarm.print();


    /*
    // Работа с динамическим массивом объектов класса
    fields1 = 1;
    Farm* dynamicFarms = new Farm[2];
    printf("\nРабота с динамическим массивом объектов класса\n");
    for (int i = 0; i < 2; ++i) {
        std::cout << "\nВведите данные для фермы " << i + 1<< ":\n";
        dynamicFarms[i].input();
    }
    for (int i = 0; i < 2; ++i) {
        dynamicFarms[i].print();
        dynamicFarms[i].logic();
        dynamicFarms[i].print();
    }
    delete[] dynamicFarms;

    // Работа с массивом динамических объектов класса
    printf("\nРабота с массивом динамических объектов класса\n");
    Farm* dynamicFarmArray[2];
    for (int i = 0; i < 2; ++i) {
        dynamicFarmArray[i] = new Farm();
        std::cout << "\nВведите данные для фермы " << i << ":\n";
        dynamicFarmArray[i]->input();
    }
    for (int i = 0; i < 2; ++i) {
        dynamicFarmArray[i]->print();
        dynamicFarmArray[i]->logic();
        dynamicFarmArray[i]->print();
        delete dynamicFarmArray[i];
    }
    */

    /* Пример использования операторов +, ++
    Plant plant1("Томаты", 60, 10, 50);
    Plant plant2("Огурцы", 50, 15, 40);

    // Используем оператор '+'
    Plant combinedPlant = plant1 + plant2;
    combinedPlant.printPlant();

    // Используем префиксный оператор '++'
    ++combinedPlant;
    combinedPlant.printPlant();

    // Используем постфиксный оператор '++'
    Plant oldPlant = combinedPlant++;
    oldPlant.printPlant(); // Выводим старое состояние
    combinedPlant.printPlant(); // Выводим новое состояние

    return 0;

    */
}