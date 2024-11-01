//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Ферма");
        System.out.print("Введите количество полей: ");
        int fields1 = sc.nextInt();
        Farm myFarm = new Farm(fields1);

        myFarm.input();
        myFarm.print();
        myFarm.logic();
        myFarm.print();
        myFarm.sell();
        myFarm.print();
    }
}