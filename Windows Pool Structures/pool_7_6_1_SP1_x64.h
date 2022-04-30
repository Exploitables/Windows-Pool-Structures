#include <Windows.h>

typedef struct _POOL_HEADER
{
    union {
        ULONG Ulong1;
        struct {
            UCHAR PreviousSize : 8;
            UCHAR PoolIndex : 8;
            UCHAR BlockSize : 8;
            UCHAR PoolType : 8;
        };
    };
    ULONG PoolTag;
    union {
        PVOID ProcessBilled; // Should be PEPROCESS
        USHORT AllocatorBackTraceIndex;
    };
    USHORT PoolTagHash;
} POOL_HEADER, * PPOOL_HEADER;

typedef struct _OBJECT_HEADER_QUOTA_INFO
{
    ULONG PagedPoolCharge;
    ULONG NonPagedPoolCharge;
    ULONG SecurityDescriptorCharge;
    PVOID SecurityDescriptorQuotaBlock;
    ULONGLONG Reserved;
} OBJECT_HEADER_QUOTA_INFO, * POBJECT_HEADER_QUOTA_INFO;

typedef struct _OBJECT_HEADER
{
    LONGLONG PointerCount;
    union {
        LONGLONG HandleCount;
        PVOID NextToFree;
    };
    EX_PUSH_LOCK Lock;
    UCHAR TypeIndex;
    UCHAR TraceFlags;
    UCHAR InfoMask;
    UCHAR Flags;
    union {
        POBJECT_CREATE_INFORMATION ObjectCreateInfo;
        PVOID QuotaBlockCharged;
    };
    PVOID SecurityDescriptor;
    QUAD Body;
} OBJECT_HEADER, * POBJECT_HEADER;

typedef struct _EX_PUSH_LOCK
{
    union {
        ULONGLONG Value;
        PVOID Ptr;
        struct {
            UCHAR Locked : 1;
            UCHAR Waiting : 1;
            UCHAR Waking : 1;
            UCHAR MultipleShared : 1;
            ULONGLONG Shared : 60;
        };
    };
} EX_PUSH_LOCK, * PEX_PUSH_LOCK;

typedef struct _OBJECT_CREATE_INFORMATION
{
    ULONG Attributes;
    PVOID RootDirectory;
    CHAR ProbeMode;
    ULONG PagedPoolCharge;
    ULONG NonPagedPoolCharge;
    ULONG SecurityDescriptorCharge;
    PVOID SecurityDescriptor;
    PSECURITY_QUALITY_OF_SERVICE SecurityQos;
    SECURITY_QUALITY_OF_SERVICE SecurityQualityOfService;
} OBJECT_CREATE_INFORMATION, * POBJECT_CREATE_INFORMATION;

typedef struct _QUAD
{
    union {
        LONGLONG UseThisFieldToCopy;
        FLOAT DoNotUseThisField;
    };
} QUAD, * PQUAD;