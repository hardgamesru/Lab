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
        System.out.print("Введите название растения: ");
        name = Help.readString();
        System.out.print("Введите время роста (в днях): ");
        growthTime = Help.readInt();
        System.out.print("Введите урожайность: ");
        yield = Help.readInt();
        System.out.print("Введите цену: ");
        price = Help.readInt();
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