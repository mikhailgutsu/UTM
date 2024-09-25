package UTM.PCD.lab2;

public class Main {
    public static void main(String[] args) {

        ThreadGroup mainGroup = new ThreadGroup("Main");

        ThreadGroup g1 = new ThreadGroup(mainGroup, "G1");

        ThreadGroup g3 = new ThreadGroup(g1, "G3");
        
        Thread thf = new Thread(g3, "Thf");
        thf.setPriority(3);
        Thread thb = new Thread(g3, "Thb");
        thb.setPriority(7);
        Thread thc = new Thread(g3, "Thc");
        thc.setPriority(3);
        Thread thd = new Thread(g3, "Thd");
        thd.setPriority(3);
        
        Thread thA = new Thread(g1, "ThA");
        thA.setPriority(3);

        ThreadGroup g2 = new ThreadGroup(mainGroup, "G2");
        Thread th8 = new Thread(g2, "Th8");
        th8.setPriority(3);
        Thread th9 = new Thread(g2, "Th9");
        th9.setPriority(4);
        Thread th3 = new Thread(g2, "Th3");
        th3.setPriority(3);

        Thread th1 = new Thread(mainGroup, "Th1");
        th1.setPriority(3);
        Thread th2 = new Thread(mainGroup, "Th2");
        th2.setPriority(3);

        displayThreadInfo(mainGroup);

        startAllThreads(mainGroup);
    }

    private static void displayThreadInfo(ThreadGroup group) {

        Thread[] threads = new Thread[group.activeCount()];
        group.enumerate(threads);
        
        for (Thread thread : threads) {
            if (thread != null) {
                System.out.println("Thread Name: " + thread.getName() + 
                                   ", Group Name: " + thread.getThreadGroup().getName() + 
                                   ", Priority: " + thread.getPriority() + " (" + thread.getPriority() + ")");
            }
        }

        ThreadGroup[] subGroups = new ThreadGroup[group.activeGroupCount()];
        group.enumerate(subGroups, true);
        
        for (ThreadGroup subGroup : subGroups) {
            if (subGroup != null) {
                System.out.println("Subgroup Name: " + subGroup.getName());
                displayThreadInfo(subGroup);
            }
        }
    }

    private static void startAllThreads(ThreadGroup group) {

        Thread[] threads = new Thread[group.activeCount()];
        group.enumerate(threads);
        
        for (Thread thread : threads) {
            if (thread != null && !thread.isAlive()) {
                thread.start();
            }
        }
    }
}
