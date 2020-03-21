#include "youdao_translate.h"
#include "json/reader.h"
#include <iostream>

namespace
{
    const std::string SRC_URL = "http://fanyi.youdao.com/translate?&doctype=json&type=AUTO&i=";
}

YouDaoTranslate::YouDaoTranslate()
{
    if(m_curlHandle)
    {
        curl_easy_setopt(m_curlHandle, CURLOPT_WRITEFUNCTION, YouDaoTranslate::GetResponse);
        curl_easy_setopt(m_curlHandle, CURLOPT_WRITEDATA, (void*)this);
    }
}

YouDaoTranslate::~YouDaoTranslate()
{

}

void YouDaoTranslate::Translate(const std::string &src, libTranslateDefine::LanguageCode targetCode)
{
    if(!m_curlHandle)
    {
        return;
    }

    char* escapeControl = curl_easy_escape(m_curlHandle, src.c_str(), src.size());
    std::string url = SRC_URL + std::string(escapeControl);
    curl_free(escapeControl);

    curl_easy_setopt(m_curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(m_curlHandle, CURLOPT_WRITEFUNCTION, YouDaoTranslate::GetResponse);
    curl_easy_setopt(m_curlHandle, CURLOPT_WRITEDATA, (void*)this);

    curl_easy_perform(m_curlHandle);
}

void YouDaoTranslate::ProcessResponse(const std::string &response) const
{
    Json::CharReaderBuilder builder;
    std::unique_ptr<Json::CharReader> charReader(builder.newCharReader());

    Json::Value root;
    JSONCPP_STRING errorStr;
    if(!charReader->parse(response.c_str(), response.c_str() + response.length(), &root, &errorStr))
    {
        //解析错误
        return;
    }
    Json::Value errorCode = root["errorCode"];
    Json::Value translateResult = root["translateResult"];
    if(0 == errorCode.asInt() && translateResult)
    {
        if(translateResult.isArray() && translateResult[0].isArray())
        {
            Json::Value tgtValue = translateResult[0][0]["tgt"];
            std::string tgt = tgtValue.asString();
            CallBackFunction(tgt);
        }
    }
}

size_t YouDaoTranslate::GetResponse(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    std::string response(ptr, size * nmemb);

    YouDaoTranslate* youdaoTranslate = (YouDaoTranslate*)userdata;
    youdaoTranslate->ProcessResponse(response);
    return size * nmemb;

}

