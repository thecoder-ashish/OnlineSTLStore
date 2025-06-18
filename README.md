# Simple C++ Online Store (Console App)

This is a simple console-based online store management system written in C++.  
It demonstrates the use of STL containers (`vector`, `deque`, `list`, `set`, `map`, `unordered_map`, `multimap`, `unordered_set`) and basic C++ programming concepts.

## Features

- Add and manage products and customers
- Place orders and track order history
- View recent customers and all registered customers
- Track product stock and categories
- Admin and customer interfaces
- Date and time formatting for order history

## How to Build

You need a C++ compiler (like g++ from MinGW or GCC):

```sh
g++ -o onlineStore stlStore.cpp
```

For a statically linked Windows executable (no DLLs needed):

```sh
g++ -static -o onlineStore.exe stlStore.cpp
```

## How to Run

```sh
./onlineStore
```
or on Windows:
```sh
onlineStore.exe
```

## Usage

- Run the program and follow the on-screen menu.
- Choose between Admin and Customer modes.
- Admin can view/add products, customers, and orders.
- Customers can view products and place orders.

## Notes

- All data is stored in memory (no file/database persistence).
- This project is for learning and demonstration purposes.

---

Feel free to fork