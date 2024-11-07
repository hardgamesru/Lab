import java.io.IOException;

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
        while (true) {
            try {
                System.out.print("Введите название растения: ");
                name = Help.readString();
                if (name.isEmpty()){
                    throw new Exception("Название растения не может быть пустым!");
                }

                System.out.print("Введите время роста (в днях): ");
                growthTime = Help.readInt();
                if (growthTime <= 0){
                    throw new Exception("Время роста должно быть положительным числом!");
                }

                System.out.print("Введите урожайность: ");
                yield = Help.readInt();
                if (yield <= 0){
                    throw new Exception("Урожайность не может быть отрицательной!");
                }

                System.out.print("Введите цену: ");
                price = Help.readInt();
                if (yield <= 0){
                    throw new Exception("Цена не может быть отрицательной!");
                }
                break;
            }
            catch(Exception e){
                System.out.println(e.getMessage());
            }
        }
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