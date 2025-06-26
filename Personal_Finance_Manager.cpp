#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class User;

class Taxes {

private:

    static float totalincometax;
    static float totalsalestax;

protected:
    float currenttax;

public:

    virtual void calculate_tax(float) = 0;

    friend void save_data(User);
    friend void load_data(User &);
    
    void update_sales_tax(float price) { totalsalestax += price; }
    
    void update_income_tax(float price) { totalincometax += price; }

    float get_currenttax() { return currenttax; }

    static float get_totalincometax() { return totalincometax; }

    static float get_totalsalestax() { return totalsalestax; }
};
float Taxes::totalincometax = 0.0;
float Taxes::totalsalestax = 0.0;

class SalesTax : public Taxes {
public:


    void calculate_tax(float price) { // calculate sales tax at 17% gst...

        currenttax = price * 0.17;
        update_sales_tax(currenttax);

    }
};

class IncomeTax : public Taxes {
public:

    void calculate_tax(float value) { // different income tax according to FBR...
        if(value <= 10000) {
            return;
        } else if (value > 10000 && value <= 20000) {
            currenttax = 0.025 * value;
            update_income_tax(currenttax);
        } else if (value > 20000 && value <= 40000) {
            currenttax = 0.125 * value;
            update_income_tax(currenttax);
        } else if (value > 40000 && value <= 60000) {
            currenttax = 0.15 * value;
            update_income_tax(currenttax);
        } else {
            currenttax = 0.2 * value;
            update_income_tax(currenttax);
        }
    }
};

class Transaction {

    private:
    string date;
    string month;
    string year;
    int transaction_ID;
    float transaction_amount;
    
    protected:
    string transaction_type;
    Taxes *tax;

    public:
    friend void save_data(User);
    friend void load_data(User &);

    Transaction(float amount, string date, string month, string year) {

        this->date = date;
        this->month = month;
        this->year = year;

        static int ID = 1;

        this->transaction_ID = ID;

        ID++;

        this->transaction_amount = amount;

    }

    //virtual function for to show all types of transactions and display all their information.
    virtual void show_transacton() = 0;

    //virtual function to get transaction source.
    virtual string get_source() = 0;

    //get transaction date.
    string get_date() {

        return this->date;

    }

    //get transaction time.
    string get_month() {

        return this->month;

    }

    //get transaction year.
    string get_year() {

        return this->year;

    }

    //get transaction ID.
    int get_transaction_ID() {

        return this->transaction_ID;

    }

    //get transaction type
    string get_type() {

        return this->transaction_type;

    }

    //get transaction amount.
    int get_amount() {

        return this->transaction_amount;

    }

    //get tax amount.
    float get_Tax_Amount() {

        return tax->get_currenttax();

    }

};

class Income: public Transaction {

    private:
    string income_source;

    public:
    Income(string source, float amount, string date, string month, string year): Transaction(amount, date, month, year) {

        this->income_source = source;
        this->transaction_type = "income";
        tax = new IncomeTax();
        tax->calculate_tax(amount);

    }

    //definition for Income transaction show function.
    void show_transacton() {

        cout << "transaction ID: " << Transaction::get_transaction_ID() << endl;
        cout << "date/month/year: " << Transaction::get_date() << " - " << Transaction::get_month() << " - " << Transaction::get_year() << endl;
        cout << "transaction type: " << Transaction::get_type() << endl;
        cout << "source: " << Income::income_source << endl;
        cout << "amount: " << Transaction::get_amount() << endl;
        cout << "Income Tax for this Transaction: " << tax->get_currenttax() << endl << endl;

    }

    //definition for get source virtual function.
    string get_source() {

        return this->income_source;

    }

};

class Expense: public Transaction {

    private:
    string expense_source;

    public:
    Expense(string source, float amount, string date, string month, string year): Transaction(amount, date, month, year) {

        this->expense_source = source;
        this->transaction_type = "expense";
        tax = new SalesTax();
        tax->calculate_tax(amount);

    }

    //definition for expense transaction show function.
    void show_transacton() {

        cout << "transaction ID: " << Transaction::get_transaction_ID() << endl;
        cout << "date/month/year: " << Transaction::get_date() << " - " << Transaction::get_month() << " - " << Transaction::get_year() << endl;
        cout << "transaction type: " << Transaction::get_type() << endl;
        cout << "source: " << Expense::expense_source << endl;
        cout << "amount: " << Transaction::get_amount() << endl;
        cout << "Sales Tax for this Transaction: " << tax->get_currenttax() << endl << endl;

    }

    //definition for get source virtual function.
    string get_source() {

        return this->expense_source;

    }

};

class Report {
private:
    int report_id;

public:
    Report() {

        srand(time(NULL));

        this->report_id = rand() % 200;

    }

    void show() {

        this->report_id = rand() % 200;
        cout << "Report ID : " << report_id << endl;
    }

    friend void save_data(User);
    friend void load_data(User &);

    void generate_report(vector<Transaction*> ptr) {

        string date_choice = "A"; //want to see dates or not.
        string transaction_id_choice = "A"; //want to see transaction ID's or not.
        string transaction_type = "A"; //want to see transaction types or not.
        string filter_amount_choice = "A"; //want filter on amount or not.
        string choice_amount = "A"; //want to see amount or not.
        string type_choice = "A"; //selector of transaction types.
        string filter_type = "A"; //want to apply filter on transaction types or not.
        float lower_amount = 0.0;
        float upper_amount = 0.0;
        string report = "A"; //select if you want to generate report.
        string report_name = "";
        string tax_choice = "A";//want to view tax information.

        cout << "Would you like to view the Date of the Transactions? [Y/N]";
        cin >> date_choice;

        cout << "Would you like to view the Transaction IDs of the Transactions? [Y/N]";
        cin >> transaction_id_choice;

        cout << "Would you like to view the Type of the Transactions? [Y/N]";
        cin >> transaction_type;

        if(transaction_type == "Y" || transaction_type == "y") {
            
            cout << "Would you like to add a filter on the type of the Transactions? [Y/N]";
            cin >> filter_type;

            if(filter_type == "Y" || filter_type == "y") {

                cout << "Kindly enter 'I' for income transactions or 'E' for expense transactions or 'B' for Both";
                cin >> type_choice;

                //standardizing the choices so that loop conditions work.
                if(type_choice == "i") {

                    type_choice  = "I";

                }else if(type_choice == "e") {

                    type_choice = "E";

                }else if(type_choice == "b") {

                    type_choice = "B";

                }

            }else {

                type_choice = "B"; //assigning type choice "B" so that by default all types of transaction prints.
            }
        }
        

        cout << "Would you like to view the Transaction Amount? [Y/N]";
        cin >> choice_amount;

        if(choice_amount == "Y" || choice_amount == "y") {

            cout << "Would you like to add a filter to your Transaction Amount [Y/N]";
            cin >> filter_amount_choice;

            if(filter_amount_choice == "Y" || filter_amount_choice == "y") {

                cout << "Enter the lower range of the Transaction Amount?";
                cin >> lower_amount;
                cout << "Enter the higher range of the Transaction Amount?";
                cin >> upper_amount;

                if(lower_amount < 0) {

                    cout << "Amount entered can not be negative...lower range amount has been set to 0" << endl;
                    lower_amount = 0.0;

                }

                if(upper_amount < 0) {
                    
                    cout << "Amount entered can not be negative...upper range amount has been set to 0" << endl;
                    upper_amount= 0.0;
                }
            }
        }

        cout << "Would you like to view Taxations? [Y/N]";
        cin >> tax_choice;

        system("cls");


        show();
        if(type_choice != "B") {

            for (int i = 0; i < ptr.size(); i++) {
                if(type_choice == "I" && ptr[i]->get_type() != "income") //loop skips if transaction is not income transaction.
                    continue;
                if(type_choice == "E" && ptr[i]->get_type() != "expense") //loop skips if transaction is not expense transaction.
                    continue;
                if(filter_amount_choice == "Y" || filter_amount_choice == "y") {

                    //loop skips if transaction amount not in filter range
                    if(ptr[i]->get_amount() < lower_amount || ptr[i]->get_amount() > upper_amount) {
                        continue;
                    }
                }

                //printing transaction ID if selected.
                if(transaction_id_choice == "Y" || transaction_id_choice == "y") {
                    cout << ptr[i]->get_transaction_ID() << "\t";
                }

                //printing dates if selected.
                if(date_choice == "Y" || date_choice == "y") {
                    cout << ptr[i]->get_date() << "-";
                    cout << ptr[i]->get_month() << "-";
                    cout << ptr[i]->get_year() << "\t";
                }

                //printing transaction types if selected.
                if(transaction_type == "Y" || transaction_type == "y") {

                    if(filter_type == "Y" || filter_type == "y") {

                        if (type_choice == "b" || type_choice == "B") {

                            cout << ptr[i]->get_type() << "\t";

                        }else if (type_choice == "I" || type_choice == "i") {

                            if(ptr[i]->get_type() == "income") { // important to check the same type of transactions are present in report...

                                cout << ptr[i]->get_type() << "\t";

                            }
                        } else if (type_choice == "E" || type_choice == "e") {

                            if(ptr[i]->get_type() == "expense") { // important to check the same type of transactions are present in report...
                    
                                cout << ptr[i]->get_type() << "\t";
                    
                            }   
                
                        } 
                    } else {
                        cout << ptr[i]->get_type() << "\t";
                    }
                }

                //printing amount if filter amount is not selected.
                if((choice_amount == "Y" || choice_amount == "y") && (filter_amount_choice != "Y" || filter_amount_choice != "y")) {
                    cout << ptr[i]->get_amount() << "\t";
                    
                    //printing tax information if selected. 
                    if(tax_choice == "Y" || tax_choice == "y") {
                        cout << ptr[i]->get_Tax_Amount() << "\t";
                    }

                    cout << endl;

                    continue;
                }

                //printing amount if filter amount is selected.
                if(filter_amount_choice == "Y" || filter_amount_choice == "y") {
                    if(ptr[i]->get_amount() >= lower_amount && ptr[i]->get_amount() <= upper_amount) {
                        cout << ptr[i]->get_amount() << "\t";
                    }
                }
                if(tax_choice == "Y" || tax_choice == "y") {
                    cout << ptr[i]->get_Tax_Amount() << "\t";
                }
                cout << endl;
            }

        }else {

            type_choice = "I";
            for (int i = 0; i < ptr.size(); i++) {
                if(type_choice == "I" && ptr[i]->get_type() != "income") //loop skips if transaction is not income transaction.
                    continue;
                if(filter_amount_choice == "Y" || filter_amount_choice == "y") {

                    //loop skips if transaction amount not in filter range
                    if(ptr[i]->get_amount() < lower_amount || ptr[i]->get_amount() > upper_amount) {
                        continue;
                    }
                }

                //printing transaction ID if selected.
                if(transaction_id_choice == "Y" || transaction_id_choice == "y") {
                    cout << ptr[i]->get_transaction_ID() << "\t";
                }

                //printing dates if selected.
                if(date_choice == "Y" || date_choice == "y") {
                    cout << ptr[i]->get_date() << "-";
                    cout << ptr[i]->get_month() << "-";
                    cout << ptr[i]->get_year() << "\t";
                }

                //printing transaction types if selected.
                if(transaction_type == "Y" || transaction_type == "y") {

                    if(filter_type == "Y" || filter_type == "y") {

                        if (type_choice == "b" || type_choice == "B") {

                            cout << ptr[i]->get_type() << "\t";

                        }else if (type_choice == "I" || type_choice == "i") {

                            if(ptr[i]->get_type() == "income") { // important to check the same type of transactions are present in report...

                                cout << ptr[i]->get_type() << "\t";

                            }
                        } else if (type_choice == "E" || type_choice == "e") {

                            if(ptr[i]->get_type() == "expense") { // important to check the same type of transactions are present in report...
                    
                                cout << ptr[i]->get_type() << "\t";
                    
                            }   
                
                        } 
                    } else {
                        cout << ptr[i]->get_type() << "\t";
                    }
                }

                //printing amount if filter amount is not selected.
                if((choice_amount == "Y" || choice_amount == "y") && (filter_amount_choice != "Y" || filter_amount_choice != "y")) {
                    cout << ptr[i]->get_amount() << "\t";

                    //printing tax information if selected. 
                    if(tax_choice == "Y" || tax_choice == "y") {
                        cout << ptr[i]->get_Tax_Amount() << "\t";
                    }

                    cout << endl;
                    continue;
                }

                //printing amount if filter amount is selected.
                if(filter_amount_choice == "Y" || filter_amount_choice == "y") {
                    if(ptr[i]->get_amount() >= lower_amount && ptr[i]->get_amount() <= upper_amount) {
                        cout << ptr[i]->get_amount() << "\t";
                    }
                }
                //printing tax information if selected. 
                if(tax_choice == "Y" || tax_choice == "y") {
                    cout << ptr[i]->get_Tax_Amount() << "\t";
                }

                cout << endl;
            }

            cout << endl;

            type_choice = "E";
            for (int i = 0; i < ptr.size(); i++) {
                if(type_choice == "E" && ptr[i]->get_type() != "expense") //loop skips if transaction is not expense transaction.
                    continue;
                if(filter_amount_choice == "Y" || filter_amount_choice == "y") {

                    //loop skips if transaction amount not in filter range
                    if(ptr[i]->get_amount() < lower_amount || ptr[i]->get_amount() > upper_amount) {
                        continue;
                    }
                }

                //printing transaction ID if selected.
                if(transaction_id_choice == "Y" || transaction_id_choice == "y") {
                    cout << ptr[i]->get_transaction_ID() << "\t";
                }

                //printing dates if selected.
                if(date_choice == "Y" || date_choice == "y") {
                    cout << ptr[i]->get_date() << "-";
                    cout << ptr[i]->get_month() << "-";
                    cout << ptr[i]->get_year() << "\t";
                }

                //printing transaction types if selected.
                if(transaction_type == "Y" || transaction_type == "y") {

                    if(filter_type == "Y" || filter_type == "y") {

                        if (type_choice == "b" || type_choice == "B") {

                            cout << ptr[i]->get_type() << "\t";

                        }else if (type_choice == "I" || type_choice == "i") {

                            if(ptr[i]->get_type() == "income") { // important to check the same type of transactions are present in report...

                                cout << ptr[i]->get_type() << "\t";

                            }
                        } else if (type_choice == "E" || type_choice == "e") {

                            if(ptr[i]->get_type() == "expense") { // important to check the same type of transactions are present in report...
                    
                                cout << ptr[i]->get_type() << "\t";
                    
                            }   
                
                        } 
                    } else {
                        cout << ptr[i]->get_type() << "\t";
                    }
                }

                //printing amount if filter amount is not selected.
                if((choice_amount == "Y" || choice_amount == "y") && (filter_amount_choice != "Y" || filter_amount_choice != "y")) {
                    cout << ptr[i]->get_amount() << "\t";

                    //printing tax information if selected. 
                    if(tax_choice == "Y" || tax_choice == "y") {
                        cout << ptr[i]->get_Tax_Amount() << "\t";
                    }

                    cout << endl;
                    continue;
                }

                //printing amount if filter amount is selected.
                if(filter_amount_choice == "Y" || filter_amount_choice == "y") {
                    if(ptr[i]->get_amount() >= lower_amount && ptr[i]->get_amount() <= upper_amount) {
                        cout << ptr[i]->get_amount() << "\t";
                    }
                }

                //printing tax information if selected. 
                if(tax_choice == "Y" || tax_choice == "y") {
                    cout << ptr[i]->get_Tax_Amount() << "\t";
                }
                cout << endl;
            }

            type_choice = "B";
        }

        cout << endl << "do you want to save report? [Y/N]: ";
        cin >> report;
        
        cout << endl;

        if(report == "Y" || report == "y") {

            cout << "Enter the name you want to save report as: ";
            fflush(stdin);
            getline(cin, report_name);
            report_name = report_name + ".txt";
            save_report(report_name, date_choice, transaction_id_choice, transaction_type, filter_amount_choice, choice_amount, type_choice, filter_type, lower_amount, upper_amount, tax_choice, ptr);

        }
    }

    private:
    void save_report(string report_name, string date_choice, string transaction_id_choice, string transaction_type, string filter_amount_choice, string choice_amount, string type_choice, string filter_type, float lower_amount, float upper_amount, string tax_choice, vector<Transaction*> ptr) {

        ofstream in_file(report_name, ios::out);

        in_file << "Report ID: " << report_id << endl;
        in_file << endl;

        if(type_choice != "B") {

            for (int i = 0; i < ptr.size(); i++) {
                if(type_choice == "I" && ptr[i]->get_type() != "income") //loop skips if transaction is not income transaction.
                    continue;
                if(type_choice == "E" && ptr[i]->get_type() != "expense") //loop skips if transaction is not expense transaction.
                    continue;
                if(filter_amount_choice == "Y" || filter_amount_choice == "y") {

                    //loop skips if transaction amount not in filter range
                    if(ptr[i]->get_amount() < lower_amount || ptr[i]->get_amount() > upper_amount) {
                        continue;
                    }
                }

                //printing transaction ID if selected.
                if(transaction_id_choice == "Y" || transaction_id_choice == "y") {
                    in_file << ptr[i]->get_transaction_ID() << "\t";
                }

                //printing dates if selected.
                if(date_choice == "Y" || date_choice == "y") {
                    in_file << ptr[i]->get_date() << "-";
                    in_file << ptr[i]->get_month() << "-";
                    in_file << ptr[i]->get_year() << "\t";
                }

                //printing transaction types if selected.
                if(transaction_type == "Y" || transaction_type == "y") {

                    if(filter_type == "Y" || filter_type == "y") {

                        if (type_choice == "b" || type_choice == "B") {

                            in_file << ptr[i]->get_type() << "\t";

                        }else if (type_choice == "I" || type_choice == "i") {

                            if(ptr[i]->get_type() == "income") { // important to check the same type of transactions are present in report...

                                in_file << ptr[i]->get_type() << "\t";

                            }
                        } else if (type_choice == "E" || type_choice == "e") {

                            if(ptr[i]->get_type() == "expense") { // important to check the same type of transactions are present in report...
                    
                                in_file << ptr[i]->get_type() << "\t";
                    
                            }   
                
                        } 
                    } else {
                        in_file << ptr[i]->get_type() << "\t";
                    }
                }

                //printing amount if filter amount is not selected.
                if((choice_amount == "Y" || choice_amount == "y") && (filter_amount_choice != "Y" || filter_amount_choice != "y")) {
                    in_file << ptr[i]->get_amount() << "\t";

                    //printing tax information if selected. 
                    if(tax_choice == "Y" || tax_choice == "y") {
                        in_file << ptr[i]->get_Tax_Amount() << "\t";
                    }

                    in_file << endl;
                    continue;
                }

                //printing amount if filter amount is selected.
                if(filter_amount_choice == "Y" || filter_amount_choice == "y") {
                    if(ptr[i]->get_amount() >= lower_amount && ptr[i]->get_amount() <= upper_amount) {
                        in_file << ptr[i]->get_amount() << "\t";
                    }
                }

                //printing tax information if selected. 
                if(tax_choice == "Y" || tax_choice == "y") {
                    in_file << ptr[i]->get_Tax_Amount() << "\t";
                }

                in_file << endl;
            }

        }else {

            type_choice = "I";
            for (int i = 0; i < ptr.size(); i++) {
                if(type_choice == "I" && ptr[i]->get_type() != "income") //loop skips if transaction is not income transaction.
                    continue;
                if(filter_amount_choice == "Y" || filter_amount_choice == "y") {

                    //loop skips if transaction amount not in filter range
                    if(ptr[i]->get_amount() < lower_amount || ptr[i]->get_amount() > upper_amount) {
                        continue;
                    }
                }

                //printing transaction ID if selected.
                if(transaction_id_choice == "Y" || transaction_id_choice == "y") {
                    in_file << ptr[i]->get_transaction_ID() << "\t";
                }

                //printing dates if selected.
                if(date_choice == "Y" || date_choice == "y") {
                    in_file << ptr[i]->get_date() << "-";
                    in_file << ptr[i]->get_month() << "-";
                    in_file << ptr[i]->get_year() << "\t";
                }

                //printing transaction types if selected.
                if(transaction_type == "Y" || transaction_type == "y") {

                    if(filter_type == "Y" || filter_type == "y") {

                        if (type_choice == "b" || type_choice == "B") {

                            in_file << ptr[i]->get_type() << "\t";

                        }else if (type_choice == "I" || type_choice == "i") {

                            if(ptr[i]->get_type() == "income") { // important to check the same type of transactions are present in report...

                                in_file << ptr[i]->get_type() << "\t";

                            }
                        } else if (type_choice == "E" || type_choice == "e") {

                            if(ptr[i]->get_type() == "expense") { // important to check the same type of transactions are present in report...
                    
                                in_file << ptr[i]->get_type() << "\t";
                    
                            }   
                
                        } 
                    } else {
                        in_file << ptr[i]->get_type() << "\t";
                    }
                }

                //printing amount if filter amount is not selected.
                if((choice_amount == "Y" || choice_amount == "y") && (filter_amount_choice != "Y" || filter_amount_choice != "y")) {
                    in_file << ptr[i]->get_amount() << "\t";

                    //printing tax information if selected. 
                    if(tax_choice == "Y" || tax_choice == "y") {
                        in_file << ptr[i]->get_Tax_Amount() << "\t";
                    }

                    in_file << endl;
                    continue;
                }

                //printing amount if filter amount is selected.
                if(filter_amount_choice == "Y" || filter_amount_choice == "y") {
                    if(ptr[i]->get_amount() >= lower_amount && ptr[i]->get_amount() <= upper_amount) {
                        in_file << ptr[i]->get_amount() << "\t";
                    }
                }

                //printing tax information if selected. 
                if(tax_choice == "Y" || tax_choice == "y") {
                    in_file << ptr[i]->get_Tax_Amount() << "\t";
                }

                in_file << endl;
            }

            in_file << endl;

            type_choice = "E";
            for (int i = 0; i < ptr.size(); i++) {
                if(type_choice == "E" && ptr[i]->get_type() != "expense") //loop skips if transaction is not expense transaction.
                    continue;
                if(filter_amount_choice == "Y" || filter_amount_choice == "y") {

                    //loop skips if transaction amount not in filter range
                    if(ptr[i]->get_amount() < lower_amount || ptr[i]->get_amount() > upper_amount) {
                        continue;
                    }
                }

                //printing transaction ID if selected.
                if(transaction_id_choice == "Y" || transaction_id_choice == "y") {
                    in_file << ptr[i]->get_transaction_ID() << "\t";
                }

                //printing dates if selected.
                if(date_choice == "Y" || date_choice == "y") {
                    in_file << ptr[i]->get_date() << "-";
                    in_file << ptr[i]->get_month() << "-";
                    in_file << ptr[i]->get_year() << "\t";
                }

                //printing transaction types if selected.
                if(transaction_type == "Y" || transaction_type == "y") {

                    if(filter_type == "Y" || filter_type == "y") {

                        if (type_choice == "b" || type_choice == "B") {

                            in_file << ptr[i]->get_type() << "\t";

                        }else if (type_choice == "I" || type_choice == "i") {

                            if(ptr[i]->get_type() == "income") { // important to check the same type of transactions are present in report...

                                in_file << ptr[i]->get_type() << "\t";

                            }
                        } else if (type_choice == "E" || type_choice == "e") {

                            if(ptr[i]->get_type() == "expense") { // important to check the same type of transactions are present in report...
                    
                                in_file << ptr[i]->get_type() << "\t";
                    
                            }   
                
                        } 
                    } else {
                        in_file << ptr[i]->get_type() << "\t";
                    }
                }

                //printing amount if filter amount is not selected.
                if((choice_amount == "Y" || choice_amount == "y") && (filter_amount_choice != "Y" || filter_amount_choice != "y")) {
                    in_file << ptr[i]->get_amount() << "\t";

                    //printing tax information if selected. 
                    if(tax_choice == "Y" || tax_choice == "y") {
                        in_file << ptr[i]->get_Tax_Amount() << "\t";
                    }

                    in_file << endl;
                    continue;
                }

                //printing amount if filter amount is selected.
                if(filter_amount_choice == "Y" || filter_amount_choice == "y") {
                    if(ptr[i]->get_amount() >= lower_amount && ptr[i]->get_amount() <= upper_amount) {
                        in_file << ptr[i]->get_amount() << "\t";
                    }
                }

                //printing tax information if selected. 
                if(tax_choice == "Y" || tax_choice == "y") {
                    in_file << ptr[i]->get_Tax_Amount() << "\t";
                }

                in_file << endl;
            }
        }

        in_file.close();

        cout << "Report sucessecfully generated!" << endl;

    }
    
};

class Budget {
private:
    char duration;
    float limit;
    float currentspent;
public:
    Budget() {

        this->duration = 'A';
        this->limit = 0.0;
        this->currentspent = 0.0;
    }

    friend void save_data(User);
    friend void load_data(User &);

    //setting duration accoirding to weekly, monthly, yearly.
    void setDurartion(char c) {
        while(1) {
            if(c == 'W' || c == 'M' || c == 'Y') {
                duration = c;
                break;
            } else {
                cout << "The duration entered is not recognized, enter a valid range" << endl;
                cin >> c;
            }
        }
    }

    //setting budget limit.
    void setLimit(float amount) {
        while(1) {
            if(amount <= 100000 && amount >= 0) {
                limit = amount;
                break;
            } else {
                cout << "The amount entered is invalid, kindly enter the correct amount" << endl;
                cin >> amount;
            }
        }
    }

    //tracks current spent and keeps track of limit.
    void setCurrentSpent(float amount) {
        
        currentspent += amount;

        if(currentspent > limit) {
            cout << "WARNING!!!\nThe amount entered exceeds your budget, please take note..." << endl;
        }   
        
    }
    
    //outputs the current spent along with the limit.
    void get_remaining_limit() {

        cout << "Spent/limit: " << currentspent << "/" << limit << endl;

    }
    
    // resets budget to initial.
    void reset_Budget() {

        this->duration = 'A';
        this->limit = 0.0;
        this->currentspent = 0.0;
    }
};

class Account {

    private:
    vector<Transaction*> transactions;
    int account_NO;
    string title;
    float debit_balance;
    float credit_balance;
    Report acc_report;

    public:
    Account() {

        srand(time(NULL));

        this->account_NO = (rand() % 1000000);
        this->title = title;
        this->debit_balance = 0.0;
        this->credit_balance = 0.0;

    }

    friend void save_data(User);
    friend void load_data(User &);

    void set_account_title(string name) {

        this->title = name;

    }

    int get_account_NO() {

        return this->account_NO;

    } 

    string get_title() {

        return this->title;

    }

    float get_debit_balance() {

        return this->debit_balance;

    }

    float get_credit_balance() {

        return this->credit_balance;
        
    }

    //function to store incomming transaction and update debit balance of account.
    void incomming_transaction(string source, float amount) {

        time_t Current_time; //making object of class time.
        Current_time = time(0); //assigning current time of system to current_time object;
        char *time = ctime(&Current_time); //storing current time on form of character array.
        string time_in_string(time); //converting current time to string format.
        string date = time_in_string.substr(8, 2); //extracting current date from time string.
        string month = time_in_string.substr(4, 3); //extracting current month from time string.
        string year = time_in_string.substr(20, 4); //extracting current year from time string.

        Transaction *incomming = new Income(source, amount, date, month, year); //creating income transaction object.
        transactions.push_back(incomming); //storing transaction in account.
        debit_balance = debit_balance + amount; //incrementing balance;

    }
    
    //funciton to set incomming transaction attributes manually.
    void incomming_transaction(string source, float amount, string date, string month, string year) {

        Transaction *incomming = new Income(source, amount, date, month, year); //creating income transaction object.
        transactions.push_back(incomming); //storing transaction in account.
        debit_balance = debit_balance + amount; //incrementing balance;

    }

    //function to store outgoing transaction and update credit balance of account.
    void outgoing_transaction(string source, float amount) {

        time_t Current_time; //making object of class time.
        Current_time = time(0); //assigning current time of system to current_time object;
        char *time = ctime(&Current_time); //storing current time on form of character array.
        string time_in_string(time); //converting current time to string format.
        string date = time_in_string.substr(8, 2); //extracting current date from time string.
        string month = time_in_string.substr(4, 3); //extracting current month from time string.
        string year = time_in_string.substr(20, 4); //extracting current year from time string.

        Transaction *outgoing = new Expense(source, amount, date, month, year); //creating expense transaction object.
        transactions.push_back(outgoing); //storing transaction in account.
        credit_balance = credit_balance + amount; //decrementing balance;

    }

    //funciton to set outgoing transaction attributes manually.
    void outgoing_transaction(string source, float amount, string date, string month, string year) {

        Transaction *outgoing = new Expense(source, amount, date, month, year); //creating expense transaction object.
        transactions.push_back(outgoing); //storing transaction in account.
        credit_balance = credit_balance + amount; //decrementing balance;

    }

    //search using date month and year.
    void search_transaction(string date, string month, string year) {

        Transaction *search;

        for(int i = 0; i < transactions.size(); i++) {

            //iterating between the different transactions stored.
            search = transactions[i];

            if((date == search->get_date()) && (month == search->get_month()) && (year == search->get_year())) {

                search->show_transacton();

            }

        }

    }

    //search transaction using transaction type.
    void search_transaction(string transaction_type) {

        Transaction *search;

        for(int i = 0; i < transactions.size(); i++) {

            //iterating between the different transactions stored.
            search = transactions[i];

            if(search->get_type() == transaction_type) {

                search->show_transacton();

            }

        }

    }

    void show_account_info() {

        cout << "account title: " << title << endl;
        cout << "account NO: " << account_NO << endl;
        cout << "debit balance: " << debit_balance << endl;
        cout << "credit balance: " << credit_balance << endl;
        cout << "net balance [positive/(negative)]: ";

        float net = debit_balance - credit_balance;

        if(net >= 0 ) {

            cout << net << endl << endl;

        }else {

            cout << "(" << net << ")" << endl << endl;

        }

    }

    void remove_transaction(string source) {

        Transaction *to_delete;
        char ans;
        int i;

        ans = 'n';

        //&& (to_delete->get_amount() == amount) && (to_delete->get_date() == date) && (to_delete->get_month() == month) && (to_delete->get_year() == year)
        //, float amount, string date, string month, string year
        
        for(i = 0; i < transactions.size(); i++) {
            
            system("cls");
            
            to_delete = transactions[i];

            if((to_delete->get_source() == source)) {

                to_delete->show_transacton();

                cout << "are you sure you want to delete this transaction? (Y/N): ";
                cin >> ans;

            }

            if((ans == 'y') || (ans == 'Y')) {
                
                break;
                    
            } 

        }

        if(to_delete->get_type() == "income" && (ans == 'y' || ans == 'Y')) {

            debit_balance = debit_balance - to_delete->get_amount();
            transactions.erase(transactions.begin() + i);
            delete to_delete;
            
        }else if(to_delete->get_type() == "expense" && (ans == 'y' || ans == 'Y')) {

            credit_balance = credit_balance - to_delete->get_amount();
            transactions.erase(transactions.begin() + i);
            delete to_delete;
        }

        

        
    }

    //prints the 5 most recent transactions.
    void get_transaction_history() {

        Transaction *t;
        int size = transactions.size() - 1;

        for(int i = size; i > (size - 5); i--) {

            t = transactions[i];

            t->show_transacton();

            if(i == 0) {

                break;
            }
            
        }

    }

    //function to call Reports's generate report.
    void get_report() {

        acc_report.generate_report(transactions);

    }

};

class User {
private:
	
	string firstname;
	string lastname;
	string address;
	string mobilenumber;
	int age;
    Account acc;
    Budget Food;
    Budget travel;
    Budget education;


	

public:
	User() {}

	/*User(string firstname, string lastname, string address, string mobilenumber, int age) {
		this->firstname = firstname;
		this->lastname = lastname;
		this->address = address;
		this->mobilenumber = mobilenumber;
		this->age = age;

        set_account_title();
	}*/
	

	void setFirstName(string firstname) {
		while(1) {
			if(firstname == "") {
				cout << "The name can not be empty. Kindly enter the correct name :" << endl;
				cin >> firstname;
			} else {
				this->firstname = firstname;
				break;
			}
		}
		
	}

	void setLastName(string lastname) {
		while(1) {
			if(lastname == "") {
				cout << "The name can not be empty. Kindly enter the correct name :" << endl;
				cin >> lastname;
			} else {
				this->lastname = lastname;
				break;
			}
		}

        set_account_title();
	}

	void setAddress(string address) {
		while(1) {
			if(address == "") {
				cout << "The name can not be empty. Kindly enter the correct name :" << endl;
				cin >> address;
			} else {
				this->address = address;
				break;
			}
		}
	}

	void setMobileNumber(string mobilenumber) {
		while(1) {
			if(mobilenumber == "" || mobilenumber.length() < 11) {
				cout << "The mobile number entered is invalid, Kindly re-enter the correct one..." << endl;
				cin >> mobilenumber;
			} else {
				this->mobilenumber = mobilenumber;
				break;
			}
		}
	}

	void setAge(int age) {
		while(1) {
			if(age < 18 || age > 100) {
				cout << "The age is out of bounds, kindly re-enter the correct age..." << endl;
				cin >> age;
			} else {
				this->age = age;
				break;
			}
		}
	}

	string getFirstName() { return firstname; }
	string getLastName() { return lastname; }
	string getAddress() { return address; }
	string getMobileNumber() { return mobilenumber; }
	int getAge() { return age; }

    private:
    //to set account title to Users name.
    void set_account_title() {

        acc.set_account_title(firstname+" "+lastname);

    }

    public:
    //allows user to make income transaction.
    void income() {

        string choice;
        string date;
        string month;
        string year;
        string source;
        float amount;

        cout << "Enter source of income: ";
        cin.ignore();
        getline(cin, source);

        cout << "Enter amount: ";
        cin >> amount;

        cout << "Do you want to manually set transaction date, month and year? [Y/N]: ";
        cin >> choice;

        if(choice == "Y" || choice == "y") {

            cout << "Enter date (01-31): ";
            cin >> date;

            cout << "Enter month (Jan-Dec): ";
            cin >> month;

            cout << "Enter year: ";
            cin >> year;

            acc.incomming_transaction(source, amount, date, month, year);

        }else {

            acc.incomming_transaction(source, amount);

        }

    }

    //allows user to make expense transaction.
    void expense() {

        string choice;
        string date;
        string month;
        string year;
        string source;
        float amount;

        cout << "Enter source of expense: ";
        cin.ignore();
        getline(cin, source);

        cout << "Enter amount: ";
        cin >> amount;

        cout << "Do you want to manually set transaction date, month and year? [Y/N]: ";
        cin >> choice;

        if(choice == "Y" || choice == "y") {

            cout << "Enter date (01-31): ";
            cin >> date;

            cout << "Enter month (Jan-Dec): ";
            cin >> month;

            cout << "Enter year: ";
            cin >> year;

            acc.outgoing_transaction(source, amount, date, month, year);

        }else {

            acc.outgoing_transaction(source, amount);

        }

    }

    //allows user to search transaction.
    void search_transaction() {

        string date, month, year, source, type, choice;

        cout << "Enter" << endl;
        cout << "1. To search using date month and year" << endl;
        cout << "2. To search using transaction type" << endl;
        cin >> choice;

        cout << endl;
        

        if(choice == "1") {

            system("cls");
            
            cout << "Enter date (01-31): ";
            cin >> date;

            cout << "Enter month (Jan-Dec): ";
            cin >> month;

            cout << "Enter year: ";
            cin >> year;

            cout << endl;
            
            system("cls");

            acc.search_transaction(date, month, year);

        }else if(choice == "2") {

            system("cls");

            cout << "Enter" << endl;
            cout << "1. To search for all Income transactions" << endl;
            cout << "2. To search for all Expense transactions" << endl;
            cin >> choice;

            

            if(choice == "1") {

                system("cls");

                acc.search_transaction("income");

            }else if(choice == "2") {

                system("cls");

                acc.search_transaction("expense");

            }else {

                cout << "Invalid choice" << endl;

            }

        }else {

            cout << "Invalid choice" << endl;

        }

    }

    //allows user to get account information.
    void get_account_info() {

        acc.show_account_info();

    }

    //allows user to delete transaction.
    void delete_transaction() {

        string source, date, month, year;
        float amount;

        cout << "Enter transaction source: ";
        cin.ignore();
        getline(cin, source);

        // cout << "Enter amount: ";
        // cin >> amount;

        // cout << "Enter date (01-31): ";
        // cin >> date;

        // cout << "Enter month (Jan-Dec): ";
        // cin >> month;

        // cout << "Enter year: ";
        // cin >> year;

        cout << endl;

        acc.remove_transaction(source);
        //, amount, date, month, year
    }

    //allows user to get the recent 5 transactions.
    void recent_transaction() {

        acc.get_transaction_history();

    }

    //allows user to print report with filters.
    void get_account_report() {

        acc.get_report();

    }

    //setting budget of Food, education and travel.
    void set_budget() {

        float limit;
        string choice;

        cout << "How much amount would like to set as limit: ";
        cin >> limit;

        cout << "Select the Item: " << endl;
        cout << "1. Food" << endl;
        cout << "2. Travel" << endl;
        cout << "3. Education" << endl;
        cin >> choice;

        if(choice == "1") {

            Food.setLimit(limit);

            cout << "Food Budget has been set to : " << limit << " successfully" << endl;
            system("pause");

        } else if (choice == "2") {

            travel.setLimit(limit);

            cout << "Travel Budget has been set to : " << limit << " successfully" << endl;
            system("pause");

        } else if (choice == "3") {

            education.setLimit(limit);

            cout << "Education Budget has been set to : " << limit << " successfully" << endl;
            system("pause");

        } else {

            cout << "Invalid Choice" << endl;
            system("pause");

        }

    }

     //setting budget duration of Food, education and travel.
    void set_duration() {

        char ch = 'A';
        string choice = "A";

        cout << "Enter the duration for the budget, 'W' for weekly, 'M' for Monthly, 'Y' for yearly.";
        cin >> ch;

        switch(ch) {
            case 'W':
            break;
            case 'M':
            break;
            case 'Y':
            break;
            default:
            cout << "Invalid Choice" << endl;
            return;
        }

        cout << "Select the Item: " << endl;
        cout << "1. Food" << endl;
        cout << "2. Travel" << endl;
        cout << "3. Education" << endl;
        cin >> choice;

        if(choice == "1") {

            Food.setDurartion(ch);
            cout << "Food Budget Duration has been set to : " << ch << " successfully" << endl;
            system("pause");

        } else if (choice == "2") {

            travel.setDurartion(ch);

            cout << "Travel Budget Duration has been set to : " << ch << " successfully" << endl;
            system("pause");

        } else if (choice == "3") {

            education.setDurartion(ch);

            cout << "Education Budget Duration has been set to : " << ch << " successfully" << endl;
            system("pause");

        } else {

            cout << "Invalid Choice" << endl;
            system("pause");

        }

    }

    //updating budget spent amount of Food, education and travel.
    void set_currentspent() {

        string choice = "A";
        float amount;

        cout << "Enter the amount you spent: ";
        cin >> amount;

        if(amount < 0 ) {
            cout << "Invalid Input..." << endl;
            system("pause");
            return;
        }

        cout << "Select the Item: " << endl;
        cout << "1. Food" << endl;
        cout << "2. Travel" << endl;
        cout << "3. Education" << endl;
        cin >> choice;

        if(choice == "1") {

            Food.setCurrentSpent(amount);

            cout << "Current Amount spent on Food is : " << amount << endl;
            system("pause");

        } else if (choice == "2") {

            travel.setCurrentSpent(amount);

            cout << "Current Amount spent on Travel is : " << amount << endl;
            system("pause");

        } else if (choice == "3") {

            education.setCurrentSpent(amount);
        
            cout << "Current Amount spent on Education is : " << amount << endl;
            system("pause");
        
        } else {

            cout << "Invalid Choice" << endl;
            system("pause");

        }
    }

    //view budgets.
    void view_remaining_limit() {

        string choice = "A";
        cout << "Select the Item you would like to view the budget of: " << endl;
        cout << "1. Food" << endl;
        cout << "2. Travel" << endl;
        cout << "3. Education" << endl;
        
        cin >> choice;

        if(choice == "1") {
            Food.get_remaining_limit();
        } else if (choice == "2") {
            travel.get_remaining_limit();
        } else if (choice == "3") {
            education.get_remaining_limit();
        } else {
            cout << "Invalid Choice" << endl;
        }
    }

    //resets budgets.
    void reset_budget() {

        
        string choice;

        cout << "Select the Item you want to reset the budget of: " << endl;
        cout << "1. Food" << endl;
        cout << "2. Travel" << endl;
        cout << "3. Education" << endl;
        cin >> choice;

        if(choice == "1") {

            Food.reset_Budget();

            cout << "Food Budget has been reset successfully" << endl;

            system("pause");

        } else if (choice == "2") {

            travel.reset_Budget();

            cout << "Travel Budget has been reset successfully" << endl;
            
            system("pause");

        } else if (choice == "3") {

            education.reset_Budget();

            cout << "Education Budget has been reset successfully" << endl;
            
            system("pause");

        } else {

            cout << "Invalid Choice" << endl;
            system("pause");

        }

    }

    // view user information...
    void show_information() {

        cout << "First Name : " << firstname << endl;
        cout << "Last Name : " << lastname << endl;
        cout << "Address : " << address << endl;
        cout << "Mobile Number : " << mobilenumber << endl;
        cout << "Age : " << age << endl;

    }
    
    friend void save_data(User);
    friend void load_data(User &);
};

void save_data(User u) {

    ofstream in_file("data.txt", ios::out);

    if(!in_file.is_open()) {

        cout << "unable to save data";
        exit(1);

    }else {
        
        //saving User class data in file.
        in_file << u.firstname << endl; //no space
        in_file << u.lastname << endl; //no space
        in_file << u.address << endl; //space
        in_file << u.mobilenumber << endl; //no space
        in_file << u.age << endl; //int
        
        //saving Account class data in file.
        in_file << u.acc.account_NO << endl; //int
        in_file << u.acc.title << endl; //space
        in_file << u.acc.debit_balance << endl; //float
        in_file << u.acc.credit_balance << endl; //float
        in_file << u.acc.transactions.size() << endl; //int
        for(int i = 0; i < u.acc.transactions.size(); i++) {

            Transaction *t;
            t = u.acc.transactions[i];

            in_file << t->date << endl; //no space
            in_file << t->month << endl; //no space
            in_file << t->year << endl; //no space;
            //in_file << t->transaction_ID << endl; //int
            in_file << t->transaction_amount << endl; //float
            in_file << t->transaction_type << endl; //no space
            in_file << t->get_source()  << endl; //space

            // Taxes *tax;
            // tax = u.acc.transactions[i]->tax;

            // in_file << tax->currenttax << endl; //float

            // delete tax;
            // delete t;

        }
        //in_file << u.acc.acc_report.report_id << endl; //int

        //saving Food Budget data in file.
        in_file << u.Food.duration << endl;
        in_file << u.Food.limit << endl;
        in_file << u.Food.currentspent << endl;
        
        //saving Travel Budget data in file.
        in_file << u.travel.duration << endl;
        in_file << u.travel.limit << endl;
        in_file << u.travel.currentspent << endl;

        //saving Education Budget data in file.
        in_file << u.education.duration << endl;
        in_file << u.education.limit << endl;
        in_file << u.education.currentspent << endl;

        in_file.close();
    }

}

void load_data(User &u) {

    ifstream from_file("data.txt", ios::in);
    string fname, lname, address, mobile, date, month, year, type, source;
    int age, int_data, transactions;
    float float_data; 

    if(!from_file.is_open()) {

        cout << "no data found. please enter the following." << endl;

        cout << "Enter first name: ";
        cin >> fname;
        u.setFirstName(fname);

        cout << "Enter last name: ";
        cin >> lname;
        u.setLastName(lname);

        cout << "Enter your address: ";
        cin.ignore();
        getline(cin, address);
        u.setAddress(address);

        cout << "Enter mobile No: ";
        cin >> mobile;
        u.setMobileNumber(mobile);

        cout << "Enter age: ";
        cin >> age;
        u.setAge(age);

    }else {

        //reading User class data from file/
        from_file >> u.firstname;
        from_file >> u.lastname;
        from_file.ignore();
        getline(from_file, u.address);
        from_file >> u.mobilenumber;
        from_file >> u.age;

        //reading Account class data from file.
        from_file >> u.acc.account_NO;
        from_file.ignore();
        getline(from_file, u.acc.title);
        from_file >> u.acc.debit_balance;
        from_file >> u.acc.credit_balance;
        from_file >> transactions;
        for(int i = 0; i < transactions; i++) {

            from_file >> date;
            from_file >> month;
            from_file >> year;
            from_file >> float_data;
            from_file >> type;
            from_file.ignore();
            getline(from_file, source);

            if(type == "income") {

                Transaction *t = new Income(source, float_data, date, month, year);
                u.acc.transactions.push_back(t);

            }else if(type == "expense") {

                Transaction *t = new Expense(source, float_data, date, month, year);
                u.acc.transactions.push_back(t);

            }
            
        }
        //from_file >> u.acc.acc_report.report_id;

        //reading Food Budget data from file.
        from_file >> u.Food.duration;
        from_file >> u.Food.limit;
        from_file >> u.Food.currentspent;
        
        //reading Travel Budget data from file.
        from_file >> u.travel.duration;
        from_file >> u.travel.limit;
        from_file >> u.travel.currentspent;

        //reading Education Budget data from file.
        from_file >> u.education.duration;
        from_file >> u.education.limit;
        from_file >> u.education.currentspent;

        from_file.close();

    }
}

int main() {

    User u;
    string choice; // outer switch...

    load_data(u);

    do {

        system("cls");
        
        cout << "WELCOME TO PERSONAL FINANCE MANAGER!" << endl;

        cout << "1. Make Transaction." << endl;
        cout << "2. Account" << endl;
        cout << "3. Budgets" << endl;
        cout << "4. User Information" << endl;
        cout << "5. Exit the Program" << endl;

        cin >> choice;

        if(choice == "1") {

             
            string option; // inner switch...   
            
            system("cls");
            
            cout << "1. Income Transaction" << endl;
            cout << "2. Expense Transaction" << endl;

            cin >> option;

            if(option == "1") {

                system("cls");

                u.income();

                system("pause");

            } else if (option == "2") {
                
                system("cls");

                u.expense();

                system("pause");

            } else {

                cout << "Invalid Option" << endl;
                system("pause");

            }
                
        } else if (choice == "2") {
                
            string option; // inner switch

            system("cls");

            cout << "1. View Account Information." << endl;
            cout << "2. View 5 most recent Transactions." << endl;
            cout << "3. Search Transaction." << endl;
            cout << "4. Delete Transaction." << endl;
            cout << "5. Account Report with filters" << endl;

            cin >> option;

            if (option == "1") {
                
                system("cls");

                u.get_account_info();

                system("pause");

            } else if (option == "2") {
                
                system("cls");

                u.recent_transaction();

                system("pause");

            } else if (option == "3") {

                system("cls");

                u.search_transaction();

                system("pause");

            } else if (option == "4") {

                system("cls");

                u.delete_transaction();

                system("pause");

            } else if (option == "5") {

                system("cls");

                u.get_account_report();

                system("pause");

            } else {

                cout << "Invalid Option" << endl;
                system("pause");

            }
                
            
                
        } else if (choice == "3") {

            string option;
            
            system("cls");

            cout << "1. Set Budget Limit" << endl;
            cout << "2. Set Budget Duration" << endl;
            cout << "3. Set Current Amount Spent" << endl;
            cout << "4. View Remaining Limit" << endl;
            cout << "5. Reset Budget" << endl;

            cin >> option;
            
            if (option == "1") {
                
                system("cls");

                u.set_budget();

            } else if (option == "2") {
                
                system("cls");

                u.set_duration();

            } else if (option == "3") {

                system("cls");

                u.set_currentspent();

            } else if (option == "4") {

                system("cls");

                u.view_remaining_limit();

                system("pause");

            } else if (option == "5") {

                system("cls");

                u.reset_budget();
            
            } else {

                cout << "Invalid Option" << endl;
                system("pause");

            }
                
                
        } else if (choice == "4") {
                
            string option;

            system("cls");

            cout << "1. View User Information." << endl;
            cout << "2. Update User Information." << endl;

            cin >> option;

            if (option == "1") {

                system("cls");

                u.show_information();

                system("pause");

            } else if (option == "2") {
                
                string select; // inner inner select...

                system("cls");
                
                cout << "1. Update Name." << endl;
                cout << "2. Update Address." << endl;
                cout << "3. Update Mobile Number." << endl;
                cout << "4. Update Age." << endl;
                
                cin >> select;

                if(select == "1") {
                    
                    string name;
                    
                    system("cls");
                    
                    cout << "Enter the First Name: ";
                    cin >> name;
                    u.setFirstName(name);

                    cout << "Enter the Last Name: ";
                    cin >> name;
                    u.setLastName(name);

                } else if (select == "2") {
                    
                    string address;
                    
                    system("cls");
                    
                    cout << "Enter the Address: ";
                    cin >> address;
                    u.setAddress(address);

                } else if (select == "3") {

                    string data;
                    
                    system("cls");
                    
                    cout << "Enter the Mobile Number: ";
                    cin >> data;
                    u.setMobileNumber(data);

                } else if (select == "4") {

                    int data;
                    
                    system("cls");
                    
                    cout << "Enter the Age: ";
                    cin >> data;
                    u.setAge(data);

                } else {

                    cout << "Invalid Option" << endl;
                    system("pause");
                
                }

            } else {
                
                cout << "Invalid Input" << endl;
                system("pause");

            }
                         
        } else if (choice == "5") {

            system("cls");

            cout << "SHUTTING DOWN..." << endl;
            cout << "PLEASE COME AGAIN :(" << endl;

            system("pause");
        
        } else {

            cout << "Invalid Input" << endl;
            system("pause");

        }
        


    } while (choice != "5");

    save_data(u);

    return 0;
}