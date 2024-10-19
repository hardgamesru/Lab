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

public:
    Plant(std::string name = "None", int growthTime = 0, int yield = 0)
        : name(name), growthTime(growthTime), yield(yield) {}

    void inputPlant() {
        std::cout << "Введите название растения: ";
        std::cin >> name;
        std::cout << "Введите время роста (в днях): ";
        std::cin >> growthTime;
        std::cout << "Введите урожайность: ";
        std::cin >> yield;
    }

    void printPlant() const {
        std::cout << "Растение: " << name << ", Время роста: " << growthTime << " дней, Урожайность: " << yield << std::endl;
    }

    int getYieldPlant() const {
        return yield;
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
        std::cout << "Поле " << id << ": ";
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
            return plant.getYieldPlant();
        }
        return 0;
    }
};

class Storage {
private:
    int plantYield;
    int animalProducts;

public:
    Storage(int plantYield = 0, int animalProducts = 0)
        : plantYield(plantYield), animalProducts(animalProducts) {}

    void printStorage() const {
        std::cout << "\nСклад: Урожай растений: " << plantYield << std::endl;
    }

    void addPlantYieldStorage(int yield) {
        plantYield += yield;
    }

};

class Farm {
private:
    Field fields[5];
    Storage storage;
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
        }
        storage.printStorage();
    }

    void logic() {
        for (int i = 0; i < 2; ++i) {
            storage.addPlantYieldStorage(fields[i].harvestField());
        }
        printf("\nПередача на склад\n");
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

    return 0;
}