#include<bits/stdc++.h>
#include <iostream>
using namespace std;

//class Medicines


class Medicines {

    public:
    string name;
    int cost;
    int quantity;

    Medicines(string name, int cost, int quantity) 
    {
        this->name = name;
        this->cost = cost;
        this->quantity = quantity;
    }

    int getCost() 
    {
        return cost;
    }

    virtual void display(){
       cout<<"Name: "<<this->name<<"\n";
       cout<<"Cost: "<<this->cost<<"\n";
       cout<<"Quantity: "<<this->quantity<<"\n";
    }
    friend class Stock;
};



// class Stock

// Search
// Add
// Update Cost
// Update Quantity
// Delete
// Display

class Stock 
{
    public:
    static vector<Medicines> stock; 
    
    int get_quantity(string currname){
        int i, quantity = 0;
        bool exist = false;
        int len = stock.size();
        for(i=0; i<len; i++)
        {
            if(stock[i].name.compare(currname)==0)
            {
                quantity = stock[i].quantity;
                exist = true;
            }
        }
        if(exist == false){
            cout<<"Not in Stock"<<endl;
            return -1;
        }
        else
        {
            return quantity;
        }
    }


    int get_cost(string name){
        int i, cost = 0;
        bool exist = false;
        int len = stock.size();
        for(i=0; i<len; i++)
        {
            if(stock[i].name.compare(name)==0){
                cost = stock[i].cost;
                exist = true;
            }
        }
        if(exist == false){
            cout<<"Not in Stock"<<endl;
            return -1;
        }
        else
        {
            return cost;
        }
    }


     Medicines search_medicine(string name) {
         for (Medicines medicine : stock) {
             if (medicine.name.compare(name)==0) 
             {
                 return medicine;
             }
         }
         Medicines obj("X",0,0);
         return obj;
     }

    void up_quantity(Medicines &up)
    {
        cout<<"Enter new quantity"<<endl;
        int newQuan;
        cin>>newQuan;
        up.quantity = up.quantity + newQuan;
        cout<<"New Quantity = " << up.quantity;
    }

    void up_cost(Medicines &up)
    {
        cout<<"Enter new cost";
        int newCost;
        cin>>newCost;
        up.cost = newCost;
       cout<<"New Cost = " << up.cost<<endl;
    }



    void update(string name)
    {
        Medicines up = search_medicine(name);
        if(up.name=="X")
        { 
          cout<<"No such medicine present in the inventory"<<endl;
          return;
        }
        up.Medicines::display();
        cout<<"What do you want to update:"<<endl;
        cout<<"1. Quantity"<<endl;
        cout<<"2. Cost"<<endl;
        cout<<"3. Both"<<endl;
        int choice;
        cin>>choice;
        switch(choice){
            case 1:
                up_quantity(up);
                break;
            case 2:
                up_cost(up);
                break;
            case 3:
                up_quantity(up);
                up_cost(up);
                break;
            default:
                cout<<"Invalid Input";
        }
    }

    void new_medicine(string name, int cost, int quantity){
        Medicines obj(name, cost, quantity);
        stock.push_back(obj);
    }

    void del_medicine(string name)
    {
        // Medicines m = search_medicine(name);
        auto it=stock.begin();
        for(;it!=stock.end();it++)
        {
          if(it->name==name)
          {
            break;
          }
        }
        stock.erase(it);
    }

    void display()
    {
        cout<<"Select Option: "<<endl;
        cout<<"1. Entire Stock"<<endl;
        cout<<"2. Specific Stock Item"<<endl;
        int choice;
        string name;
        cin>>choice;
        switch(choice){
            case 1:
                   for(int i=0;i<stock.size();i++)
                   {
                     stock[i].display();
                   }
                   break;
            case 2: {
                   cout<<"Enter name:"<<endl;
                   cin>>name;
                   Medicines obj=search_medicine(name);
                   obj.Medicines::display();
                   break;
            }
            default:
                cout<<"Invalid Command";
        }
    }

};

vector<Medicines> Stock::stock={};

// class Cusotomer;

class Customer: public Stock 
{

    public:
    string name;
    string password;
    static vector<Medicines> cmed;

    Customer(string name, string password) 
    {
        this->name = name;
        this->password = password;
    }

    void add_medicine(string name, int cost, int quantity)
    {
        cmed.push_back(Medicines(name, cost , quantity));
    }

    
    Medicines search_medicine(string name)
    {
        for(Medicines medicines: cmed){
            if(medicines.name.compare(name)==0){
                return medicines;
            }
        }
        return Medicines("X",0,0);
    }

    void rem_medicine(string name){
        Medicines m=search_medicine(name);
        auto it=cmed.begin();
        for(;it!=cmed.end();it++)
        {
          if(it->name==name)
          {
            break;
          }
        }
        cmed.erase(it);
    }

    void check_out(int total, Customer customer)
    {
        for(int i=0; i<customer.cmed.size(); i++){
            for(int j=0; j<stock.size(); j++){
                if(customer.cmed[i].name.compare(stock[j].name)==0)
                {
                    stock[j].quantity = stock[j].quantity - cmed[i].quantity;
                }
            }
        }
        cout<<"Stock Updated."<<endl;
    }


    void dis(Customer customer)
    {
        cout<<"Medicines: ";
        for(int i=0;i<cmed.size();i++)
        {
          cmed[i].display();
        }
        int total = 0;
        for(int i =0; i<cmed.size(); i++){
            total = total + cmed[i].cost;
        }
        cout<<"Total Cost Of Medicines: " << total<<endl;
        cout<<"Do you want to check out?\n1.Yes\n2.No"<<endl;
        int c;
        cin>>c;
        if(c == 1){
            check_out(total, customer);
        }
        else{
            return;
        }
    }

};

vector<Medicines> Customer::cmed={};


// class Chandle;

class Chandle: public Stock{

    public:
    static vector<Customer> customer ;

    void new_customer(string name, string password)
    {
        customer.push_back(Customer(name, password));
    }

    Customer search_customer(string name)
    {
        for(Customer customer: customer){
            if(customer.name.compare(name)==0){
                return customer;
            }
        }
        return Customer("X","X");
    }

    bool val_pass(string name, string password)
    {
      Customer obj= search_customer(name);
      if(obj.name=="X")
      {
        cout<<"This customer name doesn't exit ";
        return false;
      }
        if(obj.password.compare(password)==0)
        {
            cerr<<"Returned true";
            return true;
        }
        else
            return false;
    }
    

    void edit_customer(string name, string password)
    {
        if(val_pass(name, password))
        {
            int n = 0;
            while(n<3){
                Customer m = search_customer(name);
                cout<<"Enter Your Option:"<<endl;
                cout<<"1. Add Medicine"<<endl;
                cout<<"2. Remove Medicine"<<endl;
                cout<<"3. Exit"<<endl;
                cin>>n;
                if(n == 3){
                    cout<<"Exiting.."<<endl;
                }
                string medName;
                switch(n){
                    case 1:
                        {cout<<"Enter name of the medicine: "<<endl;
                        cin>>medName;
                        Medicines obj=search_medicine(medName);
                        if(obj.name=="X")
                        {
                          cout<<"This medicine doesnt exist in the inventory";
                          break;
                        }
                        cout<<"Enter Quantity"<<endl;
                        int j;
                        cin>>j;
                        if(j>get_quantity(medName)){
                            cout<<"Insufficient Quantity"<<endl;
                        }
                        m.add_medicine(medName, get_cost(medName)*j, j);
                        break;
                        }
                    case 2:
                        cout<<"Enter the name of the medicine:"<<endl;
                        cin>>medName;
                        m.rem_medicine(medName);
                        break;
                    default:
                        cout<<"Exiting"<<endl;
                }

            }
        }
        else {
             cout<<"Invalid Username or Password."<<endl;
        }
    }

    void dis_customer(string name)
    {
        Customer obj = search_customer(name);
        cout<<"Enter Password: "<<endl;
        string pass ;
        cin>>pass;
        if(obj.password.compare(pass)==0){
            obj.dis(obj);
        }
        else{
            cout<<"Invalid Password."<<endl;
        }

    }

};

vector<Customer> Chandle:: customer ={};

int main() {

        Stock s;
        Chandle c;

        int choice = 0;
        while(choice <= 7){
            cout<<">>>>>>> MENU <<<<<<<<"<<endl;
            cout<<"1. Add new medicine to the stock."<<endl;
            cout<<"2. Delete medicine from stock."<<endl;
            cout<<"3. Update Cost/Quantity of medicine in stock."<<endl;
            cout<<"4. Display Stock"<<endl;
            cout<<"5. New Customer"<<endl;
            cout<<"6. Edit Medicines (Customer)"<<endl;
            cout<<"7. Display Medicines (Customer)"<<endl;
            cout<<"8. Exit"<<endl;
            cin>>choice;
            string medName;
            string p;
            int costMed;
            int quan;
            switch(choice){
                case 1:
                    cout<<"Enter Name of Medicine: "<<endl;
                    cin>>medName;
                    cout<<"Enter Cost of the Medicine:"<<endl;
                    cin>>costMed;
                    cout<<"Enter Quantity"<<endl;
                    cin>>quan;
                    s.new_medicine(medName, costMed, quan);
                    break;
                case 2:
                    cout<<"Enter the name of the medicine:"<<endl;
                    cin>>medName;
                    s.del_medicine(medName);
                    break;
                case 3:
                    cout<<"Enter the name of the medicine:"<<endl;
                    cin>>medName;
                    s.update(medName);
                    break;
                case 4:
                    s.display();
                    break;
                case 5:
                    cout<<"Enter your name:"<<endl;
                    cin>>medName;
                    cout<<"Enter Password: "<<endl;
                    cin>>p;
                    c.new_customer(medName, p);
                    break;
                case 6:
                    cout<<"Enter your name:"<<endl;
                    cin>>medName;
                    cout<<"Enter Password: "<<endl;
                     cin>>p;
                    c.edit_customer(medName, p);
                    break;
                case 7:
                     cout<<"Enter your name:"<<endl;
                     cin>>medName;
                     c.dis_customer(medName);
                    break;
                default:
                    cout<<"Invalid"<<endl;
            }
        }

}