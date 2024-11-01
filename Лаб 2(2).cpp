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
        std::cin >> name;
        std::cout << "Введите время роста (в днях): ";
        std::cin >> growthTime;
        std::cout << "Введите урожайность: ";
        std::cin >> yield;
        std::cout << "Введите цену: ";
        std::cin >> price;
    }

    void printPlant() const {
        std::cout << "Растение: " << name << ", Время роста: " << growthTime << " дней, Урожайность: " << yield << " , Цена: " << price << "руб" <<std::endl;
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

    Plant getPlant() {
        return plant;
    }
};

class Storage {
private:
    Plant plant;
    std::string plantName;
    int plantYield;
    int plantPrice;
    int money;

public:
    Storage(Plant plant = Plant(), std::string plantName = "Нет растения", int plantYield = 0, int plantPrice = 0, int money = 0)
        : plantYield(plantYield), plantPrice(plantPrice) {}

    void printStorage(int i) const {
        std::cout << "\nСклад" << i <<": Название растения : " << plant.getPlantName() << ", Урожаемость растения : " << plant.getPlantYield() << ", Цена за единицу : " << plant.getPlantPrice() << " руб." << std::endl;
    }

    void addPlant(Plant plant1){
        plant = plant1;
    }

    int sellStorage() {
        money = plant.getPlantYield()* plant.getPlantPrice();
        plant = Plant();
        return money;
    }
};

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
        std::cout << "\nИнформация о ферме\n";
        std::cout << "Поля:\n";
        for (int i = 0; i < fields1; ++i) {
            fields[i].printField();
            storage[i].printStorage(i);
        }
        
    }

    void logic() {
        for (int i = 0; i < fields1; ++i) {
            storage[i].addPlant(fields[i].getPlant());
            fields[i].harvestField();
        }
        printf("\nПередача на склады\n");
    }

    void sell() {
        int sellnumber, money;
        printf("\nУрожай какого склада вы бы хотели продать?: ");
        std::cin >> sellnumber;
        printf("\nПродажа урожая со склада %d", sellnumber);
        money = storage[sellnumber-1].sellStorage();
        printf("\n\nОбщее количество денег - %d\n", money);
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

    // Выполняем основную логику 
    myFarm.logic();

    // Выводим обновленную информацию о ферме
    myFarm.print();

    myFarm.sell();

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
    return 0;
}