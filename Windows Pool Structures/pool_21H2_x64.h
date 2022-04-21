typedef struct _POOL_HEADER
{
	union
	{
		struct
		{
			unsigned char PreviousSize;
			unsigned char PoolIndex;
		};

		struct
		{
			unsigned char BlockSize;
			unsigned char PoolType;
		};
		unsigned long Ulong1;
	};

	unsigned long PoolTag;
	union
	{
		void* ProcessBilled;
		unsigned short AllocatorBackTraceIndex;
	};

	unsigned short PoolTagHash;
} POOL_HEADER, * PPOOL_HEADER;

typedef struct _OBJECT_HEADER_QUOTA
{
	unsigned long PagedPoolCharge;
	unsigned long NonPagedPoolCharge;
	unsigned long SecurityDescriptorCharge;
	unsigned long Reserved1;
	void* SecurityDescriptorQuotaBlock;
	unsigned long long Reserved2;
} OBJECT_HEADER_QUOTA, * POBJECT_HEADER_QUOTA;

typedef struct _QUAD
{
	union
	{
		unsigned long long UseThisFieldToCopy;
		double DoNotUseThisField;
	};
} QUAD, * PQUAD;

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
		unsigned char DbgRefTrace;
		unsigned char DbgTracePermanent;
	};

	unsigned char InfoMask;
	union
	{
		unsigned char Flags;
		unsigned char NewObject;
		unsigned char KernelObject;
		unsigned char KernelOnlyAccess;
		unsigned char ExclusiveObject;
		unsigned char PermanentObject;
		unsigned char DefaultSecurityQuota;
		unsigned char SingleHandleEntry;
		unsigned char DeletedInline;
	};

	unsigned long Reserved;
	union
	{
		void* ObjectCreateInfo;
		void* QuotaBlockCharged;
	};

	void* SecurityDescriptor;
	void* Body;
} OBJECT_HEADER, * POBJECT_HEADER;