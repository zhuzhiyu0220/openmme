/*
 * loadControlInformationIe.cpp
 *
 * Revisit header later
 *      Author: hariharanb
 */

#ifndef LOADCONTROLINFORMATIONIE_H_
#define LOADCONTROLINFORMATIONIE_H_

#include <map>
#include "manual/gtpV2Ie.h"
#include "manual/gtpV2GroupedIe.h"
#include "gtpV2DataTypes.h"

class LoadControlInformationIe:public GtpV2Ie
{
public:
    LoadControlInformationIe ();
    virtual ~ LoadControlInformationIe ();

    GtpV2GroupedIe & getGroupedIe (Uint8 msgType, Uint8 instance);
    void insertGroupedIeObject (Uint8 msgType, Uint8 instance,
                GtpV2GroupedIe * grpIe_p);

private:
    map < Uint16, GtpV2GroupedIe * >groupedIeObjectContainer;   // map[msgType || instance]
};

#endif
