import java.util.Scanner;

class Field {
    private int id;
    private Plant plant;
    private boolean isPlanted; // true если поле засажено, false если нет

    public Field(int id, Plant plant, boolean isPlanted) {
        this.id = id;
        this.plant = plant;
        this.isPlanted = isPlanted;
    }

    public Field() {
        this(0, new Plant(), false);
    }

    public void inputField() {
        Scanner sc = new Scanner(System.in);
        System.out.print("Введите номер поля: ");
        id = sc.nextInt();
        System.out.print("Поле засажено? (1 - да, 0 - нет): ");
        isPlanted = sc.nextInt() == 1;
        if (isPlanted) {
            plant.inputPlant();
        } else {
            plant = new Plant();
        }
    }

    public void printField() {
        System.out.print("\nПоле " + id + ": ");
        if (isPlanted) {
            plant.printPlant();
        } else {
            System.out.println("Поле не засажено");
        }
    }

    public int harvestField() {
        if (isPlanted) {
            isPlanted = false;
        }
        return 0;
    }

    public Plant getPlant() {
        return plant;
    }
}
