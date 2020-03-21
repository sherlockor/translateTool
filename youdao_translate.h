#ifndef YOUDAO_TRANSLATE_H
#define YOUDAO_TRANSLATE_H

#include "base_translate.h"

class YouDaoTranslate : public BaseTranslate
{
public:
    explicit YouDaoTranslate();
    virtual ~YouDaoTranslate();

    /*
     * @brief       翻译接口
     * @param[in]   src         需要翻译的字符串
     * @param[in]   targetCode  目标编码，可以为空，为空则表示自动检测
     * @return      翻译结果，错误则为空
     * @author      sherlock_lin
     */
    virtual void Translate(const std::string& src, libTranslateDefine::LanguageCode targetCode = libTranslateDefine::zh_CN) override;

    virtual void Read(const std::string& src) const override;

    virtual void ProcessResponse(const std::string& response) const override;

    virtual bool IsSupportVoice() const override;

public:
    static size_t GetResponse(char *ptr, size_t size, size_t nmemb, void *userData);

    static size_t GetVoiceResponse(char* ptr, size_t size, size_t nmemb, void* userData);

    static size_t GetResponseHeader(char* buffer, size_t size, size_t nitems, void* userData);
};

#endif  //YOUDAO_TRANSLATE_H
