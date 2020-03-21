#include "google_translate.h"
#include "json/reader.h"
#include <memory>

namespace
{
    const std::string SRC_URL = "http://translate.google.cn/translate_a/single?"
                            "client=gtx&dt=t&dj=1&ie=UTF-8&sl=auto";
}

GoogleTranslate::GoogleTranslate()
{
    if(m_curlHandle)
    {
        curl_easy_setopt(m_curlHandle, CURLOPT_WRITEFUNCTION, GoogleTranslate::GetResponse);
        curl_easy_setopt(m_curlHandle, CURLOPT_WRITEDATA, (void*)this);
    }
}

GoogleTranslate::~GoogleTranslate()
{

}

void GoogleTranslate::Translate(const std::string &src, libTranslateDefine::LanguageCode targetCode)
{
    if(!m_curlHandle)
    {
        return;
    }

    char* escapeControl = curl_easy_escape(m_curlHandle, src.c_str(), src.size());
    std::string url = SRC_URL
            + "&tl=" + libTranslateDefine::languageCodeStr[targetCode]
            + "&q="+std::string(escapeControl);
    curl_free(escapeControl);

    curl_easy_setopt(m_curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(m_curlHandle, CURLOPT_WRITEFUNCTION, GoogleTranslate::GetResponse);
    curl_easy_setopt(m_curlHandle, CURLOPT_WRITEDATA, (void*)this);

    curl_easy_perform(m_curlHandle);
}

void GoogleTranslate::ProcessResponse(const std::string &response) const
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
    Json::Value sentences = root["sentences"];
    if(sentences && sentences.isArray())
    {
        Json::Value result = sentences[0]["trans"];
        if(result)
        {
            std::string trans = result.asString();
            CallBackFunction(trans);
        }
    }
}

size_t GoogleTranslate::GetResponse(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    std::string response(ptr, size*nmemb);

    GoogleTranslate* googleTranslate = (GoogleTranslate*)userdata;
    googleTranslate->ProcessResponse(response);
    return size*nmemb;
}
