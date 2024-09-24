import java.util.*;

class Counter1 extends Thread {
    private int from, to, step;
    private int[] tablou;

    public Counter1(int from, int to, int step, int[] tablou) {
        this.from = from;
        this.to = to;
        this.step = step;
        this.tablou = tablou;
    }

    public void run() {
        int s1 = 0, s2 = 0, s = 0;
        int i = from;

        while (i != to) {
            if (i % 2 != 0) { 
                s1 = tablou[i];
                i += step;

                if (i % 2 != 0 && i != to) { 
                    s2 = tablou[i];
                    s = s1 * s2;

                    System.out.println(getName() + " " + s1 + " * " + s2 + " = " + s);
                }
            }

            i += step;
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Counter1 cnt1, cnt2;

        int[] tablou = new int[100];
        Random rand = new Random();

        for (int i = 0; i < 100; i++) {
            tablou[i] = rand.nextInt(100) + 1;
            System.out.print(tablou[i] + " ");
        }
        System.out.println(" ");

        cnt1 = new Counter1(1, 99, 1, tablou);
        cnt1.setName("Th1");

        cnt2 = new Counter1(99, 1, -1, tablou);
        cnt2.setName("Th2");

        cnt1.start();
        cnt2.start();

        try {
            cnt1.join();
            cnt2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        String studentInfo = " - CR-211 | FR | FCIM | Gutu Mihai - ";
        for (char c : studentInfo.toCharArray()) {
            System.out.print(c);
            try {
                Thread.sleep(100); 
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        System.out.println();
    }
}
