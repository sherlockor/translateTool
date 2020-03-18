#ifndef TRANSLATE_FACTORY_H
#define TRANSLATE_FACTORY_H

#include "base_translate.h"
#include <memory>

class TranslateFactory
{
public:
    explicit TranslateFactory();
    virtual ~TranslateFactory();

    enum TranslatePlatform
    {
        Google = 0,
        Youdao,
    };

    std::shared_ptr<BaseTranslate> GetTranslateInstance(TranslatePlatform platform) const;
};


#endif  //TRANSLATE_FACTORY_H
