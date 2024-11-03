import java.util.Scanner;

class Farm {
    private Field[] fields;
    private Storage[] storage;
    private int money;

    public Farm(int fields1) {
        fields = new Field[fields1];
        storage = new Storage[fields1];
        for (int i = 0; i < fields1; i++) {
            fields[i] = new Field(i, new Plant(), false);
            storage[i] = new Storage();
        }
    }

    public void input() {
        for (Field field : fields) {
            System.out.println("\nВведите данные для поля\n");
            field.inputField();
        }
    }

    public void print() {
        System.out.println("\nИнформация о ферме\n");
        System.out.println("Поля:");
        for (int i = 0; i < fields.length; i++) {
            fields[i].printField();
            storage[i].printStorage(i);
        }
    }

    public void logic() {
        for (int i = 0; i < fields.length; i++) {
            storage[i].addPlant(fields[i].getPlant());
            fields[i].harvestField();
        }
        System.out.println("\nПередача на склады\n");
    }

    public void sell() {
        Scanner sc = new Scanner(System.in);
        System.out.print("\nУрожай какого склада вы бы хотели продать?: ");
        int sellnumber = sc.nextInt();
        System.out.println("\nПродажа урожая со склада " + sellnumber);
        money = storage[sellnumber - 1].sellStorage();
        System.out.println("\n\nКоличество денег с продажи склада - " + money + "\n");
        System.out.println("\nОбщее количество денег с продаж " + Storage.getAllmoney() + ", количество продаж - " + Storage.getSellcount() + "\n");
    }
}