#ifndef BASE_TRANSLATE_H
#define BASE_TRANSLATE_H

#include "define.h"
#include "include/curl/curl.h"
#include <string>

typedef void(*Callback)(const std::string& response, void* userData);

class BaseTranslate
{
public:
    explicit BaseTranslate();
    virtual ~BaseTranslate();

    /*
     * @brief       翻译接口
     * @param[in]   src         需要翻译的字符串
     * @param[in]   targetCode  目标编码
     * @return      翻译结果，错误则为空
     * @author      sherlock_lin
     */
    virtual void Translate(const std::string& src,
                                  libTranslateDefine::LanguageCode targetCode = libTranslateDefine::zh_CN) = 0;

    virtual void SetCallback(Callback callback, void* m_userData);

    virtual void ProcessResponse(const std::string& response) = 0;

public:
    static void Initlization();
    static void Release();

protected:
    CURL* m_curlHandle;
    curl_slist* m_headerList;
    Callback m_callBack;
    void* m_userData;
};


#endif  //BASE_TRANSLATE_H
