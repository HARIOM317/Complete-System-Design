#include <bits/stdc++.h>

using namespace std;

class BloomFilter
{
private:
    vector<bool> bitArray; // bit array
    int m;                 // size of bit array
    int k;                 // number of hash functions

    // Generate ith hash value using double hashing technique
    int getHash(const string &s, int i)
    {
        // built-in hash functor in C++ (std::hash)
        hash<string> h; // h is an object of type hash<string>

        size_t hash1 = h(s);
        size_t hash2 = h(to_string(i) + s); // variation for multiple hashes
        return (hash1 + i * hash2) % m;
    }

public:
    BloomFilter(int size, int numHashes)
    {
        m = size;
        k = numHashes;
        bitArray.resize(m, false);
    }

    // Insert an element into the Bloom Filter
    void insert(const string &s)
    {
        for (int i = 0; i < k; i++)
        {
            int idx = getHash(s, i);
            bitArray[idx] = true;
        }
    }

    // Check if element possibly exists
    bool possiblyContains(const string &s)
    {
        for (int i = 0; i < k; i++)
        {
            int idx = getHash(s, i);
            if (!bitArray[idx])
                return false; // definitely not present
        }
        return true; // possibly present (may be false positive)
    }
};

int main()
{
    // Create a Bloom Filter with 20 bits and 3 hash functions
    BloomFilter bf(20, 3);

    // Insert some elements
    bf.insert("Hariom");
    bf.insert("Aman");
    bf.insert("Ankit");
    bf.insert("Anand");
    bf.insert("Sourabh");

    // Queries
    vector<string> queries = {"Hariom", "Ajay", "Sumit", "Pooja", "Ankit", "Harsh"};

    for (auto &q : queries)
    {
        if (bf.possiblyContains(q))
            cout << q << " is possibly in set." << endl;
        else
            cout << q << " is definitely not in set." << endl;
    }

    return 0;
}