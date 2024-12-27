#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <MinHook.h>
#include <stdio.h>

typedef const char* (*GibMessage_t)();
GibMessage_t originalGibMessage = NULL;

const char* HookedGibMessage() {
  return "I'm an evil hook!";
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ulReasonForCall, LPVOID lpReserved) {\
  MH_STATUS status;
  HMODULE victimModule;
  void* victimGibMessage;

  if (ulReasonForCall == DLL_PROCESS_ATTACH) {
    victimModule = GetModuleHandle(NULL);
    victimGibMessage = GetProcAddress(victimModule, "GibMessage");
    if (!victimGibMessage) {
      printf("Failed to find GibMessage\n");
      return FALSE;
    }

    status = MH_Initialize();
    if (status != MH_OK && status != MH_ERROR_ALREADY_INITIALIZED) {
      printf("Failed to initialize MinHook\n");
      return FALSE;
    }

    status = MH_CreateHook(victimGibMessage, &HookedGibMessage, (LPVOID*)&originalGibMessage);
    if (status != MH_OK) {
      printf("Failed to create hook\n");
      return FALSE;
    }

    status = MH_EnableHook(MH_ALL_HOOKS);
    if (status != MH_OK) {
      printf("Failed to enable hook\n");
      return FALSE;
    }
  } else if (ulReasonForCall == DLL_PROCESS_DETACH) {
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
  }
  return TRUE;
}