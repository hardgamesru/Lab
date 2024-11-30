class Storage<T extends AbstractPlant> {
    private T plant;
    private int money;

    public Storage() {
        this.plant = null;
        this.money = 0;
    }

    public void printStorage(int i) {
        if (plant != null) {
            System.out.println("Склад " + (i + 1) + ": " + plant.toString());
        } else {
            System.out.println("Склад " + (i + 1) + ": пуст");
        }
    }

    public void addPlant(T plant) {
        this.plant = plant;
    }

    public int sellStorage() {
        if (plant == null || plant.name.equals("Нет растения")) {
            throw new RuntimeException("Склад пуст!");
        }
        money = plant.yield * plant.price;
        plant = null; // Сбрасываем после продажи
        return money;
    }
}
