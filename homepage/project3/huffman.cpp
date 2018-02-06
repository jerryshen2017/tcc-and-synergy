#include <iostream>
#include <queue>
#include <map>
#include <climits>
#include "bstream.h"


using namespace std;

/* Type: ext_char
* A type representing a character, a pseudo-eof, or nothing. */
typedef int ext_char;

typedef map<ext_char, int> FreqMap;
typedef map<ext_char, string> CodeMap;

/* Constant: PSEUDO_EOF
* A constant representing the PSEUDO_EOF marker that you will
* write at the end of your Huffman-encoded file.
*/
const ext_char PSEUDO_EOF = 256;

/* Constant: NOT_A_CHAR
* A constant representing an extended character that does not
* actually hold a value.	 When you are constructing your Huffman
* encoding tree, you should set the characters in each internal
* node to this value to explicitly mark that they are not being
* used.
*/
const ext_char NOT_A_CHAR = 257;

/* Struct used to store all the informantion a huffman node needs*/
struct HuffmanNode
{
	ext_char data;
	int weight;
	HuffmanNode *left; // Left subtree ( corresponding code to '0' )
	HuffmanNode *right; // Left subtree ( corresponding code '1' )
	//constructor for leaves
	HuffmanNode(ext_char dat, int wgt) :data(dat), weight(wgt), left(NULL), right(NULL){}
	// constructor for internal nodes
	HuffmanNode(HuffmanNode *l, HuffmanNode *r) :data(NOT_A_CHAR), weight(l->weight + r->weight), left(l), right(r) {}

};


/* Structure used for comparing two huffman Node. Used by priority queue*/
struct compareHuffmanNode
{
	bool operator()(const HuffmanNode *first, const HuffmanNode *second)
	 {
		return first->weight  > second->weight;
	}
};


// Get a line from the user. 
string getLine(string str)
{
	bool tryAgain = true;
	string outString;
	while (tryAgain)
	{
		cout << str << endl;
		getline(cin, outString);
		if (outString == "")
		{
			cout << "Enter a valid string\n";
		}
		else
		{
			tryAgain = false;
		}
	}
	return outString;
}

/* Function: openFile
* --------------------------------------------------------
* Prompts the user for the name of a file to open, opening
* the indicated stream object to that file.
*/
template <typename FileStream>
void openFile(FileStream& file, string filename ) {
	//while (true) {

		file.open(filename.c_str());

		if (file.is_open()) return;

		cout << "Sorry, I couldn't open that file." << endl;
		file.clear();
		
	//}
}



/* Function: compareFiles
* --------------------------------------------------------
* Compares two files byte-by-byte to determine whether or
* not they are equivalent to one another.
*/
void compareFiles(string firstFile, string secondFile) {
	/* Get the two files to compare. */
	ifstream one, two;
	openFile(one, firstFile);
	openFile(two, secondFile);

	/* Read the contents of the files into a stringstream for
	* comparison.
	*/
	ostringstream oneContents, twoContents;
	oneContents << one.rdbuf();
	twoContents << two.rdbuf();

	const string oneString = oneContents.str(), twoString = twoContents.str();

	/* Check lengths are the same. */
	if (oneString.length() != twoString.length()) {
		cout << "Files differ!" << endl;
		cout << "File one has length " << oneString.length() << "." << endl;
		cout << "File two has length " << twoString.length() << "." << endl;
	}
	else {
		/* Compare the two sequences to find a mismatch. */
		pair<string::const_iterator, string::const_iterator> diff =
			mismatch(oneString.begin(), oneString.end(), twoString.begin());
		if (diff.first != oneString.end()) {
			cout << "Files differ!" << endl;
			ptrdiff_t offset = diff.first - oneString.begin();
			cout << "Bytes differ at offset " << offset << "." << endl;
			cout << "File one has value " << *diff.first << endl;
			cout << "File two has value " << *diff.second << endl;
		}
		else {
			/* Files match! */
			cout << "Files match!" << endl;
		}
	}
}


// Ths function simply creates a EncodeMap with the HuffmanTree as the Node and the map as the encoderMap.
// This function simply returns the current_string which is represented with 1's and 0's.
void createEncodeMap(HuffmanNode* node, map<int,string>& encoderMap, string currentString)
{
	if(node->data == NOT_A_CHAR)
	{
		createEncodeMap(node->left,encoderMap,currentString+"0");
		createEncodeMap(node->right,encoderMap,currentString+"1");
	}
	else
	{
		encoderMap[node->data] = currentString;
	}
}

/* Function: runEncoding
* --------------------------------------------------------
* Harness code to run your compression routine. */
void runEncoding()
{

	string inputFileName = getLine("Enter the name of file to encode ");
	string outputFileName = getLine("Enter the encoded file name ");
	string freqFileName = getLine("Enter the freq. file name");
  /* Your implementation */
	map<int,int> freqMap;
	//create a frequency map.
	ifstream inputFile;
	openFile(inputFile,inputFileName);
	int nextChar;
	int charct = 0;
	while( !inputFile.eof())
	{
		nextChar = inputFile.get();
		charct++;
		freqMap[nextChar]++;
	}
	cout << charct << " characters in input" << endl;
	ofstream freqFile;
	openFile(freqFile,freqFileName);
	// The first stands for the key and the second stands for the frequency.
	for(map<int,int>::iterator it = freqMap.begin(); it != freqMap.end(); it++)
	{
		freqFile << it->first << " " << it->second << "\n";
	}


	// I build a priority queue and put all the nodes in order and build build up the tree until everything is implemented.
	priority_queue<HuffmanNode*,vector<HuffmanNode*>, compareHuffmanNode> pq;
	for(map<int,int>::iterator it = freqMap.begin(); it != freqMap.end(); it++)
	{
		pq.push(new HuffmanNode(it->first,it->second));
	}
	while(pq.size() > 1)
	{

		// This is the math operation that is already being implemented inside the constructor.
		HuffmanNode* left = pq.top();
		pq.pop();
		HuffmanNode*right = pq.top();
		pq.pop();
		HuffmanNode* parent = new HuffmanNode(left,right);
		pq.push(parent);
	}
	// You simply tops out the elements.
	HuffmanNode* huffTree = pq.top();
	map<int,string> encoderMap;
	//This calls the createEncodeap functions.
	createEncodeMap(huffTree,encoderMap,"");

	ifstream instream2;
	openFile(instream2,inputFileName);
	// ofbstream converts the file into Binary encoded digits.
	ofbstream encodedFileStream;
	// This opens the file and outputs the files.
	openFile(encodedFileStream,outputFileName);
	while((nextChar = instream2.get()) != EOF)
	{

		string encodedString = encoderMap[nextChar];
		for(int i=0; i < encodedString.size(); i++)
		{
			char bitString = encodedString[i];
			// This iterator simply loops through the tree and returns 0 if you encounter 0 and returns 1 if you encounter 1.
			// and this simply writes the encoded elements onto the decoded components.
			if(bitString == '0')
			{
				encodedFileStream.writeBit(0);
			}
			else
			{
				encodedFileStream.writeBit(1);
			}
		}
	}

}


/* Function: runDecoding
* --------------------------------------------------------
* Harness code to run your decompression routine. */
void runDecoding()
{
	string inEncodeFileName = getLine("Enter the name of file to decode ");
	string outEncodeFileName = getLine("Enter the  file name to save after decoding");
	string freqFileName = getLine("Enter the freq. file name");
  /* Your implementation */

	ifstream freqStream;
	openFile(freqStream,freqFileName);

	map<int,int> freqMap;

	while(!freqStream.eof())
	{
		int ch, freq;
		freqStream >> ch >> freq;
		freqMap[ch] = freq;
	}

	priority_queue<HuffmanNode*,vector<HuffmanNode*>, compareHuffmanNode> pq;

	for(map<int,int>::iterator it = freqMap.begin(); it != freqMap.end(); it++)
	{

		// This function simply pushes the encoded elements into the decoded maps.
		pq.push(new HuffmanNode(it->first,it->second));
	}
	while(pq.size() > 1)
	{

		// This step is the same as the encoded compoenents stated above. All you have to do
		// is simply crossing the left subtree and then the right tree.

		HuffmanNode* left = pq.top();
		pq.pop();
		HuffmanNode*right = pq.top();
		pq.pop();
		HuffmanNode* parent = new HuffmanNode(left,right);
		pq.push(parent);
	}

	// Top the elements and throw it inside the decoderMap.
	HuffmanNode* huffTree = pq.top();
	map<int,string> decoderMap;
	createEncodeMap(huffTree,decoderMap,"");


	// This opens file for the encodedstream and the decodedstream.
	ifbstream encodedStream;
	openFile(encodedStream,inEncodeFileName);
	ofstream decodedStream;
	openFile(decodedStream, outEncodeFileName);
	HuffmanNode* currentNode = huffTree;
	int nextBit;
	// This loop is similar to the procedure carried out in the encoded procedure where
	// you simply throws 0 if you encounter the left tree and throws 1 if you encounter the right tree.
	while((nextBit = encodedStream.readBit()) != EOF)
	{
		if(nextBit == 0)
		{
			// 0 throws into left subtree.
			currentNode = currentNode->left;
		}
		else
		{
			// 1 throws into the subtree.
			currentNode = currentNode->right;
		}
		if(currentNode->data != NOT_A_CHAR)
		{
			// if it is not a charatcer you simply return the data.
			decodedStream.put(currentNode->data);
			currentNode = huffTree;
		}
	}
}

/* Function: runCompare
* --------------------------------------------------------
* Harness code to compare two files */
void runCompare()
{
	string firstFile = getLine("Enter the name of first file ");
	string secondFile = getLine("Enter the name of second file ");
	compareFiles(firstFile, secondFile);
}


// Entry point
int main()
{
  while (1)
  {
    cout << "Enter your choice \n"
      " 1. Huffman Encoding \n"
      " 2. Huffman Decoding \n"
      " 3. Compare Files\n" 
      " 4. Exit" << endl;
    int choice;
    cin >> choice;
    cin.clear(); cin.ignore(INT_MAX, '\n');
    if (choice == 1)
    {
      cout << " Encoding " << endl;
      runEncoding();
      cout << " Encoding done " << endl;
    }
    else if (choice == 2)
    {
      cout << " Decoding " << endl;
      runDecoding();
      cout << " Decoding done " << endl;
    }
    else if (choice == 3)
    {
      cout << "Comparing two files" <<endl;
      runCompare();
      cout << "Comparing done" <<endl;
    }
    else if( choice == 4)
    {
      cout <<"Exiting" <<endl;
      return 0;
    }
    else
    {
      cout << "Wrong choice. Try again \n";
    }
  }
  return 0;
}

int test()
{
	string name = "a.txt";
	ofbstream outfile;
	outfile.open(name.c_str());
	if (outfile.fail()) error("Can't open output file!");
	outfile << 134;
	char c = 'C';

	cout << sizeof('C') << c << " "<< int(c)<< endl;
	outfile.put('C');
	outfile.writeBit(0);
	outfile.writeBit(1);
	outfile.close();
	ifbstream infile;
	infile.open(name.c_str());
	if (infile.fail()) error("Can't open input file!");
	int num;
	infile >> num;
	cout << "read " << num;
	char dd = infile.get();
	cout << " " << dd << " and "
		<< infile.readBit() << infile.readBit() << endl;
	infile.close();
	getchar();
	getchar();
	return 0;
}
