package trie;

public class MainTest {


    public static void main(String[] args) throws InterruptedException {
        Trie<Integer> t = new Trie<>();
        t.insert("set", 1);
        t.insert("setter", 2);
        t.insert("set", 10);
        //System.out.println(t.get("set") + " " + t.get("setter") + " " + t.get("abba"));

    }
}
