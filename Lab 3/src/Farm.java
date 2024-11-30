class Farm implements FarmActions {
    private Field[] fields;
    private Storage<AbstractPlant>[] storage;
    private int money;

    public Farm(int fields1) {
        fields = new Field[fields1];
        storage = new Storage[fields1];
        for (int i = 0; i < fields1; i++) {
            fields[i] = new Field(i);
            storage[i] = new Storage<>();
        }
    }

    public void input() {
        for (Field field : fields) {
            System.out.println("\nВведите данные для поля:");
            field.inputField();
        }
    }

    public void print() {
        System.out.println("\nИнформация о ферме:");
        for (int i = 0; i < fields.length; i++) {
            fields[i].printField();
            storage[i].printStorage(i);
        }
    }

    public void logic() {
        for (int i = 0; i < fields.length; i++) {
            storage[i].addPlant(fields[i].harvestField());
        }
        System.out.println("\nПередача урожая на склады завершена.");
    }

    public void sell() {
        try {
            System.out.print("\nС какого склада продать урожай? ");
            int sellNumber = Help.readIntInRange(1, fields.length);
            int moneyEarned = storage[sellNumber - 1].sellStorage();
            money += moneyEarned;
            System.out.println("\nДеньги за продажу склада " + sellNumber + ": " + moneyEarned + " руб.");
            System.out.println("Общий доход: " + money + " руб.");
        } catch (RuntimeException e) {
            System.out.println("Ошибка: " + e.getMessage());
        }
    }
}
