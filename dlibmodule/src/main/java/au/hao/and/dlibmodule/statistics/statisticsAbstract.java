package au.hao.and.dlibmodule.statistics;

import java.util.ArrayList;

public class statisticsAbstract {
   public native double binomialrandomvarsaredifferent(String k1,String n1, String k2, String n2);
   public native double correlation(ArrayList<Integer> a,ArrayList<Integer> b);
   public native double meansignagreement(ArrayList<Integer> a,ArrayList<Integer> b);
    public native double covariance(ArrayList<Integer> a,ArrayList<Integer> b);
    public native double r1squared(ArrayList<Integer> a,ArrayList<Integer> b);
    public native double meansquarederror(ArrayList<Integer> a,ArrayList<Integer> b);
    public native double eventcorrelation(String acount,String bcount, String abcount, String total_num_observations);

    public double getDifference_binomial_random_vars(int k1,int n1,int k2, int n2){
        return binomialrandomvarsaredifferent(String.valueOf(k1),String.valueOf(n1),String.valueOf(k2),String.valueOf(n2));
    }
    public double getevent_correlation(int count_a,int count_b,int count_ab, int count_total_num_observations){
        return eventcorrelation(String.valueOf(count_a),String.valueOf(count_b),String.valueOf(count_ab),String.valueOf(count_total_num_observations));
    }
    private void initlib(){
        System.loadLibrary("statisticsabstract");
    }

    public static statisticsAbstract statisticsabstract =null;

    public static statisticsAbstract init(){
        if(statisticsabstract ==null){
            statisticsabstract =new statisticsAbstract();
            statisticsabstract.initlib();
        }
        return statisticsabstract;
    }
}
