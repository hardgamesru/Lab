import java.util.Scanner;

public class Farm {
    private Field[] fields = new Field[5];
    private Storage storage;

    public Farm(int numFields) {
        for (int i = 0; i < numFields; i++) {
            fields[i] = new Field(i, new Plant(), false);
        }
        storage = new Storage();
    }

    public void input(int numFields) {
        Scanner scanner = new Scanner(System.in);
        for (int i = 0; i < numFields; i++) {
            System.out.println("\nВведите данные для поля");
            fields[i].inputField();
        }
    }

    public void print(int numFields) {
        System.out.println("\nИнформация о ферме");
        System.out.println("Поля:");
        for (int i = 0; i < numFields; i++) {
            fields[i].printField();
        }
        storage.printStorage();
    }

    public void logic(int numFields) {
        for (int i = 0; i < numFields; i++) {
            storage.addPlantYieldStorage(fields[i].harvestField());
        }
        System.out.println("\nПередача на склад");
    }
}