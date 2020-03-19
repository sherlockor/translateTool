#ifndef GOOGLE_TRANSLATE_H
#define GOOGLE_TRANSLATE_H

#include "base_translate.h"

class GoogleTranslate : public BaseTranslate
{
public:
    explicit GoogleTranslate();
    virtual ~GoogleTranslate();

    /*
     * @brief       翻译接口
     * @param[in]   src         需要翻译的字符串
     * @param[in]   targetCode  目标编码，可以为空，为空则表示翻译成中文
     * @return      翻译结果，错误则为空
     * @author      sherlock_lin
     */
    void Translate(const std::string& src, libTranslateDefine::LanguageCode targetCode = libTranslateDefine::zh_CN) override;

    void ProcessResponse(const std::string& response) const override;

public:
    static size_t GetResponse(char *ptr, size_t size, size_t nmemb, void *userdata);

};


#endif //GOOGLE_TRANSLATE_H
