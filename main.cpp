#include <iostream>
#include<vector> //datastrucure
#include<string> //datatype
#include<algorithm>
#include<fstream>

using namespace std;

//user define datatype
struct Passwords{
    string username;
    string application;
    vector<unsigned char>password;

};


void  Add_password(vector<Passwords>& newpass ){



    Passwords object;
    cout<<"Please Enter the Application : "<<endl;
    cin>>object.application;
    cout<<"Please Enter your username : "<<endl;
    cin>>object.username;
    cout<<"Please Enter your password : "<<endl;
    string pass;
    cin>>pass;
    object.password= vector<unsigned char> (pass.begin(),pass.end());
    newpass.push_back(object);

}

void deletpass(vector<Passwords>& newpass, const string& file_pass, const string& application, const string& username) {
    auto d = find_if(newpass.begin(), newpass.end(), [&](const Passwords& object)
    {
        return object.application == application && object.username == username;
    });

    if (d != newpass.end()) {
        newpass.erase(d);
        ofstream file(file_pass, ios::trunc); // Open file in trunc mode to clear its content
        if (!file.is_open()) {
            cout << "error: can't open this file for writing" << endl;
            return;
        }
        for (const auto& object : newpass) {
            file << object.application << "  ,  " << object.username << "  ,  ";
            for (unsigned char f : object.password) {
                file << f;
            }
            file << endl;
        }
        cout << "your password deleted successfully " << endl;
    } else {
        cout << "this password is invalid " << endl;
    }
}


void changpass(vector<Passwords>& newpass , const string& application){
    auto findd=find_if (newpass.begin(),newpass.end(),[&application](const Passwords& object )
                    {
                        return object.application== application;
                    });
            if(findd != newpass.end()){
                 string chang_pass;
                 cout<<"Enter new password : "<<endl;
                 cin>>chang_pass;
                 findd->password = vector<unsigned char>(chang_pass.begin(),chang_pass.end());
                 cout<<"password  changed successfully "<<endl;


            }
            else {
                cout<<"this password not found "<<endl;
            }



}

void displaypass(const vector<Passwords>& newpass){
    if(newpass.empty()){
        cout<<endl<<"passwords not found! "<<endl;
        return ;
    }
    else{
        cout<<endl<<"This is your stored passwords : \n "<<endl;
        for(const auto&  object: newpass)
        {
            cout<<"application : "<<object.application<<" , username : "<<object.username<<" , password : ";
        for(const auto& c: object.password){
            cout<<c;
        }
        cout<<endl<<"-----------------"<<endl;
        }
    }




}

void retrievepass(const vector<Passwords>& newpass){
    string application;
    cout<<"Please Enter your Application : ";
    cin>>application;
    string username;
    cout<<"Please Enter your username : ";
    cin>>username;
    auto findd=find_if (newpass.begin(),newpass.end(),[&application,&username](const Passwords& object )
                    {
                        return object.application== application&&object.username == username;

                    });
        if(findd != newpass.end()){
            cout<<endl<<"your password for application "<<application<<" and username "<<username<<"\n is : ";
            for(unsigned char s: findd->password){
                cout<<s;
            }
            cout<<endl<<"-----------------------";

        }else{

            cout<<"sorry this password not found for this website and username "<<endl;



        }



}

void save_data(const vector<Passwords>& newpass , const string& file_pass) {
    ofstream file(file_pass, ios::trunc); // Open file in trunc mode to clear its content
    if (!file.is_open()) {
        cout << "error: can't open this file for writing " << endl;
        return;
    }
    for (const auto& object : newpass) {
        file << object.application << "  ,  " << object.username << "  ,  ";
        for (unsigned char f : object.password) {
            file << f;
        }
        file << endl;
    }
    cout << "password saved in file " << file_pass << endl;
}

vector<Passwords> read_from_file(const string& file_pass){
    vector<Passwords> newpass;
    ifstream file(file_pass);
    if (!file.is_open()) {
        cout << "error: can't open this file for reading " << endl;
        return newpass;
    }
    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find(",");
        if (pos1 == string::npos) {
            cout << "error: invalid format" << endl;
            continue;
        }
        string application = line.substr(0, pos1);
        size_t pos2 = line.find(",", pos1 + 1);
        if (pos2 == string::npos) {
            cout << "error: invalid format" << endl;
            continue;
        }
        string username = line.substr(pos1 + 1, pos2 - pos1 - 1);
        vector<unsigned char> Password;
        for (size_t i = pos2 + 1; i < line.size(); ++i) {
            Password.push_back(line[i]);
        }
        newpass.push_back({username, application, Password});
    }
    cout << "data loaded from file: " << file_pass << endl;
    return newpass;
}

int main()
{
    vector<Passwords> newpass;
    newpass=read_from_file("saved_info");

    //while loop
    while (true){
        cout<<"\nPassword   App ->>>\n\n";
        cout<<"-------------------------------"<<endl;
        cout<<"1. Add Password "<<endl;
        cout<<"2. delete Password \n";
        cout<<"3. save password \n";
        cout<<"4. Display all passwords "<<endl;
        cout<<"5. retrieve your password "<<endl;
        cout<<"6. Exit \n ";
        cout<<"Enter your choice :    \n";


        int choice;
        cin>>choice;
        if(cin.fail()){
            cout<<"invalid choice ! please enter a valid choice "<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }


        switch(choice){
    case 1:
        Add_password(newpass);
        break;
   case 2:
{
    string application, username;
    cout<<"Enter your application : ";
    cin>>application;
    cout<<"Enter your username : ";
    cin>>username;
    deletpass(newpass, "saved_info", application, username);
         break;
}

    case 3:
        {
            save_data(newpass,"saved_info");
            break;
        }
    case 4:
            displaypass(newpass);
            break;

    case 5:
            retrievepass(newpass);
            break;



    case 6:
        cout<<"Exiting your application ..... "<<endl;
        return 0;

    default:
        cout<<"invalid choices !!!! please try again "<<endl;

        }
    }







    return 0;
}
