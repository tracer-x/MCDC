/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;

/**
 *
 * @author user
 */
public class SequenceFileGenerator {
    public static void main(String[] args) throws FileNotFoundException, IOException {
        BufferedReader PC=new BufferedReader(new FileReader("exp/Condition_And_Predicates.txt"));
        String r=PC.readLine();
        int number_of_clause=0;
        while(r!=null){
            if(r.contains("&&")||r.contains("||")){
            r=r.replace("&&", "(~)");
            r=r.replace("||", "(~)");
            String p[]=r.split("(~)");
            number_of_clause+=p.length;
            }
            else
                number_of_clause+=1;
            r=PC.readLine();
        }
        
            System.out.println(""+number_of_clause);
            BufferedReader PC1=new BufferedReader(new FileReader("exp/Condition_And_Predicates.txt"));
            String r1=PC1.readLine();
            int no_of_seq=0;
            int no_of_over=0;
            int no_of_pred=0;
            int clause=1;
            while(r1!=null){
            if(!r1.contains("&&")&&!r1.contains("||")){
            no_of_seq++;
            
            PrintWriter out_cp=new PrintWriter("exp/Sequence-atom-"+clause+"-"+no_of_seq+".txt");
            out_cp.println("1"); //Length for atom
            for(int n1=1;n1<=no_of_over;n1++){
            out_cp.println("9");
            }
            //change here for not operator
            PrintWriter out_cp_onlyvalue=new PrintWriter("exp/seq/Sequence-atom-"+clause+"-"+no_of_seq+".txt");
            out_cp_onlyvalue.println("1");
			out_cp.println("1");
            for(int i=1;i<=(number_of_clause-(no_of_over+1));i++)
                out_cp.println("9");
            out_cp.flush();
			out_cp_onlyvalue.flush();
            
            
            
            no_of_seq++;
            PrintWriter out_cp1=new PrintWriter("exp/Sequence-atom-"+clause+"-"+no_of_seq+".txt");
            out_cp1.println("1"); //Length for atom
            for(int n1=1;n1<=no_of_over;n1++){
            out_cp1.println("9");
            }
            
          //change here for not operator
            PrintWriter out_cp_onlyvalue1=new PrintWriter("exp/seq/Sequence-atom-"+clause+"-"+no_of_seq+".txt");
            out_cp_onlyvalue1.println("2");
            out_cp1.println("0");
            for(int i=1;i<=(number_of_clause-(no_of_over+1));i++)
                out_cp1.println("9");
            out_cp1.flush();
			out_cp_onlyvalue1.flush();
            no_of_over++;
            clause++;
            }
            else{
            no_of_pred++;
             BufferedReader PC2=new BufferedReader(new FileReader("exp/predicateResults"+no_of_pred+".txt"));
             String r2=PC2.readLine();
             int counter_to_increase=0; 
             while(r2!=null){
                 no_of_seq++;
                 PrintWriter out_cp=new PrintWriter("exp/Sequence-pred-"+no_of_pred+"-"+no_of_seq+".txt");
				 PrintWriter out_cp_onlyvalue=new PrintWriter("exp/seq/Sequence-pred-"+no_of_pred+"-"+no_of_seq+".txt");
             String p[]=r2.split(",");
                 System.out.println(""+p.length);
                 out_cp.println(p.length); //Length for predicate
                 for(int n1=1;n1<=no_of_over;n1++){
                 out_cp.println("9");}
                 for(String k:p){
                 if(k.contains("T"))
                 {  
			     out_cp.println("1");
			     out_cp_onlyvalue.print("1");
                 }				 
                 if(k.contains("F"))
                 {
       			 out_cp.println("0"); 
                 out_cp_onlyvalue.print("2");
				 }
				 if(k.contains("X"))
                 {
       			 out_cp.println("9"); 
                 out_cp_onlyvalue.print("0");
				 }
				 }
                 counter_to_increase=p.length; 
                 for(int n1=1;n1<=(number_of_clause-(no_of_over+p.length));n1++){
                 out_cp.println("9");
                 }
                 
               out_cp.flush();
			   out_cp_onlyvalue.flush();
                 r2=PC2.readLine();
             }
             no_of_over=no_of_over + counter_to_increase;
             
            }
            r1=PC1.readLine();
            }
            
    }
}
