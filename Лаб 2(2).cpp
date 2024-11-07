#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <string>
#include <iostream>
#include <limits> // Для std::numeric_limits
#include <stdexcept> // Для исключений

int fields1;

class Help {
public:
    // Метод для ввода целого числа с проверкой на корректность
    static int inputInteger() {
        int value;
        while (true) {
            std::cin >> value;

            // Проверяем, не возникла ли ошибка ввода
            if (std::cin.fail()) {
                std::cin.clear(); // Очищаем флаг ошибки
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер
                std::cout << "Ошибка! Введите целое число." << std::endl;
            }
            else {
                // Ввод корректен
                return value;
            }
        }
    }

    // Метод для ввода целого числа с дополнительной проверкой диапазона
    static int inputIntegerInRange(int min, int max) {
        int value;
        while (true) {
            value = inputInteger(); // Используем первый метод для ввода числа
            if (value >= min && value <= max) {
                return value;
            }
            else {
                std::cout << "Ошибка! Введите число в пределах от " << min << " до " << max << "." << std::endl;
            }
        }
    }
};

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
        while (true) {
            try {
                std::cout << "Введите название растения: ";

                std::cin >> this->name; // this для повышения читаемости
                if (this->name.empty()) {
                    throw std::invalid_argument("Название растения не может быть пустым!");
                }

                std::cout << "Введите время роста (в днях): ";
                this->growthTime = Help::inputInteger();
                if (this->growthTime <= 0) {
                    throw std::invalid_argument("Время роста должно быть положительным числом!");
                }

                std::cout << "Введите урожайность : ";
                this->yield = Help::inputInteger();
                if (this->yield < 0) {
                    throw std::invalid_argument("Урожайность не может быть отрицательной!");
                }

                std::cout << "Введите цену: ";
                this->price = Help::inputInteger();
                if (this->price < 0) {
                    throw std::invalid_argument("Цена не может быть отрицательной!");
                }

                break; // Если все данные введены корректно, выходим из цикла

            }
            catch (const std::invalid_argument& e) {
                std::cout << "Ошибка: " << e.what() << std::endl;
                std::cin.clear(); // Очищаем ошибку ввода
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер ввода
            }
        }
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
        while (true) {
            try {

                std::cout << "Введите номер поля: ";
                id = Help::inputInteger();
                if (id <= 0) {
                    throw std::out_of_range("Номер поля должен быть положительным!");
                }

                std::cout << "Поле засажено? (1 - да, 0 - нет): ";
                isPlanted = Help::inputIntegerInRange(0, 1);
                if (isPlanted) {
                    plant.inputPlant();
                }
                else {
                    plant = Plant();
                }
                break; // Если все данные введены корректно, выходим из цикла

            }

            catch (const std::out_of_range& e) {
                std::cout << "Ошибка: " << e.what() << std::endl;
            }
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
        : plantYield(plantYield), plantPrice(plantPrice), money(money) {}

    void printStorage(int i) const {
        std::cout << "\nСклад " << i + 1 << ": Название растения : " << plant.getPlantName() << ", Урожаемость растения : " << plant.getPlantYield() << ", Цена за единицу : " << plant.getPlantPrice() << " руб." << std::endl;
    }

    void addPlant(Plant plant1) {
        plant = plant1;
    }

    void sellStorage(int* money) {
        if (plant.getPlantName() == "Нет растения") {
            throw std::runtime_error("Невозможно продать урожай, склад пуст!");
        }

        *money = plant.getPlantYield() * plant.getPlantPrice();
        allmoney += *money;
        sellcount++;
        plant = Plant(); // После продажи склад очищается
    }


    void sellStorageRef(int& money) {
        if (plant.getPlantName() == "Нет растения") {
            throw std::runtime_error("Невозможно продать урожай, склад пуст!");
        }

        money = plant.getPlantYield() * plant.getPlantPrice();
        allmoney += money;
        sellcount++;
        plant = Plant(); // После продажи склад очищается
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
        try {
            printf("\nУрожай какого склада вы бы хотели продать?: ");
            sellnumber = Help::inputIntegerInRange(1, fields1);
            printf("\nПродажа урожая со склада %d (через указатель)\n", sellnumber);
            storage[sellnumber - 1].sellStorage(&money);
            printf("\nКоличество денег с продажи склада- %d\n", money);
            printf("\nОбщее количество денег с продаж %d, количество продаж - %d\n", Storage::getAllmoney(), Storage::getSellcount());
        }
        catch (const std::runtime_error& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    }

    void sellref() { // через ссылку
        int sellnumber;
        try {
            printf("\nУрожай какого склада вы бы хотели продать?: ");
            sellnumber = Help::inputIntegerInRange(1, fields1);
            printf("\nПродажа урожая со склада %d (через ссылку)\n", sellnumber);
            storage[sellnumber - 1].sellStorageRef(money);
            printf("\nКоличество денег с продажи склада- %d\n", money);
            printf("\nОбщее количество денег с продаж %d, количество продаж - %d\n", Storage::getAllmoney(), Storage::getSellcount());
        }
        catch (const std::runtime_error& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
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

    try {
        printf("Введите количество полей : ");
        fields1 = Help::inputIntegerInRange(2, 5); // Используем метод для ввода

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
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
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
    return 0;
}
