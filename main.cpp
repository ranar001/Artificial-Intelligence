//
//  main.cpp
//  testInput
//
//  Created by Ronny Anariva on 5/25/20.
//  Copyright © 2020 Ronny Anariva. All rights reserved.
//
//  Some instructions were commneted out because they were placed for testing purposed

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
using namespace std;
using namespace chrono;

//function definitions:
int countRows(vector<double> in);
void normalizeVec( vector<double> in);
double findAccuracy(vector<int> ftrs);

//global variables
vector<double> normData;

int main(int argc, const char * argv[]) {

    int choice=0;
    
    //will create a menu HERE:
        ifstream input;
        string inData;
        double convData;
        vector<double> data;
        vector<int> search;/*= {1,2,3,4,5,6,7,8,9,10};*/
        vector<int> highestAcc;
        cout<<"#############################################################################################################"<<endl;
        cout<<"#                              Hello and Welcome to Ronny's AI Project                                    ###"<<endl;
        cout<<"#    Given FOUR datasets we return the best features to be applied to it and return the best accuracy     ###"<<endl;
        cout<<"#                               Please choose one of the following...                                     ###"<<endl;
        cout<<"#   1. SMALL Test Dataset                                                                                 ###"<<endl;
        cout<<"#   2. LARGE Test Dataset                                                                                 ###"<<endl;
        cout<<"#   3. SMALL ASSIGNED Dataset                                                                             ###"<<endl;
        cout<<"#   4. LARGE ASSIGNED Dataset                                                                             ###"<<endl;
        cout<<"#   5. EXIT                                                                                               ###"<<endl;
        cout<<"#                                                                                                         ###"<<endl;
        cout<<"# NOTE: this is done using FORWARD selection  &  Leave one out validation                                 ###"<<endl;
        cout<<"#############################################################################################################"<<endl;
        cout << endl <<"ENTER CHOICE HERE: ";
        cin >> choice;
        cout <<endl;
        //NOTE: could potentially have the user enter their PWD so that the program can access their personal dataset
        // didn't implement this here but should be easy to implement... by asking the user for input string
        // with that input string we can just pass it to the function: input.open(string);
        switch (choice) {
            case 1:
                cout<< "Your choice was: SMALL TEST DATASET..." <<endl;
                input.open("/Users/ronnyanariva/Downloads/cs_170_small80.txt"); // found how to use this function cplusplus.com
                while(! input.eof()){
                    input >> inData;
                    // cout<< inData << endl;
                    convData = atof(inData.c_str());
                    //cout << setprecision(8)<< convData << endl << endl;
                    data.push_back(convData);
                }
                input.close();
                break;
            case 2:
                cout<< "Your choice was: LARGE TEST DATASET..." <<endl;
                input.open("/Users/ronnyanariva/Downloads/cs_170_large80.txt"); // found how to use this function cplusplus.com
                while(! input.eof()){
                    input >> inData;
                    // cout<< inData << endl;
                    convData = atof(inData.c_str());
                    //cout << setprecision(8)<< convData << endl << endl;
                    data.push_back(convData);
                }
                input.close();
                break;
            case 3:
                cout<< "Your choice was: SMALL ASSIGNED DATASET..." <<endl;
                input.open("/Users/ronnyanariva/Downloads/cs_170_small4.txt"); // found how to use this function cplusplus.com
                while(! input.eof()){
                    input >> inData;
                    // cout<< inData << endl;
                    convData = atof(inData.c_str());
                    //cout << setprecision(8)<< convData << endl << endl;
                    data.push_back(convData);
                }
                input.close();
                break;
            case 4:
                cout<< "Your choice was: LARGE ASSIGNED DATASET..." <<endl;
                input.open("/Users/ronnyanariva/Downloads/cs_170_large4.txt"); // found how to use this function cplusplus.com
                while(! input.eof()){
                    input >> inData;
                    // cout<< inData << endl;
                    convData = atof(inData.c_str());
                    //cout << setprecision(8)<< convData << endl << endl;
                    data.push_back(convData);
                }
                input.close();
                break;
            case 5:
                cout<<"THANK YOU!!..... GOODBYE :)" <<endl;
                exit(0);
                break;
            default:
                cout<<"Input NOT recognized..." <<endl << endl;;
                //continue;
        }
    
        steady_clock::time_point t1 = chrono::steady_clock::now(); //wanted to print out the elapsed time so found this on cplusplus.com
        //wasn't required but for it was just an extra feature I wanted to add...
        double vectorSz= data.size()-1;
        int numOfRows =countRows(data);

        //number of columns:
        int numOfCol= vectorSz/ numOfRows;
      //  cout<<endl <<numOfRows << " x " << numOfCol  << endl;
        
        normalizeVec(data);
        /*
        ofstream output; // doing this to compare data using text files... easier to see the difference
        output.open("/Users/ronnyanariva/Desktop/Spring 20/CS170_AI/WIP/testInput/normData.txt"); // easier to study results...
        for(int i=0; i<normData.size(); i++){
            if( (normData[i] == 1) || (normData[i] == 2) ){
                if(i==0){
                    output<< normData[i]<< "  ";
                }
                else
                output<< endl << normData[i]<< "  ";
            }
            else{
                output << "  "<< setprecision(7) << normData[i] << "   ";
            }
        }
        output.close();*/
        
        //this was used for testing, given the results provided on iLearn
        vector<int> test= {1,15,27};
        double acc=0;
        acc=findAccuracy(test);// this is here for testing purposes
        
        for(int i=1; i<numOfCol; i++){ //populating the vector with features from 1 to N where is number of columns - 1
            search.push_back(i);
        }
        //double store[search.size()][2];
        int it=0, greatest=0;
        int current=0;
        int next= 1;
        //cout<< "Highest Accuracy is Feature: " << greatest <<endl;
        //highestAcc.push_back(greatest);
        //now have to create a subset of the {5}
        //ie: {1,5} {2,5},....., {n,5}
        //highestAcc.pop_back();//removes the 5 stored before...
        
        it=1; greatest=0;
        double best[search.size()];
        int siz=search.size();
        //UP to this point all we had done is data manipulation...
        //now that we have the data in the format that we need it to be
        //then we can go ahead and do feature search...
        //##################################################################################################################
        //##################################################################################################################
        //Feature Search STARTS HERE:
        double store1[siz][2];
        for(int i=0; i<search.size(); i++){ // iterates for all possible features
            int repeated=0;
            while(it<=search.size() ){
                int allow=0;
                for(int i=0; i<highestAcc.size(); i++){
                    if(it==highestAcc[i]){
                        store1[it-1][0]=0; //setting it to zero solves issue of finding greates value later
                        store1[it-1][1]=it;
                        it++;
                        allow=1; //we want to move into the next iteration since, the current feature has already been explored
                        break;
                    }
                }
                if(allow ==1){
                    continue;
                }
                else{
                    highestAcc.push_back(search[it-1]);
                    double finRes= findAccuracy(highestAcc);
                    store1[it-1][0]=finRes; //stores the accuracy of features
                    store1[it-1][1]=it;  //stores the feature evaluated 1...n
      //            cout<< it << ": Feature " <<it << " has accuracy: "<< finRes << endl;
                    highestAcc.pop_back();
                    ++it;
                }
            }
            int current=0;
            int next= 1;

            while( (current<search.size())  && (next <search.size()) ){
                if(store1[current][0] >= store1[next][0]){
                    greatest=store1[current][1];
                    ++next;
                }
                else current=next;
            }
     //       cout<< "Highest Accuracy is Feature: " << greatest <<endl;
            highestAcc.push_back(greatest);//greedy search, find the highest one and push it
            double finalAcc;
            finalAcc=findAccuracy(highestAcc);
            best[i]=finalAcc;
            it=1;
            
            
        }
        int num=0;
        double max=0;
        current=0;next=1;
        while( (current<siz)  && (next <siz) ){
            if(best[current] >= best[next]){
                max=best[current];
                ++next;
                num=current;
            }
            else current=next;
            ++next;
        }
        vector<int> finalTest;
      //  cout <<endl << endl << max <<" at  " << num <<endl; //holds max value of the array containing the best accuracy and location @num
        cout<< "Using the following features will result in HIGHEST accuracy \n";
        for(int i=0; i<=num; i++){
            int var=highestAcc[i];
            finalTest.push_back(var);
            cout << var << "  ";
        }
        double finalAccuracy;
        finalAccuracy=findAccuracy(finalTest);
        cout << endl << "with an accuracy of: " <<finalAccuracy <<"%"<<endl<<endl;
        
        steady_clock::time_point t2 = steady_clock::now(); //got this from cplusplus.com just to print out the run time of the code...
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1); //used as a reference only
    if (time_span.count()>59){
        cout<<"Total runtime: " << (time_span.count() / 60) << " min"<<endl<<"WELL... That took a while!" << endl<< "THANK YOU.... ADIOS!"<<endl;
    }
    else    cout<<"Total runtime: " <<time_span.count() << " sec"<<endl<< "THANK YOU.... GOODBYE!"<<endl;
        
    return 0;
}










//################################################################################################################
//function implementations START HERE
int countRows(vector<double> in){
     int numOfRows =0;
     double vectorSz= in.size()-1;
     //returns number of rows
     for(int i=0; i<vectorSz ; i++){
         if( (in[i] == 1) || (in[i] == 2) ){
             ++numOfRows;
         }
     }
    return numOfRows;
}

void normalizeVec( vector<double> in){
    double sum=0, inner=0, result,stdDev;
    for(int i=0; i<in.size()-1; i++){
        if( (in[i] == 1) || (in[i] == 2) ){
            sum +=0;
        }
        else sum += in[i];
    }
    double average=0;
    int vecSz= in.size()-1;
    int rows= countRows(in);
    int column=(vecSz/rows) -1; // only counts features 1 to n.... does not consider the elements containing class classification
    int numOfEntries= rows * column;
    average= sum/ numOfEntries;
    
    for(int i=0; i<in.size()-1; i++){
        if( (in[i] == 1) || (in[i] == 2) ){
            inner +=0;
        }
        else inner += pow(in[i]-average, 2);
    }
    result = inner/numOfEntries;
    stdDev=pow(result,0.5);
    
    for(int i=0; i<in.size()-1; i++){ //populating the vector with normalized data
        if( (in[i] == 1) || (in[i] == 2) ){
            normData.push_back(in[i]);
        }
        else{
            double temp= (in[i]- average)/ stdDev;
            normData.push_back(temp);
        }
    }
}

double findAccuracy(vector<int> ftrs){
    int sizeDataVec= normData.size();
    int rowsOfData = countRows(normData);
    int columnsOfData= sizeDataVec/rowsOfData;
    double tempNormArr[rowsOfData][columnsOfData];
    int r=0, c=0;
    //converted normalized data vector into an array with the same normalized data
    for(int i=0; i<sizeDataVec; i++){
        if( ((i % columnsOfData) == 0) && (i !=0) ){
            ++r;
            c=0;
            tempNormArr[r][c]=normData[i];
            ++c;
        }
        else{
            tempNormArr[r][c]=normData[i];
            ++c;
        }
    } // up to here we have an arra with normalized data
    int szFtrVec= ftrs.size();
    int arr[szFtrVec]; //10 possible features 1:10
    for(int cnt=0; cnt<ftrs.size(); cnt++){
        arr[cnt]=ftrs[cnt];
    }
    
     int  loc=0, temp;
        double min=0,sum=0, distance[rowsOfData], root=0,hits=0;
        for(int r=0; r<rowsOfData; r++){ // test data
            for(int r1=0; r1<rowsOfData; r1++){ //trainin data
                sum=0; //reset sum value
                if(r!=r1){
                    for(int it = 0; it<szFtrVec; it++ ){ //selecting the features
                        if(arr[it]!=0){
                            temp=arr[it];
                            sum+= pow( (tempNormArr[r][temp] - tempNormArr[r1][temp]),2); // [ f(r)- f(r1) ]^2
                        }
                    }
                }
                root= pow(sum, 0.5);
                distance[r1]= root;
            }
        //finding min distance
        min=distance[0];
        for(int j=0;j<rowsOfData; j++){
            if(min== 0 && j<1){
                min= distance[j+1];
            }
            else if( (distance[j]!=0) && (min > distance[j]) ){
                min=distance[j];
                loc=j;
            }
        }
            //cout<< r+1 << ". CLASS: " << normArr[r][0]<< " ----->  CLASS: " << normArr[loc][0] << endl;
            if(tempNormArr[loc][0]==tempNormArr[r][0]){
                hits+=1; //increments the number of hits if the classes are the same
            }
            
        }//end outter for loop
        hits= (hits/rowsOfData) * 100;
        //cout <<"Accuracy of : " <<hits << "%" << endl;
    return hits;// must change to return accuracy at the end....
}

double defRateAcc(vector<double> empty){ //used for empty set, ie no features
    int count1=0, count2=0;
    double defRate=0;
    double vecSz=0;
    vecSz= empty.size();
    double numRows=0;
    double numCol=0;
    numRows=countRows(empty);
    numCol=vecSz/numRows;
    
    for(int i=0; i<numRows; i++){
        if(empty[i]==1) count1++;
        else if(empty[i]==2) count2++;
    }
    if(count1>count2) defRate= count1/ (numCol*numRows);
    else if(count1<count2) defRate= count2/ (numRows*numCol);
    
    return defRate;
}
