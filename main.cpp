#include <string.h>
#include <iostream>
#include <fstream>
#include "translate_factory.h"
#include "google_translate.h"
#include "youdao_translate.h"
using namespace std;

void PrintResutl(const std::string& response, void* userData)
{
    ofstream stream;
    stream.open("test.mpeg", std::ofstream::binary | std::ofstream::app);
    stream.write(response.c_str(), response.length());
    stream.close();
}

int main(void)
{
    BaseTranslate::GlobalInitlization();

    TranslateFactory factory;
    std::shared_ptr<BaseTranslate> googleTranslte = factory.GetTranslateInstance(TranslateFactory::Google);
    googleTranslte->SetResultCallback(&PrintResutl, NULL);
    googleTranslte->Translate("my boy friend is handsome", libTranslateDefine::zh_CN);

    std::shared_ptr<BaseTranslate> youdaoTranslate = factory.GetTranslateInstance(TranslateFactory::Youdao);
    youdaoTranslate->SetVoiceCallback(&PrintResutl, NULL);
    //youdaoTranslate->Translate("支持全球27个语种的高质量互译服务");
    youdaoTranslate->Read("我是谁");

    BaseTranslate::GlobalRelease();

    return 0;
}
