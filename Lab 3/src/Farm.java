import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

class Farm implements FarmActions {
    private List<Field> fields;
    private List<Storage<AbstractPlant>> storage;
    private int money;

    public Farm(int fieldCount) {
        fields = new ArrayList<>();
        storage = new ArrayList<>();
        for (int i = 0; i < fieldCount; i++) {
            fields.add(new Field(i));
            storage.add(new Storage<>());
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
        for (int i = 0; i < fields.size(); i++) {
            fields.get(i).printField();
            storage.get(i).printStorage(i);
        }
    }

    public void logic() {
        for (int i = 0; i < fields.size(); i++) {
            storage.get(i).addPlant(fields.get(i).harvestField());
        }
        System.out.println("\nПередача урожая на склады завершена.");
    }

    public void sell() {
        try {
            System.out.print("\nС какого склада продать урожай? ");
            int sellNumber = Help.readIntInRange(1, fields.size());
            int moneyEarned = storage.get(sellNumber - 1).sellStorage();
            money += moneyEarned;
            System.out.println("\nДеньги за продажу склада " + sellNumber + ": " + moneyEarned + " руб.");
            System.out.println("Общий доход: " + money + " руб.");
        } catch (RuntimeException e) {
            System.out.println("Ошибка: " + e.getMessage());
        }
    }

    public void sortFieldsByYield() {
        fields.sort((field1, field2) -> Integer.compare(field2.getPlantYield(), field1.getPlantYield()));
        System.out.println("\nПоля отсортированы по урожайности.");
    }

    public AbstractPlant findBestPlant() {
        return fields.stream()
                .filter(Field::isPlanted)
                .map(Field::getPlant)
                .max(Comparator.comparingInt(plant -> plant.yield * plant.price))
                .orElse(null);
    }
}
