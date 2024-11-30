class Fruits extends Plant {
    protected String season;

    public Fruits(String name, int growthTime, int yield, int price, String season) {
        super(name, growthTime, yield, price);
        this.season = season;
    }

    public Fruits() {
        super();
        this.season = "Неизвестный сезон";
    }

    @Override
    public void inputPlant() {
        super.inputPlant();
        System.out.print("Введите сезон: ");
        season = Help.readString();
    }

    @Override
    public String toString() {
        return super.toString() + ", Сезон: " + season;
    }
}
