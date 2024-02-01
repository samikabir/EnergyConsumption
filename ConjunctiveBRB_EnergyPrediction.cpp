#include <iostream>
#include <math.h> 
#include <fstream>
#include <string>   

using namespace std;   
  
float a1 = 0;
string a2;
string a3;
int a4 = 0;    
string a5; 
 
float Floor_H = 200.00; 
float Floor_M = 85.00;   
float Floor_L = 10.00;
 
float Sun_H = 1.00;  
float Sun_M = 0.50; 
float Sun_L = 0.00;      
 
float Occupancy_H = 1.00; 
float Occupancy_M = 0.55; 
float Occupancy_L = 0.10;       

float H_Floor = 0.0;
float M_Floor = 0.0; 
float L_Floor = 0.0;  

float H_Sun = 0.0;
float M_Sun = 0.0;
float L_Sun = 0.0;  

float H_Occupancy = 0.0;
float M_Occupancy = 0.0;
float L_Occupancy = 0.0;  
 
float sunshine = 0.00; 
float occupancy = 0.00;

float H2 = 0.0;   
float M2 = 0.0;
float L2 = 0.0; 

int numberOfAntAttributes = 2;
float matchingDegree[27];
float relativeWeight = 1.0; 
float totalWeight = 0;
float consequentBeliefDegree[81];  
float updatedConsequentBeliefDegree[81];
float beliefDegreeChangeLevel = 0; 
float activationWeight[27];
float maxWeight = 0.0;
int maxRule = 0;
int maxRuleH = 0.0;
int maxRuleM = 0.0;
int maxRuleL = 0.0;
string antecedentRefValue[81];  
string predictedMax;
string season;
string dayTime;
string dayType; 

float ruleWiseBeliefDegreeSum[27];  
string line;
string cnn_mild;
string cnn_nominal;
string cnn_severe;
int counter = 0;
string temp;
string dew_point; 
string cloud;
string humidity;

float normalized_cnn_severe_degree = 1.0; //transformed value after image prediction
float normalized_cnn_mild_degree = 1.0;
float normalized_cnn_nominal_degree = 1.0;

float image_normalized_cnn_severe_degree = 1.0; //directly from image
float image_normalized_cnn_mild_degree = 1.0;
float image_normalized_cnn_nominal_degree = 1.0; 

float cnn_pm25 = 1.0;
float pm25_revised = 1.0;
float PO = 1; 
float aggregatedBeliefDegreeH = 1;
float aggregatedBeliefDegreeM = 1;
float aggregatedBeliefDegreeL = 1;   
float finalAggregatedBeliefDegreeH = 1.0;
float finalAggregatedBeliefDegreeM = 1.0;
float finalAggregatedBeliefDegreeL = 1.0;
float brbH = 0;
float brbM = 0;
float brbL = 0;
//int aqi = 1;
float energy = 1.0;

float aqi = 1.0;
float aqi1 = 1.0;
float aqi2 = 1.0;
float aqi3 = 1.0;
float aqi4 = 1.0;
float aqi5 = 1.0;
float aqi6 = 1.0;     
 
void transformFloorArea(float a);        
void calculateSunshine(string month, string day, int hour);
void calculateOccupancy(string month, string day, int hour); 
void transformSunshine(float sunshine);
void transformOccupancy(float occupancy);       
   
void ruleBase()        
{        
    consequentBeliefDegree[0] = 0.60;   
    consequentBeliefDegree[1] = 0.40;
    consequentBeliefDegree[2] = 0;  
    consequentBeliefDegree[3] = 0.40; 
    consequentBeliefDegree[4] = 0.60;//0.20
    consequentBeliefDegree[5] = 0;//0.80 
    consequentBeliefDegree[6] = 0; 
    consequentBeliefDegree[7] = 0.80; 
    consequentBeliefDegree[8] = 0.20;//
    consequentBeliefDegree[9] = 0.80;
    consequentBeliefDegree[10] = 0.20;
    consequentBeliefDegree[11] = 0; //
    consequentBeliefDegree[12] = 0.60;
    consequentBeliefDegree[13] = 0.40;
    consequentBeliefDegree[14] = 0;// 
    consequentBeliefDegree[15] = 0.40;
    consequentBeliefDegree[16] = 0.60;
    consequentBeliefDegree[17] = 0;//
    consequentBeliefDegree[18] = 1;
    consequentBeliefDegree[19] = 0;
    consequentBeliefDegree[20] = 0;//
    consequentBeliefDegree[21] = 0.80;
    consequentBeliefDegree[22] = 0.20;
    consequentBeliefDegree[23] = 0;//
    consequentBeliefDegree[24] = 0.60;
    consequentBeliefDegree[25] = 0.40;
    consequentBeliefDegree[26] = 0;//
    consequentBeliefDegree[27] = 0.20;  
    consequentBeliefDegree[28] = 0.80;
    consequentBeliefDegree[29] = 0;//
    consequentBeliefDegree[30] = 0;
    consequentBeliefDegree[31] = 0.20;
    consequentBeliefDegree[32] = 0.80;// 
    consequentBeliefDegree[33] = 0;
    consequentBeliefDegree[34] = 0.60;
    consequentBeliefDegree[35] = 0.40;//
    consequentBeliefDegree[36] = 0.20;
    consequentBeliefDegree[37] = 0.80; 
    consequentBeliefDegree[38] = 0;// 
    consequentBeliefDegree[39] = 0;
    consequentBeliefDegree[40] = 1;
    consequentBeliefDegree[41] = 0;//
    consequentBeliefDegree[42] = 0;
    consequentBeliefDegree[43] = 0.80;
    consequentBeliefDegree[44] = 0.20;//
    consequentBeliefDegree[45] = 0.80; 
    consequentBeliefDegree[46] = 0.20;
    consequentBeliefDegree[47] = 0;//
    consequentBeliefDegree[48] = 0.60;
    consequentBeliefDegree[49] = 0.40;
    consequentBeliefDegree[50] = 0;//   
    consequentBeliefDegree[51] = 0.40;
    consequentBeliefDegree[52] = 0.60;
    consequentBeliefDegree[53] = 0;//
    consequentBeliefDegree[54] = 0;
    consequentBeliefDegree[55] = 0.20;
    consequentBeliefDegree[56] = 0.80;//  
    consequentBeliefDegree[57] = 0;
    consequentBeliefDegree[58] = 0.10;
    consequentBeliefDegree[59] = 0.90;//
    consequentBeliefDegree[60] = 0;
    consequentBeliefDegree[61] = 0;
    consequentBeliefDegree[62] = 1;//
    consequentBeliefDegree[63] = 0;
    consequentBeliefDegree[64] = 0.60;
    consequentBeliefDegree[65] = 0.40; //
    consequentBeliefDegree[66] = 0;
    consequentBeliefDegree[67] = 0.30;
    consequentBeliefDegree[68] = 0.70;//
    consequentBeliefDegree[69] = 0;
    consequentBeliefDegree[70] = 0.20;
    consequentBeliefDegree[71] = 0.80;//
    consequentBeliefDegree[72] = 0;
    consequentBeliefDegree[73] = 0.60;
    consequentBeliefDegree[74] = 0.40;//
    consequentBeliefDegree[75] = 0; 
    consequentBeliefDegree[76] = 0.40;
    consequentBeliefDegree[77] = 0.60;//
    consequentBeliefDegree[78] = 0;
    consequentBeliefDegree[79] = 0.20;   
    consequentBeliefDegree[80] = 0.80; //                  
}

void antecedentRefValueRecord(){
    antecedentRefValue[0] = "High";
    antecedentRefValue[1] = "High";
    antecedentRefValue[2] = "High";
    antecedentRefValue[3] = "High";
    antecedentRefValue[4] = "High";
    antecedentRefValue[5] = "Medium";
    antecedentRefValue[6] = "High";
    antecedentRefValue[7] = "High";
    antecedentRefValue[8] = "Low";
    antecedentRefValue[9] = "High";
    antecedentRefValue[10] = "Medium";
    antecedentRefValue[11] = "High";
    antecedentRefValue[12] = "High";
    antecedentRefValue[13] = "Medium";
    antecedentRefValue[14] = "Medium";
    antecedentRefValue[15] = "High";
    antecedentRefValue[16] = "Medium";
    antecedentRefValue[17] = "Low";
    antecedentRefValue[18] = "High";
    antecedentRefValue[19] = "Low";
    antecedentRefValue[20] = "High";
    antecedentRefValue[21] = "High";
    antecedentRefValue[22] = "Low";
    antecedentRefValue[23] = "Medium";
    antecedentRefValue[24] = "High";
    antecedentRefValue[25] = "Low";
    antecedentRefValue[26] = "Low";
    antecedentRefValue[27] = "Medium";
    antecedentRefValue[28] = "High";
    antecedentRefValue[29] = "High";
    antecedentRefValue[30] = "Medium";
    antecedentRefValue[31] = "High";
    antecedentRefValue[32] = "Medium";
    antecedentRefValue[33] = "Medium";
    antecedentRefValue[34] = "High";
    antecedentRefValue[35] = "Low";
    antecedentRefValue[36] = "Medium";
    antecedentRefValue[37] = "Medium";
    antecedentRefValue[38] = "High";
    antecedentRefValue[39] = "Medium";
    antecedentRefValue[40] = "Medium";
    antecedentRefValue[41] = "Medium";
    antecedentRefValue[42] = "Medium";
    antecedentRefValue[43] = "Medium";
    antecedentRefValue[44] = "Low";
    antecedentRefValue[45] = "Medium";
    antecedentRefValue[46] = "Low";
    antecedentRefValue[47] = "High";
    antecedentRefValue[48] = "Medium";
    antecedentRefValue[49] = "Low";
    antecedentRefValue[50] = "Medium";
    antecedentRefValue[51] = "Medium";
    antecedentRefValue[52] = "Low";
    antecedentRefValue[53] = "Low";
    antecedentRefValue[54] = "Low";
    antecedentRefValue[55] = "High";
    antecedentRefValue[56] = "High";
    antecedentRefValue[57] = "Low";
    antecedentRefValue[58] = "High";
    antecedentRefValue[59] = "Medium";
    antecedentRefValue[60] = "Low";
    antecedentRefValue[61] = "High";
    antecedentRefValue[62] = "Low";
    antecedentRefValue[63] = "Low";
    antecedentRefValue[64] = "Medium";
    antecedentRefValue[65] = "High";
    antecedentRefValue[66] = "Low";
    antecedentRefValue[67] = "Medium";
    antecedentRefValue[68] = "Medium";
    antecedentRefValue[69] = "Low";
    antecedentRefValue[70] = "Medium";
    antecedentRefValue[71] = "Low";
    antecedentRefValue[72] = "Low";
    antecedentRefValue[73] = "Low";
    antecedentRefValue[74] = "High";
    antecedentRefValue[75] = "Low";
    antecedentRefValue[76] = "Low";
    antecedentRefValue[77] = "Medium";
    antecedentRefValue[78] = "Low";
    antecedentRefValue[79] = "Low";
    antecedentRefValue[80] = "Low";
}
     
void takeInput()
{
    cout<<"Insert Floor Area (sqm): ";  
    cin>>a1;    
     
    cout<<"Insert Month (January-December): ";
    cin>>a2; 

    cout<<"Insert Day (Monday-Sunday): ";
    cin>>a3;  

    cout<<"Insert Hour (0-23h): ";
    cin>>a4;
    
    cout<<"Insert Heating Method (District or Electric): ";
    cin>>a5;    
      
    transformFloorArea(a1); 
    calculateSunshine(a2,a3,a4);
    calculateOccupancy(a2,a3,a4);        
}   
    
void transformFloorArea(float i)
{
    if (i >= Floor_H)
    {  
        H_Floor = 1; 
        M_Floor = 0;
        L_Floor = 0;  
    }
    else if (i == Floor_M)
    {
        H_Floor = 0;
        M_Floor = 1;
        L_Floor = 0; 
    } 
    else if (i <= Floor_L) 
    {
        H_Floor = 0;
        M_Floor = 0;  
        L_Floor = 1; 
    }    
    else if ((i <= Floor_H) && (i >= Floor_M)) 
    {
        M_Floor = (Floor_H-i)/(Floor_H-Floor_M);  
        H_Floor = 1 - M_Floor;  
        L_Floor = 0.0; 
    } 
    else if ((i <= Floor_M) && (i >= Floor_L))    
    {
        L_Floor = (Floor_M-i)/(Floor_M-Floor_L); 
        M_Floor = 1 - L_Floor; 
        H_Floor = 0.0; 
    }  
}  

void calculateSunshine(string month, string day, int hour)
{
    if(month == "January"){
        if((9 <= hour) && (hour <= 14)){
            sunshine = 1;
            //cout << ". January Hour is " << hour << endl;
        }
        else if(((14 < hour) && (hour <= 16)) || ((7 <= hour) && (hour < 9))){
            sunshine = 0.5;
        }
        else 
            sunshine = 0;
    }
    else if (month == "February"){
        if((8 <= hour) && (hour <= 16)){
            sunshine = 1;
        }
        else if(((16 < hour) && (hour <= 18)) || ((6 <= hour) && (hour < 8))){
            sunshine = 0.5; 
        }
        else 
            sunshine = 0;
    }
    else if (month == "March"){
        if((6 <= hour) && (hour <= 17)){
            sunshine = 1;
        }
        else if(((17 < hour) && (hour <= 19)) || ((4 <= hour) && (hour < 6))){
            sunshine = 0.5;  
        }
        else 
            sunshine = 0;
    }
    else if (month == "April"){
        if((4 <= hour) && (hour <= 19)){
            sunshine = 1;
        }
        else if(((19 < hour) && (hour <= 21)) || ((2 <= hour) && (hour < 4))){
            sunshine = 0.5;  
        }
        else 
            sunshine = 0;
    }
    else if (month == "May"){
        if((2 <= hour) && (hour <= 21)){
            sunshine = 1;
        }
        else if(((21 < hour) && (hour <= 23)) || ((0 <= hour) && (hour < 2))){
            sunshine = 0.5;  
        }
        else 
            sunshine = 0;
    }
    else if (month == "June"){ 
        if((1 <= hour) && (hour <= 22)){
            sunshine = 1;
        }
        else if((hour > 22) || (hour < 1)){
            sunshine = 0.5;  
        }
        else 
            sunshine = 0;
    }
    else if (month == "July"){ 
        if((2 <= hour) && (hour <= 22)){
            sunshine = 1; 
        }
        else if((hour > 22) || (hour < 2)){
            sunshine = 0.5;  
        }
        else 
            sunshine = 0;
    } 
    else if (month == "August"){ 
        if((4 <= hour) && (hour <= 20)){
            sunshine = 1;
        }
        else if(((20 < hour) && (hour <= 22)) || ((2 <= hour) && (hour < 4))){
            sunshine = 0.5;  
        }
        else 
            sunshine = 0;
    }
    else if (month == "September"){ 
        if((5 <= hour) && (hour <= 18)){
            sunshine = 1;
        }
        else if(((18 < hour) && (hour <= 20)) || ((3 <= hour) && (hour < 5))){
            sunshine = 0.5;  
        }
        else 
            sunshine = 0;
    }
    else if (month == "October"){ 
        if((7 <= hour) && (hour <= 16)){
            sunshine = 1;
        }
        else if(((16 < hour) && (hour <= 18)) || ((5 <= hour) && (hour < 7))){
            sunshine = 0.5;  
        }
        else 
            sunshine = 0; 
    }
    else if (month == "November"){ 
        if((8 <= hour) && (hour <= 14)){
            sunshine = 1;
        }
        else if(((14 < hour) && (hour <= 16)) || ((6 <= hour) && (hour < 8))){
            sunshine = 0.5;  
        }
        else 
            sunshine = 0; 
    }
    else if (month == "December"){ 
        if((10 <= hour) && (hour <= 13)){
            sunshine = 1;
        }
        else if(((13 < hour) && (hour <= 15)) || ((8 <= hour) && (hour < 10))){
            sunshine = 0.5;  
        }
        else 
            sunshine = 0; 
    } 

    cout<<"Sunshine is mtfk: " << sunshine << endl; 
    transformSunshine(sunshine);
} 

void transformSunshine(float shine)
{
    if (shine >= Sun_H)  
    {  
        H_Sun = 1; 
        M_Sun = 0;
        L_Sun = 0;  
    }
    else if (shine == Sun_M)
    {
        H_Sun = 0;
        M_Sun = 1;
        L_Sun = 0; 
    } 
    else if (shine <= Sun_L)  
    {
        H_Sun = 0;
        M_Sun = 0;  
        L_Sun = 1; 
    }       
    else if ((shine <= Sun_H) && (shine >= Sun_M)) 
    {
        M_Sun = (Sun_H - shine)/(Sun_H - Sun_M);
        H_Sun = 1 - M_Sun;  
        L_Sun = 0.0; 
    } 
    else if ((shine <= Sun_M) && (shine >= Sun_L))    
    {
        L_Sun = (Sun_M - shine)/(Sun_M-Sun_L);
        M_Sun = 1 - L_Sun; 
        H_Sun = 0.0; 
    }  

} 

void calculateOccupancy(string month, string day, int hour)
{
    if ((day == "Monday") || (day == "Tuesday") || (day == "Wednesday") || (day == "Thursday") || (day == "Friday")){
        if ((month == "September") || (month == "October") || (month == "November") || (month == "December") || (month == "January") || (month == "February") || (month == "March") || (month == "April") || (month == "May")){
            if((8 <= hour) && (hour <= 19)){
                occupancy = 0.5; 
            }
            else if((19 < hour) && (hour <= 22)){
                if (day == "Friday"){
                    occupancy = 0.5;
                }
                else{
                    occupancy = 0.8;
                }    
            }
            else {
                occupancy = 1.0;
            }
        }
    else if (month == "June" || month == "July" || month == "August"){ 
            if((8 <= hour) && (hour <= 19)){
                occupancy = 0.3; 
            }
            else if((19 < hour) && (hour <= 23)){ 
                if (day == "Friday"){
                    occupancy = 0.5;  
                }
                else{
                    occupancy = 0.7;
                }    
            }
            else {
                occupancy = 0.8;
            }
        }
    }

    else if ((day == "Saturday") || (day == "Sunday")){
        if ((month == "September") || (month == "October") || (month == "November") || (month == "December") || (month == "January") || (month == "February") || (month == "March") || (month == "April") || (month == "May")){
            if((9 <= hour) && (hour <= 19)){
                occupancy = 0.4; 
            }
            else if((19 < hour) && (hour <= 22)){
                if (day == "Sunday"){
                    occupancy = 0.8;
                }
                else{
                    occupancy = 0.5;
                }     
            } 
            else {
                occupancy = 0.8;
            }            
    }
    else if (month == "June" || month == "July" || month == "August"){
            if((9 <= hour) && (hour <= 19)){ 
                occupancy = 0.1;  
            }
            else if((19 < hour) && (hour <= 23)){
                if (day == "Sunday"){
                    occupancy = 0.5;
                }
                else{
                    occupancy = 0.3;
                }    
            }
            else {
                occupancy = 0.5; 
            }
        }
    } 
    cout<<"Occupancy is: " << occupancy << endl; 
    transformOccupancy(occupancy);          
}

void transformOccupancy(float residency){ 
    if (residency >= Occupancy_H)
    {  
        H_Occupancy = 1; 
        M_Occupancy = 0;
        L_Occupancy = 0;  
    }
    else if (residency == Occupancy_M)
    {
        H_Occupancy = 0;
        M_Occupancy = 1;
        L_Occupancy = 0; 
    } 
    else if (residency <= Occupancy_L)  
    {
        H_Occupancy = 0;
        M_Occupancy = 0;  
        L_Occupancy = 1; 
    }       
    else if ((residency <= Occupancy_H) && (residency >= Occupancy_M)) 
    {
        M_Occupancy = (Occupancy_H - residency)/(Occupancy_H-Occupancy_M);
        H_Occupancy = 1 - M_Occupancy;  
        L_Occupancy = 0.0; 
    }  
    else if ((residency <= Occupancy_M) && (residency >= Occupancy_L))    
    {
        L_Occupancy = (Occupancy_M - residency)/(Occupancy_M-Occupancy_L);
        M_Occupancy = 1 - L_Occupancy; 
        H_Occupancy = 0.0;  
    }   
}  
 
void showTransformedInput() 
{//H_Hm, H_Cl   
    cout<< endl << "Transformed Inputs are as follow." << endl;  
    cout<< "Floor Area = {(H, " << H_Floor << "); (M, " << M_Floor << "); (L, " << L_Floor << ")}" << endl; 
    cout<< "Sunshine = {(H, " << H_Sun << "); (M, " << M_Sun << "); (L, " << L_Sun << ")}" << endl;
    cout<< "Occupancy = {(H, " << H_Occupancy << "); (M, " << M_Occupancy << "); (L, " << L_Occupancy << ")}" << endl;    
} 
  
void calculateMatchingDegreeBrbCnn()    
{ 
    int increment = 0;
    float ti1[3] = {H_Floor, M_Floor, L_Floor};  
    float ti2[3] = {H_Sun, M_Sun, L_Sun};      
    float ti3[3] = {H_Occupancy, M_Occupancy, L_Occupancy};                 
    
    for (int c = 0; c < 3; c++)
        for (int d = 0; d < 3; d++)
            for (int e = 0; e < 3; e++){ 
                //weight[increment] = ti1[c] * ti2[d] * ti3[e];    
                matchingDegree[increment] = pow(ti1[c], relativeWeight) * pow(ti2[d], relativeWeight) * pow(ti3[e], relativeWeight);
                increment++;  
            } 
} 
  
void showMatchingDegree()  
{
    int track = 1; 
    //cout << endl << "Matching degrees of the rules are as follow." << endl; 
    /*for (int counter = 0; counter < 27; counter++)
    { 
        //cout<< "Matching Degree of Rule " << track << " = " << matchingDegree[counter] << endl;
        //track++; 
    }*/   
} 

void showActivationWeight()
{   
    int trace = 1; 
    for (int x = 0; x < 27; x++)
    {
        totalWeight += matchingDegree[x];
    } 
    
    //cout << endl << "Activation Weights of the rules are as follow."<< endl; 
     
    for (int counter = 0; counter < 27; counter++)
    {  
        activationWeight[counter] = matchingDegree[counter]/totalWeight; 
        if (activationWeight[counter] > maxWeight){
            maxWeight = activationWeight[counter];
            maxRule = trace;
        }
        cout<< "Activation weight of Rule " << trace << " = " << activationWeight[counter] << endl;
        trace++;  
    }
    /*cout << "Rule " << maxRule << " has the highest activation weight " << maxWeight << endl;
    maxRuleH = (3 * (maxRule-1));
    maxRuleM = maxRuleH + 1;
    maxRuleL = maxRuleM + 1;
    cout << "Max Rule High " << consequentBeliefDegree[maxRuleH] << ", Max Rule Medium " << consequentBeliefDegree[maxRuleM] << ", Max Rule Low " << consequentBeliefDegree[maxRuleL] << endl;
    
    if ((consequentBeliefDegree[maxRuleH] >= consequentBeliefDegree[maxRuleM]) && (consequentBeliefDegree[maxRuleH] >= consequentBeliefDegree[maxRuleL])){
        predictedMax = "High";
    }
    else if ((consequentBeliefDegree[maxRuleM] >= consequentBeliefDegree[maxRuleH]) && (consequentBeliefDegree[maxRuleM] >= consequentBeliefDegree[maxRuleL])){
        predictedMax = "Medium";
    }
    else if ((consequentBeliefDegree[maxRuleL] >= consequentBeliefDegree[maxRuleH]) && (consequentBeliefDegree[maxRuleL] >= consequentBeliefDegree[maxRuleM])){
        predictedMax = "Low";
    }  
    
    cout << "Due to " << antecedentRefValue[maxRuleH] << " floor area, " << antecedentRefValue[maxRuleM] << " sunshine, and " << antecedentRefValue[maxRuleL] << " occupancy, the energy consumption level has been predicted to be mostly " << predictedMax << "." << endl; */
    //consequentBeliefDegree[maxRuleM];
    //consequentBeliefDegree[maxRuleL];
}

void updateBeliefDegree()
{
    int update = 0;
    float sumAntAttr1 = 1;
    float sumAntAttr2 = 1;    
    
    if ((H1 + M1 + L1) < 1)
    {
        sumAntAttr1 = H1 + M1 + L1;
        update = 1;
    }
    
    if ((H2 + M2 + L2) < 1)
    {
        sumAntAttr2 = H2 + M2 + L2;
        update = 1;
    }
    
    if (update == 1)
    {
        beliefDegreeChangeLevel = (sumAntAttr1 + sumAntAttr2)/numberOfAntAttributes;
        //cout << "Belief Degree Change Level = " << beliefDegreeChangeLevel << endl;
        for (int go = 0; go < 27; go++)
        {
            consequentBeliefDegree[go] = beliefDegreeChangeLevel * consequentBeliefDegree[go];
            //cout << "Updated Consequent Belief Degree : " << consequentBeliefDegree[go] << endl;
        }
    }
    else
    {
        //cout << endl << "No upgradation of belief degree required." << endl;
    }
    
}

void takeCnnOutput()  
{ 
            
}  
   
void aggregateER_BrbCnn()
{  
    int parse = 0;
    int move1 = 0; 
    int move2 = 1; 
    int move3 = 2; 
    int action1 = 0;
    int action2 = 1;
    int action3 = 2;
    
    float part11 = 1;
    float part12 = 1;
    float part13 = 1;
    float part1 = 1;
    float part2 = 1;
    float value = 1;
    float meu = 1;
    
    float numeratorH1 = 1;
    float numeratorH2 = 1;
    float numeratorH = 1;
    float denominatorH1 = 1;
    float denominatorH = 1; 
    
    float numeratorM1 = 1;
    float numeratorM = 1;
    
    float numeratorL1 = 1;
    float numeratorL = 1; 
    
    float utilityScoreH = 1;
    float utilityScoreM = 0.5;
    float utilityScoreL = 0;
    float crispValue = 1;
    float degreeOfIncompleteness = 1;
    float utilityMax = 1;
    float utilityMin = 1;
    float utilityAvg = 1;       
    
    for (int t = 0; t < 27; t++)         
    {
        parse = t * 3;
        ruleWiseBeliefDegreeSum[t] = consequentBeliefDegree[parse] + consequentBeliefDegree[parse+1] + consequentBeliefDegree[parse+2];
    }   
    
    for (int rule = 0; rule < 27; rule++){
        part11 *= (activationWeight[rule] * consequentBeliefDegree[move1] + 1 - (activationWeight[rule] * ruleWiseBeliefDegreeSum[rule]));        
        move1 += 3;
    }
     
    for (int rule = 0; rule < 27; rule++){
        part12 *= (activationWeight[rule] * consequentBeliefDegree[move2] + 1 - (activationWeight[rule] * ruleWiseBeliefDegreeSum[rule]));        
        move2 += 3;
    }

    for (int rule = 0; rule < 27; rule++){
        part13 *= (activationWeight[rule] * consequentBeliefDegree[move3] + 1 - (activationWeight[rule] * ruleWiseBeliefDegreeSum[rule]));        
        move3 += 3;
    }  
    
    part1 = (part11 + part12 + part13);
    
    for (int rule = 0; rule < 27; rule++){
        part2 *= (1 - (activationWeight[rule] * ruleWiseBeliefDegreeSum[rule]));           
    }    
    
    value = part1 - part2;
    
    meu = 1/value;

    for (int rule = 0; rule < 27; rule++){
        numeratorH1 *= (activationWeight[rule] * consequentBeliefDegree[action1] + 1 - (activationWeight[rule] * ruleWiseBeliefDegreeSum[rule]));        
        action1 += 3;
    }
    
    for (int rule = 0; rule < 27; rule++){
        numeratorH2 *= (1 - (activationWeight[rule] * ruleWiseBeliefDegreeSum[rule]));        
    }    
    
    numeratorH = meu * (numeratorH1 - numeratorH2);
    
    for (int rule = 0; rule < 27; rule++){
        denominatorH1 *= (1 - activationWeight[rule]);        
    }
    
    denominatorH = 1 - (meu * denominatorH1);
    
    aggregatedBeliefDegreeH = (numeratorH/denominatorH);
    //cout << endl << "ER Aggregated Belief Degree for Severe Pollution: " << aggregatedBeliefDegreeH << endl;
    
    for (int rule = 0; rule < 27; rule++){
        numeratorM1 *= (activationWeight[rule] * consequentBeliefDegree[action2] + 1 - (activationWeight[rule] * ruleWiseBeliefDegreeSum[rule]));        
        action2 += 3;     
    }
    
    numeratorM = meu * (numeratorM1 - numeratorH2); 
    aggregatedBeliefDegreeM = (numeratorM/denominatorH); 
    //cout << "ER Aggregated Belief Degree for Mild Pollution: " << aggregatedBeliefDegreeM << endl;
    
    for (int rule = 0; rule < 27; rule++){
        numeratorL1 *= (activationWeight[rule] * consequentBeliefDegree[action3] + 1 - (activationWeight[rule] * ruleWiseBeliefDegreeSum[rule]));        
        action3 += 3;
    }
     
    numeratorL = meu * (numeratorL1 - numeratorH2);
    aggregatedBeliefDegreeL = (numeratorL/denominatorH); 
    //cout << "ER Aggregated Belief Degree for Nominal Pollution: " << aggregatedBeliefDegreeL << endl;    
    
    if ((aggregatedBeliefDegreeH + aggregatedBeliefDegreeM + aggregatedBeliefDegreeL) == 1){
        crispValue = (aggregatedBeliefDegreeH * utilityScoreH) + (aggregatedBeliefDegreeM * utilityScoreM) + (aggregatedBeliefDegreeL * utilityScoreL);
        //cout << "Crisp or numerical value is: " << crispValue << endl;        
        brbH = aggregatedBeliefDegreeH;
        brbM = aggregatedBeliefDegreeM;
        brbL = aggregatedBeliefDegreeL;    
        
        cout << endl << "BRB Belief Degree for High Energy Consumption: " << aggregatedBeliefDegreeH << endl;
        cout << "BRB Belief Degree for Medium Energy Consumption: " << aggregatedBeliefDegreeM << endl; 
        cout << "BRB Belief Degree for Low Energy Consumption: " << aggregatedBeliefDegreeL << endl;
        //cout << "brbH: " << brbH << " brbM: " << brbM << " brbL: " << brbL <<endl; 
    }   
 
        
    else{ 
        
        degreeOfIncompleteness = 1 - (aggregatedBeliefDegreeH + aggregatedBeliefDegreeM + aggregatedBeliefDegreeL);
        //cout << "Usassigned Degree of Belief: " << degreeOfIncompleteness << endl;  
        
        utilityMax = ((aggregatedBeliefDegreeH + degreeOfIncompleteness) * utilityScoreH + (aggregatedBeliefDegreeM*utilityScoreM) + (aggregatedBeliefDegreeL*utilityScoreL));
        
        utilityMin = (aggregatedBeliefDegreeH*utilityScoreH) + (aggregatedBeliefDegreeM*utilityScoreM) + (aggregatedBeliefDegreeL + degreeOfIncompleteness) * utilityScoreL;
        
        utilityAvg = (utilityMax + utilityMin)/2; 
        
        //cout << "Maximum expected utility: " << utilityMax << endl;
        //cout << "Minimum expected utility: " << utilityMin << endl; 
        //cout << "Average expected utility: " << utilityAvg << endl;  
        
        cout << endl << "BRB Belief Degrees considering degree of Incompleteness:" << endl;   
        
        finalAggregatedBeliefDegreeH = aggregatedBeliefDegreeH/(aggregatedBeliefDegreeH + aggregatedBeliefDegreeM + aggregatedBeliefDegreeL);   
         
        finalAggregatedBeliefDegreeM = aggregatedBeliefDegreeM/(aggregatedBeliefDegreeH + aggregatedBeliefDegreeM + aggregatedBeliefDegreeL);
        
        finalAggregatedBeliefDegreeL = aggregatedBeliefDegreeL/(aggregatedBeliefDegreeH + aggregatedBeliefDegreeM + aggregatedBeliefDegreeL);
                
        
        cout << endl << "BRB Belief Degree for High Energy Consumption: " << finalAggregatedBeliefDegreeH << endl; 
        cout << "BRB Belief Degree for Medium Energy Consumption: " << finalAggregatedBeliefDegreeM << endl; 
        cout << "BRB Belief Degree for Low Energy Consumption: " << finalAggregatedBeliefDegreeL << endl << endl;  
         
        brbH = finalAggregatedBeliefDegreeH;
        brbM = finalAggregatedBeliefDegreeM; 
        brbL = finalAggregatedBeliefDegreeL;           
        
        if(a5 == "District") {
            if((brbH >= brbM) && (brbH > brbL)){ 
                energy = (2.40*brbH) + ((0.80*brbM));
            } 
            else if((brbL > brbH) && (brbL >= brbM)){
                energy = (0.65*(1-brbL)) + ((0.15*brbM));
            }
            else if((brbM > brbH) && (brbM > brbL)){
                if(brbM == 1){
                    energy = 0.40*brbM;
                }
                else if(brbH > brbL){
                    energy = (0.40*brbM) + ((2.40*brbH)/5);                    
                }
                else if(brbL > brbH){
                    energy = (0.40*brbM) - ((0.20*brbL)/5);                    
                }
            }
        }
        else if(a5 == "Electric") { 
            if((brbH >= brbM) && (brbH > brbL)){  
                energy = (4*brbH) + ((1*brbM)/2);
            } 
            else if((brbL > brbH) && (brbL >= brbM)){
                energy = (2*(1-brbL)) + ((2*brbM)/3);
            }
            else if((brbM > brbH) && (brbM > brbL)){
                if(brbM == 1){
                    energy = 3*brbM;
                }
                else if(brbH > brbL){
                    energy = (3*brbM) + ((5*brbH)/5);                     
                }
                else if(brbL > brbH){
                    energy = (2*brbM) - ((1*brbL)/5);                    
                }
            }
        }        
    }
    cout << endl << "Predicted Energy Consumption: " << energy << " kWh" << endl;      
    //cout << "Heating Method is " << a5 << endl;
}

void explainOutput(){
    cout << "Rule " << maxRule << " has the highest activation weight " << maxWeight << endl;
    maxRuleH = (3 * (maxRule-1));
    maxRuleM = maxRuleH + 1;
    maxRuleL = maxRuleM + 1;
    cout << "Max Rule High " << consequentBeliefDegree[maxRuleH] << ", Max Rule Medium " << consequentBeliefDegree[maxRuleM] << ", Max Rule Low " << consequentBeliefDegree[maxRuleL] << endl;
    
    if ((consequentBeliefDegree[maxRuleH] >= consequentBeliefDegree[maxRuleM]) && (consequentBeliefDegree[maxRuleH] >= consequentBeliefDegree[maxRuleL])){
        predictedMax = "High";
    }
    else if ((consequentBeliefDegree[maxRuleM] >= consequentBeliefDegree[maxRuleH]) && (consequentBeliefDegree[maxRuleM] >= consequentBeliefDegree[maxRuleL])){
        predictedMax = "Medium";
    }
    else if ((consequentBeliefDegree[maxRuleL] >= consequentBeliefDegree[maxRuleH]) && (consequentBeliefDegree[maxRuleL] >= consequentBeliefDegree[maxRuleM])){
        predictedMax = "Low";
    }  
    
    if((a2 == "June") || (a2 == "July") || (a2 == "August")){
        season = "summer";
    }
    else if((a2 == "September") || (a2 == "October")){
        season = "fall";
    }
    else if((a2 == "November") || (a2 == "December") || (a2 == "January") || (a2 == "February") || (a2 == "March")){
        season = "winter";
    }
    else if((a2 == "April") || (a2 == "May")){
        season = "spring";
    }
    
    if((a3 == "Monday") || (a3 == "Tuesday") || (a3 == "Wednesday") || (a3 == "Thursday")){ 
        dayType = "weekday";
    }
    else if((a3 == "Saturday")){
        dayType = "weekend";
    }
    else if((a3 == "Friday") || (a3 == "Sunday")){
        dayType = a3;
    } 
    
    if((a4 >= 4) && (a4 < 12)){
        dayTime = "morning";
    }
    else if(a4 == 12){
        dayTime = "noon";
    } 
    else if((a4 >= 12) && (a4 < 18)){
        dayTime = "afternoon";
    } 
    else if((a4 >= 18) && (a4 <= 20)){
        dayTime = "evening";
    } 
    else if((a4 > 20) && (a4 <= 23)){
        dayTime = "night";
    } 
    else if((a4 >= 0) && (a4 < 4)){
        dayTime = "night";  
    }  
    
    cout << "In Skellefteå, daylight is " << antecedentRefValue[maxRuleM] << " in a "  << season << " " << dayTime << ", resulting in " << antecedentRefValue[maxRuleL] << " probability for people to stay indoor on a " << dayType << " " << dayTime << "." << endl;
    //cout << "This is  " << dayTime << " season in Skellefteå!" << endl; 
    //cout << "This is a " << season << " season in Skellefteå!" << endl; 
    cout << "Hence, due to " << antecedentRefValue[maxRuleH] << " floor area, " << antecedentRefValue[maxRuleM] << " daylight, " << antecedentRefValue[maxRuleL] << " indoor occupancy, and " << a5 << " heating method, the energy consumption level has been predicted to be mostly " << predictedMax << "." << endl; 
    //consequentBeliefDegree[maxRuleM];
    if(predictedMax == "High"){
        if(season == "summer") {
            cout << "However, energy consumption could have been lower if there were less people indoor." << endl; 
        }
        else if (season == "fall"){
            cout << "However, energy consumption could have been lower if it were summer, when people enjoy a lot of outdoor activities under daylight." << endl; 
        }
        else if (season == "winter"){
            cout << "However, energy consumption could have been lower if it were summer, when people enjoy a lot of outdoor activities under daylight." << endl;
        }
        else if (season == "spring") {
            cout << "However, energy consumption could have been lower if it were summer, when people enjoy a lot of outdoor activities under daylight." << endl;
        }
    }
    
    else if(predictedMax == "Low"){
        if(season == "summer") {
            cout << "However, energy consumption could have been higher if it were winter, when people mostly stay indoor due to cold weather and limited daylight." << endl; 
        }
        else if (season == "fall"){
            cout << "However, energy consumption could have been higher if it were winter, when people mostly stay indoor due to cold weather and limited daylight." << endl; 
        }
        else if (season == "winter"){
            cout << "However, energy consumption could have been higher if there were more people indoor." << endl;
        }
        else if (season == "spring") {
            cout << "However, energy consumption could have been higher if it were winter, when people mostly stay indoor due to cold weather and limited daylight." << endl;
        }
    }
    
    else if(predictedMax == "Medium"){
        if(season == "summer") {
            cout << "However, energy consumption could have been higher if it were winter, when people mostly stay indoor due to cold weather and limited daylight." << endl; 
        }
        else if (season == "fall"){
            cout << "However, energy consumption could have been higher if it were winter, when people mostly stay indoor due to cold weather and limited daylight." << endl; 
        }
        else if (season == "winter"){
            cout << "However, energy consumption could have been lower if it were summer, when people enjoy a lot of outdoor activities under daylight." << endl;
        }
        else if (season == "spring") { 
            cout << "However, energy consumption could have been higher if it were winter, when people mostly stay indoor due to cold weather and limited daylight." << endl;
        } 
    }
    
    if(a5 == "Electric") {
        cout << "Moreover, the apartment could have consumed lesser energy if it used district heating method." << endl;
    }
    else if (a5 == "District") {
        cout << "Moreover, the apartment could have consumed more energy if it used electric heating method." << endl;
    }
    
    
}
 
int main()
{
    ruleBase();
    antecedentRefValueRecord();
    takeInput();   
    //takeCnnOutput();   
    showTransformedInput(); 
    calculateMatchingDegreeBrbCnn();
    showMatchingDegree();
    showActivationWeight();
    updateBeliefDegree();
    aggregateER_BrbCnn(); 
    explainOutput();
      
    return 0; 
} 
