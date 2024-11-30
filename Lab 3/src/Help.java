import java.util.Scanner;

class Help {
    private static Scanner scanner = new Scanner(System.in);

    public static int readInt() {
        while (true) {
            try {
                return Integer.parseInt(scanner.nextLine());
            } catch (NumberFormatException e) {
                System.out.println("Ошибка: Введите целое число.");
            }
        }
    }

    public static int readIntInRange(int min, int max) {
        int value;
        while (true) {
            value = readInt();
            if (value >= min && value <= max) {
                return value;
            } else {
                System.out.println("Ошибка! Введите число в пределах от " + min + " до " + max + ".");
            }
        }
    }

    public static String readString() {
        return scanner.nextLine();
    }
}
