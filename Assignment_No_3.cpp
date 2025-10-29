#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// Class representing a relief item
class ReliefItem
{
public:
    double weight;
    double utility; // importance of the item
    bool divisible; // true if item can be taken fractionally

    ReliefItem(double w, double u, bool d) : weight(w), utility(u), divisible(d) {}

    // Utility per unit weight
    double utilityPerWeight() const
    {
        return utility / weight;
    }
};

// Comparator: sort items by descending utility per weight
bool compareItems(const ReliefItem &a, const ReliefItem &b)
{
    return a.utilityPerWeight() > b.utilityPerWeight();
}

// Fractional Knapsack algorithm
double fractionalKnapsack(double maxWeight, vector<ReliefItem> &items)
{
    // Sort items by value/weight ratio
    sort(items.begin(), items.end(), compareItems);

    cout << fixed << setprecision(2);
    cout << "\nItems sorted by utility/weight ratio (descending):\n";
    cout << "Weight\tUtility\tDivisible\tUtility/Weight\n";
    for (const auto &item : items)
    {
        cout << item.weight << "\t"
             << item.utility << "\t"
             << (item.divisible ? "Yes" : "No") << "\t\t"
             << item.utilityPerWeight() << endl;
    }
    cout << endl;

    double totalUtility = 0.0;
    double remainingCapacity = maxWeight;

    for (const auto &item : items)
    {
        if (remainingCapacity == 0)
            break;

        if (item.divisible)
        {
            double takeWeight = min(item.weight, remainingCapacity);
            totalUtility += takeWeight * item.utilityPerWeight();
            remainingCapacity -= takeWeight;
        }
        else
        {
            if (item.weight <= remainingCapacity)
            {
                totalUtility += item.utility;
                remainingCapacity -= item.weight;
            }
        }
    }

    return totalUtility;
}

int main()
{
    double boatCapacity;
    int numItems;

    cout << "Enter boat maximum weight capacity (kg): ";
    cin >> boatCapacity;

    cout << "Enter number of relief items: ";
    cin >> numItems;

    vector<ReliefItem> items;
    items.reserve(numItems);

    for (int i = 0; i < numItems; i++)
    {
        double weight, utility;
        int divisibleFlag;
        cout << "\nEnter details for item " << i + 1 << ":\n";
        cout << "Weight (kg): ";
        cin >> weight;
        cout << "Utility value: ";
        cin >> utility;
        cout << "Divisible? (1 for yes, 0 for no): ";
        cin >> divisibleFlag;

        items.emplace_back(weight, utility, divisibleFlag == 1);
    }

    double maxUtility = fractionalKnapsack(boatCapacity, items);

    cout << "\n Maximum utility value the boat can carry: " << maxUtility << endl;

    return 0;
}