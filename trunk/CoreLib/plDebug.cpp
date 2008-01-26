#include "plDebug.h"
#include <cstdarg>
#include <cstdlib>

hsStream* plDebug::fDebugStream = NULL;
int plDebug::fDebugLevel = kDLNone;
bool plDebug::fIOwnStream = false;

void plDebug::Init(int level, hsStream* stream) {
    fDebugLevel = level;
    if (stream == NULL) {
        fDebugStream = new hsStdioStream(true);
        fIOwnStream = true;
    } else {
        fDebugStream = stream;
        fIOwnStream = false;
    }

    // Register cleanup
    atexit(&plDebug::DeInit);
}

void plDebug::DeInit() {
    if (fIOwnStream && (fDebugStream != NULL))
        delete fDebugStream;
}

void plDebug::Error(const char* fmt, ...) {
    if (fDebugStream == NULL)
        Init();
    if (fDebugLevel >= kDLError) {
        va_list aptr;
        va_start(aptr, fmt);
        WriteLn(fmt, aptr);
        va_end(aptr);
    }
}

void plDebug::Warning(const char* fmt, ...) {
    if (fDebugStream == NULL)
        Init();
    if (fDebugLevel >= kDLWarning) {
        va_list aptr;
        va_start(aptr, fmt);
        WriteLn(fmt, aptr);
        va_end(aptr);
    }
}

void plDebug::Debug(const char* fmt, ...) {
    if (fDebugStream == NULL)
        Init();
    if (fDebugLevel >= kDLDebug) {
        va_list aptr;
        va_start(aptr, fmt);
        WriteLn(fmt, aptr);
        va_end(aptr);
    }
}

void plDebug::WriteLn(const char* fmt, va_list args) {
    fDebugStream->writeLine(plString::FormatV(fmt, args));
}