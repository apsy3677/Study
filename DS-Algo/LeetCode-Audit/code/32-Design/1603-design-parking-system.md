# 1603. Design Parking System

[Problem](https://leetcode.com/problems/design-parking-system/) · Easy · Design → Counters

LeetCode tags: design, simulation, counting

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-30 13:58 IST · Accepted · C++

[submission 924700966](https://leetcode.com/submissions/detail/924700966/) · tests 102/102 · runtime 88 ms (beats 5.0%)

```cpp
class Parking{
    public:
    virtual bool spotAvailable() = 0;
};

class BigCarParking : public Parking{
    int capacity;
    priority_queue<int> bigCars;
    public:
    BigCarParking(int _capacity){
        this->capacity = _capacity;
        // fill queue with capacity spots
        for(int spot =0; spot<capacity; spot++){
            bigCars.push(spot);
        }
    }
    bool spotAvailable(){
        return bigCars.size() > 0;
    }
    bool addSpot(){
        if(this->spotAvailable()){
            bigCars.pop();
            return true;
        }
        return false;
    }
};

class MediumCarParking: public Parking{
    int capacity;
    priority_queue<int> mediumCars;
    public:
    MediumCarParking(int _capacity){
        this->capacity = _capacity;
        // fill queue with capacity spots
        for(int spot =0; spot<capacity; spot++){
            mediumCars.push(spot);
        }
    }
    bool spotAvailable(){
        return mediumCars.size() > 0;
    }
    bool addSpot(){
        if(this->spotAvailable()){
            mediumCars.pop();
            return true;
        }
        return false;
    }

};

class SmallCarParking: public Parking{
    int capacity;
    priority_queue<int> smallCars;

    public:
    SmallCarParking(int _capacity){
        this->capacity = _capacity;
        // fill queue with capacity spots
        for(int spot = 0; spot<capacity; spot++){
            smallCars.push(spot);
        }
    }
    bool spotAvailable(){
        return smallCars.size() > 0;
    }
    bool addSpot(){
        if(this->spotAvailable()){
            smallCars.pop();
            return true;
        }
        return false;
    }
};

class ParkingSystem {
    BigCarParking *bigCarParking;
    SmallCarParking *smallCarParking;
    MediumCarParking *mediumCarParking;

public:
    ParkingSystem(int big, int medium, int small) {
        // initialze Parking Spots
        bigCarParking = new BigCarParking(big);
        mediumCarParking = new MediumCarParking(medium);
        smallCarParking = new SmallCarParking(small);
    }
    
    bool addCar(int carType) {
        
        switch(carType){
            case 1:
            return bigCarParking->addSpot();
            break;
            case 2:
            return mediumCarParking->addSpot();
            break;
            case 3:
            return smallCarParking->addSpot();
            break;
        }
        return false;

    }
};

/**
 * Your ParkingSystem object will be instantiated and called as such:
 * ParkingSystem* obj = new ParkingSystem(big, medium, small);
 * bool param_1 = obj->addCar(carType);
 */
```
