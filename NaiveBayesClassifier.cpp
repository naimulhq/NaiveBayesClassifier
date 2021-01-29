// Naimul Hoque Machine Problem 1 Naive Bayes Classifier

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

int main(int argc, char *argv[]){

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
    vector<string> sex;
    vector<string> patient_type;
    vector<string> entry_date;
    vector<string> date_symptoms;
    vector<string> date_died;
    vector<string> intubed;
    vector<string> pneumonia;
    vector<string> age;
    vector<string> pregnancy;
    vector<string> diabetes;
    vector<string> copd;
    vector<string> asthma;
    vector<string> inmsupr;
    vector<string> hypertension;
    vector<string> other_disease;
    vector<string> cardiovascular;
    vector<string> obesity;
    vector<string> renal_chronic;
    vector<string> tobacco;
    vector<string> contact_other_covid;
    vector<string> covid_res;
    vector<string> icu;

    ifstream csv_file(cvd_train);
    if(csv_file.is_open()){
        while(csv_file.good()){
            getline(csv_file,line,',');
            sex.push_back(line);

            getline(csv_file,line,',');
            patient_type.push_back(line);

            getline(csv_file,line,',');
            entry_date.push_back(line);

            getline(csv_file,line,',');
            date_symptoms.push_back(line);

            getline(csv_file,line,',');
            date_died.push_back(line);

            getline(csv_file,line,',');
            intubed.push_back(line);

            getline(csv_file,line,',');
            pneumonia.push_back(line);

            getline(csv_file,line,',');
            age.push_back(line);

            getline(csv_file,line,',');
            pregnancy.push_back(line);

            getline(csv_file,line,',');
            diabetes.push_back(line);

            getline(csv_file,line,',');
            copd.push_back(line);

            getline(csv_file,line,',');
            asthma.push_back(line);

            getline(csv_file,line,',');
            inmsupr.push_back(line);

            getline(csv_file,line,',');
            hypertension.push_back(line);

            getline(csv_file,line,',');
            other_disease.push_back(line);

            getline(csv_file,line,',');
            cardiovascular.push_back(line);

            getline(csv_file,line,',');
            obesity.push_back(line);

            getline(csv_file,line,',');
            renal_chronic.push_back(line);

            getline(csv_file,line,',');
            tobacco.push_back(line);
            
            getline(csv_file,line,',');
            contact_other_covid.push_back(line);

            getline(csv_file,line,',');
            covid_res.push_back(line);

            getline(csv_file,line,'\n');
            icu.push_back(line);
        
        }
        csv_file.close();
    }
    else{
        cout << "Unable to open file: covid_train.csv" << endl;
        exit(EXIT_FAILURE);
    }

   
    return 0;
}
