public class Main {
    public static void main(String[] args) {
        System.out.println("Ферма");
        System.out.print("Введите количество полей: ");
        int fields1 = Help.readInt();
        Farm myFarm = new Farm(fields1);

        myFarm.input();
        myFarm.print();
        myFarm.logic();
        myFarm.print();
        myFarm.sell();
        myFarm.print();
        myFarm.sell();
        myFarm.print();
    }
}