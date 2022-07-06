#ifndef OPTIONGENERATOR_H
#define OPTIONGENERATOR_H

#include "common/common.h"

#include <QWidget>

namespace dpfservice {

class OptionGenerator : public Generator
{
    Q_OBJECT
public:
    OptionGenerator(){}
    virtual ~OptionGenerator(){}
    virtual QWidget *optionWidget(){ return nullptr; }
};

} // namespace dpfservice

#endif // OPTIONGENERATOR_H