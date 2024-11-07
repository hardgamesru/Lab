public class Main {
    public static void main(String[] args) {
        System.out.println("Ферма");
        while (true) {
            try {
                System.out.print("Введите количество полей: ");
                int fields1 = Help.readInt();
                if (fields1 <= 0) {
                    throw new Exception("Номер поля должен быть положительным!");
                }
                Farm myFarm = new Farm(fields1);
                myFarm.input();
                myFarm.print();
                myFarm.logic();
                myFarm.print();
                myFarm.sell();
                myFarm.print();
                myFarm.sell();
                myFarm.print();
                break;
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }
        /*
        final int rows = 2;  // Количество рядов на ферме
        final int cols = 2;  // Количество столбцов на ферме

        // Создание двумерного массива объектов Field (2x2)
        Field[][] farm1 = new Field[rows][cols];

        // Ввод данных для каждого поля
        System.out.println("Введите данные для полей фермы:");
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                System.out.println("\nВведите данные для поля [" + (i + 1) + "][" + (j + 1) + "]:");
                farm1[i][j].inputField();
            }
        }

        // Вывод данных о полях фермы
        System.out.println("\nИнформация о полях фермы:");
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                System.out.println("\nИнформация о поле [" + (i + 1) + "][" + (j + 1) + "]:");
                farm1[i][j].printField();
            }
        }
         */
    }
}