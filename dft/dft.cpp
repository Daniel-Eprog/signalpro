#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

vector<pair<float, float>> DFT(vector<float> timeDomain);
vector<float> IDFT(vector<pair<float, float>> frequencyDomain);
void printBottomGraph(int numberOfEntries);
template<typename T>
void printGraph(vector<T> const& functionToGraph, bool graphFrequency);

int main()
{

    vector<float> timeDomain;
    vector<pair<float, float>> frequencyDomain;

    //set function
    for(float i = 0; i < 1.02; i += 0.02)
    {
        timeDomain.push_back(i - 0.5);
    }

    frequencyDomain = DFT(timeDomain);
    
    //print time domain coefficients
    for(int i = 0; i < timeDomain.size(); i++)
    {
        cout << timeDomain.at(i) << " ";
    }

    //place space between the output
    cout << endl;

    //print out absolute value of complex DFT coefficients
    //here |a + bi| = sqrt(a^2 + b^2)
    // for(int i = 0; i < timeDomain.size(); i++)
    // {
    //     cout << sqrt(pow(frequencyDomain.at(i).first, 2) + pow(frequencyDomain.at(i).second, 2)) << " ";
    // }

    printBottomGraph(timeDomain.size());
    printGraph(frequencyDomain, true);
   
    return 0;
}

vector<pair<float,float>> DFT(vector<float> timeDomain)
{
    vector<pair<float, float>> frequencyDomain;

    //convert to frequency domain DFT
    for(int i = 0; i < timeDomain.size(); i++)
    {
        float DFT_real = 0.0f;
        float DFT_imaginary = 0.0f;

        for(int j = 0; j < timeDomain.size(); j++)
        {
            DFT_real += timeDomain.at(j) * (cos((2*M_PI*i*j)/timeDomain.size()));
            DFT_imaginary += -1 * timeDomain.at(j) * sin((2*M_PI*i*j)/timeDomain.size());
        }

        frequencyDomain.push_back(make_pair(DFT_real, DFT_imaginary));
    }

    return frequencyDomain;

}

void printBottomGraph(int numberOfEntries)
{
    cout << "   ";

    for(int i = 0; i < numberOfEntries; i++)
    {
        if(i == numberOfEntries - 1 || i == numberOfEntries/2 || i == 0)
        {
            cout << "^ ";
        }
        else 
        {
            cout << "  ";
        }
    }

    cout << endl;
    cout << "   ";

    for(int i = 0; i < numberOfEntries; i++)
    {
        if(i == numberOfEntries - 1 || i == numberOfEntries/2 || i == 0)
        {
            cout << i << " ";
        }
        else
        {
            cout << "  ";
        }
    }

}

template<typename T>
void printGraph(vector<T> const& functionToGraph, bool graphFrequency)
{   
    float graphMax = 0.0f;
    float graphMin = 0.0f;

    //finds parameters for plotting the graph between the maximum and minimum values
    for(int i = 0; i < functionToGraph.size(); i++)
    {
        //differentiates finding the parameters for frequency and time domain
        if(graphFrequency)
        {
            if(sqrt(pow(functionToGraph.at(i).first, 2) + pow(functionToGraph.at(i).second, 2)) > graphMax)
            {
                graphMax = sqrt(pow(functionToGraph.at(i).first, 2) + pow(functionToGraph.at(i).second, 2));
            }
            if(sqrt(pow(functionToGraph.at(i).first, 2) + pow(functionToGraph.at(i).second, 2)) < graphMin)
            {
                graphMin = sqrt(pow(functionToGraph.at(i).first, 2) + pow(functionToGraph.at(i).second, 2));
            }
        }
        else if(!graphFrequency)
        {
            if(functionToGraph.at(i) > graphMax)
            {
                graphMax = functionToGraph.at(i);
            }
            if(functionToGraph.at(i) < graphMin)
            {
                graphMin = functionToGraph.at(i);
            }

        }
    }

    //print as a plotted graph with floor
    for(int j = graphMax; j >= 0; j--)
    {
        cout << j << "> ";

        for(int i = 0; i < timeDomain.size(); i++)
        {
            if(sqrt(pow(frequencyDomain.at(i).first, 2) + pow(frequencyDomain.at(i).second, 2)) >= j)
            {
                cout << "* ";
            }
            else
            {
                cout << "  ";
            }
        }

        cout << endl;

    }


}