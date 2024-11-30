abstract class AbstractPlant {
    protected String name;
    protected int growthTime;
    protected int yield;
    protected int price;

    public AbstractPlant(String name, int growthTime, int yield, int price) {
        this.name = name;
        this.growthTime = growthTime;
        this.yield = yield;
        this.price = price;
    }

    public AbstractPlant() {
        this("Нет растения", 0, 0, 0);
    }

    public abstract void inputPlant();

    @Override
    public String toString() {
        return "Растение: " + name + ", Время роста: " + growthTime + " дней, Урожайность: " + yield + ", Цена: " + price + " руб.";
    }
}






