import java.util.Scanner;

class Field {
    private int id;
    private Plant plant;
    private boolean isPlanted;

    public Field(int id, Plant plant, boolean isPlanted) {
        this.id = id;
        this.plant = plant;
        this.isPlanted = isPlanted;
    }

    public Field() {
        this.id = 0;
        this.plant = new Plant();
        this.isPlanted = false;
    }

    public void inputField() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите номер поля: ");
        this.id = scanner.nextInt();
        System.out.print("Поле засажено? (1 - yes, 0 - no): ");
        this.isPlanted = scanner.nextInt() == 1;
        if (isPlanted) {
            plant.inputPlant();
        } else {
            plant = new Plant();
        }
    }

    public void printField() {
        System.out.print("Поле " + id + ": ");
        if (isPlanted) {
            plant.printPlant();
        } else {
            System.out.println("Поле не засажено");
        }
    }

    public int harvestField() {
        if (isPlanted) {
            isPlanted = false;
            return plant.getYieldPlant();
        }
        return 0;
    }
}
