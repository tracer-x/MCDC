
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

//import com.sun.org.apache.xpath.internal.Expression;
//import com.sun.xml.internal.bind.v2.schemagen.xmlschema.List;
public class Sequence {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("Sanghu is good boy!");
		int count=0;
		String q;
		String my_new_str = "";
		try {

			File f = new File("finalpredicate.txt");

			BufferedReader b = new BufferedReader(new FileReader(f));

			String readLine = "";

			System.out.println("Reading file using Buffered Reader");

			while ((readLine = b.readLine()) != null) {
				System.out.println(readLine);


				//String k="((A)||!((B)&&(C)))";
				String k=readLine;
				String m=k;
				System.out.println(""+k);
				k=k.replace("|", "k");
				k=k.replace("(", "").replace(")", "").replaceAll("&", "").replaceAll("!", "").replaceAll("k", "");
				int no_of_var=k.length();
				int p=(int) Math.pow(2, no_of_var);
				boolean tt[][]=new boolean[p][no_of_var+1];
				//System.out.println(""+k+p);
				//System.out.println(""+no_of_var);
				for (int b_val_str=0;b_val_str<p;b_val_str++){
					String maxAmpStr = Integer.toBinaryString(b_val_str);

					String catstring="";
					if(maxAmpStr.length()<no_of_var){
						int hm=no_of_var-maxAmpStr.length();
						for(int h2=0;h2<hm;h2++){
							catstring=catstring+"0";
						}
						maxAmpStr=catstring+maxAmpStr;
					}
					//System.out.println("**"+maxAmpStr);
					char[] arr = maxAmpStr.toCharArray();
					for (int i=0; i<maxAmpStr.length()&&i<no_of_var; i++){
						if (arr[i] == '1'){             
							tt[b_val_str][i] = true;  
						}
						else if (arr[i] == '0'){
							tt[b_val_str][i] = false; 
						}
					}
				}
				int no_of_con[]=new int[p];

				String dup_dont[][]=new String[p][no_of_var+1];
				for(int h1=0;h1<p;h1++){
					boolean exp_val=false;
					int upto=0;
					int keep[]=new int[no_of_var];
					for(int h3=0;h3<no_of_var;h3++){
						keep[h3]=h3;
					}
					char[] arr2 = m.toCharArray();
					String expr="";
					for (int i=0,j=0; i<m.length(); i++){
						if(arr2[i]>='A'&&arr2[i]<='Z'){
							expr=expr+"tt[h1][keep["+j+"]++]";
							j++;
						}
						else{
							expr=expr+arr2[i];
						}
					}
					expr=expr+";";
					System.out.println("**"+expr);
					String h= "(tt[h1][upto++]||!(tt[h1][upto++]&&tt[h1][upto++]))||(tt[h1][upto++]&&tt[h1][upto++])";

					//yahan values ko input string ke according dalna hai...or keep ki value ko inclrease karna hai

					//String array_variable=readLine;
		
						        
					Boolean truth = Boolean.valueOf(expr);
					exp_val=truth;
				
				System.out.println(exp_val);
					
				  //java.beans.Expression e = new java.beans.Expression(expr, expr, dup_dont);
					 //exp_val=((tt[h1][keep[0]++])&&(tt[h1][keep[1]++])&&(tt[h1][keep[2]++]));
				      //exp_val=((tt[h1][keep[0]++])&&(tt[h1][keep[1]++]));
					//exp_val=(boolean)((Object) e).evaluate();
                        
					
					//yahan se 2^n combinations ate hain
					tt[h1][no_of_var]=exp_val;
					for(int h3=0;h3<no_of_var;h3++){
						if(keep[h3]==h3)
						{dup_dont[h1][h3]="X";}
						else{
							if(tt[h1][h3]==true){
								dup_dont[h1][h3]="T";
							}
							else{
								dup_dont[h1][h3]="F";
							}}
					} 
					if(tt[h1][no_of_var]==true)
						dup_dont[h1][no_of_var]= "T";
					else
						dup_dont[h1][no_of_var]= "F";
					//System.out.println(""+exp_val+upto);
				}

				for(int h1=0;h1<p;h1++){
					for(int h2=0;h2<=no_of_var;h2++){
						System.out.print(dup_dont[h1][h2]+"    ");
					}
					System.out.println("");
				}
				int bitset[]=new int[p];
				for(int hr=0;hr<p;hr++)bitset[hr]=0;
				for(int h1=0;h1<p;h1++){
					for(int h2=h1+1;h2<p;h2++){
						int k_mat=0;
						if(bitset[h2]==0){
							for(int h3=0;h3<=no_of_var;h3++){
								if(dup_dont[h1][h3].equals(dup_dont[h2][h3])) k_mat++;
							}
							if(k_mat==no_of_var+1)
							{ 
								//System.out.println("kmat  "+h1+"  "+k_mat+"  "+h2);
								bitset[h2]=1;}

						}
					}
				}
			}
				//-----------------Counting MCC Rows---------------
				//yahan se mcc-sc nikalta hai
				/*int mcc_rows=0;
				for(int ik=0;ik<p;ik++){
					if(bitset[ik]==0){
						mcc_rows++;
					}
				}
				//------------------------------------------------
				String MCC_Data[][]=new String[mcc_rows][no_of_var+1];
				System.out.println("\nRefined Shortcircuit MCC Truth Table");
				for(int ik=0,ikp1=0;ik<p;ik++){
					if(bitset[ik]==0){
						for(int h2=0;h2<=no_of_var;h2++){
							MCC_Data[ikp1][h2]=dup_dont[ik][h2];
							System.out.print(dup_dont[ik][h2]+"    ");
						}
						ikp1++;  System.out.println("");
					}

				}
				String ETT_Data[][]=new String[mcc_rows][no_of_var];
				for(int e1=0;e1<mcc_rows;e1++){
					for(int e2=0;e2<no_of_var;e2++){
						ETT_Data[e1][e2]="";
					}
				}
				for(int e1=0;e1<mcc_rows;e1++){
					for(int e2=0;e2<no_of_var;e2++){
						for(int e3=0;e3<mcc_rows;e3++){
							if((!MCC_Data[e1][e2].equals(MCC_Data[e3][e2]))&&(!MCC_Data[e1][no_of_var].equals(MCC_Data[e3][no_of_var]))){
								int e5=0;
								for(int e4=0;e4<no_of_var;e4++){
									if(e4!=e2){
										if(MCC_Data[e1][e4].equals(MCC_Data[e3][e4])||MCC_Data[e1][e4].equals("X")||MCC_Data[e3][e4].equals("X")){e5++;}
									}
								}
								if(e5==no_of_var-1){
									if(ETT_Data[e1][e2].length()<1) ETT_Data[e1][e2]=""+e3;
									else ETT_Data[e1][e2]=ETT_Data[e1][e2]+","+e3;

								}
							}
						}
					}
				}/*
				
				
				//yahan se mc/dc ett banta hai
				/*System.out.println(""+"MC/DC Extended Truth Table generation");
				System.out.print("TC   ");
				for( char pk=65,e2=0;e2<no_of_var;e2++,pk++){
					System.out.print(pk+"   ");
				}
				System.out.print("  R"+"    ");
				for( char pk=65,e2=0;e2<no_of_var;e2++,pk++){
					System.out.print(pk+"            ");
				}
				System.out.println("");
				for(int e1=0;e1<mcc_rows;e1++){
					System.out.print(""+e1+"    ");
					for(int e2=0;e2<no_of_var;e2++){
						System.out.print(MCC_Data[e1][e2]+"   ");
					}

					System.out.print("  "+MCC_Data[e1][no_of_var]+"    ");

					for(int e2=0;e2<no_of_var;e2++){
						System.out.print(ETT_Data[e1][e2]+"            ");
					}
					System.out.println("");
				}*/
			//}

		}
		
		catch (IOException e) {
			e.printStackTrace();
		}

	}
}


