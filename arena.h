#pragma once
#include <stdint.h>
#include <stdlib.h>

// special value meaning "nothing here"
#define EMPTY_KEY     0xFFFFFFFFu

// keep struct layout consistent across compilers
#pragma pack(push, 4)
struct SnapshotHeader
{
    uint32_t id;      // snapshot's ID number
    uint32_t offset;  // where in memory it starts
    uint32_t size;    // how big it is
};
#pragma pack(pop)

// slot in the hash map (key = ID, val = header index)
struct HashSlot
{
    uint32_t key;
    uint32_t val;
};

// info you pass around when writing to arena
struct ArenaWriteHandle
{
    uint32_t id;
    uint32_t offset;
    uint32_t size;
};

// free chunk of memory inside the arena
struct FreeBlock
{
    uint32_t offset;
    uint32_t size;
};

// main memory arena struct that holds all snapshots
struct SnapshotArena
{
    uint8_t* memory;           // big memory buffer for snapshots
    SnapshotHeader* headers;   // metadata for each snapshot

    HashSlot* map;             // hash map for quick ID lookups
    uint32_t hashCap;          // how many slots in the map

    FreeBlock* freeBlocks;     // list of free memory chunks
    uint32_t freeCount;        // how many free chunks
    uint32_t freeCap;          // max free chunks we can track

    uint64_t capacity;         // total bytes the arena can hold
    uint32_t maxSnapshots;     // limit for how many snapshots at once
    uint64_t used;             // bytes currently used
    uint32_t snapshotCount;    // how many snapshots exist
    uint64_t freeBytes;        // total free space available
};

// branch prediction hints (MSVC can't do the GCC-style macros)
#if defined(_MSC_VER)
#define likely(x)   (x)
#define unlikely(x) (x)
#else
#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#endif

typedef void (*LogCallback)(const char*);

static LogCallback g_LogCallback = nullptr;
#ifndef INVALID_INDEX
#define INVALID_INDEX (0xFFFFFFFFu)
#endif

// returns the next power of two greater than or equal to v
static inline uint32_t NextPow2(uint32_t v) {}

// simple 32-bit integer hash function
static inline uint32_t Hash32(uint32_t x) {}

// make sure the arena has a valid hash map ready
static inline void EnsureIndexMap(SnapshotArena* a) {}

// try to find an ID in the arena's hash map
static inline bool MapFind(const SnapshotArena* a, uint32_t id, uint32_t* outHeaderIdx) {}

// put a new ID/index pair into the map
static inline void MapInsert(SnapshotArena* a, uint32_t id, uint32_t headerIdx) {}

// remove an ID from the map
static inline bool MapErase(SnapshotArena* a, uint32_t id) {}

extern "C" {
    // make a new arena with given size and max number of snapshots
    __declspec(dllexport) SnapshotArena* Arena_Create(uint64_t sizeBytes, uint32_t maxSnapshots);

    // completely free and clean up an arena
    __declspec(dllexport) void Arena_Destroy(SnapshotArena* a);

    // wipe all snapshots from the arena but keep the memory ready
    __declspec(dllexport) void Arena_Clear(SnapshotArena* a);

    // check if there’s enough space for a snapshot of this size
    __declspec(dllexport) bool Arena_CanFit(SnapshotArena* a, uint32_t size);

    // start writing a new snapshot, gives you a handle and memory pointer
    __declspec(dllexport) bool Arena_BeginWrite(SnapshotArena* a, uint32_t id, uint32_t size, ArenaWriteHandle* outHandle, uint8_t** outPtr);

    // finish writing a snapshot and register it in the arena
    __declspec(dllexport) void Arena_EndWrite(SnapshotArena* a, const ArenaWriteHandle* handle);

    // remove a snapshot from the arena by its ID
    __declspec(dllexport) bool Arena_DeleteSnapshot(SnapshotArena* a, uint32_t id);

    // get the header info (offset/size) for a given snapshot ID
    __declspec(dllexport) bool Arena_GetSnapshotInfo(SnapshotArena* a, uint32_t id, SnapshotHeader* out);

    // how many bytes are currently used in the arena
    __declspec(dllexport) uint64_t Arena_GetUsedBytes(SnapshotArena* a);

    // how many bytes the arena can hold total
    __declspec(dllexport) uint64_t Arena_GetCapacityBytes(SnapshotArena* a);

    // print all snapshot info to the log for debugging
    __declspec(dllexport) void Arena_PrintDebug(SnapshotArena* a);

    // copy a snapshot’s data into a buffer
    __declspec(dllexport) bool Arena_ReadSnapshot(SnapshotArena* arena, uint32_t id, void* outBuffer, uint32_t* outSize);

    // copy a snapshot from one arena to another
    __declspec(dllexport) bool Arena_CloneSnapshot(SnapshotArena* src, SnapshotArena* dst, uint32_t id);

    // get a direct pointer to the arena’s memory buffer
    __declspec(dllexport) uint8_t* Arena_GetMemoryPtr(SnapshotArena* a);

    // manually mark extra bytes as used in the arena
    __declspec(dllexport) void Arena_AddUsedBytes(SnapshotArena* a, uint32_t bytes);


    __declspec(dllexport) void Arena_SetLogCallback(LogCallback cb) {
        // Let Unity give us a function we can call to send log messages
    }

    __declspec(dllexport) void Arena_InitSimd() {
        // Prepare the fastest copy method we can use
    }

    __declspec(dllexport) void FastCopy(void* dst, const void* src, size_t size) {
        // Copy memory using the method chosen in Arena_InitSimd
    }
}