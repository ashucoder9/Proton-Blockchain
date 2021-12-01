#include <bits/stdc++.h>

using namespace std;

// Transaction Data
struct Transaction {
  double amount;
  string senderkey;
  string receiverkey;
  time_t timestamp;
};

// Block Class
class Block {
private:
  int index;
  size_t blockHash;
  size_t previousHash;
  size_t generateHash(); // Hash Generator for Current Block

public:
  // Block Constructor
  Block(int idx, Transaction d, size_t prevHash);

  // Get Hash
  size_t getHash();

  // Fetch Previous Hash
  size_t getPreviousHash();

  // Transaction Data
  Transaction data;

  bool isHashValid();
};

// Block Constructor
Block::Block(int idx, Transaction d, size_t prevHash) {
  index = idx;
  data = d;
  previousHash = prevHash;
  blockHash = generateHash();
}

size_t Block::generateHash() {
  hash<string> hash1;
  hash<size_t> hash2;
  hash<size_t> finalHash;

  string toHash = to_string(data.amount) + data.receiverkey + data.senderkey +
                  to_string(data.timestamp);

  return finalHash(hash1(toHash) + hash2(previousHash));
}

size_t Block::getHash() { return blockHash; }

size_t Block::getPreviousHash() { return previousHash; }

bool Block::isHashValid() { return generateHash() == blockHash; }

// Blockchain Class
class Blockchain {
private:
  Block createProtonBlock();

public:
  // Public Chain
  vector<Block> chain;

  // Constructor
  Blockchain();

  // Functions
  void addBlock(Transaction data);
  bool isChainValid();
  Block *getLatestBlock();
};

// Blockchain Constructor
Blockchain::Blockchain() {
  Block proton = createProtonBlock();
  chain.push_back(proton);
}

Block Blockchain::createProtonBlock() {
  time_t current;
  Transaction d;
  d.amount = 0;
  d.receiverkey = "None";
  d.senderkey = "None";
  d.timestamp = time(&current);

  hash<int> hash1;
  Block proton(0, d, hash1(0));
  return proton;
}

Block *Blockchain::getLatestBlock() { return &chain.back(); }

void Blockchain::addBlock(Transaction d) {
  int index = (int)chain.size() - 1;
  Block newBlock(index, d, getLatestBlock()->getHash());
}

bool Blockchain::isChainValid() {
  int chainLength = (int)chain.size();
  for (auto it = chain.begin(); it != chain.end(); it++) {
    Block currBlock = *it;
    if (currBlock.isHashValid() == false)
      return false; // INVALID
    if (chainLength > 1) {
      Block previousBlock = *(it - 1);
      if (currBlock.getPreviousHash() != previousBlock.getHash())
        return false; // INVALID
    }
  }

  return true;
}

int main() {
  // Start Blockchain
  Blockchain MyCoin;

  // First Transaction
  Transaction d;
  time_t getTime;
  d.amount = 2500.00;
  d.senderkey = "A";
  d.receiverkey = "Z";
  d.timestamp = time(&getTime);

  MyCoin.addBlock(d);
  
  // In similar manner, we can add more transactions to the Chain

  cout << "Is Chain Valid?" << endl << MyCoin.isChainValid() << endl;
}
