#include <iostream>
#include <windows.h>
#include <vector>

void saveConsoleContent(HANDLE hConsole, COORD bufferSize, std::vector<CHAR_INFO>& buffer) {
    SMALL_RECT readRegion = { 0, 0, bufferSize.X - 1, bufferSize.Y - 1 };
    buffer.resize(bufferSize.X * bufferSize.Y);

    ReadConsoleOutput(hConsole, buffer.data(), bufferSize, { 0, 0 }, &readRegion);
}

void clearConsole() {
    system("cls");
}

void restoreConsoleContent(HANDLE hConsole, COORD bufferSize, const std::vector<CHAR_INFO>& buffer) {
    SMALL_RECT writeRegion = { 0, 0, bufferSize.X - 1, bufferSize.Y - 1 };
    WriteConsoleOutput(hConsole, buffer.data(), bufferSize, { 0, 0 }, &writeRegion);
}

int main() {
    std::cout << "This will be here back later...\n";
    std::cin.get();

    // Get console handle
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get current console screen buffer size
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD bufferSize = csbi.dwSize;

    // Save current console content
    std::vector<CHAR_INFO> consoleBuffer;
    saveConsoleContent(hConsole, bufferSize, consoleBuffer);

    // Clear console
    clearConsole();

    // Output new text
    std::cout << "This is the new text!" << std::endl;

    // Wait for a key press to restore the console content
    std::cout << "Press any key to restore the previous console content...";
    std::cin.get();

    // Restore previous console content
    restoreConsoleContent(hConsole, bufferSize, consoleBuffer);

    return 0;
}