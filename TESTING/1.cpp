#include <iostream>
#include <string>
using namespace std;

// Node structure for Ride Requests
struct RideRequest
{
  int requestID;
  string customerName;
  string pickup;
  string dropoff;
  float fare;
  string date; // Added date field in DD/MM/YYYY format
  RideRequest *next;
};
// Node structure for Active Rides
struct ActiveRide
{
  int rideID;
  string customerName;
  string driverName;
  string pickup;
  string dropoff;
  float fare;
  string date; // Added date field in DD/MM/YYYY format
  ActiveRide *next;
};
// Node structure for Ride History
struct RideHistory
{
  int rideID;
  string customerName;
  string driverName;
  string pickup;
  string dropoff;
  float fare;
  string date;   // Added date field in DD/MM/YYYY format
  string status; // Completed or Canceled
  RideHistory *next;
};
// Main RideNow System Class
class RideNowSystem
{
private:
  RideRequest *requestHead;
  ActiveRide *activeHead;
  RideHistory *historyHead;

  bool isEmpty(RideRequest *head)
  {
    return head == NULL;
  }

  bool isEmpty(ActiveRide *head)
  {
    return head == NULL;
  }
  bool isEmpty(RideHistory *head)
  {
    return head == NULL;
  }

public:
  RideNowSystem()
  {
    requestHead = NULL;
    activeHead = NULL;
    historyHead = NULL;
  }
  // ========== Ride Request Functions ==========
  void addRideRequest(int id, string cname, string pu, string doff, float f, string d)
  {
    RideRequest *n = new RideRequest();
    n->requestID = id;
    n->customerName = cname;
    n->pickup = pu;
    n->dropoff = doff;
    n->fare = f;
    n->date = d;
    n->next = NULL;

    if (isEmpty(requestHead))
    {
      requestHead = n;
    }
    else
    {
      RideRequest *temp = requestHead;
      while (temp->next != NULL)
      {
        temp = temp->next;
      }
      temp->next = n;
    }
  }
  void cancelRideRequest(int id)
  {
    if (isEmpty(requestHead))
    {
      cout << "No ride requests to cancel.\n";
      return;
    }

    if (requestHead->requestID == id)
    {
      RideRequest *temp = requestHead;
      requestHead = requestHead->next;
      delete temp;
      cout << "Ride request with ID " << id << " canceled successfully.\n";
      return;
    }

    RideRequest *current = requestHead;
    RideRequest *previous = NULL;
    while (requestHead != NULL && requestHead->requestID != id)
    {
      previous = current;
      current = current->next;
    }
    if (isEmpty(current))
    {
      cout << "Ride request with ID " << id << " not found.\n";
      return;
    }
    previous->next = current->next;
    delete current;
    cout << "Ride request with ID " << id << " canceled successfully.\n";
  }
  void displayRideRequests()
  {
    if (isEmpty(requestHead))
    {
      cout << "No current ride requests.\n";
      return;
    }
    cout << "Current Ride Requests:\n";
    RideRequest *temp = requestHead;
    while (temp != NULL)
    {
      cout << "Request ID: " << temp->requestID << ", Customer: " << temp->customerName
           << ", Pickup: " << temp->pickup << ", Dropoff: " << temp->dropoff
           << ", Fare: $" << temp->fare << ", Date: " << temp->date << "\n";
      temp = temp->next;
    }
  }
  void assignRideToDriver(int id, string dName)
  {
    if (isEmpty(requestHead))
    {
      cout << "No ride requests to assign.\n";
      return;
    }

    RideRequest *current = requestHead;
    RideRequest *previous = NULL;

    while (requestHead != NULL && requestHead->requestID != id)
    {
      previous = current;
      current = current->next;
    }
    if (isEmpty(current))
    {
      cout << "Ride request with ID " << id << " not found.\n";
      return;
    }

    ActiveRide *newRide = new ActiveRide();
    newRide->rideID = current->requestID;
    newRide->customerName = current->customerName;
    newRide->driverName = dName;
    newRide->pickup = current->pickup;
    newRide->dropoff = current->dropoff;
    newRide->fare = current->fare;
    newRide->date = current->date;
    newRide->next = NULL;

    if (isEmpty(activeHead))
    {
      activeHead = newRide;
    }
    else
    {
      ActiveRide *temp = activeHead;
      while (temp->next != NULL)
      {
        temp = temp->next;
      }
      temp->next = newRide;
    }

    if (requestHead == current)
    {
      requestHead = requestHead->next;
    }
    else
    {
      RideRequest *prev = requestHead;
      while (prev != current)
      {
        prev = prev->next;
      }
      prev->next = current->next;
    }
    delete current;
    cout << "Ride request with ID " << id << " assigned to driver " << dName << " successfully.\n";
  }
  // ========== Active Ride Functions ==========
  void completeActiveRide(int id, bool completed)
  {
    if (isEmpty(activeHead))
    {
      cout << "No active rides to complete.\n";
      return;
    }

    // Find the active ride
    ActiveRide *current = activeHead;
    ActiveRide *prev = NULL;
    while (current != NULL && current->rideID != id)
    {
      prev = current;
      current = current->next;
    }
    if (isEmpty(current))
    {
      cout << "Active ride with ID " << id << " not found.\n";
      return;
    }
    // Move to Ride History
    RideHistory *newHistory = new RideHistory();
    newHistory->rideID = current->rideID;
    newHistory->customerName = current->customerName;
    newHistory->driverName = current->driverName;
    newHistory->pickup = current->pickup;
    newHistory->dropoff = current->dropoff;
    newHistory->fare = current->fare;
    newHistory->date = current->date;
    newHistory->status = completed ? "Completed" : "Canceled";
    newHistory->next = historyHead;
    historyHead = newHistory;

    // Remove from active rides
    if (isEmpty(prev))
    {
      activeHead = current->next;
    }
    else
    {
      prev->next = current->next;
    }
    delete current;
  }
  void displayActiveRides()
  {
    if (isEmpty(activeHead))
    {
      cout << "No active rides.\n";
      return;
    }
    ActiveRide *temp = activeHead;
    cout << "Active Rides:\n";
    while (temp != NULL)
    {
      cout << "Ride ID: " << temp->rideID
           << ", Customer: " << temp->customerName
           << ", Driver: " << temp->driverName
           << ", Pickup: " << temp->pickup
           << ", Dropoff: " << temp->dropoff
           << ", Fare: $" << temp->fare
           << ", Date: " << temp->date << "\n";
      temp = temp->next;
    }
  }
  void searchActiveRideByCustomer(string cname)
  {
    if (isEmpty(activeHead))
    {
      cout << "No active rides available.\n";
      return;
    }

    ActiveRide *temp = activeHead;
    bool found = false;
    cout << "Active Rides for Customer: " << cname << "\n";
    while (temp != NULL)
    {
      if (temp->customerName == cname)
      {
        found = true;
        cout << "Ride ID: " << temp->rideID
             << ", Driver: " << temp->driverName
             << ", Pickup: " << temp->pickup
             << ", Dropoff: " << temp->dropoff
             << ", Fare: $" << temp->fare
             << ", Date: " << temp->date << "\n";
      }
      temp = temp->next;
    }
    if (!found)
    {
      cout << "No active rides found for customer: " << cname << "\n";
    }
  }
  void totalRevenue()
  {
    if (isEmpty(historyHead))
    {
      cout << "No ride history available to calculate revenue.\n";
      return;
    }
    RideHistory *temp = historyHead;
    float total = 0.0;
    while (temp != NULL)
    {
      if (temp->status == "Completed")
      {
        total += temp->fare;
      }
      temp = temp->next;
    }
    cout << "Total Revenue: $" << total << "\n";
  }

  void sortRideHistoryByFare()
  {
    if (isEmpty(historyHead) || isEmpty(historyHead->next))
    {
      cout << "No rides to sort or only one ride present.\n";
      return;
    }
    bool swaped;
    do
    {
      swaped = false;
      RideHistory *temp = historyHead;
      while (temp != NULL && temp->next != NULL)
      {
        if (temp->fare > temp->next->fare)
        {
          // Swap the rides
          swap(temp->rideID, temp->next->rideID);
          swap(temp->customerName, temp->next->customerName);
          swap(temp->driverName, temp->next->driverName);
          swap(temp->pickup, temp->next->pickup);
          swap(temp->dropoff, temp->next->dropoff);
          swap(temp->fare, temp->next->fare);
          swap(temp->status, temp->next->status);
          swaped = true;
        }
        temp = temp->next;
      }

    } while (swaped);
  }
  void reverseRideHistory()
  {
    if (isEmpty(historyHead) || isEmpty(historyHead->next))
    {
      cout << "No rides to reverse or only one ride present.\n";
      return;
    }

    RideHistory *prev = NULL;
    RideHistory *current = historyHead;
    RideHistory *next = NULL;

    while (current != NULL)
    {
      next = current->next;
      current->next = prev;
      prev = current;
      current = next;
    }
    historyHead = prev;
  }
};