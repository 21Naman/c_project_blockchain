Blockchain Banking System
A simple blockchain-based banking application implemented in C that demonstrates core blockchain concepts including mining, proof-of-work, and immutable transaction records.

FEATURES:

User Authentication: Register new accounts and login with username/password

Blockchain Technology: All transactions are stored in an immutable blockchain

Proof-of-Work Mining: Each block must be mined with a nonce that produces a hash starting with "1111"

Transaction Management:

    Deposit money from bank

    Transfer money between users

    Check account balance

    View complete blockchain history

Data Persistence: Transactions and user credentials are saved to files


How It Works

Blockchain Structure:

Each block contains:

Index: Position in the chain

Nonce: Value found through mining to create valid hash

Data: Transaction information (e.g., "Alice sent Bob 100")

Previous Hash: Hash of the previous block

Current Hash: Hash of this block (must start with 1111)


Mining Algorithm:
The system uses a proof-of-work algorithm where, a hash is calculated from: index + nonce + data + previous_hash

The nonce is incremented until the hash starts with "1111"

This ensures computational work was performed to add each block


Hash Function:

Custom hash function that:

Concatenates block data into a string

Applies polynomial rolling hash (multiplier of 31)

Returns a 16-digit hash value


Prerequisites:

GCC compiler or any C compiler

Standard C libraries

Compile:

gcc -o main main.c

Running the Program

./main



First Time Setup:

Choose option 1 to Register

Enter a username and password

Login with your credentials


Main Menu Options:

Deposit Money: Add funds to your account from the bank

Money Transfer: Send money to another user

Check Balance: View your current account balance

View Blockchain: Display the entire blockchain history

Exit: Close the application


Example Transaction Flow

1. Deposit: "bank sent Alice 1000"

2. Transfer: "Alice sent Bob 500"

3. Check Balance: Alice has 500, Bob has 500


File Structure:

data.csv: Stores user registration information (username, password)

data.txt: Stores all blockchain transactions for persistence

main.c: Main source code


Technical Details:

Balance Verification:

Balance is calculated by traversing the entire blockchain

All transactions to a user increase balance

All transactions from a user decrease balance

Bank has unlimited balance (INT_MAX)

Transfers are only allowed if sender has sufficient balance


Data Persistence:

On program restart:

Previous blockchain is reconstructed from data.txt

All historical transactions are loaded and re-mined

Users can resume from their last session