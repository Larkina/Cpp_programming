
package trie;

import com.sun.xml.internal.ws.message.saaj.SAAJHeader;
import java.util.Map;
import java.util.TreeMap;

public class Trie<T>{

    private String[] words = new String[2];
    private int count;

    protected class Range {
        public int idx, left, right;

        public Range(int idx, int left, int right) {
            this.idx = idx;
            this.left = left;
            this.right = right;
        }

    }

    protected class Node {
        private T val;
        private Object[] children = new Object[0];
        private int count;

        private void growChildren(){
            if(++count > children.length){
                Object[] tmp = new Object[children.length];
                System.arraycopy(words, 0, tmp, 0, children.length);
                children = new Object[2 * count];
                System.arraycopy(tmp, 0, children, 0, tmp.length);
            }
        }

        public Node(T val) {
            this.val = val;
        }

        public Node() {
            val = null;
        }

    }

    private void growWords(){
        if (++count >= words.length){
            String[] tmp = new String[words.length];
            System.arraycopy(words, 0, tmp, 0, words.length);
            words = new String[2 * count];
            System.arraycopy(tmp, 0, words, 0, tmp.length);
        }
    }

    private Node root = new Node();

    private Range findMostCommonSubSequence(String a, String b){
        int idx = -1;
        for(int i = 0; i < Math.min(a.length(), b.length()); ++i){
            if (a.charAt(i) != b.charAt(i))
                break;
            idx = i;
        }
        return new Range(0, 0, idx);
    }

    public void insert(String key, T val){
        growWords();
        Node node = root;
        if (node.children.length == 0){
            node.growChildren();
            node.children[node.count - 1] = new Range(0, 0, key.length());
            words[count - 1] = key;
            return;
        }
        for (int i = 0; i < node.count; ++i) {
            Range tmp = (Range)node.children[i];
            String str = words[tmp.idx].substring(tmp.left, tmp.right);
            Range r = findMostCommonSubSequence(str, key);
            if (r.right == -1){
            // To do: запилить новый чайлд у текущего
            }
            else {
            // To do: расплить строчку на два детенка.
            }
        }
        node.val = val;
    }

    public T get(String key){
        Node v = root;
        return v.val;
    }

}
