#ifndef CPP06_EX00_CONSTANTS_HPP_
# define CPP06_EX00_CONSTANTS_HPP_

# include <string>

# ifdef COLORLESS
namespace Constants {
    const std::string kTextInfo         = "";
    const std::string kTextWarning      = "";
    const std::string kTextError        = "";
    const std::string kTextLifeCycle    = "";
    const std::string kTextReset        = "";
}
# else
namespace Constants {
    const std::string kTextInfo         = "\x1B[92m";
    const std::string kTextWarning      = "\x1B[95m";
    const std::string kTextError        = "\x1B[91m";
    const std::string kTextLifeCycle    = "\x1B[94m";
    const std::string kTextReset        = "\x1B[m";
}
# endif

#endif
