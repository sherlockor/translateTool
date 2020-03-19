#include "base_translate.h"

BaseTranslate::BaseTranslate() :m_curlHandle(NULL), m_headerList(NULL), m_callBack(NULL), m_userData(NULL)
{
    m_curlHandle = curl_easy_init();
    if(m_curlHandle && !m_headerList)
    {
        m_headerList = curl_slist_append(m_headerList,"Accept:*/*");
        m_headerList = curl_slist_append(m_headerList,"User-Agent:Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)");
        m_headerList = curl_slist_append(m_headerList,"Connection:keep-alive");

        curl_easy_setopt(m_curlHandle, CURLOPT_HTTPHEADER, m_headerList);
    }
}

BaseTranslate::~BaseTranslate()
{
    if(m_curlHandle)
    {
        curl_easy_cleanup(m_curlHandle);
    }
    if(m_headerList)
    {
        curl_slist_free_all(m_headerList);
    }
}

void BaseTranslate::SetCallback(Callback callback, void *userData)
{
    m_callBack = callback;
    m_userData = userData;
}

void BaseTranslate::CallBackFunction(const std::string &result) const
{
    if(m_callBack)
    {
        m_callBack(result, m_userData);
    }
}

void BaseTranslate::GlobalInitlization()
{
    curl_global_init(CURL_GLOBAL_ALL);
}

void BaseTranslate::GlobalRelease()
{
    curl_global_cleanup();
}
