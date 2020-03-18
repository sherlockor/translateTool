#include <string.h>
#include <iostream>
#include <fstream>
#include "translate_factory.h"
#include "google_translate.h"
#include "youdao_translate.h"
#include <QDebug>
#include <QString>
using namespace std;

void PrintResutl(const std::string& response, void* userData)
{
    qDebug()<<QString::fromStdString(response);
}

int main(void)
{
    BaseTranslate::Initlization();

    TranslateFactory factory;
    std::shared_ptr<BaseTranslate> googleTranslte = factory.GetTranslateInstance(TranslateFactory::Google);
    googleTranslte->SetCallback(&PrintResutl, NULL);
    googleTranslte->Translate("my boy friend is handsome", libTranslateDefine::zh_CN);

    std::shared_ptr<BaseTranslate> youdaoTranslate = factory.GetTranslateInstance(TranslateFactory::Youdao);
    youdaoTranslate->SetCallback(&PrintResutl, NULL);
    youdaoTranslate->Translate("我男朋友很帅");

    BaseTranslate::Release();

    return 0;
}
