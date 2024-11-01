import java.util.Scanner;

class Plant {
    private String name;
    private int growthTime; // Время роста в днях
    private int yield; // Урожайность
    private int price; // Цена

    public Plant(String name, int growthTime, int yield, int price) {
        this.name = name;
        this.growthTime = growthTime;
        this.yield = yield;
        this.price = price;
    }

    public Plant() {
        this("Нет растения", 0, 0, 0);
    }

    public void inputPlant() {
        Scanner sc = new Scanner(System.in);
        System.out.print("Введите название растения: ");
        name = sc.nextLine();
        System.out.print("Введите время роста (в днях): ");
        growthTime = sc.nextInt();
        System.out.print("Введите урожайность: ");
        yield = sc.nextInt();
        System.out.print("Введите цену: ");
        price = sc.nextInt();
    }

    public void printPlant() {
        System.out.println("Растение: " + name + ", Время роста: " + growthTime + " дней, Урожайность: " + yield + ", Цена: " + price + " руб");
    }

    public String getPlantName() {
        return name;
    }

    public int getPlantYield() {
        return yield;
    }

    public int getPlantPrice() {
        return price;
    }
}