// Naimul Hoque Machine Problem 1 Naive Bayes Classifier

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>

using namespace std;

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

    if(str1.compare("covid_valid.csv") != 0 && str2.compare("covid_valid.csv") != 0){
        cout << "Incorrect File: covid_valid.csv" << endl;
        exit(EXIT_FAILURE);
    }
    if(str1.compare("covid_train.csv") != 0 && str2.compare("covid_train.csv") != 0){
        cout << "Incorrect File: covid_train.csv" << endl;
        exit(EXIT_FAILURE);
    }
    
    string cvd_train = "covid_train.csv";
    string cvd_valid = "covid_valid.csv";


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

    cout << "Begin Algorithm" << endl << endl;
    cout << "Getting Label Probabilities" << endl << endl;
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

    // Print out probability of P(dead) and P(Survive)
    cout << "Probability of Surviving Training Data: " << P_survive << endl;
    cout << "Probability of Dying Training Data: " << P_dead << endl << endl;

    // Time to determine conditional probabilities given the person survives.
    cout << "Gather conditional probabilities given the person survives" << endl << endl;
    
    vector<double> survived_cond_prob;
    vector<double> not_survived_cond_prob;

    // Chose 1 = true and 2 = false
    for(int i = 0; i < featureLength; i++){

        bool ignore = features[i].compare("entry_date") == 0 || features[i].compare("date_symptoms") == 0 
        || features[i].compare("date_died") == 0 || features[i].compare("age") == 0 ;

        if(ignore){
            // Skip
        }else{
            int yes = 0;
            int no = 0;
            int ignoredVals = 0;
            int counts = 0;
            for(int j = 1; j < rows; j++){
                int value = atoi(data[j][i].c_str());
                if(data[j][date_died_ind].compare("9999-99-99") == 0)
                    ;
                else if(value == 1){
                    counts++;
                    yes++;
                }
                else if(value == 2){
                    counts++;
                    no++;
                }
                else
                    ignoredVals++;
            }
            double prob_true_given_survive = double(yes)/(counts);
            double prob_false_given_survive = double(no)/(counts);
            cout << "P(" << features[i] << " | Survive) = " << prob_true_given_survive << endl;
            cout << "P(not " << features[i] << " | Survive) = " << prob_false_given_survive << endl;
            survived_cond_prob.push_back(prob_true_given_survive);
            survived_cond_prob.push_back(prob_false_given_survive);
            
        }
        
    }

     // Time to determine conditional probabilities given the person survives.
    cout << "Gather conditional probabilities given the person does not survives" << endl << endl;

     // Chose 1 = true and 2 = false
    for(int i = 0; i < featureLength; i++){

        bool ignore = features[i].compare("entry_date") == 0 || features[i].compare("date_symptoms") == 0 
        || features[i].compare("date_died") == 0 || features[i].compare("age") == 0 ;

        if(ignore){
            // Skip
        }else{
            int yes = 0;
            int no = 0;
            int ignoredVals = 0;
            int counts = 0;
            for(int j = 1; j < rows; j++){
                int value = atoi(data[j][i].c_str());
                if(data[j][date_died_ind].compare("9999-99-99") != 0)
                    ;
                else if(value == 1){
                    yes++;
                    counts++;
                }
                else if(value == 2){
                    counts++;
                    no++;
                }
                else
                    ignoredVals++;
            }
            double prob_true_given_not_survive = double(yes)/(counts);
            double prob_false_given_not_survive = double(no)/(counts);
            cout << "P(" << features[i] << " | not Survive) = " << prob_true_given_not_survive << endl;
            cout << "P(not " << features[i] << " | not Survive) = " << prob_false_given_not_survive << endl;
            not_survived_cond_prob.push_back(prob_true_given_not_survive);
            not_survived_cond_prob.push_back(prob_false_given_not_survive);
            
        }
        
    }

    t = clock() - t;
    cout << "\nTraining Time: " << float(t)/CLOCKS_PER_SEC << " seconds" << endl << endl;

    cout << "Begin testing.";
    // Test the data set
    
}
