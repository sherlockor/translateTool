#ifndef YOUDAO_TRANSLATE_H
#define YOUDAO_TRANSLATE_H

#include "base_translate.h"

class YouDaoTranslate : public BaseTranslate
{
public:
    explicit YouDaoTranslate();
    virtual ~YouDaoTranslate();

    void Translate(const std::string& src, libTranslateDefine::LanguageCode targetCode = libTranslateDefine::zh_CN) override;

    void ProcessResponse(const std::string& response) override;

public:
    static size_t GetResponse(char *ptr, size_t size, size_t nmemb, void *userdata);
};

#endif  //YOUDAO_TRANSLATE_H
