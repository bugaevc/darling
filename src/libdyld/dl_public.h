/*
This file is part of Darling.

Copyright (C) 2015 Lubos Dolezel

Darling is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Darling is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Darling.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DL_PUBLIC_H
#define DL_PUBLIC_H
#include <dlfcn.h>
#include <string>

#define DARWIN_RTLD_LAZY		0x1
#define DARWIN_RTLD_NOW			0x2
#define DARWIN_RTLD_LOCAL		0x4
#define DARWIN_RTLD_GLOBAL		0x8
#define DARWIN_RTLD_NOLOAD		0x10
#define DARWIN_RTLD_NODELETE	0x80
#define DARWIN_RTLD_FIRST		0x100

#define DARWIN_RTLD_NEXT		((void*)-1)
#define DARWIN_RTLD_DEFAULT		((void*)-2)
#define DARWIN_RTLD_SELF		((void*)-3)
#define DARWIN_RTLD_MAIN_ONLY	((void*)-5)

#define NSLINKMODULE_OPTION_NONE		0x0
#define NSLINKMODULE_OPTION_BINDNOW		0x1
#define NSLINKMODULE_OPTION_PRIVATE		0x2
#define NSLINKMODULE_OPTION_RETURN_ON_ERROR	0x4
#define NSLINKMODULE_OPTION_DONT_CALL_MOD_INIT_ROUTINES 0x8
#define NSLINKMODULE_OPTION_TRAILING_PHYS_NAME	0x10

typedef enum {
    NSLinkEditFileAccessError,
    NSLinkEditFileFormatError,
    NSLinkEditMachResourceError,
    NSLinkEditUnixResourceError,
    NSLinkEditOtherError,
    NSLinkEditWarningError,
    NSLinkEditMultiplyDefinedError,
    NSLinkEditUndefinedError
} NSLinkEditErrors;

typedef enum {
    NSObjectFileImageFailure,
    NSObjectFileImageSuccess,
    NSObjectFileImageInappropriateFile,
    NSObjectFileImageArch,
    NSObjectFileImageFormat,
    NSObjectFileImageAccess
} NSObjectFileImageReturnCode;

namespace Darling
{
	class LoadableObject;
	
	typedef bool (*DlsymHookFunc)(char* symName);
	void registerDlsymHook(DlsymHookFunc func);
	void deregisterDlsymHook(DlsymHookFunc func);
	
	void dl_setLastError(const std::string& str);
}

typedef void* NSSymbol;
typedef Darling::LoadableObject* NSModule;
typedef void* NSObjectFileImage;

extern "C"
{

void* __darwin_dlopen(const char* filename, int flag);
int __darwin_dlclose(void* handle);
const char* __darwin_dlerror(void);
void* __darwin_dlsym(void* handle, const char* symbol);
int __darwin_dladdr(void *addr, Dl_info *info);

void __darling_get_args(int** argc, char**** argv, char**** environ, struct ProgramVars* vars);

// Obsolete (or "not recommended") APIs
NSSymbol NSLookupAndBindSymbol(const char* symbolName);
void* NSAddressOfSymbol(NSSymbol nssymbol);
NSSymbol NSLookupSymbolInModule(NSModule module, const char* symbolName);
const char* NSNameOfSymbol(NSSymbol nssymbol);
int NSIsSymbolNameDefined(const char* name);
NSModule NSModuleForSymbol(NSSymbol symbol);
int NSIsSymbolNameDefinedInImage(const struct mach_header *image, const char *symbolName);
const char* NSNameOfModule(NSModule m); 
const char* NSLibraryNameForModule(NSModule m);

NSObjectFileImageReturnCode NSCreateObjectFileImageFromFile(const char* pathName, NSObjectFileImage * objectFileImage);
NSModule NSLinkModule( NSObjectFileImage objectFileImage, const char* moduleName, uint32_t options);
bool NSDestroyObjectFileImage( NSObjectFileImage objectFileImage);
bool NSUnLinkModule( NSModule module, uint32_t options);
void NSLinkEditError(NSLinkEditErrors *c, int *errorNumber, const char** fileName, const char** errorString);

typedef struct {
     void     (*undefined)(const char* symbolName);
     NSModule (*multiple)(NSSymbol s, NSModule oldModule, NSModule newModule); 
     void     (*linkEdit)(NSLinkEditErrors errorClass, int errorNumber,
                          const char* fileName, const char* errorString);
} NSLinkEditErrorHandlers;

void NSInstallLinkEditErrorHandlers(const NSLinkEditErrorHandlers *handlers);

// TODO: rest of these NS* calls if used anywhere

}

#endif

