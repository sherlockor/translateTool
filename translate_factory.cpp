#include "translate_factory.h"
#include "google_translate.h"
#include "youdao_translate.h"

TranslateFactory::TranslateFactory()
{

}

TranslateFactory::~TranslateFactory()
{

}

std::shared_ptr<BaseTranslate> TranslateFactory::GetTranslateInstance(TranslateFactory::TranslatePlatform platform) const
{
    std::shared_ptr<BaseTranslate> baseTranslate = NULL;
    switch(platform)
    {
    case Google:
        baseTranslate = std::make_shared<GoogleTranslate>();
        break;
    case Youdao:
        baseTranslate = std::make_shared<YouDaoTranslate>();
        break;
    default:
        baseTranslate = NULL;
        break;
    }

    return baseTranslate;
}
