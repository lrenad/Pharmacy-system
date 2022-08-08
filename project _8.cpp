//Pharmacy system
//team number: 2 

//arwa alhindi    2210003264
//manar alzahrani 2210003175
//dana albrahim   2210003181
//renad alharbi   2210002476


#include <iostream>
#include <string>
#include <fstream>
#include <ctime>


using namespace std;

const int MAX_SIZE=150;

//stat counters
	int add_count=0, delete_count=0, update_count=0, stock_count=0;


struct Medicine{
  string med_num;
  string med_name;
  string manufacturer;
  int quantity;
};
struct record
{
	
	int records;
	int day;
	int month;
	int year;
	int hour;
	int mins;
	int sec;
};
record Data;

void Menu(int& x);
void display_meds(Medicine m[], int size);
void add_meds(Medicine m[], int size);
bool delete_meds(Medicine m[], int size);
bool search_meds(Medicine* m, int size);
void sort_meds(Medicine m[], int size);
void update_meds(Medicine m[], int size);
bool take_meds(Medicine m[], int size);
void open_file(string FileName, Medicine m[], int &size);
void save_file(string FileName, Medicine m[], int size);
bool login(string , bool & );
bool login(int , bool & );
int Nrecord(int & , int & ); 



void Menu(int& x)
{
  cout << endl;
    cout << "\t the main Survices of pharmacy store: " << endl;
  cout << "Choose one of the operations by entering the number or press 0 to exit: " << endl;
  cout << " 1- View all the medicine \n 2- Adding new medicine \n 3- Delete medicine \n 4- Search for specific medicine \n 5- Update medicine name \n 6- Sort the madicine in the store \n 7- Take medicine" << endl;
  cin >> x;}


void display_meds(Medicine m[], int n){
  
  if (n>0)
  {
     for(int i=0; i<n;i++)
      {
        cout<<"\tNumber of the medicine: "<<m[i].med_num<<endl;
        cout<<"\tName of the medicine: "<<m[i].med_name<<endl;
        cout<<"\tManufacturer: "<<m[i].manufacturer<<endl;
        cout<<"\tQuantity: "<<m[i].quantity<<endl;
        cout<<"-------------------------------------------"<<endl;
        
      }
  }
  else
      cout<<"No medicine records saved."<<endl;
}


void add_meds(Medicine m[], int n){
  cout<<"Enter the name of the medicine:"<<endl;
  cin.ignore();
  getline(cin, m[n].med_name);
  cout<<"Enter the name of the manufacturer of the medicine:"<<endl;
  getline(cin, m[n].manufacturer);
  cout<<"Enter the medicine number :"<<endl;
  cin>>m[n].med_num;
  cout<<"Enter the amount of medicine available:"<<endl;
  cin>>m[n].quantity;
  n++;
}



bool delete_meds(Medicine m[], int size)
{
  bool flag = false;
  string deletemedicine;
  cout << "Which medicine do you want to delete?"<<endl;
  cin >> deletemedicine;
  for (int i = 0; i < size - 1; i++)
  {
    if (m[i].med_name == deletemedicine)
    {
      flag = true;
      for (int j = i; j < size - 1; j++)
      {
        m[j] = m[j + 1];
        
      }
    }

  }

  return flag;
}

bool search_meds(Medicine* m, int size) {
  string searchmeds;
  bool found = false;
  cout << "Enter the name of the medicine you want to find: ";
  cin >> searchmeds;

  for (int i = 0; i <= size; i++) {
    if (m[i].med_name == searchmeds) {
      found = true;
      cout << "Medicine: " << searchmeds << " was found in shelf number: " << i + 1<<endl;
    }
  }
  if (found == false)
  {
    cout << "Sorry, we cant find your medicine."<<endl;
  }

  return found;
}



void sort_meds(Medicine m[], int size)
{
  Medicine X;

  int W = size;
  cout << "Sorting................." << endl;

  for (W; W > 0; W--)
  {
    for (int i = 0; i < size - 1; i++)
    {
      if (m[i].med_name > m[i + 1].med_name)
      {
        X = m[i + 1];
        m[i + 1] = m[i];
        m[i]= X;
      }

    }
    size--;
  }
  
  cout<<"Sorting complete."<<endl;

}

void update_meds(Medicine m[], int size){
  
  string newname;
  string oldname;
  
  cout<<"Enter the name of the medicine you would like to update:"<<endl;
  cin>>oldname;
  
  for (int i = 0; i <= size; i++) {
    if (m[i].med_name == oldname) {
      cout <<"Enter the new name for the medicine:"<<endl;
      cin>>newname;
      m[i].med_name=newname;
       cout<<"Updating complete."<<endl;
    }
  }
 
}

bool take_meds(Medicine m[] ,int size)
{
	string takemedicine;
	bool found=false;
	int amount;
	cout<<"Which medicine would you like to take?"<<endl;
	cin>>takemedicine;
	
	for (int i=0; i<size; i++)
	{
		if (m[i].med_name == takemedicine)
		{
			found=true;
			cout<<"How much would you like to take?"<<endl;
			cin>>amount;
			
			if (m[i].quantity<amount)
			{
				cout<<"There is not enough medicine in stock."<<endl;
			} else {
				m[i].quantity=m[i].quantity-amount;
				cout<<"There is now "<<m[i].quantity<<" medicine left in stock."<<endl;
			}
			if (m[i].quantity<2)
				{
					cout<<"Medicine stock is low. Restock needed."<<endl;
				}
		}
		
	}
	if (!found)
	{
		cout<<"Medicine not found."<<endl;
	}
	return found ;
}

void save_file(string FileName, Medicine m[], int size)
{
	ofstream outFile;
	outFile.open(FileName.c_str());
	if(outFile.is_open())
	{
		for (int i=0;i<size;i++)
		{
		outFile << endl;
		outFile << m[i].quantity<<endl;
		outFile << m[i].med_num <<endl;
		outFile << m[i].med_name <<endl;
		outFile << m[i].manufacturer;
		}
	outFile.close();
	}

}

void open_file(string FileName, Medicine m[], int &size){
  
	ifstream inFile;
	inFile.open(FileName.c_str());
	
	
	if(inFile.is_open() == true || inFile.is_open()) {
			int counter=0;
		while(!inFile.eof()) {
				inFile >> m[counter].quantity;
				inFile.ignore();
		        getline(inFile, m[counter].med_num);
		        getline(inFile, m[counter].med_name);
		        getline(inFile, m[counter].manufacturer);
		        counter++;}
		    size=counter;
			} 
		else {cout<< "File not found."<<endl;}
		
		inFile.close();
  
}




bool login(string username, bool &found1) {
	cout << "Enter username   :";
	cin >> username; 
	if (username == "P1") {found1 = true;}
	else{found1 = false;}
	return found1;
}

bool login(int passcode, bool &found1) {
	cout << "Enter passcode  :";
	cin >> passcode;
	if (passcode == 2022) {found1 = true;}
	else {found1 = false;}
	return found1;
}

int Nrecord(int &Rsize, int &y) 
{

	while (y!=0)
	{
		cout << "Please indicate a maximum size for the records, range from 10 to 150" << endl; 
		cin >> Rsize;
		
		if (Rsize >= 10 && Rsize <= 150) {
			cout << "Records maximum size is: " << Rsize << endl; 
			y = 0;
		}
		else {
			cout << "incorrect size." << endl;
		}
			
    }  
    return Rsize;
}

int main(){
	int numOfMeds;
	string username;
	int passcode;
	bool foundUser;
	bool foundPass;
	int x;
  	int Rsize;
	int y = 1;
	
   
	  
	cout<<"------------------------------------------------\n";
	cout << " \t WELCOME TO THE IT PHARMACY STORE \t" << endl;
	cout<<"------------------------------------------------\n";
	  
	login(username, foundUser); 
	login(passcode, foundPass);
	if (foundUser && foundPass) {Nrecord(Rsize, y);} 
	else{cout << "sorry, you are not an admin !"<<endl;}
	Medicine meds[Rsize];
	
  	//load file
	open_file("meds.txt", meds, numOfMeds);
  

   
    if (y == 0)
    {
    cout << "\n\t----- Hello pharmacist------ \n";
      do {
        
        Menu(x);


        
      
             if (x == 1)
        {
        	display_meds(meds, numOfMeds);
          
        }
        else if (x == 2)
        {
        	add_meds(meds, numOfMeds);
        	numOfMeds++;
        	add_count++;
        }

        else if (x == 3)
        {
        	delete_meds(meds, numOfMeds);
        	numOfMeds--;
        	delete_count++;
        }
        else if (x == 4)
        {
        	search_meds(meds, numOfMeds);
        
        }
        else if (x == 5)
        {
        	update_meds(meds, numOfMeds);
        	update_count++;
        }
        else if (x == 6)
        {
        	sort_meds(meds, numOfMeds);
        }
        else if ( x == 7)
        {
        	take_meds(meds, numOfMeds);
        	stock_count++;
		}
        else if (x<0||x>7)
        {
          cout << "Invalid choice, please try again.\n";
        }


      } while (x != 0);
      save_file("meds.txt", meds, numOfMeds);
      }

   


	ofstream outf;
	outf.open("Report.txt", ios::app);
	if (outf.fail())
	{
		cout << "Cant Open File." << endl;
	}
	else
	{
		time_t now;
		struct tm nowLocal;
		now = time(0);
		nowLocal = *localtime(&now);
		
		Data.day = nowLocal.tm_mday;
		Data.month = nowLocal.tm_mon + 1;
		Data.year = nowLocal.tm_year + 1900;
		Data.hour = nowLocal.tm_hour;
		Data.mins = nowLocal.tm_min;
		Data.sec = nowLocal.tm_sec;

		outf << Data.day << "/";
		outf << Data.month << "/";
		outf << Data.year << endl;
		outf << Data.hour << ":";
		outf << Data.mins << ":";
		outf << Data.sec << endl;
		outf << "Medicine count: "<< numOfMeds << endl;
		outf << "Medicines added: "<< add_count <<endl;
		outf << "Medicines updated: "<< update_count <<endl;
		outf << "Medicines deleted: "<< delete_count <<endl;
		outf << "Medicines taken: "<< stock_count <<endl;
		outf << "------------------------------------------"<<endl;

	}

    
  return 0;}



