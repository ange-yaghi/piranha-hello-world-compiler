#include "../include/language_rules.h"

LanguageRules::LanguageRules() {
    /* void */
}

LanguageRules::~LanguageRules() {
    /* void */
}

void LanguageRules::registerBuiltinNodeTypes() {
    registerBuiltinType<piranha::NoOpNode>(
        "int_channel", &piranha::FundamentalType::IntType);

    registerBuiltinType<piranha::DefaultLiteralIntNode>(
        "literal_int", &piranha::FundamentalType::IntType);

    registerLiteralType(piranha::LITERAL_INT, "literal_int");
}
