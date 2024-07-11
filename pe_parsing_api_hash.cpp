#include <stdio.h>
#include <windows.h>
#include <winternl.h>

extern "C" DWORD calculate_api_hash(char *api_name);
extern "C" DWORD calculate_dll_hash(wchar_t *dll_name, DWORD dll_length);
// extern "C" DWORD32 __ROR__(DWORD32 value, BYTE count);

char *get_api_name_from_hash(DWORD hash_value) {

    wchar_t *kernel32 = (wchar_t*)L"kernel32.dll";
    wchar_t *ntdll = (wchar_t*)L"ntdll.dll";
    wchar_t *wininet = (wchar_t*)L"wininet.dll";

    wchar_t *dll_list[] = {kernel32, ntdll, wininet};

    for (int i = 0; i < 3; i++) {

        unsigned char *dll_base = (unsigned char*)LoadLibraryW(dll_list[i]);
        wchar_t *dll_name = (wchar_t*)dll_list[i];

        IMAGE_DOS_HEADER *dos_header = (IMAGE_DOS_HEADER*)dll_base;
        IMAGE_NT_HEADERS *nt_header = (IMAGE_NT_HEADERS*)(dos_header->e_lfanew + dll_base);

        IMAGE_EXPORT_DIRECTORY *export_directory = (IMAGE_EXPORT_DIRECTORY*)(dll_base + nt_header->OptionalHeader.DataDirectory[0].VirtualAddress);
        DWORD *names = (DWORD*)(dll_base + export_directory->AddressOfNames);
        DWORD *functions = (DWORD*)(dll_base + export_directory->AddressOfFunctions);
        WORD *ordinals = (WORD*)(dll_base + export_directory->AddressOfNameOrdinals);

        DWORD dll_hash = calculate_dll_hash(dll_name, 2 * (wcslen(dll_name) + 1));

        for (int i = 0; i < export_directory->NumberOfNames; i++) {

            WORD ordinal = ordinals[i];
            char *api_name = (char*)(dll_base + names[ordinal]);
            DWORD *func = (DWORD*)(dll_base + functions[2 * ordinal]);

            DWORD api_hash = calculate_api_hash(api_name);

            if (api_hash + dll_hash == hash_value) {
                return api_name;
            }
        }
    }

    return NULL;
}


int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("usage: %s <api_hash>", argv[0]);
        return 0;
    }

    DWORD api_hash;
    sscanf(argv[1], "%x", &api_hash);

    printf("found api: %s\n", get_api_name_from_hash(api_hash));

    return 0;
}
