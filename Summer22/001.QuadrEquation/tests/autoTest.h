#include "TestResult.h"

namespace autoTest {
    FILE* openTestFile(int argc, char** argv);

    bool runTest(TestResult(*testFunction) (FILE* inputFile), const char* name, char* command, FILE* testFile);
}
