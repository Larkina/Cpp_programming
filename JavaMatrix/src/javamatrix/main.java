
package javamatrix;

public class main {

    public static void main(String[] args) throws InterruptedException {
            Matrix t = new Matrix(2, 3);
            Matrix b = new Matrix(3, 2);
            t.a[0][0] = 2;
            t.a[0][1] = 1;
            t.a[0][2] = -1;
            t.a[1][0] = 0;
            t.a[1][1] = 3;
            t.a[1][2] = 5;
            b.a[0][0] = 1;
            b.a[0][1] = 2;
            b.a[1][0] = 1;
            b.a[1][1] = -2;
            b.a[2][0] = 1;
            b.a[2][1] = 3;
            t.multiply(b, true).print();
            Matrix x = new Matrix(1000, 1000, 1);
            x.power(2);
    }
}
