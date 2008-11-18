#ifndef _PLMESSAGE_H
#define _PLMESSAGE_H

#include "PRP/plCreatable.h"
#include "Util/hsTArray.hpp"
#include "PRP/KeyedObject/plKey.h"

DllClass plMessage : public plCreatable {
public:
    enum plBCastFlags {
        kBCastNone = 0x0,
        kBCastByType = 0x1,
        kBCastUNUSED_0 = 0x2,
        kPropagateToChildren = 0x4,
        kBCastByExactType = 0x8,
        kPropagateToModifiers = 0x10,
        kClearAfterBCast = 0x20,
        kNetPropagate = 0x40,
        kNetSent = 0x80,
        kNetUseRelevanceRegions = 0x100,
        kNetForce = 0x200,
        kNetNonLocal = 0x400,
        kLocalPropagate = 0x800,
        kNetNonDeterministic = 0x200,
        kMsgWatch = 0x1000,
        kNetStartCascade = 0x2000,
        kNetAllowInterAge = 0x4000,
        kNetSendUnreliable = 0x8000,
        kCCRSendToAllPlayers = 0x10000,
        kNetCreatedRemotely = 0x20000
    };

protected:
    plWeakKey fSender;
    hsTArray<plWeakKey> fReceivers;
    double fTimeStamp;
    unsigned int fBCastFlags;

public:
    plMessage();
    virtual ~plMessage();

    DECLARE_CREATABLE(plMessage)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    void IMsgRead(hsStream* S, plResManager* mgr);
    void IMsgWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plWeakKey getSender() const;
    double getTimeStamp() const;
    unsigned int getBCastFlags() const;

    void setSender(plWeakKey sender);
    void setTimeStamp(double timestamp);
    void setBCastFlags(unsigned int flags);

    size_t getNumReceivers() const;
    plWeakKey getReceiver(size_t idx) const;
    void addReceiver(plWeakKey receiver);
    void delReceiver(size_t idx);
    void clearReceivers();
};

#endif