#include <iostream>
#include <stdlib.h>
#include<time.h>
#include <windows.h>
#include <stdlib.h>
#include <mysql.h>
#include <iomanip>
#include <string>
#include <conio.h>

using namespace std;
string usname;
bool res,valid,conct;
int choice;
string querry="";
string no="";
string name="";
static bool qrTy;
int i = 0;
char cont;
char pass[10];

//Sock
MYSQL *sock;

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

bool login(string us, string ps)
{
    if(us.empty()||ps.empty()) {
        res = false;
    } else if(us == "Namrata" && ps =="Namrata") {
        res = true;
    }
    return res;
}

bool conn()
{
    //connection params
    char *host ="localhost";
    char *user="root";
    char *pass="root";
    char *db="phonebookdir";
    //Sock
    //MYSQL *sock;
    sock =mysql_init(0);

    if(sock) {
        cout<<"\t\tSock handle ok"<<endl;
    }
    else {
        cout<<"\t\tFailed"<<mysql_error(sock)<<endl;
    }
    //connection
    if(mysql_real_connect(sock , host, user, pass, db,0,NULL,0)) {
        conct = true;
        cout<<"\t\tSuccessfull"<<endl;
    }
    else {
        conct = false;
        cout<<"\t\tFailed!!!!!"<<mysql_error(sock)<<endl;
    }
    return conct;
}

void querryRun(string query)
{
    const char* q = query.c_str();
    cout<<"\t\tQuery is: "<<q<<endl;
    char qstate = mysql_query(sock,q);

    if(!qstate) {
        cout<<"\t\tSuccess..."<<endl;
        cout<<"\t\t------------------------------------------------------"<<endl;
    }
    else {
        cout<<"\t\tQuery problem: "<<mysql_error(sock)<<endl;
    }

    if(qrTy == false) {
        qstate = mysql_query(sock,"select * from phonebook");
    }
    if(!qstate) {
        cout<<endl;
        MYSQL_RES* res = mysql_store_result(sock);
        MYSQL_ROW row;
        int totalrows = mysql_num_rows(res);
        int numfields = mysql_num_fields(res);
        MYSQL_FIELD *mfield;
        cout<<"\t\t";
        cout<<left <<setw(20)<<"Name"<<"\t\t\t"<<left <<setw(20)<<"Phone No"<<endl<<"\t\t";
        cout<<"-------------------------------------------------------"<<endl;
        while((row = mysql_fetch_row(res)))
        {
            char *val = row[0];
            char *val1 = row[1];
            cout<<"\t\t"<<left <<setw(20)<<val<<"\t\t\t"<<left<<setw(20)<<val1<<endl;
        }
        cout<<endl<<endl;
    }

    else {
        cout<<"\t\tquery error: "<<mysql_error(sock)<<endl;
    }
}

int main()
{
    cout <<endl<<endl;
    cout <<"\t\t\tLogin  " << endl <<endl;
    cout <<"\t\tUser Name : ";
    cin >>usname;
    cout <<endl<<"\t\tPassword : ";

    for(int i=0; i<7; i++) {
        pass[i]=getch();
        cout<<"*";

        if(pass[i]=='\r') //check if enter key is pressed
            break;

        else if(pass[i]=='\b') {

            if(i==0)
                cout<<"\b"<<" "<<"\b";
            else if(i>=1) {
                pass[i-1]='\0';//make the previous byte null if backspase is pressed
                i=i-2;
                cout<<"\b"<<" "<<"\b\b"<<" "<<"\b";
            }

        }
    }

    //cin >>pass;
    cout<<endl<<endl;
    valid = login(usname,pass);
    bool chk = conn();

    if(valid == false) {
        cout<<endl<<endl<<"\t\tWrong username or password!!"<<endl;
        goto out;
    }
    else if(chk == true) {
        while(1) {
rep :
            system("cls");

            cout<<endl<<endl<<"\t\t\tWelcome to phone book directory "<<endl<<endl;
            cout<<"\n\t\t*****Phone Book*****";
            cout<<"\n\t\t1) Add New Record\n";
            cout<<"\t\t2) Display All Records\n";
            cout<<"\t\t3) Search Telephone No.\n";
            cout<<"\t\t4) Search Person Name.\n";
            cout<<"\t\t5) Update Telephone No.\n";
            cout<<"\t\t6) Delete Telephone No.\n";
            cout<<"\t\t7) Exit\n";
            cout<<"\n\t\tChoose your choice : ";
            cin>>choice;

            cout<<endl;
            switch(choice) {
            case 1 : //New Record
                qrTy = false;
                cout <<"\t\tEnter Name : ";
                cin >> name;
                cout <<"\t\tEnter Number : ";
                cin >> no;
                querry = "insert into phonebook(Name,Phone_No) values('"+name+"','"+no+"')";
                querryRun(querry);
                cout<<"\t\tPress Any AlphaNumeric Key to continue : ";
                cin>>cont;
                if(cont == '\r') {
                    goto rep;
                }
                else {
                    goto rep ;
                }
                break;
            case 2 : //Display Record
                qrTy = true;
                querry = "select * from phonebook";
                querryRun(querry);
                cout<<"\t\tPress Any AlphaNumeric Key to continue : ";
                cin>>cont;
                if(cont == '\r') {
                    break;
                }
                else {
                    break;
                }
                break;
            case 3 : //Search by Name in Record
                qrTy = true;
                cout<<"\t\tEnter Name : ";
                cin>>name;
                querry = "select * from phonebook where Name='"+name+"'";
                querryRun(querry);
                cout<<"\t\tPress Any AlphaNumeric Key to continue : ";
                cin>>cont;
                if(cont == '\r') {
                    goto rep;
                }
                else {
                    goto rep ;
                }
                break;
            case 4 : //Search by No in Recordr
                qrTy = true;
                cout<<"\t\tEnter Number : ";
                cin>>no;
                querry = "select * from phonebook where Phone_No='"+no+"'";
                querryRun(querry);
                cout<<"\t\tPress Any AlphaNumeric Key to continue : ";
                cin>>cont;
                if(cont == '\r') {
                    goto rep;
                }
                else {
                    goto rep ;
                }
                break;
            case 5 : //Update in Record
                qrTy = false;
                cout<<endl<<"\t\tEnter Name : ";
                cin>>name;
                cout<<"\n\t\tEnter Number : ";
                cin>>no;
                querry = "update phonebook set Phone_No='"+no+"'where Name ='"+name+"'";
                querryRun(querry);
                cout<<"\t\tPress Any AlphaNumeric Key to continue : ";
                cin>>cont;
                if(cont == '\r') {
                    goto rep;
                }
                else {
                    goto rep ;
                }
                break;
            case 6: //Delete from Record
                qrTy = false;
                cout<<endl<<"\t\tEnter Name : ";
                cin>>name;
                querry="delete from phonebook where Name = '"+name+"'";
                querryRun(querry);
                cout<<"\t\tPress Any AlphaNumeric Key to continue : ";
                cin>>cont;
                if(cont == '\r') {
                    goto rep;
                }
                else {
                    goto rep ;
                }
                break;
            case 7: //Exit
                system("cls");
                cout<<"\n\n\t\t\tThank You \n\t\t\tExit"<<endl<<endl;
                goto out;
                break;
            }
        }
    }
out:
    return 0;
}
