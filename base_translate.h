#ifndef BASE_TRANSLATE_H
#define BASE_TRANSLATE_H

#include "define.h"
#include "include/curl/curl.h"
#include <string>

/*
 * @brief   回调函数类型
 * @author  sherlock_lin
 */
typedef void(*Callback)(const std::string& response, void* userData);

class BaseTranslate
{
public:
    explicit BaseTranslate();
    virtual ~BaseTranslate();

    /*
     * @brief       翻译接口
     * @param[in]   src         需要翻译的字符串
     * @param[in]   targetCode  目标编码，可以为空
     * @return      翻译结果，错误则为空
     * @author      sherlock_lin
     */
    virtual void Translate(const std::string& src,
                                  libTranslateDefine::LanguageCode targetCode = libTranslateDefine::zh_CN) = 0;

    /*
     * @brief       设置回调函数，当得到翻译结果后，会调用回调函数
     * @param[in]   callback    回调函数指针
     * @param[in]   userData    用户自定义指针，会随着回调函数传回
     * @author      sherlock_lin
     */
    virtual void SetCallback(Callback callback, void* userData);

    /*
     * @brief       处理response
     * @param[in]   response    得到的翻译API的response
     * @author      sherlock_lin
     */
    virtual void ProcessResponse(const std::string& response) const = 0;

public:
    /*
     * @brief   全局初始化，在使用前必须执行并只能执行一次
     * @author  sherlock_lin
     */
    static void GlobalInitlization();

    /*
     * @brief   全局资源释放，程序结束后释放，和GlobalInitlization一一对应
     * @author  sherlock_lin
     */
    static void GlobalRelease();

protected:
    /*
     * @brief   调用回调函数
     * @author  sherlock_lin
     */
    virtual void CallBackFunction(const std::string& result) const;

protected:
    CURL* m_curlHandle;
    curl_slist* m_headerList;
    Callback m_callBack;
    void* m_userData;
};


#endif  //BASE_TRANSLATE_H
