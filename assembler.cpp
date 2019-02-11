#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <time.h>
#include <unordered_map>
#include <stdio.h>
#include <ctime>
// #include <bits/stdc++.h>
using namespace std;
#define Size 10
typedef class Table1
{
  public:
    string key1; // register or Mneumonics
    int machineCode, noofOperands, instSize;
    //string binary_rep;
    Table1 *next;
    Table1(string k, int machineCode, int noofOperands, int instSize)
    {
        this->key1 = k;
        this->machineCode = machineCode;
        this->noofOperands = noofOperands;
        this->instSize = instSize;
        this->next = nullptr;
    }
} node1;

typedef class Table2
{
  public:
    string key2, binary_rep;
    Table2 *next;
    Table2(string k, string bin)
    {
        this->key2 = k;
        this->binary_rep = bin;
        this->next = nullptr;
    }
} node2;

// typedef class Table3 {
//     public:
//     string key3;
//     int address;
//     Table3 *next;

//     Table3(string k, int v) {
//         this->key3 = k;
//         this->address = v;
//         this->next = nullptr;
//     }
// }node3;

class HashTable
{
  public:
    node1 **Mneumonics; // MNEMONICS HASH TABLE
    node2 **regisTer;   // REGISTER HASH TABLE
                        // node3 **pseudo_user; // pseudo operations and user defined table
    HashTable()
    {
        Mneumonics = new node1 *[Size];
        regisTer = new node2 *[Size];
        //pseudo_user = new node3 *[Size];
        for (int i = 0; i < Size; i++)
        {
            Mneumonics[i] = NULL;
            regisTer[i] = NULL;
            //pseudo_user[i] = NULL;
        }
    }

    void insertMne(string k, int machineCode, int noofOperands, int instSize)
    {
        int chh = HashFunction(k);
        node1 *ptr2 = Mneumonics[chh], *ptr1 = nullptr;
        while (ptr2 != nullptr)
        {
            ptr1 = ptr2;
            ptr2 = ptr2->next;
        }
        if (ptr2 == nullptr)
        {
            ptr2 = new node1(k, machineCode, noofOperands, instSize);
            if (ptr1 == nullptr)
            {
                Mneumonics[chh] = ptr2;
            }
            else
            {
                ptr1->next = ptr2;
            }
        }
        else
        {
            ptr2->machineCode = machineCode;
            ptr2->noofOperands = noofOperands;
            ptr2->instSize = instSize;
        }
    }

    void insertReg(string k, string bin)
    {
        int chh = HashFunction(k);
        node2 *ptr2 = regisTer[chh], *ptr1 = nullptr;
        while (ptr2 != nullptr)
        {
            ptr1 = ptr2;
            ptr2 = ptr2->next;
        }
        if (ptr2 == nullptr)
        {
            ptr2 = new node2(k, bin);
            if (ptr1 == nullptr)
            {
                regisTer[chh] = ptr2;
            }
            else
            {
                ptr1->next = ptr2;
            }
        }
        else
        {
            ptr1->binary_rep = bin;
        }
    }

    int HashFunction(string s)
    {
        char *ptr;
        ptr = &s[0];
        return int(*ptr) % 10; // MOD of first charecter of the string
    }

    void viewHashTable()
    {
        int i = 0;

        cout << "Mnemonics Hash Table : \n";
        for (i = 0; i < Size; i++)
        {
            node1 *ptr1 = Mneumonics[i];
            cout << i << "   ";
            while (ptr1 != nullptr)
            {
                cout << ptr1->key1 << " " << ptr1->machineCode << " " << ptr1->noofOperands << " " << ptr1->instSize << ", ";
                ptr1 = ptr1->next;
            }
            cout << "\n";
        }

        cout << "Register Hash Table \n";

        cout << "\n\n";
        for (i = 0; i < Size; i++)
        {
            node2 *ptr1 = regisTer[i];
            cout << i << "   ";
            while (ptr1 != nullptr)
            {
                cout << ptr1->key2 << " " << ptr1->binary_rep << ", ";
                ptr1 = ptr1->next;
            }
            cout << "\n";
        }

        cout << "Pseudo Operations Hash Table : \n";
        for (i = 0; i < Size; i++)

            cout << "Both Hash Tables\n";
    }

    int recLen(char *str)
    {
        if (*str == '\0')
            return 0;
        else
            return 1 + recLen(str + 1);
    }

    int searchHash(string key)
    {
        int chh = HashFunction(key);

        // priing string length for tables
        if (recLen(&key[0]) == 1)
        {
            // register table
            node2 *ptr2 = regisTer[chh];
            while (ptr2 != nullptr)
            {
                if (ptr2->key2 == key)
                {
                    return 1;
                }
                ptr2 = ptr2->next;
            }
        }
        else if (recLen(&key[0]) > 1)
        {
            // Menmonics table
            node1 *ptr1 = Mneumonics[chh];
            while (ptr1 != nullptr)
            {
                if (ptr1->key1 == key)
                {
                    return 1;
                }
                ptr1 = ptr1->next;
            }
        }
        return 0;
    }

    int retMachine_Code(string key, int code)
    { // code - 1 // Opcode (ret machine code)   // code - 2 // register(ret address)
        if (code == 1)
        {
            int index = HashFunction(key);
            node1 *ptr2 = Mneumonics[index];
            while (ptr2 != nullptr)
            {
                if (ptr2->key1 == key)
                {
                    return ptr2->machineCode;
                }
                ptr2 = ptr2->next;
            }
            return -1;
        }
        else if (code == 2)
        { // register table
            int index = HashFunction(key);
            node2 *ptr2 = regisTer[index];
            while (ptr2 != nullptr)
            {
                if (ptr2->key2 == key)
                {
                    return stoi(ptr2->binary_rep);
                }
            }
            return -1;
        }
    }

    string retBinCode(string key)
    { // for indexes only.
        int index = HashFunction(key);
        node2 *ptr = regisTer[index];
        while (ptr != nullptr)
        {
            if (ptr->key2 == key)
            {
                return (ptr->binary_rep);
            }
            ptr = ptr->next;
        }
        return "-1";
    }

    int retNoofOperands(string key)
    {
        //cout << key << " Found ? : " << searchHash(key) << "\n";
        //cout << key << " size : " << recLen(&key[0]) << "\n";
        if (searchHash(key) == 1)
        {
            if (recLen(&key[0]) == 1)
            {
                // register table
                return 1;
            }
            else if (recLen(&key[0]) > 1)
            {
                // Mnemonics table
                int chh = HashFunction(key);
                node1 *ptr = Mneumonics[chh];
                while (ptr != nullptr)
                {
                    if (ptr->key1 == key)
                    {
                        return ptr->noofOperands;
                    }
                    ptr = ptr->next;
                }
            }
        }
        return -1;
    }

    friend class Assembler;
    friend class HTWrapper;
    friend void insertTableValues(HashTable H)
    {
        H.insertMne("MOV", 44, 2, 4);
        H.insertMne("ADD", 47, 2, 4);
        H.insertMne("JUMP", 67, 1, 2);
        H.insertMne("CMP", 23, 2, 4);

        //H.insertMne("INC", 20, 1, 2);
        H.insertMne("END", 21, 0, 2);
        H.insertMne("BYTE", 62, 2, 4);
        H.insertMne("START", 01, 1, 2);
        H.insertMne("RESB", 63, 1, 2);
        H.insertMne("RESW", 64, 1, 2);
        H.insertMne("WORD", 61, 2, 4);
        H.insertMne("MUL", 40, 1, 2);

        H.insertReg("A", "000");
        H.insertReg("B", "001");
        H.insertReg("C", "010");
        H.insertReg("D", "011");
        H.insertReg("E", "100");
        H.insertReg("F", "101");
        H.insertReg("G", "110");
        H.insertReg("H", "111");

        //H.viewHashTable();
    }
};

class HTWrapper
{
    fstream file1, file2;

  public:
    HTWrapper()
    {
        file1.open("MnemonicsHash.txt");
        file2.open("registerHash.txt");
    }

    void saveTables(HashTable H)
    {

        // Mnemoics Table store
        for (int i = 0; i < Size; i++)
        {
            node1 *ptr1 = H.Mneumonics[i];
            while (ptr1 != nullptr)
            {
                file1 << ptr1->key1 << " " << ptr1->machineCode << " " << ptr1->noofOperands << " " << ptr1->instSize << ",";
                ptr1 = ptr1->next;
            }
            file1 << "\n";
        }
        file1.close();

        for (int j = 0; j < Size; j++)
        {
            node2 *ptr2 = H.regisTer[j];
            while (ptr2 != nullptr)
            {
                file2 << ptr2->key2 << " " << ptr2->binary_rep << ",";
                ptr2 = ptr2->next;
            }
            file2 << "\n";
        }
        file2.close();
    }

    void viewTables(HashTable H)
    {
        file1.open("MnemonicsHash.txt");
        // Mnemonics hash table
        string line1;
        while (file1)
        {
            getline(file1, line1);
            cout << line1 << "\n";
        }
        file1.close();

        file2.open("registerHash.txt");
        // register hash table
        string line2;
        while (file2)
        {
            getline(file2, line2);
            cout << line2 << "\n";
        }
        file2.close();
    }
};

// ASSEMBLY LANGUAGE
class Assembler
{

    fstream file3;
    //vector<string> input;
    int lineNumber;
    int errorType; // 1 - invalid number of operands    // 2 - chh not defined    // 3 - no such opcode // 4 - variable not declared
    string input;
    vector<string> v;
    string tmp;
    int chhCount;
    int location;
    unordered_map<string, int> indexes;
    //unordered_map<string, int> variables;

  public:
    int isError;
    //Assembler() { file3.open("AssemblyLanguage.txt"); }

    void firstPass(HashTable H)
    {
        int locCtr = -1;
        file3.open("AssemblyLanguage.txt");
        while (file3)
        {
            getline(file3, input);
            v.push_back(input);
        }
        for (vector<string>::iterator it = v.begin(); it != v.end(); ++it)
        {
            istringstream iss(*it);
            vector<string> result;
            for (string s; iss >> s;)
                result.push_back(s);

            string key = result[0];

            if (key == "START")
            {
                locCtr = stoi(result[1]); // pointing to start address
            }
            else

                if (key == "MOV" || key == "ADD" || key == "CMP")
            {
                locCtr += 4;
            }
            else if (key == "JUMP")
            {
                locCtr += 2;
            }

            else if (key.back() == ':')
            {
                // indexed statement
                string new_key = key;
                new_key.resize(new_key.size() - 1);
                indexes[new_key] = locCtr;
            }
            else if (key == "BYTE" || key == "WORD" || key == "RESW" || key == "RESB")
            {
                if (result[1].size() != 1)
                {
                    // variable
                    H.insertMne(result[1], -1, locCtr, -1);
                }
            }
        }
        // FIRST PASS
    }

    void readCode(HashTable H)
    {

        firstPass(H);

        isError = 0;
        file3.open("AssemblyLanguage.txt");
        lineNumber = 0;
        while (file3)
        {
            getline(file3, input);
            v.push_back(input);
            // taking whole line in the string
            // parsing afterwords.
        }
        for (vector<string>::iterator it = v.begin(); it != v.end(); ++it)
        {
            chhCount = 0;
            istringstream iss(*it);
            // parsing a single line
            // parsed line stored in the vector result.
            vector<string> result;
            for (string s; iss >> s;)
                result.push_back(s);

            // result contains parsed words
            string key = result[0]; // by default

            if (key == "START")
            {
                location = stoi(result[1]);
            } // storing location address

            if (key == "BYTE" || key == "RESB" || key == "RESW" || key == "WORD")
            { // variable declared
                if (key == "BYTE" || key == "WORD")
                {
                    location += 4;
                }
                else
                {
                    location += 2;
                }
            }

            if (key == "MUL" || key == "DIV")
            {
                location += 2;
                if (H.searchHash(result[1]) != 1)
                {
                    //variable or direct value
                    if (result[1][0] != '#')
                    {
                        // variable not found , throw error
                        errorType = 4;
                        errorHandler(errorType, lineNumber);
                    }
                }
            }

            if (key == "ADD" || key == "SUB" || key == "MOV")
            {
                location += 4;
                string s = result[1];
                s.resize(s.size() - 1);
                if (H.searchHash(s) != 1)
                {
                    // variable not found , throw error
                    errorType = 4;
                    errorHandler(errorType, lineNumber);
                }
            }

            else
            {

                string pri = result[0];
                if (pri.back() == ':')
                {
                    // indexed value already stored in first pass
                    key = result[1];
                    int operands = H.retNoofOperands(key);
                    if (operands != result.size() - 2)
                    {
                        errorType = 1;
                        errorHandler(errorType, lineNumber);
                    }
                }
                if (key == "JUMP")
                {
                    unordered_map<string, int>::const_iterator got = indexes.find(result[1]);
                    if (got == indexes.end())
                    {
                        errorType = 2;
                        errorHandler(errorType, lineNumber);
                    }
                    location += 2;
                }
                if (key == "END")
                {
                    return;
                }
                else if (H.searchHash(key) == 1)
                {
                    // hash found
                    int operands = H.retNoofOperands(key);
                    if (operands != result.size() - 1 && key == result[0])
                    {
                        errorType = 1;
                        errorHandler(errorType, lineNumber);
                    }
                }
                else if (H.searchHash(key) == 0)
                {
                    errorType = 3;
                    errorHandler(errorType, lineNumber);
                }
            }
            lineNumber++;
        }

        file3.close();
    }

    void printCode()
    {
        file3.open("AssemblyLanguage.txt");
        string in;
        while (file3)
        {
            getline(file3, in);
            cout << in << "\n";
        }
        file3.close();
    }

    void errorHandler(int errorNumber, int line)
    {

        line += 1;
        isError = 1;
        if (errorNumber == 1)
        {
            cout << "Error in Line : " << line << " Invalid Number of Operands.\n";
        }
        else if (errorNumber == 2)
        {
            cout << "Error in Line : " << line << " chh not defined.\n";
        }
        else if (errorNumber == 3)
        {
            cout << "Error in Line : " << line << " OpCode not defined.\n";
        }
        else if (errorNumber == 4)
        {
            cout << "Error in Line : " << line << " Variable not Declared\n";
        }
    }

    void ObjectModulePseudo(HashTable H)
    {
        string input;
        vector<string> v1;
        fstream f1;
        f1.open("AssemblyLanguage.txt");
        while (f1)
        {
            getline(f1, input);
            v1.push_back(input);
        }
        f1.close();
        for (vector<string>::iterator itr = v1.begin(); itr != v1.end(); itr++)
        {

            string opCode, operand1, operand2;
            int chhCount = 0;
            int locCtr;
            istringstream iss(*itr);
            vector<string> result;
            for (string s; iss >> s;)
                result.push_back(s);

            string key = result[0];

            if (key.back() == ':')
            {
                string new_key = key;
                new_key.resize(new_key.size() - 1);
                cout << new_key << ", " << locCtr << "\n";
            }

            if (key == "START")
            {
                locCtr = stoi(result[1]); // string to int
                locCtr += 2;
            }
            else if (key == "END")
            {
                // cout << "EOF\n";
                return;
            }
            else if (key == "BYTE" || key == "RESB")
            {
                locCtr += 4;
                if (key == "BYTE")
                {
                    cout << result[1] << ", " << H.retNoofOperands(result[1]) << "\n";
                }
                else
                {
                    cout << result[1] << ", " << H.retNoofOperands(result[1]) << "\n";
                }
            }
            else if (key == "WORD" || key == "RESW")
            {
                locCtr += 2;
                if (key == "RESW")
                    cout << result[1] << ", " << H.retNoofOperands(result[1]) << "\n";
                else
                    cout << result[1] << ", " << H.retNoofOperands(result[1]) << "\n";
            }
            else if (key == "JUMP")
            {
                if (isError == true)
                {
                    cout << result[1] << " was never defined in the program \n";
                }
                else
                    cout << result[1] << " " << indexes[result[1]] << "\n";
            }
            else if (key == "ADD" || key == "SUB")
            {
                locCtr += 4;
            }
            else if (key == "MUL" || key == "MOV")
            {
                locCtr += 2;
            }
            else if (key == "INC")
            {
                locCtr += 1;
            }
        }
    }

    // string decToBinary(int toConv) // decimal to binary conversion
    // {
    //     string binaryOut, revBinaryOut;
    //     while (toConv >= 1)
    //     {
    //         if (toConv % 2 == 0)
    //             binaryOut += "0";
    //         else
    //             binaryOut += "1";
    //         toConv /= 2;
    //     }
    //     for (int i = binaryOut.length(); i >= 0; i--)
    //     {
    //         revBinaryOut += binaryOut[i];
    //     }
    //     return revBinaryOut;
    // }

    void date1()
    {
        time_t t = time(0);
        tm *now = localtime(&t);
        cout << (now->tm_year + 1900)
             << (now->tm_mon + 1)
             << now->tm_mday
             << "` ";
    }
    void time1()
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        cout << (ltm->tm_hour) << ltm->tm_min << ltm->tm_sec << "` ";
    }
    void objectFile(HashTable H)
    {
        string input;
        vector<string> v1;
        fstream f1;
        f1.open("AssemblyLanguage.txt");
        while (f1)
        {
            getline(f1, input);
            v1.push_back(input);
        }
        f1.close();
        for (vector<string>::iterator itr = v1.begin(); itr != v1.end(); itr++)
        {

            string opCode, operand1, operand2;
            int chhCount = 0;
            int locCtr;
            istringstream iss(*itr);
            vector<string> result;
            for (string s; iss >> s;)
                result.push_back(s);

            string key = result[0];
            string op1;
            string op2, op3;

            //cout << "key : " << key << "\n";

            if (key.back() == ':')
            {
                key = result[1];
            }

            if (key == "START")
            {
                cout << "OBJ` ";
                date1();
                time1();
                cout << result[1] << "`\n";
            }
            else if (key == "MOV")
            {

                if (key == result[1])
                {
                    op1 = result[2];
                    op2 = result[3];
                }
                else
                {
                    op1 = result[1];
                    op2 = result[2];
                }
                cout << H.retMachine_Code(key, 1) << "` ";

                string new_op1 = op1;
                new_op1.resize(new_op1.size() - 1);
                if (new_op1.size() == 1)
                {
                    // register
                    cout << H.retBinCode(new_op1) << "` ";
                }
                else
                {
                    // variable
                    cout << H.retNoofOperands(new_op1) << "` ";
                }
                // 2nd operand
                if (op2[0] == '#')
                {
                    // immidiate opearnd
                    string new_op = op2;
                    reverse(new_op.begin(), new_op.end());
                    new_op.resize(new_op.size() - 1);
                    int x = stoi(new_op);
                    string binary = bitset<4>(x).to_string();
                    cout << binary << "`\n";
                }
                else if (op2.size() == 1)
                {
                    // register
                    cout << H.retBinCode(op2) << "`\n";
                }
                else
                {
                    // variable
                    cout << H.retNoofOperands(op2) << "`\n";
                }
            }
            else if (key == "ADD" || key == "SUB")
            {

                if (key == result[1])
                {
                    op1 = result[2];
                    op2 = result[3];
                }
                else
                {
                    op1 = result[1];
                    op2 = result[2];
                }
                cout << H.retMachine_Code(key, 1) << "` ";
                string new_op = op1;
                new_op.resize(new_op.size() - 1);

                if (new_op.size() == 1)
                {
                    // register
                    cout << H.retBinCode(new_op) << "` ";
                }
                else
                {
                    // variable
                    cout << H.retNoofOperands(new_op) << "` ";
                }

                if (op2[0] == '#')
                {
                    // immidiate opearnd
                    string new_op = op2;
                    reverse(new_op.begin(), new_op.end());
                    new_op.resize(new_op.size() - 1);
                    int x = stoi(new_op);
                    string binary = bitset<4>(x).to_string();
                    cout << binary << "`\n";
                }
                else if (op2.size() == 1)
                {
                    // register
                    cout << H.retBinCode(op2) << "`\n";
                }
                else
                {
                    // variable
                    cout << H.retNoofOperands(op2) << "`\n";
                }
            }
            else if (key == "JUMP")
            {
                cout << H.retMachine_Code(key, 1) << "` " << indexes[result[1]] << "`\n";
            }
            else if (key == "END")
            {
                return;
            }
            else if (key == "BYTE" || key == "RESW" || key == "RESB")
            {

                string new_val = result[2];
                reverse(new_val.begin(), new_val.end());
                new_val.resize(new_val.size() - 1);
                int x = stoi(new_val);
                string binary = bitset<4>(x).to_string();
                cout << binary << "`\n";
            }
        }
    }
};

int main()
{
    HashTable H;
    insertTableValues(H);

    //H.viewHashTable();
    HTWrapper htw;
    htw.saveTables(H);
    // htw.viewTables(H);

    Assembler a;
    // a.printCode();
    a.readCode(H);
    if (a.isError == true)
    {
        cout << "\n\nPseudo Codes  : \n\n";
        a.ObjectModulePseudo(H);
        cout << "ASSEMBLER : CODE CANNOT BE CONVERTED!\n\n";
    }
    else
    {
        // cout << "\nPseudo Codes : \n\n";
        // a.ObjectModulePseudo(H);
        // cout << "\n\n";
        cout << "ASSEMBLER : CODE CONVERTED SUCCESSFULLY!\n";
        cout << "OBJECT FILE \n \n\n\n";
        a.objectFile(H);

        //cout << "Time : \n";
        //a.date1();
    }
    return 0;
}
