package javaqueue;

import java.util.Arrays;
import java.util.Comparator;
import java.util.Iterator;

public class PriorityQueue<T> {
    
    private static final int DEFAULT_CAPACITY = 11;
    private Object[] h;
    private int heap_size;
    private Comparator<T> comp;
	
    public class Iter implements Iterator<T> {
        private int idx;
        private PriorityQueue<T> pq;

        public Iter(int idx, PriorityQueue<T> pq){
            this.idx = idx;
            this.pq = pq;
        }

        @Override
        public boolean hasNext(){
            return idx <= heap_size;
        }

        @Override
        public void remove(){
            pq.delete(idx);
        }

        @Override
        public T next() {
            return (T)pq.h[idx++];
        }

    }
	
    public PriorityQueue(int initial_capacity, Comparator<T> comp) {
        this.comp = comp;
        h = new Object[initial_capacity];
    }

    public PriorityQueue(int initial_capacity){
        this(initial_capacity, null);
    }
	
    public PriorityQueue(){
        this(DEFAULT_CAPACITY, null);
    }

    public PriorityQueue(PriorityQueue<T> pq){
        this.comp = pq.comparator();
        h = new Object[pq.size()];
        System.arraycopy(pq.h, 0, pq, 0, heap_size);
    }
    
    private void swap(int i, int j, Object[] arr) {
        Object t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }

    private void siftUp(int i) {
        if (i / 2 == 0) {
            return;
        }
        if (comp != null) {
            if (comp.compare((T)h[i / 2], (T)h[i]) == 1) {
                swap(i / 2, i, h);
                siftUp(i / 2);
            }
        }
        else {
            Comparable<T> left = (Comparable<T>)h[i / 2];
            Comparable<T> right = (Comparable<T>)h[i];
            if(left.compareTo((T)right) == 1){
                swap(i / 2, i, h);
                siftUp(i / 2);
            }
        }
    }

    private void siftDown(int i) {
        int s;
        boolean res;
        if (comp != null)
            res = 2 * i <= heap_size && comp.compare((T)h[i], (T)h[2 * i]) == 1;
        else {
            if (2 * i <= heap_size){
                Comparable<T> left = (Comparable<T>)h[i];
                Comparable<T> right = (Comparable<T>)h[2 * i];
                res = left.compareTo((T)right) == 1;
            } else
                res = false;
        }
        if (res) {
            s = 2 * i;
        } else {
            s = i;
        }
        if (comp != null)
            res = 2 * i + 1 <= heap_size && comp.compare((T)h[s], (T)h[2 * i + 1]) == 1;
        else {
            if (2 * i + 1 <= heap_size){
                Comparable<T> left = (Comparable<T>)h[s];
                Comparable<T> right = (Comparable<T>)h[2 * i + 1];
                res = left.compareTo((T)right) == 1;
            }
            else
                res = false;
        }
        if (res) {
            s = 2 * i + 1;
        }
        if (s != i) {
            swap(s, i, h);
            siftDown(s);
        }
    }

    public void add(T x) {
        heap_size++;
        if (heap_size >= h.length) {
            try{
                Object[] tmp = new Object[h.length];
                System.arraycopy(h, 0, tmp, 0, h.length);
                h = new Object[2 * heap_size + 1];
                System.arraycopy(tmp, 0, h, 0, tmp.length);
            }
            catch(OutOfMemoryError e) {
                System.out.println(e.getMessage());
            }
        }
        h[heap_size] = x;
        siftUp(heap_size);
    }

    public T peek() {
        return (T)h[1];
    }

    public T poll() {
        T tmp = (T)h[1];
        delete(1);
        return tmp;
    }

    protected void delete(int i) {
        swap(i, heap_size, h);
        heap_size--;
        siftDown(i);
    }
	
    public void offer(T x){
        add(x);
    }
	
    public int size(){
        return heap_size;
    }
	
    public boolean contains(Object o){
        return indexOf(o) != -1;
    }
	
    public Comparator<T> comparator(){
        return comp;
    }
    
    public int indexOf(Object o){
        for(int i = 0; i < heap_size; ++i)
            if (o.equals(h[i]))
                return i;
        return -1;
    }
    
    public boolean remove(Object o){
        int idx = indexOf(o);
        if (idx == -1)
            return false;
        delete(idx);
        return false;
    }
	
    public void clear(){
        for(int i = 0; i < h.length; ++i)
            h[i] = 0;
        heap_size = 0;
    }
	
    public Object[] toArray(){
        return Arrays.copyOf(h, heap_size);
    }
    
    public Iterator<T> iterator(){
        return new Iter(1, this);
    }
}
