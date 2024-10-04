#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include "split.h"

using namespace std;

// Customer class
struct Customer
{
    int id;
    string name;
    string street;
    string city;
    string state;
    string zip;
    string phone;
    string email;
};

// Item class
struct Item
{
    int id;
    string description;
    double price;
};

// Payment class
class Payment
{
public:
    virtual string print_detail() const = 0;
    virtual ~Payment() {}
};

// Credit class
class Credit : public Payment
{
private:
    string card_number;
    string expiration_date;

public:
    Credit(const string &card_num, const string &exp_date)
        : card_number(card_num), expiration_date(exp_date) {}

    string print_detail() const override
    {
        return "Paid by Credit card " + card_number + ", exp. " + expiration_date;
    }
};

// PayPal class
class PayPal : public Payment
{
private:
    string paypal_id;

public:
    PayPal(const string &paypal_id) : paypal_id(paypal_id) {}

    string print_detail() const override
    {
        return "Paid by PayPal ID: " + paypal_id;
    }
};

// WireTransfer class
class WireTransfer : public Payment
{
private:
    string bank_id;
    string account_id;

public:
    WireTransfer(const string &bank_id, const string &account_id)
        : bank_id(bank_id), account_id(account_id) {}

    string print_detail() const override
    {
        return "Paid by Wire transfer from Bank ID " + bank_id + ", Account# " + account_id;
    }
};

// LineItem class
struct LineItem
{
    int item_id;
    int quantity;
};

// Order class
class Order
{
private:
    int customer_id;
    int order_number;
    string order_date;
    vector<LineItem> line_items;
    Payment *payment;

public:
    Order(int cust_id, int order_num, const string &date, const vector<LineItem> &items, Payment *pay)
        : customer_id(cust_id), order_number(order_num), order_date(date), line_items(items), payment(pay) {}

    ~Order()
    {
        delete payment;
    }

    string print_order() const
    {
        ostringstream oss;
        oss << "===========================" << endl;
        oss << "Order #" << order_number << ", Date: " << order_date << endl;
        oss << "Amount: $" << calculate_total() << ", " << payment->print_detail() << endl;
        oss << "Customer ID #" << customer_id << ":" << endl;
        // Add customer info here
        oss << "Order Detail:" << endl;
        // Add item details here
        for (const auto &item : line_items)
        {
            // Add each item detail
        }
        oss << "===========================" << endl;
        return oss.str();
    }

    double calculate_total() const
    {
        double total = 0.0;
        for (const auto &item : line_items)
        {
            // Calculate total price for each line item
            // and sum them up
        }
        return total;
    }
};

// Global vectors and list
vector<Customer> customers;
vector<Item> items;
list<Order> orders;

// Function prototypes
void read_customers(const string &filename);
void read_items(const string &filename);
void read_orders(const string &filename);

void read_customers(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening customers file" << endl;
        exit(1);
    }

    string line;
    while (getline(file, line))
    {
        auto fields = split(line, ',');
        Customer customer;
        customer.id = stoi(fields[0]);
        customer.name = fields[1];
        customer.street = fields[2];
        customer.city = fields[3];
        customer.state = fields[4];
        customer.zip = fields[5];
        customer.phone = fields[6];
        customer.email = fields[7];
        customers.push_back(customer);
    }
    file.close();
}

void read_items(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening items file." << endl;
        exit(1);
    }

    string line;
    while (getline(file, line))
    {
        auto fields = split(line, ',');
        Item item;
        item.id = stoi(fields[0]);
        item.description = fields[1];
        item.price = stod(fields[2]);
        items.push_back(item);
    }
    file.close();
}

void read_orders(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening orders file" << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string customer_id_str, order_number_str, order_date, item_details;
        getline(iss, customer_id_str, ',');
        getline(iss, order_number_str, ',');
        getline(iss, order_date, ',');
        getline(iss, item_details);

        // Process item details
        vector<string> items_quantity_pairs = split(item_details, '-');
        // Add code to create Order object and add it to the global orders list
    }

    file.close();
}

void one_customer_order()
{
    cout << "Number of customers: " << customers.size() << endl;
    cout << "Number of items: " << items.size() << endl;

    int customer_id;
    cout << "Enter customer number: ";
    cin >> customer_id;

    bool customer_found = false;
    Customer customer;
    for (const auto &c : customers)
    {
        if (c.id == customer_id)
        {
            customer = c;
            customer_found = true;
            break;
        }
    }

    if (!customer_found)
    {
        cout << "Customer not found. Existing." << endl;
        return;
    }

    double total_cost = 0.0;
    int num_items = 0;

    while (true)
    {
        int item_id;
        cout << "Enter item number (0 to finish): ";
        cin >> item_id;

        if (item_id == 0)
        {
            break;
        }

        bool item_found = false;
        Item item;
        for (const auto &i : items)
        {
            if (i.id == item_id)
            {
                item = i;
                item_found = true;
                break;
            }
        }

        if (!item_found)
        {
            cout << "Item not found." << endl;
            continue;
        }

        total_cost += item.price;
        num_items++;
        cout << "Item description: " << item.description << ", Price: $" << item.price << endl;
    }

    cout << "Total items purchased: " << num_items << endl;
    cout << "Total cost: $" << fixed << setprecision(2) << total_cost << endl;
}

// Main function
int main()
{
    read_customers("customers.txt");
    read_items("items.txt");
    read_orders("orders.txt");

    ofstream ofs("order_report.txt");
    for (const auto &order : orders)
        ofs << order.print_order() << endl;

    return 0;
}
