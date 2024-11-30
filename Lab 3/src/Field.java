class Field {
    private int id;
    private AbstractPlant plant;
    private boolean isPlanted;

    public Field(int id) {
        this.id = id;
        this.plant = new Plant();
        this.isPlanted = false;
    }

    public void inputField() {
        System.out.print("Введите номер поля: ");
        id = Help.readInt();

        System.out.print("Поле засажено? (1 - да, 0 - нет): ");
        isPlanted = Help.readIntInRange(0, 1) == 1;

        if (isPlanted) {
            System.out.print("Выберите тип растения (1 - Обычное, 2 - Фрукт): ");
            int choice = Help.readIntInRange(1, 2);

            if (choice == 1) {
                plant = new Plant();
            } else {
                plant = new Fruits();
            }
            plant.inputPlant();
        } else {
            plant = new Plant();
        }
    }

    public void printField() {
        System.out.print("\nПоле " + id + ": ");
        if (isPlanted) {
            System.out.println(plant.toString());
        } else {
            System.out.println("Поле не засажено.");
        }
    }

    public AbstractPlant harvestField() {
        if (isPlanted) {
            isPlanted = false;
            return plant;
        }
        return new Plant();
    }
}
