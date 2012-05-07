package javamatrix;

import com.sun.org.apache.bcel.internal.generic.SWAP;
import java.io.PrintStream;
import java.lang.Thread;

public class Matrix {

    public class MatrixThread implements Runnable{

        double[][] a, b, res;
        int count, col;

        public MatrixThread(double[][] _a, double[][] _b, double[][] _res, int col_number, int _count){
            a = _a.clone();
            b = _b.clone();
            res = _res;
            col = col_number;
            count = _count;
        }

        @Override
        public void run() {
            for(int i = col; i < col + count; ++i)
                for(int j = 0; j < b[i].length; ++j){
                    res[i][j] = 0;
                    for(int k = 0; k < a[i].length; ++k)
                        res[i][j] += a[i][k] * b[k][j];
                }
        }
    }

    private int n, m;
    public double a[][];

    public int getRowCount(){
        return n;
    }

    public int getColCount(){
        return m;
    }

    public void assignVal(double val){
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                a[i][j] = val;
    }

    public Matrix(int _n, int _m, double val){
        n = _n;
        m = _m;
        a = new double[n][m];
        assignVal(val);
    }

    public Matrix(int _n, int _m){
        this(_n, _m, 0);
    }

    public Matrix(int n){
        this(n, n, 0);
    }

    public Matrix(Matrix t){
        n = t.getColCount();
        m = t.getRowCount();
        a = new double[n][m];
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                a[i][j] = t.a[i][j];
    }

    public boolean isSquare(){
        return n == m;
    }

    public boolean isSymmetric(){
        Matrix t = new Matrix(this);
        return this == t.transpose();
    }

    public boolean isEqualSize(Matrix t){
        return n == t.getColCount() && m == t.getRowCount();
    }

    public boolean isEqual(Matrix t){
        if (!isEqualSize(t))
            return false;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(a[i][j] != t.a[i][j])
                    return false;
        return true;
    }

    public void print(PrintStream out){
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j)
                out.print(a[i][j] + " ");
            out.println();
        }
    }

    public void print(){
        print(System.out);
    }

    // Возвращаем себя же, чтобы можно было проводить цепные операции
    // a.add(5).multiply(3);
    public Matrix add(Matrix t){
        if(!isEqualSize(t))
            return this;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                a[i][j] += t.a[i][j];
        return this;
    }

    public Matrix multiply(double t){
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                a[i][j] *= t;
        return this;
    }

    public Matrix opposite(){
        return this.multiply(-1);
    }

    public Matrix minus(Matrix t){
        Matrix x = new Matrix(t);
        return this.add(x.opposite());
    }

    public Matrix transpose(){
        double t[][] = new double[n][m];
        t = a.clone();
        a = new double[m][n];
        int g = n;
        n = m;
        m = g;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                a[i][j] = t[j][i];
        return this;
    }

    public Matrix multiply(Matrix t, boolean optim) throws InterruptedException{
        if (m != t.getRowCount())
            return this;
        double res[][] = new double[n][t.getColCount()];
        if (optim){
            int count = Math.max(n / 4, 1);
            Thread th[] = new Thread[Math.min(4, n)];
            for(int i = 0; i < Math.min(4, n); ++i){
                th[i] = new Thread(new MatrixThread(a, t.a, res, i * count, count));
                th[i].start();
                th[i].join();
            }
        } else
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < t.getColCount(); ++j){
                    res[i][j] = 0;
                    for(int k = 0; k < m; ++k)
                        res[i][j] += a[i][k] * t.a[k][j];
                }
        m = t.getColCount();
        a = new double[n][m];
        a = res.clone();
        return this;
    }

    public Matrix power(int p) throws InterruptedException{
        if (p < -1 || p > 10)
            return this;
        if (p == 0){
            if ( n != m)
                return this;
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < m; ++j)
                    a[i][j] = i == j ? 1 : 0;
        }
        else
            for(int i = 0; i < p - 1; ++i)
                multiply(this, true);
        return this;
    }

    public double det(){
        return 0;
    }

}
