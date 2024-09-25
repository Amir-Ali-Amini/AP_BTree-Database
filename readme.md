
# BTree Database

## Introduction

This project implements a database system using the **B-Tree** data structure in C++. It provides functionality for creating tables, inserting records, deleting records, updating records, and selecting records, similar to a relational database. Each query is optimized for time complexity using the B-Tree for efficient data storage and retrieval.

## Database Overview

A **database** is a collection of organized data stored and accessed electronically. A centralized system controls this collection, allowing one or more users to simultaneously interact with the stored data.

### Examples of Databases

- File archives
- Student information in a university
- Customer data of an organization
- Sales reports of a company

The most common type of database is the **Relational Database** (RDBMS), which stores data in tables. Each table consists of:

- **Fields**: Columns, representing a specific type of information.
- **Records**: Rows, representing a set of related fields.

Each table is defined with a structure that includes column names and data types. Data in each column must conform to the defined data type.

## Supported Operations

The database system supports the following operations (queries):

### 1. Create a Table

```sql
CREATE TABLE {table name} (column1 type, column2 type, ...)
```

Example:

```sql
CREATE TABLE employee (name string, joinDate timestamp, income int)
```

Note: The `id` column is automatically generated for each table.

### 2. Insert Records

```sql
INSERT INTO {table name} VALUES (field1, field2, ...)
```

Example:

```sql
INSERT INTO employee VALUES ("Hamid", 2022/8/6, 45000)
```

### 3. Delete Records

```sql
DELETE FROM {table name} WHERE {condition}
```

Example:

```sql
DELETE FROM employee WHERE name == "Hamid"
DELETE FROM employee WHERE income > 40000
```

Conditions can include equality (`==`) or inequality (`<>`).

### 4. Update Records

```sql
UPDATE {table name} SET (field1, field2, ...) WHERE {condition}
```

Example:

```sql
UPDATE employee SET ("Hamid", 2022/8/7, 50000) WHERE name == "Hamid"
```

### 5. Select Records

```sql
SELECT {(column1, column2, ...) or *} FROM {table name} WHERE {condition}
```

Example:

```sql
SELECT * FROM employee WHERE income > 45000
SELECT (name, income) FROM employee WHERE income > 45000
```

## B-Tree Implementation

The database uses **B-Tree** to ensure efficient query operations. Each column in a table is stored in its own B-Tree, where the keys are hashed values of the actual data.

### Time Complexity

- **INSERT**: O(log n)
- **DELETE, UPDATE, SELECT**: O(kc log n) where `n` is the number of records, `c` is the number of columns, and `k` is the number of records matching the condition.

## Node Structure

Each node in the B-Tree follows the structure:

```cpp
class Node {
public:
    int data;
    Node* nextField;
    BTNode* self;
}
```

- **data**: Integer representation (hash) of the stored data.
- **nextField**: Pointer to the next field in the same record.
- **self**: Pointer to the B-Tree node containing this field.

Non-integer data (e.g., strings, timestamps) are hashed before being stored in the B-Tree nodes.

## Input/Output Format

### Input

- The first line contains an integer `n`, the number of queries.
- Each of the next `n` lines contains a query.

### Output

- Results from `SELECT` queries are printed line by line.
- Fields in each row are separated by a space.

### Example Input

```plaintext
10
CREATE TABLE employee (name string,joinDate timestamp,income int)
INSERT INTO employee VALUES ("atena", 2019/7/6, 55000)
INSERT INTO employee VALUES ("sajede", 2020/5/24, 20000)
INSERT INTO employee VALUES ("zahra", 2019/4/5, 70000)
INSERT INTO employee VALUES ("narges", 2018/4/5, 40000)
INSERT INTO employee VALUES ("mohammad", 2020/1/1, 67000)
DELETE FROM employee WHERE income < 50000
INSERT INTO employee VALUES ("asha", 2018/12/5, 60000)
SELECT * FROM employee WHERE name == "asha"
SELECT (name,income) FROM employee WHERE income > 60000
```

### Example Output

```plaintext
2 asha 2018/12/5 60000
zahra 70000
mohammad 67000
```

(Note: Output is sorted by record `id`.)

## Bonus Features

This project includes the following error-checking features:

1. Type mismatch detection during insertion.
2. Syntax error detection.
3. Validation of date formats.
4. Support for a single usage of `&` and `|` in query conditions.

## Project Structure

- **`BTree.h`**: Contains the B-Tree implementation.
- **`Database.h`**: Defines the table and query handling logic.
- **`main.cpp`**: Entry point of the project where queries are parsed and executed.
