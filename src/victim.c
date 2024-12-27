#include <stdio.h>
#include <windows.h>

#pragma optimize("", off)
__declspec(dllexport, noinline) const char* GibMessage() {
  return "I'm fine!";
}

int main() {
  int count = 0;
  while (1) {
    const char* message = GibMessage();
    if (!message) {
      printf("GibMessage returned NULL\n");
      return 1;
    }
    printf("%p %s %d\n", &GibMessage, message, count++);
    Sleep(500);
  }
  return 0;
}
#pragma optimize("", on) 