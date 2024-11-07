import java.util.Scanner;

class Help {
    private static Scanner scanner = new Scanner(System.in);

    // Метод для безопасного считывания целого числа
    public static int readInt() {
        int value = 0;
        boolean valid = false;
        while (!valid) {
            try {
                value = Integer.parseInt(scanner.nextLine());
                valid = true;
            } catch (NumberFormatException e) {
                System.out.println("Ошибка: Введите целое число.");
            }
        }
        return value;
    }

    public static int readIntInRange(int min, int max) {
        int value;
        while (true) {
            value = readInt(); // Используем метод для ввода числа
            if (value >= min && value <= max) {
                return value;
            } else {
                System.out.println("Ошибка! Введите число в пределах от " + min + " до " + max + ".");
            }
        }
    }

    // Метод для безопасного считывания строки
    public static String readString() {
        return scanner.nextLine();
    }
}