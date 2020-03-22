#ifndef BASE_TRANSLATE_H
#define BASE_TRANSLATE_H

#include "define.h"
#include "include/curl/curl.h"
#include <string>

/*
 * @brief       回调函数类型
 * @author      sherlock_lin
 * @param[in]   response    如果是执行文字翻译，则表示翻译结果；如果是阅读，则表示音频数据
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
     * @brief       读单词
     * @param[in]   src     需要读的单词
     */
    virtual void Read(const std::string& src) const = 0;

    /*
     * @brief       设置回调函数，当得到翻译结果后，会调用回调函数
     * @param[in]   callback    回调函数指针
     * @param[in]   userData    用户自定义指针，会随着回调函数传回
     * @author      sherlock_lin
     */
    virtual void SetResultCallback(Callback callback, void* userData);

    /*
     * @brief       设置回调函数，当得到发音后，会调用回调函数
     * @param[in]   callback    回调函数指针
     * @param[in]   userData    用户自定义指针，会随着回调函数传回
     * @author      sherlock_lin
     */
    virtual void SetVoiceCallback(Callback callback, void* userData);

    /*
     * @brief       处理response
     * @param[in]   response    得到的翻译API的response
     * @author      sherlock_lin
     */
    virtual void ProcessResponse(const std::string& response) const = 0;

    /*
     * @brief   返回是否支持发音
     * @author  sherlock_lin
     */
    virtual bool IsSupportVoice() const = 0;

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
     * @brief   调用翻译结果回调函数
     * @author  sherlock_lin
     */
    virtual void CallBackResultFunction(const std::string& result) const;

    /*
     * @brief   调用发言回调函数
     * @author  sherlock_lin
     */
    virtual void CallBackVoiceFunction(const std::string& voiceStreamData) const;

protected:
    CURL* m_curlHandle;
    curl_slist* m_headerList;

    //设定用于获取翻译结果的回调函数
    Callback m_resultCallBack;
    void* m_resultUserData;

    //设定用于获取发音的回调函数
    Callback m_voiceCallBack;
    void* m_voiceUserData;
};


#endif  //BASE_TRANSLATE_H
