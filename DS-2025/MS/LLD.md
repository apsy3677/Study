## Microsoft LLD Solutions (Class Designs + Core Code)

Designed for a 10+ YOE interview: clear requirements, extensible class design, and working code for critical components. Language: C++ (Java only where noted).

### Alert Monitoring System
Requirements
- Sensors publish readings (temperature, pressure, etc.). Each has lower/upper thresholds.
- When readings go out of range, create an alert; users can acknowledge/resolve.
- Discuss push (sensor -> queue) vs pull (system polls sensors).

Key Design Choices
- Use push via a message queue for decoupling and scalability; support polling adapter if needed.
- Alert state machine: OPEN -> ACKNOWLEDGED -> RESOLVED.
- Persistence for alerts; idempotency on duplicate sensor messages.

Class Design
- `Sensor` (interface), `TemperatureSensor`, `PressureSensor`
- `SensorData` (immutable reading)
- `Alert`, `AlertStatus`
- `AlertMonitoringService` (core logic), `AlertRepository` (persistence)
- `MessageBus` (interface) to abstract queue (Kafka/Service Bus)

```cpp
#include <string>
#include <memory>
#include <chrono>
using namespace std;

// Domain
enum class AlertStatus { OPEN, ACKNOWLEDGED, RESOLVED };

struct SensorData {
    string sensorId;
    string type; // e.g., "TEMP", "PRESSURE"
    double value;
    long long timestampEpochMs;
    double lowThreshold;
    double highThreshold;
    bool isOutOfRange() const { return value < lowThreshold || value > highThreshold; }
};

class Alert {
    string alertId;
    string sensorId;
    string type;
    double value;
    long long createdAt;
    AlertStatus status;
public:
    Alert(string id, string sid, string t, double v, long long ts)
        : alertId(move(id)), sensorId(move(sid)), type(move(t)), value(v), createdAt(ts), status(AlertStatus::OPEN) {}
    void acknowledge() { if (status == AlertStatus::OPEN) status = AlertStatus::ACKNOWLEDGED; }
    void resolve() { status = AlertStatus::RESOLVED; }
    const string& getSensorId() const { return sensorId; }
};

// Ports
struct AlertRepository {
    virtual ~AlertRepository() = default;
    virtual void save(const Alert& alert) = 0;
    virtual unique_ptr<Alert> findOpenBySensorId(const string& sensorId) = 0;
};

struct MessageBus {
    virtual ~MessageBus() = default;
    virtual void publish(const string& topic, const SensorData& data) = 0;
};

// Application service
class AlertMonitoringService {
    AlertRepository& repo;
    static string generateId() {
        return to_string(chrono::steady_clock::now().time_since_epoch().count());
    }
public:
    explicit AlertMonitoringService(AlertRepository& repo) : repo(repo) {}
    void onSensorData(const SensorData& data) {
        if (!data.isOutOfRange()) return;
        auto existing = repo.findOpenBySensorId(data.sensorId);
        if (!existing) {
            long long nowMs = chrono::duration_cast<chrono::milliseconds>(
                chrono::system_clock::now().time_since_epoch()).count();
            Alert alert(generateId(), data.sensorId, data.type, data.value, nowMs);
            repo.save(alert);
        }
    }
};
```

Notes
- To support polling, add a `SensorGateway` that reads current values and converts to `SensorData` messages periodically.
- For scale, run multiple consumers; ensure one open alert per sensor via unique constraint or compare-and-set.

### Multi-level EV Charging Station
Requirements
- Multiple levels, each with multiple chargers; vehicles arrive with connector type and power needs.
- Schedule vehicles to slots, track sessions, pricing, and payments.

Class Design
- `ChargingStation` aggregates `Level` -> `Charger` -> `Slot`
- `Vehicle`, `ChargingSession`, `PricingStrategy`, `SchedulingStrategy`

```cpp
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

class Vehicle {
    string id;
    string connectorType;
public:
    Vehicle(string id, string connector) : id(move(id)), connectorType(move(connector)) {}
    const string& getId() const { return id; }
    const string& getConnectorType() const { return connectorType; }
};

class Charger {
    string id;
    string connectorType; // CCS, CHAdeMO, Type2
    int maxKw;
    bool occupied{false};
public:
    Charger(string id, string connector, int maxKw)
        : id(move(id)), connectorType(move(connector)), maxKw(maxKw) {}
    bool canServe(const string& connector) const { return !occupied && connectorType == connector; }
    void setOccupied(bool v) { occupied = v; }
    int getMaxKw() const { return maxKw; }
    const string& getId() const { return id; }
};

struct SchedulingStrategy {
    virtual ~SchedulingStrategy() = default;
    virtual Charger* selectCharger(vector<Charger>& chargers, const Vehicle& v) = 0;
};

struct FastestAvailableStrategy : SchedulingStrategy {
    Charger* selectCharger(vector<Charger>& chargers, const Vehicle& v) override {
        Charger* best = nullptr;
        for (auto& c : chargers) {
            if (c.canServe(v.getConnectorType()) && (!best || c.getMaxKw() > best->getMaxKw())) {
                best = &c;
            }
        }
        return best;
    }
};

struct ChargingSession {
    string vehicleId;
    string chargerId;
    long long startedAtMs;
};

class ChargingService {
    SchedulingStrategy& strategy;
public:
    explicit ChargingService(SchedulingStrategy& s) : strategy(s) {}
    ChargingSession startSession(vector<Charger>& chargers, const Vehicle& v) {
        Charger* chosen = strategy.selectCharger(chargers, v);
        if (!chosen) throw runtime_error("No charger available");
        chosen->setOccupied(true);
        long long nowMs = chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()).count();
        return {v.getId(), chosen->getId(), nowMs};
    }
};
```

Extensibility: Add queueing and fairness via priority queues per connector. Payments via Strategy pattern.

### Chess Game
Requirements
- Support standard chess, clear separation of rules per piece, move validation, and game state.

Class Design
- `Board` (8x8 `Cell`), `Piece` (abstract) -> `King`, `Queen`, ...
- `Move`, `Player`, `Game`

```cpp
#include <cstdlib>

struct Cell {
    int x, y;
    bool isEmpty;
    bool targetIsWhite; // simplified for capture rule demo
};

class Board { /* omitted */ };

class Piece {
protected:
    bool white;
public:
    explicit Piece(bool white) : white(white) {}
    virtual ~Piece() = default;
    virtual bool isValidMove(const Board& board, const Cell& from, const Cell& to) const = 0;
};

class Knight : public Piece {
public:
    explicit Knight(bool white) : Piece(white) {}
    bool isValidMove(const Board&, const Cell& from, const Cell& to) const override {
        int dx = abs(from.x - to.x);
        int dy = abs(from.y - to.y);
        if (!((dx == 1 && dy == 2) || (dx == 2 && dy == 1))) return false;
        return to.isEmpty || to.targetIsWhite != this->white;
    }
};
```

Notes: Use composition for move generation and validators to keep pieces simple.

### Rate Limiter (LLD)
Implement Token Bucket as reusable component. Thread-safe, monotonic time.

```cpp
#include <mutex>
#include <chrono>
using namespace std;

class TokenBucketRateLimiter {
    double capacity;
    double refillPerSec;
    double tokens;
    chrono::steady_clock::time_point lastRefill;
    mutex mu;
    void refillLocked() {
        auto now = chrono::steady_clock::now();
        chrono::duration<double> delta = now - lastRefill;
        tokens = min(capacity, tokens + delta.count() * refillPerSec);
        lastRefill = now;
    }
public:
    TokenBucketRateLimiter(double capacity, double refillPerSec)
        : capacity(capacity), refillPerSec(refillPerSec), tokens(capacity),
          lastRefill(chrono::steady_clock::now()) {}
    bool allow() {
        lock_guard<mutex> lock(mu);
        refillLocked();
        if (tokens >= 1.0) { tokens -= 1.0; return true; }
        return false;
    }
};
```

### Useful Design Patterns
- Factory: object creation by type (`SensorFactory`, `PieceFactory`).
- Strategy: pluggable algorithms (`SchedulingStrategy`, `PricingStrategy`).
- Observer: event subscriptions (alert subscribers, UI updates).
- Repository: persistence abstraction (`AlertRepository`).


