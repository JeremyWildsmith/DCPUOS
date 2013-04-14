var md__code =
[
    [ "bitmap10c", "bitmap10c.html", [
      [ "Bitmap", "bitmap10c.html#Bitmap", [
        [ "Module Details", "bitmap10c.html#bitmapDetails", null ],
        [ "Bitmaps", "bitmap10c.html#Bitmaps", null ]
      ] ],
      [ "Functions", "bitmap10c.html#DASMDOC_S10", [
        [ "bitmap_set", "bitmap10c.html#DASMDOC_S11", null ],
        [ "bitmap_clear", "bitmap10c.html#DASMDOC_S12", null ],
        [ "bitmap_get", "bitmap10c.html#DASMDOC_S13", null ],
        [ "bitmap_nandRun", "bitmap10c.html#DASMDOC_S14", null ],
        [ "bitmap_findClearRun", "bitmap10c.html#DASMDOC_S15", null ]
      ] ]
    ] ],
    [ "clock10c", "clock10c.html", [
      [ "Constants", "clock10c.html#DASMDOC_S16", [
        [ "CLOCK_HIGHID", "clock10c.html#DASMDOC_S17", null ],
        [ "CLOCK_LOWID", "clock10c.html#DASMDOC_S18", null ],
        [ "CLOCK_INTERRUPTCODE_SETTICKS", "clock10c.html#DASMDOC_S19", null ],
        [ "CLOCK_INTERRUPTCODE_GETTICKS", "clock10c.html#DASMDOC_S20", null ],
        [ "CLOCK_INTERRUPTCODE_SETMESSAGE", "clock10c.html#DASMDOC_S21", null ]
      ] ],
      [ "Data", "clock10c.html#DASMDOC_S22", [
        [ "clock_deviceIndex", "clock10c.html#DASMDOC_S23", null ]
      ] ],
      [ "Functions", "clock10c.html#DASMDOC_S24", [
        [ "clock_init", "clock10c.html#DASMDOC_S25", null ],
        [ "clock_getTicks", "clock10c.html#DASMDOC_S26", null ],
        [ "clock_interrupt", "clock10c.html#DASMDOC_S27", null ]
      ] ]
    ] ],
    [ "device10c", "device10c.html", [
      [ "Device", "device10c.html#deviceManager", [
        [ "Module Details", "device10c.html#deviceManagerDetails", null ],
        [ "Device Manager", "device10c.html#deviceManagerDevice", null ],
        [ "Device Manager Entry", "device10c.html#deviceEntryLayout", null ]
      ] ],
      [ "Constants", "device10c.html#DASMDOC_S28", [
        [ "DEVICE_DEVICEENTRY_OFFSET_HARDWAREIDLOW", "device10c.html#DASMDOC_S29", null ],
        [ "DEVICE_DEVICEENTRY_OFFSET_HARDWAREIDHIGH", "device10c.html#DASMDOC_S30", null ],
        [ "DEVICE_DEVICEENTRY_OFFSET_HARDWAREVERSION", "device10c.html#DASMDOC_S31", null ],
        [ "DEVICE_DEVICEENTRY_OFFSET_HANDLER", "device10c.html#DASMDOC_S32", null ],
        [ "DEVICE_DEVICEENTRY_SIZE", "device10c.html#DASMDOC_S33", null ],
        [ "DEVICE_DEVICEENTRY_MAXENTRIES", "device10c.html#DASMDOC_S34", null ],
        [ "DEVICE_DEVICEENTRY_MAXENTRYINDEX", "device10c.html#DASMDOC_S35", null ],
        [ "DEVICE_DEVICEENTRY_INVALIDENTRY", "device10c.html#DASMDOC_S36", null ]
      ] ],
      [ "Data", "device10c.html#DASMDOC_S37", [
        [ "device_deviceEntryTable", "device10c.html#DASMDOC_S38", null ]
      ] ],
      [ "Functions", "device10c.html#DASMDOC_S39", [
        [ "device_init", "device10c.html#DASMDOC_S40", null ],
        [ "device_getDeviceInterruptMessage", "device10c.html#DASMDOC_S41", null ],
        [ "device_findIndexOfDevice", "device10c.html#DASMDOC_S42", null ],
        [ "device_allocateDevice", "device10c.html#DASMDOC_S43", null ],
        [ "device_freeDevice", "device10c.html#DASMDOC_S44", null ],
        [ "device_defaultInterruptHandler", "device10c.html#DASMDOC_S45", null ],
        [ "device_interruptHandler", "device10c.html#DASMDOC_S46", null ]
      ] ]
    ] ],
    [ "interrupt10c", "interrupt10c.html", [
      [ "Interrupt Handler", "interrupt10c.html#interrupt", [
        [ "Module Details", "interrupt10c.html#interruptDetails", null ],
        [ "Interrupts", "interrupt10c.html#interrupts", null ],
        [ "Software Interrupts", "interrupt10c.html#softwareInterrupts", null ]
      ] ],
      [ "Constants", "interrupt10c.html#DASMDOC_S47", [
        [ "INTERRUPT_MESSAGE_DEBUGBREAK", "interrupt10c.html#DASMDOC_S48", null ],
        [ "INTERRUPT_MESSAGE_KERNELERROR", "interrupt10c.html#DASMDOC_S49", null ],
        [ "INTERRUPT_MESSAGE_THREADENDCYCLE", "interrupt10c.html#DASMDOC_S50", null ],
        [ "INTERRUPT_MESSAGE_THREADEXCEPTION", "interrupt10c.html#DASMDOC_S51", null ],
        [ "INTERRUPT_DEVICEMASK", "interrupt10c.html#DASMDOC_S52", null ]
      ] ],
      [ "Functions", "interrupt10c.html#DASMDOC_S53", [
        [ "interrupt_enable", "interrupt10c.html#DASMDOC_S54", null ],
        [ "interrupt_disable", "interrupt10c.html#DASMDOC_S55", null ],
        [ "interrupt_handler", "interrupt10c.html#DASMDOC_S56", null ],
        [ "interrupt_handler_breakpoint", "interrupt10c.html#DASMDOC_S57", null ]
      ] ]
    ] ],
    [ "main10c", "main10c.html", [
      [ "Kernel", "main10c.html#KernelMain", [
        [ "Module Details", "main10c.html#mainmoddet", null ]
      ] ],
      [ "Data", "main10c.html#DASMDOC_S58", [
        [ "kernel_image_header", "main10c.html#DASMDOC_S59", null ],
        [ "kernel_sBootstrapName", "main10c.html#DASMDOC_S60", null ],
        [ "kernel_size", "main10c.html#DASMDOC_S61", null ]
      ] ],
      [ "Functions", "main10c.html#DASMDOC_S62", [
        [ "kernel_main", "main10c.html#DASMDOC_S63", null ],
        [ "kernel_initThreadEp", "main10c.html#DASMDOC_S64", null ]
      ] ]
    ] ],
    [ "memory10c", "memory10c.html", [
      [ "Memory Manager", "memory10c.html#memoryManager", [
        [ "Memory Management", "memory10c.html#memoryManagerDetails", null ],
        [ "Reserving Manager", "memory10c.html#memoryManagerReservingMemory", null ],
        [ "Memory Swapping", "memory10c.html#memoryManagerMemorySwapping", null ]
      ] ],
      [ "Constants", "memory10c.html#DASMDOC_S65", [
        [ "MEMORY_CHUNK_SIZE", "memory10c.html#DASMDOC_S66", null ],
        [ "MEMORY_MAX_CHUNKS", "memory10c.html#DASMDOC_S67", null ],
        [ "MEMORY_CHUNK_LASTINDEX", "memory10c.html#DASMDOC_S68", null ],
        [ "MEMORY_ALLOCATIONBITMAP_SIZE", "memory10c.html#DASMDOC_S69", null ]
      ] ],
      [ "Data", "memory10c.html#DASMDOC_S70", [
        [ "memory_allocationBitmap", "memory10c.html#DASMDOC_S71", null ],
        [ "memory_accessMutex", "memory10c.html#DASMDOC_S72", null ]
      ] ],
      [ "Functions", "memory10c.html#DASMDOC_S73", [
        [ "memory_init", "memory10c.html#DASMDOC_S74", null ],
        [ "memory_reserve", "memory10c.html#DASMDOC_S75", null ],
        [ "memory_allocate", "memory10c.html#DASMDOC_S76", null ],
        [ "memory_free", "memory10c.html#DASMDOC_S77", null ],
        [ "memory_copy", "memory10c.html#DASMDOC_S78", null ]
      ] ]
    ] ],
    [ "mutex10c", "mutex10c.html", [
      [ "MutexManager", "mutex10c.html#mutex", [
        [ "Module Details", "mutex10c.html#MUTEXDetails", null ],
        [ "Mutexes", "mutex10c.html#MutexManager", null ]
      ] ],
      [ "Constants", "mutex10c.html#DASMDOC_S79", [
        [ "MUTEX_INVALIDMUTEX", "mutex10c.html#DASMDOC_S80", null ],
        [ "MUTEX_TABLE_ENTRIES", "mutex10c.html#DASMDOC_S81", null ]
      ] ],
      [ "Data", "mutex10c.html#DASMDOC_S82", [
        [ "mutex_mutexAllocationTable", "mutex10c.html#DASMDOC_S83", null ],
        [ "mutex_mutexStateTable", "mutex10c.html#DASMDOC_S84", null ]
      ] ],
      [ "Functions", "mutex10c.html#DASMDOC_S85", [
        [ "mutex_create", "mutex10c.html#DASMDOC_S86", null ],
        [ "mutex_destroy", "mutex10c.html#DASMDOC_S87", null ],
        [ "mutex_lock", "mutex10c.html#DASMDOC_S88", null ],
        [ "mutex_wait", "mutex10c.html#DASMDOC_S89", null ],
        [ "mutex_release", "mutex10c.html#DASMDOC_S90", null ]
      ] ]
    ] ],
    [ "peLoader10c", "pe_loader10c.html", [
      [ "PeLoader", "pe_loader10c.html#PeLoader", [
        [ "Module Details", "pe_loader10c.html#peLoaderDetails", null ],
        [ "Decription of Executables", "pe_loader10c.html#peLoaderExec", null ],
        [ "Export Table", "pe_loader10c.html#peLoaderExportTable", null ],
        [ "IAT/EAT", "pe_loader10c.html#peLoaderImportExport", null ],
        [ "Flags & Next", "pe_loader10c.html#peLoaderPeFlags", null ],
        [ "Relocation Table", "pe_loader10c.html#peLoaderRelocTable", null ]
      ] ],
      [ "Constants", "pe_loader10c.html#DASMDOC_S91", [
        [ "PEIMAGE_SIGNATURE", "pe_loader10c.html#DASMDOC_S92", null ],
        [ "PEIMAGE_NAMELEN", "pe_loader10c.html#DASMDOC_S93", null ],
        [ "PEIMAGE_INVALID_NEXT", "pe_loader10c.html#DASMDOC_S94", null ],
        [ "PEIMAGE_INVALID_IMPORT", "pe_loader10c.html#DASMDOC_S95", null ],
        [ "PEIMAGE_INVALID_EXPORT", "pe_loader10c.html#DASMDOC_S96", null ],
        [ "PEIMAGE_OFFSET_SIGNATURE", "pe_loader10c.html#DASMDOC_S97", null ],
        [ "PEIMAGE_OFFSET_PEFLAGS", "pe_loader10c.html#DASMDOC_S98", null ],
        [ "PEIMAGE_OFFSET_NEXT", "pe_loader10c.html#DASMDOC_S99", null ],
        [ "PEIMAGE_OFFSET_NAME", "pe_loader10c.html#DASMDOC_S100", null ],
        [ "PEIMAGE_OFFSET_RVA_ENTRY_POINT", "pe_loader10c.html#DASMDOC_S101", null ],
        [ "PEIMAGE_OFFSET_RVA_IMPORT_TABLE", "pe_loader10c.html#DASMDOC_S102", null ],
        [ "PEIMAGE_OFFSET_RVA_EXPORT_TABLE", "pe_loader10c.html#DASMDOC_S103", null ],
        [ "PEIMAGE_OFFSET_RVA_RELOCATION_TABLE", "pe_loader10c.html#DASMDOC_S104", null ],
        [ "PEIMAGE_OFFSET_IMAGE_SIZE", "pe_loader10c.html#DASMDOC_S105", null ],
        [ "PEIMAGE_OFFSET_IMAGE_MD5SPECHASH", "pe_loader10c.html#DASMDOC_S106", null ],
        [ "PEIMAGE_PEFLAG_FORCEINIT", "pe_loader10c.html#DASMDOC_S107", null ]
      ] ],
      [ "Data", "pe_loader10c.html#DASMDOC_S108", [
        [ "peLoader_root", "pe_loader10c.html#DASMDOC_S109", null ]
      ] ],
      [ "Functions", "pe_loader10c.html#DASMDOC_S110", [
        [ "peLoader_loadImage", "pe_loader10c.html#DASMDOC_S111", null ],
        [ "peLoader_initImage", "pe_loader10c.html#DASMDOC_S112", null ],
        [ "peLoader_findLastImage", "pe_loader10c.html#DASMDOC_S113", null ],
        [ "peLoader_findImage", "pe_loader10c.html#DASMDOC_S114", null ],
        [ "peLoader_findImageEx", "pe_loader10c.html#DASMDOC_S115", null ],
        [ "peLoader_findExport", "pe_loader10c.html#DASMDOC_S116", null ]
      ] ]
    ] ],
    [ "threading10c", "threading10c.html", [
      [ "Threading", "threading10c.html#mutlithreading", [
        [ "Module Details", "threading10c.html#mutlithreadingDetails", null ],
        [ "Threads", "threading10c.html#threads", null ],
        [ "Locking Thread Manager", "threading10c.html#lockingthreadm", null ],
        [ "TEB", "threading10c.html#threadingTeb", null ],
        [ "ThreadContext", "threading10c.html#threadingContext", null ]
      ] ],
      [ "Constants", "threading10c.html#DASMDOC_S117", [
        [ "THREADING_INVALIDENTRY", "threading10c.html#DASMDOC_S118", null ],
        [ "THREADCONTEXT_SIZE", "threading10c.html#DASMDOC_S119", null ],
        [ "THREADCONTEXT_OFFSET_END", "threading10c.html#DASMDOC_S120", null ],
        [ "THREADCONTEXT_OFFSET_PC", "threading10c.html#DASMDOC_S121", null ],
        [ "THREADCONTEXT_OFFSET_SP", "threading10c.html#DASMDOC_S122", null ],
        [ "THREADCONTEXT_OFFSET_EX", "threading10c.html#DASMDOC_S123", null ],
        [ "THREADCONTEXT_OFFSET_A", "threading10c.html#DASMDOC_S124", null ],
        [ "THREADCONTEXT_OFFSET_B", "threading10c.html#DASMDOC_S125", null ],
        [ "THREADCONTEXT_OFFSET_C", "threading10c.html#DASMDOC_S126", null ],
        [ "THREADCONTEXT_OFFSET_X", "threading10c.html#DASMDOC_S127", null ],
        [ "THREADCONTEXT_OFFSET_Y", "threading10c.html#DASMDOC_S128", null ],
        [ "THREADCONTEXT_OFFSET_Z", "threading10c.html#DASMDOC_S129", null ],
        [ "THREADCONTEXT_OFFSET_I", "threading10c.html#DASMDOC_S130", null ],
        [ "THREADCONTEXT_OFFSET_J", "threading10c.html#DASMDOC_S131", null ],
        [ "THREADCONTEXT_OFFSET_NEXT", "threading10c.html#DASMDOC_S132", null ],
        [ "THREADCONTEXT_TEB_OFFSET", "threading10c.html#DASMDOC_S133", null ],
        [ "THREADCONTEXT_TEB_OFFSET_PARENTIMAGE", "threading10c.html#DASMDOC_S134", null ],
        [ "THREADING_STATE_NORMAL", "threading10c.html#DASMDOC_S135", null ],
        [ "THREADING_STATE_LOCKED", "threading10c.html#DASMDOC_S136", null ]
      ] ],
      [ "Data", "threading10c.html#DASMDOC_S137", [
        [ "threading_activeThread", "threading10c.html#DASMDOC_S138", null ],
        [ "threading_rootThread", "threading10c.html#DASMDOC_S139", null ],
        [ "threading_state", "threading10c.html#DASMDOC_S140", null ]
      ] ],
      [ "Functions", "threading10c.html#DASMDOC_S141", [
        [ "threading_endCycle", "threading10c.html#DASMDOC_S142", null ],
        [ "threading_createThread", "threading10c.html#DASMDOC_S143", null ],
        [ "threading_createThreadEx", "threading10c.html#DASMDOC_S144", null ],
        [ "threading_removeThread", "threading10c.html#DASMDOC_S145", null ],
        [ "threading_lock", "threading10c.html#DASMDOC_S146", null ],
        [ "threading_free", "threading10c.html#DASMDOC_S147", null ],
        [ "threading_endOfThread", "threading10c.html#DASMDOC_S148", null ],
        [ "threading_interrupt", "threading10c.html#DASMDOC_S149", null ]
      ] ]
    ] ],
    [ "vfs10c", "vfs10c.html", [
      [ "VFS", "vfs10c.html#virtualFileSystem", [
        [ "Module Details", "vfs10c.html#virtualFileSystemDetails", null ],
        [ "Kernel VFS", "vfs10c.html#virtualFileSystemVFS", null ],
        [ "File Descriptors", "vfs10c.html#virtualFileSystemFileDesc", null ],
        [ "Mount Point Layout", "vfs10c.html#virtualFileSystemMountLayout", null ],
        [ "File Layout", "vfs10c.html#virtualFileSystemFileLayout", null ],
        [ "File Flags", "vfs10c.html#vfsFileFlags", null ]
      ] ],
      [ "Constants", "vfs10c.html#DASMDOC_S150", [
        [ "VFS_MAXMOUNTS", "vfs10c.html#DASMDOC_S151", null ],
        [ "VFS_MOUNTPOINT_OFFSET_MEDIASTORAGEDRIVER", "vfs10c.html#DASMDOC_S152", null ],
        [ "VFS_MOUNTPOINT_OFFSET_FILESYSTEMDRIVER", "vfs10c.html#DASMDOC_S153", null ],
        [ "VFS_MOUNTPOINT_SIZE", "vfs10c.html#DASMDOC_S154", null ],
        [ "VFS_FILE_OFFSET_LENGTH", "vfs10c.html#DASMDOC_S155", null ],
        [ "VFS_FILE_OFFSET_FILEFLAGS", "vfs10c.html#DASMDOC_S156", null ],
        [ "VFS_FILE_OFFSET_CURSOR", "vfs10c.html#DASMDOC_S157", null ],
        [ "VFS_FILE_OFFSET_FILEIDHI", "vfs10c.html#DASMDOC_S158", null ],
        [ "VFS_FILE_OFFSET_FILEIDLO", "vfs10c.html#DASMDOC_S159", null ],
        [ "VFS_FILE_OFFSET_MOUNTPOINT", "vfs10c.html#DASMDOC_S160", null ],
        [ "VFS_FILE_OFFSET_SECTORSIZE", "vfs10c.html#DASMDOC_S161", null ],
        [ "VFS_FILE_OFFSET_MEDIAREAD", "vfs10c.html#DASMDOC_S162", null ],
        [ "VFS_FILE_OFFSET_MEDIAWRITE", "vfs10c.html#DASMDOC_S163", null ],
        [ "VFS_FILE_OFFSET_LASTMEMBER", "vfs10c.html#DASMDOC_S164", null ],
        [ "VFS_FILE_SIZE", "vfs10c.html#DASMDOC_S165", null ],
        [ "VFS_NAMELEN", "vfs10c.html#DASMDOC_S166", null ],
        [ "VFS_FILE_FILEFLAGS_DIRECTORY", "vfs10c.html#DASMDOC_S167", null ],
        [ "VFS_FILE_FILEFLAGS_EOF", "vfs10c.html#DASMDOC_S168", null ]
      ] ],
      [ "Data", "vfs10c.html#DASMDOC_S169", [
        [ "vfs_mounts", "vfs10c.html#DASMDOC_S170", null ]
      ] ],
      [ "Functions", "vfs10c.html#DASMDOC_S171", [
        [ "vfs_getMountFilesystem", "vfs10c.html#DASMDOC_S172", null ],
        [ "vfs_getMountMediaStorage", "vfs10c.html#DASMDOC_S173", null ],
        [ "vfs_findFreeMount", "vfs10c.html#DASMDOC_S174", null ],
        [ "vfs_createMount", "vfs10c.html#DASMDOC_S175", null ],
        [ "vfs_endMount", "vfs10c.html#DASMDOC_S176", null ],
        [ "vfs_fOpenFile", "vfs10c.html#DASMDOC_S177", null ],
        [ "vfs_fGetRoot", "vfs10c.html#DASMDOC_S178", null ],
        [ "vfs_fOpen", "vfs10c.html#DASMDOC_S179", null ],
        [ "vfs_fClose", "vfs10c.html#DASMDOC_S180", null ],
        [ "vfs_fRead", "vfs10c.html#DASMDOC_S181", null ],
        [ "vfs_fEnum", "vfs10c.html#DASMDOC_S182", null ]
      ] ]
    ] ]
];