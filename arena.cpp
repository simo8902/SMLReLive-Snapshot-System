#if defined(_MSC_VER)
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((visibility("default")))
#endif

#include "arena.h"
#include <stdint.h>
#include <stdio.h>


static inline void* AlignedAlloc64(size_t size) {
    // Allocate memory that starts at an address divisible by 64
    return nullptr;
}

static inline void AlignedFree(void* p) {
    // Free memory that was allocated with AlignedAlloc64
}

static inline SnapshotHeader* FastGetById(SnapshotArena* a, uint32_t id, uint32_t* outIndex) {
    // Quickly find a snapshot by its ID without checking every single one
    return nullptr;
}

enum SimdLevel : uint8_t { SIMD_NONE, SIMD_SSE2, SIMD_AVX2, SIMD_AVX512 };

static inline void cpuidex(int out[4], int leaf, int subleaf) {
    // Ask the CPU what features it supports
}

static inline uint64_t xgetbv0() {
    // Ask the CPU/OS what vector registers we can use
    return 0;
}

static SimdLevel DetectSimd() {
    // Detect the highest SIMD feature the CPU supports (SSE2, AVX2, AVX512)
    return SIMD_NONE;
}

static inline void* ptr_add(void* p, size_t n) {
    // Move a pointer forward by n bytes
    return p;
}

static inline const void* ptr_add(const void* p, size_t n) {
    // Move a const pointer forward by n bytes
    return p;
}

static void FastCopy_Fallback(void* dst, const void* src, size_t size) {
    // Copy data the normal way, without any SIMD optimizations
}

static void FastCopy_AVX2(void* dst, const void* src, size_t size) {
    // Copy data using AVX2 (256-bit wide CPU instructions)
}

static void FastCopy_AVX512(void* dst, const void* src, size_t size) {
    // Copy data using AVX512 (512-bit wide CPU instructions)
}

using FastCopyFn = void(*)(void*, const void*, size_t);

static void InitFastCopy() {
    // Pick the best copy function based on what the CPU supports
}

#define LogToUnity(fmt, ...) do { \
    if (g_LogCallback) { \
        char buf[512]; \
        snprintf(buf, sizeof(buf), fmt, __VA_ARGS__); \
        g_LogCallback(buf); \
    } \
} while(0)



extern "C" {
    EXPORT SnapshotArena* Arena_Create(uint64_t sizeBytes, uint32_t maxSnapshots)
    {
        LogToUnity("Arena_Create [public]: sizeBytes=%llu maxSnapshots=%u",
            (unsigned long long)sizeBytes, maxSnapshots);
        return nullptr;
    }

    EXPORT void Arena_Destroy(SnapshotArena* a)
    {
        LogToUnity("Arena_Destroy [public]: a=%p", a);
    }

    EXPORT void Arena_Clear(SnapshotArena* a)
    {
        LogToUnity("Arena_Clear [public]: a=%p", a);
    }

    EXPORT bool Arena_CanFit(SnapshotArena* a, uint32_t size)
    {
        LogToUnity("Arena_CanFit [public]: a=%p size=%u", a, size);
        return false;
    }

    EXPORT bool Arena_BeginWrite(SnapshotArena* a, uint32_t id, uint32_t size, ArenaWriteHandle* outHandle, uint8_t** outPtr)
    {
        LogToUnity("Arena_BeginWrite [public]: a=%p id=%u size=%u", a, id, size);
        return false;
    }

    EXPORT void Arena_EndWrite(SnapshotArena* a, const ArenaWriteHandle* handle)
    {
        LogToUnity("Arena_EndWrite [public]: a=%p handle=%p", a, handle);
    }

    EXPORT bool Arena_DeleteSnapshot(SnapshotArena* a, uint32_t id)
    {
        LogToUnity("Arena_DeleteSnapshot [public]: a=%p id=%u", a, id);
        return false;
    }

    EXPORT bool Arena_GetSnapshotInfo(SnapshotArena* a, uint32_t id, SnapshotHeader* out)
    {
        LogToUnity("Arena_GetSnapshotInfo [public]: a=%p id=%u out=%p", a, id, out);
        return false;
    }

    EXPORT uint64_t Arena_GetUsedBytes(SnapshotArena* a)
    {
        LogToUnity("Arena_GetUsedBytes [public]: a=%p", a);
        return 0;
    }

    EXPORT uint64_t Arena_GetCapacityBytes(SnapshotArena* a)
    {
        LogToUnity("Arena_GetCapacityBytes [public]: a=%p", a);
        return 0;
    }

    EXPORT void Arena_PrintDebug(SnapshotArena* a)
    {
        LogToUnity("Arena_PrintDebug [public]: a=%p", a);
    }

    EXPORT bool Arena_ReadSnapshot(SnapshotArena* a, uint32_t id, void* outBuffer, uint32_t* outSize)
    {
        LogToUnity("Arena_ReadSnapshot [public]: a=%p id=%u outBuffer=%p outSize=%p", a, id, outBuffer, outSize);
        return false;
    }

    EXPORT bool Arena_CloneSnapshot(SnapshotArena* src, SnapshotArena* dst, uint32_t id)
    {
        LogToUnity("Arena_CloneSnapshot [public]: src=%p dst=%p id=%u", src, dst, id);
        return false;
    }

    EXPORT uint8_t* Arena_GetMemoryPtr(SnapshotArena* a)
    {
        LogToUnity("Arena_GetMemoryPtr [public]: a=%p", a);
        return nullptr;
    }

    EXPORT void Arena_AddUsedBytes(SnapshotArena* a, uint32_t bytes)
    {
        LogToUnity("Arena_AddUsedBytes [public]: a=%p bytes=%u", a, bytes);
    }
}