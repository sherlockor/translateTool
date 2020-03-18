#ifndef GOOGLE_TRANSLATE_H
#define GOOGLE_TRANSLATE_H

#include "base_translate.h"

class GoogleTranslate : public BaseTranslate
{
public:
    explicit GoogleTranslate();
    virtual ~GoogleTranslate();

    void Translate(const std::string &src, libTranslateDefine::LanguageCode targetCode = libTranslateDefine::zh_CN) override;

    void ProcessResponse(const std::string& response) override;

public:
    static size_t GetResponse(char *ptr, size_t size, size_t nmemb, void *userdata);

};


#endif //GOOGLE_TRANSLATE_H
