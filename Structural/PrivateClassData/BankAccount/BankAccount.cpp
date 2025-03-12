#include <iostream>
using namespace std;

// Private data class: Hides sensitive details
class AccountData {
private:
    string accountNumber;
    double balance;

public:
    AccountData(string accNum, double bal) : accountNumber(accNum), balance(bal) {}

    string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    void updateBalance(double amount) {
        balance += amount;
    }
};

// Bank Account class using Private Class Data
class BankAccount {
private:
    AccountData* data; // Composition (contains private class)

public:
    BankAccount(string accNum, double bal) {
        data = new AccountData(accNum, bal);
    }

    ~BankAccount() { delete data; }

    void deposit(double amount) {
        if (amount > 0) {
            data->updateBalance(amount);
            cout << "Deposited: $" << amount << endl;
        } else {
            cout << "Invalid deposit amount" << endl;
        }
    }

    void showBalance() const {
        cout << "Account: " << data->getAccountNumber()
             << ", Balance: $" << data->getBalance() << endl;
    }
};

int main() {
    BankAccount account("123456789", 500.0);

    account.showBalance();
    account.deposit(200);
    account.showBalance();

    return 0;
}
