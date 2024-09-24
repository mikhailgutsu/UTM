package UTM.PCD.lab2;

public class Main {
    public static void main(String[] args) {
        ThreadGroup sys = Thread.currentThread().getThreadGroup();
        sys.list();
        
        sys.setMaxPriority(Thread.MAX_PRIORITY - 1);
        Thread curr = Thread.currentThread();
        curr.setPriority(curr.getPriority() + 1);
        sys.list();

        ThreadGroup g1 = new ThreadGroup("g1");
        g1.setMaxPriority(Thread.MAX_PRIORITY);
        Thread t = new Thread(g1, "A");
        t.setPriority(Thread.MAX_PRIORITY);
        g1.list();

        g1.setMaxPriority(Thread.MAX_PRIORITY - 2);
        g1.setMaxPriority(Thread.MAX_PRIORITY);
        g1.list();

        t = new Thread(g1, "B");
        t.setPriority(Thread.MAX_PRIORITY);
        g1.list();

        g1.setMaxPriority(Thread.MIN_PRIORITY + 2);
        t = new Thread(g1, "C");
        g1.list();
        
        t.setPriority(t.getPriority() - 1);
        g1.list();

        ThreadGroup g2 = new ThreadGroup(g1, "g2");
        g2.list(); // (8)
        g2.setMaxPriority(Thread.MAX_PRIORITY);
        g2.list(); // (9)

        for (int i = 0; i < 5; i++) {
            new Thread(g2, Integer.toString(i));
        }
        
        sys.list(); // (10)
        System.out.println("Starting all threads:");

        Thread[] all = new Thread[sys.activeCount()];
        sys.enumerate(all);
        for (int i = 0; i < all.length; i++) {
            if (!all[i].isAlive()) {
                all[i].start();
            }
        }
    }
} // End of ThreadGroup1
