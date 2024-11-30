class Plant extends AbstractPlant implements Cloneable {

    public Plant(String name, int growthTime, int yield, int price) {
        super(name, growthTime, yield, price);
    }

    public Plant() {
        super();
    }

    @Override
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

    @Override
    protected Object clone() throws CloneNotSupportedException {
        return super.clone(); // мелкое клонирование
    }

    public Plant deepClone() {
        return new Plant(name, growthTime, yield, price); // глубокое клонирование
    }
}
