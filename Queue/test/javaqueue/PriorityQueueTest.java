package javaqueue;

import java.util.Comparator;
import java.util.Iterator;
import java.util.Random;
import org.junit.*;
import static org.junit.Assert.*;

public class PriorityQueueTest {
    
    public PriorityQueue<Integer> int_heap = new PriorityQueue(1);
    public PriorityQueue<Double> double_heap = new PriorityQueue(1);
    public PriorityQueue<String> string_heap = new PriorityQueue(1);
    
    public PriorityQueueTest() {
    }

    @BeforeClass
    public static void setUpClass() throws Exception {
    }

    @AfterClass
    public static void tearDownClass() throws Exception {
    }
    
    @Before
    public void setUp() {        
    }
    
    @After
    public void tearDown() {
    }

    @Test
    public void testAdd() {
        System.out.println("add");
        Integer in = 10;
        Double doub = 3.14;
        String str = "Heap";
        int_heap.add(in);
        double_heap.add(doub);
        string_heap.add(str);
        assertEquals(str, string_heap.poll());
        assertEquals(in, int_heap.poll());
        assertEquals(doub, double_heap.peek());
        for(int i = 0; i < 100; ++i)
            int_heap.add(100 - i - 1);
        for(int i = 0; i < 100; ++i)
            assertEquals(i, (int)int_heap.poll());
    }

    /**
     * Test of peek method, of class PriorityQueue.
     */
    @Test
    public void testPeek() {
        System.out.println("peek");
        for(int i = 100; i > 0; --i){
            int_heap.add(i);
            assertEquals(i, (int)int_heap.peek());
        }
    }

    /**
     * Test of poll method, of class PriorityQueue.
     */
    @Test
    public void testPoll() {
        for(Integer i = 100; i < 500; ++i){
            string_heap.add(i.toString());
            assertEquals(i.toString(), string_heap.poll());
        }
    }

    /**
     * Test of delete method, of class PriorityQueue.
     */
    @Test
    public void testDelete() {
        System.out.println("delete");
        double_heap.add(1.1);
        double_heap.add(1.2);
        double_heap.add(1.3);
        double_heap.delete(1);
        assertEquals(1.2, double_heap.peek(), 0.0);
        double_heap.delete(2);
        double_heap.delete(1);
        double_heap.add(5.0);
        assertEquals(5, double_heap.peek(), 0.0);
    }

    /**
     * Test of offer method, of class PriorityQueue.
     */
    public static class IntReverseComparator implements Comparator<Integer> {

        @Override
        public int compare(Integer x, Integer y) {
            return -x.compareTo(y);
        }
    }
    
    @Test
    public void testOffer() {
        System.out.println("offer");
        PriorityQueue<Integer> h = new PriorityQueue<>(1, new IntReverseComparator());
        for(int i = 0; i < 100; ++i)
            h.offer(i);
        for(int i = 0; i < 100; ++i)
            assertEquals(100 - i - 1, (int)h.poll());
    }

    /**
     * Test of size method, of class PriorityQueue.
     */
    @Test
    public void testSize() {
        System.out.println("size");
        int_heap.clear();
        for(int i = 0; i < 100; ++i)
            int_heap.add(i);
        int i = 0;
        while (int_heap.size() > 0){
            assertEquals(i++, (int)int_heap.poll());
        }
    }

    /**
     * Test of contains method, of class PriorityQueue.
     */
    @Test
    public void testContains() {
        System.out.println("contains");
        double_heap.add(66.6);
        for(int i = 0; i < 10; ++i)
            double_heap.add(i / 3.3);
        assertTrue(double_heap.contains(66.6));
    }

    /**
     * Test of remove method, of class PriorityQueue.
     */
    @Test
    public void testRemove() {
        System.out.println("remove");
        string_heap.add("abc");
        string_heap.add("bcd");
        string_heap.remove("abc");
        assertEquals("bcd", string_heap.poll());
    }

    /**
     * Test of clear method, of class PriorityQueue.
     */
    @Test
    public void testClear() {
        System.out.println("clear");
        for(int i = 0; i < 1000; ++i)
            double_heap.add(new Random().nextGaussian());
        assertEquals(1000, double_heap.size());
        double_heap.clear();
        assertEquals(0, double_heap.size());
    }

    /**
     * Test of iterator method, of class PriorityQueue.
     */
    @Test
    public void testIterator() {
        System.out.println("iterator");
        for(Integer i = 0; i < 100; ++i)
            string_heap.add(i.toString());
        Iterator<String> it = string_heap.iterator();
        Integer i = 0;
        while(it.hasNext()){
            assertEquals(i.toString(), it.next());
            ++i;
        }
        Iterator<Integer> it_int = int_heap.iterator();
        for(int j = 0; j < 100; ++j)
            int_heap.add(new Random().nextInt(200));
        while(int_heap.size() > 0 ){
            it_int.remove();
        }
    }
}
