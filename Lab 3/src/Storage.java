class Storage {
    private Plant plant;
    private String plantName;
    private int plantYield;
    private int plantPrice;
    private int money;
    private static int sellcount;
    private static int allmoney;

    public Storage(Plant plant, String plantName, int plantYield, int plantPrice, int money) {
        this.plant = plant;
        this.plantName = plantName;
        this.plantYield = plantYield;
        this.plantPrice = plantPrice;
        this.money = money;
    }

    public Storage() {
        this(new Plant(), "Нет растения", 0, 0, 0);
    } // демонстрация разумного использования оператора this

    static{
        sellcount = 0;
        allmoney = 0;
    }

    public void printStorage(int i) {
        System.out.println("\nСклад " + (i + 1) + ": Название растения : " + plant.getPlantName() + ", Урожаемость растения : " + plant.getPlantYield() + ", Цена за единицу : " + plant.getPlantPrice() + " руб.");
    }

    public void addPlant(Plant plant) {
        this.plant = plant;
    }

    public int sellStorage() {
        money = plant.getPlantYield() * plant.getPlantPrice();
        allmoney += money;
        sellcount++;
        plant = new Plant();
        return money;
    }

    public static int getSellcount() {
        return sellcount;
    }

    public static int getAllmoney() {
        return allmoney;
    }

}
