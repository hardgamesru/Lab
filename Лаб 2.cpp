#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Структура для представления растения
typedef struct {
    char name[20];
    int growthTime; // Время роста в днях
    int yield; // Урожайность
} Plant;

// Структура для представления животного
typedef struct {
    char name[20];
    int age; // Возраст в годах
    int productivity; // Продуктивность (например, количество молока в л в день)
} Animal;

// Структура для представления поля
typedef struct {
    int id;
    Plant plant;
    int isPlanted; // 1 если поле засажено, 0 если нет
} Field;

// Структура для представления склада
typedef struct {
    int plantYield;
    int animalProducts;
} Storage;

// Структура для представления фермы
typedef struct {
    Field fields[10];
    Animal animals[10];
    Storage storage;
} Farm;

// Инициализации 
Plant createPlant(const char* name, int growthTime, int yield) {
    Plant plant;
    strcpy(plant.name, name);
    plant.growthTime = growthTime;
    plant.yield = yield;
    return plant;
}

Animal createAnimal(const char* name, int age, int productivity) {
    Animal animal;
    strcpy(animal.name, name);
    animal.age = age;
    animal.productivity = productivity;
    return animal;
}

Field createField(int id, Plant plant, int isPlanted) {
    Field field;
    field.id = id;
    field.plant = plant;
    field.isPlanted = isPlanted;
    return field;
}

Storage createStorage(int plantYield, int animalProducts) {
    Storage storage;
    storage.plantYield = plantYield;
    storage.animalProducts = animalProducts;
    return storage;
}

Farm createFarm() {
    Farm farm;
    for (int i = 0; i < 2; i++) {
        farm.fields[i] = createField(i, createPlant("", 0, 0), 0);
        farm.animals[i] = createAnimal("", 0, 0);
    }
    farm.storage = createStorage(0, 0);
    return farm;
}

// Функции для ввода
void inputPlant(Plant* plant) {
    while (getchar() != '\n');
    printf("Введите название растения: ");
    fgets(plant->name,20,stdin);
    printf("Введите время роста (в днях): ");
    scanf("%d", &plant->growthTime);
    printf("Введите урожайность: ");
    scanf("%d", &plant->yield);
}

void inputAnimal(Animal* animal) {
    while (getchar() != '\n');
    printf("Введите название животного: ");
    fgets(animal->name, 20, stdin);
    printf("Введите возраст животного: ");
    scanf("%d", &animal->age);
    printf("Введите количество кг продукта, которое произведит животное: ");
    scanf("%d", &animal->productivity);
}

void inputField(Field* field) {
    printf("Введите номер поля: ");
    scanf("%d", &field->id);
    printf("Поле засажено? (1 - да, 0 - нет): ");
    scanf("%d", &field->isPlanted);
    if (field->isPlanted) {
        inputPlant(&field->plant);
    }
    else {
        field->plant = createPlant("", 0, 0);
    }
}

void inputFarm(Farm* farm, int flieds, int animals) {
    for (int i = 0; i < flieds; i++) {
        printf("\nВведите данные для поля\n");
        inputField(&farm->fields[i]);
    }
    for (int j = 0; j < animals; j++) {
        printf("\nВведите данные для животного\n");
        inputAnimal(&farm->animals[j]);
    }
}

// Функции для вывода

void printPlant(Plant plant) {
    printf("Растение: %sВремя роста: %d дней, Количество урожая: %d\n", plant.name, plant.growthTime, plant.yield);
}

void printAnimal(Animal animal) {
    printf("\nЖивотное: %sВозраст: %d лет, Продукты(в кг): %d\n", animal.name, animal.age, animal.productivity);
}

void printField(Field field) {
    printf("\nПоле %d: ", field.id);
    if (field.isPlanted) {
        printPlant(field.plant);
    }
    else {
        printf("Поле не засажено\n");
    }
}

void printStorage(Storage storage) {
    printf("\nСклад: Урожай растений: %d, Продукты животных: %d кг\n", storage.plantYield, storage.animalProducts);
}

void printFarm(Farm farm, int flieds, int animals) {
    printf("\nИнформация о ферме\n");
    printf("Поля:\n");
    for (int i = 0; i < flieds; i++) {
        printField(farm.fields[i]);
    }
    printf("\nЖивотные\n");
    for (int i = 0; i < animals; i++) {
        printAnimal(farm.animals[i]);
    }
    printStorage(farm.storage);
}

// Основная логика 
void logic(Farm* farm, int flieds, int animals) {
    // Пример бизнес логики: сбор урожая и продукции животных
    for (int i = 0; i < flieds; i++) {
        if (farm->fields[i].isPlanted) {
            farm->storage.plantYield += farm->fields[i].plant.yield;
            farm->fields[i].isPlanted = 0; // Поле становится свободным после сбора урожая
        }
    }
    for (int j = 0; j < animals; j++) {
        farm->storage.animalProducts += farm->animals[j].productivity;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    system("color F0");
    int fields, animals;
    Farm myFarm = createFarm();
    
    //Ввод количества полей и животных
    printf("Ферма\n");
    printf("Введите количество полей:\n");
    scanf("%d", &fields);
    printf("Введите количество животных:\n");
    scanf("%d", &animals);

    // Ввод данных о ферме
    inputFarm(&myFarm, fields, animals);

    // Вывод информации о ферме
    printFarm(myFarm, fields, animals);

    // Выполняем основную логику игры
    logic(&myFarm, fields, animals);

    // Выводим обновленную информацию о ферме
    printFarm(myFarm, fields, animals);

    return 0;
}