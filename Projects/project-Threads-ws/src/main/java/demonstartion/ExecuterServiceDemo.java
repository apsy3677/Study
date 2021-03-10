package demonstartion;

import jdk.nashorn.internal.codegen.CompilerConstants;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Random;
import java.util.concurrent.*;

public class ExecuterServiceDemo {

    public static void main(String[] args) {

        ExecutorService service = Executors.newFixedThreadPool(5);

        Runnable Task = new Runnable() {
            public void run() {
                System.out.println("Thread " + Thread.currentThread().getName() );
                for(int i=0; i< 10;i++){
                    System.out.println("Thread "+ i );
                }
            }
        };

        List<Future> allFutures =  new ArrayList<Future>();
        for(int i=0;i< 100;i++){
//            service.execute(Task);
            Future<Integer> future = service.submit(new Task());
            allFutures.add(future);
            // perform unrelated operations


        }
//        List
        for(int i=0;i<100;i++){
            Future<Integer> future = allFutures.get(i);
            // blocking operation
            try {
                Integer result = future.get();
            } catch (InterruptedException e) {
                e.printStackTrace();
            } catch (ExecutionException e) {
                e.printStackTrace();
            }
        }
    }

    static class Task implements Callable<Integer>{
        public Integer call() throws Exception {
            System.out.println("Thread name "+ Thread.currentThread().getName());
            Thread.sleep(3000);
            return new Random().nextInt();
        }
    }
}
