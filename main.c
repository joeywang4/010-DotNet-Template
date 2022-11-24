// book keeping variables
local int64 StringHeapLoc;
local DWORD StringHeapSize;
local int64 GUIDLoc;
local DWORD GUIDSize;
local int64 BlobLoc;
local DWORD BlobSize;
local int64 USLoc;
local DWORD USSize;

// .NET --- Headers
#include "src/CorHdr.c"
#include "src/GeneralMdHdr.c"
#include "src/StreamHdr.c"

// .NET --- streams
#include "src/Stream/Util.c"
#include "src/Stream/Metadata.c"
#include "src/Stream/Strings.c"
#include "src/Stream/GUID.c"
#include "src/Stream/Blob.c"
#include "src/Stream/US.c"

// IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR
void ParseDotNet()
{
    if ( 
        NtHeader.OptionalHeader.DataDirArray.COMRuntimedescriptor.VirtualAddress == 0 ||
        NtHeader.OptionalHeader.DataDirArray.COMRuntimedescriptor.Size == 0    
    ) 
    {
        return;
    }

    local ULONG dotNetDirFOA = RVA2FOA(
        NtHeader.OptionalHeader.DataDirArray.COMRuntimedescriptor.VirtualAddress
    );
    FSeek(dotNetDirFOA);
    // Defined in src/CorHdr.c
    IMAGE_COR20_HEADER DotNetDir <bgcolor=cLtPurple>;

    if ( DotNetDir.MetaData.VirtualAddress == 0 || DotNetDir.MetaData.Size == 0 )
    {
        Printf("Invalid Metadata header address 0x%X", DotNetDir.MetaData.VirtualAddress);
        Printf(" or size 0x%X\n", DotNetDir.MetaData.Size);
        return;
    }

    local ULONG metadataFOA = RVA2FOA(DotNetDir.MetaData.VirtualAddress);
    FSeek(metadataFOA);
    // Defined in src/GeneralMdHdr.c
    GENERAL_METADATA_HEADER Metadata <bgcolor=cLtPurple>;

    if ( Metadata.Signature != 0x424A5342 )
    {
        Printf("Invalid Metadata header signature: 0x%X\n", Metadata.Signature);
        return;
    }

    // Defined in src/StreamHdr.c
    STREAM_HEADER_ARR StreamHeaders(Metadata.Streams) <bgcolor=cLtGray>;

    local int i = 0;
    local string streamName;
    for (i = 0; i < Metadata.Streams; i++)
    {
        streamName = StreamHeaders.StreamHeaderArr[i].Name;
        FSeek(metadataFOA + StreamHeaders.StreamHeaderArr[i].Offset);

        // Metadata tables
        // Defined in src/stream/Metadata.c
        if ( streamName == "#~" ) METADATA_STREAM MetadataStream <read="#~">;

        // Other streams
        if ( streamName == "#Strings" )
        {
            StringHeapLoc = FTell();
            StringHeapSize = StreamHeaders.StreamHeaderArr[i].Size;
            // Defined in src/stream/Strings.c
            STRING_HEAP StringHeap <fgcolor=cDkPurple,read="#Strings">;
        }
        if ( streamName == "#GUID" )
        {
            GUIDLoc = FTell();
            GUIDSize = StreamHeaders.StreamHeaderArr[i].Size;
            // Defined in src/stream/GUID.c
            GENERIC_STREM GuidStream(
                StreamHeaders.StreamHeaderArr[i].Size
            ) <bgcolor=cLtPurple,read="#GUID">;
        }
        if ( streamName == "#Blob" )
        {
            BlobLoc = FTell();
            BlobSize = StreamHeaders.StreamHeaderArr[i].Size;
            // Defined in src/stream/Blob.c
            BLOB_HEAP BlobStream <read="#Blob">;
        }
        if ( streamName == "#US" )
        {
            USLoc = FTell();
            USSize = StreamHeaders.StreamHeaderArr[i].Size;
            // Defined in src/stream/US.c
            USER_STRING_HEAP UserStringHeap <read="#US">;
        }
    }
}

ParseDotNet();
