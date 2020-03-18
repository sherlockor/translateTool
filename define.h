#ifndef DEFINE_H
#define DEFINE_H

#include <string>

namespace libTranslateDefine {
    enum LanguageCode{
        zh_CN = 0,
        zh_TW,
        en,
        en_US,
        Other
    };
    const std::string languageCodeStr [Other] = {
        "zh-CN",
        "zh-TW",
        "en",
        "en-US",
    };
}


#endif  //DEFINE_H
