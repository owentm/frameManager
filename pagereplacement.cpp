// CS390 assignment 4
// @author: Owen Murphy
// @professor: Dr. Gayathri Sadanala
//

#include <iostream>
#include <vector>

using namespace std;

/**
* FIFO is the first page replacement algorithm used in this assingment, replacing pages based on when they were added where the first page to
* be added is the first to be replaced
* @param string r is the reference string, inputted by the user
* @param int array is the page table, holding the data in each position
* @param int arraySize is the size of the array so sizeof(array) is not neccessary
*/
int FIFO(string r, char array[], int arraySize);

/**
* optimal is the most efficent function used, which is the hardest on processing standards, but also usually is the best for using as little
* page replacements as needed. optimal replaces the page whose data will be used the latest into the reference string
* @param string r is the reference string, inputted by the user
* @param int array is the page table, holding the data in each position
* @param int arraySize is the size of the array so sizeof(array) is not neccessary
*/
int optimal(string r, char array[], int arraySize);

/**
* LRU is the final algorithm implemented in this code, standing for "least recently used". This algorithm finds the page that has not been used
* in the most time
* @param string r is the reference string, inputted by the user
* @param int array is the page table, holding the data in each position
* @param int arraySize is the size of the array so sizeof(array) is not neccessary
*/
int LRU(string r, char array[], int arraySize);




int main()
{
    // allow the user to input a reference string
    string referenceString1 = " ";

    cout << "Please enter reference string. Please only enter numbers:  ";


    while (true) {

        bool doneFlag = true;
        cin >> referenceString1;

        // simple input validation to make sure that the reference string is only integers -- this may not be true to real life, 
        // but because this is a simulation, that's okay
        for (int i = 0; i < referenceString1.length(); i++)
        {

            // if the value is not a digit, denoted by "isdigit" returning a 0, keep the flag false and continue
            if (isdigit(referenceString1[i]) == 0)
            {
                cout << "Value at index " << i << " is not a digit. Please reenter: ";
                doneFlag = false;
            }
        }
           
        // otherwise, continue
        if (doneFlag == true)
        {
            break;
        }

    }

    // prompt the user to input free frames
    int pageFrames = 0;

    cout << "How many free frames are in the system: ";
    cin >> pageFrames;


    // make a dynamically allocated array that fills in ! for empty indexes which the program will recognize as an empty page
    char* pageTable = new char[pageFrames]();
    for (int i = 0; i < pageFrames ; i++)
    {
        pageTable[i] = '!';

    }

    // then, get the page faults from each of the algorithms, ensuring that the array is made empty at the end of each function again
    int fNumber1 = FIFO(referenceString1, pageTable, pageFrames);
    
    for (int i = 0; i < pageFrames; i++)
    {
        pageTable[i] = '!';

    }

    int fNumber2 = optimal(referenceString1, pageTable, pageFrames);

    for (int i = 0; i < pageFrames; i++)
    {
        pageTable[i] = '!';

    }

    int fNumber3 = LRU(referenceString1, pageTable, pageFrames);
  
    // then, output all page faults together to see the results together
    cout << "FIFO: " << fNumber1 << endl << "optimal: " << fNumber2 << endl << "LRU: " << fNumber3;

  
    delete[] pageTable;

    
        
}


int FIFO(string r, char array[], int arraySize)
{
    // set the amount of pageFaults to 0, and position add to 0, which will keep track of which index to replace
    int pageFaults = 0;
    int positionAdd = 0;

    cout << endl << "FIFO ALGORITHM: " << endl;

    // start looking through the string
    for (int i = 0; i < r.length(); ++i)
    {
        // make a flag that will tell us if we need to replace a page
        bool addFlag = true;
       
        
        // start a new for loop to see if the integer is contained in the page table
        for (int j = 0; j <= arraySize; j++)
        {
            // if it is, we know that we don't need to replace a page, so we will set the flag to false
            if (r[i] == array[j])
            {
                addFlag = false;
            }
        }
        
        // otherwise, continue with the replacement algorithm
        if (addFlag == true)
        {
            // we add the new data into the page that was added first. because the array comes in empty, it starts as being the first position
            // we add to the position every time a page is replaced, and in order to stay in bounds of the array, we perform the modulo operation
            // to keep all of the indexes in bounds
            array[positionAdd % arraySize] = r[i];
            pageFaults++;
            positionAdd++;
            
            // finally, to simulate the page table, we output the array at it's current state
            cout << "   -" << endl;
            for (int k = 0; k < arraySize; ++k)
            {
                cout << " | " << array[k] << " | " << endl;
            }
            cout << "   -" << endl << endl << endl;
        }
    }

    return pageFaults;
}

int optimal(string r, char array[], int arraySize)
{
    int pageFaults = 0;
    
    cout << endl << "OPTIMAL ALGORITHM: " << endl;

    // start by looking through the reference string, as we have already done
    for (int i = 0; i < r.length(); ++i)
    {
        bool addFlag = true;

        // once again, check for empty values
        for (int j = 0; j < arraySize; ++j)
        {
            if (array[j] == '!')
            {
                array[j] = r[i];
                pageFaults++;

                cout << "   -" << endl;
                for (int k = 0; k < arraySize; ++k)
                {
                    cout << " | " << array[k] << " | " << endl;
                }
                cout << "   -" << endl << endl << endl;

                addFlag = false;
                break;
              
            }

            // if the value is already in the table, replace it
            if (r[i] == array[j])
            {
                addFlag = false;
                break;
            }
        }


        if (addFlag == true)
        {
            // set the max index and position to 0, which will be overwritten in the for loops
            int maxIndex = 0;
            int maxPosition = 0;

            // start by looking at each value of the array
            for (int k = 0; k < arraySize; ++k)
            {
                
                // set the temporary furthest value to 0, and a found flag which will be used later to false
                int tempFurthest = 0;
                bool foundFlag = false;

                // then look through the rest of the reference string searching through the array value
                for (int p = i + 1; p < r.length(); ++p)
                {
                    // if found, set the temporary furthest value to the index of the string and set the found flag to true
                    if (array[k] == r[p])
                    {
                        tempFurthest = p;
                        foundFlag = true;
                        break;
                    }
                }

                // if the value was not found in the string, set the max index to the array value of which was not found, and break the loop
                // since if it is not found, it is automatically the furthest away the value can be
                if (foundFlag == false)
                {
                    maxIndex = k;
                    break;
                }
                
                // if found, however, check to see if the new value is higher than the current maximum index
                if (tempFurthest > maxPosition)
                {
                    // if it is, replace the max with the new value
                    maxPosition = tempFurthest;
                    maxIndex = k;
                }
            }
            
            // finally, add the page and display as done before
            array[maxIndex] = r[i];

            cout << "   -" << endl;
            for (int k = 0; k < arraySize; ++k)
            {
                cout << " | " << array[k] << " | " << endl;
            }
            cout << "   -" << endl << endl << endl;

            pageFaults++;
        }

    }

    return pageFaults;
}

int LRU(string r, char array[], int arraySize)
{
    // start by setting up a vector that will tell us which data value was last used
    vector<char> leastUsed;
    int pageFaults = 0;

    cout << endl << "LEAST RECENTLY USED ALGORITHM: " << endl;

    for (int i = 0; i < r.length(); ++i)
    {
        bool addFlag = true;

        for (int j = 0; j <= arraySize; ++j)
        {
            if (array[j] == '!')
            {
                // this time, if an empty value is found, we add that value to our vector as well as everything else that we've done
                array[j] = r[i];
                leastUsed.push_back(r[i]);
                pageFaults++;

                cout << "   -" << endl;
                for (int m = 0; m < arraySize; ++m)
                {
                    cout << " | " << array[m] << " | " << endl;
                }
                cout << "   -" << endl << endl << endl;

                addFlag = false;
                break;
            }

            else if (r[i] == array[j])
            {
                // if the page is found, we also make the add flag false, but then we look for the value in the string, when found, we
                // delete it from the vector and add it again to the end of the vector to accurately depict the least recently seen data point
                addFlag = false;
                auto it = find(leastUsed.begin(), leastUsed.end(), r[i]);
                if (it != leastUsed.end())
                {
                    leastUsed.erase(it);
                    leastUsed.push_back(r[i]);
                }

                break;
            }
            
            else
            {
                addFlag = true;
            }

        }

        if (addFlag == true)
        {
            for (int k = 0; k <= arraySize; k++)
            {
                // if the least used element is in the array, replace it
                // this ensures only one copy of each unique element will be present in the array at a time in order to accurately represent
                // the least recently used element
                if (array[k] == leastUsed.at(0))
                {
                    array[k] = r[i];
              
                    leastUsed.push_back(r[i]);
                    leastUsed.erase(leastUsed.begin());
                    
                    pageFaults++;


                    cout << "   -" << endl;
                    for (int m = 0; m < arraySize; ++m)
                    {
                        cout << " | " << array[m] << " | " << endl;
                    }
                    cout << "   -" << endl << endl << endl;
                 
                    break;
                }

            }

        }

    }


    return pageFaults;
}