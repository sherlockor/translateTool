#include <string.h>
#include <iostream>
#include <fstream>
#include "translate_factory.h"
#include "google_translate.h"
#include <QString>
#include <QDebug>
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

    BaseTranslate::Release();

    return 0;
}
