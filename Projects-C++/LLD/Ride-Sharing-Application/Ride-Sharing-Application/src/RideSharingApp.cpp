#include<iostream>
#include <vector>
using namespace std;


enum RideStatus {
	IDLE,
	CREATED,
	WITHDRAWN,
	COMPLETED
};

class Ride {
public:
	Ride(int id, int origin, int dest, int seats, RideStatus ride_status)
		: id(id),
		  origin(origin),
		  dest(dest),
		  seats(seats),
		  rideStatus(ride_status)
	{
	}
	Ride()
	{
		id = 0;
		origin = 0;
		dest = 0;
		seats = 0;
		rideStatus = IDLE;
	}
	int calculateFare(bool preferredCustomer)
	{
		int dist = (dest-origin);
		if(seats <2)
		{
			return dist * AMT_PER_KM * (preferredCustomer ? 0.75 : 1);
		}
		return dist * AMT_PER_KM * (0.75);
	}
public:
	static const int AMT_PER_KM = 20;
	int id = 0;
	int origin, dest;
	int seats;
	RideStatus rideStatus;
};

class Person{
public:
	string name;
};

class Driver : private Person{
public:
	Driver(string name) {
		this->name = name;
	}
};

class Rider : private Person{
private:
	vector<Ride> completedRides;
	Ride currRide;
public:
	Rider(string name)
	{
		this->name = name;
	}
	void createRide(int id, int origin, int dest, int seats)
	{
		if(origin >= dest)
		{
			cout << "Wrong Values of Origin and Destination";
			return;
		}
		currRide.id = id;
		currRide.origin = origin;
		currRide.dest = dest;
		currRide.seats = seats;
		currRide.rideStatus = RideStatus::CREATED;
	}
	void updateRide(int id, int origin, int dest, int seats)
	{
		if(currRide.rideStatus == RideStatus::WITHDRAWN)
		{
			cout << "can't Update a Widthdrwan Ride";
			return;
		}
		if(currRide.rideStatus == RideStatus::COMPLETED)
		{
			cout << "can't Update a COMPLETED Ride";
			return;
		}
		createRide(id, origin, dest, seats);
	}
	void widthDrawRide(int id)
	{
		if(currRide.id != id)
		{
			cout << "Wrong ID Input" << endl;
			return;
		}
		if (currRide.rideStatus != RideStatus::CREATED)
		{
			cout << "can't Withdraw a Ride which is not in progress";
			return;
		}
		currRide.rideStatus = RideStatus::WITHDRAWN;
	}
	int closeRide()
	{
		if(currRide.rideStatus == RideStatus::CREATED)
		{
			
			currRide.rideStatus = RideStatus::COMPLETED;
			completedRides.push_back(currRide);
			int fare = currRide.calculateFare(completedRides.size() >= 10);
			return fare;
		}
		cout << "Ride is not in Progress, Can't calculate Fare" << endl;
		return -1;
	}
};

int main() {
	cout << "Ride Sharing App" << endl;

	Rider rider("R1");
	Driver driver("D1");

	rider.createRide(1, 50, 100, 1);
	cout << rider.closeRide() << endl;

	rider.updateRide(1, 50, 100, 2);
	cout << rider.closeRide() << endl;

	rider.createRide(1, 50, 100, 1);
	rider.widthDrawRide(1);

	rider.updateRide(1, 50, 100, 2);
	cout << rider.closeRide() << endl;

	return 0;
}