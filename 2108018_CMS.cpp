/*The following program is about a contact management system that covers the following OOP concepts

1)class and objects
2)Encapsulation
3)Abstraction
4)Constructors and member functions
5)operator overloading
6)friend function
7)File handling  & ifstream and ofstream classes
8)Inheritance
9)Polymorphism
10)Switch statement for menu driven program

*/

#include <iostream>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
using namespace std;

class contact{
protected:
	char fName[50], lName[50], address[50], email[50];
	long long phNo;

public:
    contact()                                               //default constructor that sets all the data members to 0 or null values
    {
        for(int i=0; i<50; i++){
            fName[i]='\0';
            lName[i]='\0';
            address[i]='\0';
            email[i]='\0';
        }
        phNo=0;
    }
	virtual ~contact(){}							//virtual destructor to prevent any memory leaks due to deletion of base class pointer

    virtual void writeOnFile()=0;
    virtual void readFromFile()=0;                              // pure virtual functions
    virtual void searchOnFile()=0;                              //These are used to achieve abstract in runtime polymorphism
    virtual void deleteFromFile()=0;
    virtual void editContact()=0;

     friend ostream& operator<<(ostream& os, contact& obj) {      //ostream operator overloading
        os << "Name: " << obj.fName << " " << obj.lName << endl;
        os << "Phone: " << obj.phNo << endl;
        os << "Address: " << obj.address << endl;
        os << "Email: " << obj.email << endl;
        return os;
    }

    friend istream& operator>>(istream& is, contact& obj) {             //istream operator overloading
        cout << "Enter first name: ";
        is >> obj.fName;
        cout << "Enter last name: ";
        is >> obj.lName;
        cout << "Enter phone number: ";
        is >> obj.phNo;
        cout << "Enter address: ";
        is >> obj.address;
        cout << "Enter email: ";
        is >> obj.email;
        return is;
    }
};

class add_contact: public contact
{
public:
	void writeOnFile() {
		char ch;
		ofstream f1;
		f1.open("CMS.dat",ios::binary|ios::app);

		do {
			cin>>*this;                                       //overloaded cin used
			f1.write((char*)(this),sizeof(*this));

			cout<<"Do you have next data?(y/n)"<<endl;
			cin>>ch;
		}while(ch=='y');

		cout<<"Contact has been Successfully Created...";
		f1.close();
	}


     void readFromFile(){};                              // overrides the pure virtual functions form base class
     void searchOnFile(){};
     void deleteFromFile(){};
     void editContact(){};
};



class show_contacts : public contact
{
public:
	void readFromFile() {
		ifstream f2;
		f2.open("CMS.dat",ios::binary);

		cout<<"\n================================\n";
		cout<<"LIST OF CONTACTS";
		cout<<"\n================================\n";

		while(!f2.eof()) {
			if(f2.read((char*)(this),sizeof(*this)))
			{
				cout<<*this;                                    //overloaded cout used
				cout<<"\n================================\n";
			}
		}

		f2.close();
	}


     void writeOnFile(){};                              // overrides the pure virtual functions form base class
     void searchOnFile(){};
     void deleteFromFile(){};
     void editContact(){};
};


class search_contact: public contact
{
    public:
	void searchOnFile() {
		ifstream f3;
		long long phone;
		cout<<"Enter phone no.: ";
		cin>>phone;
		f3.open("CMS.dat",ios::binary);

		while(!f3.eof()) {
			if(f3.read((char*)(this), sizeof(*this))) {
				if (phone==phNo) {
					cout<<*this;                             //overloaded cout used
					return;
				}
			}
		}
		cout<<"\n\nNo record found";
		f3.close();
	}


     void writeOnFile(){};                             // overrides the pure virtual functions form base class
     void readFromFile(){};
     void deleteFromFile(){};
     void editContact(){};
};

class delete_contact : public contact
{

public:
	void deleteFromFile() {
		long long num;
		int flag = 0;
		ofstream f4;
		ifstream f5;

		f5.open("CMS.dat",ios::binary);
		f4.open("temp.dat",ios::binary);

		cout<<"Enter phone no. to delete: ";
		cin>>num;

		while(!f5.eof()) {
			if(f5.read((char*)(this),sizeof(*this))) {
				if(phNo!=num) {
					f4.write((char*)(this),sizeof(*this));
				}
				else
					flag = 1;
			}
		}
		f5.close();
		f4.close();

		remove("CMS.dat");
		rename("temp.dat","CMS.dat");

		flag==1?
		cout<<"\tContact Deleted...":
		cout<<"\tContact Not Found...";
	}



     void writeOnFile(){};
     void readFromFile(){};                          // overrides the pure virtual functions form base class
     void searchOnFile(){};
     void editContact(){};
};

class edit_contact: public contact
{
public:
	void editContact() {
		long long num;
		fstream f6;

		cout<<"Edit contact";
		cout<<"\n===============================\n\n";
		cout<<"Enter the phone number to edit: ";
		cin>>num;

		f6.open("CMS.dat",ios::binary|ios::out|ios::in);

		while(!f6.eof()) {
			if(f6.read((char*)(this),sizeof(*this))) {
				if (phNo==num) {
					cout<<"Enter new record\n";
					cin>>*this;                                 //overloaded cin used

					int pos=-1*sizeof(*this);
					f6.seekp(pos,ios::cur);

					f6.write((char*)(this),sizeof(*this));
					cout<<endl<<endl<<"\t Contact Successfully Updated...";
					return;
				}
			}
		}
		cout<<"\n\nNo record found";
		f6.close();
	}



     void writeOnFile(){};
     void readFromFile(){};
     void searchOnFile(){};                              // overrides the pure virtual functions form base class
     void deleteFromFile(){};
};

int main() {
	system("cls");
	system("Color 2F"); // "Color XY", X - background color, Y - text color

	cout<<"\n\n\n\n\n\n\n\n\t\t\t\t\t* WELCOME TO CONTACT MANAGEMENT SYSTEM *";
	getch();

	while(1) {

        add_contact ob_add;
        show_contacts ob_show;
        search_contact ob_search;
        delete_contact ob_delete;
        edit_contact ob_edit;

		contact *c1;

		int choice;

		system("cls");
		system("Color 02");

		cout<<"\nCONTACT MANAGEMENT SYSTEM";
        cout<<"\n\nMAIN MENU";
		cout<<"\n=====================\n";
        cout<<"[1] Add a new Contact\n";
        cout<<"[2] List all Contacts\n";
        cout<<"[3] Search for contact\n";
        cout<<"[4] Delete a Contact\n";
        cout<<"[5] Edit a Contact\n";
        cout<<"[0] Exit";
		cout<<"\n=====================\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice) {
        	case 1:
        		system("cls");

                c1=&ob_add;
        		c1->writeOnFile();                   //polymorphism achieved
        		break;

        	case 2:
				system("cls");

                c1=&ob_show;
        		c1->readFromFile();                  //polymorphism achieved
        		break;

			case 3:
        		system("cls");

                c1=&ob_search;
        		c1->searchOnFile();                  //polymorphism achieved
        		break;

        	case 4:
				system("cls");

                c1=&ob_delete;
        		c1->deleteFromFile();                   //polymorphism achieved
        		break;

        	case 5:
			    system("cls");

                c1=&ob_edit;
        		c1->editContact();                       //polymorphism achieved
        		break;

        	case 0:
        		system("cls");
        		cout<<"\n\n\n\t\t\tThank you for using CMS."<<endl<<endl;
        		exit(0);
        		break;

        	default:
				continue;
		}

		int opt;
		cout<<"\n\n::Enter the Choice:\n[1] Main Menu\t\t[0] Exit\n";
		cin>>opt;

		switch (opt) {
			case 0:
        		system("cls");
        		cout<<"\n\n\n\t\t\tThank you for using Contact Management System."<<endl<<endl;
        		exit(0);
        		break;

			default:
				continue;
		}
	}

	return 0;
}
