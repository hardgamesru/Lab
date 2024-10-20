//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Ферма");
        System.out.print("Введите количество полей: ");
        int numFields = scanner.nextInt();

        Farm myFarm = new Farm(numFields);
        myFarm.input(numFields);
        myFarm.print(numFields);
        myFarm.logic(numFields);
        myFarm.print(numFields);
    }
}