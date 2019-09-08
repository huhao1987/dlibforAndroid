package au.hao.and.dlibmodule;

import java.util.ArrayList;

public class Algorithms {
   public native double binomialrandomvarsaredifferent(String k1,String n1, String k2, String n2);
   public native double correlation(ArrayList<Integer> a,ArrayList<Integer> b);

    public double getDifference_binomial_random_vars(int k1,int n1,int k2, int n2){
        return binomialrandomvarsaredifferent(String.valueOf(k1),String.valueOf(n1),String.valueOf(k2),String.valueOf(n2));

    }
    private void initlib(){
        System.loadLibrary("algorithms");
    }

    public static Algorithms algorithms=null;

    public static Algorithms init(){
        if(algorithms==null){
            algorithms=new Algorithms();
            algorithms.initlib();
        }
        return algorithms;
    }
}
