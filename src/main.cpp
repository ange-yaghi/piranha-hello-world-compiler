#include <piranha.h>

#include "../include/language_rules.h"

#include <string>

void printError(const piranha::CompilationError *err) {
    const piranha::ErrorCode_struct &errorCode = err->getErrorCode();
    std::cout
        << err->getCompilationUnit()->getPath().getStem()
        << "(" << err->getErrorLocation()->lineStart << "): error "
        << errorCode.stage << errorCode.code << ": " << errorCode.info << std::endl;

    piranha::IrContextTree *context = err->getInstantiation();
    while (context != nullptr) {
        piranha::IrNode *instance = context->getContext();
        if (instance != nullptr) {
            std::string instanceName = instance->getName();
            std::string definitionName = (instance->getDefinition() != nullptr)
                ? instance->getDefinition()->getName()
                : std::string("<Type Error>");

            std::string formattedName = instanceName.empty()
                ? "<unnamed> " + definitionName
                : instanceName + " " + definitionName;

            std::cout
                << "       While instantiating: "
                << instance->getParentUnit()->getPath().getStem()
                << "(" << instance->getSummaryToken()->lineStart << "): "
                << formattedName << std::endl;
        }

        context = context->getParent();
    }
}

void printErrorTrace(const piranha::ErrorList *errList) {
    int errorCount = errList->getErrorCount();
    for (int i = 0; i < errorCount; i++) {
        printError(errList->getCompilationError(i));
    }
}

int main() {
    std::string fname;
    std::cout << "Input script: ";
    std::cin >> fname;

    LanguageRules rules;
    rules.initialize();
    piranha::Compiler compiler(&rules);
    piranha::IrCompilationUnit *unit = compiler.compile(fname);

    const piranha::ErrorList *errorList = compiler.getErrorList();
    if (errorList->getErrorCount() > 0) {
        std::cout << "There were " << errorList->getErrorCount() << " compilation errors\n";
        printErrorTrace(errorList);
    }
    else {
        std::cout << "Compilation was successful\n";

        // Build the program
        piranha::NodeProgram program;
        unit->build(&program);

        // Write the assembly information
        program.writeAssembly(unit->getPath().getStem() + ".pasm");

        // Run the program
        program.execute();

        // Free the program
        program.free();
    }

    // Free all compiler memory
    compiler.free();

    return 0;
}
