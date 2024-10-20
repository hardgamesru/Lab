public class Storage {
    private int plantYield;
    private int animalProducts;

    public Storage() {
        this.plantYield = 0;
        this.animalProducts = 0;
    }

    public void printStorage() {
        System.out.println("\nСклад: Урожай растений: " + plantYield);
    }

    public void addPlantYieldStorage(int yield) {
        plantYield += yield;
    }
}