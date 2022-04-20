#include <Windows.h>

typedef struct _POOL_HEADER
{
	union
	{
		struct
		{
			unsigned long PreviousSize;
			unsigned long PoolIndex;
			unsigned long BlockSize;
			unsigned long PoolType;
		};
		unsigned long Ulong1;
	};

	unsigned long PoolTag;
	union
	{
		unsigned short AllocatorBackTraceIndex;
		unsigned short PoolTagHash;
	};
} POOL_HEADER, * PPOOL_HEADER;

typedef struct _OBJECT_HEADER_QUOTA
{
	unsigned long PagedPoolCharge;
	unsigned long NonPagedPoolCharge;
	unsigned long SecurityDescriptorCharge;
	unsigned long Reserved1;
	unsigned long long SecurityDescriptorQuotaBlock;
	unsigned long Reserved2;
} OBJECT_HEADER_QUOTA, * POBJECT_HEADER_QUOTA;

typedef struct _OBJECT_HEADER
{
	unsigned long long PointerCount;
	union
	{
		unsigned long long HandleCount;
		void* NextToFree;
	};

	void* Lock;
	unsigned char TypeIndex;
	union
	{
		unsigned char TraceFlags;
		unsigned long DbgRefTrace;
		unsigned long DbgTracePermanent;
	};

	unsigned char InfoMask;
	union
	{
		unsigned char Flags;
		unsigned long NewObject;
		unsigned long KernelObject;
		unsigned long KernelOnlyAccess;
		unsigned long ExclusiveObject;
		unsigned long PermanentObject;
		unsigned long DefaultSecurityQuota;
		unsigned long SingleHandleEntry;
		unsigned long DeletedInline;
	};

	unsigned long Reserved;
	union
	{
		unsigned long long* ObjectCreateInfo;
		unsigned long long* QuotaBlockCharged;
	};

	unsigned long long* SecurityDescriptor;
	void* Body;
} OBJECT_HEADER, * POBJECT_HEADER;
