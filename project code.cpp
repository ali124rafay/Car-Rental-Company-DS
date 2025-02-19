#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <sstream>
using namespace std;

class Customer;

int driver_rent = 3000;

class cars{
	int carid;
	char car_name[100];
	float price_mil;
	
	public:
		cars(){
		 carid = 000;
		 strcpy(car_name,"Hello");
		 price_mil = 45.5;
		}
		cars(int a, char* arr, float c)
		{
			carid = a;
			strcpy(car_name,arr);
			price_mil = c;
		}
		
		int getid()
		{
			return carid;
		}
		char* getname()
		{
			return car_name;
		}
		float getprice()
		{
			return price_mil;
		}
		
		void display()
		{
			cout<<"#  "<<carid<<"\t\t"<<car_name<<"\t\t"<<price_mil<<"\t\t#"<<endl;
		}
		
		bool compare(cars obj)
		{
			if(obj.getid() == carid)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

};

class node{
	public:
	cars data;
	node *left;
	node *right;
	
	node(cars temp)
	{
		data = temp;
		left = NULL;
		right = NULL;
	}
};

class BST{
	node *root;
	int flag;
	void inorder(node *temp)
		{
			if(temp != NULL)
			{
				inorder(temp->left);
				temp->data.display();
				inorder(temp->right);
			}
		}
	
	node* minvaluenode(node* n){
        node* current = n;
        
        while(current -> left != NULL)
            current = current->left;
            
        return current;
    }
	
	node* Deletenode(node* rot, int data){
        if(rot == NULL)
            return NULL;
            
        else if(data < rot->data.getid())
            rot->left = Deletenode(rot->left, data);
            
        else if(data > rot->data.getid())
            rot->right = Deletenode(rot->right, data);
            
        else{
            if(rot->left == NULL){
                node* temp = rot->right;
                delete rot;
                return temp;
            }
            
            else if(rot->right == NULL){
                node* temp = rot->left;
                delete rot;
                return temp;
            }
            
            else{
                node* temp = minvaluenode(rot->right);
                rot->data = temp->data;
                rot->right = Deletenode(rot->right, temp->data.getid());
            }
        }
        return rot;
    }
		
		void traverse(node *temp)
		{
			if(temp!=NULL)
			{
				cars cobj;
				traverse(temp->left);
				fstream obj;
				obj.open("car.txt",ios::out | ios::binary | ios::app );	
				if(!obj)
				cout<<" error while opening the file ! "<<"app"<<endl;
			    cobj=temp->data;
			    obj.write((char*)&cobj,sizeof(cars));
			    obj.close();
				
				traverse(temp->right);  
			}
		}
		
		
	public:
		BST()
		{
			root = NULL;
		}
		
		void insert(cars data)
		{
			node *n = new node(data);
			if(root == NULL)
			{
				root = n;
			}
			else
			{
				node *temp = root;
				while(temp != NULL)
				{
					if(data.getid() == temp->data.getid())
					{
						break;
					}
					else if(data.getid() > temp->data.getid())
					{
						if(temp->right == NULL)
						{
							temp->right = n;
							break;
						}
						temp = temp->right;
					}
					else
					{
						if(temp->left == NULL)
						{
							temp->left = n;
							break;
						}
						temp = temp->left;
					}
				}
			}
		}
		
		void del_car(int id)
		{
			node *temp = root;
			if(Deletenode(temp,id)==NULL)
			{
				cout<<"Car not found";
			}
		}
		
		void display()
		{
			cout<<"\n\n\n";
			for(int i=0;i<57;i++)
				cout<<"#";
			cout<<endl;	
			cout<<"#  "<<"ID"<<"\t\t"<<"NAME"<<"\t\t\t"<<"RENT PER Day"<<"\t#"<<endl;
			for(int i=0;i<57;i++)
				cout<<"#";
			cout<<endl;	
			node *temp = root;
			inorder(temp);
			for(int i=0;i<57;i++)
				cout<<"#";
				cout<<"\n\n\n";
		}
		
		cars search(int a)
		{
			if(root->data.getid()==a)
			{
				return root->data;		
			}
			else
			{
				flag = 0;
				node *temp = root;
				while(temp != NULL)
				{
					if(temp->data.getid()==a)
					{
						flag = 1;
						return temp->data;
					}
					else if(a > temp->data.getid())
					{
						temp = temp->right;
					}
					else
					{
						temp = temp->left;
					}
				}
				cars x;
				if(flag == 0)
				{
					cout<<"Car not found\n";
					return x; 
				}
			}
		}
		
		void move_cars_to_file()
		{
			
			fstream obj;
			obj.open("car.txt",ios::out | ios::binary | ios::trunc);
			if(!obj)
			cout<<" error while opening the file ! "<<"trunc"<<endl;
			else
			{
			node *temp = root;
			traverse(temp);   
			}
		}
};

void move_to_BST(BST *obj)
{
		int a;
		char* b;
		float c;
		fstream my_file;
		my_file.open("car.txt", ios::in|ios::binary);
     	if (!my_file) 
		{
			cout << "No such file";
     	}
		else 
		{
		    cars car_object;	
			while(!my_file.eof())
			{
				my_file.read((char*)&car_object,sizeof(cars));
				a = car_object.getid();
				b = car_object.getname();
				c = car_object.getprice();
				cars temp(a,b,c);
				obj->insert(temp);    
			} 
			my_file.close();
		}
	}

void add_car()
{
	int id;
	char name[100];
	float price;    
	
	cout<<"Enter the id of the car that you want to add: ";
	fflush(stdin);
	cin>>id;
	fflush(stdin);
	cout<<"Enter the name of new car : ";
	fflush(stdin);
	cin.get(name, 100);
	cout<<"Enter the rent per day of new car :  ";
	fflush(stdin);
	cin>>price;
	fflush(stdin);
	cars car_object(id,name,price);
		      
	fstream obj;
	obj.open("car.txt",ios::out|ios::binary|ios::app);
	if(!obj)
		cout<<"File not oppened successfully!"<<endl;
	else
	{
		obj.write((char*)&car_object,sizeof(cars));
		obj.close();
	}
		    
}

void modify_car(BST obj)
{
	int n;
	cars temp,temp1;
	obj.display();
	cout<<"Enter id of car you want to modify: ";
	cin>>n;
	temp = obj.search(n);
	if(temp.compare(temp1))
	{
		cout<<"Car not found";
	}
	else
	{
		int nflag = 0,pflag = 0;
		char t[100];
		float d;
		for(int i=0;i<20;i++)//name change
		{
			cout<<"Do you want to edit name of car: [Press 1 fot yes/0 for no]: ";
			cin>>n;
			if(n>1 || n<0)
			{
				cout<<"Invalid\n";
			}
			else if(n==1)
			{
				nflag = 1;
				cout<<"Enter new name for the car: ";
				fflush(stdin);
				cin.get(t, 100);
				fflush(stdin);
				i=20;
			}
			else
			{
				i = 20;
			}
		}	
		for(int i=0;i<20;i++)//price change
	{
			cout<<"Do you want to edit price of car: [Press 1 fot yes/0 for no]: ";
			cin>>n;
			if(n>1 || n<0)
			{
				cout<<"Invalid\n";
			}
			else if(n==1)
			{
				pflag = 1;
				cout<<"Enter new price for the car: ";
				fflush(stdin);
				cin>>d;
				fflush(stdin);
				i=20;
			}
			else
			{
				i = 20;
			}
		}	
		if(nflag == 1 && pflag == 1)
		{
			cout<<"\n\nChanging both name and price - - - - ";
			cars temp2(temp.getid(),t,d);
			obj.del_car(temp.getid());
			obj.insert(temp2);
			obj.move_cars_to_file();
		}	
		else if(nflag == 1 && pflag == 0)
		{
			cout<<"Changing name - - - - -";
			cars temp2(temp.getid(),t,temp.getprice());
			obj.del_car(temp.getid());
			obj.insert(temp2);
			obj.move_cars_to_file();
		}	
		else if(nflag == 0 && pflag == 1)
		{
			cout<<"Changing price - - - - -";
			cars temp2(temp.getid(),temp.getname(),d);
			obj.del_car(temp.getid());
			obj.insert(temp2);
			obj.move_cars_to_file();
		}
		cout<<"Car updated successfully\n\n";	
	}
}
void add_car_obj(cars c_obj)
{
	fstream obj;
	obj.open("car.txt",ios::out|ios::binary|ios::app);
	if(!obj)
		cout<<"File not oppened successfully!"<<endl;
	else
	{
		obj.write((char*)&c_obj,sizeof(cars));
		obj.close();
	}
}
class Customer{
    public:
	int cnic;
	char name[100];
	int carid;
	char car_name[100];
	float rent;
	int days;
	bool driver;
	bool pick;
	Customer(int a,string b,int c,string d,float e,int f,bool k,bool h)
	{
	    cnic=a;
	    strcpy(name, b.c_str());
	    carid=c;
	    strcpy(car_name, d.c_str());
	    rent=e;
	    days=f;
	    driver=k;
	    pick=h;
	}
	Customer()
	{
	    cnic=0000;
	    strcpy(name,"-------");
	    carid=0000;
	    strcpy(car_name,"------");
	    rent=0;
	    days=0;
	    driver=0;
	    pick=0; 
	}
	
	bool compare(Customer data)
	{
		if(data.cnic==cnic)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	
	void readcustomer()
	{
	   
	    fstream obj;
	    obj.open("customer.txt",ios::binary|ios::in);
	      if(!obj)
	    cout<<"File can't be open "<<endl;
	    else
	    {
	        cout<<" File opened succesfully "<<endl;
	        obj.read((char*)this,sizeof(*this));
	        while(!obj.eof())
	        {
	           	obj.read((char*)this,sizeof(*this));
	           	cout<<this->car_name<<endl;
	           	cout<<this->carid<<endl;
	
	        }
	        obj.close();
		}
	}
	

};

void addcustomer(Customer cust)
{
	cout<<"\n\n\t\t\tSaving!\n\n\n";
    fstream obj;
    obj.open("customer.txt",ios::binary|ios::app|ios::out);
    if(!obj)
    	cout<<"File can't be open "<<endl;
	else
	{
	     
	    obj.write((char*)&cust,sizeof(Customer));
		obj.close();    
	}
}	
class cnode{
	public:
	Customer data;
	cnode *next;
	
	cnode(Customer n)
	{
		data = n;
		next = NULL;
	}
};

class CLL{
	cnode *head;
	int flag;
	public:
		
		CLL()
		{
			head = NULL;
		}
		void insert(Customer obj)
		{
			cnode *n = new cnode(obj);
			if(head == NULL)
			{
				head = n;
				return;
			}
			else
			{
				cnode *temp = head;
				while(temp->next!=NULL)
				{
					if(temp->next->data.cnic == obj.cnic)
					{
						break;
					}
					temp = temp->next;
				}
				temp->next=n;
			}
		}
		Customer search(int n)
		{
			flag = 0;
			Customer obj;
			if(head == NULL)
			{
				return obj;
				head = NULL;
				move_customer_to_file();
			}
			if(head->data.cnic == n)
			{
				return head->data;
			}
			else
			{
				cnode *temp = head;
				while(temp->next != NULL)
				{
					if(temp->next->data.cnic == n)
					{
						cnode *x = temp->next;
						temp->next = temp->next->next;
						flag = 1;
						move_customer_to_file();
						return x->data;
					}
					temp = temp->next;
				}
				if(flag == 0)
				{
					return obj;
				}
			}
		}
		void move_customer_to_file()
		{
			Customer cobj;
			cnode *temp;
			temp=head;
			fstream obj;
			obj.open("customer.txt",ios::out | ios::binary | ios::trunc);
			if(!obj)
			cout<<" error while opening the file ! "<<"trunc"<<endl;
			else
			
			obj.close();
			obj.open("customer.txt",ios::out | ios::binary | ios::app );	
			if(!obj)
			cout<<" error while opening the file ! "<<"app"<<endl;
			while(temp!=NULL)
			{
			    cobj=temp->data;
			    obj.write((char*)&cobj,sizeof(Customer));
			    temp=temp->next;
			}
			obj.close();    
		}
//		void disp()
//		{
//			cout<<"\n\n\nClient list:\n";
//			if(head == NULL)
//			{
//				cout<<"No data\n\n\n";
//			}
//			cnode *temp = head;
//			while(temp != NULL)
//			{
//				cout<<temp->data.cnic<<endl;
//				temp = temp->next;
//			}
//			cout<<"\n\n\n";
//		}
};

void new_customer(int nic)
{ 
	cout<<"NIC: "<<nic<<endl;
	int x, choice;
	cars temp,temp1;
	char name[100], car_name[1000];
	bool driver, pick;
	int carid, days;
	float rent;
	cout<<"Enter your name: ";
	cin>>name;
	cout<<"\n\n\n\t\tWelcome! "<<name<<" to FAST car rental services\n\n";

	//________________________________________________move data from file in BST obj_______________//

	BST obj;
	move_to_BST(&obj);
	obj.display();
	cout<<"\n\n-------------------- SELECT CAR --------------------\n\n\n\n";
	
	for(int i=0;i<20;i++) // car choose
	{
		cout<<"Enter id of car you want: ";
		cin>>x;
		temp = obj.search(x);
		if(temp.compare(temp1))
		{
			cout<<"Invalid!\n";
		}
		else
		{
			cout<<"Car found\n";
			cout<<"You have choosen the following car\n";
			temp.display();
			i = 20;
		}
	}


	cout<<"\n\n-------------------- SELECT DRIVER --------------------\n\n\n\n";
	choice = 3;
	for(int i=0;i<20;i++)  // driver
	{
		cout<<"Do you want driver for your car: [Press 1 for yes/0 for no]";
		cin>>choice;
		if(choice == 1)
		{
			cout<<"Driver will charge Rs "<<driver_rent<<"/- per day\n";
			i = 20;
			driver = true;
		}
		else if(choice == 0)
		{
			cout<<"No extra charges will be applied for driver\n";
			i = 20;
			driver = false;
		}
		else
		{
			cout<<"Invalid\n";
		}
	}


	cout<<"\n\n-------------------- SELECT DAYS --------------------\n\n\n\n";
	days = 100;
	for(int i=0;i<20;i++)  // days
	{
		cout<<"Enter days for which you want the car (Max 20): ";
		cin>>days;
		if(days>20)
		{
			cout<<"Invalid!\n";
		}
		else
		{
			cout<<"You choosed "<<days<<" days\n";
			i = 20;
		}
	}

	cout<<"\n\n-------------------- SELECT PICKUP --------------------\n\n\n\n";
	choice = 3;
	for(int i=0;i<20;i++)  // pickup
	{
		cout<<"\n\nWill you pick it from the garage or shall we drop it to your home [1 for garage/ 2 for home] ";
	    fflush(stdin);
	    cin>>choice;
	
		if(choice==1)
		{
			cout<<"\n                   The location of garages are :  ";
			cout<<"\n                   Our Garages Locations are as follow\n";
			cout<<"                    Nazimabad no 4 behind Imtiaz Super Market\n";
			cout<<"                    Soldier Bazar no 2 near Taj Gasoline pump\n";
			cout<<"                    Malir Halt 11-A near Shamsi Masjid\n";
			cout<<"                    Shah Latif Town near Fast Nu.\n";
			i = 20;
			pick = false;
		}
		else if(choice==2)
		{
			string address;
			cout<<"Enter your address\n";
			fflush(stdin);
			cin>>address;
			i = 20;
			pick = true;
		}
		else
		{
			cout<<"Invalid!\n";
		}
	}

	cout<<"\n\n\n\t\t\t~~CAR RENTED SUCCESSFULLY~~\n\n\n\n\t\t\t5 litres of fuel will be given with the car!";
	obj.del_car(temp.getid());
	obj.move_cars_to_file();
	int a=temp.getid();
	char* b=temp.getname();
	float c=temp.getprice();
	Customer cust(nic,name,a,b,c,days,driver,pick);
	addcustomer(cust);
}
//_____________________________________________________________________________________________________//

void pending_customer(Customer cust)
{
	cars car_obj(cust.carid,cust.car_name,cust.rent);
	add_car_obj(car_obj);
	int rdays,pdays=0;
	int Discount=0;
	cout<<"\n\n\n\t\t\tWELCOME "<<cust.name<<"\n\n\n";
	
	for(int i=0;i<20;i++)  // days
	{
		cout<<"In how many days have you returned the car ";
		cin>>rdays;
		if(rdays>30)
		{
			cout<<"Invalid!\n";
		}
		else if(cust.days == rdays)
		{
			cout<<"Great work! You have returned the car on the communicated date";
			Discount=1;

			i = 20;
		}
		else if(rdays>cust.days)
		{
			pdays = rdays - cust.days;
			cout<<"You have returned the car "<<pdays<<" after the communicated date\nRs1500 per day will pe charged as penalty"<<endl;
			i=20;
		}
		else if(cust.days > rdays)
		{
			cout<<"You have returned the car "<<cust.days-rdays<<" before the communicated date"<<endl;
			Discount=1;
			i = 20;
		}
		
		}
		   
    char condition;
    
    int damage=0;
    
    float bill=(cust.days)*(cust.rent);
    
    float x=(cust.days)*(cust.rent);
    
	cout<<"\nTell about the condition of car \n1.Good(G)\n2.Bad(B)\n";
	
    cin>>condition;
    
	switch(condition)
	{
		case 'G':
		case 'g':	
			cout<<"No extra charges will be added on total bill\n";
			Discount=1;
			break;
		case 'B':
		case 'b':
    	cout<<"What type of damage occurs to the car:\nPress F for Tyre Flat(F)\nPress E for Engine Exhaust(E)\nPress G for Gear Box/Transmission Problem(G)\nPress O for Other problems(O)\n";
		Discount=0;
		char type;
		cin>>type;
		
			if(type=='F')
			{
				cout<<"7000 PKR will be surcharged as penalty.\n";
				damage=damage+7000;
			}
			else if(type=='E')
			{
				cout<<"50000 PKR will be surcharged as penalty.\n";
				damage=damage+50000;
			}
			else if(type=='G')
			{
				cout<<"15000 PKR will be surcharged as penalty.\n";
				damage=damage+15000;
			}
			else if(type=='O')
			{
				cout<<"35000 PKR will be surcharged as penalty.\n";
				damage=damage+35000;
			}
			break;			
		default:
			cout<<"Invalid.\n";
	}
	
	cout<<"\nPress any key for bill reciept\n";
      getch();
      int drent = 0;
	if(cust.driver==1)
	{
		drent = rdays*driver_rent; 
	}
	bill = bill + drent;
	
    bill=bill+damage+(pdays*2000)+1000*rdays;
    if(bill>100000 && Discount==1)
    {
    	Discount=50;
	}
	else if(bill>50000 && bill <=100000 && Discount==1)
	{
		Discount=25;
	}
	else if(bill>25000 && bill<=50000 && Discount==1)
	{
		Discount=15;
	}
	else if(bill<25000 && bill>0 && Discount==1)
	{
		Discount=10;
	}
	else
	Discount=0;
    
    cout<<" ---- Generating bill ! ---- "<<endl;
    
    system("cls");
    
    cout<<"############### FAST CAR RENTAL MANAGEMENT SYSTEM ############### "<<endl;
    cout<<"\n\n";
    
    cout<<"------------------------------------------------------------------"<<endl;
    cout<<"\n\n";
    
    cout<<"\t\t\t\t~~ Bill Receipt ~~\t\t\t "<<endl;
    
    cout<<"\n\n";
    
    cout<<"\t\t\t~~ Client Details ~~\t\t\t"<<endl;
    
    cout<<" Name :  "<<cust.name<<endl;
    cout<<" Last 5 NIC digits : "<<cust.cnic<<endl;
    cout<<"\n\n";
    
    cout<<"\t\t\t~~ Car Details ~~\t\t\t"<<endl;
    cout<<"\n\n";
    
    cout<<" Car Name : "<<cust.car_name<<endl;
    cout<<" Rent per day : "<<cust.rent<<endl;
    cout<<" No of Days Car rented for : "<<cust.days<<endl;
    cout<<" No of Days car returned in : "<<rdays<<endl;
    if(cust.pick==false)
    cout<<"Car Pickup location : Garage "<<endl;
    else
    cout<<"Car Dropped at home "<<endl;
    if(cust.driver==true)
    cout<<"Driver : YES "<<endl;
    else
    cout<<" Driver : NO "<<endl;
    
    cout<<"\n\n";
    
    cout<<"\t\t\t~~ Amount Details ~~\t\t\t"<<endl;
    cout<<"\n";
    
    cout<<"Car Over Days Penalty : "<<(pdays*2000)<<endl;
    cout<<"Driver Rent : "<<drent;
    cout<<"Car Demage Penalty : "<<damage<<endl;
    cout<<"Car Rent : "<<x<<endl;
    
   
    cout<<" Total Bill Generated : "<<bill<<endl;
    
     if(Discount!=0)
     {
	
    cout<<"Congratulations ! You have earned "<<Discount<<" Percent Discount "<<endl;
    if(Discount==10)
    bill=bill*0.1;
    if(Discount==50)
    bill=bill*0.5;
    if(bill==25)
    bill=bill*0.25;
    if(bill==15)
    bill=bill*0.15;

    cout<<" Total Bill Generated after Discount  : "<<bill<<endl;
    
    
    
     }
    
    
     
}

void view_customers()
{
	Customer temp;
	int a;
	string n;
	int id;
	string car_n;
	float r;
	int d;
	bool dr;
	bool p;
	fstream obj;
	obj.open("customer.txt",ios::binary|ios::in);
	if(!obj)
	    cout<<"File can't be open "<<endl;
	else
	{
		
        cout<<" File opened succesfully "<<endl;
	    obj.read((char*)&temp,sizeof(Customer));
		while(!obj.eof())
	    {
	      	obj.read((char*)&temp,sizeof(Customer));
	      	cout<<"NIC: "<<temp.cnic<<endl;
	      	cout<<"Name: "<<temp.name<<endl;
	      	cout<<"\nCar_id: "<<temp.carid<<endl;
	      	cout<<"\nCar_name: "<<temp.car_name<<"\n\n\n\n\n";
	      	r=temp.rent;
	      	dr=temp.driver;
	      	p=temp.pick;
	      	d = temp.days;
	        }
	        obj.close();
		}
}		    
   
//______________________________________________________________________________________________________________________//
void admin_portal()
{
	cout<<"\n\n\n\n\n\t\t\tWELCOME TO ADMIN PORTAL\n\n\n\n\n\n";
	BST obj;
	move_to_BST(&obj);
	obj.display();
	int choice;
	for(int i=0;i<100;i++)
	{
		cout<<"\n\n\n\n\nPress 1 to view the car details\n";
		cout<<"Press 2 to add the car \n";
		cout<<"Press 3 to remove the car\n";
		cout<<"Press 4 to modify the car details\n";
		cout<<"Press 5 to view rented cars and customers\n";
		cout<<"Press 6 to change the driver rent\n";
		cout<<"Press -1 to exit the admin portal\n";
		cout<<"Choice: ";
		cin>>choice;
		switch(choice)
		{
			case 1:
				obj.display();
				break;
			case 2:
				add_car();
				move_to_BST(&obj);
				break;
			case 3:
				int n;
				obj.display();
				cout<<"Enter car id to delete: ";
				cin>>n;
				obj.del_car(n);
				obj.display();
				obj.move_cars_to_file();
				move_to_BST(&obj);
				cout<<"\n\n\n";
				obj.display();
				break;
			case 4:
				modify_car(obj);
				move_to_BST(&obj);
				obj.display();
				break;
			case 5:
				view_customers();
				break;
			case 6:
				cout<<"Enter new rent per day of driver: ";
				cin>>driver_rent;
				break;
			default:
				cout<<"Invalid choice!\n\n";
				break;								
		}
	}
}	

move_to_CLL(CLL *ll)
{
	Customer temp;
	int a;
	string n;
	int id;
	string car_n;
	float r;
	int d;
	bool dr;
	bool p;
	fstream obj;
	obj.open("customer.txt",ios::binary|ios::in);
	if(!obj)
	    cout<<"File can't be open "<<endl;
	else
	{
		cout<<endl;
	    obj.read((char*)&temp,sizeof(Customer));
		while(!obj.eof())
	    {
	      	obj.read((char*)&temp,sizeof(Customer));
	      	a=temp.cnic;
	      	n=temp.name;
	      	id=temp.carid;
	      	car_n=temp.car_name;
	      	r=temp.rent;
	      	dr=temp.driver;
	      	p=temp.pick;
	      	d = temp.days;
	      	
	      	Customer temp1(a,n,id,car_n,r,d,dr,p);
	      	ll->insert(temp1);
	        }
	        obj.close();
		}
}

bool check_int(string s, int &num)
{
	int flag = 0;
	stringstream ss; 
    ss << s;
    ss >> num;
  
	for(int i=0;i<s.length();i++)
	{
		if(s[i]<'0' || s[i]>'9')
		{
			flag++ ;
		}
	}
	
	if(flag == 0){
		return true;
	}
	else{
		return false;
	}
}
int main()
{
	ch:
	string s;
	int n;
	cout<<"\n\n\n\n\t\t\tWELCOME TO FAST CAR RENTAL SYSTEM\n\n";
	cout<<"Enter last five digits of your nic number: ";
	cin>>s;
	if(s == "admin")
	{
		admin_portal();
		goto abc;
	}
	else
	{
		if(!check_int(s,n))
			goto ch;
		if(n>99999 || n<10000)
		{
			cout<<"Invalid!\n";
			goto ch;
		 } 
		CLL ll;
		move_to_CLL(&ll);
		Customer temp = ll.search(n);
		Customer temp1;
		if(temp.compare(temp1))
		{
			new_customer(n);
			goto abc;
		}
		else
		{
			
			pending_customer(temp);
			goto abc;
		}
	}
	
	abc:
	cout<<"\n\n\n\n\n\t\t\tThanks for using our servives";	
}
