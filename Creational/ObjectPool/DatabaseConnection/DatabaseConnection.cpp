#include <iostream>
#include <vector>
#include <memory>  // For smart pointers
using namespace std;

// The object being pooled
class DatabaseConnection {
public:
    DatabaseConnection(int id) : id(id) {
        cout << "Database Connection " << id << " created." << endl;
    }

    void connect() {
        cout << "Database Connection " << id << " is now active." << endl;
    }

    void disconnect() {
        cout << "Database Connection " << id << " is now inactive." << endl;
    }

    int getId() const {
        return id;
    }

    ~DatabaseConnection() {
        cout << "Database Connection " << id << " destroyed." << endl;
    }

private:
    int id;  // Unique ID for debugging
};

// Object Pool for Database Connections
class ConnectionPool {
public:
    ConnectionPool(int poolSize) {
        for (int i = 0; i < poolSize; ++i) {
            pool.push_back(make_unique<DatabaseConnection>(i));
            available.push_back(pool.back().get());  // Store raw pointer in available list
        }
    }

    DatabaseConnection* acquire() {
        if (available.empty()) {
            cout << "No available connections. Wait or expand pool." << endl;
            return nullptr;
        }

        DatabaseConnection* conn = available.back();
        available.pop_back();
        conn->connect();
        return conn;
    }

    void release(DatabaseConnection* conn) {
        if (conn) {
            conn->disconnect();
            available.push_back(conn);
        }
    }

    ~ConnectionPool() {
        cout << "ConnectionPool shutting down. Releasing all resources." << endl;
    }

private:
    vector<unique_ptr<DatabaseConnection>> pool;  // Stores actual objects
    vector<DatabaseConnection*> available;  // Pointers to available objects
};

int main() {
    ConnectionPool pool(3);  // Create a pool with 3 connections

    DatabaseConnection* conn1 = pool.acquire();
    DatabaseConnection* conn2 = pool.acquire();

    pool.release(conn1);  // Return connection to pool
    pool.release(conn2);

    DatabaseConnection* conn3 = pool.acquire();
    DatabaseConnection* conn4 = pool.acquire();  // This will fail if pool is exhausted

    pool.release(conn3);

    return 0;
}
