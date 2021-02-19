// Naimul Hoque Machine Problem 1 Naive Bayes Classifier

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <math.h>

using namespace std;
double getAccuracy(string,double,double, vector<double>, vector<double>,int);

int main(int argc, char *argv[]){

    clock_t t;
    t = clock();
    // Check if arugments are valid. 
    if(argc != 3){
        cout << "Either too little or too many arguments. Expected 2." << endl;
        exit(EXIT_FAILURE);
    }
        
    string str1 = argv[1];
    string str2 = argv[2];

    if(str1.compare("covid_test.csv") != 0 && str2.compare("covid_test.csv") != 0){
        cout << "Incorrect File: covid_test.csv" << endl;
        exit(EXIT_FAILURE);
    }
    if(str1.compare("covid_train.csv") != 0 && str2.compare("covid_train.csv") != 0){
        cout << "Incorrect File: covid_train.csv" << endl;
        exit(EXIT_FAILURE);
    }
    
    string cvd_train = str1;
    string cvd_valid = str2;


    // Open the training file
    string line;
    
    // Get all data seperated to vectors. We will decide which to use later on.
    int rows = 0;
    ifstream csv_file(cvd_train);
    if(csv_file.is_open()){
        while(csv_file.good()){
            getline(csv_file,line);
            rows++;
        }   
    }
    else{
        cout << "Unable to open file: covid_train.csv" << endl;
        exit(EXIT_FAILURE);
    }
    
    rows -= 100000;
    int featureLength = 22;

    // Construct 2D dynamic array to hold information regarding the dataset
    string **data = new string*[rows];
    for(int i = 0; i < rows; i++)
        data[i] = new string[featureLength];

    
    csv_file.clear();
    csv_file.seekg(0);
    
    if(csv_file.is_open()){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < featureLength; j++){
                if(j == featureLength - 1)
                    getline(csv_file,line,'\n');
                else
                    getline(csv_file,line,',');
                data[i][j] = line;
            }
        }
        csv_file.close();
    }
    else{
        cout << "Unable to open file: covid_train.csv" << endl;
        exit(EXIT_FAILURE);
    }

    
    // Seperate Features from Data
    string *features = new string[featureLength];
    for(int i = 0; i < featureLength; i++)
        features[i] = data[0][i];

    // Get P(Dead) and P(Survive)
    double P_survive, P_dead; 
    double surviveCount = 0;
    int date_died_ind;
    for(int i = 0; i < featureLength; i++){
        if(features[i] == "date_died"){
            date_died_ind = i;
            for(int j = 1; j < rows; j++){
                if(data[j][i].compare("9999-99-99") == 0){
                    surviveCount++;
                }
            }
            break;
        }
    }

    double not_survive_count = rows - surviveCount;
    P_survive = surviveCount/rows;
    P_dead = 1 - P_survive;

    // cout << "Probability of Surviving: " << P_survive << endl;
    // cout << "Probability of not Surviving " << P_dead << endl;
    // att =

    // vector<double> accuracies;
    // // for(int att = 8; att < featureLength; att++){
    // //     if(att == 9 || att == 8 || att == 11 || att == 10)
    // //         continue;
    // for (int age_desired = 30; age_desired < 90; age_desired++){
        int age_desired = 51;
        vector<double> survived_cond_prob;
        vector<double> not_survived_cond_prob;

        

        // Chose 1 = true and 2 = false, "sex" "copd" "asthma" "inmsupr" "hypertension"
        for(int i = 0; i < featureLength; i++){
            bool ignore = features[i].compare("entry_date") == 0 || features[i].compare("date_symptoms") == 0 
            || features[i].compare("date_died") == 0 || i == 1 || i == 9 || i == 8 || i == 11 || i == 10;

            if(ignore){
                // Skip
            }else{
                int yes_Survive = 0;
                int no_Survive = 0;
                int yes_NoSurvive = 0;
                int no_NoSurvive = 0;

                int counts_survive = 0;
                int counts_dead = 0;
                for(int j = 1; j < rows; j++){
                    int value = atoi(data[j][i].c_str());
                    if(data[j][date_died_ind].compare("9999-99-99") == 0){
                        counts_survive++;
                        if(features[i].compare("age") == 0){
                            if(value  >= age_desired)
                                yes_Survive++;
                            else if(value < age_desired)
                                no_Survive++;
                            else
                                continue;
                        }
                        else{
                            if(value == 1)
                                yes_Survive++;
                            else if(value == 2)
                                no_Survive++;
                            else
                                continue;
                        }
                    }
                    else{
                        counts_dead++;
                        if(features[i].compare("age") == 0){
                            if(value >= age_desired)
                                yes_NoSurvive++;
                            else if(value < age_desired)
                                no_NoSurvive++;
                            else
                                continue;
                        }
                        else{
                            if(value == 1)
                                yes_NoSurvive++;
                            else if(value == 2)
                                no_NoSurvive++;
                            else
                                continue;
                        }
                    }             
                }
                double alpha = .5;
                double prob_true_given_survive = (double(yes_Survive)+alpha)/((counts_survive) + alpha*(featureLength - 1));
                double prob_false_given_survive = (double(no_Survive) + alpha)/((counts_survive) + alpha*(featureLength - 1));
                double prob_true_given_not_survive = (double(yes_NoSurvive) + alpha)/((counts_dead) + alpha*(featureLength - 1));
                double prob_false_given_not_survive = (double(no_NoSurvive) + alpha)/((counts_dead) + alpha*(featureLength - 1));
            
                // cout << "P( " << features[i] << " | Survive ) = " << prob_true_given_survive << endl;
                // cout << "P( not " << features[i] << " | Survive ) = " << prob_false_given_survive << endl;
                // cout << "P( " << features[i] << " | not Survive ) = " << prob_true_given_not_survive << endl;
                // cout << "P( not " << features[i] << " | not Survive ) = " << prob_false_given_not_survive << endl;
                
                survived_cond_prob.push_back(prob_true_given_survive);
                survived_cond_prob.push_back(prob_false_given_survive);
                not_survived_cond_prob.push_back(prob_true_given_not_survive);
                not_survived_cond_prob.push_back(prob_false_given_not_survive);
            }
            
        }
        
        // double trainTime = double(clock() - t) / CLOCKS_PER_SEC;
        // cout << "Training Time: " << trainTime << " seconds" << endl;
        // t = clock();
        //double train_accuracy = getAccuracy(cvd_train,P_survive,P_dead, survived_cond_prob,not_survived_cond_prob,age_desired);
        double test_accuracy = getAccuracy(cvd_valid,P_survive,P_dead, survived_cond_prob,not_survived_cond_prob,age_desired);
        // double testTime = double(clock() - t) / CLOCKS_PER_SEC;
        // cout << "Test Time: " << testTime << " seconds" << endl;
        // cout << "Test Accuracy: " << test_accuracy << endl;
        // cout << "Train Accuracy: " << train_accuracy << endl;
        
        // cout << "Sizes: " << survived_cond_prob.size() << "     " << not_survived_cond_prob.size() << endl;
        //cout << "Test Accuracy: " << test_accuracy << endl;

    //     accuracies.push_back(test_accuracy);

    // }

    // double maxAccuracy = accuracies[0];
    // int maxAge = 30;
    // for(int i = 0; i < accuracies.size(); i++){
    //     if(accuracies[i] > maxAccuracy)
    //     {
    //         maxAge = i + 30;
    //         maxAccuracy = accuracies[i];
    //     }
    // }

    // cout << "Max Accuracy: " << maxAccuracy << endl;
    // cout << "Max Age: " << maxAge << endl;
    return 0;    
}

double getAccuracy(string file_name , double survive, double dead, vector<double> survive_cond, vector<double> dead_cond, int age_desired){
    double accuracy;
    double correct = 0;
    double total = 0;

     // Open the training file
    string line;
    ifstream csv_file(file_name);
    getline(csv_file,line);

    int featureLength = 22; 

    if(csv_file.is_open()){
        while(csv_file.good()){
            int label = 0;
            double survive_prob = log(survive);
            double dead_prob = log(dead);
            int predicted_label = 0;
            int vectorCount = 0;
            for(int j = 0; j < featureLength; j++){
                if(j == featureLength - 1){
                    getline(csv_file,line,'\n');
                    int value = atoi(line.c_str());
                    if(value == 1){
                        survive_prob += log(survive_cond[2*vectorCount]);
                        dead_prob += log(dead_cond[2*vectorCount]);
                    }
                    else if(value == 2){
                        survive_prob += log(survive_cond[(2*vectorCount)+1]);
                        dead_prob += log(dead_cond[(2*vectorCount)+1]);
                    }
                    else{
                        continue;
                    }
                }
                else if(j == 2 || j == 3 || j == 1 || j == 9 || j == 8 || j == 11 || j == 10){
                    getline(csv_file,line,',');
                }
                else if(j == 4){
                    getline(csv_file,line,',');
                    if(line.compare("9999-99-99") == 0)
                        label = 0;
                    else
                        label = 1;
                }
                else{
                    getline(csv_file,line,',');
                    int value = atoi(line.c_str());
                    if(value == 1 || ((value >= age_desired) && j == 7)){
                        survive_prob += log(survive_cond[2*vectorCount]);
                        dead_prob += log(dead_cond[2*vectorCount]);
                    }
                    else if(value == 2 || ((value < age_desired) && j == 7)){
                        survive_prob += log(survive_cond[(2*vectorCount)+1]);
                        dead_prob += log(dead_cond[(2*vectorCount)+1]);
                    }
                    else{
                        ;
                    }
                    vectorCount++;
                    
                }
            }
            
            if(survive_prob > dead_prob)
                predicted_label = 0;
            else
                predicted_label = 1;
            
            cout << predicted_label << endl;
            if(label == predicted_label)
                correct++;

            total++;
        }
    }
    else{
        cout << "Unable to open file: covid_train.csv" << endl;
        exit(EXIT_FAILURE);
    }
    
    csv_file.close();
    accuracy = double(correct)/total;
    return accuracy;
}