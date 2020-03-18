#include "google_translate.h"
#include "json/reader.h"

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

void GoogleTranslate::ProcessResponse(const std::string &response)
{
    Json::Reader reader;
    Json::Value root;
    if(!reader.parse(response, root))
    {
        return;
    }
    Json::Value sentences = root["sentences"][0];
    if(sentences)
    {
        std::string trans = sentences["trans"].asString();
        if(m_callBack)
        {
            m_callBack(trans, m_userData);
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
