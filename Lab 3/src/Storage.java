class Storage {
    private Plant plant;
    private String plantName;
    private int plantYield;
    private int plantPrice;
    private int money;

    public Storage(Plant plant, String plantName, int plantYield, int plantPrice, int money) {
        this.plant = plant;
        this.plantName = plantName;
        this.plantYield = plantYield;
        this.plantPrice = plantPrice;
        this.money = money;
    }

    public Storage() {
        this(new Plant(), "Нет растения", 0, 0, 0);
    }

    public void printStorage(int i) {
        System.out.println("\nСклад " + i + ": Название растения : " + plant.getPlantName() + ", Урожаемость растения : " + plant.getPlantYield() + ", Цена за единицу : " + plant.getPlantPrice() + " руб.");
    }

    public void addPlant(Plant plant) {
        this.plant = plant;
    }

    public int sellStorage() {
        money = plant.getPlantYield() * plant.getPlantPrice();
        plant = new Plant();
        return money;
    }
}
