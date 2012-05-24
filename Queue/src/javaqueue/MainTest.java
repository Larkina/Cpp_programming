package javaqueue;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Random;

public class MainTest {

    public static class IntReverseComparator implements Comparator<Integer> {

        @Override
        public int compare(Integer x, Integer y) {
            return x.compareTo(y);
        }
    }

    public static void main(String[] args) throws InterruptedException {
    
    }
}
