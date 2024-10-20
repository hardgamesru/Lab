import java.util.Scanner;

public class Plant {
    private String name;
    private int growthTime; // Time in days
    private int yield;

    public Plant(String name, int growthTime, int yield) {
        this.name = name;
        this.growthTime = growthTime;
        this.yield = yield;
    }

    public Plant() {
        this.name = "None";
        this.growthTime = 0;
        this.yield = 0;
    }

    public void inputPlant() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите название растения: ");
        this.name = scanner.next();
        System.out.print("Введите время роста (в днях): ");
        this.growthTime = scanner.nextInt();
        System.out.print("Введите урожаемость: ");
        this.yield = scanner.nextInt();
    }

    public void printPlant() {
        System.out.println("Растение: " + name + ", Время роста: " + growthTime + " дней, Урожаемость: " + yield);
    }

    public int getYieldPlant() {
        return yield;
    }
}