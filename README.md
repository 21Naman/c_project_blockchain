Blockchain Banking System
A simple blockchain-based banking application implemented in C that demonstrates core blockchain concepts including mining, proof-of-work, and immutable transaction records.

FEATURES:

User Authentication: Register new accounts and login with username/password

Blockchain Technology: All transactions are stored in an immutable blockchain

Proof-of-Work Mining: Each block must be mined with a nonce that produces a hash starting with "1111"

Transaction Management:

1 Deposit money from bank

2 Transfer money between users

3 Check account balance

4 View complete blockchain history

Data Persistence: Transactions and user credentials are saved to files


HOW IT WORKS:

Each block contains:

1 Index: Position in the chain

2 Nonce: Value found through mining to create valid hash

3 Data: Transaction information (e.g., "Alice sent Bob 100")

4 Previous Hash: Hash of the previous block

5 Current Hash: Hash of this block (must start with 1111)


MINING ALGORITHM:

The system uses a proof-of-work algorithm where, a hash is calculated from: index + nonce + data + previous_hash

The nonce is incremented until the hash starts with "1111"

This ensures computational work was performed to add each block


HASH FUNCTION:

Custom hash function that:

Concatenates block data into a string

Applies polynomial rolling hash (multiplier of 31)

Returns a 16-digit hash value


PREREQUISITES:

GCC compiler or any C compiler

Standard C libraries

Compile:

gcc -o main main.c

Running the Program

./main



FIRST TIME SETUP:

Choose option 1 to Register

Enter a username and password

Login with your credentials


MAIN MENU OPTIONS:

1 Deposit Money: Add funds to your account from the bank

2 Money Transfer: Send money to another user

3 Check Balance: View your current account balance

4 View Blockchain: Display the entire blockchain history

5 Exit: Close the application


Example Transaction Flow

1. Deposit: "bank sent Alice 1000"

2. Transfer: "Alice sent Bob 500"

3. Check Balance: Alice has 500, Bob has 500


FILE STRUCTURE:

data.csv: Stores user registration information (username, password)

data.txt: Stores all blockchain transactions for persistence

main.c: Main source code


TECHNICAL DETAILS:

Balance Verification:

Balance is calculated by traversing the entire blockchain

All transactions to a user increase balance

All transactions from a user decrease balance

Transfers are only allowed if sender has sufficient balance


DATA PERSISTENCE:

On program restart:

Previous blockchain is reconstructed from data.txt

All historical transactions are loaded and re-mined

Users can resume from their last session
