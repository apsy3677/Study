# Adobe C++ Interview: Design Patterns for Senior Developers (10+ Years Experience)

## Core Design Patterns for Adobe Products

### 1. Singleton Pattern - Logger System for Creative Suite

**Adobe Context**: Unified logging across Photoshop, Illustrator, and InDesign applications.

#### Basic Thread-Safe Implementation
```cpp
#include <mutex>
#include <memory>
#include <string>
#include <fstream>

class Logger {
private:
    static std::unique_ptr<Logger> instance;
    static std::mutex mutex_;
    std::ofstream logFile;
    
    // Private constructor
    Logger() {
        logFile.open("adobe_creative_suite.log", std::ios::app);
    }
    
public:
    // Thread-safe getInstance method
    static Logger* getInstance() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (instance == nullptr) {
            instance = std::make_unique<Logger>();
        }
        return instance.get();
    }
    
    void log(const std::string& level, const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex_);
        logFile << "[" << level << "] " << message << std::endl;
    }
    
    // Prevent copying
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};

// Static member definitions
std::unique_ptr<Logger> Logger::instance = nullptr;
std::mutex Logger::mutex_;
```

#### Better Implementations for Senior Interview

**1. Meyers' Singleton (Recommended for Adobe)**
```cpp
class ModernLogger {
public:
    static ModernLogger& getInstance() {
        static ModernLogger instance; // Thread-safe since C++11
        return instance;
    }
    
    void log(const std::string& level, const std::string& message) {
        std::lock_guard<std::mutex> lock(logMutex_);
        // Implementation
    }
    
private:
    ModernLogger() = default;
    mutable std::mutex logMutex_;
    
    // Prevent copying
    ModernLogger(const ModernLogger&) = delete;
    ModernLogger& operator=(const ModernLogger&) = delete;
};
```

**2. Double-Checked Locking (Classic but Problematic)**
```cpp
class DCLLogger {
private:
    static std::atomic<DCLLogger*> instance;
    static std::mutex mutex_;
    
public:
    static DCLLogger* getInstance() {
        DCLLogger* tmp = instance.load(std::memory_order_acquire);
        if (tmp == nullptr) {
            std::lock_guard<std::mutex> lock(mutex_);
            tmp = instance.load(std::memory_order_relaxed);
            if (tmp == nullptr) {
                tmp = new DCLLogger();
                instance.store(tmp, std::memory_order_release);
            }
        }
        return tmp;
    }
};
```

**3. Call-Once Implementation (Production Quality)**
```cpp
class CallOnceLogger {
private:
    static std::unique_ptr<CallOnceLogger> instance;
    static std::once_flag onceFlag;
    
    static void createInstance() {
        instance = std::make_unique<CallOnceLogger>();
    }
    
public:
    static CallOnceLogger* getInstance() {
        std::call_once(onceFlag, createInstance);
        return instance.get();
    }
};
```

### 2. Factory Pattern - Plugin Architecture for Creative Suite

**Adobe Context**: Loading different file format handlers (JPEG, PNG, PSD, AI) dynamically.

```cpp
#include <memory>
#include <unordered_map>
#include <functional>

// Abstract product
class ImageProcessor {
public:
    virtual ~ImageProcessor() = default;
    virtual void process(const std::string& filename) = 0;
    virtual std::string getFormat() const = 0;
};

// Concrete products
class JPEGProcessor : public ImageProcessor {
public:
    void process(const std::string& filename) override {
        // JPEG-specific processing with Adobe's color management
        std::cout << "Processing JPEG with Adobe RGB color profile: " << filename << std::endl;
    }
    std::string getFormat() const override { return "JPEG"; }
};

class PSDProcessor : public ImageProcessor {
public:
    void process(const std::string& filename) override {
        // PSD layer processing
        std::cout << "Processing PSD layers and blend modes: " << filename << std::endl;
    }
    std::string getFormat() const override { return "PSD"; }
};

// Modern Factory with registration
class ImageProcessorFactory {
private:
    using CreatorFunc = std::function<std::unique_ptr<ImageProcessor>()>;
    std::unordered_map<std::string, CreatorFunc> creators;
    
public:
    template<typename T>
    void registerProcessor(const std::string& format) {
        creators[format] = []() { return std::make_unique<T>(); };
    }
    
    std::unique_ptr<ImageProcessor> createProcessor(const std::string& format) {
        auto it = creators.find(format);
        if (it != creators.end()) {
            return it->second();
        }
        throw std::runtime_error("Unsupported format: " + format);
    }
    
    // Singleton access for global registration
    static ImageProcessorFactory& getInstance() {
        static ImageProcessorFactory instance;
        return instance;
    }
};

// Usage in Adobe application startup
void initializeProcessors() {
    auto& factory = ImageProcessorFactory::getInstance();
    factory.registerProcessor<JPEGProcessor>("JPEG");
    factory.registerProcessor<PSDProcessor>("PSD");
}
```

### 3. Observer Pattern - Document-View Architecture

**Adobe Context**: Multiple panels updating when a document changes in Photoshop.

```cpp
#include <vector>
#include <memory>
#include <algorithm>

// Observer interface
class DocumentObserver {
public:
    virtual ~DocumentObserver() = default;
    virtual void onDocumentChanged(const std::string& changeType) = 0;
    virtual void onLayerAdded(int layerId) = 0;
    virtual void onLayerDeleted(int layerId) = 0;
};

// Subject (Document)
class PhotoshopDocument {
private:
    std::vector<std::weak_ptr<DocumentObserver>> observers;
    std::string documentName;
    std::vector<int> layers;
    
public:
    PhotoshopDocument(const std::string& name) : documentName(name) {}
    
    void addObserver(std::shared_ptr<DocumentObserver> observer) {
        observers.push_back(observer);
    }
    
    void removeObserver(std::shared_ptr<DocumentObserver> observer) {
        observers.erase(
            std::remove_if(observers.begin(), observers.end(),
                [&](const std::weak_ptr<DocumentObserver>& weak_obs) {
                    return weak_obs.expired() || weak_obs.lock() == observer;
                }),
            observers.end()
        );
    }
    
    void addLayer() {
        int layerId = layers.size() + 1;
        layers.push_back(layerId);
        notifyLayerAdded(layerId);
    }
    
    void deleteLayer(int layerId) {
        auto it = std::find(layers.begin(), layers.end(), layerId);
        if (it != layers.end()) {
            layers.erase(it);
            notifyLayerDeleted(layerId);
        }
    }
    
    void modifyDocument(const std::string& changeType) {
        // Document modification logic
        notifyDocumentChanged(changeType);
    }
    
private:
    void notifyDocumentChanged(const std::string& changeType) {
        cleanupExpiredObservers();
        for (auto& weak_obs : observers) {
            if (auto obs = weak_obs.lock()) {
                obs->onDocumentChanged(changeType);
            }
        }
    }
    
    void notifyLayerAdded(int layerId) {
        cleanupExpiredObservers();
        for (auto& weak_obs : observers) {
            if (auto obs = weak_obs.lock()) {
                obs->onLayerAdded(layerId);
            }
        }
    }
    
    void notifyLayerDeleted(int layerId) {
        cleanupExpiredObservers();
        for (auto& weak_obs : observers) {
            if (auto obs = weak_obs.lock()) {
                obs->onLayerDeleted(layerId);
            }
        }
    }
    
    void cleanupExpiredObservers() {
        observers.erase(
            std::remove_if(observers.begin(), observers.end(),
                [](const std::weak_ptr<DocumentObserver>& weak_obs) {
                    return weak_obs.expired();
                }),
            observers.end()
        );
    }
};

// Concrete observers (UI panels)
class LayersPanel : public DocumentObserver {
private:
    std::string panelName;
    
public:
    LayersPanel(const std::string& name) : panelName(name) {}
    
    void onDocumentChanged(const std::string& changeType) override {
        std::cout << panelName << " updating for document change: " << changeType << std::endl;
    }
    
    void onLayerAdded(int layerId) override {
        std::cout << panelName << " adding layer " << layerId << " to UI" << std::endl;
    }
    
    void onLayerDeleted(int layerId) override {
        std::cout << panelName << " removing layer " << layerId << " from UI" << std::endl;
    }
};

class HistoryPanel : public DocumentObserver {
public:
    void onDocumentChanged(const std::string& changeType) override {
        std::cout << "History Panel: Recording action - " << changeType << std::endl;
    }
    
    void onLayerAdded(int layerId) override {
        std::cout << "History Panel: Added layer " << layerId << std::endl;
    }
    
    void onLayerDeleted(int layerId) override {
        std::cout << "History Panel: Deleted layer " << layerId << std::endl;
    }
};
```

### 4. Strategy Pattern - Compression Algorithms

**Adobe Context**: Different compression strategies for saving files in various formats.

```cpp
#include <memory>
#include <vector>

// Strategy interface
class CompressionStrategy {
public:
    virtual ~CompressionStrategy() = default;
    virtual std::vector<uint8_t> compress(const std::vector<uint8_t>& data) = 0;
    virtual std::vector<uint8_t> decompress(const std::vector<uint8_t>& data) = 0;
    virtual std::string getAlgorithmName() const = 0;
    virtual double getCompressionRatio() const = 0;
};

// Concrete strategies
class LZWCompression : public CompressionStrategy {
public:
    std::vector<uint8_t> compress(const std::vector<uint8_t>& data) override {
        // LZW compression implementation for TIFF files
        std::cout << "Compressing with LZW (TIFF format)" << std::endl;
        // Simplified - return data with simulated compression
        return std::vector<uint8_t>(data.begin(), data.begin() + data.size() / 2);
    }
    
    std::vector<uint8_t> decompress(const std::vector<uint8_t>& data) override {
        // LZW decompression
        std::cout << "Decompressing LZW data" << std::endl;
        return data; // Simplified
    }
    
    std::string getAlgorithmName() const override { return "LZW"; }
    double getCompressionRatio() const override { return 0.6; }
};

class JPEGCompression : public CompressionStrategy {
private:
    int quality;
    
public:
    JPEGCompression(int q = 85) : quality(q) {}
    
    std::vector<uint8_t> compress(const std::vector<uint8_t>& data) override {
        std::cout << "Compressing with JPEG, quality: " << quality << std::endl;
        // JPEG DCT compression
        return std::vector<uint8_t>(data.begin(), data.begin() + data.size() / 3);
    }
    
    std::vector<uint8_t> decompress(const std::vector<uint8_t>& data) override {
        std::cout << "Decompressing JPEG data" << std::endl;
        return data;
    }
    
    std::string getAlgorithmName() const override { return "JPEG"; }
    double getCompressionRatio() const override { return 0.1 + (quality / 100.0) * 0.4; }
};

class LosslessCompression : public CompressionStrategy {
public:
    std::vector<uint8_t> compress(const std::vector<uint8_t>& data) override {
        std::cout << "Compressing with PNG lossless compression" << std::endl;
        return std::vector<uint8_t>(data.begin(), data.begin() + data.size() * 0.8);
    }
    
    std::vector<uint8_t> decompress(const std::vector<uint8_t>& data) override {
        std::cout << "Decompressing PNG data" << std::endl;
        return data;
    }
    
    std::string getAlgorithmName() const override { return "PNG Lossless"; }
    double getCompressionRatio() const override { return 0.8; }
};

// Context class
class ImageExporter {
private:
    std::unique_ptr<CompressionStrategy> compressionStrategy;
    std::string exportFormat;
    
public:
    ImageExporter(std::unique_ptr<CompressionStrategy> strategy, const std::string& format)
        : compressionStrategy(std::move(strategy)), exportFormat(format) {}
    
    void setCompressionStrategy(std::unique_ptr<CompressionStrategy> strategy) {
        compressionStrategy = std::move(strategy);
    }
    
    void exportImage(const std::vector<uint8_t>& imageData, const std::string& filename) {
        std::cout << "Exporting to " << exportFormat << " format" << std::endl;
        
        auto compressedData = compressionStrategy->compress(imageData);
        
        std::cout << "Original size: " << imageData.size() << " bytes" << std::endl;
        std::cout << "Compressed size: " << compressedData.size() << " bytes" << std::endl;
        std::cout << "Compression ratio: " << compressionStrategy->getCompressionRatio() << std::endl;
        std::cout << "Algorithm: " << compressionStrategy->getAlgorithmName() << std::endl;
        
        // Write to file (simplified)
        std::cout << "Saved as: " << filename << std::endl;
    }
};

// Factory for compression strategies
class CompressionFactory {
public:
    static std::unique_ptr<CompressionStrategy> createStrategy(const std::string& format, int quality = 85) {
        if (format == "TIFF") {
            return std::make_unique<LZWCompression>();
        } else if (format == "JPEG") {
            return std::make_unique<JPEGCompression>(quality);
        } else if (format == "PNG") {
            return std::make_unique<LosslessCompression>();
        }
        throw std::runtime_error("Unsupported compression format: " + format);
    }
};
```

### 5. Publish-Subscribe Pattern - Event System for Adobe Creative Suite

## What is Publish-Subscribe (Pub-Sub)?

**Publish-Subscribe** is a messaging pattern where:
- **Publishers** send messages without knowing who will receive them
- **Subscribers** receive messages they're interested in without knowing who sent them
- A **Message Broker/Event Bus** acts as the intermediary

**Real-world analogy**: Like subscribing to a YouTube channel. You (subscriber) get notified when your favorite creator (publisher) uploads a video, but the creator doesn't know you personally.

## Adobe Context & Requirements

**Scenario**: In Photoshop, when a user changes a layer:
- The **Layers Panel** needs to update the UI
- The **History Panel** needs to record the action  
- The **Properties Panel** needs to show new layer properties
- **Cloud Sync** might need to save the change

**Without Pub-Sub**: The layer modification code would need to directly call all these components - tight coupling!

**With Pub-Sub**: Layer modification just publishes a "LayerChanged" event, and interested panels subscribe to it.

## Step-by-Step Design Process

### Step 1: Basic Requirements
```
1. Publishers can send events without knowing subscribers
2. Subscribers can listen to events without knowing publishers  
3. Multiple subscribers can listen to the same event type
4. Easy to add/remove subscribers at runtime
5. Type-safe (compile-time error prevention)
```

### Step 2: What Are We Building?
We're building an **Event Bus** for Adobe Creative Suite that handles:
- Document operations (open, save, close)
- Layer modifications (add, delete, modify)
- Tool changes (brush selected, zoom changed)
- Cross-panel communication

### Step 3: Simple Implementation (Step by Step)

#### Step 3.1: Basic Event Structure
```cpp
#include <string>
#include <iostream>

// Simple event - just a message
struct Event {
    std::string type;
    std::string data;
    
    Event(const std::string& t, const std::string& d) 
        : type(t), data(d) {}
};

// Example events
Event layerChanged("LayerChanged", "Layer1:opacity=50%");
Event documentOpened("DocumentOpened", "/path/to/file.psd");
```

#### Step 3.2: Basic Subscriber Interface
```cpp
// What every subscriber must implement
class Subscriber {
public:
    virtual ~Subscriber() = default;
    virtual void onEvent(const Event& event) = 0;
    virtual std::string getName() const = 0;
};

// Example subscriber
class LayersPanel : public Subscriber {
public:
    void onEvent(const Event& event) override {
        if (event.type == "LayerChanged") {
            std::cout << "[LayersPanel] Updating UI for: " << event.data << std::endl;
        }
    }
    
    std::string getName() const override { 
        return "LayersPanel"; 
    }
};
```

#### Step 3.3: Simple Event Bus (Raw Pointers First)
```cpp
#include <vector>
#include <unordered_map>

class SimpleEventBus {
private:
    // Map: event_type -> list_of_subscribers
    std::unordered_map<std::string, std::vector<Subscriber*>> subscribers;
    
public:
    // Subscribe to an event type
    void subscribe(const std::string& eventType, Subscriber* subscriber) {
        subscribers[eventType].push_back(subscriber);
    }
    
    // Publish an event to all subscribers
    void publish(const Event& event) {
        auto it = subscribers.find(event.type);
        if (it != subscribers.end()) {
            for (Subscriber* sub : it->second) {
                sub->onEvent(event);
            }
        }
    }
};
```

### Step 4: Why Raw Pointers Are Problematic

**Problem 1: Dangling Pointers**
```cpp
{
    LayersPanel panel;
    eventBus.subscribe("LayerChanged", &panel);
}  // panel destroyed here, but eventBus still has its address!

eventBus.publish(Event("LayerChanged", "data")); // CRASH! Dangling pointer
```

**Problem 2: Memory Management Confusion**
- Who owns the subscriber objects?
- Who's responsible for cleanup?
- What if subscriber is deleted but not unsubscribed?

### Step 5: Smart Pointer Solutions

#### Option 1: shared_ptr (Ownership Sharing)
```cpp
#include <memory>

class EventBus {
private:
    std::unordered_map<std::string, std::vector<std::shared_ptr<Subscriber>>> subscribers;
    
public:
    void subscribe(const std::string& eventType, std::shared_ptr<Subscriber> subscriber) {
        subscribers[eventType].push_back(subscriber);
    }
    
    void publish(const Event& event) {
        auto it = subscribers.find(event.type);
        if (it != subscribers.end()) {
            for (auto& sub : it->second) {
                sub->onEvent(event);
            }
        }
    }
};

// Usage
auto panel = std::make_shared<LayersPanel>();
eventBus.subscribe("LayerChanged", panel);
// Safe: panel won't be destroyed while eventBus holds reference
```

**Pros**: Simple, safe
**Cons**: EventBus keeps objects alive even when you don't want them

#### Option 2: weak_ptr (Preferred for Pub-Sub)
```cpp
class EventBus {
private:
    std::unordered_map<std::string, std::vector<std::weak_ptr<Subscriber>>> subscribers;
    
public:
    void subscribe(const std::string& eventType, std::shared_ptr<Subscriber> subscriber) {
        subscribers[eventType].push_back(subscriber);
    }
    
    void publish(const Event& event) {
        auto it = subscribers.find(event.type);
        if (it != subscribers.end()) {
            for (auto& weak_sub : it->second) {
                if (auto sub = weak_sub.lock()) {  // Check if still alive
                    sub->onEvent(event);
                }
            }
        }
    }
};

// Usage
auto panel = std::make_shared<LayersPanel>();
eventBus.subscribe("LayerChanged", panel);
panel.reset(); // Panel destroyed, eventBus automatically handles cleanup
```

**Pros**: Automatic cleanup, no dangling pointers, doesn't keep objects alive
**Cons**: Slightly more complex

### Step 6: Why weak_ptr is Perfect for Pub-Sub

1. **Natural Lifecycle**: Subscribers control their own lifetime
2. **Automatic Cleanup**: No manual unsubscribe needed  
3. **No Circular Dependencies**: EventBus doesn't own subscribers
4. **Performance**: Failed lock() calls are fast

Let's continue building from here! Should we add thread safety next, or work on type safety with templates?

## Advanced Interview Topics

### Memory Management in Adobe Products - Deep Dive

## Why Memory Management is Critical for Adobe

**Adobe's Challenge**: Processing 8K images, 4GB+ PSD files, real-time video editing
- **Photoshop**: May need 32GB+ RAM for large documents
- **After Effects**: Processes gigabytes of video frames per second
- **Premiere Pro**: Handles multiple 4K video streams simultaneously

## Step 1: Basic C++ Memory Problems

### Problem 1: Memory Leaks
```cpp
// BAD: Classic memory leak
class ImageProcessor {
public:
    void processImage(const std::string& filename) {
        uint8_t* imageData = new uint8_t[1024 * 1024 * 100]; // 100MB allocation
        
        // Process image...
        if (someErrorCondition) {
            return; // LEAK! Never called delete[]
        }
        
        delete[] imageData; // Only reached if no error
    }
};
```

**Impact**: In Adobe products, this could leak 100MB per image operation!

### Problem 2: Dangling Pointers
```cpp
// BAD: Dangling pointer scenario
class LayerManager {
private:
    Layer* activeLayer;
    
public:
    void setActiveLayer(Layer* layer) {
        activeLayer = layer;
    }
    
    void processActiveLayer() {
        activeLayer->applyFilter(); // CRASH if layer was deleted elsewhere!
    }
};
```

### Problem 3: Double Delete
```cpp
// BAD: Double deletion
class DocumentManager {
private:
    Layer* layer;
    
public:
    ~DocumentManager() {
        delete layer; // First deletion
    }
    
    void cleanup() {
        delete layer; // CRASH! Double deletion
        layer = nullptr;
    }
};
```

## Step 2: Modern C++ Solutions

### Solution 1: RAII (Resource Acquisition Is Initialization)
```cpp
// GOOD: RAII with smart pointers
class ImageProcessor {
public:
    void processImage(const std::string& filename) {
        // Automatic cleanup even with exceptions
        auto imageData = std::make_unique<uint8_t[]>(1024 * 1024 * 100);
        
        // Process image...
        if (someErrorCondition) {
            return; // No leak! unique_ptr automatically cleans up
        }
        
        // imageData automatically cleaned up when going out of scope
    }
};
```

### Solution 2: Smart Pointer Hierarchy
```cpp
// GOOD: Clear ownership with smart pointers
class LayerManager {
private:
    std::weak_ptr<Layer> activeLayer; // Non-owning reference
    
public:
    void setActiveLayer(std::shared_ptr<Layer> layer) {
        activeLayer = layer;
    }
    
    void processActiveLayer() {
        if (auto layer = activeLayer.lock()) { // Safe check
            layer->applyFilter();
        }
        // If layer was deleted, just silently skip
    }
};
```

## Step 3: Adobe-Scale Memory Challenges

### Challenge 1: Large Image Processing
```cpp
// Adobe's real-world challenge: Processing massive images
class PhotoshopDocument {
private:
    struct ImageLayer {
        std::unique_ptr<uint8_t[]> pixelData;
        size_t width, height, channels;
        size_t dataSize;
        
        ImageLayer(size_t w, size_t h, size_t c) 
            : width(w), height(h), channels(c) {
            dataSize = width * height * channels * sizeof(uint32_t); // 4 bytes per pixel
            
            if (dataSize > 2'000'000'000) { // 2GB limit check
                throw std::runtime_error("Image too large for single allocation");
            }
            
            pixelData = std::make_unique<uint8_t[]>(dataSize);
        }
    };
    
    std::vector<std::unique_ptr<ImageLayer>> layers;
    
public:
    void addLayer(size_t width, size_t height, size_t channels = 4) {
        try {
            layers.push_back(std::make_unique<ImageLayer>(width, height, channels));
        } catch (const std::bad_alloc& e) {
            // Handle out of memory gracefully
            throw std::runtime_error("Insufficient memory for new layer");
        }
    }
    
    size_t getTotalMemoryUsage() const {
        size_t total = 0;
        for (const auto& layer : layers) {
            total += layer->dataSize;
        }
        return total;
    }
};
```

### Challenge 2: Memory Fragmentation
```cpp
// Problem: Frequent allocations cause fragmentation
void badAllocationPattern() {
    for (int i = 0; i < 1000; ++i) {
        auto small = std::make_unique<uint8_t[]>(1024);     // 1KB
        auto large = std::make_unique<uint8_t[]>(1024*1024); // 1MB
        // Creates fragmented memory pattern
    }
}
```

## Step 4: Custom Memory Management Solutions

### Solution 1: Memory Pool for Frequent Allocations
```cpp
// Adobe-style memory pool implementation
class ImageMemoryPool {
private:
    struct Block {
        void* memory;
        size_t size;
        bool inUse;
        std::chrono::steady_clock::time_point lastUsed;
        
        Block(size_t s) : size(s), inUse(false) {
            memory = std::aligned_alloc(64, s); // 64-byte aligned for SIMD
            if (!memory) throw std::bad_alloc();
            lastUsed = std::chrono::steady_clock::now();
        }
        
        ~Block() {
            std::free(memory);
        }
    };
    
    std::vector<std::unique_ptr<Block>> blocks;
    std::mutex poolMutex;
    
    // Common sizes for Adobe operations
    static constexpr size_t COMMON_SIZES[] = {
        1024 * 1024,      // 1MB - thumbnail
        4 * 1024 * 1024,  // 4MB - small image layer
        64 * 1024 * 1024, // 64MB - medium layer
        256 * 1024 * 1024 // 256MB - large layer
    };
    
public:
    void* allocate(size_t size) {
        std::lock_guard<std::mutex> lock(poolMutex);
        
        // Find exact size match first (fastest)
        for (auto& block : blocks) {
            if (!block->inUse && block->size == size) {
                block->inUse = true;
                block->lastUsed = std::chrono::steady_clock::now();
                return block->memory;
            }
        }
        
        // Find larger block that can accommodate request
        for (auto& block : blocks) {
            if (!block->inUse && block->size >= size) {
                block->inUse = true;
                block->lastUsed = std::chrono::steady_clock::now();
                return block->memory;
            }
        }
        
        // No suitable block found, create new one
        blocks.push_back(std::make_unique<Block>(findBestSize(size)));
        auto& newBlock = blocks.back();
        newBlock->inUse = true;
        return newBlock->memory;
    }
    
    void deallocate(void* ptr) {
        if (!ptr) return;
        
        std::lock_guard<std::mutex> lock(poolMutex);
        for (auto& block : blocks) {
            if (block->memory == ptr) {
                block->inUse = false;
                block->lastUsed = std::chrono::steady_clock::now();
                return;
            }
        }
    }
    
    // Cleanup old unused blocks to prevent unlimited growth
    void cleanup() {
        std::lock_guard<std::mutex> lock(poolMutex);
        auto now = std::chrono::steady_clock::now();
        
        blocks.erase(
            std::remove_if(blocks.begin(), blocks.end(),
                [now](const std::unique_ptr<Block>& block) {
                    return !block->inUse && 
                           (now - block->lastUsed) > std::chrono::minutes(5);
                }),
            blocks.end()
        );
    }
    
    size_t getMemoryUsage() const {
        std::lock_guard<std::mutex> lock(poolMutex);
        size_t total = 0;
        for (const auto& block : blocks) {
            total += block->size;
        }
        return total;
    }
    
private:
    size_t findBestSize(size_t requested) {
        // Find the smallest common size that fits the request
        for (size_t commonSize : COMMON_SIZES) {
            if (commonSize >= requested) {
                return commonSize;
            }
        }
        // If larger than all common sizes, round up to next power of 2
        size_t powerOf2 = 1;
        while (powerOf2 < requested) {
            powerOf2 <<= 1;
        }
        return powerOf2;
    }
};

// Singleton access to global pool
class MemoryManager {
public:
    static ImageMemoryPool& getImagePool() {
        static ImageMemoryPool instance;
        return instance;
    }
    
    // RAII wrapper for automatic cleanup
    class PooledMemory {
    private:
        void* ptr;
        size_t size;
        
    public:
        PooledMemory(size_t s) : size(s) {
            ptr = getImagePool().allocate(size);
        }
        
        ~PooledMemory() {
            getImagePool().deallocate(ptr);
        }
        
        void* get() const { return ptr; }
        size_t getSize() const { return size; }
        
        // Prevent copying
        PooledMemory(const PooledMemory&) = delete;
        PooledMemory& operator=(const PooledMemory&) = delete;
        
        // Allow moving
        PooledMemory(PooledMemory&& other) noexcept 
            : ptr(other.ptr), size(other.size) {
            other.ptr = nullptr;
            other.size = 0;
        }
    };
};
```

### Solution 2: Custom Allocator for STL Containers
```cpp
// Custom allocator for Adobe's specific needs
template<typename T>
class AdobePoolAllocator {
public:
    using value_type = T;
    
    AdobePoolAllocator() = default;
    
    template<typename U>
    AdobePoolAllocator(const AdobePoolAllocator<U>&) noexcept {}
    
    T* allocate(std::size_t n) {
        size_t bytes = n * sizeof(T);
        void* ptr = MemoryManager::getImagePool().allocate(bytes);
        return static_cast<T*>(ptr);
    }
    
    void deallocate(T* ptr, std::size_t n) {
        MemoryManager::getImagePool().deallocate(ptr);
    }
    
    template<typename U>
    bool operator==(const AdobePoolAllocator<U>&) const noexcept {
        return true;
    }
};

// Usage: STL containers with custom allocator
using AdobeVector = std::vector<uint8_t, AdobePoolAllocator<uint8_t>>;
using AdobeString = std::basic_string<char, std::char_traits<char>, AdobePoolAllocator<char>>;
```

## Step 5: Memory Monitoring and Debugging

### Real-time Memory Tracking
```cpp
class MemoryTracker {
private:
    std::atomic<size_t> totalAllocated{0};
    std::atomic<size_t> peakUsage{0};
    std::atomic<size_t> allocationCount{0};
    std::mutex detailsMutex;
    std::unordered_map<std::string, size_t> allocationsByType;
    
public:
    void recordAllocation(const std::string& type, size_t size) {
        allocationCount++;
        totalAllocated += size;
        
        size_t current = totalAllocated.load();
        size_t peak = peakUsage.load();
        while (current > peak && !peakUsage.compare_exchange_weak(peak, current)) {
            // Update peak usage atomically
        }
        
        std::lock_guard<std::mutex> lock(detailsMutex);
        allocationsByType[type] += size;
    }
    
    void recordDeallocation(const std::string& type, size_t size) {
        totalAllocated -= size;
        
        std::lock_guard<std::mutex> lock(detailsMutex);
        allocationsByType[type] -= size;
    }
    
    void printMemoryReport() const {
        std::cout << "\n=== Memory Usage Report ===" << std::endl;
        std::cout << "Current Usage: " << (totalAllocated.load() / (1024*1024)) << " MB" << std::endl;
        std::cout << "Peak Usage: " << (peakUsage.load() / (1024*1024)) << " MB" << std::endl;
        std::cout << "Total Allocations: " << allocationCount.load() << std::endl;
        
        std::lock_guard<std::mutex> lock(detailsMutex);
        std::cout << "\nBreakdown by Type:" << std::endl;
        for (const auto& [type, size] : allocationsByType) {
            if (size > 0) {
                std::cout << "  " << type << ": " << (size / (1024*1024)) << " MB" << std::endl;
            }
        }
    }
    
    static MemoryTracker& getInstance() {
        static MemoryTracker instance;
        return instance;
    }
};
```

## Step 6: Exception Safety and Error Recovery

### RAII for Complex Resources
```cpp
class PhotoshopOperation {
private:
    MemoryManager::PooledMemory workBuffer;
    std::unique_ptr<TempFile> tempFile;
    
public:
    PhotoshopOperation(size_t bufferSize) 
        : workBuffer(bufferSize)
        , tempFile(std::make_unique<TempFile>()) {
        
        MemoryTracker::getInstance().recordAllocation("PhotoshopOp", bufferSize);
    }
    
    ~PhotoshopOperation() {
        MemoryTracker::getInstance().recordDeallocation("PhotoshopOp", workBuffer.getSize());
        // tempFile and workBuffer automatically cleaned up
    }
    
    void processImage() {
        // All cleanup happens automatically even if exceptions thrown
        if (workBuffer.get() == nullptr) {
            throw std::runtime_error("Failed to allocate work buffer");
        }
        
        // Process using workBuffer.get()...
    }
};
```

Let's continue with thread-safe memory management and performance optimization techniques!

### Cross-Platform Considerations
```cpp
// Platform-specific implementations
#ifdef _WIN32
    #include <windows.h>
    using PlatformMutex = CRITICAL_SECTION;
#else
    #include <pthread.h>
    using PlatformMutex = pthread_mutex_t;
#endif

class CrossPlatformLogger {
private:
    PlatformMutex mutex;
    
public:
    CrossPlatformLogger() {
#ifdef _WIN32
        InitializeCriticalSection(&mutex);
#else
        pthread_mutex_init(&mutex, nullptr);
#endif
    }
    
    ~CrossPlatformLogger() {
#ifdef _WIN32
        DeleteCriticalSection(&mutex);
#else
        pthread_mutex_destroy(&mutex);
#endif
    }
};
```

## Key Interview Points for Adobe

1. **Performance**: Adobe products process large files - discuss memory efficiency
2. **Thread Safety**: UI responsiveness while processing - explain synchronization
3. **Plugin Architecture**: Extensibility through design patterns
4. **Cross-Platform**: Windows, macOS support - platform abstraction
5. **Memory Management**: Large image processing - custom allocators
6. **Error Handling**: Robust error recovery in creative workflows

## Common Follow-up Questions

**"How would you handle plugin crashes without affecting the main application?"**
- Process isolation, COM interfaces, exception boundaries

**"How do you ensure UI responsiveness during heavy image processing?"**
- Worker threads, progress callbacks, asynchronous patterns

**"How would you implement undo/redo for complex operations?"**
- Command pattern, memento pattern, differential snapshots
