#include <Windows.h>
#include "pool_enums.h"

typedef struct _POOL_HEADER
{
	struct {
		UCHAR PreviousSize : 8;
		UCHAR PoolIndex : 8;
	};
	struct {
		UCHAR BlockSize : 8;
		UCHAR PoolType : 8;
	};
	ULONG Ulong1;
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
	ULONG Reserved1;
	PVOID SecurityDescriptorQuotaBlock;
	ULONGLONG Reserved2;
} OBJECT_HEADER_QUOTA_INFO, * POBJECT_HEADER_QUOTA_INFO;

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

typedef struct _QUAD
{
	union {
		LONGLONG UseThisFieldToCopy;
		FLOAT DoNotUseThisField;
	};
} QUAD, * PQUAD;

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

typedef struct _OBJECT_HEADER
{
	LONGLONG PointerCount;
	union {
		LONGLONG HandleCount;
		PVOID NextToFree;
	};
	PEX_PUSH_LOCK Lock;
	UCHAR TypeIndex;
	union {
		UCHAR TraceFlags;
		struct {
			UCHAR DbgRefTrace : 1;
			UCHAR DbgTracePermanent : 1;
		};
	};
	UCHAR InfoMask;
	union {
		UCHAR Flags;
		struct {
			UCHAR NewObject : 1;
			UCHAR KernelObject : 1;
			UCHAR KernelOnlyAccess : 1;
			UCHAR ExclusiveObject : 1;
			UCHAR PermanentObject : 1;
			UCHAR DefaultSecurityQuota : 1;
			UCHAR SingleHandleEntry : 1;
			UCHAR DeletedInline : 1;
		};
	};
	ULONG Reserved;
	union {
		POBJECT_CREATE_INFORMATION ObjectCreateInfo;
		PVOID QuotaBlockCharged;
	};
	PVOID SecurityDescriptor;
	PQUAD Body;
} OBJECT_HEADER, * POBJECT_HEADER;

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	_Field_size_bytes_part_opt_(MaximumLength, Length) PWCH Buffer;
} UNICODE_STRING, * PUNICODE_STRING;

typedef struct _OBJECT_TYPE_INITIALIZER
{
	USHORT Length;
	union {
		USHORT ObjectTypeFlags;
		struct {
			UCHAR CaseInsensitive : 1;
			UCHAR UnnamedObjectsOnly : 1;
			UCHAR UseDefaultObject : 1;
			UCHAR SecurityRequired : 1;
			UCHAR MaintainHandleCount : 1;
			UCHAR MaintainTypeList : 1;
			UCHAR SupportsObjectCallbacks : 1;
			UCHAR CacheAligned : 1;
		};
	};
	struct {
		UCHAR UseExtendedParameters : 1;
		UCHAR Reserved : 7;
	};
	ULONG ObjectTypeCode;
	ULONG InvalidAttributes;
	GENERIC_MAPPING GenericMapping;
	ULONG ValidAccessMask;
	ULONG RetainAccess;
	POOL_TYPE PoolType;
	ULONG DefaultPagedPoolCharge;
	ULONG DefaultNonPagedPoolCharge;
	PVOID DumpProcedure;
	PVOID OpenProcedure;
	PVOID CloseProcedure;
	PVOID DeleteProcedure;
	union {
		PVOID ParseProcedure;
		PVOID ParseProcedureEx;
	};
	PVOID SecurityProcedure;
	PVOID QueryNameProcedure;
	PVOID OkayToCloseProcedure;
	ULONG WaitObjectFlagMask;
	USHORT WaitObjectFlagOffset;
	USHORT WaitObjectPointerOffset;
} OBJECT_TYPE_INITIALIZER, * POBJECT_TYPE_INITIALIZER;

typedef struct _OBJECT_TYPE
{
	LIST_ENTRY TypeList;
	UNICODE_STRING Name;
	PVOID DefaultObject;
	UCHAR Index;
	ULONG TotalNumberOfObjects;
	ULONG TotalNumberOfHandles;
	ULONG HighWaterNumberOfObjects;
	ULONG HighWaterNumberOfHandles;
	OBJECT_TYPE_INITIALIZER TypeInfo;
	EX_PUSH_LOCK TypeLock;
	ULONG Key;
	LIST_ENTRY CallbackList;
} OBJECT_TYPE, * POBJECT_TYPE;